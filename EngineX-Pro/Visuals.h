#pragma once
class Visuals :public IAbstractModuleBase, public Singleton<Visuals>
{
private:
public:
	virtual void OnStart()
	{

	}

	virtual void OnStop()
	{
	}

	virtual void OnUpdate()
	{

	}

	virtual void OnRender()
	{

	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("VisualsBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::Checkbox("ON/OFF Render Scene", &Settings::PROTECTION_DISABLE_RENDER_ENABLE);
		ImGui::Checkbox("ON/OFF Update Scene", &Settings::PROTECTION_DISABLE_UPDATE_ENABLE);
		ImGui::ColorEdit4("##RenderWH", (float*)&Settings::MAIN_WH_RENDER_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Render WaitHack", &Settings::MAIN_WH_RENDER_ENABLE);
		ImGui::ColorEdit4("##RendeFarm", (float*)&Settings::RADAR_WAYPOINT_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Render FarmBot Path", &Settings::FARM_RENDER_PATH_ENABLE);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTab2()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("RadarBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::ColorEdit3("##Monsters", (float*)&Settings::RADAR_MONSTER_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Monsters", &Settings::RADAR_MONSTER_SHOW_ENABLE);
		ImGui::ColorEdit3("##Bosses", (float*)&Settings::RADAR_BOSS_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Boss", &Settings::RADAR_BOSS_SHOW_ENABLE);
		ImGui::ColorEdit3("##NPC", (float*)&Settings::RADAR_NPC_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Npc", &Settings::RADAR_NPC_SHOW_ENABLE);
		ImGui::ColorEdit3("##ZYLY", (float*)&Settings::RADAR_MINE_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Veins", &Settings::RADAR_MINING_SHOW_ENABLE);
		ImGui::ColorEdit3("##METIN", (float*)&Settings::RADAR_STONE_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Metin", &Settings::RADAR_STONE_SHOW_ENABLE);
		ImGui::ColorEdit3("##Players", (float*)&Settings::RADAR_PLAYER_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Players", &Settings::RADAR_PLAYER_SHOW_ENABLE);
		ImGui::ColorEdit3("##Waypoints", (float*)&Settings::RADAR_WAYPOINT_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Waypoints", &Settings::RADAR_WAYPOINT_SHOW_ENABLE);

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(40, "General");
		MainForm::AddTab(41, "Radar");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 40:
			OnTab1();
			break;
		case 41:
			OnTab2();
			break;
		}
	}
};