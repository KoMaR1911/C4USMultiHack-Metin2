#pragma once
class MainCore
{
public:
	static bool DXLoaded;
	static bool isInitialized;
	static void StartCrack();
	static void Crack();
	static void NetworkThread();
	static bool CheckMembers();	
	static void Initialize();
	static void UpdateLoop();
	static void ConsoleOutput(const char* txt, ...);
	static map < pair<DWORD, DWORD>, pair<bool, shared_ptr<IAbstractModuleBase>>> moduleList;
};

map < pair<DWORD, DWORD>, pair<bool, std::shared_ptr<IAbstractModuleBase>>>  MainCore::moduleList =
{
	{ make_pair(10, 1), make_pair(true, shared_ptr<IAbstractModuleBase >(new Main()))},
	{ make_pair(14, 1), make_pair(true,shared_ptr<IAbstractModuleBase >(new Item()))},
    { make_pair(16, 1), make_pair(true, shared_ptr<IAbstractModuleBase >(new Farm()))},
	{ make_pair(17, 1), make_pair(true,shared_ptr<IAbstractModuleBase >(new Buff()))},

#ifdef FISHBOT
	{ make_pair(20, 2), make_pair(true, shared_ptr<IAbstractModuleBase >(new Fish()))},
#endif

//	{ make_pair(30, 3), make_pair(false, shared_ptr<IAbstractModuleBase >(new AutoTalk()))},
	{ make_pair(31, 3), make_pair(true, shared_ptr<IAbstractModuleBase >(new Status()))},
	{ make_pair(32, 3), make_pair(true,shared_ptr<IAbstractModuleBase >(new Inventory()))},
	{ make_pair(33, 3), make_pair(true,shared_ptr<IAbstractModuleBase >(new Spam()))},
	{ make_pair(34, 3), make_pair(true, shared_ptr<IAbstractModuleBase >(new PythonScript()))},

	{ make_pair(40, 4), make_pair(true,shared_ptr<IAbstractModuleBase >(new Visuals()))},
	{ make_pair(50, 5), make_pair(true, shared_ptr<IAbstractModuleBase >(new Protection()))},
	{ make_pair(60, 6), make_pair(true,shared_ptr<IAbstractModuleBase >(new Configuration()))},

#ifdef DEVELOPER_MODE
	//{ make_pair(70, 7), make_pair(true, shared_ptr<IAbstractModuleBase >(new Debug()))},
	{ make_pair(71, 7), make_pair(true, shared_ptr<IAbstractModuleBase >(new PacketSniffer()))},
	{ make_pair(72, 7), make_pair(true, shared_ptr<IAbstractModuleBase >(new MainDungs()))},
#endif
};
