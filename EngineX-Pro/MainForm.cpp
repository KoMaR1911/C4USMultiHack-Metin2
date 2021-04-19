#include "stdafx.h"
#include "CRender.h"
#include "MainForm.h"
#include "xorstr.hpp"
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef HRESULT(WINAPI* Prototype_Present)(DirectDevice2, const RECT*, const RECT*, HWND, const RGNDATA*);
Prototype_Present Original_Present;
typedef HRESULT(WINAPI* Prototype_End)(DirectDevice2);
Prototype_End Original_End;
typedef HRESULT(WINAPI* Prototype_Reset)(DirectDevice2, D3DPRESENT_PARAMETERS*);
Prototype_Reset Original_Reset;

DirectTexture ImageLoad(int resourceID = 0)
{
	DirectTexture texture = nullptr;
	D3DXCreateTextureFromResource(Device::pDevice, Globals::hModule, MAKEINTRESOURCE(resourceID), &texture);
	return texture;
}

bool MainForm::IsRadarHovered = false;
map<string, DirectTexture> MainForm::ResourceMap;

//DirectTexture MainForm::LogoHref;
//DirectTexture MainForm::Background;
//DirectTexture MainForm::WindowOn;
//DirectTexture MainForm::WindowOff;
//DirectTexture MainForm::RadarOn;
//DirectTexture MainForm::RadarOff;
//DirectTexture MainForm::MHOn;
//DirectTexture MainForm::MHOff;
//DirectTexture MainForm::AutologinOn;
//DirectTexture MainForm::AutologinOff;
//DirectTexture MainForm::FishbotOn;
//DirectTexture MainForm::FishbotOff;
//DirectTexture MainForm::ExitGameIcon;
//DirectTexture MainForm::ChannelChangerIcon;
//
//DirectTexture MainForm::LogOn;
//DirectTexture MainForm::LogOff;
//
//DirectTexture MainForm::MainTab;
//DirectTexture MainForm::FishbotTab;
//DirectTexture MainForm::AdditionalTab;
//DirectTexture MainForm::VisualsTab;
//DirectTexture MainForm::ProtectionTab;
//DirectTexture MainForm::SettingsTab;
//DirectTexture MainForm::DeveloperTab;
//
//
//DirectTexture MainForm::ninja_a_0;
//DirectTexture MainForm::ninja_a_1;
//DirectTexture MainForm::ninja_a_2;
//DirectTexture MainForm::ninja_a_3;
//DirectTexture MainForm::ninja_a_4;
//DirectTexture MainForm::ninja_a_5;
//
//DirectTexture MainForm::ninja_d_0;
//DirectTexture MainForm::ninja_d_1;
//DirectTexture MainForm::ninja_d_2;
//DirectTexture MainForm::ninja_d_3;
//DirectTexture MainForm::ninja_d_4;
//DirectTexture MainForm::ninja_d_5;
//
//DirectTexture MainForm::shaman_d_0;
//DirectTexture MainForm::shaman_d_1;
//DirectTexture MainForm::shaman_d_2;
//DirectTexture MainForm::shaman_d_3;
//DirectTexture MainForm::shaman_d_4;
//DirectTexture MainForm::shaman_d_5;
//
//
//DirectTexture MainForm::shaman_h_0;
//DirectTexture MainForm::shaman_h_1;
//DirectTexture MainForm::shaman_h_2;
//DirectTexture MainForm::shaman_h_3;
//DirectTexture MainForm::shaman_h_4;
//DirectTexture MainForm::shaman_h_5;
//
//
//
//DirectTexture MainForm::sura_b_0;
//DirectTexture MainForm::sura_b_1;
//DirectTexture MainForm::sura_b_2;
//DirectTexture MainForm::sura_b_3;
//DirectTexture MainForm::sura_b_4;
//DirectTexture MainForm::sura_b_6;
//
//
//DirectTexture MainForm::sura_w_0;
//DirectTexture MainForm::sura_w_1;
//DirectTexture MainForm::sura_w_2;
//DirectTexture MainForm::sura_w_3;
//DirectTexture MainForm::sura_w_4;
//DirectTexture MainForm::sura_w_5;
//
//
//DirectTexture MainForm::warrior_b_0;
//DirectTexture MainForm::warrior_b_1;
//DirectTexture MainForm::warrior_b_2;
//DirectTexture MainForm::warrior_b_3;
//DirectTexture MainForm::warrior_b_4;
//DirectTexture MainForm::warrior_b_5;
//
//
//
//DirectTexture MainForm::warrior_m_0;
//DirectTexture MainForm::warrior_m_1;
//DirectTexture MainForm::warrior_m_2;
//DirectTexture MainForm::warrior_m_3;
//DirectTexture MainForm::warrior_m_4;
//DirectTexture MainForm::warrior_m_5;
//
//DirectTexture MainForm::skill_none;
//DirectTexture MainForm::skill_on;
//DirectTexture MainForm::skill_off;

map < pair<DWORD, DirectTexture>, pair<string, DWORD>> MainForm::TabMenuList;

HCURSOR hCurs;
HWND GameHWND = nullptr;
WNDPROC oWndProc = nullptr;
bool CheatWindowOpen = false;
bool LogWindowOpen = false;

