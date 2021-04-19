// dear imgui: Renderer for DirectX9
// This needs to be used along with a Platform Binding (e.g. Win32)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'LPDIRECT3DTEXTURE9' as ImTextureID. Read the FAQ about ImTextureID!
//  [X] Renderer: Support for large meshes (64k+ vertices) with 16-bit indices.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// CHANGELOG
// (minor and older changes stripped away, please see git history for details)
//  2019-05-29: DirectX9: Added support for large mesh (64K+ vertices), enable ImGuiBackendFlags_RendererHasVtxOffset flag.
//  2019-04-30: DirectX9: Added support for special ImDrawCallback_ResetRenderState callback to reset render state.
//  2019-03-29: Misc: Fixed erroneous assert in ImGui_ImplDX8_InvalidateDeviceObjects().
//  2019-01-16: Misc: Disabled fog before drawing UI's. Fixes issue #2288.
//  2018-11-30: Misc: Setting up io.BackendRendererName so it can be displayed in the About Window.
//  2018-06-08: Misc: Extracted imgui_impl_DX8.cpp/.h away from the old combined DX8+Win32 example.
//  2018-06-08: DirectX9: Use draw_data->DisplayPos and draw_data->DisplaySize to setup projection matrix and clipping rectangle.
//  2018-05-07: Render: Saving/restoring Transform because they don't seem to be included in the StateBlock. Setting shading mode to Gouraud.
//  2018-02-16: Misc: Obsoleted the io.RenderDrawListsFn callback and exposed ImGui_ImplDX8_RenderDrawData() in the .h file so you can call it yourself.
//  2018-02-06: Misc: Removed call to ImGui::Shutdown() which is not available from 1.60 WIP, user needs to call CreateContext/DestroyContext themselves.

#include "imgui.h"
#include "imgui_impl_dx8.h"

// DirectX
#include <d3d8.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// DirectX data
static LPDIRECT3DDEVICE8        g_pd3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER8  g_pVB = NULL;
static LPDIRECT3DINDEXBUFFER8   g_pIB = NULL;
static LPDIRECT3DVERTEXBUFFER8  g_maskVB = NULL;
static LPDIRECT3DINDEXBUFFER8   g_maskIB = NULL;
static LPDIRECT3DTEXTURE8       g_FontTexture = NULL;
static int                      g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;
static IDirect3DSurface8*       g_DepthBuffer = nullptr;
IDirect3DSurface8* realDepthStencilBuffer;

struct CUSTOMVERTEX
{
    float    pos[3];
    D3DCOLOR col;
    float    uv[2];
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

static void ImGui_ImplDX8_SetupRenderState(ImDrawData* draw_data)
{
    // Setup viewport
    D3DVIEWPORT8 vp;
    vp.X = vp.Y = 0;
    vp.Width = (DWORD)draw_data->DisplaySize.x;
    vp.Height = (DWORD)draw_data->DisplaySize.y;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    g_pd3dDevice->SetViewport(&vp);

    // Setup render state: fixed-pipeline, alpha-blending, no face culling, no depth testing, shade mode (for gradient)
	g_pd3dDevice->GetDepthStencilSurface(&realDepthStencilBuffer);
	g_pd3dDevice->SetRenderTarget(nullptr, g_DepthBuffer);
    g_pd3dDevice->SetPixelShader(NULL);
	g_pd3dDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX);
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
    g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    //g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
    g_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);//new
    g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, false);//new
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
    //g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    //g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // Setup orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    // Being agnostic of whether <d3DX8.h> or <DirectXMath.h> can be used, we aren't relying on D3DXMatrixIdentity()/D3DXMatrixOrthoOffCenterLH() or DirectX::XMMatrixIdentity()/DirectX::XMMatrixOrthographicOffCenterLH()
    {
        float L = draw_data->DisplayPos.x + 0.5f;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x + 0.5f;
        float T = draw_data->DisplayPos.y + 0.5f;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y + 0.5f;\
        D3DMATRIX mat_identity = { { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } } };
        D3DMATRIX mat_projection =
        { { {
            2.0f/(R-L),   0.0f,         0.0f,  0.0f,
            0.0f,         2.0f/(T-B),   0.0f,  0.0f,
            0.0f,         0.0f,         0.5f,  0.0f,
            (L+R)/(L-R),  (T+B)/(B-T),  0.5f,  1.0f
        } } };
        g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_identity);
        g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_identity);
        g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_projection);
    }
}

