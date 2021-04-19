


#pragma once
class Main :public IAbstractModuleBase, public Singleton<Main>
{
private:

	DWORD lastTimeRefreshItemList = 0;
	D3DVECTOR  lastPosition = D3DVECTOR{ 0, 0, 0 };
	DWORD lastTimeBackToPosition = 0;
	DWORD lastMiniMHRotation = 0;
	DWORD lastTimeAttackEnable = 0;
	DWORD lastWaitHackEnable = 0;
	DWORD lastWaitHackSkillDelay = 0;
	DWORD lastTimeUpdateIcons = 0;
	bool playerUsingHorse = false;
	bool autoReviveNeedWait = false;
	DWORD lastMiniMHMoveSpeed = 0;
	DWORD lastMiniMHAttackSpeed = 0;

	DWORD lastTimeStonesArrowShow = 0;

	DirectTexture texture_Skill_0;
	DirectTexture texture_Skill_1;
	DirectTexture texture_Skill_2;
	DirectTexture texture_Skill_3;
	DirectTexture texture_Skill_4;
	DirectTexture texture_Skill_5;
	DirectTexture texture_Skill_None;

	int chmuraCount = 50;

	void  SetJobRaceTextures(int job, int race)
	{

		texture_Skill_None = MainForm::ResourceMap["skill_none"];
		if (job == 0)
		{
			texture_Skill_0 = texture_Skill_None;
			texture_Skill_1 = texture_Skill_None;
			texture_Skill_2 = texture_Skill_None;
			texture_Skill_3 = texture_Skill_None;
			texture_Skill_4 = texture_Skill_None;
			texture_Skill_5 = texture_Skill_None;
			return;
		}
		else
		{
		}
		if (race == 0 || race == 4)
		{
			if (job == 1)
			{

				texture_Skill_0 = MainForm::ResourceMap["warrior_b_0"];
				texture_Skill_1 = MainForm::ResourceMap["warrior_b_1"];
				texture_Skill_2 = MainForm::ResourceMap["warrior_b_2"];
				texture_Skill_3 = MainForm::ResourceMap["warrior_b_3"];
				texture_Skill_4 = MainForm::ResourceMap["warrior_b_4"];
				texture_Skill_5 = MainForm::ResourceMap["warrior_b_5"];
				return;
			}
			if (job == 2)
			{

				texture_Skill_0 = MainForm::ResourceMap["warrior_m_0"];
				texture_Skill_1 = MainForm::ResourceMap["warrior_m_1"];
				texture_Skill_2 = MainForm::ResourceMap["warrior_m_2"];
				texture_Skill_3 = MainForm::ResourceMap["warrior_m_3"];
				texture_Skill_4 = MainForm::ResourceMap["warrior_m_4"];
				texture_Skill_5 = MainForm::ResourceMap["warrior_m_5"];
				return;
			}
		}

		if (race == 1 || race == 5)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::ResourceMap["ninja_d_0"];
				texture_Skill_1 = MainForm::ResourceMap["ninja_d_1"];
				texture_Skill_2 = MainForm::ResourceMap["ninja_d_2"];
				texture_Skill_3 = MainForm::ResourceMap["ninja_d_3"];
				texture_Skill_4 = MainForm::ResourceMap["ninja_d_4"];
				texture_Skill_5 = MainForm::ResourceMap["ninja_d_5"];
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::ResourceMap["ninja_a_0"];
				texture_Skill_1 = MainForm::ResourceMap["ninja_a_1"];
				texture_Skill_2 = MainForm::ResourceMap["ninja_a_2"];
				texture_Skill_3 = MainForm::ResourceMap["ninja_a_3"];
				texture_Skill_4 = MainForm::ResourceMap["ninja_a_4"];
				texture_Skill_5 = MainForm::ResourceMap["ninja_a_5"];
				return;
			}
		}

		if (race == 2 || race == 6)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::ResourceMap["sura_w_0"];
				texture_Skill_1 = MainForm::ResourceMap["sura_w_1"];
				texture_Skill_2 = MainForm::ResourceMap["sura_w_2"];
				texture_Skill_3 = MainForm::ResourceMap["sura_w_3"];
				texture_Skill_4 = MainForm::ResourceMap["sura_w_4"];
				texture_Skill_5 = MainForm::ResourceMap["sura_w_5"];
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::ResourceMap["sura_b_0"];
				texture_Skill_1 = MainForm::ResourceMap["sura_b_1"];
				texture_Skill_2 = MainForm::ResourceMap["sura_b_2"];
				texture_Skill_3 = MainForm::ResourceMap["sura_b_3"];
				texture_Skill_4 = MainForm::ResourceMap["sura_b_4"];
				texture_Skill_5 = MainForm::ResourceMap["sura_b_6"];
				return;
			}
		}

		if (race == 3 || race == 7)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::ResourceMap["shaman_d_0"];
				texture_Skill_1 = MainForm::ResourceMap["shaman_d_1"];
				texture_Skill_2 = MainForm::ResourceMap["shaman_d_2"];
				texture_Skill_3 = MainForm::ResourceMap["shaman_d_3"];
				texture_Skill_4 = MainForm::ResourceMap["shaman_d_4"];
				texture_Skill_5 = MainForm::ResourceMap["shaman_d_5"];
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::ResourceMap["shaman_h_0"];
				texture_Skill_1 = MainForm::ResourceMap["shaman_h_1"];
				texture_Skill_2 = MainForm::ResourceMap["shaman_h_2"];
				texture_Skill_3 = MainForm::ResourceMap["shaman_h_3"];
				texture_Skill_4 = MainForm::ResourceMap["shaman_h_4"];
				texture_Skill_5 = MainForm::ResourceMap["shaman_h_5"];
				return;
			}
		}
	}


