// Fixed implementation for ImGui DirectX8 by KoMaR1911 - FIXED VERSION
// thanks for seremo 
// Bye bye to C4US Project forever ;(

#include "imgui.h"
#include "imgui_impl_dx8.h"
#include <d3d8.h>

// DirectX data
static LPDIRECT3DDEVICE8        g_pd3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER8  g_pVB = NULL;
static LPDIRECT3DINDEXBUFFER8   g_pIB = NULL;
static LPDIRECT3DTEXTURE8       g_FontTexture = NULL;
static IDirect3DSurface8* g_pDepthStencilBuffer = NULL;
static int                      g_VertexBufferSize = 5000;
static int                      g_IndexBufferSize = 10000;

struct CUSTOMVERTEX
{
    float    pos[3];
    D3DCOLOR col;
    float    uv[2];
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

static void ImGui_ImplDX8_SetupRenderState(ImDrawData* draw_data)
{
    D3DVIEWPORT8 vp;
    vp.X = vp.Y = 0;
    vp.Width = (DWORD)draw_data->DisplaySize.x;
    vp.Height = (DWORD)draw_data->DisplaySize.y;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    g_pd3dDevice->SetViewport(&vp);

    g_pd3dDevice->SetPixelShader(NULL);
    g_pd3dDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX);
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
    g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0F);

    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

    {
        float L = draw_data->DisplayPos.x + 0.5f;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x + 0.5f;
        float T = draw_data->DisplayPos.y + 0.5f;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y + 0.5f;
        D3DMATRIX mat_identity = { { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } } };
        D3DMATRIX mat_projection =
        { { {
            2.0f / (R - L),   0.0f,         0.0f,  0.0f,
            0.0f,         2.0f / (T - B),   0.0f,  0.0f,
            0.0f,         0.0f,         0.5f,  0.0f,
            (L + R) / (L - R),  (T + B) / (B - T),  0.5f,  1.0f
        } } };
        g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_identity);
        g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_identity);
        g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_projection);
    }
}

void ImGui_ImplDX8_RenderDrawData(ImDrawData* draw_data)
{
    if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
        return;

    if (FAILED(g_pd3dDevice->TestCooperativeLevel()))
        return;

    if (!g_pVB || g_VertexBufferSize < draw_data->TotalVtxCount)
    {
        if (g_pVB) { g_pVB->Release(); g_pVB = NULL; }
        g_VertexBufferSize = draw_data->TotalVtxCount + 5000;
        if (FAILED(g_pd3dDevice->CreateVertexBuffer(g_VertexBufferSize * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB)))
            return;
    }
    if (!g_pIB || g_IndexBufferSize < draw_data->TotalIdxCount)
    {
        if (g_pIB) { g_pIB->Release(); g_pIB = NULL; }
        g_IndexBufferSize = draw_data->TotalIdxCount + 10000;
        if (FAILED(g_pd3dDevice->CreateIndexBuffer(g_IndexBufferSize * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_pIB)))
            return;
    }

    DWORD stateBlockToken = 0;
    if (FAILED(g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &stateBlockToken)))
        return;

    IDirect3DSurface8* pOldRenderTarget = NULL;
    IDirect3DSurface8* pOldDepthStencil = NULL;
    g_pd3dDevice->GetRenderTarget(&pOldRenderTarget);
    g_pd3dDevice->GetDepthStencilSurface(&pOldDepthStencil);

    if (g_pDepthStencilBuffer)
        g_pd3dDevice->SetRenderTarget(pOldRenderTarget, g_pDepthStencilBuffer);

    CUSTOMVERTEX* vtx_dst;
    ImDrawIdx* idx_dst;
    if (FAILED(g_pVB->Lock(0, (UINT)draw_data->TotalVtxCount * sizeof(CUSTOMVERTEX), (BYTE**)&vtx_dst, D3DLOCK_DISCARD)))
        goto cleanup;
    if (FAILED(g_pIB->Lock(0, (UINT)draw_data->TotalIdxCount * sizeof(ImDrawIdx), (BYTE**)&idx_dst, D3DLOCK_DISCARD)))
    {
        g_pVB->Unlock();
        goto cleanup;
    }
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;
        for (int i = 0; i < cmd_list->VtxBuffer.Size; i++)
        {
            vtx_dst->pos[0] = vtx_src->pos.x; vtx_dst->pos[1] = vtx_src->pos.y; vtx_dst->pos[2] = 0.0f;
            vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);
            vtx_dst->uv[0] = vtx_src->uv.x; vtx_dst->uv[1] = vtx_src->uv.y;
            vtx_dst++; vtx_src++;
        }
        memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        idx_dst += cmd_list->IdxBuffer.Size;
    }
    g_pVB->Unlock();
    g_pIB->Unlock();

    ImGui_ImplDX8_SetupRenderState(draw_data);

    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

    int global_vtx_offset = 0;
    int global_idx_offset = 0;
    ImVec2 clip_off = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplDX8_SetupRenderState(draw_data);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                const RECT r = { (LONG)(pcmd->ClipRect.x - clip_off.x), (LONG)(pcmd->ClipRect.y - clip_off.y), (LONG)(pcmd->ClipRect.z - clip_off.x), (LONG)(pcmd->ClipRect.w - clip_off.y) };

                g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
                g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
                g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
                g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
                g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 1);

                CUSTOMVERTEX clip_verts[4];
                clip_verts[0] = { { (float)r.left,  (float)r.bottom, 0.0f }, 0xFFFFFFFF, { 0, 0 } };
                clip_verts[1] = { { (float)r.left,  (float)r.top,    0.0f }, 0xFFFFFFFF, { 0, 0 } };
                clip_verts[2] = { { (float)r.right, (float)r.bottom, 0.0f }, 0xFFFFFFFF, { 0, 0 } };
                clip_verts[3] = { { (float)r.right, (float)r.top,    0.0f }, 0xFFFFFFFF, { 0, 0 } };
                g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, clip_verts, sizeof(CUSTOMVERTEX));

                g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0F);
                g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
                g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

                g_pd3dDevice->SetStreamSource(0, g_pVB, sizeof(CUSTOMVERTEX));
                g_pd3dDevice->SetIndices(g_pIB, global_vtx_offset + pcmd->VtxOffset);
                g_pd3dDevice->SetTexture(0, (LPDIRECT3DTEXTURE8)pcmd->TextureId);

                g_pd3dDevice->DrawIndexedPrimitive(
                    D3DPT_TRIANGLELIST,
                    0,                                     
                    (UINT)draw_data->TotalVtxCount,        
                    global_idx_offset + pcmd->IdxOffset,   
                    pcmd->ElemCount / 3                    
                );

                g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
            }
        }
        global_idx_offset += cmd_list->IdxBuffer.Size;
        global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