static void build_mask_vbuffer(const RECT* rect) {
    CUSTOMVERTEX* vtx_dst;
    g_maskVB->Lock(0, (UINT)(6 * sizeof(CUSTOMVERTEX)), (BYTE**)&vtx_dst, 0);
    vtx_dst[0].pos[0] = (float)rect->left;
    vtx_dst[0].pos[1] = (float)rect->bottom;
    vtx_dst[0].pos[2] = 0;
    vtx_dst[1].pos[0] = (float)rect->left;
    vtx_dst[1].pos[1] = (float)rect->top;
    vtx_dst[1].pos[2] = 0;
    vtx_dst[2].pos[0] = (float)rect->right;
    vtx_dst[2].pos[1] = (float)rect->top;
    vtx_dst[2].pos[2] = 0;
    vtx_dst[3].pos[0] = (float)rect->left;
    vtx_dst[3].pos[1] = (float)rect->bottom;
    vtx_dst[3].pos[2] = 0;
    vtx_dst[4].pos[0] = (float)rect->right;
    vtx_dst[4].pos[1] = (float)rect->top;
    vtx_dst[4].pos[2] = 0;
    vtx_dst[5].pos[0] = (float)rect->right;
    vtx_dst[5].pos[1] = (float)rect->bottom;
    vtx_dst[5].pos[2] = 0;
    vtx_dst[0].col = 0xFFFFFFFF;
    vtx_dst[1].col = 0xFFFFFFFF;
    vtx_dst[2].col = 0xFFFFFFFF;
    vtx_dst[3].col = 0xFFFFFFFF;
    vtx_dst[4].col = 0xFFFFFFFF;
    vtx_dst[5].col = 0xFFFFFFFF;
    vtx_dst[0].uv[0] = 0;
    vtx_dst[0].uv[1] = 0;
    vtx_dst[1].uv[0] = 0;
    vtx_dst[1].uv[1] = 0;
    vtx_dst[2].uv[0] = 0;
    vtx_dst[2].uv[1] = 0;
    vtx_dst[3].uv[0] = 0;
    vtx_dst[3].uv[1] = 0;
    vtx_dst[4].uv[0] = 0;
    vtx_dst[4].uv[1] = 0;
    vtx_dst[5].uv[0] = 0;
    vtx_dst[5].uv[1] = 0;
    g_maskVB->Unlock();
}