void MainForm::SetImages() {
	ResourceMap.insert(make_pair(XOR("LogoHref"), ImageLoad(IDB_PNG1)));
	ResourceMap.insert(make_pair(XOR("Background"), ImageLoad(IDB_PNG2)));
	ResourceMap.insert(make_pair(XOR("WindowOn"), ImageLoad(IDB_PNG3)));
	ResourceMap.insert(make_pair(XOR("WindowOff"), ImageLoad(IDB_PNG4)));
	ResourceMap.insert(make_pair(XOR("RadarOn"), ImageLoad(IDB_PNG5)));
	ResourceMap.insert(make_pair(XOR("RadarOff"), ImageLoad(IDB_PNG6)));
	ResourceMap.insert(make_pair(XOR("AutologinOn"), ImageLoad(IDB_PNG7)));
	ResourceMap.insert(make_pair(XOR("AutologinOff"), ImageLoad(IDB_PNG8)));
	ResourceMap.insert(make_pair(XOR("FishbotOn"), ImageLoad(IDB_PNG9)));
	ResourceMap.insert(make_pair(XOR("FishbotOff"), ImageLoad(IDB_PNG10)));
	ResourceMap.insert(make_pair(XOR("MHOn"), ImageLoad(IDB_PNG11)));
	ResourceMap.insert(make_pair(XOR("MHOff"), ImageLoad(IDB_PNG12)));
	ResourceMap.insert(make_pair(XOR("ExitGameIcon"), ImageLoad(IDB_PNG13)));
	ResourceMap.insert(make_pair(XOR("ChannelChangerIcon"), ImageLoad(IDB_PNG14)));
	ResourceMap.insert(make_pair(XOR("LogOn"), ImageLoad(IDB_PNG15)));
	ResourceMap.insert(make_pair(XOR("LogOff"), ImageLoad(IDB_PNG16)));
	ResourceMap.insert(make_pair(XOR("PotionOff"), ImageLoad(IDB_POTION_OFF)));
	ResourceMap.insert(make_pair(XOR("PotionOn"), ImageLoad(IDB_POTION_ON)));

	ResourceMap.insert(make_pair(XOR("MainTab"), ImageLoad(IDB_MainTab)));
	ResourceMap.insert(make_pair(XOR("FishbotTab"), ImageLoad(IDB_FishbotTab)));
	ResourceMap.insert(make_pair(XOR("AdditionalTab"), ImageLoad(IDB_AdditionalTab)));
	ResourceMap.insert(make_pair(XOR("VisualsTab"), ImageLoad(IDB_VisualsTab)));
	ResourceMap.insert(make_pair(XOR("ProtectionTab"), ImageLoad(IDB_ProtectionTab)));
	ResourceMap.insert(make_pair(XOR("SettingsTab"), ImageLoad(IDB_SettingsTab)));
	ResourceMap.insert(make_pair(XOR("DeveloperTab"), ImageLoad(IDB_DeveloperTab)));

	ResourceMap.insert(make_pair(XOR("ninja_a_0"), ImageLoad(NINJA_A_0)));
	ResourceMap.insert(make_pair(XOR("ninja_a_1"), ImageLoad(NINJA_A_1)));
	ResourceMap.insert(make_pair(XOR("ninja_a_2"), ImageLoad(NINJA_A_2)));
	ResourceMap.insert(make_pair(XOR("ninja_a_3"), ImageLoad(NINJA_A_3)));
	ResourceMap.insert(make_pair(XOR("ninja_a_4"), ImageLoad(NINJA_A_4)));
	ResourceMap.insert(make_pair(XOR("ninja_a_5"), ImageLoad(NINJA_A_5)));
	ResourceMap.insert(make_pair(XOR("ninja_d_0"), ImageLoad(NINJA_D_0)));
	ResourceMap.insert(make_pair(XOR("ninja_d_1"), ImageLoad(NINJA_D_1)));
	ResourceMap.insert(make_pair(XOR("ninja_d_2"), ImageLoad(NINJA_D_2)));
	ResourceMap.insert(make_pair(XOR("ninja_d_3"), ImageLoad(NINJA_D_3)));
	ResourceMap.insert(make_pair(XOR("ninja_d_4"), ImageLoad(NINJA_D_4)));
	ResourceMap.insert(make_pair(XOR("ninja_d_5"), ImageLoad(NINJA_D_5)));

	ResourceMap.insert(make_pair(XOR("shaman_d_0"), ImageLoad(SHAMAN_D_0)));
	ResourceMap.insert(make_pair(XOR("shaman_d_1"), ImageLoad(SHAMAN_D_1)));
	ResourceMap.insert(make_pair(XOR("shaman_d_2"), ImageLoad(SHAMAN_D_2)));
	ResourceMap.insert(make_pair(XOR("shaman_d_3"), ImageLoad(SHAMAN_D_3)));
	ResourceMap.insert(make_pair(XOR("shaman_d_4"), ImageLoad(SHAMAN_D_4)));
	ResourceMap.insert(make_pair(XOR("shaman_d_5"), ImageLoad(SHAMAN_D_5)));
	ResourceMap.insert(make_pair(XOR("shaman_h_0"), ImageLoad(SHAMAN_H_0)));
	ResourceMap.insert(make_pair(XOR("shaman_h_1"), ImageLoad(SHAMAN_H_1)));
	ResourceMap.insert(make_pair(XOR("shaman_h_2"), ImageLoad(SHAMAN_H_2)));
	ResourceMap.insert(make_pair(XOR("shaman_h_3"), ImageLoad(SHAMAN_H_3)));
	ResourceMap.insert(make_pair(XOR("shaman_h_4"), ImageLoad(SHAMAN_H_4)));
	ResourceMap.insert(make_pair(XOR("shaman_h_5"), ImageLoad(SHAMAN_H_5)));

	ResourceMap.insert(make_pair(XOR("sura_b_0"), ImageLoad(SURA_B_0)));
	ResourceMap.insert(make_pair(XOR("sura_b_1"), ImageLoad(SURA_B_1)));
	ResourceMap.insert(make_pair(XOR("sura_b_2"), ImageLoad(SURA_B_2)));
	ResourceMap.insert(make_pair(XOR("sura_b_3"), ImageLoad(SURA_B_3)));
	ResourceMap.insert(make_pair(XOR("sura_b_4"), ImageLoad(SURA_B_4)));
	ResourceMap.insert(make_pair(XOR("sura_b_5"), ImageLoad(SURA_B_5)));
	ResourceMap.insert(make_pair(XOR("sura_w_0"), ImageLoad(SURA_W_0)));
	ResourceMap.insert(make_pair(XOR("sura_w_1"), ImageLoad(SURA_W_1)));
	ResourceMap.insert(make_pair(XOR("sura_w_2"), ImageLoad(SURA_W_2)));
	ResourceMap.insert(make_pair(XOR("sura_w_3"), ImageLoad(SURA_W_3)));
	ResourceMap.insert(make_pair(XOR("sura_w_4"), ImageLoad(SURA_W_4)));
	ResourceMap.insert(make_pair(XOR("sura_w_5"), ImageLoad(SURA_W_5)));

	ResourceMap.insert(make_pair(XOR("warrior_b_0"), ImageLoad(WARRIOR_B_0)));
	ResourceMap.insert(make_pair(XOR("warrior_b_1"), ImageLoad(WARRIOR_B_1)));
	ResourceMap.insert(make_pair(XOR("warrior_b_2"), ImageLoad(WARRIOR_B_2)));
	ResourceMap.insert(make_pair(XOR("warrior_b_3"), ImageLoad(WARRIOR_B_3)));
	ResourceMap.insert(make_pair(XOR("warrior_b_4"), ImageLoad(WARRIOR_B_4)));
	ResourceMap.insert(make_pair(XOR("warrior_b_5"), ImageLoad(WARRIOR_B_5)));
	ResourceMap.insert(make_pair(XOR("warrior_m_0"), ImageLoad(WARRIOR_M_0)));
	ResourceMap.insert(make_pair(XOR("warrior_m_1"), ImageLoad(WARRIOR_M_1)));
	ResourceMap.insert(make_pair(XOR("warrior_m_2"), ImageLoad(WARRIOR_M_2)));
	ResourceMap.insert(make_pair(XOR("warrior_m_3"), ImageLoad(WARRIOR_M_3)));
	ResourceMap.insert(make_pair(XOR("warrior_m_4"), ImageLoad(WARRIOR_M_4)));
	ResourceMap.insert(make_pair(XOR("warrior_m_5"), ImageLoad(WARRIOR_M_5)));
	ResourceMap.insert(make_pair(XOR("skill_none"), ImageLoad(SKILL_NONE)));
	ResourceMap.insert(make_pair(XOR("skill_on"), ImageLoad(SKILL_ON)));
	ResourceMap.insert(make_pair(XOR("skill_off"), ImageLoad(SKILL_OFF)));
}



