#include "stdafx.h"
#include "CRender.h"
struct SD3DVertex{
	float x, y, z, rhw;
	DWORD colour;
};

typedef struct SPDTVertex
{
	D3DVECTOR	position;
	DWORD	diffuse;
	D3DXVECTOR2 texCoord;
} TPDTVertex;

struct SPDTVertexRaw
{
	float px, py, pz;
	DWORD diffuse;
	float u, v;
};

CRender::CRender() {}
CRender::~CRender() {}

D3DMATRIX CRender::WorldStateCopy;
#ifdef DX9
#define SetVertex SetFVF
#define GetVertex GetFVF
#define IndexBuffer LPDIRECT3DINDEXBUFFER9
#define VertexBuffer LPDIRECT3DVERTEXBUFFER9
#else
#define SetVertex SetVertexShader
#define GetVertex GetVertexShader
#define IndexBuffer LPDIRECT3DINDEXBUFFER8
#define VertexBuffer LPDIRECT3DVERTEXBUFFER8

#endif

DWORD textureFactor;
DWORD colorArg1;
DWORD colorArg2;
DWORD colorOp;
DWORD alphaArg1;
DWORD alphaArg2;
DWORD alphaOp;
DWORD alpaBlend;
DWORD srcBlend;
DWORD destBlend;

DWORD FillOld;
D3DXMATRIX stateold;

DWORD culling;
DWORD Lighting;
DirectTexture Red, Green, Blue, Yellow;
HRESULT GenerateTexture(DirectDevice pDevice, DirectTexture* ppD3Dtex, DWORD colour32)
{
	//pDevice->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex);
	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD* pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

class RestoreStateWithWorld
{
public:
	DWORD	m_dwVS;
	RestoreStateWithWorld(D3DFILLMODE d3dFillMode, const D3DXMATRIX& c_rmatWorld, D3DCOLOR colour)
	{
		//BACKUP
		Device::pDevice->GetVertex(&m_dwVS);
		Device::pDevice->GetRenderState(D3DRS_CULLMODE, &culling);
		Device::pDevice->GetRenderState(D3DRS_FILLMODE, &FillOld);
		Device::pDevice->GetRenderState(D3DRS_TEXTUREFACTOR, &textureFactor);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &colorArg1);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLORARG2, &colorArg2);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &colorOp);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &alphaArg1);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &alphaArg2);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &alphaOp);
		Device::pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &alpaBlend);
		Device::pDevice->GetRenderState(D3DRS_SRCBLEND, &srcBlend);
		Device::pDevice->GetRenderState(D3DRS_DESTBLEND, &destBlend);
		Device::pDevice->GetTransform(D3DTS_WORLD, &stateold);

		//SET VALUES
		Device::pDevice->SetTexture(0, NULL);
		Device::pDevice->SetTexture(1, NULL);
		Device::pDevice->SetPixelShader(NULL);

		Device::pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		Device::pDevice->SetRenderState(D3DRS_FILLMODE, d3dFillMode);
		Device::pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, colour);

		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		Device::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		Device::pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Device::pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Device::pDevice->SetTransform(D3DTS_WORLD, &c_rmatWorld);
	}

	virtual ~RestoreStateWithWorld()
	{
		//RESTORE
		Device::pDevice->SetVertex(m_dwVS);
		Device::pDevice->SetRenderState(D3DRS_CULLMODE, culling);
		Device::pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, textureFactor);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, colorArg1);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, colorArg2);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLOROP, colorOp);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, alphaArg1);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, alphaArg2);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, alphaOp);
		Device::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, alpaBlend);
		Device::pDevice->SetRenderState(D3DRS_SRCBLEND, srcBlend);
		Device::pDevice->SetRenderState(D3DRS_DESTBLEND, destBlend);
		Device::pDevice->SetTransform(D3DTS_WORLD, &stateold);
		Device::pDevice->SetRenderState(D3DRS_FILLMODE, FillOld);
	}
};


DWORD textureFactorGame;
DWORD colorArg1Game;
DWORD colorArg2Game;
DWORD colorOpGame;
DWORD alphaArg1Game;
DWORD alphaArg2Game;
DWORD alphaOpGame;
DWORD alpaBlendGame;
DWORD srcBlendGame;
DWORD destBlendGame;

DWORD FillOldGame;
D3DXMATRIX stateoldGame;