cleanup:
    if (pOldRenderTarget) { g_pd3dDevice->SetRenderTarget(pOldRenderTarget, pOldDepthStencil); pOldRenderTarget->Release(); }
    if (pOldDepthStencil) { pOldDepthStencil->Release(); }
    if (stateBlockToken) { g_pd3dDevice->ApplyStateBlock(stateBlockToken); g_pd3dDevice->DeleteStateBlock(stateBlockToken); }
}

bool ImGui_ImplDX8_Init(IDirect3DDevice8* device)
{
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "imgui_impl_dx8";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    g_pd3dDevice = device;
    g_pd3dDevice->AddRef();
    return true;
}

void ImGui_ImplDX8_Shutdown()
{
    ImGui_ImplDX8_InvalidateDeviceObjects();
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

static bool ImGui_ImplDX8_CreateFontsTexture()
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    if (FAILED(g_pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_FontTexture)))
        return false;

    D3DLOCKED_RECT tex_locked_rect;
    if (FAILED(g_FontTexture->LockRect(0, &tex_locked_rect, NULL, 0)))
        return false;

    for (int y = 0; y < height; y++)
        memcpy((unsigned char*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width * 4) * y, (width * 4));
    g_FontTexture->UnlockRect(0);

    io.Fonts->TexID = (ImTextureID)g_FontTexture;
    return true;
}

static bool ImGui_ImplDX8_CreateDepthStencilBuffer()
{
    if (!g_pd3dDevice) return false;
    if (g_pDepthStencilBuffer) return true;

    IDirect3DSurface8* pBackBuffer = NULL;
    if (FAILED(g_pd3dDevice->GetRenderTarget(&pBackBuffer))) return false;

    D3DSURFACE_DESC desc;
    HRESULT hr = pBackBuffer->GetDesc(&desc);
    pBackBuffer->Release();
    if (FAILED(hr)) return false;

    if (FAILED(g_pd3dDevice->CreateDepthStencilSurface(desc.Width, desc.Height, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, &g_pDepthStencilBuffer)))
        return false;

    return true;
}

bool ImGui_ImplDX8_CreateDeviceObjects()
{
    if (!g_pd3dDevice)
        return false;
    if (FAILED(g_pd3dDevice->TestCooperativeLevel()))
        return false;
    if (!ImGui_ImplDX8_CreateFontsTexture())
        return false;
    if (!ImGui_ImplDX8_CreateDepthStencilBuffer())
        return false;
    return true;
}

void ImGui_ImplDX8_InvalidateDeviceObjects()
{
    if (!g_pd3dDevice) return;
    if (g_pVB) { g_pVB->Release(); g_pVB = NULL; }
    if (g_pIB) { g_pIB->Release(); g_pIB = NULL; }
    if (g_pDepthStencilBuffer) { g_pDepthStencilBuffer->Release(); g_pDepthStencilBuffer = NULL; }
    if (g_FontTexture)
    {
        g_FontTexture->Release();
        g_FontTexture = NULL;
        ImGui::GetIO().Fonts->TexID = NULL;
    }
}

void ImGui_ImplDX8_NewFrame()
{
    if (!g_FontTexture)
        ImGui_ImplDX8_CreateDeviceObjects();
}
