#pragma once
class Inventory :public IAbstractModuleBase, public Singleton<Inventory>
{
private:
public:
	void OnStart()
	{

	}

	void OnStop()
	{
	}

	map<int, string> attributesMap =
	{
		{ 0, "None"},
		{ 1, "Max. HP +%d"},
		{ 2, "Max. SP +%d"},
		{ 3, "Vitality +%d"},
		{ 4, "Intelligence +%d"},
		{ 5, "Strength +%d"},
		{ 6, "Dexterity +%d"},
		{ 9, "Casting Speed +%d%%"},
		{ 10, "HP Regeneration +%d%%"},
		{ 12, "Poisoning chance %d%%"},
		{ 13, "Blackout chance %d%%"},
		{ 14, "Slowing chance %d%%"},
		{ 15, "Chance of critical hit +%d%%"},
		{ 16, "%d%% Chance for piercing Hits"},
		{ 17, "Strong against Half Humans +%d%%"},
		{ 18, "Strong against Animals +%d%%"},
		{ 19, "Strong against Orcs +%d%%"},
		{ 20, "Strong against Mystics +%d%%"},
		{ 21, "Strong against Undead +%d%%"},
		{ 22, "Strong against Devils +%d%%"},
		{ 23, "%d%% damage  will be absorbed by HP"},
		{ 27, "Chance to block a close-combat attack %d%%"},
		{ 28, "Chance to avoid Arrows %d%%"},
		{ 29, "Sword Defence %d%%"},
		{ 30, "Two-Handed Defence %d%%"},
		{ 31, "Dagger Defence %d%%"},
		{ 32, "Bell Defence %d%%"},
		{ 33, "Fan Defence %d%%"},
		{ 34, "Arrow Defence %d%%"},
		{ 35, "Fire Resistance %d%%"},
		{ 36, "Lightning Resistance %d%%"},
		{ 37, "Magic Resistance %d%%"},
		{ 38, "Wind Resistance %d%%"},
		{ 39, "%d%% Chance to reflect close combat hits"},
		{ 41, "Poison Resistance %d%%"},
		{ 43, "%d%% Chance for EXP Bonus"},
		{ 44, "%d%% Chance to drop double Yang"},
		{ 45, "%d%% Chance to drop double the Items"},
		{ 48, "Defence against blackouts"},
		{ 49, "Defence against slowing"},
		{ 53, "Attack Value +%d"},
		{ 71, "Skill Damage %d%%"},
		{ 72, "Average Damage %d%%"},
	};

	int Page = 1;
	vector<int> selectedSlots = { };
	bool PlayerIsInstance = false;
	int PackCount = 1;
	int SplitCount = 1;
	
	ImVec4 titleColor = ImVec4(0.9490f, 0.9058f, 0.7568f, 1.0f);
	ImVec4 socketColor = ImVec4(0.5411f, 0.7254f, 0.5568f, 1.0f);
	ImVec4 bonusColor = ImVec4(0.6911f, 0.8754f, 0.7068f, 1.0f);
	ImVec4 inactiveSwitcher = ImVec4(1.0f, 0.0f, 0.0f, 0.2f);
	ImVec4 finishedSwitcher = ImVec4(0.0f, 1.0f, 0.0f, 0.2f);

	int bonusSwitcherSpeed = 10;
	int bonusSlot[6] = { 0 };
	bool bonusSlotRunning[6] = { 0 };

	int bonusSlotPacketCount[6] = { 0 };
	int bonusSlotChanged[6] = { 0 };

	map < DWORD, int> lastLastItemAttributes[6];

	int bonusIndexType[6][5];
	int bonusIndexLastType[6][5];
	int bonusIndexValue[6][5];
	int bonusIndexLastValue[6][5];

	template <typename Map>
	bool map_compare(Map const& lhs, Map const& rhs) {
		return lhs.size() == rhs.size()
			&& std::equal(lhs.begin(), lhs.end(),
				rhs.begin());
	}