DWORD cullingGame;
DWORD LightingGame;
class RestoreStateGame
{
public:
	DWORD	m_dwVS;
	RestoreStateGame(D3DFILLMODE d3dFillMode, D3DCOLOR colour)
	{
		//BACKUP
		Device::pDevice->GetVertex(&m_dwVS);
		Device::pDevice->GetRenderState(D3DRS_CULLMODE, &cullingGame);
		Device::pDevice->GetRenderState(D3DRS_TEXTUREFACTOR, &textureFactorGame);
		Device::pDevice->GetRenderState(D3DRS_FILLMODE, &FillOldGame);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &colorArg1Game);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLORARG2, &colorArg2Game);
		Device::pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &colorOpGame);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &alphaArg1Game);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &alphaArg2Game);
		Device::pDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &alphaOpGame);
		Device::pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &alpaBlendGame);
		Device::pDevice->GetRenderState(D3DRS_SRCBLEND, &srcBlendGame);
		Device::pDevice->GetRenderState(D3DRS_DESTBLEND, &destBlendGame);
		Device::pDevice->GetTransform(D3DTS_WORLD, &stateoldGame);

		//SET VALUES
		Device::pDevice->SetTexture(0, NULL);
		Device::pDevice->SetTexture(1, NULL);
		Device::pDevice->SetPixelShader(NULL);

		Device::pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		Device::pDevice->SetRenderState(D3DRS_FILLMODE, d3dFillMode);
		Device::pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, colour);

		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


		Device::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		Device::pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Device::pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Device::pDevice->SetTransform(D3DTS_WORLD, &CRender::WorldStateCopy);
	}

	virtual ~RestoreStateGame()
	{
		//RESTORE
		Device::pDevice->SetVertex(m_dwVS);
		Device::pDevice->SetRenderState(D3DRS_CULLMODE, cullingGame);
		Device::pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, textureFactorGame);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, colorArg1Game);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, colorArg2Game);
		Device::pDevice->SetTextureStageState(0, D3DTSS_COLOROP, colorOpGame);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, alphaArg1Game);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, alphaArg2Game);
		Device::pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, alphaOpGame);
		Device::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, alpaBlendGame);
		Device::pDevice->SetRenderState(D3DRS_SRCBLEND, srcBlendGame);
		Device::pDevice->SetRenderState(D3DRS_DESTBLEND, destBlendGame);
		Device::pDevice->SetTransform(D3DTS_WORLD, &stateoldGame);
		Device::pDevice->SetRenderState(D3DRS_FILLMODE, FillOldGame);
	}
};


void CRender::RenderSphere(LPD3DXMESH lpMesh, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode, D3DCOLOR colour) {
	D3DXMATRIX matTranslation;
	D3DXMATRIX matScaling;

	D3DXMatrixTranslation(&matTranslation, fx, fy, fz);
	D3DXMatrixScaling(&matScaling, fRadius, fRadius, fRadius);

	D3DXMATRIX matWorld;
	matWorld = matScaling * matTranslation;

	RestoreStateWithWorld SetRenderingOption(d3dFillMode, matWorld, colour);
	IndexBuffer lpIndexBuffer;
	VertexBuffer lpVertexBuffer;
	lpMesh->GetIndexBuffer(&lpIndexBuffer);
	lpMesh->GetVertexBuffer(&lpVertexBuffer);
#ifdef DX9
	Device::pDevice->SetVertex(lpMesh->GetFVF());
	Device::pDevice->SetIndices(lpIndexBuffer);
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, 0, 24);
	Device::pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, lpMesh->GetNumVertices(), 0, lpMesh->GetNumFaces());
#else
	Device::pDevice->SetVertexShader(lpMesh->GetFVF());
	Device::pDevice->SetIndices(lpIndexBuffer, 0);
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, 24);
	Device::pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, lpMesh->GetNumVertices(), 0, lpMesh->GetNumFaces());
#endif
}


void CRender::RenderBox(LPD3DXMESH ms_lpSphereMesh, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode, D3DCOLOR colour) {
	D3DXMATRIX matTranslation;
	D3DXMATRIX matScaling;
	D3DXMatrixTranslation(&matTranslation, fx, fy, fz);
	D3DXMatrixScaling(&matScaling, fRadius, fRadius, fRadius);
	D3DXMATRIX matWorld;
	matWorld = matScaling * matTranslation;
	RestoreStateWithWorld SetRenderingOption(d3dFillMode, matWorld, colour);
	IndexBuffer lpIndexBuffer;
	VertexBuffer lpVertexBuffer;
	ms_lpSphereMesh->GetIndexBuffer(&lpIndexBuffer);
	ms_lpSphereMesh->GetVertexBuffer(&lpVertexBuffer);
	ms_lpSphereMesh->DrawSubset(0);
#ifdef DX9
	Device::pDevice->SetVertex(ms_lpSphereMesh->GetFVF());
	Device::pDevice->SetIndices(lpIndexBuffer);
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, 0, 24);
	Device::pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, ms_lpSphereMesh->GetNumVertices(), 0, ms_lpSphereMesh->GetNumFaces());
