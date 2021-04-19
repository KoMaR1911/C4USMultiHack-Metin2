#pragma once
class CRender {
public:
	CRender();
	~CRender();

	static D3DMATRIX WorldStateCopy;
	static void String(int x, int y, D3DCOLOR colour, ID3DXFont* font, bool outlined, char* string, ...);
	static int StringWidth(ID3DXFont* font, char* string);
	static void Line(int x, int y, int x2, int y2, D3DCOLOR colour);
	static void FilledBox(int x, int y, int width, int height, D3DCOLOR colour);
	static void FilledBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor);
	static void BorderedBox(int x, int y, int width, int height, int thickness, D3DCOLOR colour);
	static void BorderedBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR outlinecolor);
	static void GradientBox(int x, int y, int width, int height, D3DCOLOR colour, D3DCOLOR color2, bool vertical);
	static void GradientBoxOutlined(int x, int y, int width, int height, int thickness, D3DCOLOR colour, D3DCOLOR color2, D3DCOLOR outlinecolor, bool vertical);
	static void Circle(int x, int y, int z, int radius, int points, D3DCOLOR colour);
	static void Line3D(int x, int y, int z, int ex, int ey, int ez, ImVec4 colour);
	static void Circle3D(int x, int y, int radius, int points, ImVec4 colour);
	static void Box3D(int x, int y, int z, int ex, int ey, int ez, D3DCOLOR colour);
	static void Cube3D(int x, int y, int z, int ex, int ey, int ez, D3DCOLOR colour);
	static void FilledCircle(int x, int y, int radius, int points, D3DCOLOR colour);
	static void FilledCircle3D(int x, int y, int z, int radius, int points, D3DCOLOR colour);
	static void RenderBox(LPD3DXMESH ms_lpSphereMesh, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode, D3DCOLOR colour);
	static void RenderSphere(LPD3DXMESH ms_lpSphereMesh, float fx, float fy, float fz, float fRadius, D3DFILLMODE d3dFillMode, D3DCOLOR colour);
	static int FrameRate();
};