public:


	void OnStart()
	{
		Settings::GLOBAL_SWITCH_ENABLE = true;
		playerUsingHorse = GameFunctionsCustom::PlayerIsMountingHorse();
		lastPosition = GameFunctionsCustom::PlayerGetPixelPosition();

	}

	void OnStop()
	{
		Settings::GLOBAL_SWITCH_ENABLE = false;
		GameFunctions::PlayerSetAttackKeyState(false);
		autoReviveNeedWait = false;
		playerUsingHorse = false;
	}

	void OnUpdate()
	{

		if (GameFunctionsCustom::PlayerIsInstance())
		{
			SetJobRaceTextures(GameFunctions::NetworkStreamGetMainActorSkillGroup(), GameFunctions::PlayerGetRace());
		}
		else
		{
			SetJobRaceTextures(0, 0);
		}
		if (Settings::MAIN_POTION_ENABLE)
		{
			Potions();
		}
		if (Settings::GLOBAL_SWITCH_ENABLE)
		{
			if (GameFunctionsCustom::PlayerIsInstance())
			{
				bool canAttack = true;
				Other();
				if (Revive())
				{
					return;
				}
				if ((GetTickCount() - lastTimeBackToPosition) > 1200 && GameFunctionsCustom::PlayerGetDistance(lastPosition) > 200 && !playerUsingHorse && Settings::MAIN_ATTACK_ENABLE)
				{
					GameFunctionsCustom::LookAtDestPixelPosition(lastPosition);
					GameFunctionsCustom::PlayerMoveToDestPixelPositionDirection(lastPosition);

					lastTimeBackToPosition = GetTickCount();
				}
				if (Settings::MAIN_MOB_DETECT_ENABLE)
				{
					canAttack = IsAttackMobDistance();
				}
				else
				{

				}

				if (Settings::MAIN_MOBBER_ENABLE)
				{

					if (DynamicTimer::CheckAutoSet("MobMagnet", 5000))
					{
						GameFunctions::NetworkStreamSendUseSkillPacket(163, 0);
					}
				}

				Skill();
				WaitHack();
#ifdef DEVELOPER_MODE
				Odpychaj();
				Przyciagaj();
#endif
				if (Settings::MAIN_ATTACK_ENABLE)
				{
					GameFunctions::PlayerSetAttackKeyState(canAttack);
				}


			}
			else
			{


			}
		}
		else
		{


		}
	}

	void OnRender()
	{
		if (Settings::MAIN_WH_RENDER_ENABLE)
		{
			D3DVECTOR mainPos;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &mainPos);
			CRender::Circle3D(mainPos.x, mainPos.y, Settings::MAIN_WH_DISTANCE_VALUE, 60.0f, Settings::MAIN_WH_RENDER_COLOR);
		}
	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("AtakBorder", ImVec2(ImGui::GetWindowWidth() - 10, 120), true);
		if (ImGui::Checkbox("Auto Attack    ", &Settings::MAIN_ATTACK_ENABLE))
		{
			lastPosition = GameFunctionsCustom::PlayerGetPixelPosition();
		}
		else
		{
			GameFunctions::PlayerSetAttackKeyState(false);
		}
		ImGui::SameLine();
		ImGui::Checkbox("Mob Detect", &Settings::MAIN_MOB_DETECT_ENABLE);
		ImGui::Checkbox("Rotation", &Settings::MAIN_ROTATION_ENABLE);
		ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::SliderInt("Rotation Frequency", &Settings::MAIN_ROTATION_SPEED_VALUE, 1, 100);
		ImGui::Checkbox("Auto Revive", &Settings::MAIN_AUTO_REVIVE_ENABLE); ImGui::SameLine();
		ImGui::SliderInt("Resume Attack After HP %", &Settings::MAIN_AUTO_REVIVE_PERCENTAGE_VALUE, 1, 100);
		ImGui::EndChild();
		ImGui::PopStyleVar(); /*ImGui::SameLine();*/

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("OtherBorder", ImVec2(ImGui::GetWindowWidth() - 10, 180), true);
		ImGui::Checkbox("Wallhack Mob", &Settings::MAIN_WALL_MOB_ENABLE); ImGui::SameLine();
		ImGui::Checkbox("Wallhack Object", &Settings::MAIN_WALL_OBJECT_ENABLE); ImGui::SameLine();
		ImGui::Checkbox("Wallhack Terrain", &Settings::MAIN_WALL_TERRAIN_ENABLE);
		ImGui::Checkbox("Enemy AntiFly", &Settings::MAIN_NOK_ENABLE); ImGui::SameLine();
		ImGui::Checkbox("Player AntiFly", &Settings::MAIN_NOP_ENABLE);
		ImGui::Checkbox("Detect Stones", &Settings::MAIN_STONE_DETECT_ENABLE);
		switch (Globals::Server)
		{
		case ServerName::MEDIUMMT2:
			ImGui::Checkbox("Medium Mobber", &Settings::MAIN_MOBBER_ENABLE);
			break;
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("WHBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("WaitHack", &Settings::MAIN_WH_ENABLE);
		ImGui::RadioButton("Standard", &Settings::MAIN_WH_ATTACK_TYPE, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Target", &Settings::MAIN_WH_ATTACK_TYPE, 1);
#ifdef DEVELOPER_MODE
		ImGui::SameLine();
		ImGui::RadioButton("Standard+", &Settings::MAIN_WH_ATTACK_TYPE, 2);
#endif
		ImGui::PushItemWidth(100); ImGui::InputInt("Time(ms)", &Settings::MAIN_WH_TIME, 5, 100);
		ImGui::Checkbox("Range", &Settings::MAIN_WAITHACK_RANGE_ENABLE); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputInt("Attack Distance", &Settings::MAIN_WH_DISTANCE_VALUE, 100, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputInt("Teleport Step", &Settings::MAIN_WH_DISTANCE_STEP, 100, 1000);
		ImGui::RadioButton("Sword", &Settings::MAIN_WH_WEAPON_TYPE, 0); ImGui::SameLine();
		ImGui::RadioButton("Bow", &Settings::MAIN_WH_WEAPON_TYPE, 1);

		ImGui::Text("Applies to");
		ImGui::Checkbox("Monster", &Settings::MAIN_WH_MONSTER); ImGui::SameLine();
		ImGui::Checkbox("Metin", &Settings::MAIN_WH_METIN); ImGui::SameLine();
		ImGui::Checkbox("Boss", &Settings::MAIN_WH_BOSS); ImGui::SameLine();
		ImGui::Checkbox("Player", &Settings::MAIN_WH_PLAYER);

#ifdef DEVELOPER_MODE
		ImGui::RadioButton("Skill", &Settings::MAIN_WH_WEAPON_TYPE, 2); ImGui::SameLine();
		ImGui::InputInt("Chmura Multipler", &chmuraCount, 0, 0);
		ImGui::InputInt("Skill Number", &Settings::MAIN_WH_SKILL_VALUE, 1, 111); ImGui::SameLine();
		ImGui::InputInt("Skill Time", &Settings::MAIN_WH_SKILL_COOLDOWN_TIME, 1, 10);
		ImGui::Checkbox("Odpychanie", &Odpychanie); ImGui::SameLine();
		ImGui::InputInt("Odpychanie Time", &odpychanieTime);
		ImGui::Checkbox("Przyciaganie", &Przyciaganie); ImGui::SameLine();
		ImGui::InputInt("Przyciaganie Time", &przyciaganieTime);
		ImGui::InputInt("Animation", &Animation);
		ImGui::InputInt("Attach Range", &range);
		ImGui::InputInt("ExternalForce Range", &range2);
#endif	
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab3()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("MHUsager", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("HP Potion           ", &Settings::MAIN_RED_POTION_ENABLE);
		ImGui::PushItemWidth(100); ImGui::SliderInt("Speed(ms)##1", &Settings::MAIN_RED_POTION_SPEED_VALUE, 1, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::SliderInt("Below % HP", &Settings::MAIN_RED_POTION_PERCENTAGE_VALUE, 1, 100);
		ImGui::Separator();
		ImGui::Checkbox("MP Potion           ", &Settings::MAIN_BLUE_POTION_ENABLE);
		ImGui::PushItemWidth(100); ImGui::SliderInt("Speed(ms)##2", &Settings::MAIN_BLUE_POTION_SPEED_VALUE, 1, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::SliderInt("Below % MP", &Settings::MAIN_BLUE_POTION_PERCENTAGE_VALUE, 1, 100);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab4()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("SkillsBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::IconButton2(&Settings::MAIN_SKILL_1_ENABLE, "Skill 1", texture_Skill_0, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_2_ENABLE, "Skill 2", texture_Skill_1, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_3_ENABLE, "Skill 3", texture_Skill_2, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_4_ENABLE, "Skill 4", texture_Skill_3, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_5_ENABLE, "Skill 5", texture_Skill_4, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_6_ENABLE, "Skill 6", texture_Skill_5, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(10, "General");
		MainForm::AddTab(11, "WaitHack");
		MainForm::AddTab(12, "Potions");
		MainForm::AddTab(13, "Skills");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 10:
			OnTab1();
			break;
		case 11:
			OnTab2();
			break;
		case 12:
			OnTab3();
			break;
		case 13:
			OnTab4();
			break;
		}
	}

private:
	bool Revive()
	{
		if (!Settings::MAIN_AUTO_REVIVE_ENABLE)
		{
			autoReviveNeedWait = false;
			return false;
		}
		if (GameFunctionsCustom::PlayerIsDead())
		{
			if (DynamicTimer::CheckAutoSet("Revive", 1000))
			{
				GameFunctionsCustom::PlayerRevive();
				autoReviveNeedWait = true;
				GameFunctions::PlayerSetAttackKeyState(false);
			}
			return true;
		}

		else if (GameFunctionsCustom::GetHpProcentageStatus() < Settings::MAIN_AUTO_REVIVE_PERCENTAGE_VALUE && autoReviveNeedWait)
		{
			return true;
		}
		else if (GameFunctionsCustom::GetHpProcentageStatus() > Settings::MAIN_AUTO_REVIVE_PERCENTAGE_VALUE&& autoReviveNeedWait)
		{
			if (playerUsingHorse)
			{
				GameFunctionsCustom::MountHorse();
			}
			autoReviveNeedWait = false;
			return false;
		}
		else
		{
			return false;
		}
	}
	bool IsAttackMobDistance()
	{
		if (((GetTickCount() - lastTimeAttackEnable) > 500))
		{

			if (GameFunctionsCustom::GetObjectListCount(OBJECT_MOB, 300) == 0)
			{

				return false;
			}
			else
			{
				return true;
			}



			lastTimeAttackEnable = GetTickCount();
		}

		else
		{
			return false;
		}


	}

	void Skill()
	{

		if (Settings::MAIN_SKILL_1_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(1) && !GameFunctions::PlayerIsSkillCoolTime(1))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 1);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 1);
				}
			}

		}
		if (Settings::MAIN_SKILL_2_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(2) && !GameFunctions::PlayerIsSkillCoolTime(2))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 2);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 2);
				}
			}

		}
		if (Settings::MAIN_SKILL_3_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(3) && !GameFunctions::PlayerIsSkillCoolTime(3))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 3);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 3);
				}
			}

		}
		if (Settings::MAIN_SKILL_4_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(4) && !GameFunctions::PlayerIsSkillCoolTime(4))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 4);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 4);
				}
			}

		}
		if (Settings::MAIN_SKILL_5_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(5) && !GameFunctions::PlayerIsSkillCoolTime(5))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 5);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 5);
				}
			}

		}
		if (Settings::MAIN_SKILL_6_ENABLE)
		{
			if (!GameFunctions::PlayerIsSkillActive(6) && !GameFunctions::PlayerIsSkillCoolTime(6))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 6);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 6);
				}
			}

		}
	}

	bool WHCanAttack(int targetType, bool isBoss)
	{
		bool canAttack = false;
		if (targetType == TYPE_ENEMY && !isBoss && Settings::MAIN_WH_MONSTER)
		{
			canAttack = true;
		}
		if (targetType == TYPE_ENEMY && isBoss && Settings::MAIN_WH_BOSS)
		{
			canAttack = true;
		}
		if (targetType == TYPE_STONE && Settings::MAIN_WH_METIN)
		{
			canAttack = true;
		}
		if (targetType == TYPE_PC && Settings::MAIN_WH_PLAYER)
		{
			canAttack = true;
		}
		return canAttack;
	}

	void SwordWH()
	{
		D3DVECTOR oldPosition;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, Settings::MAIN_WH_DISTANCE_VALUE);
		for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
		{
			DWORD vid = itor->first;
			DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
			bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
			if (WHCanAttack(type, isBoss) == false)
			{
				continue;
			}
			GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
			GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
			if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
			{
				vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, oldPosition, newPosition);
				int i = 0;
				for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
				{			
					GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);				
					i++;
				}
			}
			
			GameFunctionsCustom::NetworkStreamSendAttackPacket(0, vid);

			if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
			{
				vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, newPosition, oldPosition);
				int i = 0;
				for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
				{				
					GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);		
					i++;
				}
			}
		}
	}

	void BowWH()
	{
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, Settings::MAIN_WH_DISTANCE_VALUE);
		for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
		{
			DWORD vid = itor->first;
			DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
			bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
			if (WHCanAttack(type, isBoss) == false)
			{
				continue;
			}
			GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
			GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
			
		}
		if (objectList.size())
		{
			GameFunctions::NetworkStreamSendShootPacket(0);
		}

	}