#else
	Device::pDevice->SetVertexShader(ms_lpSphereMesh->GetFVF());
	Device::pDevice->SetIndices(lpIndexBuffer, 0);
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, 24);
	Device::pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, ms_lpSphereMesh->GetNumVertices(), 0, ms_lpSphereMesh->GetNumFaces());
#endif
}

template<typename T>
inline T Clamp(float v, T mn, T mx)
{
	return (v < mn) ? mn : (v > mx) ? mx : v;
}

void CRender::Line3D(int x, int y, int z, int ex, int ey, int ez, ImVec4 colorvec)
{
	float f[4] = { colorvec.x, colorvec.y, colorvec.z, colorvec.w };
	int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };
	D3DCOLOR color = D3DCOLOR_RGBA(Clamp(i[0], 0, 255), Clamp(i[1], 0, 255), Clamp(i[2], 0, 255), Clamp(i[3], 0, 255));
	SPDTVertexRaw pVertex[2] =
	{
		{ x, y, z, color, 0.0f, 0.0f },
		{ ex, ey, ez, color, 0.0f, 0.0f }
	};

	int count = 2;
	VertexBuffer lpVertexBuffer;
#ifdef DX9
	Device::pDevice->CreateVertexBuffer(sizeof(TPDTVertex) * 16, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1, D3DPOOL_SYSTEMMEM, &lpVertexBuffer, NULL);
#else
	Device::pDevice->CreateVertexBuffer(sizeof(TPDTVertex) * 16, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1, D3DPOOL_SYSTEMMEM, &lpVertexBuffer);
#endif
	SD3DVertex* pVoid;
#ifdef DX9
	lpVertexBuffer->Lock(0, sizeof(TPDTVertex) * count, (void**)&pVoid, D3DLOCK_DISCARD);
#else
	lpVertexBuffer->Lock(0, sizeof(TPDTVertex) * count, (BYTE**)&pVoid, D3DLOCK_DISCARD);
#endif
	memcpy(pVoid, pVertex, sizeof(TPDTVertex) * count);
	lpVertexBuffer->Unlock();

	RestoreStateGame SetRenderingOption(D3DFILL_SOLID, color);

	Device::pDevice->SetVertex(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
#ifdef DX9
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, 0, sizeof(TPDTVertex));
#else
	Device::pDevice->SetStreamSource(0, lpVertexBuffer, sizeof(TPDTVertex));
#endif
	Device::pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);


	lpVertexBuffer->Release();
	lpVertexBuffer = NULL;
}

void CRender::Circle3D(int fx, int fy, int radius, int points, ImVec4 colour) {
	int count;
	float theta, delta;
	std::vector<D3DXVECTOR3> pts;
	pts.clear();
	pts.resize(points);
	theta = 0.0;
	delta = 2 * D3DX_PI / float(points);
	for (count = 0; count < points; count++)
	{
		pts[count] = D3DXVECTOR3(radius * cosf(theta), radius * sinf(theta), 0.0f);
		theta += delta;
	}
	for (count = 0; count < points - 1; count++)
	{
		float fx1 = fx + pts[count].x;
		float fx2 = fx + pts[count + 1].x;
		float fy1 = fy + pts[count].y;
		float fy2 = fy + pts[count + 1].y;
		float fz1 = GameFunctions::GetBackgroundHeight(fx1, fy1) + 10.0f;
		float fz2 = GameFunctions::GetBackgroundHeight(fx2, fy2) + 10.0f;
		Line3D(fx1, -fy1, fz1, fx2, -fy2, fz2, colour);
	}
	float fx1 = fx + pts[points - 1].x;
	float fx2 = fx + pts[0].x;
	float fy1 = fy + pts[points - 1].y;
	float fy2 = fy + pts[0].y;
	float fz1 = GameFunctions::GetBackgroundHeight(fx1, fy1) + 10.0f;
	float fz2 = GameFunctions::GetBackgroundHeight(fx2, fy2) + 10.0f;
	Line3D(fx1, -fy1, fz1, fx2, -fy2, fz2, colour);
}

