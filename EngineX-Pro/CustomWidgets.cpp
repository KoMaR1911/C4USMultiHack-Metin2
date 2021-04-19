
#include "CustomWidgets.h"

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	//if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

bool ImGui::Combo(const char* label, int* currIndex, std::map<int, std::string>& map)
{
	if (map.empty())
	{
		return false;
	}
	std::vector<std::string> vector_values;
	for (auto value : map)
	{
		vector_values.push_back(string_format(value.second, 0));
	}
	return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&vector_values), vector_values.size());
}

bool ImGui::Combo(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty())
	{
		return false;
	}
	return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
}

bool ImGui::ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty())
	{
		return false;
	}
	return ImGui::ListBox(label, currIndex, ImGui::vector_getter, static_cast<void*>(&values), values.size());
}



const char* const KeyNames[] = {
	"Unknown",
	"LBUTTON",
	"RBUTTON",
	"CANCEL",
	"MBUTTON",
	"XBUTTON1",
	"XBUTTON2",
	"Unknown",
	"BACK",
	"TAB",
	"Unknown",
	"Unknown",
	"CLEAR",
	"RETURN",
	"Unknown",
	"Unknown",
	"SHIFT",
	"CONTROL",
	"MENU",
	"PAUSE",
	"CAPITAL",
	"KANA",
	"Unknown",
	"JUNJA",
	"FINAL",
	"KANJI",
	"Unknown",
	"ESCAPE",
	"CONVERT",
	"NONCONVERT",
	"ACCEPT",
	"MODECHANGE",
	"SPACE",
	"PRIOR",
	"NEXT",
	"END",
	"HOME",
	"LEFT",
	"UP",
	"RIGHT",
	"DOWN",
	"SELECT",
	"PRINT",
	"EXECUTE",
	"SNAPSHOT",
	"INSERT",
	"DELETE",
	"HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"LWIN",
	"RWIN",
	"APPS",
	"Unknown",
	"SLEEP",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9",
	"MULTIPLY",
	"ADD",
	"SEPARATOR",
	"SUBTRACT",
	"DECIMAL",
	"DIVIDE",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"NUMLOCK",
	"SCROLL",
	"OEM_NEC_EQUAL",
	"OEM_FJ_MASSHOU",
	"OEM_FJ_TOUROKU",
	"OEM_FJ_LOYA",
	"OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"LSHIFT",
	"RSHIFT",
	"LCONTROL",
	"RCONTROL",
	"LMENU",
	"RMENU",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown"
};



