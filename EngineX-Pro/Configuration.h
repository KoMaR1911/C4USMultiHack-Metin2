#pragma once
class Configuration :public IAbstractModuleBase, public Singleton<Configuration>
{
private:
	/*vector<string> configs;*/
	int configSelected  = 0;
	string newFileName;
	string newFileName2;
	string newFileName3;
	int currentIndex = 0;
	int currentIndex2 = 0;
	int currentIndex3 = 0;
	DWORD hotkeyTime = 500;
public:

	string str0 ="";
	void OnStart()
	{
		vector<string> configs = FileExtension::GetDirectoryFiles(FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "mc"   /*format "exe"*/);
		for (auto const& value : configs)
		{
			if (value == "Default")
			{
				Settings::Load("Default", FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
				return;
			}
		}
		Settings::Save("Default", FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
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

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("ConfBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		vector<string> configs = FileExtension::GetDirectoryFiles(FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "mc"   /*format "exe"*/);
		ImGui::PushItemWidth(200);
		if (ImGui::Combo("Configs", &currentIndex, configs))
		{
			newFileName = configs[currentIndex];
		}
		ImGui::InputText("##FileName1", &newFileName);
		if (ImGui::Button("Load Settings"))
		{
			Settings::Load(newFileName, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Settings"))
		{
			Settings::Save(newFileName, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove Settings"))
		{
			if (newFileName != "Default")
			{
				Settings::Remove(newFileName, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "mc");
			}
		}
		ImGui::Separator();
		vector<string> configs2 = FileExtension::GetDirectoryFiles(FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "ic"   /*format "exe"*/);
		ImGui::PushItemWidth(200);
		if (ImGui::Combo("Items", &currentIndex2, configs2))
		{
			newFileName2 = configs2[currentIndex2];
		}
		ImGui::InputText("##FileName2", &newFileName2);
		if (ImGui::Button("Load Item List"))
		{
			Settings::LoadItemFilter(newFileName2, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Item List"))
		{
			Settings::SaveItemFilter(newFileName2, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove Item List"))
		{
			Settings::Remove(newFileName2, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "ic");
		}
		ImGui::Separator();
		vector<string> configs3 = FileExtension::GetDirectoryFiles(FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "fc"   /*format "exe"*/);
		ImGui::PushItemWidth(200);
		if (ImGui::Combo("Paths", &currentIndex3, configs3))
		{
			newFileName3 = configs3[currentIndex3];
		}
		ImGui::InputText("##FileName3", &newFileName3);
		if (ImGui::Button("Load Paths"))
		{
			Settings::LoadFarm(newFileName3, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Paths"))
		{
			Settings::SaveFarm(newFileName3, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"));
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove Paths"))
		{
			Settings::Remove(newFileName3, FileExtension::GetAppDataDirectory() + XOR("\\EngineX\\"), "fc");
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("BindBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);

		ImGui::Hotkey(hotkeyTime, "Boost         ", &Settings::MAIN_BOOST_KEY);
		ImGui::Hotkey(hotkeyTime, "Relog         ", &Settings::MAIN_RELOG_KEY);
		ImGui::Hotkey(hotkeyTime, "MH Switch", &Settings::MAIN_GLOBAL_SWITCH_KEY);
		ImGui::Hotkey(hotkeyTime, "Hide UI      ", &Settings::MAIN_HIDE_UI_KEY);

		ImGui::PushItemWidth(100); ImGui::InputInt("Boost Distance", &Settings::MAIN_BOOST_SPEED, 5, 100);
		ImGui::InputInt("Channel Changer Port +/-", &Settings::MAIN_CHANNEL_CHANGER_PORT_OFFSET, 1, 1);

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(60, "Configuration");
		MainForm::AddTab(61, "Binds");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 60:
			OnTab1();
			break;
		case 61:
			OnTab2();
			break;
		}
	}
};
