#pragma once
class Item :public IAbstractModuleBase, public Singleton<Item>
{
	vector<TCItemData*> ItemsListDisplay;
private:
	
	



	map< DWORD, pair<string, bool>> itemPickupFilteredList;
	string filterItemLine=  string(60, 0x00);;
	string filterItemLineLast = string(60, 0x00);;

	string newFileName;
	int currentIndex = 0;

	DWORD itemPickupFilteredListSelected = 0;
	DWORD itemPickupSelectedListSelected = 0;
public:
	void OnStart()
	{

	}
	void OnStop()
	{

	}

	void OnRender()
	{
	}

	void OnTab1()
	{
		/*if (!Globals::itemProtoList.size())
		{
			Globals::itemProtoList = GameFunctionsCustom::GetItemProtoList();
		}*/
		if (!Globals::itemProtoNames.size())
		{
			Globals::itemProtoNames = GameFunctionsCustom::GetItemProtoNames();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("PickupBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Pickup Enable", &Settings::ITEM_PICKUP_ENABLE); ImGui::SameLine();
		ImGui::RadioButton("Normal", &Settings::ITEM_PICKUP_TYPE, 0); ImGui::SameLine();
		ImGui::RadioButton("Range", &Settings::ITEM_PICKUP_TYPE, 1);
		ImGui::PushItemWidth(150); ImGui::SliderInt("Delay(ms)", &Settings::ITEM_PICKUP_TIME, 0, 3000); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputInt("Distance", &Settings::ITEM_PICKUP_DISTANCE, 100, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputInt("Step", &Settings::ITEM_PICKUP_STEP, 100, 1000);
		ImGui::Separator();
		ImGui::Checkbox("Filter", &Settings::ITEM_PICKUP_FILTER_ENABLE); ImGui::SameLine();
		ImGui::InputText("Search", &filterItemLine[0], filterItemLine.size());
		ImGui::Columns(2, "PickupList", false);
		ImGui::BeginChild("ItemProtoList", ImVec2(225, 160), true);
		if (strlen(&filterItemLine[0]) >= 2)
		{
			if (filterItemLine != filterItemLineLast)
			{
				filterItemLineLast = filterItemLine;
				itemPickupFilteredList.clear();
				for (map<DWORD, const char*>::iterator itor = Globals::itemProtoNames.begin(); itor != Globals::itemProtoNames.end(); itor++)
				{
					switch (Globals::Server)
					{
					case ServerName::AELDRA:
					{
						if (!StringExtension::Equals(itor->second, "") && StringExtension::Contains(itor->second, filterItemLine.c_str()))
						{
							itemPickupFilteredList.insert(std::make_pair(itor->first, std::make_pair(string(itor->second) + " " + to_string(itor->first), false)));
						}
						break;
					}
					default:
					{
						if (!StringExtension::Equals(itor->second, "") && StringExtension::Contains(itor->second, filterItemLine.c_str()))
						{
							itemPickupFilteredList.insert(std::make_pair(itor->first, std::make_pair(StringExtension::ASCIIToUTF8(itor->second) + " " + to_string(itor->first), false)));
						}
						break;
					}
					}
				}
			}
		}
		if (!itemPickupFilteredList.size())
		{
			ImGui::Text("Type 3 Letters...");
		}
		else
		{
			for (map< DWORD, pair<string, bool>>::iterator itor = itemPickupFilteredList.begin(); itor != itemPickupFilteredList.end(); itor++)
			{
				if (ImGui::Selectable(itor->second.first.c_str(), itor->second.second))
				{
					itemPickupFilteredListSelected = itor->first;
				}
				if (itor->first == itemPickupFilteredListSelected)
				{
					itor->second.second = true;
				}
				else
				{
					itor->second.second = false;
				}

			}
		}
		ImGui::EndChild();
		ImGui::NextColumn();
		ImGui::BeginChild("ItemProtoListFiltered", ImVec2(225, 160), true);
		for (map< DWORD, pair<string, bool>>::iterator itor = Settings::ITEM_PICKUP_SELECTED_LIST.begin(); itor != Settings::ITEM_PICKUP_SELECTED_LIST.end(); itor++)
		{
			if (ImGui::Selectable(itor->second.first.c_str(), itor->second.second))
			{
				itemPickupSelectedListSelected = itor->first;
			}
			if (itor->first == itemPickupSelectedListSelected)
			{
				itor->second.second = true;
			}
			else
			{
				itor->second.second = false;
			}
		}
		ImGui::EndChild();
		ImGui::EndColumns();
		if (ImGui::Button("Add"))
		{
			for (map< DWORD, pair<string, bool>>::iterator itor = itemPickupFilteredList.begin(); itor != itemPickupFilteredList.end(); itor++)
			{
				if (itor->second.second)
				{
					if (Settings::ITEM_PICKUP_SELECTED_LIST.count(itor->first))
					{

					}
					else
					{
						Settings::ITEM_PICKUP_SELECTED_LIST.insert(std::make_pair(itor->first, std::make_pair(itor->second.first, false)));
					}

				}

			}
		}
		ImGui::SameLine(); ImGui::Dummy(ImVec2(200.0f, 0.0f)); ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{

			DWORD key = 0;
			for (map< DWORD, pair<string, bool>>::iterator itor = Settings::ITEM_PICKUP_SELECTED_LIST.begin(); itor != Settings::ITEM_PICKUP_SELECTED_LIST.end(); itor++)
			{
				if (itor->second.second)
				{

					key = itor->first;
				}

			}
			Settings::ITEM_PICKUP_SELECTED_LIST.erase(key);

		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);

		static float ITEM_SLOT_RANDOM_MIN_TIME;
		static float ITEM_SLOT_RANDOM_MAX_TIME;

		ImGui::BeginChild("SlotsBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Random +/- (s.ms)", &Settings::ITEM_SLOT_RANDOM_ENABLE); /*ImGui::SameLine();*/
		ImGui::InputFloatMinMax("Min", &Settings::ITEM_SLOT_RANDOM_MIN_TIME, 0.0f, 100.0f, 0.100, 1);
		ImGui::InputFloatMinMax("Max", &Settings::ITEM_SLOT_RANDOM_MAX_TIME, 0.0f, 100.0f, 0.100, 1);

		ImGui::Separator();
		ImGui::Text("Slots(s.ms)");
		if (ImGui::BeginTable("##table1", 3))
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot3time", &Settings::ITEM_SLOT_3_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("3", &Settings::ITEM_SLOT_3_ENABLE);
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot4time", &Settings::ITEM_SLOT_4_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("4", &Settings::ITEM_SLOT_4_ENABLE);
			ImGui::TableSetColumnIndex(2);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot5time", &Settings::ITEM_SLOT_5_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("5", &Settings::ITEM_SLOT_5_ENABLE);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot6time", &Settings::ITEM_SLOT_6_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("6", &Settings::ITEM_SLOT_6_ENABLE);
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot7time", &Settings::ITEM_SLOT_7_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("7", &Settings::ITEM_SLOT_7_ENABLE);
			ImGui::TableSetColumnIndex(2);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot8time", &Settings::ITEM_SLOT_8_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("8", &Settings::ITEM_SLOT_8_ENABLE);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot9time", &Settings::ITEM_SLOT_9_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("9", &Settings::ITEM_SLOT_10_ENABLE);
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot10time", &Settings::ITEM_SLOT_10_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("10", &Settings::ITEM_SLOT_10_ENABLE);
			ImGui::TableSetColumnIndex(2);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot11time", &Settings::ITEM_SLOT_11_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("11", &Settings::ITEM_SLOT_11_ENABLE);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot12time", &Settings::ITEM_SLOT_12_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("12", &Settings::ITEM_SLOT_12_ENABLE);
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot13time", &Settings::ITEM_SLOT_13_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("13", &Settings::ITEM_SLOT_14_ENABLE);
			ImGui::TableSetColumnIndex(2);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot14time", &Settings::ITEM_SLOT_14_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("14", &Settings::ITEM_SLOT_14_ENABLE);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot15time", &Settings::ITEM_SLOT_15_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("15", &Settings::ITEM_SLOT_15_ENABLE);
			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(100); ImGui::InputFloat("##slot15time", &Settings::ITEM_SLOT_16_TIME, 0.100, 1); ImGui::SameLine();
			ImGui::Checkbox("16", &Settings::ITEM_SLOT_16_ENABLE);
			ImGui::EndTable();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(14, "Pickup");
		MainForm::AddTab(15, "Slots");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 14:
			OnTab1();
			break;
		case 15:
			OnTab2();
			break;
		}
	}

	void OnUpdate()
	{
		
		if (Settings::GLOBAL_SWITCH_ENABLE && GameFunctionsCustom::PlayerIsInstance())
		{		
			Pickup();
			Slots();
//#ifdef VIDGAR
//			vector<DWORD> eraseList;
//			for (map<DWORD, TGroundItemInstance*>::iterator itor = Globals::GroundItemList.begin(); itor != Globals::GroundItemList.end(); itor++)
//			{			
//				D3DVECTOR playerPosition = GameFunctionsCustom::PlayerGetPixelPosition();
//				LONG GlobalX = playerPosition.x;
//				LONG GlobalY = playerPosition.y;	
//				float Distance = MiscExtension::CountDistanceTwoPoints(GlobalX, GlobalY, itor->second->v3EndPosition.x, -itor->second->v3EndPosition.y);
//				if (Distance > 30000)
//				{
//					eraseList.push_back(itor->first);
//				}		
//			}
//			for (auto itor = eraseList.begin(); itor != eraseList.end(); itor++)
//			{
//				Globals::GroundItemList.erase(*itor);
//			}
//#endif
		}

	} 
	void Slots()
	{
		float randomMinMax = 0;
		if (Settings::ITEM_SLOT_RANDOM_ENABLE)
		{
			randomMinMax = MiscExtension::RandomFloat(Settings::ITEM_SLOT_RANDOM_MIN_TIME, Settings::ITEM_SLOT_RANDOM_MAX_TIME);
		}
		if (  Settings::ITEM_SLOT_3_ENABLE && DynamicTimer::CheckAutoSet ("UseSlot3", (randomMinMax + Settings::ITEM_SLOT_3_TIME) *1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 2));
		}
		if (Settings::ITEM_SLOT_4_ENABLE && DynamicTimer::CheckAutoSet("UseSlot4", (randomMinMax + Settings::ITEM_SLOT_4_TIME)* 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 3));
		}
		if (Settings::ITEM_SLOT_5_ENABLE && DynamicTimer::CheckAutoSet("UseSlot5", (randomMinMax + Settings::ITEM_SLOT_5_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 4));
		}
		if (Settings::ITEM_SLOT_6_ENABLE && DynamicTimer::CheckAutoSet("UseSlot6", (randomMinMax + Settings::ITEM_SLOT_6_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 5));
		}
		if (Settings::ITEM_SLOT_7_ENABLE && DynamicTimer::CheckAutoSet("UseSlot7", (randomMinMax + Settings::ITEM_SLOT_7_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 6));
		}
		if (Settings::ITEM_SLOT_8_ENABLE && DynamicTimer::CheckAutoSet("UseSlot8", (randomMinMax + Settings::ITEM_SLOT_8_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 7));

		}
		if (Settings::ITEM_SLOT_9_ENABLE && DynamicTimer::CheckAutoSet("UseSlot9", (randomMinMax + Settings::ITEM_SLOT_9_TIME )* 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 8));
		}
		if (Settings::ITEM_SLOT_10_ENABLE && DynamicTimer::CheckAutoSet("UseSlot10", (randomMinMax + Settings::ITEM_SLOT_10_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 9));
		}
		if (Settings::ITEM_SLOT_11_ENABLE && DynamicTimer::CheckAutoSet("UseSlot11", (randomMinMax + Settings::ITEM_SLOT_11_TIME )* 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 10));
		}
		if (Settings::ITEM_SLOT_12_ENABLE && DynamicTimer::CheckAutoSet("UseSlot12", (randomMinMax + Settings::ITEM_SLOT_12_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 11));
		}
		if (Settings::ITEM_SLOT_13_ENABLE && DynamicTimer::CheckAutoSet("UseSlot13", (randomMinMax + Settings::ITEM_SLOT_13_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 12));
		}
		if (Settings::ITEM_SLOT_14_ENABLE && DynamicTimer::CheckAutoSet("UseSlot14", (randomMinMax + Settings::ITEM_SLOT_14_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 13));
		}
		if (Settings::ITEM_SLOT_15_ENABLE && DynamicTimer::CheckAutoSet("UseSlot15", (randomMinMax + Settings::ITEM_SLOT_15_TIME )* 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 14));
		}
		if (Settings::ITEM_SLOT_16_ENABLE && DynamicTimer::CheckAutoSet("UseSlot16", (randomMinMax + Settings::ITEM_SLOT_16_TIME) * 1000))
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 15));
		}
	}
	void Pickup()
	{
		if (DynamicTimer::CheckAutoSet("PickUp", Settings::ITEM_PICKUP_TIME) && Settings::ITEM_PICKUP_ENABLE)
		{
			map<DWORD, TGroundItemInstance*> groundItemList = GameFunctionsCustom::GetGroundItemList();
			for (map<DWORD, TGroundItemInstance*>::iterator itor = groundItemList.begin(); itor != groundItemList.end(); itor++)
			{
				DWORD itemVID = itor->first;
				TGroundItemInstance* groundItemInstance = itor->second;
				if (Settings::ITEM_PICKUP_FILTER_ENABLE)
				{
					if (!Settings::ITEM_PICKUP_SELECTED_LIST.count(groundItemInstance->dwVirtualNumber))
					{
						continue;
					}		
				}
				D3DVECTOR playerPosition = GameFunctionsCustom::PlayerGetPixelPosition();
				float distance = MiscExtension::CountDistanceTwoPoints(playerPosition.x, playerPosition.y, groundItemInstance->v3EndPosition.x, -groundItemInstance->v3EndPosition.y);
				switch (Settings::ITEM_PICKUP_TYPE)
				{
				case 0://normal
					if (distance < 300)
					{
						GameFunctions::NetworkStreamSendItemPickUpPacket(itemVID);
						if (Settings::ITEM_PICKUP_TIME == 0)
						{
							continue;
						}
						else
						{
							return;
						}
						
					}
					break;
				case 1://range
					if (distance < 300)
					{
						GameFunctions::NetworkStreamSendItemPickUpPacket(itemVID);
						if (Settings::ITEM_PICKUP_TIME == 0)
						{
							continue;
						}
						else
						{
							return;
						}
					}
					else if (distance > 300 && distance < Settings::ITEM_PICKUP_DISTANCE)
					{
						vector< D3DVECTOR> steps = MiscExtension::DivideTwoPointsByDistance(Settings::ITEM_PICKUP_STEP, playerPosition, D3DVECTOR{ groundItemInstance->v3EndPosition.x, -groundItemInstance->v3EndPosition.y, groundItemInstance->v3EndPosition.z });
						int i = 0;
						for (vector< D3DVECTOR>::iterator it = steps.begin(); it != steps.end(); ++it)
						{
							GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						}
						GameFunctions::NetworkStreamSendItemPickUpPacket(itemVID);
						steps = MiscExtension::DivideTwoPointsByDistance(Settings::ITEM_PICKUP_STEP, D3DVECTOR{ groundItemInstance->v3EndPosition.x, -groundItemInstance->v3EndPosition.y, groundItemInstance->v3EndPosition.z }, playerPosition);
						for (vector< D3DVECTOR>::iterator it = steps.begin(); it != steps.end(); ++it)
						{
							GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						}
						if (Settings::ITEM_PICKUP_TIME == 0)
						{
							continue;
						}
						else
						{
							return;
						}
					}
					break;
				}
			}
			
		}
	}
};