bool ImGui::Selectable2(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns) // FIXME-OPT: Avoid if vertically clipped.
		PushColumnsBackground();

	ImGuiID id = window->GetID(label);
	ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 size(size_arg.x != 0.0f ? size_arg.x : label_size.x, size_arg.y != 0.0f ? size_arg.y : label_size.y);
	ImVec2 pos = window->DC.CursorPos;
	pos.y += window->DC.CurrLineTextBaseOffset;
	ImRect bb_inner(pos, pos + size);
	ItemSize(size, 0.0f);

	// Fill horizontal space.
	const float min_x = (flags & ImGuiSelectableFlags_SpanAllColumns) != 0 ? window->ParentWorkRect.Min.x : pos.x;
	const float max_x = (flags & ImGuiSelectableFlags_SpanAllColumns) != 0 ? window->ParentWorkRect.Max.x : window->WorkRect.Max.x;
	if (size_arg.x == 0.0f || (flags & ImGuiSelectableFlags_SpanAvailWidth))
		size.x = ImMax(label_size.x, max_x - min_x);

	// Text stays at the submission position, but bounding box may be extended on both sides
	const ImVec2 text_min = pos;
	const ImVec2 text_max(min_x + size.x, pos.y + size.y);

	// Selectables are meant to be tightly packed together with no click-gap, so we extend their box to cover spacing between selectable.
	ImRect bb(min_x, pos.y, text_max.x, text_max.y);
	if ((flags & ImGuiSelectableFlags_NoPadWithHalfSpacing) == 0)
	{
		const float spacing_x = style.ItemSpacing.x;
		const float spacing_y = style.ItemSpacing.y;
		const float spacing_L = IM_FLOOR(spacing_x * 0.50f);
		const float spacing_U = IM_FLOOR(spacing_y * 0.50f);
		bb.Min.x -= spacing_L;
		bb.Min.y -= spacing_U;
		bb.Max.x += (spacing_x - spacing_L);
		bb.Max.y += (spacing_y - spacing_U);
	}

	bool item_add;
	if (flags & ImGuiSelectableFlags_Disabled)
	{
		ImGuiItemFlags backup_item_flags = window->DC.ItemFlags;
		window->DC.ItemFlags |= ImGuiItemFlags_Disabled | ImGuiItemFlags_NoNavDefaultFocus;
		item_add = ItemAdd(bb, id);
		window->DC.ItemFlags = backup_item_flags;
	}
	else
	{
		item_add = ItemAdd(bb, id);
	}
	if (!item_add)
	{
		if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns)
			PopColumnsBackground();
		return false;
	}

	// We use NoHoldingActiveID on menus so user can click and _hold_ on a menu then drag to browse child entries
	ImGuiButtonFlags button_flags = 0;
	//if (flags & ImGuiSelectableFlags_NoHoldingActiveID) button_flags |= ImGuiButtonFlags_NoHoldingActiveID;
	if (flags & ImGuiSelectableFlags_SelectOnClick) { button_flags |= ImGuiButtonFlags_PressedOnClick; }
	if (flags & ImGuiSelectableFlags_SelectOnRelease) { button_flags |= ImGuiButtonFlags_PressedOnRelease; }
	if (flags & ImGuiSelectableFlags_Disabled) button_flags |= ImGuiButtonFlags_Disabled;
	if (flags & ImGuiSelectableFlags_AllowDoubleClick) button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;
	if (flags & ImGuiSelectableFlags_AllowItemOverlap) button_flags |= ImGuiButtonFlags_AllowItemOverlap;

	if (flags & ImGuiSelectableFlags_Disabled)
		selected = false;

	const bool was_selected = selected;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held, button_flags);

	// Update NavId when clicking or when Hovering (this doesn't happen on most widgets), so navigation can be resumed with gamepad/keyboard
	if (pressed || (hovered && (flags & ImGuiSelectableFlags_SetNavIdOnHover)))
	{
		if (!g.NavDisableMouseHover && g.NavWindow == window && g.NavLayer == window->DC.NavLayerCurrent)
		{
			g.NavDisableHighlight = true;
#ifdef NDEBUG
			SetNavID(id, window->DC.NavLayerCurrent, 0);
#else
			SetNavID(id, window->DC.NavLayerCurrent, 0);
#endif
		}
	}
	if (pressed)
		MarkItemEdited(id);

	if (flags & ImGuiSelectableFlags_AllowItemOverlap)
		SetItemAllowOverlap();

	// In this branch, Selectable() cannot toggle the selection so this will never trigger.
	if (selected != was_selected) //-V547
		window->DC.LastItemStatusFlags |= ImGuiItemStatusFlags_ToggledSelection;

	// Render
	if (held && (flags & ImGuiSelectableFlags_DrawHoveredWhenHeld))
		hovered = true;
	if (hovered || selected)
	{
		const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
		RenderFrame(bb.Min, bb.Max, col, false, 0.0f);
		RenderNavHighlight(bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);
		ImGuiWindow* window = GetCurrentWindow();
		window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Min.x + 4.0f, bb.Max.y), GetColorU32(ImGuiCol_NavHighlight), 0.0f, ~0);
	}

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns)
	{
		PopColumnsBackground();
		bb.Max.x -= (GetContentRegionMax().x - max_x);
	}

	if (flags & ImGuiSelectableFlags_Disabled) PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]);
	//RenderTextClipped(bb_inner.Min, bb_inner.Max, label, NULL, &label_size, style.SelectableTextAlign, &bb);	
	RenderTextClipped(ImVec2(bb_inner.Min.x + 6.0f, bb_inner.Min.y), ImVec2(bb_inner.Max.x + 6.0f, bb_inner.Max.y), label, NULL, &label_size, style.SelectableTextAlign, &bb);
	if (flags & ImGuiSelectableFlags_Disabled) PopStyleColor();

	// Automatically close popups
	if (pressed && (window->Flags & ImGuiWindowFlags_Popup) && !(flags & ImGuiSelectableFlags_DontClosePopups) && !(window->DC.ItemFlags & ImGuiItemFlags_SelectableDontClosePopup))
		CloseCurrentPopup();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	return pressed;
}