public:
	void ResetSkillTimer()
	{
		lastWaitHackSkillDelay = 0;
	}
private:
#ifdef DEVELOPER_MODE
	void SkillWH()
	{
		D3DVECTOR oldPosition;
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, Settings::MAIN_WH_DISTANCE_VALUE);
		if (objectList.size() > 0)
		{
			for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
			{
				DWORD vid = itor->first;
				DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
				bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
				if (WHCanAttack(type, isBoss) == false)
				{
					continue;
				}
				if ((GetTickCount() - Main::lastWaitHackSkillDelay) > Settings::MAIN_WH_SKILL_COOLDOWN_TIME * 1000)
				{
					GameFunctions::NetworkStreamSendUseSkillPacket(Settings::MAIN_WH_SKILL_VALUE, vid);
					Main::lastWaitHackSkillDelay = GetTickCount();
				}
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
				GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
				if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
				{
					vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, oldPosition, newPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						i++;
					}
				}
				GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
				if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
				{
					GameFunctions::NetworkStreamSendShootPacket(Settings::MAIN_WH_SKILL_VALUE);
					vector< D3DVECTOR> distanceSteps = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, newPosition, oldPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = distanceSteps.begin(); it != distanceSteps.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						i++;
					}
				}

			}
			if (!Settings::MAIN_WAITHACK_RANGE_ENABLE)
			{
				GameFunctions::NetworkStreamSendShootPacket(Settings::MAIN_WH_SKILL_VALUE);
			}
		}
	}

	//chmurka tak bardzo przez was poszukiwana - obejscie limitera na wiekszosci serwerwo

	void SkillWHx50()
	{
		D3DVECTOR oldPosition;
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, Settings::MAIN_WH_DISTANCE_VALUE);
		if (objectList.size() > 0)
		{
			for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
			{
				DWORD vid = itor->first;
				DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
				bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
				if (WHCanAttack(type, isBoss) == false)
				{
					continue;
				}
				if ((GetTickCount() - Main::lastWaitHackSkillDelay) > Settings::MAIN_WH_SKILL_COOLDOWN_TIME * 1000)
				{
					GameFunctions::NetworkStreamSendUseSkillPacket(Settings::MAIN_WH_SKILL_VALUE, vid);
					Main::lastWaitHackSkillDelay = GetTickCount();
				}
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
				GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);

				if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
				{
					vector< D3DVECTOR> distanceSteps = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, oldPosition, newPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = distanceSteps.begin(); it != distanceSteps.end(); ++it)
					{				
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						i++;
					}
				}
				if (type == TYPE_ENEMY && !GameFunctionsCustom::InstanceIsBoss(itor->second))
				{
					GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
					GameFunctions::NetworkStreamSendShootPacket(Settings::MAIN_WH_SKILL_VALUE);
				}
				else 
				{
					for (int i = 0; i < chmuraCount; i++)
					{
						GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ 0,0,0 });
						GameFunctions::NetworkStreamSendShootPacket(Settings::MAIN_WH_SKILL_VALUE);
					}
				}
				if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
				{
					vector< D3DVECTOR> distanceSteps = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, newPosition, oldPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = distanceSteps.begin(); it != distanceSteps.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						i++;
					}
				}

			}
		}
	}