void CRender::Circle(int x, int y, int z, int radius, int points, D3DCOLOR colour) {
	SD3DVertex* pVertex = new SD3DVertex[points + 1];
	for (int i = 0; i <= points; i++) {
		pVertex[i] = { x + radius * cos(D3DX_PI * (i / (points / 2.0f))), y - radius * sin(D3DX_PI * (i / (points / 2.0f))), 0.0f, 1.0f, colour };
	}
	Device::pDevice->SetVertex(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	Device::pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, points, pVertex, sizeof(SD3DVertex));
	delete[] pVertex;
}

void CRender::Box3D(int sx, int sy, int sz, int ex, int ey, int ez, D3DCOLOR ms_diffuseColor) {
	SD3DVertex* pVertex = new SD3DVertex[8];
	pVertex[0] = { (float)sx, (float)sy,(float)sz, 1.0f, ms_diffuseColor };
	pVertex[1] = { (float)ex, (float)sy, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[2] = { (float)sx, (float)sy, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[3] = { (float)sx, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[4] = { (float)ex, (float)sy, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[5] = { (float)ex, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[6] = { (float)sx, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[7] = { (float)ex + 1.0f, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	for (int i = 0; i <= 8; i++) {
		Device::pDevice->SetTexture(0, NULL);
		Device::pDevice->SetTexture(1, NULL);
		Device::pDevice->SetVertex(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		Device::pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 12, pVertex, sizeof(SD3DVertex));
	}
	delete[] pVertex;
}

const WORD c_FillRectIndices[20] = { 2, 2, 1, 2, 2, 1,2, 2, 1,2, 2, 1,2, 2, 1,2, 2, 1, 2,2 };
void CRender::Cube3D(int sx, int sy, int sz, int ex, int ey, int ez, D3DCOLOR ms_diffuseColor) {
	SD3DVertex* pVertex = new SD3DVertex[8];
	pVertex[0] = { (float)sx, (float)sy,(float)sz, 1.0f, ms_diffuseColor };
	pVertex[1] = { (float)ex, (float)sy, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[2] = { (float)sx, (float)ey, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[3] = { (float)ex, (float)ey, (float)sz, 1.0f, ms_diffuseColor };
	pVertex[4] = { (float)sx, (float)sy, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[5] = { (float)ex, (float)sy, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[6] = { (float)sx, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	pVertex[7] = { (float)ex, (float)ey, (float)ez, 1.0f, ms_diffuseColor };
	for (int i = 0; i <= 8; i++) {
		Device::pDevice->SetTexture(0, NULL);
		Device::pDevice->SetTexture(1, NULL);
		Device::pDevice->SetVertex(D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);
		Device::pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 20, pVertex, sizeof(SD3DVertex));
		//Device::pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 8, 12, c_FillRectIndices, D3DFMT_INDEX16, pVertex, sizeof(SD3DVertex));
	}
	delete[] pVertex;
}

void CRender::FilledCircle3D(int x, int y, int z, int radius, int points, D3DCOLOR colour) {
	int count;
	float theta, delta;
	std::vector<D3DXVECTOR3> pts;
	pts.clear();
	pts.resize(points);
	theta = 0.0;
	delta = 2 * D3DX_PI / float(points);
	for (count = 0; count < points; count++)
	{
		pts[count] = D3DXVECTOR3(radius * cosf(theta), radius * sinf(theta), 0.0f);
		theta += delta;
	}
	SD3DVertex* pVertex = new SD3DVertex[points];
	for (int i = 0; i < points; i++) {
		pVertex[i] = { 
			x + pts[i].x,
			y + pts[i].y,
			z + pts[i].z,
			1.0f, colour 
		};
	}
	Device::pDevice->SetTexture(0, NULL);
	Device::pDevice->SetTexture(1, NULL);
	Device::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device::pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device::pDevice->SetVertex(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	Device::pDevice->DrawPrimitiveUP(D3DPT_LINELIST, points, pVertex, sizeof(SD3DVertex));
	delete[] pVertex;
}

int CRender::FrameRate() {
	static int iFps, iLastFps;
	static float flLastTickCount, flTickCount;
	flTickCount = clock() * 0.001f;
	iFps++;
	if ((flTickCount - flLastTickCount) >= 1.0f) {
		flLastTickCount = flTickCount;
		iLastFps = iFps;
		iFps = 0;
	}
	return iLastFps;
}