void ImGui::DrawImagePos(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& Pos, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col) {
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImRect bb(Pos, Pos + size);
	window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, GetColorU32(tint_col));
}

void ImGui::DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col) {
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
	window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, GetColorU32(tint_col));
}

bool ImGui::ItemImage(std::string identificator, ImTextureID user_texture_id, int count, const ImVec2& f_size, bool selected, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImVec2 size = ImVec2(32, 33 * 0.90f);
	ImVec2 img_size = ImVec2(f_size.x, f_size.y * 0.90f + 1.0f);
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	std::string unique = identificator + "##itemimage";
	ImGuiID id = window->GetID(unique.c_str());
	ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
	ImRect img_bb(window->DC.CursorPos, window->DC.CursorPos + img_size);
	ItemSize(bb);
	if (!ItemAdd(img_bb, 0))
		return false;

	ImGuiSelectableFlags flags = 0;
	ImGuiButtonFlags button_flags = 0;
	const bool was_selected = selected;
	bool hovered, held;
	bool pressed = ButtonBehavior(img_bb, id, &hovered, &held, button_flags);

	if (pressed || (hovered && (flags & ImGuiSelectableFlags_SetNavIdOnHover)))
	{
		if (!g.NavDisableMouseHover && g.NavWindow == window && g.NavLayer == window->DC.NavLayerCurrent)
		{
			g.NavDisableHighlight = true;
#ifdef NDEBUG
			SetNavID(id, window->DC.NavLayerCurrent, 0);
#else
			SetNavID(id, window->DC.NavLayerCurrent, 0);
#endif
		}
	}
	if (pressed)
		MarkItemEdited(id);

	if (selected != was_selected) //-V547
		window->DC.LastItemStatusFlags |= ImGuiItemStatusFlags_ToggledSelection;

	if (held && (flags & ImGuiSelectableFlags_DrawHoveredWhenHeld))
		hovered = true;

	if (hovered || selected)
	{
		float AddX = 3.5f;
		float AddY = 1.0f;
		const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
		RenderFrame(ImVec2(img_bb.Min.x - AddX, img_bb.Min.y - AddY), ImVec2(img_bb.Max.x + AddX, img_bb.Max.y + AddY), col, false, 0.0f);
		RenderNavHighlight(img_bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);
		ImGuiWindow* window = GetCurrentWindow();
		window->DrawList->AddRectFilled(ImVec2(img_bb.Min.x - AddX, img_bb.Min.y - AddY), ImVec2(img_bb.Min.x, img_bb.Max.y + AddY), GetColorU32(ImGuiCol_NavHighlight), 0.0f, ~0);
	}
	if (user_texture_id)
	{
		window->DrawList->AddImage(user_texture_id, img_bb.Min, img_bb.Max, uv0, uv1, GetColorU32(tint_col));
		if (count > 1)
		{
			std::string text = std::to_string(count);
			const ImVec2 label_size = CalcTextSize(text.c_str(), NULL, true);
			const ImVec2 label_size_outline = ImVec2(label_size.x + 10.0f, label_size.y + 10.0f);
			ImVec2 textMin = ImVec2(img_bb.Max.x - (label_size.x), img_bb.Max.y - 10.0f);
			ImVec2 textMax = ImVec2(img_bb.Max.x, img_bb.Max.y);
			RenderTextClipped(textMin, textMax, text.c_str(), NULL, &label_size, style.ButtonTextAlign, &img_bb);
		}
	}
	return pressed;
}