#endif
	void Target()
	{
		DWORD vid = GameFunctions::PlayerGetTargetVID();
		if (vid == 0)
		{
			return;
		}
		D3DVECTOR oldPosition;
		D3DVECTOR newPosition;
		DWORD* targetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		DWORD targetType = GameFunctions::InstanceBaseGetInstanceType(targetInstance);
		bool isBoss = GameFunctionsCustom::InstanceIsBoss(targetInstance);
		GameFunctions::InstanceBaseNEW_GetPixelPosition(targetInstance, &newPosition);
		if (targetInstance != 0)
		{
			if (WHCanAttack(targetType, isBoss) == false)
			{
				return;
			}
			if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 0, 0, 0);
			}
			switch (Settings::MAIN_WH_WEAPON_TYPE)
			{
			case 0:
				GameFunctionsCustom::NetworkStreamSendAttackPacket(0, vid);
				break;
			case 1:
				GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
				GameFunctions::NetworkStreamSendShootPacket(0);
				break;

#ifdef DEVELOPER_MODE
			case 2:
				if ((GetTickCount() - Main::lastWaitHackSkillDelay) > (Settings::MAIN_WH_SKILL_COOLDOWN_TIME * 1000))
				{
					GameFunctions::NetworkStreamSendUseSkillPacket(Settings::MAIN_WH_SKILL_VALUE, vid);
					Main::lastWaitHackSkillDelay = GetTickCount();
				}
				for (int i = 0; i < 50; i++) {
					GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ 0,0,0 });
					GameFunctions::NetworkStreamSendShootPacket(Settings::MAIN_WH_SKILL_VALUE);
				}
				break;
