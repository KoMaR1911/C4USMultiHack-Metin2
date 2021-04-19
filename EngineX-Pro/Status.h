#pragma once
class Status :public IAbstractModuleBase, public Singleton<Status>
{
	 DWORD lastTimeCheckStatus = 0;
	
	 string stringPlayerName ="";
	 string stringPlayerID = "";
	 string stringPlayerPositionX = "";
	 string stringPlayerPositionY = "";
	 string stringPlayerPositionZ = "";
	 string stringTargetIndex = "";
	 string stringTargetRank = "";
	 string stringTargetVnum = "";
	 string stringTargetDistance = "";
	 string stringTargetType = "";
	 string stringTargetName = "";
	 string stringPlayersCount = "";
	 string stringNpcCount = "";
	 string stringMetinCount = "";
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
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("StatusBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Status Enable", &Settings::STATUS_ENABLE);


		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Player Name");
		ImGui::SameLine();

		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayerName.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Position X Y:");

		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayerPositionX.c_str());
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "/");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayerPositionY.c_str());
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "/");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayerPositionZ.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "VID Player:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayerID.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "VID Target:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetIndex.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "VNUM Target:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetVnum.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "VNUM Rank:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetRank.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Target Distance:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetDistance.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Target Type:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetType.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Target Name:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringTargetName.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Players Viewport:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringPlayersCount.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "NPC Viewport:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringNpcCount.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Stones Viewport:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), stringMetinCount.c_str());

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(31, "Status");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 31:
			OnTab1();
			break;
		}
	}

	void OnUpdate()
	{


		if (Settings::STATUS_ENABLE)
		{

			if (!GameFunctionsCustom::PlayerIsInstance() || (GetTickCount() - lastTimeCheckStatus) < 1000)
			{
				return;
			}
			else
			{
				lastTimeCheckStatus = GetTickCount();
			}
			const char* playerName = GameFunctionsCustom::PlayerGetName();
			int playerIndex = GameFunctions::PlayerGetMainCharacterIndex();
			int targetIndex = GameFunctions::PlayerGetTargetVID();
			int targetVnum = 0;
			if (targetIndex != NULL) {
				targetVnum = GameFunctions::InstanceBaseGetVirtualNumber(GameFunctions::CharacterManagerGetInstancePtr(targetIndex));
			}
			int bRank = GameFunctionsCustom::GetObjectRank(targetVnum);
			int targetType = GameFunctionsCustom::InstanceGetInstanceTypeByVID(targetIndex);
			const char* targetName = GameFunctionsCustom::InstanceGetNameByVID(targetIndex);
			float distance = GameFunctionsCustom::PlayerGetCharacterDistance(targetIndex);
			int hpPercent = GameFunctionsCustom::GetHpProcentageStatus();
			int mpPercent = GameFunctionsCustom::GetMpProcentageStatus();


			int NPCViewportCount = GameFunctionsCustom::GetObjectListCount(OBJECT_NPC);
			int PlayersViewportCount = GameFunctionsCustom::GetObjectListCount(OBJECT_PC);
			int StonesViewportCount = GameFunctionsCustom::GetObjectListCount(OBJECT_STONE);




			D3DVECTOR playerPosition = GameFunctionsCustom::PlayerGetPixelPosition();

			int playerIsAlive = !GameFunctionsCustom::PlayerIsDead();
			int playerIsMouting = GameFunctionsCustom::PlayerIsMountingHorse();
			if (playerName != NULL)
			{
				stringPlayerName = string(playerName);
			}
			else
			{
				stringPlayerName = "-/-";
			}
			if (playerPosition.x != 0 && playerPosition.y != 0)
			{
				stringPlayerPositionX = to_string(playerPosition.x);
				stringPlayerPositionY = to_string(playerPosition.y);
				stringPlayerPositionZ = to_string(playerPosition.z);
			}
			else
			{
				stringPlayerPositionX = "-";
				stringPlayerPositionY = "-";
				stringPlayerPositionZ = "-";
			}

			if (targetIndex != 0)
			{
				stringTargetIndex = to_string(targetIndex);
			}
			else
			{
				stringTargetIndex = "-/-";
			}

			if (targetVnum != 0)
			{
				stringTargetVnum = to_string(targetVnum);
			}
			else
			{
				stringTargetVnum = "-/-";
			}

			if (bRank != 0)
			{
				stringTargetRank = to_string(bRank);
			}
			else
			{
				stringTargetRank = "-/-";
			}

			if (playerIndex != 0)
			{
				stringPlayerID = to_string(playerIndex);
			}
			else
			{
				stringPlayerID = "-/-";
			}

			if (distance != -1)
			{
				stringTargetDistance = to_string(distance);
			}
			else
			{
				stringTargetDistance = "-/-";
			}

			if (targetType == -1)
			{
				stringTargetType = "-/-";
			}
			else if (targetType == 0)
			{
				stringTargetType = "MOB";
			}
			else if (targetType == 1)
			{
				stringTargetType = "NPC";
			}
			else if (targetType == 2)
			{
				stringTargetType = "METIN";
			}
			else if (targetType == 6)
			{
				stringTargetType = "GRACZ";
			}
			else
			{
				stringTargetType = to_string(targetType);
			}


			if (targetName != NULL)
			{
				stringTargetName = targetName;
			}
			else
			{
				stringTargetName = "-/-";
			}
			if (hpPercent != 0)
			{

			}
			if (mpPercent != 0)
			{

			}
			if (NPCViewportCount > 0)
			{
				stringNpcCount = to_string(NPCViewportCount);
			}
			else
			{
				stringNpcCount = "-/-";
			}
			if (PlayersViewportCount > 0)
			{
				stringPlayersCount = to_string(PlayersViewportCount);
			}
			else
			{
				stringPlayersCount = "-/-";
			}
			if (StonesViewportCount > 0)
			{
				stringMetinCount = to_string(StonesViewportCount);
			}
			else
			{
				stringMetinCount = "-/-";
			}
			if (playerIsAlive != -1)
			{

			}
			if (playerIsMouting != -1)
			{

			}

			

		}

	}

};


