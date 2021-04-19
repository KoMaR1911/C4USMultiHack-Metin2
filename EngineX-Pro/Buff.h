
#pragma once
class Buff : public IAbstractModuleBase, public Singleton<Buff>
{

	class TargetBuff
	{

	public:
		TargetBuff(string targetName, DWORD  targetVid)
		{
			this->targetName = targetName;
			this->targetVid = targetVid;
		}
		DWORD lastTimeBuff_1 = 0;
		DWORD lastTimeBuff_2 = 0;
		DWORD lastTimeBuff_3 = 0;
		string targetName = "";
		DWORD targetVid = 0;
		bool guiLineIsSelected = false;
	};



private:
	map<DWORD , std::shared_ptr<TargetBuff>> targetList;
	
	DWORD selectedTargetLine=0;
	
	DirectTexture textureSkill_1;
	DirectTexture textureSkill_2;
	DirectTexture textureSkill_3;


	void  SetJobRaceTextures(int job, int race)
	{
		if (!GameFunctionsCustom::PlayerIsInstance())
		{
			job = 0;
			race = 0;
		}
		if (job == 0)
		{
			textureSkill_1 = MainForm::ResourceMap["skill_none"];
			textureSkill_2 = MainForm::ResourceMap["skill_none"];
			textureSkill_3 = MainForm::ResourceMap["skill_none"];
			return;
		}
		else
		{

		}
		if (race == 0 || race == 4)
		{
			if (job == 1)
			{

				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];
			}
		}

		if (race == 1 || race == 5)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];
			}
		}

		if (race == 2 || race == 6)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];

			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::ResourceMap["skill_none"];
				textureSkill_2 = MainForm::ResourceMap["skill_none"];
				textureSkill_3 = MainForm::ResourceMap["skill_none"];
			}
		}

		if (race == 3 || race == 7)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::ResourceMap["shaman_d_3"];
				textureSkill_2 = MainForm::ResourceMap["shaman_d_4"];
				textureSkill_3 = MainForm::ResourceMap["shaman_d_5"];
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::ResourceMap["shaman_h_3"];
				textureSkill_2 = MainForm::ResourceMap["shaman_h_4"];
				textureSkill_3 = MainForm::ResourceMap["shaman_h_5"];
			}
		}
	}

public:
	virtual void OnStart()
	{
		
		
	}


	virtual void OnStop()
	{
		
	}

	virtual void OnUpdate()
	{
		/*if(GameFunctionsCustom::PlayerIsInstance())
		{ }*/
		SetJobRaceTextures(GameFunctions::NetworkStreamGetMainActorSkillGroup(), GameFunctions::PlayerGetRace());
		if (Settings::BUFF_ENABLE)
		{
			if (!GameFunctions::NetworkStreamGetMainActorSkillGroup())
			{
				return;
			}
			if (GameFunctions::PlayerGetRace() == 3 || GameFunctions::PlayerGetRace() == 7)
			{
				
			}
			else
			{
				return;
			}
			if (Settings::BUFF_ENABLE)
			{
				if(DynamicTimer::CheckAutoSet("Skill", 500))
				{
					if (Settings::BUFF_SKILL_1_ENABLE)
					{
						if (DynamicTimer::Check("BuffBotSkill1Time", Settings::BUFF_SKILL_1_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if ((GetTickCount() - itor->second.get()->lastTimeBuff_1) > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(4);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill1Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
					}
					if (Settings::BUFF_SKILL_2_ENABLE)
					{
						if (DynamicTimer::Check("BuffBotSkill2Time", Settings::BUFF_SKILL_2_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (GetTickCount() - itor->second.get()->lastTimeBuff_2 > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(5);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill2Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
					}
					if (Settings::BUFF_SKILL_3_ENABLE)
					{
						if (DynamicTimer::Check("BuffBotSkill3Time", Settings::BUFF_SKILL_3_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (GetTickCount() - itor->second.get()->lastTimeBuff_3 > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(6);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill3Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
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
		ImGui::BeginChild("BuffSkillsBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("Buff Enable", &Settings::BUFF_ENABLE);
		if (ImGui::BeginTable("##table1", 3))
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::IconButton2(&Settings::BUFF_SKILL_1_ENABLE, "Skill 1", textureSkill_1, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
			ImGui::SameLine();
			ImGui::PushItemWidth(100);  ImGui::InputFloat("##Skill1Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);
			ImGui::TableSetColumnIndex(1);
			ImGui::IconButton2(&Settings::BUFF_SKILL_2_ENABLE, "Skill 2", textureSkill_2, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
			ImGui::SameLine();
			ImGui::PushItemWidth(100);  ImGui::InputFloat("##Skill2Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);
			ImGui::TableSetColumnIndex(2);
			ImGui::IconButton2(&Settings::BUFF_SKILL_3_ENABLE, "Skill 3", textureSkill_3, MainForm::ResourceMap["skill_on"], MainForm::ResourceMap["skill_off"], ImVec2(32, 32));
			ImGui::SameLine();
			ImGui::PushItemWidth(100);  ImGui::InputFloat("##Skill3Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);
			ImGui::EndTable();
		}

		ImGui::BeginChild("BuffTargetList", ImVec2(190, 200), true);
		for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
		{

			if (ImGui::Selectable(itor->second.get()->targetName.c_str(), itor->second.get()->guiLineIsSelected))
			{
				selectedTargetLine = itor->first;
			}
			else
			{

			}
			if (itor->first == selectedTargetLine)
			{
				itor->second.get()->guiLineIsSelected = true;
			}
			else
			{
				itor->second.get()->guiLineIsSelected = false;
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();
		if (ImGui::Button("Add"))
		{
			if (!Settings::BUFF_ENABLE)
			{
				DWORD targetVID = GameFunctions::PlayerGetTargetVID();
				if (targetVID)
				{
					int  targetType = GameFunctionsCustom::InstanceGetInstanceTypeByVID(targetVID);
					if (targetType == TYPE_PC)
					{
						string targetName = GameFunctionsCustom::InstanceGetNameStringByVID(GameFunctions::PlayerGetTargetVID());
						if (targetName != GameFunctionsCustom::PlayerGetNameString())
						{
							bool isExistInMap = false;
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (itor->second.get()->targetName == targetName)
								{
									isExistInMap = true;
								}

							}
							if (!isExistInMap)
							{
								DWORD emptyLastKey = 0;

								for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
								{

									emptyLastKey = itor->first;
								}
								emptyLastKey++;


								targetList.insert(std::make_pair(emptyLastKey, shared_ptr<TargetBuff >(new TargetBuff(targetName, targetVID))));
							}
						}
					}
				}
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			if (!Settings::BUFF_ENABLE)
			{
				DWORD key = 0;
				for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
				{
					if (itor->second.get()->guiLineIsSelected)
					{

						key = itor->first;
					}

				}
				targetList.erase(key);
			}

		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(17, "Buff");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 17:
			OnTab1();
			break;
		}
	}
};