	bool Match(map < DWORD, int> bsItemAttributes, map < DWORD, int> currentItemAttributes)
	{
		for (map < DWORD, int>::iterator itor = bsItemAttributes.begin(); itor != bsItemAttributes.end(); itor++)
		{
			bool itemHaveOne = false;
			for (map < DWORD, int>::iterator itorSecound = currentItemAttributes.begin(); itorSecound != currentItemAttributes.end(); itorSecound++)
			{
				if (itorSecound->first == itor->first && itorSecound->second >= itor->second)
				{
					itemHaveOne = true;
				}
			}
			if (!itemHaveOne)
			{
				return false;
			}
		}
		return true;
	}

	int GetBonusTypeFromMap(int index)
	{
		int i = 0;
		for (auto it : attributesMap)
		{
			if (i == index)
			{
				return it.first;
			}
			i++;
		}
	}

	void OnUpdate()
	{
		PlayerIsInstance = GameFunctionsCustom::PlayerIsInstance();
		if (!PlayerIsInstance)
		{
			return;
		}
		if (DynamicTimer::CheckAutoSet("BonusSwitcher", bonusSwitcherSpeed))
		{
			for (int i = 0; i < 6; i++)
			{
				if (bonusSlot[i] != 0 && bonusSlotRunning[i])
				{
					bool mixItem = false;
					map < DWORD, int> lastItemAttributes;
					map < DWORD, int> slotItemAttributes;
					map < DWORD, int> currentItemAttributes;
					for (int bonus = 0; bonus < 5; bonus++)
					{
						BYTE bType;
						short bValue;
						GameFunctions::PlayerGetItemAttribute(TItemPos(INVENTORY, bonusSlot[i]), bonus, &bType, &bValue);
						if (GetBonusTypeFromMap(bonusIndexType[i][bonus]) != 0)
						{
							slotItemAttributes.insert(make_pair((DWORD)GetBonusTypeFromMap(bonusIndexType[i][bonus]), (int)bonusIndexValue[i][bonus]));
						}
						if (currentItemAttributes.size() <= 5)
						{
							if (!currentItemAttributes.count(bType))
							{
								if (bType != 0)
								{
									currentItemAttributes.insert(make_pair((DWORD)bType, (int)bValue));
								}
							}
						}
						if (lastItemAttributes.size() <= 5)
						{
							if (!lastItemAttributes.count(bType))
							{
								if (bonusIndexLastType[i][bonus] != 0)
								{
									lastItemAttributes.insert(make_pair((DWORD)bonusIndexLastType[i][bonus], (int)bonusIndexLastValue[i][bonus]));
								}
							}
						}
						bonusIndexLastType[i][bonus] = bType;
						bonusIndexLastValue[i][bonus] = bValue;
					}
					if (!Match(slotItemAttributes, currentItemAttributes))
					{
						if (!map_compare(currentItemAttributes, lastItemAttributes))
						{
							if (!map_compare(lastLastItemAttributes[i], lastItemAttributes))
							{
								bonusSlotChanged[i]++;
							}
							lastLastItemAttributes[i] = lastItemAttributes;
						}
						if (bonusSlotChanged[i] == bonusSlotPacketCount[i])
						{
							vector<DWORD> slots = GameFunctionsCustom::FindItemSlotsInInventory(71084);
							GameFunctions::NetworkStreamSendItemUseToItemPacket(TItemPos(INVENTORY, slots[0]), TItemPos(INVENTORY, bonusSlot[i]));
							bonusSlotPacketCount[i]++;
						}
					}
					else
					{
						string title = "Bonus switcher slot ";
						title += to_string(bonusSlot[i] + 1);
						title += " completed after ";
						title += to_string(bonusSlotPacketCount[i]);
						title += " changes!";
						MiscExtension::UpdateBalloon(Globals::mainHwnd, XOR("C4US.PL - MultiHack"), title.c_str(), NULL);
						for (int bonus = 0; bonus < 5; bonus++)
						{
							bonusIndexLastType[i][bonus] = 0;
							bonusIndexLastValue[i][bonus] = 0;
						}
						bonusSlotPacketCount[i] = 0;
						bonusSlotChanged[i] = 0;
						bonusSlotRunning[i] = false;
						lastLastItemAttributes[i].clear();
					}
				}
			}
		}
	}