DWORD HotkeyTime;
bool MainForm::Hotkey(int vKey, int time)
{
	bool isPressed = GetAsyncKeyState(vKey) & 0x8000 && GetTickCount() - HotkeyTime > time ;
	if (isPressed)
	{
		HotkeyTime = GetTickCount();
	}
	return isPressed;
}



bool GetKeyPressedTwice(int vKey, int vKey2, int time = 300)
{
	bool isPressed = GetAsyncKeyState(vKey) & 0x8000 && GetAsyncKeyState(vKey2) & 0x8000 && GetTickCount() - HotkeyTime > time && GetTickCount() - HotkeyTime > 1000;
	if (isPressed)
	{
		HotkeyTime = GetTickCount();
	}
	return isPressed;
}






bool show = true;
bool MainForm::ShowFishLog = true;


#define DEG2RAD(x)  ( (float)(x) * (float)(M_PI / 180.f) )
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
void rotateVector(float& x, float& y, float angle, float originX = 0, float originY = 0) {
	x -= originX;
	y -= originY;
	float tx = x, ty = y;
	float fCos = cos(angle);
	float fSin = sin(angle);

	tx = x * fCos - y * fSin;
	ty = x * fSin + y * fCos;

	x = tx + originX;
	y = ty + originY;
}

void rotateVectorX(float& x, float& y, float angle, float originX = 0, float originY = 0) {
	x -= originX;
	float tx = x;
	float fCos = cos(angle);
	float fSin = sin(angle);
	tx = x * fCos - y * fSin;
	x = tx + originX;
}

void rotateVectorY(float& x, float& y, float angle, float originX = 0, float originY = 0) {
	y -= originY;
	float ty = y;
	float fCos = cos(angle);
	float fSin = sin(angle);
	ty = x * fSin + y * fCos;
	y = ty + originY;
}

string GetMapFolder(int i, int j) 
{
	if (i == 0) 
	{
		return "00000" + to_string(j);
	}
	else if (i == 1)
	{
		return "00100" + to_string(j);
	}
	else if (i == 2) 
	{
		return "00200" + to_string(j);
	}
	else if (i == 3) 
	{
		return "00300" + to_string(j);
	}
	else if (i == 4) 
	{
		return "00400" + to_string(j);
	}
	else if (i == 5) 
	{
		return "00500" + to_string(j);
	}
	return "";
}


int CurSelectedCfg;
int ChannelChanger = 0;
bool m_radarIsActive = false;

INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";
ImColor FrameColor;

size_t MainForm::CurTabOpen = 10;
size_t MainForm::CurMenuOpen = 1;
bool MainForm::IsInitialized = 0;
bool MainForm::SideBarIsOpen = true;
double StartPopup = 0.015487;

ImVec4 TabOpenColor = (ImVec4)ImColor(33, 69, 119);
ImVec4 TabClosedColor = (ImVec4)ImColor(16, 49, 94);
ImVec4 TabHoveredColor = (ImVec4)ImColor(83, 116, 161);
ImVec4 TabClickColor = (ImVec4)ImColor(55, 90, 139);
ImVec4 HeaderFooterColor = (ImVec4)ImColor(28, 40, 64);

void MainForm::AddTab(size_t Index, const char* Text)
{
	static const size_t TabWidth = 75;
	static const size_t TabHeight = 20;

	ImGui::PushID(Index);
	ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.0f, 0.5f));

	if (CurTabOpen == Index)
	{

		ImGui::PushStyleColor(ImGuiCol_Header, (ImVec4)ImColor(45, 45, 45));			// Color on tab open
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(38, 121, 199));
	}
	else 
	{
		ImGui::PushStyleColor(ImGuiCol_Header, (ImVec4)ImColor(15, 16, 15));			// Color on tab closed
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(246, 244, 244));
	}
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor(40, 40, 40));			// Color on mouse hover in tab
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor(35, 35, 35));			// Color on click tab


	bool isSelected = CurTabOpen == Index;
	if (ImGui::Selectable2(Text, isSelected, 0, ImVec2(TabWidth, TabHeight))) 
	{
		CurTabOpen = Index;
		for (map < pair<DWORD, DirectTexture>, pair<string, DWORD>> ::iterator itor = MainForm::TabMenuList.begin(); itor != MainForm::TabMenuList.end(); itor++)
		{
			if (CurMenuOpen == itor->first.first)
			{
				itor->second.second = CurTabOpen;
			}
		}
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(4);
	ImGui::PopID();
}

