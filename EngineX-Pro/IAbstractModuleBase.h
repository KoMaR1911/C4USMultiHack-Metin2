#pragma once

class IAbstractModuleBase : public TAbstractSingleton<IAbstractModuleBase>
{
public:
	IAbstractModuleBase() {}
	virtual ~IAbstractModuleBase() {}

	virtual void OnStart() = 0;
	virtual void OnStop() = 0;
	virtual void OnTabs() = 0;
	virtual void OnMenu() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
};