#endif
			}
			if (Settings::MAIN_WAITHACK_RANGE_ENABLE)
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(oldPosition, 0, 0, 0);
			}
		}
	}


	void WaitHack()
	{
		if (((GetTickCount() - lastWaitHackEnable) > Settings::MAIN_WH_TIME) && Settings::MAIN_WH_ENABLE)
		{

			if (Settings::MAIN_WH_DETECT_PLAYER_ENABLE && GameFunctionsCustom::DetectPlayer(Settings::PROTECTION_DETECT_PLAYER_WHITE_LIST))
			{
				return;
			}
			if (Settings::MAIN_WH_ATTACK_TYPE == 1)
			{
				Target();
			}
			else if(Settings::MAIN_WH_ATTACK_TYPE == 0)
			{
				switch (Settings::MAIN_WH_WEAPON_TYPE)
				{
				case 0:
					SwordWH();
					break;
				case 1:
					BowWH();
					break;
#ifdef DEVELOPER_MODE
				case 2:
					SkillWH();
					break;
#endif
				}
			}
#ifdef DEVELOPER_MODE
			else if (Settings::MAIN_WH_WEAPON_TYPE == 2)
			{
				SkillWHx50();
			}
#endif
			lastWaitHackEnable = GetTickCount();
		}
	}


