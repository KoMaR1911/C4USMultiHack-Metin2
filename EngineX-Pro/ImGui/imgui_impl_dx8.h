// dear imgui: Renderer for DirectX9
// This needs to be used along with a Platform Binding (e.g. Win32)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'LPDIRECT3DTEXTURE9' as ImTextureID. Read the FAQ about ImTextureID!
//  [X] Renderer: Support for large meshes (64k+ vertices) with 16-bit indices.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#pragma once

//struct IDirect3DDevice9;
struct IDirect3DDevice8;
IMGUI_IMPL_API bool     ImGui_ImplDX8_Init(IDirect3DDevice8* device);
IMGUI_IMPL_API void     ImGui_ImplDX8_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplDX8_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplDX8_RenderDrawData(ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_IMPL_API bool     ImGui_ImplDX8_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_ImplDX8_InvalidateDeviceObjects();
