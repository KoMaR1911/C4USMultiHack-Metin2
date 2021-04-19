#pragma once
class Protection :public IAbstractModuleBase, public Singleton<Protection>
{
private:
	
	string lastPlayerName="";
	bool isShowLogs = false;
public:
	void OnStart()
	{

	}
	void OnStop()
	{

	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("ProtectionBorder", ImVec2(ImGui::GetWindowWidth() - 10, 310), true);;
		ImGui::Checkbox("Whisper Logs", &Settings::PROTECTION_SHOW_WHISPER_LOGS_ENABLE);
		ImGui::Checkbox("Whisper Balloon", &Settings::PROTECTION_SHOW_WHISPER_BALLOON_ENABLE);
		ImGui::Checkbox("Whisper Beep", &Settings::PROTECTION_PLAY_WHISPER_BEEP_ENABLE);
		ImGui::Checkbox("Whisper Restore Window", &Settings::PROTECTION_RESTORE_WISPER_WINDOW_ENABLE);
		ImGui::Checkbox("Whisper Window Flash", &Settings::PROTECTION_FLASH_WHISPER_ICON_ENABLE);


		ImGui::Checkbox("Normal Logs", &Settings::PROTECTION_SHOW_TALK_LOGS_ENABLE);
		ImGui::Checkbox("Normal Balloon", &Settings::PROTECTION_SHOW_TALK_BALLOON_ENABLE);
		ImGui::Checkbox("Normal Beep", &Settings::PROTECTION_PLAY_TALK_BEEP_ENABLE);
		ImGui::Checkbox("Normal Window Flash", &Settings::PROTECTION_FLASH_TALK_ICON_ENABLE);

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("DetectorBorder", ImVec2(ImGui::GetWindowWidth() - 10, 310), true);;
		ImGui::Checkbox("Detect Player WaitHack", &Settings::MAIN_WH_DETECT_PLAYER_ENABLE);
#ifdef FISHBOT
		ImGui::Checkbox("Detect Player FishBot", &Settings::FISH_DETECT_PLAYER_ENABLE);
#endif
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(50, "Protection");
		MainForm::AddTab(51, "Detector");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 50:
			OnTab1();
			break;
		case 51:
			OnTab2();
			break;
		}
	}

	void OnRender()
	{
	}

	void OnUpdate()
	{
		if (Globals::Server == ServerName::METINPL)
		{
			if (Settings::PROTECTION_AUTO_LOGIN_ENABLE && DynamicTimer::CheckAutoSet("AutoLogin", 7000))
			{
				if (GameFunctionsCustom::PlayerDirectEnter())
				{
					Main::Instance().ResetSkillTimer();
				}
			}
		}
		else 
		{
			if (DynamicTimer::CheckAutoSet("AutoLogin", 3000) && Settings::PROTECTION_AUTO_LOGIN_ENABLE)
			{
				if (GameFunctionsCustom::PlayerDirectEnter())
				{
					Main::Instance().ResetSkillTimer();
				}
			}
		}
	}
};