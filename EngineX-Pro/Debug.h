#pragma once



class Debug :public IAbstractModuleBase, public Singleton<Debug>
{
private:
	int recv_limit = 3;
	string packetHex = string(900, '\0');;

	D3DVECTOR NewPosition;
public:
	void OnStart()
	{

	}

	void OnStop()
	{
	}



	void OnUpdate()
	{

	}

	void OnRender()
	{
	}


	void Rozdzielacz(int vnum)
	{

	}

	string  whisperTextName = string(500, '\0');
	string  whisperTextMessage = string(500, '\0');

	string ShopName = "";
	int whitePearlPrice = 10000000;
	int bluePearlPrice = 1500000;
	int yabbaPrice = 2500000;
	bool whitePearlAdd = true;
	bool bluePearlAdd = true;
	bool yabbaAdd = true;

	void BuildShop()
	{
		typedef DWORD(__thiscall* GetItemCount)(void* This, TItemPos Cell);
		GetItemCount ItemCount = (GetItemCount)PatternScan::FindPatternGlobal("55 8B EC 83 EC 08 89 4D F8 8D 4D 08 E8 ? ? ? ? 0F B6 C0 85 C0 75 04 33 C0 EB 31", Globals::hEntryBaseAddress, Globals::hEntryBaseSize); //0xEFB70

		DWORD Instance = *reinterpret_cast<DWORD*>(PatternScan::FindPatternGlobal("55 8B EC 83 EC 1C 8D 45 FB", Globals::hEntryBaseAddress, Globals::hEntryBaseSize) + 0x103); //Globals::hEntryBaseAddress + 0x201F3AC
		DWORD iCPythonShopInstance = *reinterpret_cast<DWORD*>(Instance);
		
		typedef void(__thiscall* AddPrivateShopItemStock)(void* This, TItemPos Cell, BYTE dwDisplayPos, DWORD dwPrice, BYTE checkque);
		AddPrivateShopItemStock AddItemStock = (AddPrivateShopItemStock)(PatternScan::FindPatternGlobal("55 8B EC 81 EC 94 01 00 00 56", Globals::hEntryBaseAddress, Globals::hEntryBaseSize));//Globals::hEntryBaseAddress + 0x1ACFC0
		
		typedef void(__thiscall* BuildPrivateShop)(void* This, const char* c_szName);
		BuildPrivateShop BuildShop = (BuildPrivateShop)(PatternScan::FindPatternGlobal("55 8B EC 6A FF 68 ? ? ? ? 64 A1 00 00 00 00 50 81 EC 18 01 00 00 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 00 00 00 00 89 8D DC FE FF FF 8D 4D DC", Globals::hEntryBaseAddress, Globals::hEntryBaseSize));//Globals::hEntryBaseAddress + 0x1AD420

		int shopIndex = 0;
		if (whitePearlAdd)
		{
			vector<DWORD> whiteSlot = GameFunctionsCustom::FindItemSlotsInInventory(27992);
			for (auto slot : whiteSlot)
			{
				if (ItemCount((void*)(Globals::iCPythonPlayerInstance + 4), TItemPos(INVENTORY, slot)) == 1)
				{
					AddItemStock((void*)iCPythonShopInstance, TItemPos(INVENTORY, slot), shopIndex, whitePearlPrice, 0);
					shopIndex++;
				}
			}
		}
		if (bluePearlAdd)
		{
			vector<DWORD> whiteSlot = GameFunctionsCustom::FindItemSlotsInInventory(27993);
			for (auto slot : whiteSlot)
			{
				if (ItemCount((void*)(Globals::iCPythonPlayerInstance + 4), TItemPos(INVENTORY, slot)) == 1)
				{
					AddItemStock((void*)iCPythonShopInstance, TItemPos(INVENTORY, slot), shopIndex, bluePearlPrice, 0);
					shopIndex++;
				}
			}
		}
		if (yabbaAdd)
		{
			vector<DWORD> yabbaSlot = GameFunctionsCustom::FindItemSlotsInInventory(27887);
			for (auto slot : yabbaSlot)
			{
				if (ItemCount((void*)(Globals::iCPythonPlayerInstance + 4), TItemPos(INVENTORY, slot)) == 1)
				{
					AddItemStock((void*)iCPythonShopInstance, TItemPos(INVENTORY, slot), shopIndex, yabbaPrice, 0);
					shopIndex++;
				}
			}
		}
		BuildShop((void*)iCPythonShopInstance, ShopName.c_str());
	}
	DirectTexture LoadTextureFromFile(const char* filename)
	{
		// Load texture from disk
		DirectTexture texture;
		HRESULT hr = D3DXCreateTextureFromFileA(Device::pDevice, filename, &texture);
		if (hr != S_OK)
			return false;

		// Retrieve description of the texture surface so we can access its size
		D3DSURFACE_DESC my_image_desc;
		texture->GetLevelDesc(0, &my_image_desc);
	
		return texture;

		
	}
	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("DebugBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Use Python", &Globals::UsePythonFunctions);
		ImGui::InputText("Shop Name", &ShopName);
		ImGui::Checkbox("Add WhitePearl", &whitePearlAdd);
		ImGui::Checkbox("Add BluePearl", &bluePearlAdd);
		ImGui::Checkbox("Add Yabba", &yabbaAdd);
		ImGui::InputInt("WhitePearl Price", &whitePearlPrice);
		ImGui::InputInt("BluePearl Price", &bluePearlPrice);
		ImGui::InputInt("Yabba Price", &yabbaPrice);
		if(ImGui::Button("Add Items to Shop"))
		{
			BuildShop();
		}
		//ImGui::Text("GetItemCount:0x%x", (*(DWORD*)(GameFunctions::PlayerNEW_GetMainActorPtr() + 512)) - Globals::hEntryBaseAddress);
		ImGui::Text("BaseAddress  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::hEntryBaseAddress).c_str());
		ImGui::Text("CPythonPlayerInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCPythonPlayerInstance).c_str());
		ImGui::Text("CPythonCharacterManagerInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCPythonCharacterManagerInstance).c_str());
		ImGui::Text("CPythonNetworkStreamInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCPythonNetworkStreamInstance).c_str());
		ImGui::Text("CPythonItemInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCPythonItemInstance).c_str());
		ImGui::Text("CItemManagerInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCItemManagerInstance).c_str());
		ImGui::Text("CPythonApplicationInstance  "); ImGui::SameLine();
		ImGui::Text(StringExtension::DWORDToHexString(Globals::iCPythonApplicationInstance).c_str());
		ImGui::Text("Inventory Eq Percent Usage "); ImGui::SameLine(); ImGui::Text(to_string(GameFunctionsCustom::InventoryEquippedPercentage()).c_str());
		ImGui::Text("ID First Slot Item  "); ImGui::SameLine(); ImGui::Text(to_string(GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, 0))).c_str());
		ImGui::Text("ID Weapon Slot Item  "); ImGui::SameLine(); ImGui::Text(to_string(GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4))).c_str());
		ImGui::InputText("Packet Hex", &packetHex[0], packetHex.size());
		if (ImGui::Button("Send Packet"))
		{
			GameFunctionsCustom::SendPacket(string(packetHex.c_str()));
		}
		if (ImGui::Button("TEST 1"))
		{
			cout << GameFunctionsCustom::PlayerIsRodEquipped() << endl;
		}
		if (ImGui::Button("TEST 2"))
		{
			GameFunctions::NetworkStreamSendGiveItemPacket(GameFunctions::PlayerGetTargetVID(), TItemPos(EQUIPMENT, 4), 0);
		}
		if (ImGui::Button("TEST 3"))
		{
			cout << GameFunctions::PlayerGetItemMetinSocket(TItemPos(INVENTORY, 0), 0) << endl;
		}
		if (ImGui::Button("TEST 4"))
		{
			GameFunctions::NetworkStreamSendGiveItemPacket(GameFunctions::PlayerGetTargetVID(), TItemPos(INVENTORY, 0), 0);
		}
		if (ImGui::Button("TEST 6"))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(EQUIPMENT, 4));
		}
		if (ImGui::Button("Reload Icon [Adrian ZJEB]"))
		{
			MainForm::ResourceMap["LogoHref"] = LoadTextureFromFile("c:\\Adi\\logo.png");
			MainForm::ResourceMap["Background"] = LoadTextureFromFile("c:\\Adi\\background2.png");
			MainForm::ResourceMap["WindowOn"] = LoadTextureFromFile("c:\\Adi\\window_on.png");
			MainForm::ResourceMap["WindowOff"] = LoadTextureFromFile("c:\\Adi\\window_off.png");
			MainForm::ResourceMap["RadarOn"] = LoadTextureFromFile("c:\\Adi\\radar_on.png");
			MainForm::ResourceMap["RadarOff"] = LoadTextureFromFile("c:\\Adi\\radar_off.png");
			MainForm::ResourceMap["AutologinOn"] = LoadTextureFromFile("c:\\Adi\\autologin_on.png");
			MainForm::ResourceMap["AutologinOff"] = LoadTextureFromFile("c:\\Adi\\autologin_off.png");
			MainForm::ResourceMap["FishbotOn"] = LoadTextureFromFile("c:\\Adi\\fishbot_on.png");
			MainForm::ResourceMap["FishbotOff"] = LoadTextureFromFile("c:\\Adi\\fishbot_off.png");
			MainForm::ResourceMap["MHOn"] = LoadTextureFromFile("c:\\Adi\\mh_on.png");
			MainForm::ResourceMap["MHOff"] = LoadTextureFromFile("c:\\Adi\\mh_off.png");
			MainForm::ResourceMap["ExitGameIcon"] = LoadTextureFromFile("c:\\Adi\\exit.png");
			MainForm::ResourceMap["ChannelChangerIcon"] = LoadTextureFromFile("c:\\Adi\\channel.png");
			MainForm::ResourceMap["LogOn"] = LoadTextureFromFile("c:\\Adi\\log_on.png");
			MainForm::ResourceMap["LogOff"] = LoadTextureFromFile("c:\\Adi\\log_off.png");
			MainForm::ResourceMap["PotionOff"] = LoadTextureFromFile("c:\\Adi\\Autopoty_OFF.png");
			MainForm::ResourceMap["PotionOn"] = LoadTextureFromFile("c:\\Adi\\Autopoty_ON.png");

			MainForm::ResourceMap["MainTab"] = LoadTextureFromFile("c:\\Adi\\Main.png");
			MainForm::ResourceMap["FishbotTab"] = LoadTextureFromFile("c:\\Adi\\Fishbot.png");
			MainForm::ResourceMap["AdditionalTab"] = LoadTextureFromFile("c:\\Adi\\Additional.png");
			MainForm::ResourceMap["VisualsTab"] = LoadTextureFromFile("c:\\Adi\\Visuals.png");
			MainForm::ResourceMap["SettingsTab"] = LoadTextureFromFile("c:\\Adi\\Protection.png");
			MainForm::ResourceMap["DeveloperTab"] = LoadTextureFromFile("c:\\Adi\\Developer.png");
		}
		if (ImGui::Button("TEST 8"))
		{
			
		}
		if (ImGui::Button("TEST 9"))
		{
			
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(70, "Debug");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 70:
			OnTab1();
			break;
		}
	}

	void DebugMsgBoxNoBlocking(string message,...)
	{
		MessageBox(NULL, "Cheat Wrong Version", "Error", 0);
	}
};