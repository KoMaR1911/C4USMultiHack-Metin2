#pragma once
class PythonScript :public IAbstractModuleBase, public Singleton<PythonScript>
{
private:
	string pythonBuffer = string(15000, '\0');;

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

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("PythonBorder", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		ImGui::InputTextMultiline("##Code", &pythonBuffer[0], pythonBuffer.size(), ImVec2(ImGui::GetWindowWidth() - 40, ImGui::GetWindowHeight() - 80));
		if (ImGui::Button("Execute"))
		{
			Globals::PyRun_SimpleStringFlags(pythonBuffer.c_str(), 0);
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		//if (Globals::Server == ServerName::METINPL)
		//{
			MainForm::AddTab(34, "PythonScript");
	//	}
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 34:
			OnTab1();
			break;
		}
	}
};