	void OnRender()
	{
	}

	string GetItemIconPath(int vnum)
	{
		DWORD* pItemData;
		GameFunctions::ItemManagerGetItemDataPointer(vnum, &pItemData);
		std::string iconPath = "";
		switch (Globals::Server)
		{
		case ServerName::METINPL:
			iconPath = GetStr((DWORD)pItemData + 92);
			break;
		case ServerName::AELDRA:
			iconPath = GetStr((DWORD)pItemData + 80);
			break;
		case ServerName::KEVRA:
			iconPath = GetStr((DWORD)pItemData + 100);
			break;
		default:
			iconPath = GetStr((DWORD)pItemData + 76);
			break;
		}
		return iconPath;
	}

	void OnTabbarRefine()
	{
		ImGui::PushItemWidth(100); ImGui::SliderInt("Count", &Settings::REFINE_UPGRADE_COUNT, 1, 9); ImGui::SameLine();
		if (ImGui::Button("Upgrade"))
		{
			for (int i = 0; i < Settings::REFINE_UPGRADE_COUNT; i++)
			{
				for (auto slot : selectedSlots)
				{
					GameFunctions::NetworkStreamSendRefinePacket(slot, Settings::REFINE_UPGRADE_TYPE);
				}
			}
		}
	}

	void OnTabbarActions()
	{
		if (ImGui::Button("Split"))
		{
			int i = 0;
			for (auto slot : selectedSlots)
			{
				DelayActions::Append(150 * i, &GameFunctionsCustom::ItemSplitter, slot, PackCount, SplitCount);
				i++;
			}
		}  ImGui::SameLine();
		ImGui::InputInt("Pack##split", &PackCount, 0, 0);  ImGui::SameLine();
		ImGui::InputInt("Count##split", &SplitCount, 0, 0);
		if (ImGui::Button("Sell"))
		{
			for (auto slot : selectedSlots)
			{
				GameFunctions::NetworkStreamSendShopSellPacketNew(slot, GameFunctions::PlayerGetItemCount(TItemPos(INVENTORY, slot)));
			}
		}
	}

	string IDName(const char* btn, int id)
	{
		return btn + (string)"##" + to_string(id);
	}