void ImGui::CenterHorizontal(ImVec2 size)
{
	ImVec2 pos = GetCursorPos();
	ImVec2 center = (ImGui::GetWindowSize() - size) * 0.5f;
	SetCursorPos(ImVec2(center.x, pos.y));
}

void ImGui::CenterVertical(ImVec2 size)
{
	ImVec2 pos = GetCursorPos();
	ImVec2 center = (ImGui::GetWindowSize() - size) * 0.5f;
	SetCursorPos(ImVec2(pos.x, center.y));
}

void ImGui::ImageAuto(DirectTexture user_texture_id, float scale_width, float scale_height, bool center, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col) {
	if (user_texture_id == NULL)
		return;
	D3DSURFACE_DESC desc;
	user_texture_id->GetLevelDesc(0, &desc);
	float width = desc.Width * scale_width;
	float height = desc.Height * scale_height;
	if (width > 0 && height > 0) {
		if (center)
		{
			CenterHorizontal(ImVec2(width, height));
		}
		ImGui::Image(user_texture_id, ImVec2(width, height), uv0, uv1, tint_col, border_col);
	}
}

void ImGui::ImageSwitcher(DirectTexture user_texture_id, const ImVec4& border_col) 
{
	if (user_texture_id == NULL)
		return;
	D3DSURFACE_DESC desc;
	user_texture_id->GetLevelDesc(0, &desc);
	float width = desc.Width;
	float height = desc.Height;
	if (width > 0 && height > 0) {;
		ImVec2 size = ImVec2(width, height);
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
		if (border_col.w > 0.0f)
			bb.Max += ImVec2(2, 2);
		ItemSize(bb);
		if (!ItemAdd(bb, 0))
			return;

		window->DrawList->AddRectFilled(bb.Min, bb.Max, GetColorU32(border_col), 0.0f);
		window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), ImVec2(0, 0), ImVec2(1, 1), GetColorU32(ImVec4(1, 1, 1, 1)));
		//window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, GetColorU32(tint_col));
	}
}

bool ImGui::PopupButton(const char* tooltip, ImTextureID texture, const ImVec2& size) {
	int frame_padding = -1;
	const ImVec2& uv0 = ImVec2(0, 0);
	const ImVec2& uv1 = ImVec2(1, 1);
	const ImVec4& bg_col = ImVec4(0, 0, 0, 0);
	const ImVec4& tint_col = ImVec4(1, 1, 1, 1);
	ImTextureID user_texture_id = NULL;
	user_texture_id = texture;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void*)(intptr_t)tooltip);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	if (hovered) {
		ImGui::BeginTooltip();
		ImGui::SetTooltip(tooltip);
		ImGui::EndTooltip();
	}
	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

	return pressed;
}

void ImGui::Logo(ImTextureID texture, const ImVec2& size) {
	int frame_padding = -1;
	const ImVec2& uv0 = ImVec2(0, 0);
	const ImVec2& uv1 = ImVec2(1, 1);
	const ImVec4& bg_col = ImVec4(0, 0, 0, 0);
	const ImVec4& tint_col = ImVec4(1, 1, 1, 1);
	ImTextureID user_texture_id = texture;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void*)(intptr_t)texture);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return;
	//bool hovered, held;
	//bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	// Render
	//const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	//RenderNavHighlight(bb, id);
	//RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	//if (bg_col.w > 0.0f)
	//	window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));
	return;
}