void MainForm::AddMenu(size_t Index, ImTextureID texture, const char* Text)
{
	static const size_t TabWidth = 28;
	static const size_t TabHeight = 28;

	ImGui::PushID(Index);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

	if (Index > 0)
		ImGui::SameLine();

	bool Open = CurMenuOpen == Index;
	if (Open)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, TabOpenColor);			// Color on tab open
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(255, 255, 255));
	}
	else 
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, TabClosedColor);			// Color on tab closed
		ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(246, 244, 244));
	}

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, TabHoveredColor);			// Color on mouse hover in tab
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, TabClickColor);			// Color on click tab
	
	//ImGui::Dummy(ImVec2(0.0f, 5.0f));
	if (ImGui::IconMenuButton(Text, texture, ImVec2(TabWidth, TabHeight), Open))	// If tab clicked
	{
		CurMenuOpen = Index;
		for (map < pair<DWORD, DirectTexture>, pair<string, DWORD>> ::iterator itor = MainForm::TabMenuList.begin(); itor != MainForm::TabMenuList.end(); itor++)
		{
			if (CurMenuOpen == itor->first.first)
			{
				CurTabOpen = itor->second.second;
			}
		}
	}

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);
	ImGui::PopID();
}


int tes = 0;
int tesk = 0;

//using namespace std::chrono;
ImVec2 bgSize;
ImVec2 midRadar;
float mapSizeX;
float mapSizeY;


D3DVECTOR PositionToRadarPosition(D3DVECTOR posA, D3DVECTOR posB)
{
	D3DVECTOR posRet;
	D3DVECTOR posC = { posA.x - posB.x, posA.y - posB.y, posA.z - posB.z };
	posRet.x = midRadar.x + (posC.x / mapSizeX) * bgSize.x;
	posRet.y = midRadar.y + (posC.y / mapSizeY) * bgSize.y;
	rotateVectorX(posRet.x, posRet.y, DEG2RAD(180.0f), midRadar.x, midRadar.y);
	return posRet;
}

float SizeToZoom(float size)
{
	return size * Settings::RADAR_ZOOM;
}