// Render function.
// (this used to be set in io.RenderDrawListsFn and called by ImGui::Render(), but you can now call this directly from your main loop)
void ImGui_ImplDX8_RenderDrawData(ImDrawData* draw_data)
{
    try
    {
        // Avoid rendering when minimized
        if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
            return;

        // Create and grow buffers if needed
        if (!g_pVB || g_VertexBufferSize < draw_data->TotalVtxCount)
        {
            if (g_pVB) { g_pVB->Release(); g_pVB = NULL; }
            g_VertexBufferSize = draw_data->TotalVtxCount + 5000;
            if (g_pd3dDevice->CreateVertexBuffer(g_VertexBufferSize * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB) < 0)
                return;
        }
        if (!g_pIB || g_IndexBufferSize < draw_data->TotalIdxCount)
        {
            if (g_pIB) { g_pIB->Release(); g_pIB = NULL; }
            g_IndexBufferSize = draw_data->TotalIdxCount + 10000;
            if (g_pd3dDevice->CreateIndexBuffer(g_IndexBufferSize * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_pIB) < 0)
                return;
        }
        if (!g_maskVB && !g_maskIB) {
            if (g_pd3dDevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_maskVB) < 0) return;
            if (g_pd3dDevice->CreateIndexBuffer(6, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_maskIB) < 0) return;
            ImDrawIdx* idx_dst;
            g_maskIB->Lock(0, 6 * sizeof(ImDrawIdx), (BYTE**)&idx_dst, D3DLOCK_DISCARD);
            idx_dst[0] = 0;
            idx_dst[1] = 1;
            idx_dst[2] = 2;
            idx_dst[3] = 0;
            idx_dst[4] = 2;
            idx_dst[5] = 3;
            g_maskIB->Unlock();
        }
        // Backup the DX8 state
        DWORD stateBlockToken = 0;
        if (g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &stateBlockToken) < 0) return;
        /* IDirect3DStateBlock9* d3d9_state_block = NULL;
         if (g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &d3d9_state_block) < 0)
             return;*/

        // Backup the DX8 transform (DX8 documentation suggests that it is included in the StateBlock but it doesn't appear to)
        D3DMATRIX last_world, last_view, last_projection;//new
        g_pd3dDevice->GetTransform(D3DTS_WORLD, &last_world);//new
        g_pd3dDevice->GetTransform(D3DTS_VIEW, &last_view);//new
        g_pd3dDevice->GetTransform(D3DTS_PROJECTION, &last_projection);//new

        // Copy and convert all vertices into a single contiguous buffer, convert colors to DX8 default format.
        // FIXME-OPT: This is a waste of resource, the ideal is to use imconfig.h and
        //  1) to avoid repacking colors:   #define IMGUI_USE_BGRA_PACKED_COLOR
        //  2) to avoid repacking vertices: #define IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT struct ImDrawVert { ImVec2 pos; float z; ImU32 col; ImVec2 uv; }
        CUSTOMVERTEX* vtx_dst;
        ImDrawIdx* idx_dst;
        if (g_pVB->Lock(0, (UINT)(draw_data->TotalVtxCount * sizeof(CUSTOMVERTEX)), (BYTE**)&vtx_dst, D3DLOCK_DISCARD) < 0)
            return;
        if (g_pIB->Lock(0, (UINT)(draw_data->TotalIdxCount * sizeof(ImDrawIdx)), (BYTE**)&idx_dst, D3DLOCK_DISCARD) < 0)
            return;
        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];
            const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;
            for (int i = 0; i < cmd_list->VtxBuffer.Size; i++)
            {
                vtx_dst->pos[0] = vtx_src->pos.x;
                vtx_dst->pos[1] = vtx_src->pos.y;
                vtx_dst->pos[2] = 0.0f;
                vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);     // RGBA --> ARGB for DirectX9
                vtx_dst->uv[0] = vtx_src->uv.x;
                vtx_dst->uv[1] = vtx_src->uv.y;
                vtx_dst++;
                vtx_src++;
            }
            memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
            idx_dst += cmd_list->IdxBuffer.Size;
        }
        g_pVB->Unlock();
        g_pIB->Unlock();
        g_pd3dDevice->SetStreamSource(0, g_pVB, sizeof(CUSTOMVERTEX));
        g_pd3dDevice->SetIndices(g_pIB, 0);
        g_pd3dDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX);//new

        // Setup desired DX state
        ImGui_ImplDX8_SetupRenderState(draw_data);

        // Render command lists
        // (Because we merged all buffers into a single one, we maintain our own offset into them)
        int global_vtx_offset = 0;
        int global_idx_offset = 0;
        ImVec2 clip_off = draw_data->DisplayPos;
        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];
            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
            {
                const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback != NULL)
                {
                    // User callback, registered via ImDrawList::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                    if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                        ImGui_ImplDX8_SetupRenderState(draw_data);
                    else
                        pcmd->UserCallback(cmd_list, pcmd);
                }
                else
                {
                    const RECT r = { (LONG)(pcmd->ClipRect.x - clip_off.x), (LONG)(pcmd->ClipRect.y - clip_off.y), (LONG)(pcmd->ClipRect.z - clip_off.x), (LONG)(pcmd->ClipRect.w - clip_off.y) };
                    const LPDIRECT3DTEXTURE8 texture = (LPDIRECT3DTEXTURE8)pcmd->TextureId;
                    g_pd3dDevice->SetTexture(0, texture);
                    build_mask_vbuffer(&r);
                    g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
                    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFF);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xFF);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
                    g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0xFF);
                    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, 0);
                    g_pd3dDevice->SetStreamSource(0, g_maskVB, sizeof(CUSTOMVERTEX));
                    g_pd3dDevice->SetIndices(g_maskIB, 0);
                    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 4, 0, 2);//new			
                    g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
                    g_pd3dDevice->SetStreamSource(0, g_pVB, sizeof(CUSTOMVERTEX));
                    g_pd3dDevice->SetIndices(g_pIB, global_vtx_offset);
                    g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xF);
                    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xFF);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
                    g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0xFF);
                    //g_pd3dDevice->SetScissorRect(&r);
                    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, (UINT)cmd_list->VtxBuffer.Size, pcmd->IdxOffset + global_idx_offset, pcmd->ElemCount / 3);
                }
            }
            global_idx_offset += cmd_list->IdxBuffer.Size;
            global_vtx_offset += cmd_list->VtxBuffer.Size;
        }

        // Restore the DX8 transform
        g_pd3dDevice->SetTransform(D3DTS_WORLD, &last_world);//new
        g_pd3dDevice->SetTransform(D3DTS_VIEW, &last_view);//new
        g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &last_projection);//new

        // Restore the DX8 state
        // d3d9_state_block->Apply();
        // d3d9_state_block->Release();
        g_pd3dDevice->SetRenderTarget(nullptr, realDepthStencilBuffer);
        g_pd3dDevice->ApplyStateBlock(stateBlockToken);
        g_pd3dDevice->DeleteStateBlock(stateBlockToken);
    }
    catch (...)
    {

    }
}