bool ImGui::IconMenuButton(const char* tooltip, ImTextureID texture, const ImVec2& size_arg, bool Open) {
	int frame_padding = -1;
	const ImVec2& uv0 = ImVec2(0, 0);
	const ImVec2& uv1 = ImVec2(1, 1);
	const ImVec4& bg_col = ImVec4(0, 0, 0, 0);
	const ImVec4& tint_col = ImVec4(1, 1, 1, 1);
	ImTextureID user_texture_id = texture;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void*)(intptr_t)tooltip);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;

	const ImVec2 label_size = CalcTextSize(tooltip, NULL, true);
	ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size_arg + padding * 2);
	ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + (ImVec2(size_arg.x - 8.0f, size_arg.y - 8.0f)));
	if (Open)
	{
		ImVec2 size = ImVec2(size_arg.x + label_size.x, size_arg.y);
		bb = ImRect(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	}
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	if (hovered && !Open) {
		ImGui::BeginTooltip();
		ImGui::SetTooltip(tooltip);
		ImGui::EndTooltip();
	}
	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	if (Open)
	{
		window->DrawList->AddImage(user_texture_id, ImVec2(image_bb.Min.x, image_bb.Min.y + 3.0f), ImVec2(image_bb.Max.x, image_bb.Max.y + 3.0f), uv0, uv1, GetColorU32(tint_col));
		ImVec2 textMin = ImVec2(bb.Min.x + size_arg.x + 0.0f, bb.Min.y);
		ImVec2 textMax = ImVec2(bb.Max.x, bb.Max.y);
		RenderTextClipped(textMin, textMax, tooltip, NULL, &label_size, style.ButtonTextAlign, &bb);
	}
	else
	{
		window->DrawList->AddImage(user_texture_id, ImVec2(image_bb.Min.x + 3.0f, image_bb.Min.y + 3.0f), ImVec2(image_bb.Max.x + 3.0f, image_bb.Max.y + 3.0f), uv0, uv1, GetColorU32(tint_col));
	}
	return pressed;
}

bool ImGui::IconButton(bool* state, const char* tooltip, ImTextureID textureOn, ImTextureID textureOff, const ImVec2& size) {
	int frame_padding = -1;
	const ImVec2& uv0 = ImVec2(0, 0);
	const ImVec2& uv1 = ImVec2(1, 1);
	const ImVec4& bg_col = ImVec4(0, 0, 0, 0);
	const ImVec4& tint_col = ImVec4(1, 1, 1, 1);
	ImTextureID user_texture_id = NULL;
	if (*state) {
		user_texture_id = textureOn;
	}
	else {
		user_texture_id = textureOff;
	}
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void*)(intptr_t)tooltip);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	if (hovered) {
		ImGui::BeginTooltip();
		ImGui::SetTooltip(tooltip);
		ImGui::EndTooltip();
	}
	if (pressed) {
		*state = !(*state);
	}

	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

	return pressed;
}

bool ImGui::IconButton2(bool* state, const char* tooltip, ImTextureID texture, ImTextureID textureOn, ImTextureID textureOff, const ImVec2& size) {
	int frame_padding = -1;
	const ImVec2& uv0 = ImVec2(0, 0);
	const ImVec2& uv1 = ImVec2(1, 1);
	const ImVec4& bg_col = ImVec4(0, 0, 0, 0);
	const ImVec4& tint_col = ImVec4(1, 1, 1, 1);
	ImTextureID user_texture_id = texture;
	ImTextureID user_texture_id2 = NULL;
	if (*state) {
		user_texture_id2 = textureOn;
	}
	else {
		user_texture_id2 = textureOff;
	}
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void*)(intptr_t)tooltip);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	if (hovered) {
		ImGui::BeginTooltip();
		ImGui::SetTooltip(tooltip);
		ImGui::EndTooltip();
	}
	if (pressed) {
		*state = !(*state);
	}

	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));

	window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));
	window->DrawList->AddImage(user_texture_id2, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

	return pressed;
}