float minZoom;
void MainForm::ShowRadar() 
{
	ImGui::SetNextWindowBgAlpha(0.9f);
	ImGui::SetNextWindowSize(ImVec2(386, 386));
	if (ImGui::Begin(XOR("Radar"), &m_radarIsActive, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
		if (!GameFunctionsCustom::PlayerIsInstance())
		{
			ImGui::End();
			return;
		}
		IsRadarHovered = ImGui::IsWindowHovered();
		ImVec2 bgPos = ImGui::GetCursorScreenPos();
		bgSize = ImGui::GetContentRegionAvail();
		D3DVECTOR charPosition;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &charPosition);
		D3DVECTOR Position;
		float x, y;
		midRadar = ImVec2(bgPos.x + (bgSize.x / 2), bgPos.y + (bgSize.y / 2));
		mapSizeX = 25600 / -Settings::RADAR_ZOOM;
		mapSizeY = 25600 / Settings::RADAR_ZOOM;
		//MAPA
		LONG GlobalX = charPosition.x;
		LONG GlobalY = charPosition.y;
		GameFunctions::BackgroundLocalPositionToGlobalPosition(GlobalX, GlobalY);

		string MapName = "";
		int Width;
		int Height;
		switch (Globals::Server)
		{
			case ServerName::METINPL:
			{
				TMapInfoGlobal* map_info = (TMapInfoGlobal*)GameFunctions::BackgroundGlobalPositionToMapInfo(GlobalX, GlobalY);
				if (map_info) {
					MapName = GetStr((DWORD)map_info->name);
					Width = map_info->m_dwSizeX;
					Height = map_info->m_dwSizeY;
				}
				break;
			}
			default:
			{
				TMapInfo* map_info = GameFunctions::BackgroundGlobalPositionToMapInfo(GlobalX, GlobalY);
				if (map_info) {
					MapName = GetStr((DWORD)map_info->name);
					Width = map_info->m_dwSizeX;
					Height = map_info->m_dwSizeY;
				}
				break;
			}
		}
		if (MapName != "") {
			minZoom = 2.0f / (Width * Height);
			if (Settings::RADAR_ZOOM < minZoom)
			{
				Settings::RADAR_ZOOM = minZoom;
			}
			float ZoomSizeX = (25600 / mapSizeY) * bgSize.x;
			float ZoomSizeY = (25600 / mapSizeY) * bgSize.y;
			float AtlasX = midRadar.x + (charPosition.x / mapSizeX) * bgSize.x;
			float AtlasY = midRadar.y - (charPosition.y / mapSizeY) * bgSize.y;
			float PosX = AtlasX;
			for (int i = 0; i < Width; i++)
			{
				float PosY = AtlasY;
				for (int j = 0; j < Height; j++)
				{
					string MapPath = MapName;
					MapPath += XOR("\\");
					MapPath += GetMapFolder(i, j);
					MapPath += XOR("\\minimap.dds");
					ImGui::DrawImagePos(GameFunctionsCustom::GetD3DTexture(MapPath.c_str()), ImVec2(ZoomSizeX, ZoomSizeY), ImVec2(PosX, PosY));
					PosY += ZoomSizeY;
				}
				PosX += ZoomSizeX;
			}
		}
		//MAPA
		ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x - bgSize.x / 2.f, midRadar.y), ImVec2(midRadar.x + bgSize.x / 2.f, midRadar.y), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 64)));
		ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x, midRadar.y - bgSize.y / 2.f), ImVec2(midRadar.x, midRadar.y + bgSize.y / 2.f), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 64)));
		x = midRadar.x;
		y = midRadar.y;
		ImVec2 pos1 = ImVec2(x, y - 12);
		ImVec2 pos2 = ImVec2(x - 8, y + 12);
		ImVec2 pos3 = ImVec2(x + 8, y + 12);
		float fov = DEG2RAD(GameFunctionsCustom::PlayerGetRotation());
		rotateVector(pos1.x, pos1.y, fov, x, y);
		rotateVector(pos2.x, pos2.y, fov, x, y);
		rotateVector(pos3.x, pos3.y, fov, x, y);
		//Wait Hack Distance
		float radius = (Settings::MAIN_WH_DISTANCE_VALUE / mapSizeY) * bgSize.x;
		ImVec4 col = Settings::MAIN_WH_RENDER_COLOR;
		col.w = 0.35f;
		ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(col), 50);
		ImGui::GetWindowDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 255)), 50);
		//Player Triangle
		ImGui::GetWindowDrawList()->AddTriangleFilled(pos1, pos2, pos3, ImGui::ColorConvertFloat4ToU32(ImColor(210, 105, 30)));
		ImGui::GetWindowDrawList()->AddTriangle(pos1, pos2, pos3, ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 255)));
		if (IsRadarHovered && GetForegroundWindow() == Globals::mainHwnd)
		{
			if (Hotkey(VK_MBUTTON)) {
				float winX = midRadar.x - ImGui::GetWindowPos().x;
				float winY = midRadar.y - ImGui::GetWindowPos().y;
				float mouseX = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
				float mouseY = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;
				float distanceX = winX - mouseX;
				float distanceY = winX - mouseY;
				float scaleX = distanceX * (mapSizeY / bgSize.x);
				float scaleY = distanceY * (mapSizeY / bgSize.y);
				D3DVECTOR new_position{ charPosition.x - scaleX, charPosition.y - scaleY, charPosition.z };
				float distance = MiscExtension::CountDistanceTwoPoints(new_position.x, new_position.y, charPosition.x, charPosition.y);
				int TmpCount = 0;
				int Count, Crap;
				D3DVECTOR TempPos = GameFunctionsCustom::GetTempPosition(new_position, Count);
				while (TmpCount < Count)
				{
					TempPos = GameFunctionsCustom::GetTempPosition(new_position, Crap);
					GameFunctions::InstanceBaseSCRIPT_SetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), TempPos.x, TempPos.y);
					GameFunctions::NetworkStreamSendCharacterStatePacket(TempPos, GameFunctionsCustom::PlayerGetRotation(), 0, 0);
					TmpCount += 1;
				}
				GameFunctionsCustom::PlayerMoveToDestPixelPositionDirection(TempPos);
			}
		}
		//FarmBot Points
		if (Settings::RADAR_WAYPOINT_SHOW_ENABLE) 
		{
			for (auto itor = Settings::cordsMaps.begin(); itor != Settings::cordsMaps.end(); itor++)
			{
				auto ItorNext = itor;
				ItorNext++;
				if (ItorNext == Settings::cordsMaps.end())
					break;
				D3DVECTOR LinePosition1 = PositionToRadarPosition(*itor, charPosition);
				D3DVECTOR LinePosition2 = PositionToRadarPosition(*ItorNext, charPosition);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(LinePosition1.x, LinePosition1.y), ImVec2(LinePosition2.x, LinePosition2.y), ImGui::ColorConvertFloat4ToU32(Settings::RADAR_WAYPOINT_COLOR));
				ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(LinePosition2.x, LinePosition2.y), SizeToZoom(2.0f), ImGui::ColorConvertFloat4ToU32(ImColor(255, 255, 255, 255)));
			}
		}
		// Players positions
		ImU32 color = ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 255, 255));
		auto m_kAliveInstMap = GameFunctionsCustom::GetObjectList(OBJECT_ALL);
		for (auto itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
		{
			DWORD* instance = itor->second;
			if (instance == NULL || instance == GameFunctions::PlayerNEW_GetMainActorPtr())
				continue;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(instance, &Position);
			D3DVECTOR ObjectPosition = PositionToRadarPosition(Position, charPosition);
			int objectType = GameFunctions::InstanceBaseGetInstanceType(instance);
			if (objectType == 0) {
				ImVec2 start;
				ImVec2 end;
				if (Settings::RADAR_BOSS_SHOW_ENABLE && GameFunctionsCustom::InstanceIsBoss(instance)) 
				{
					start = ImVec2(ObjectPosition.x - 6, ObjectPosition.y - 6);

					end = ImVec2(ObjectPosition.x + 6, ObjectPosition.y + 6);
					color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_BOSS_COLOR);
				}
				else if (Settings::RADAR_MONSTER_SHOW_ENABLE)
				{
					start = ImVec2(ObjectPosition.x - 2, ObjectPosition.y - 2);
					end = ImVec2(ObjectPosition.x + 2, ObjectPosition.y + 2);
					color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_MONSTER_COLOR);
				}

				ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
				ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
			}
			else if (objectType == 1) 
			{
				if (GameFunctionsCustom::InstanceIsResource(GameFunctions::InstanceBaseGetVirtualNumber(instance)) && Settings::RADAR_MINING_SHOW_ENABLE)
				{
					color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_MINE_COLOR);
					ImVec2 start = ImVec2(ObjectPosition.x - 4, ObjectPosition.y - 4);
					ImVec2 end = ImVec2(ObjectPosition.x + 4, ObjectPosition.y + 4);
					ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
					ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
				}
				else if (Settings::RADAR_NPC_SHOW_ENABLE) 
				{
					color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_NPC_COLOR);
					ImVec2 start = ImVec2(ObjectPosition.x - 2, ObjectPosition.y - 2);
					ImVec2 end = ImVec2(ObjectPosition.x + 2, ObjectPosition.y + 2);
					ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
					ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
				}
			}
			else if (objectType == 2 && Settings::RADAR_STONE_SHOW_ENABLE) 
			{
				color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_STONE_COLOR);
				ImVec2 start = ImVec2(ObjectPosition.x - 4, ObjectPosition.y - 4);
				ImVec2 end = ImVec2(ObjectPosition.x + 4, ObjectPosition.y + 4);
				ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
				ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
			}
			else if (objectType == 3 && Settings::RADAR_STONE_SHOW_ENABLE)
			{
				color = ImGui::ColorConvertFloat4ToU32(ImColor(102, 0, 102));
				ImVec2 start = ImVec2(ObjectPosition.x - 7, ObjectPosition.y - 7);
				ImVec2 end = ImVec2(ObjectPosition.x + 7, ObjectPosition.y + 7);
				ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
				ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
			}
			else if (objectType == 6 && Settings::RADAR_PLAYER_SHOW_ENABLE) 
			{
				color = ImGui::ColorConvertFloat4ToU32(Settings::RADAR_PLAYER_COLOR);
				ImVec2 start = ImVec2(ObjectPosition.x - 3, ObjectPosition.y - 3);
				ImVec2 end = ImVec2(ObjectPosition.x + 3, ObjectPosition.y + 3);
				ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, 1.0f);
				ImGui::GetWindowDrawList()->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 64)));
			}
		}
	}
	if (ImGui::Button(" + ")) 
	{
		Settings::RADAR_ZOOM *= 2.0f;
		if (Settings::RADAR_ZOOM >= 4.0f)
			Settings::RADAR_ZOOM = 4.0f;
	} ImGui::SameLine();
	if (ImGui::Button(" - "))
	{
		Settings::RADAR_ZOOM *= 0.5f;
		if (Settings::RADAR_ZOOM <= minZoom)
			Settings::RADAR_ZOOM = minZoom;
	}
	ImGui::End();
}