	void OnTabbarBS()
	{
		ImGui::SliderInt("Switchbot Speed", &bonusSwitcherSpeed, 0, 100);
		ImGui::BeginTable("##tablebs", 3, ImGuiTableFlags_Borders, ImVec2(0.0f, 0.0f));
		float width = 85.0f;
		float height = 105.0f;
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
		int index = 0;
		for (int row = 0; row < 2; row++)
		{
			ImGui::TableNextRow(ImGuiTableRowFlags_None, height);
			for (int column = 0; column < 3; column++)
			{
				ImGui::TableSetColumnIndex(column);
				if (selectedSlots.size() == 1 && bonusSlot[index] == 0)
				{
					if (ImGui::Button(IDName(ICON_FA_PLUS, index).c_str()))
					{
						ImGui::OpenPopup(IDName("Bonus Switcher", index).c_str());
					}
					if (ImGui::BeginPopupModal(IDName("Bonus Switcher", index).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
					{
						int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, selectedSlots[0]));
						DirectTexture D3DTexture = GameFunctionsCustom::GetD3DTexture(GetItemIconPath(currentVnum).c_str());
						ImGui::ImageAuto(D3DTexture, 1.0f, 1.0f, true);
						const char* itemName = GameFunctions::ItemDataGetName(currentVnum);
						ImVec2 label_size = ImGui::CalcTextSize(itemName, NULL, true);
						ImGui::CenterHorizontal(label_size);
						ImGui::TextColored(titleColor, StringExtension::ASCIIToUTF8(itemName).c_str());
						for (int i = 0; i < 5; i++)
						{
							ImGui::Combo(("Bonus " + to_string(i + 1)).c_str(), &bonusIndexType[index][i], attributesMap);
							ImGui::InputInt(("##Bonus " + to_string(i + 1)).c_str(), &bonusIndexValue[index][i]);
						}
						if (ImGui::Button("Add", ImVec2(120.0f, 0.0f)))
						{
							bonusSlot[index] = selectedSlots[0];
							ImGui::CloseCurrentPopup();
						}
						ImGui::SameLine();
						if (ImGui::Button("Close", ImVec2(120.0f, 0.0f)))
						{
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}
				}
				if (bonusSlot[index] == 0)
				{
					index++;
					continue;
				}
				int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, bonusSlot[index]));
				if (currentVnum > 0)
				{
					ImGui::BeginTable("##tableitembs", 2, ImGuiTableFlags_None, ImVec2(0.0f, 0.0f));
					ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 32.0f);
					ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 36.0f);
					ImGui::TableNextRow(ImGuiTableRowFlags_None, 100.0f);
					ImGui::TableSetColumnIndex(0);
					DirectTexture D3DTexture = GameFunctionsCustom::GetD3DTexture(GetItemIconPath(currentVnum).c_str());
					ImGui::ImageSwitcher(D3DTexture, bonusSlotRunning[index] ? inactiveSwitcher : finishedSwitcher);
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("Slot %d", bonusSlot[index] + 1);
					if(ImGui::Button(IDName(ICON_FA_PLAY, index).c_str(), ImVec2(20.0f, 20.0f)))
					{
						bonusSlotRunning[index] = true;
					}	ImGui::SameLine();
					if (ImGui::Button(IDName(ICON_FA_PAUSE, index).c_str(), ImVec2(20.0f, 20.0f)))
					{
						bonusSlotRunning[index] = false;
					}
					if (ImGui::Button(IDName(ICON_FA_EDIT, index).c_str(), ImVec2(20.0f, 20.0f)))
					{
						ImGui::OpenPopup(IDName("Bonus Switcher", index).c_str());
					}	ImGui::SameLine();
					if (ImGui::Button(IDName(ICON_FA_TRASH, index).c_str(), ImVec2(20.0f, 20.0f)))
					{
						bonusSlot[index] = 0;
						for (int bonus = 0; bonus < 5; bonus++)
						{
							bonusIndexLastType[index][bonus] = 0;
							bonusIndexLastValue[index][bonus] = 0;
						}
						bonusSlotPacketCount[index] = 0;
						bonusSlotChanged[index] = 0;
						bonusSlotRunning[index] = false;
						lastLastItemAttributes[index].clear();
					}
					if (ImGui::BeginPopupModal(IDName("Bonus Switcher", index).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
					{
						int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, bonusSlot[index]));
						DirectTexture D3DTexture = GameFunctionsCustom::GetD3DTexture(GetItemIconPath(currentVnum).c_str());
						ImGui::ImageAuto(D3DTexture, 1.0f, 1.0f, true);
						const char* itemName = GameFunctions::ItemDataGetName(currentVnum);
						ImVec2 label_size = ImGui::CalcTextSize(itemName, NULL, true);
						ImGui::CenterHorizontal(label_size);
						ImGui::TextColored(titleColor, StringExtension::ASCIIToUTF8(itemName).c_str());
						for (int i = 0; i < 5; i++)
						{
							ImGui::Combo(("Bonus " + to_string(i + 1)).c_str(), &bonusIndexType[index][i], attributesMap);
							ImGui::InputInt(("##Bonus " + to_string(i + 1)).c_str(), &bonusIndexValue[index][i]);
						}
						if (ImGui::Button("Close", ImVec2(240.0f, 0.0f)))
						{
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}
					ImGui::EndTable();
					index++;
				}
			}
		}
		ImGui::EndTable();
	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("RefineBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::BeginTable("##table1", 2);
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 205.0f);
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		if (PlayerIsInstance)
		{
			int Multipler = (Page - 1) * 45;
			int i = 0;
			static ImGuiTableFlags flags = ImGuiTableFlags_Borders;//ImGuiTableFlags_RowBg
			ImGui::BeginTable("##tableinventory", 5, flags, ImVec2(0.0f, 0.0f));
			float width = 32.0f;
			float height = 33.0f;
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, width);
			for (int row = 0; row < 9; row++)
			{
				ImGui::TableNextRow(ImGuiTableRowFlags_None, height);
				for (int column = 0; column < 5; column++)
				{
					ImGui::TableSetColumnIndex(column);
					int currentSlot = i + Multipler;
					int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, currentSlot));
					if (currentVnum > 0)
					{

						DirectTexture D3DTexture = GameFunctionsCustom::GetD3DTexture(GetItemIconPath(currentVnum).c_str());
						D3DSURFACE_DESC desc;
						D3DTexture->GetLevelDesc(0, &desc);
						std::string itemid = "##" + std::to_string(currentSlot);
						bool isSelected = std::find(selectedSlots.begin(), selectedSlots.end(), currentSlot) != selectedSlots.end();
						if (ImGui::ItemImage(itemid, D3DTexture, GameFunctions::PlayerGetItemCount(TItemPos(INVENTORY, currentSlot)), ImVec2(desc.Width, desc.Height), isSelected))
						{
							if (isSelected)
							{
								selectedSlots.erase(std::find(selectedSlots.begin(), selectedSlots.end(), currentSlot));
							}
							else
							{
								selectedSlots.push_back(currentSlot);
							}
						}
						if (ImGui::IsItemHovered()) {
							ImGui::BeginTooltip();
							std::string name = GameFunctions::ItemDataGetName(currentVnum);
							ImGui::TextColored(titleColor, StringExtension::ASCIIToUTF8(name.c_str()).c_str());
							if (Globals::Server != ServerName::METINPL)
							{
								for (int bonus = 0; bonus < 5; bonus++)
								{
									BYTE bType;
									short bValue;
									GameFunctions::PlayerGetItemAttribute(TItemPos(INVENTORY, currentSlot), bonus, &bType, &bValue);
									if (bType != 0)
									{
										ImGui::TextColored(bonusColor, attributesMap[bType].c_str(), bValue);
									}
								}
							}
							ImGui::EndTooltip();
						}
					}
					else
					{
						bool isSelected = std::find(selectedSlots.begin(), selectedSlots.end(), currentSlot) != selectedSlots.end();
						if (isSelected)
						{
							selectedSlots.erase(std::find(selectedSlots.begin(), selectedSlots.end(), currentSlot));
						}
					}
					i++;
				}
			}
			ImGui::EndTable();
		}
		ImGui::TableSetColumnIndex(1);
		ImGui::PushItemWidth(70); ImGui::SliderInt("Page", &Page, 1, Settings::INVENTORY_PAGE_COUNT);  ImGui::SameLine();
		if (ImGui::Button("Uncheck All"))
		{
			selectedSlots.clear();
		}
		ImGui::BeginTabBar("#Inventory Manager");
		if (ImGui::BeginTabItem("Refine"))
		{
			OnTabbarRefine();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Actions"))
		{
			OnTabbarActions();
			ImGui::EndTabItem();
		}
		if (Globals::Server != ServerName::METINPL)
		{
			if (ImGui::BeginTabItem("Bonus Switcher"))
			{
				OnTabbarBS();
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
		ImGui::EndTable();
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(32, "Inventory");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 32:
			OnTab1();
			break;
		}
	}
};