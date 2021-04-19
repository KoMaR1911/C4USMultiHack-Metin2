#pragma once
//#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
//#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui/imgui_internal.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#ifdef DX9
#define DirectDevice IDirect3DDevice9*
#define DirectDevice2 LPDIRECT3DDEVICE9
#define DirectTexture LPDIRECT3DTEXTURE9
#include "ImGui/imgui_impl_dx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#else
#define DirectDevice IDirect3DDevice8*
#define DirectDevice2 LPDIRECT3DDEVICE8
#define DirectTexture LPDIRECT3DTEXTURE8
#include "ImGui/imgui_impl_dx8.h"
#include <d3d8.h>
#include <d3dx8.h>
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#endif
#include <map>

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size()))
		{
			return false;
		}
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Hotkey(DWORD& hotKeyTime, const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
	void Logo(ImTextureID texture, const ImVec2& size);
	bool IconMenuButton(const char* tooltip, ImTextureID texture, const ImVec2& size, bool Open);
	bool IconButton(bool* state, const char* tooltip, ImTextureID textureOn, ImTextureID textureOff, const ImVec2& size);
	bool IconButton2(bool* state, const char* tooltip, ImTextureID texture, ImTextureID textureOn, ImTextureID textureOff, const ImVec2& size);
	bool InputFloatMinMax(const char* label, float* v, float Min, float Max, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool PopupButton(const char* tooltip, ImTextureID texture, const ImVec2& size);
	bool Selectable2(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));  // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
	void DrawImagePos(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& pos, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	void DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	void ImageAuto(DirectTexture user_texture_id, float scale_width = 1.0f, float scale_height = 1.0f, bool center = false,  const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	void ImageSwitcher(DirectTexture user_texture_id, const ImVec4& border_col);
	bool ItemImage(std::string id, ImTextureID user_texture_id, int count, const ImVec2& size, bool selected = false, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
	void CenterVertical(ImVec2 size);
	void CenterHorizontal(ImVec2 size);

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool Combo(const char* label, int* currIndex, std::map<int, std::string>& values);
	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);
};