void MainForm::Menu() {
	//FPS TEST
	CurrentTickCount = clock() * 0.001f;
	Fps++;
	if ((CurrentTickCount - LastTickCount) > 1.0f)
	{
		LastTickCount = CurrentTickCount;
		sprintf(FrameRate, XOR("[FPS: %d] "), Fps);
		if (Fps < 16)
		{
			FrameColor = ImColor(255, 30, 0, 255);
		}
		else if (Fps < 44)
		{
			FrameColor = ImColor(249, 105, 14, 255);
		}
		else if (Fps < 63)
		{
			FrameColor = ImColor(30, 255, 0, 255);
		}
		else
		{
			FrameColor = ImColor(255, 252, 0, 255);
		}
		Fps = 0;
	}
	//
	if (GetForegroundWindow() == Globals::mainHwnd)
	{
		if (Hotkey(Settings::MAIN_GLOBAL_SWITCH_KEY))
		{
			Settings::GLOBAL_SWITCH_ENABLE = !Settings::GLOBAL_SWITCH_ENABLE;
			if (Settings::GLOBAL_SWITCH_ENABLE == true)
			{
				Main::Instance().OnStart();
			}
			else 
			{
				Main::Instance().OnStop();
			}
		}
								
		

		
	}
	if (SideBarIsOpen)
	{
#ifdef DX9
		ImGui_ImplDX9_NewFrame();
#else
		ImGui_ImplDX8_NewFrame();
#endif	
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;
#if defined(DEVELOPER_MODE) && defined(_DEBUG)
		//	ImGui::ShowDemoWindow();
#else
			if (StartPopup != 0.077435)
			{
				
				
				ImGui::OpenPopup(VMProtectDecryptStringA("WARNING"));
				bool open = true;
				if (ImGui::BeginPopupModal(VMProtectDecryptStringA("WARNING"), &open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
				{
					ImGui::Text(VMProtectDecryptStringA("The only owner of this cheat is C4US.PL!"));
					ImGui::Text(VMProtectDecryptStringA("It is 100%% free, if you paid u have been scammed."));
					ImGui::NewLine();
					ImGui::Text(VMProtectDecryptStringA("If you downloaded the cheat from an unknown source, scan your computer!"));
					ImGui::Text(VMProtectDecryptStringA("We recommend you to create an account on C4US.PL, because it will allow you to use our work in the future."));
					if (ImGui::Button(VMProtectDecryptStringA("OK")))
					{
						
						StartPopup = StartPopup * 5;
						ImGui::CloseCurrentPopup();
					} ImGui::SameLine();
					if (ImGui::Button(VMProtectDecryptStringA("Website")))
					{
						StartPopup = StartPopup * 5;
						ImGui::CloseCurrentPopup();
						MiscExtension::OpenWebiste(VMProtectDecryptStringA("https://www.cheats4us.pl"));
					} ImGui::SameLine();
					if (ImGui::Button(VMProtectDecryptStringA("Discord")))
					{
						StartPopup = StartPopup * 5;
						ImGui::CloseCurrentPopup();
						MiscExtension::OpenWebiste(VMProtectDecryptStringA("https://discord.gg/Wvh3JEe"));
					}
					ImGui::EndPopup();
				}
				
			}
			
#endif
			ImGui::SetNextWindowBgAlpha(0.0f);
			ImGui::SetNextWindowPos(ImVec2(0, GameFunctionsCustom::GetWindowHeight() / 10));
			ImGui::Begin(XOR("Buttons"), &SideBarIsOpen, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavInputs);
			{
				ImGui::TextColored(ImColor(MiscExtension::RandomInt(0,255), MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), 255), XOR("C4US.PL"));
				ImGui::TextColored(FrameColor, FrameRate);
				ImGui::IconButton(&CheatWindowOpen, XOR("Cheat Window"), ResourceMap[XOR("WindowOn")], ResourceMap[XOR("WindowOff")], ImVec2(20, 20));
				ImGui::IconButton(&LogWindowOpen, XOR("Log Window"), ResourceMap[XOR("LogOn")], ResourceMap[XOR("LogOff")], ImVec2(20, 20));
				ImGui::IconButton(&m_radarIsActive, XOR("Radar Window"), ResourceMap[XOR("RadarOn")], ResourceMap[XOR("RadarOff")], ImVec2(20, 20));
				if (ImGui::IconButton(&Settings::GLOBAL_SWITCH_ENABLE, XOR("MultiHack Switch"), ResourceMap[XOR("MHOn")], ResourceMap[XOR("MHOff")], ImVec2(20, 20)))
				{
					if (Settings::GLOBAL_SWITCH_ENABLE == true) 
					{
						Main::Instance().OnStart();
					}
					else
					{
						Main::Instance().OnStop();
					}
				}
				ImGui::IconButton(&Settings::PROTECTION_AUTO_LOGIN_ENABLE, XOR("Auto-Login"), ResourceMap[XOR("AutologinOn")], ResourceMap[XOR("AutologinOff")], ImVec2(20, 20));

#ifdef FISHBOT
				if (ImGui::IconButton(&Settings::FISH_ENABLE, XOR("FishBot Switch"), ResourceMap[XOR("FishbotOn")], ResourceMap[XOR("FishbotOff")], ImVec2(20, 20)))
				{
					if (Settings::FISH_ENABLE) 
					{
						Fish::Instance().OnStart();
					}
					else
					{
						Fish::Instance().OnStop();
					}
				}
#endif
				ImGui::IconButton(&Settings::MAIN_POTION_ENABLE, XOR("Auto-Potion"), ResourceMap[XOR("PotionOn")], ResourceMap[XOR("PotionOff")], ImVec2(20, 20));
				if (ImGui::PopupButton(XOR("Channel Change"), ResourceMap[XOR("ChannelChangerIcon")], ImVec2(20, 20)))
				{
					ImGui::OpenPopup(XOR("##channelchange"));
				}
				if (ImGui::BeginPopup(XOR("##channelchange"), ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (Globals::Server == ServerName::METINPL)
					{
						for (map< pair<DWORD, pair<string, string>>, pair<DWORD, string>>::iterator itor = Settings::SERVER_INFO_LIST_GLOBAL.begin(); itor != Settings::SERVER_INFO_LIST_GLOBAL.end(); itor++)
						{
							const char* serverName = (const char*)(GetStr(Globals::iCPythonNetworkStreamInstance + 0x7A70));
							if (StringExtension::Contains(serverName, itor->first.second.first.c_str()))
							{
								if (ImGui::Button(itor->first.second.second.c_str(), ImVec2(60, 0)))
								{
									GameFunctions::NetworkStream__DirectEnterMode_Set(0);
									GameFunctions::NetworkStreamConnect(inet_addr(itor->second.second.c_str()), itor->second.first + Settings::MAIN_CHANNEL_CHANGER_PORT_OFFSET);
								}
							}
						}
					}
					else
					{
						for (map< pair<DWORD, pair<DWORD, string>>, pair<DWORD, string>>::iterator itor = Settings::SERVER_INFO_LIST.begin(); itor != Settings::SERVER_INFO_LIST.end(); itor++)
						{
							if (itor->first.second.first == Globals::Server)
							{
								if (ImGui::Button(itor->first.second.second.c_str(), ImVec2(60, 0)))
								{
									GameFunctions::NetworkStream__DirectEnterMode_Set(0);
									GameFunctions::NetworkStreamConnect(inet_addr(itor->second.second.c_str()), itor->second.first + Settings::MAIN_CHANNEL_CHANGER_PORT_OFFSET);
								}
							}
						}
					}			
					ImGui::EndPopup();
				}
				if (ImGui::PopupButton(XOR("Exit Game"), ResourceMap[XOR("ExitGameIcon")], ImVec2(20, 20)))
				{
					ImGui::OpenPopup(XOR("##exitgame"));
				}
				if (ImGui::BeginPopup(XOR("##exitgame"), ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (ImGui::Button(XOR("Exit"), ImVec2(60, 0))) {
						
						PostQuitMessage(0);
					}
					if (ImGui::Button(XOR("Logout"), ImVec2(60, 0)))
					{
						
						if (Globals::Server == ServerName::METINPL)
						{
							GameFunctions::NetworkStreamSendCommandPacket(0, 2, "");
						}
						else
						{
							GameFunctions::NetworkStreamSendChatPacket(XOR("/logout"));
						}
					}
					
					ImGui::EndPopup();
				}
			}
			ImGui::End();
			if (LogWindowOpen)
			{
				Logger::Draw();
			}
			if(CheatWindowOpen)
			{
				//ImGui::Begin("Color Window");
				//ImGui::ColorEdit3("TabOpen", (float*)&TabOpenColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
				//ImGui::ColorEdit3("TabCloes", (float*)&TabClosedColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
				//ImGui::ColorEdit3("TabHovered", (float*)&TabHoveredColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
				//ImGui::ColorEdit3("TabClick", (float*)&TabClickColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
				//ImGui::ColorEdit3("HeaderFooterColor", (float*)&HeaderFooterColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
				//ImGui::End();
				//ImGui::DrawImage(Background, ImVec2(1920 / 2.25, 1080 / 2.35), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.f, 1.f, 1.f, 0.2f));
				//ImGui::SameLine();
				ImGui::SetNextWindowBgAlpha(0.90f);
				ImGui::SetNextWindowSize(ImVec2(600, 385));
				ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin(XOR("##Window"), &CheatWindowOpen, flags);
				ImGui::PopStyleVar();
				ImGui::PushStyleColor(ImGuiCol_ChildBg, HeaderFooterColor);
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
				ImGui::BeginChild(XOR("Header"), ImVec2(ImGui::GetWindowWidth(), 40), false);
				ImGui::Logo(ResourceMap[XOR("LogoHref")], ImVec2(38, 28));
				for (map < pair<DWORD, DirectTexture>, pair<string, DWORD>> ::iterator itor = MainForm::TabMenuList.begin(); itor != MainForm::TabMenuList.end(); itor++)
				{
					AddMenu(itor->first.first, itor->first.second, itor->second.first.c_str());
				}
				ImGui::EndChild();
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();

				ImGui::DrawImage(ResourceMap[XOR("Background")], ImVec2(1920 / 3.2, 600 / 1.5), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.f, 1.f, 1.f, 0.75f));
				ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor(18, 20, 23, 200));
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 6.0f));
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
				ImGui::BeginChildFrame(1, ImVec2(75, 325));
				for (map< pair<DWORD, DWORD>, pair<bool, std::shared_ptr<IAbstractModuleBase>>> ::iterator itor = MainCore::moduleList.begin(); itor != MainCore::moduleList.end(); itor++)
				{
					if (itor->second.first && itor->first.second == CurMenuOpen)
					{
						itor->second.second->OnTabs();
					}
				}
				ImGui::EndChild();
				ImGui::PopStyleColor();
				ImGui::PopStyleVar(2);

				ImGui::SameLine();

				ImGui::BeginChildFrame(2, ImVec2(ImGui::GetWindowWidth() - 80, 325), ImGuiWindowFlags_NoBackground);
				for (map< pair<DWORD, DWORD>, pair<bool, std::shared_ptr<IAbstractModuleBase>>> ::iterator itor = MainCore::moduleList.begin(); itor != MainCore::moduleList.end(); itor++)
				{
					itor->second.second->OnMenu();
				}
				ImGui::EndChild();

				ImGui::PushStyleColor(ImGuiCol_ChildBg, HeaderFooterColor);
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
				ImGui::BeginChild(XOR("Footer"), ImVec2(ImGui::GetWindowWidth(), 20), false);
				ImGui::Dummy(ImVec2(5.0f, 0.0f)); ImGui::SameLine();
				ImGui::Text(XOR("Multihack Metin2 - Free Version"));
				ImGui::SameLine(ImGui::GetWindowWidth() - 45);
				ImGui::Text(XOR("C4US.PL"));
				ImGui::EndChild();
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::End();
			}

			if (m_radarIsActive) 
			{
				ShowRadar();
			}	
		}
		ImGui::EndFrame();
		ImGui::Render();
