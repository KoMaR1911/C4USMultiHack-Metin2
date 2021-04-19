#pragma once

class MainForm
{
public:
	

	static size_t CurTabOpen ;
	static size_t CurMenuOpen;
	static bool IsInitialized;
	static bool SideBarIsOpen;
	static bool ShowFishLog;

	static bool IsRadarHovered;
	static void AddTab(size_t Index, const char* Text);
	static void AddMenu(size_t Index, ImTextureID texture, const char* Text);




	static void Initialize();
	static void ShowRadar();
	static void Menu();

	static void SetImages();
	static bool Hotkey(int vKey, int time = 500);

	static map<string, DirectTexture> ResourceMap;
	//static DirectTexture LogoHref;
	//static DirectTexture Background;
	//static DirectTexture WindowOn;
	//static DirectTexture WindowOff;
	//static DirectTexture RadarOn;
	//static DirectTexture RadarOff;
	//static DirectTexture MHOn;
	//static DirectTexture MHOff;
	//static DirectTexture AutologinOn;
	//static DirectTexture AutologinOff;
	//static DirectTexture FishbotOn;
	//static DirectTexture FishbotOff;
	//static DirectTexture ExitGameIcon;
	//static DirectTexture ChannelChangerIcon;
	//static DirectTexture LogOn;
	//static DirectTexture LogOff;
	////MenuTabs
	//static DirectTexture MainTab;
	//static DirectTexture FishbotTab;
	//static DirectTexture AdditionalTab;
	//static DirectTexture VisualsTab;
	//static DirectTexture ProtectionTab;
	//static DirectTexture SettingsTab;
	//static DirectTexture DeveloperTab;

	//static DirectTexture ninja_a_0;
	//static DirectTexture ninja_a_1;
	//static DirectTexture ninja_a_2;
	//static DirectTexture ninja_a_3;
	//static DirectTexture ninja_a_4;
	//static DirectTexture ninja_a_5;

	//static DirectTexture ninja_d_0;
	//static DirectTexture ninja_d_1;
	//static DirectTexture ninja_d_2;
	//static DirectTexture ninja_d_3;
	//static DirectTexture ninja_d_4;
	//static DirectTexture ninja_d_5;

	//static DirectTexture shaman_d_0;
	//static DirectTexture shaman_d_1;
	//static DirectTexture shaman_d_2;
	//static DirectTexture shaman_d_3;
	//static DirectTexture shaman_d_4;
	//static DirectTexture shaman_d_5;

	//static DirectTexture shaman_h_0;
	//static DirectTexture shaman_h_1;
	//static DirectTexture shaman_h_2;
	//static DirectTexture shaman_h_3;
	//static DirectTexture shaman_h_4;
	//static DirectTexture shaman_h_5;

	//static DirectTexture sura_b_0;
	//static DirectTexture sura_b_1;
	//static DirectTexture sura_b_2;
	//static DirectTexture sura_b_3;
	//static DirectTexture sura_b_4;
	//static DirectTexture sura_b_6;

	//static DirectTexture sura_w_0;
	//static DirectTexture sura_w_1;
	//static DirectTexture sura_w_2;
	//static DirectTexture sura_w_3;
	//static DirectTexture sura_w_4;
	//static DirectTexture sura_w_5;

	//static DirectTexture warrior_b_0;
	//static DirectTexture warrior_b_1;
	//static DirectTexture warrior_b_2;
	//static DirectTexture warrior_b_3;
	//static DirectTexture warrior_b_4;
	//static DirectTexture warrior_b_5;

	//static DirectTexture warrior_m_0;
	//static DirectTexture warrior_m_1;
	//static DirectTexture warrior_m_2;
	//static DirectTexture warrior_m_3;
	//static DirectTexture warrior_m_4;
	//static DirectTexture warrior_m_5;

	//static DirectTexture skill_none;
	//static DirectTexture skill_on;
	//static DirectTexture skill_off;
	static map < pair<DWORD, DirectTexture>, pair<string, DWORD>> TabMenuList;
};