bool ImGui::InputFloatMinMax(const char* label, float* v, float Min, float Max, float step, float step_fast, const char* format, ImGuiInputTextFlags flags)
{
	flags |= ImGuiInputTextFlags_CharsScientific;
	void* p_data = (void*)v;
	void* p_step = (void*)(step > 0.0f ? &step : NULL);
	void* p_step_fast = (void*)(step_fast > 0.0f ? &step_fast : NULL);
	ImGuiDataType data_type = ImGuiDataType_Float;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiStyle& style = g.Style;

	if (format == NULL)
		format = DataTypeGetInfo(data_type)->PrintFmt;

	char buf[64];
	DataTypeFormatString(buf, IM_ARRAYSIZE(buf), data_type, p_data, format);

	bool value_changed = false;
	if ((flags & (ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsScientific)) == 0)
		flags |= ImGuiInputTextFlags_CharsDecimal;
	flags |= ImGuiInputTextFlags_AutoSelectAll;
	flags |= ImGuiInputTextFlags_NoMarkEdited;  // We call MarkItemEdited() ourselve by comparing the actual data rather than the string.

	if (p_step != NULL)
	{
		const float button_size = GetFrameHeight();

		BeginGroup(); // The only purpose of the group here is to allow the caller to query item data e.g. IsItemActive()
		PushID(label);
		SetNextItemWidth(ImMax(1.0f, CalcItemWidth() - (button_size + style.ItemInnerSpacing.x) * 2));

		if (InputText("", buf, IM_ARRAYSIZE(buf), flags))
		{
			float final_value;
			sscanf(buf, "%f", &final_value);
			printf("%f \n", final_value);
			if (final_value >= Min && final_value <= Max)
			{
				value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialTextA.Data, data_type, p_data, format);
			}
		}

		// Step buttons
		const ImVec2 backup_frame_padding = style.FramePadding;
		style.FramePadding.x = style.FramePadding.y;
		ImGuiButtonFlags button_flags = ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups;
		if (flags & ImGuiInputTextFlags_ReadOnly)
			button_flags |= ImGuiButtonFlags_Disabled;
		SameLine(0, style.ItemInnerSpacing.x);
		void* final_step = g.IO.KeyCtrl && p_step_fast ? p_step_fast : p_step;
		if (ButtonEx("-", ImVec2(button_size, button_size), button_flags))
		{
			float final_value = *(float*)v - *(float*)final_step;
			if (final_value >= Min && final_value <= Max)
			{
				DataTypeApplyOp(data_type, '-', p_data, p_data, final_step);
				value_changed = true;
			}
		}
		SameLine(0, style.ItemInnerSpacing.x);
		if (ButtonEx("+", ImVec2(button_size, button_size), button_flags))
		{
			float final_value = *(float*)v + *(float*)final_step;
			if (final_value >= Min && final_value <= Max)
			{
				DataTypeApplyOp(data_type, '+', p_data, p_data, final_step);
				value_changed = true;
			}
		}

		const char* label_end = FindRenderedTextEnd(label);
		if (label != label_end)
		{
			SameLine(0, style.ItemInnerSpacing.x);
			TextEx(label, label_end);
		}
		style.FramePadding = backup_frame_padding;

		PopID();
		EndGroup();
	}
	else
	{
		if (InputText(label, buf, IM_ARRAYSIZE(buf), flags))
		{
			float final_value;
			sscanf(buf, "%f", &final_value);
			printf("%f \n", final_value);
			if (final_value >= Min && final_value <= Max)
			{
				value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialTextA.Data, data_type, p_data, format);
			}
		}
	}
	if (value_changed)
		MarkItemEdited(window->DC.LastItemId);

	return value_changed;
}

bool ImGui::Hotkey( DWORD& hotKeyTime,const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y*2.0f);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	const bool focus_requested_by_code = focus_requested;//&& (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent)
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (IsKeyPressedMap(ImGuiKey_Escape)) {
			*k = 0;
			ImGui::ClearActiveID();
		}
		else {
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);

	if (*k != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, KeyNames[*k]);
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "<Press a key>");
		hotKeyTime = GetTickCount();
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);
	return value_changed;
}