#ifdef DX9
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#else
		ImGui_ImplDX8_RenderDrawData(ImGui::GetDrawData());
#endif	
	}
}


void MainForm::Initialize() 
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	static const ImWchar ranges[] = 
	{
		0x0020, 0x00FF,
		0x0104, 0x017C,
		0,
	};
	ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(&PoppinsMedium_compressed_data, PoppinsMedium_compressed_size, 13.0f, 0, ranges);
	unsigned char* pixels;
	int width, height, BYTEs_per_pixel;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &BYTEs_per_pixel);
	if (Globals::Server != ServerName::METINPL)
	{
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		io.Fonts->AddFontFromMemoryCompressedTTF(&FontAwesome_compressed_data, FontAwesome_compressed_size, 12.0f, &icons_config, icons_ranges);
	}
	font->AddRemapChar(0xA5, 0x0104);
	font->AddRemapChar(0xC6, 0x0106);
	font->AddRemapChar(0xCA, 0x0118);
	font->AddRemapChar(0xA3, 0x0141);
	font->AddRemapChar(0xD1, 0x0143);
	font->AddRemapChar(0xD3, 0x00D3);
	font->AddRemapChar(0x8C, 0x015A);
	font->AddRemapChar(0x8F, 0x0179);
	font->AddRemapChar(0xAF, 0x017B);

	font->AddRemapChar(0xB9, 0x0105);
	font->AddRemapChar(0xE6, 0x0107);
	font->AddRemapChar(0xEA, 0x0119);
	font->AddRemapChar(0xB3, 0x0142);
	font->AddRemapChar(0xF1, 0x0144);
	font->AddRemapChar(0xF3, 0x00F3);
	font->AddRemapChar(0x9C, 0x015B);
	font->AddRemapChar(0x9F, 0x017A);
	font->AddRemapChar(0xBF, 0x017C);

	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = NULL;
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(5, 5);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(6, 6);
	style->ItemInnerSpacing = ImVec2(4, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 10.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
	style->WindowBorderSize = 0.0f;
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.70f, 0.78f, 0.90f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.26f, 0.48f, 0.85f, 0.43f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.70f, 0.78f, 0.90f, 0.05f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.70f, 0.78f, 0.90f, 0.34f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.70f, 0.78f, 0.90f, 0.58f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 191.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.26f, 0.48f, 0.85f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.26f, 0.48f, 0.85f, 0.62f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.33f, 0.84f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.48f, 0.85f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.33f, 0.84f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.26f, 0.48f, 0.85f, 0.60f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.48f, 0.85f, 0.86f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.26f, 0.48f, 0.85f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.48f, 0.85f, 1.00f);
	style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	ImGui_ImplWin32_Init(Globals::mainHwnd);
