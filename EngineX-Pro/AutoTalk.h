#pragma once
class AutoTalk :public IAbstractModuleBase/*, public Singleton<AutoTalk>*/
{
private:
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

	}

	void OnTabs()
	{
		MainForm::AddTab(30, "AutoTalk");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 30:
			OnTab1();
			break;
		}
	}
};

