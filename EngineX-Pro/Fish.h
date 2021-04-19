#pragma once
class Fish : public IAbstractModuleBase, public Singleton<Fish>
{
private:


public:
	int action = 0;
	int couting = 0;
	bool isEnable = false;
	DWORD lastTimeFishing = 0;
	bool isNeedRoundTimeCast = false;
	DWORD  lastTimeBotCast = 0;
	DWORD  lastTimeBotRoundTime = 0;
	int trueMessage = 0;
	int messageCount = 0;
	D3DVECTOR standingPosition;
	void OnStart()
	{
		isEnable = true;
		lastTimeFishing = GetTickCount();

		lastTimeBotCast = GetTickCount();
		lastTimeBotRoundTime = GetTickCount();
		Logger::Add(Logger::FISH, true, Logger::GREEN, "START");

		standingPosition = GameFunctionsCustom::PlayerGetPixelPosition();
		Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("POSITION %d %d", (int)(standingPosition.x / 100), (int)(standingPosition.y / 100)).c_str());
		NewCast();
	

	}
	void OnStop()
	{
		isEnable = false;
		Logger::Add(Logger::FISH, true, Logger::RED, "STOP");
		standingPosition = { 0, 0, 0 };
		if (Globals::Server == ServerName::METINPL)
		{
			GameFunctions::NetworkStreamSendEmoticon(116);
			GameFunctions::NetworkStreamSendFishingQuitPacket(3, GameFunctionsCustom::PlayerGetRotation());
		}
	}
	void OnUpdate()
	{

		if (isEnable)
		{
			if (Settings::FISH_EMERGENCY_RUN_TIME_ENABLE)
			{
				if ((GetTickCount() - lastTimeFishing) > Settings::FISH_EMERGENCY_RUN_TIME_VALUE&& lastTimeFishing != 0)
				{
					action = -1;
					messageCount = 0;
					trueMessage = 0;
					Logger::Add(Logger::FISH, true, Logger::RED, "RESUME");
					if (Globals::Server == ServerName::METINPL)
					{
						Cast2();
					}
					NewCast();
					lastTimeFishing = GetTickCount();
				}
			}
			if (action > 0 && action < 7)
			{
				if (Settings::FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE)
				{
					int loseRandom = MiscExtension::RandomInt(1, 100);
					if (loseRandom <= Settings::FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE)
					{
						Logger::Add(Logger::FISH, true, Logger::WHITE, "RANDOM FALSE");
						action += 1;
					}
					else
					{


					}
				}
				if (Settings::FISH_CAST_TIME_ENABLE)
				{
					int clickTime = MiscExtension::RandomInt(Settings::FISH_CAST_TIME_MIN_VALUE, Settings::FISH_CAST_TIME_MAX_VALUE);
					if ((GetTickCount() - lastTimeBotCast) > clickTime)
					{
						if (Globals::Server == ServerName::METINPL)
						{
							Cast2();
						}
						else 
						{
							Cast();
						}
						Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("CLICK %d AFTER %d (ms)", action, clickTime).c_str());
						action--;
						
						lastTimeBotCast = GetTickCount();
						if (action == 0)
						{
							lastTimeBotRoundTime = GetTickCount();
							isNeedRoundTimeCast = true;
						}
					}
				}
				else
				{
					if (Globals::Server == ServerName::METINPL)
					{
						Cast2();
					}
					else
					{
						Cast();
					}
					action--;
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("CLICK %d", action).c_str());
					if (action == 0)
					{
						lastTimeBotRoundTime = GetTickCount();
						isNeedRoundTimeCast = true;
					}
				}
			}
			else
			{
				if (Settings::FISH_ROUND_TIME_ENABLE)
				{
					int waitTime = MiscExtension::RandomInt(Settings::FISH_ROUND_TIME_MIN_VALUE, Settings::FISH_ROUND_TIME_MAX_VALUE);
					if ((GetTickCount() - lastTimeBotRoundTime) > waitTime && isNeedRoundTimeCast)
					{

						Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("WAIT FOR ENDING %d (ms)", waitTime).c_str());//GREEN
						NewCast();
						action = -1;
						lastTimeBotRoundTime = GetTickCount();
						isNeedRoundTimeCast = false;
					}
				}
				else
				{
					if ((GetTickCount() - lastTimeBotRoundTime) > 0 && isNeedRoundTimeCast)
					{


						Logger::Add(Logger::FISH, true, Logger::WHITE, "NEW START");
						NewCast();
						action = -1;
						lastTimeBotRoundTime = GetTickCount();
						isNeedRoundTimeCast = false;
					}
				}
			}
		}
	}

	void OnRender()
	{
	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("RandomizerBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		//Przyciski
		ImGui::Checkbox("Stop - Position Changed", &Settings::FISH_STOP_IF_POSITION_CHANGED_ENABLE); 	ImGui::SameLine();
		ImGui::Checkbox("Stop - Equipment Full", &Settings::FISH_STOP_IF_INVENTORY_FULL_ENABLE);
		/*ImGui::Text("Randomizer(1000=1sekunda)");*/
		ImGui::Columns(2, "randomizer", false);  // 3-ways, no border
		ImGui::Checkbox("Random Falsa %", &Settings::FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE);
		ImGui::SliderInt("%", &Settings::FISH_SUCCESS_PERCENTAGE_VALUE, 0, 100);
		ImGui::Checkbox("Random Click Time", &Settings::FISH_CAST_TIME_ENABLE);
		ImGui::InputInt("##randclick", &Settings::FISH_CAST_TIME_MIN_VALUE, 100, 1000);
		ImGui::InputInt("##randclick2", &Settings::FISH_CAST_TIME_MAX_VALUE, 100, 1000);
		ImGui::NextColumn();
		ImGui::Checkbox("Emergency Resume", &Settings::FISH_EMERGENCY_RUN_TIME_ENABLE);
		ImGui::InputInt("##emergencytimeout", &Settings::FISH_EMERGENCY_RUN_TIME_VALUE, 100, 1000);
		ImGui::Checkbox("Random End Times", &Settings::FISH_ROUND_TIME_ENABLE);
		ImGui::InputInt("##randtour", &Settings::FISH_ROUND_TIME_MIN_VALUE, 100, 1000);
		ImGui::InputInt("##randtour2", &Settings::FISH_ROUND_TIME_MAX_VALUE, 100, 1000);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		//Przynety
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("BaitBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Text("Bait Type Use");
		ImGui::Checkbox("1 slot", &Settings::FISH_USE_FIRST_SLOT_ENABLE);

		for (map< pair<DWORD, bool>, pair<DWORD, string>> ::iterator itor = Settings::FISH_BAIT_LIST.begin(); itor != Settings::FISH_BAIT_LIST.end(); itor++)
		{

			ImGui::Checkbox(itor->second.second.c_str(), (bool*)&itor->first.second);
			ImGui::NextColumn();

		}
#ifdef DEVELOPER_MODE
		ImGui::Checkbox("Buy Bait", &Settings::FISH_BUY_BAIT_ENABLE);
		ImGui::InputInt("Count", &Settings::FISH_BUY_BAIT_SHOP_COUNT);
		ImGui::InputInt("Slot", &Settings::FISH_BUY_BAIT_SHOP_SLOT);
		ImGui::Checkbox("Teleport", &Settings::FISH_SHOP_CAST_TELEPORT_ENABLE);
		ImGui::InputInt("Teleport Step", &Settings::FISH_TELEPORT_STEP_RANGE);
		if (ImGui::Button("Add Shop Pos"))
		{
			Settings::FISH_SHOP_TELEPORT_CORDS = GameFunctionsCustom::PlayerGetPixelPosition();
		}
		ImGui::SameLine(); ImGui::Text((to_string(DWORD(Settings::FISH_SHOP_TELEPORT_CORDS.x / 100)) + " " + to_string(DWORD(Settings::FISH_SHOP_TELEPORT_CORDS.y / 100))).c_str());
		if (ImGui::Button("Add Cast Pos"))
		{
			Settings::FISH_CAST_TELEPORT_CORDS = GameFunctionsCustom::PlayerGetPixelPosition();
		}
		ImGui::SameLine(); ImGui::Text((to_string(DWORD(Settings::FISH_CAST_TELEPORT_CORDS.x / 100)) + " " + to_string(DWORD(Settings::FISH_CAST_TELEPORT_CORDS.y / 100))).c_str());
#endif
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab3()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("KillBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Kill Fish", &Settings::FISH_KILL_FISH_ENABLE);
		ImGui::Columns(3, "KillColumns", false);

		ImGui::Separator();

		for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_KILL_FISH_LIST.begin(); itor != Settings::FISH_KILL_FISH_LIST.end(); itor++)
		{
			ImGui::Checkbox(itor->second.second.c_str(), (bool*)&itor->first.second);
			ImGui::NextColumn();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab4()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("DropBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Drop Trash", &Settings::FISH_DROP_TRASH_ENABLE);
		ImGui::Separator();
		ImGui::Columns(3, "DropColumns", false);
		for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_DROP_LIST.begin(); itor != Settings::FISH_DROP_LIST.end(); itor++)
		{
			ImGui::Checkbox(itor->second.second.c_str(), (bool*)&itor->first.second);
			ImGui::NextColumn();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab5()
	{
#ifdef DEVELOPER_MODE
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("SellBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::PushItemWidth(150); ImGui::Checkbox("Sell Trash", &Settings::FISH_SELL_TRASH_ENABLE); ImGui::SameLine();
		ImGui::InputInt("After % EQ Filled", &Settings::FISH_SELL_TRASH_AFTER_PERCENTAGE, 5, 100);
		ImGui::Separator();
		ImGui::Columns(3, "SellColumns", false);
		for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_SELL_LIST.begin(); itor != Settings::FISH_SELL_LIST.end(); itor++)
		{
			ImGui::Checkbox(itor->second.second.c_str(), (bool*)&itor->first.second);
			ImGui::NextColumn();
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
#endif
	}

	void OnTabs()
	{
		MainForm::AddTab(20, "Main");
		MainForm::AddTab(21, "Bait");
		MainForm::AddTab(22, "Kill");
		MainForm::AddTab(23, "Drop");
#ifdef DEVELOPER_MODE
		MainForm::AddTab(24, "Sell");
#endif
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 20:
			OnTab1();
			break;
		case 21:
			OnTab2();
			break;
		case 22:
			OnTab3();
			break;
		case 23:
			OnTab4();
			break;
#ifdef DEVELOPER_MODE
		case 24:
			OnTab5();
			break;
#endif
		}
	}



	void AppendCastDirect(int num)
	{
		if (!isEnable)
		{
			return;
		}
		action = num;
		Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());

	}
	void AppendCastDirectString(int num, const char* message)
	{
		if (!isEnable)
		{
			return;
		}
		action = num;
	}





	void CheckPosition()
	{
		if (Settings::FISH_STOP_IF_POSITION_CHANGED_ENABLE)
		{

			D3DVECTOR currentPosition = GameFunctionsCustom::PlayerGetPixelPosition();
			if ((int)standingPosition.x != (int)currentPosition.x || (int)standingPosition.y != (int)currentPosition.y)
			{
				Logger::Add(Logger::FISH, true, Logger::RED, "DIFFRENT POSITION ABORT!");
				Settings::FISH_ENABLE = false;;
				isEnable = false;
				return;
			}

		}
	}

	void Cast()
	{

		if (!isEnable)
		{
			return;
		}
		CheckPosition();
		if (Settings::FISH_STOP_IF_INVENTORY_FULL_ENABLE)
		{
			//if (GameFunctionsCustom::InventoryEquippedPercentage() > 80)
			//{
			   // MainForm::orbital_log_fishing(0, "##### Prawie Pelny ekwipunek - Stop   ######\n");
			   // ;
			   ///* Settings::FishBotEnable = false;
			   // isEnable = false;*/
			//}
		}
#if defined(DEVELOPER_MODE)		
		
		switch (Globals::Server)
		{
			case ServerName::METINPL:
				{
					GameFunctionsCustom::SendPacket("0E 06 00 06 0A 00");
					break;
				}
			default:
				{
					GameFunctions::PythonPlayerNEW_Fishing();
					/*GameFunctions::NetworkStreamSendFishingPacket(GameFunctionsCustom::PlayerGetRotation());*/
				}
		}
		
#else
		GameFunctions::PythonPlayerNEW_Fishing();
		/*GameFunctions::PlayerSetAttackKeyState();*/
#endif
		lastTimeFishing = GetTickCount();
	}

	void Cast2()
	{
		if (Settings::FISH_DETECT_PLAYER_ENABLE)
		{
			if (GameFunctionsCustom::DetectPlayer(Settings::PROTECTION_DETECT_PLAYER_WHITE_LIST))
			{

				Logger::Add(Logger::FISH, true, Logger::RED, "DETECT PLAYER WAIT TO RESUME");
				return;
			}
		}
		GameFunctions::NetworkStreamSendEmoticon(116);
		if (!isEnable)
		{
			return;
		}
		CheckPosition();
		if (Settings::FISH_STOP_IF_INVENTORY_FULL_ENABLE)
		{
			if (GameFunctionsCustom::IsFullInventory())
			{
				Logger::Add(Logger::FISH, true, Logger::WHITE, "EQUPMENT FULL ABORT!");
				Settings::FISH_ENABLE = false;
				isEnable = false;
			}
		}
		GameFunctions::NetworkStreamSendFishingQuitPacket(3, GameFunctionsCustom::PlayerGetRotation());
		lastTimeFishing = GetTickCount();
	}

	void NewCast()
	{
		if (!isEnable)
		{
			return;
		}
		if (Settings::FISH_DETECT_PLAYER_ENABLE)
		{
			if (GameFunctionsCustom::DetectPlayer(Settings::PROTECTION_DETECT_PLAYER_WHITE_LIST))
			{

				Logger::Add(Logger::FISH, true, Logger::WHITE, "DETECT PLAYER WAIT TO RESUME");
				return;
			}
		}
#ifdef DEVELOPER_MODE
		/*if (DynamicTimer::CheckAutoSet("RefineRod", 10000))
		{
			RefineRod();
		}*/
		
#endif
		if (Settings::FISH_DROP_TRASH_ENABLE)
		{
			DropItems();
		}
		if (Settings::FISH_KILL_FISH_ENABLE)
		{
			KillFishes();
		}
		if (!UseBait())
		{
			if (Settings::FISH_BUY_BAIT_ENABLE)
			{
				BuyBait();
				if (!UseBait())
				{
					Logger::Add(Logger::FISH, true, Logger::WHITE, "NO BAITS ABORT!");
					return;
				}
			}
		}

#ifdef DEVELOPER_MODE
		D3DVECTOR oldPosition;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
		if (Settings::FISH_SHOP_CAST_TELEPORT_ENABLE)
		{	
			vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(1000, oldPosition, Settings::FISH_CAST_TELEPORT_CORDS);
			int i = 0;
			for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
			{

				GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);

				i++;
			}
		}
#endif
		if (Settings::FISH_SELL_TRASH_ENABLE && GameFunctionsCustom::InventoryEquippedPercentage() > Settings::FISH_SELL_TRASH_AFTER_PERCENTAGE)
		{
			SellItems();
		}
		Cast();
#ifdef DEVELOPER_MODE
		if (Settings::FISH_SHOP_CAST_TELEPORT_ENABLE)
		{

			vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(1000, Settings::FISH_CAST_TELEPORT_CORDS, oldPosition);
			int i = 0;
			for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
			{

				GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);

				i++;
			}
		}
#endif
	}

	bool RefineRod()
	{
		bool isNeedEquipRod = false;
		if (GameFunctionsCustom::PlayerIsRodEquipped())
		{
			if (GameFunctionsCustom::PlayerCanRefineRod()&&GameFunctions::PlayerGetItemMetinSocket(TItemPos(EQUIPMENT, 4), 0) == Settings::FISH_ROD_REFINE_POINTS[GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4))].second)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(EQUIPMENT, 4));
				isNeedEquipRod = true;
			}
			else
			{
				
			}
		}
		vector<DWORD> rodsList = GameFunctionsCustom::FindItemSlotsInInventory(27400, 27590);
		for (vector<DWORD>::iterator it = rodsList.begin(); it != rodsList.end(); ++it)
		{

			if (GameFunctions::PlayerGetItemMetinSocket(TItemPos(INVENTORY, *it), 0) == Settings::FISH_ROD_REFINE_POINTS[GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, *it))].second)
			{
				DWORD fishermanVid = GameFunctionsCustom::GetCloseObjectByVnum(9009);
				if (fishermanVid)
				{
					GameFunctions::NetworkStreamSendGiveItemPacket(fishermanVid, TItemPos(INVENTORY, *it), 1);
					GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				}
			}
		}
		if (isNeedEquipRod)
		{
			vector<DWORD> rodsList = GameFunctionsCustom::FindItemSlotsInInventory(27400, 27590);
			for (vector<DWORD>::iterator it = rodsList.begin(); it != rodsList.end(); ++it)
			{

				if (GameFunctions::PlayerGetItemMetinSocket(TItemPos(INVENTORY, *it), 0) < Settings::FISH_ROD_REFINE_POINTS[GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, *it))].second)
				{
					GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, *it));
					return true;
				}
			}
			if (rodsList.size() > 0)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, rodsList[0]));
				return true;
			}
			return false;
		}
		return true;
	}
	bool BuyBait()
	{
		DWORD fishermanVid = GameFunctionsCustom::GetCloseObjectByVnum(9009);
		if (!fishermanVid)
		{
			Logger::Add(Logger::FISH, true, Logger::WHITE, "NO FISHERMAN!");
			return false;
		}
		GameFunctions::NetworkStreamSendOnClickPacket(fishermanVid);
		GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
		for (int i = 0; i < Settings::FISH_BUY_BAIT_SHOP_COUNT; i++)
		{
			GameFunctions::NetworkStreamSendShopBuyPacket(Settings::FISH_BUY_BAIT_SHOP_SLOT - 1);
		}
		GameFunctions::NetworkStreamSendShopEndPacket();
		return true;
	}

	bool SellItems()
	{
		switch(Globals::Server)
		{
			case ServerName::KEVRA:
			{
				DWORD fishermanVid = GameFunctionsCustom::GetCloseObjectByVnum(15657);
				if (!fishermanVid)
				{
					Logger::Add(Logger::FISH, true, Logger::WHITE, "NO FISHERMAN!");
					return false;
				}
				for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_SELL_LIST.begin(); itor != Settings::FISH_SELL_LIST.end(); itor++)
				{
					if (itor->first.second)
					{
						int i = 1;
						vector<DWORD> slotList = GameFunctionsCustom::FindItemSlotsInInventory(itor->second.first);
						for (vector<DWORD>::iterator it = slotList.begin(); it != slotList.end(); ++it, i++)
						{
							DWORD slot = *it;
							GameFunctions::NetworkStreamSendGiveItemPacket(fishermanVid, TItemPos(INVENTORY, slot), 1);
							Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("SELLED %s FROM SLOT %d", itor->second.second.c_str()).c_str(), slot);
						}
					}
				}
				break;
			}
			default:
			{
				DWORD fishermanVid = GameFunctionsCustom::GetCloseObjectByVnum(9009);
				if (!fishermanVid)
				{
					Logger::Add(Logger::FISH, true, Logger::WHITE, "NO FISHERMAN!");
					return false;
				}
				GameFunctions::NetworkStreamSendOnClickPacket(fishermanVid);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
				for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_SELL_LIST.begin(); itor != Settings::FISH_SELL_LIST.end(); itor++)
				{
					if (itor->first.second)
					{
						int i = 1;
						vector<DWORD> slotList = GameFunctionsCustom::FindItemSlotsInInventory(itor->second.first);
						for (vector<DWORD>::iterator it = slotList.begin(); it != slotList.end(); ++it, i++)
						{

							GameFunctions::NetworkStreamSendShopSellPacketNew(*it, 255);
							Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("SELLED %s FROM SLOT %d", itor->second.second.c_str()).c_str(), *it);
						}
					}
				}
				GameFunctions::NetworkStreamSendShopEndPacket();
				break;
			}
		}
		return true;
	}

	void DropItems()
	{
		for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_DROP_LIST.begin(); itor != Settings::FISH_DROP_LIST.end(); itor++)
		{
			if (itor->first.second)
			{
				int i = 1;
				vector<DWORD> slotList = GameFunctionsCustom::FindItemSlotsInInventory(itor->second.first);
				for (vector<DWORD>::iterator it = slotList.begin(); it != slotList.end(); ++it, i++)
				{

					GameFunctions::NetworkStreamSendItemDropPacketNew(TItemPos(INVENTORY, *it), 0, 255);
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("DROPED %s FROM SLOT %d", itor->second.second.c_str()).c_str(), *it);
				}
			}
		}
	}

	void KillFishes()
	{
		int i = 1;
		for (map< pair<DWORD, bool>, pair<DWORD, string>>::iterator itor = Settings::FISH_KILL_FISH_LIST.begin(); itor != Settings::FISH_KILL_FISH_LIST.end(); itor++)
		{
			if (itor->first.second)
			{

				vector<DWORD> slotList = GameFunctionsCustom::FindItemSlotsInInventory(itor->second.first);
				for (vector<DWORD>::iterator it = slotList.begin(); it != slotList.end(); ++it, i++)
				{

					GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, *it));
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("KILLED %s FROM SLOT %d", itor->second.second.c_str()).c_str(), *it);
				}
			}
		}
	}

	bool UseBait()
	{
		for (map< pair<DWORD, bool>, pair<DWORD, string>> ::iterator itor = Settings::FISH_BAIT_LIST.begin(); itor != Settings::FISH_BAIT_LIST.end(); itor++)
		{
			if (itor->first.second)
			{
				int slot = GameFunctionsCustom::FindItemSlotInInventory(itor->second.first);
				if (slot != -1)
				{
					GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("USED %s FROM SLOT %d", itor->second.second.c_str()).c_str(), slot);
					return true;
				}
				else
				{
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("MISSING %s", itor->second.second.c_str()).c_str());
				}
			}
		}
		if (Settings::FISH_USE_FIRST_SLOT_ENABLE)
		{
			Logger::Add(Logger::FISH, true, Logger::WHITE, "BAIT 1 SLOT");
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, 0));
			return true;
		}
		return false;
	}

	void ParseMessage(const char* message)
	{
		if (!isEnable)
		{
			return;
		}

		switch (Globals::Server)
		{
		case ServerName::CLASSIC:
			
			if (StringExtension::Contains(message, "Prawdziwy komunikat to:"))
			{
				messageCount = 0;
				trueMessage = 0;
				if (StringExtension::Contains(message, "pierwszy"))
				{
					trueMessage = 1;
					
				}
				else if (StringExtension::Contains(message, "drugi"))
				{
					trueMessage = 2;
				}
				else if (StringExtension::Contains(message, "trzeci"))
				{
					trueMessage = 3;
				}
				
				
			}
			if (StringExtension::Contains(message, "Po prostu nawalaj w te spacje"))
			{
				
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 30);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			break;
		case ServerName::MEDIUMMT2:
			if (StringExtension::Contains(message, "Musze nacisnac "))
			{
				int num1 = atoi(message + 15);
				int num2 = atoi(message + 19);
				int sum = atoi(message + 30);
				if ((num1 + num2) == sum)
				{
					action = sum;
					Logger::Add(Logger::FISH, true, Logger::WHITE, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
				}
			}
			if (StringExtension::Contains(message, "Prawdziwy komunikat to:"))
			{
				if (StringExtension::Contains(message, "pierwszy"))
				{
					trueMessage = 1;
				}
				else if (StringExtension::Contains(message, "drugi"))
				{
					trueMessage = 2;
				}
				else if (StringExtension::Contains(message, "trzeci"))
				{
					trueMessage = 3;
				}
			}
			if (StringExtension::Contains(message, "W tej chwili kliknij "))
			{
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 21);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			if (StringExtension::Contains(message, "Wybierz przycisk spacja "))
			{
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 24);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			if (StringExtension::Contains(message, "Kliknij w spacje"))
			{
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 24);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			if (StringExtension::Contains(message, "Czyzby rybka brala"))
			{
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 24);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			if (StringExtension::Contains(message, "Masz refleks"))
			{
				messageCount++;
				if (messageCount == trueMessage)
				{
					action = atoi(message + 24);
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
					messageCount = 0;
					trueMessage = 0;
				}
			}
			break;
		default:
			for (map< DWORD, pair<string, DWORD>>::iterator itor = Settings::FISH_COMMAND_LIST.begin(); itor != Settings::FISH_COMMAND_LIST.end(); itor++)
			{
				string messageASCI = StringExtension::UTF8ToANSI((char*)itor->second.first.c_str());

				if (StringExtension::Contains(message, messageASCI))
				{

					action = itor->second.second;
					Logger::Add(Logger::FISH, true, Logger::GREEN, StringExtension::StringFormat("REQUEST CLICK COUNT %d", action).c_str());
				}
			}

			break;
		}
	}
};