#ifdef DX9
	ImGui_ImplDX9_Init(Device::pDevice);
#else
	ImGui_ImplDX8_Init(Device::pDevice);
#endif	
	SetImages();

	CurTabOpen = 10;
	D3DXCreateSphere(Device::pDevice, 1.0f, 32, 32, &Device::ms_lpSphereMesh, NULL);
	D3DXCreateCylinder(Device::pDevice, 1.0f, 1.0f, 1.0f, 8, 8, &Device::ms_lpCylinderMesh, NULL);
	oWndProc = (WNDPROC)SetWindowLongPtr(Globals::mainHwnd, GWL_WNDPROC, (LONG)WndProc);
	TabMenuList =
	{
		{make_pair(1, ResourceMap[XOR("MainTab")]), make_pair(XOR("Main"), 10)},
#ifdef FISHBOT
		{ make_pair(2, ResourceMap[XOR("FishbotTab")]), make_pair(XOR("Fishbot"), 20) },
#endif
		{ make_pair(3, ResourceMap[XOR("AdditionalTab")]), make_pair(XOR("Additional"), 31) },
		{ make_pair(4, ResourceMap[XOR("VisualsTab")]), make_pair(XOR("Visuals"), 40) },
		{ make_pair(5, ResourceMap[XOR("ProtectionTab")]), make_pair(XOR("Protection"), 50) },
		{ make_pair(6, ResourceMap[XOR("SettingsTab")]), make_pair(XOR("Settings"), 60) },
#ifdef DEVELOPER_MODE
		{ make_pair(7, ResourceMap[XOR("DeveloperTab")]), make_pair(XOR("Developer"), 70) }
#endif
	};
	IsInitialized = true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (MainForm::SideBarIsOpen) 
	{
		//ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		ImGuiIO& io = ImGui::GetIO();
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			io.MouseDown[0] = true;
			break;
		case WM_LBUTTONUP:
			io.MouseDown[0] = false;
			break;
		case WM_RBUTTONDOWN:
			io.MouseDown[1] = true;
			break;
		case WM_RBUTTONUP:
			io.MouseDown[1] = false;
			break;
		case WM_MBUTTONDOWN:
			io.MouseDown[2] = true;
			break;
		case WM_MBUTTONUP:
			io.MouseDown[2] = false;
			break;
		case WM_MOUSEWHEEL:
			io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
			if (MainForm::IsRadarHovered)
			{
				Settings::RADAR_ZOOM *= GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 2.0f : 0.5f;
				if (Settings::RADAR_ZOOM >= 4.0f)
					Settings::RADAR_ZOOM = 4.0f;
				if (Settings::RADAR_ZOOM <= minZoom)
					Settings::RADAR_ZOOM = minZoom;
			}
			break;		
		case WM_MOUSEMOVE:
			io.MousePos.x = (signed short)(lParam);
			io.MousePos.y = (signed short)(lParam >> 16);
			break;
		case WM_KEYDOWN:
			if (wParam < 256)
				io.KeysDown[wParam] = 1;
			break;
		case WM_KEYUP:
			if (wParam < 256)
				io.KeysDown[wParam] = 0;
			break;
		case WM_CHAR:
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
				io.AddInputCharacter((unsigned short)wParam);
			break;
		}
		if (io.WantCaptureMouse || io.WantCaptureKeyboard || io.WantTextInput) 
		{
			return true;
		}
	}
	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