#ifdef DEVELOPER_MODE
	bool Odpychanie = false;
	bool Przyciaganie = false;
	int odpychanieTime = 500;
	int przyciaganieTime = 500;
	int lastOdpychanie = 0;
	int lastPrzyciaganie = 0;

	int Funkcja = 3;
	int Animation = 17;
	int range = 2000;
	int range2 = 2000;

	void Odpychaj()
	{
		if ((GetTickCount() - Main::lastOdpychanie) > Main::odpychanieTime && Odpychanie)
		{
			Main::lastOdpychanie = GetTickCount();
			D3DVECTOR charPosition;
			D3DVECTOR mobPosition;
			map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, range);
			if (objectList.size() > 0)
			{
				for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
				{
					DWORD vid = itor->first;
					DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
					bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
					if (WHCanAttack(type, isBoss) == false)
					{
						continue;
					}
					GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &charPosition);
					GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &mobPosition);

					//tp to mob
					/*vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, charPosition, mobPosition);
					for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
					}*/

					//attach
					D3DVECTOR newPosition{ charPosition.x, charPosition.y, charPosition.z };
					newPosition.x += range2;
					newPosition.y -= range2;
					GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 0, Funkcja, Animation);
					GameFunctions::NetworkStreamSendSyncPositionPacket(vid, newPosition.x, newPosition.y);
					GameFunctions::InstanceBaseSCRIPT_SetPixelPosition(itor->second, newPosition.x, newPosition.y);
					//tp back
					/*vector< D3DVECTOR> distanceSteps = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, mobPosition, charPosition);
					for (vector< D3DVECTOR>::iterator it = distanceSteps.begin(); it != distanceSteps.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
					}*/
				}
			}
		}
	}

	void Przyciagaj()
	{
		if ((GetTickCount() - Main::lastPrzyciaganie) > Main::przyciaganieTime && Przyciaganie)
		{
			Main::lastPrzyciaganie = GetTickCount();
			D3DVECTOR charPosition;
			D3DVECTOR mobPosition;
			map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE | OBJECT_PC, range);
			if (objectList.size() > 0)
			{
				for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
				{
					DWORD vid = itor->first;
					DWORD type = GameFunctions::InstanceBaseGetInstanceType(itor->second);
					bool isBoss = GameFunctionsCustom::InstanceIsBoss(itor->second);
					if (WHCanAttack(type, isBoss) == false)
					{
						continue;
					}
					GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &charPosition);
					GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &mobPosition);

					//tp to mob
					/*vector< D3DVECTOR> distancePoints = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, charPosition, mobPosition);
					for (vector< D3DVECTOR>::iterator it = distancePoints.begin(); it != distancePoints.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
					}*/

					//attach
					GameFunctions::NetworkStreamSendCharacterStatePacket(mobPosition, 0, Funkcja, Animation);
					GameFunctions::NetworkStreamSendSyncPositionPacket(vid, charPosition.x, charPosition.y);
					GameFunctions::InstanceBaseSCRIPT_SetPixelPosition(itor->second, charPosition.x, charPosition.y);

					//tp back
					/*vector< D3DVECTOR> distanceSteps = MiscExtension::DivideTwoPointsByDistance(Settings::MAIN_WH_DISTANCE_STEP, mobPosition, charPosition);
					for (vector< D3DVECTOR>::iterator it = distanceSteps.begin(); it != distanceSteps.end(); ++it)
					{
						GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
					}*/
				}
			}
		}
	}