bool ImGui_ImplDX8_Init(IDirect3DDevice8* device)
{
    // Setup back-end capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "cf0f1aa24cbb7951ebcf8dbda5f80855eba60fc7";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.

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
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height, BYTEs_per_pixel;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &BYTEs_per_pixel);

    // Upload texture to graphics system
    g_FontTexture = NULL;
    if (g_pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_FontTexture) < 0)
        return false;
    D3DLOCKED_RECT tex_locked_rect;
    if (g_FontTexture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
        return false;
    for (int y = 0; y < height; y++)
        memcpy((unsigned char *)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width * BYTEs_per_pixel) * y, (width * BYTEs_per_pixel));
    g_FontTexture->UnlockRect(0);

    // Store our identifier
    io.Fonts->TexID = (ImTextureID)g_FontTexture;

    return true;
}

static bool ImGui_ImplD3D8_CreateDepthStencilBuffer() {
	if (g_pd3dDevice == nullptr) {
		return false;
	}
	if (g_DepthBuffer == nullptr) {
		IDirect3DSurface8* realDepth;
		D3DSURFACE_DESC sfcDesc;

		g_pd3dDevice->GetDepthStencilSurface(&realDepth);
		if (realDepth->GetDesc(&sfcDesc)) {
			return false;
		}
		if (g_pd3dDevice->CreateDepthStencilSurface(sfcDesc.Width, sfcDesc.Height, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, &g_DepthBuffer)) {
			return false;
		}
	}

	return true;
}


bool ImGui_ImplDX8_CreateDeviceObjects()
{
    if (!g_pd3dDevice)
        return false;
    if (!ImGui_ImplDX8_CreateFontsTexture())
        return false;
	if (!ImGui_ImplD3D8_CreateDepthStencilBuffer()) {
		return false;
	}
    return true;
}

void ImGui_ImplDX8_InvalidateDeviceObjects()
{
	if (!g_pd3dDevice)
		return;
	if (g_pVB)
	{
		g_pVB->Release();
		g_pVB = NULL;
	}
	if (g_pIB)
	{
		g_pIB->Release();
		g_pIB = NULL;
	}
	if (g_maskVB) {
		g_maskVB->Release();
		g_maskVB = nullptr;
	}
	if (g_maskIB) {
		g_maskIB->Release();
		g_maskIB = nullptr;
	}
	if (g_DepthBuffer) {
		g_DepthBuffer->Release();
		g_DepthBuffer = nullptr;
	}
    if (g_FontTexture) { g_FontTexture->Release(); g_FontTexture = NULL; ImGui::GetIO().Fonts->TexID = NULL; }
    //if (LPDIRECT3DTEXTURE8 tex = (LPDIRECT3DTEXTURE8)ImGui::GetIO().Fonts->TexID)
    //{
    //    tex->Release();
    //    g_FontTexture = NULL;
    //    ImGui::GetIO().Fonts->TexID = 0;
    //}
}

void ImGui_ImplDX8_NewFrame()
{
	if(!g_FontTexture || !g_DepthBuffer)
        ImGui_ImplDX8_CreateDeviceObjects();
}