#endif

	void Other()
	{
		if (Settings::MAIN_NOP_ENABLE)
		{
			switch (Globals::Server)
			{
				case ServerName::AELDRA:
				{
					GameFunctions::InstanceBase__SetAffect(GameFunctions::PlayerNEW_GetMainActorPtr(), 40, true);
					break;
				}
			
				default:
				{
					GameFunctions::InstanceBase__SetAffect(GameFunctions::PlayerNEW_GetMainActorPtr(), 16, true);
					break;
				}
			}		
		}

		if (((GetTickCount() - lastMiniMHRotation) > (MiscExtension::RandomInt(500, 8000))) && Settings::MAIN_ROTATION_ENABLE)
		{
			if (MiscExtension::RandomInt(0, 100) < Settings::MAIN_ROTATION_SPEED_VALUE)
			{

				
				GameFunctions::InstanceSetRotation(GameFunctions::PlayerNEW_GetMainActorPtr(), MiscExtension::RandomInt(0, 360));



			}
			lastMiniMHRotation = GetTickCount();
		}
		if ((GetTickCount() - lastTimeStonesArrowShow) > 4000 && Settings::MAIN_STONE_DETECT_ENABLE)
		{
			DWORD vid = GameFunctionsCustom::GetCloseObject(OBJECT_STONE);
			if (vid > 0)
			{
				GameFunctionsCustom::PlayerShowTargetArrow(vid, 3);

				lastTimeStonesArrowShow = GetTickCount();
			}

		}

	}

	void MPPotion() 
	{
		int slot = GameFunctionsCustom::FindItemSlotInInventory(27004);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27005);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27006);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		if (Globals::Server == ServerName::METINPL)
		{
			slot = GameFunctionsCustom::FindItemSlotInInventory(27008);
			if (slot != -1)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
				return;
			}
			slot = GameFunctionsCustom::FindItemSlotInInventory(27052);
			if (slot != -1)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
				return;
			}
		}
	}

	void Potions()
	{
		if (Settings::MAIN_RED_POTION_ENABLE)
		{
			if (GameFunctionsCustom::GetHpProcentageStatus() < Settings::MAIN_RED_POTION_PERCENTAGE_VALUE)
			{
				if (DynamicTimer::CheckAutoSet("HPPotion", Settings::MAIN_RED_POTION_SPEED_VALUE))
				{
					HPPotion();
				}

			}
		}
		if (Settings::MAIN_BLUE_POTION_ENABLE)
		{
			if (GameFunctionsCustom::GetMpProcentageStatus() < Settings::MAIN_BLUE_POTION_PERCENTAGE_VALUE)
			{
				if (DynamicTimer::CheckAutoSet("MPPotion", Settings::MAIN_BLUE_POTION_SPEED_VALUE))
				{
					MPPotion();
				}
			}
		}
	}

	void HPPotion() 
	{
		int slot = GameFunctionsCustom::FindItemSlotInInventory(27001);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27002);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27003);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		if (Globals::Server == ServerName::METINPL)
		{
			slot = GameFunctionsCustom::FindItemSlotInInventory(27007);
			if (slot != -1)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
				return;
			}
			slot = GameFunctionsCustom::FindItemSlotInInventory(27051);
			if (slot != -1)
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
				return;
			}
		}
	}
};

