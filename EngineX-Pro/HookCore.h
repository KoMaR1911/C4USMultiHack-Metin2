#pragma once

class Hooks
{
public:
	static Globals::tPyCallClassMemberFunc nPyCallClassMemberFunc;
	static Globals::tCNetworkStreamRecv nCNetworkStreamRecv;
	static Globals::tCNetworkStreamSend nCNetworkStreamSend;
	static Globals::tCNetworkStreamSendAeldra nCNetworkStreamSendAeldra;
	static Globals::tCPythonChatAppendChat nCPythonChatAppendChat;
	static Globals::tCInstanceBaseBlockMovement nCInstanceBaseBlockMovement;
	static Globals::tCInstanceBaseAvoidObject nCInstanceBaseAvoidObject;
	static Globals::tCActorInstanceTestActorCollision nCActorInstanceTestActorCollision;
	static Globals::tCPhysicsObjectIncreaseExternalForce nCPhysicsObjectIncreaseExternalForce;
	static Globals::tCPythonApplicationRenderGame nCPythonApplicationRenderGame;
	static Globals::tCPythonEventManagerRegisterEventSetFromString nCPythonEventManagerRegisterEventSetFromString;
	static Globals::tCResourceManagerGetResourcePointer nCResourceManagerGetResourcePointer;
	
	static PLH::VFuncMap directxVTable;
	static Globals::tDirectEndScene nDirectEndScene;
	static Globals::tDirectReset nDirectReset;
	static Globals::tCInputKeyboardUpdateKeyboard nCInputKeyboardUpdateKeyboard;
	static std::shared_ptr<PLH::HWBreakPointHook> screenToClientHwBpHook;
	typedef bool(__stdcall* tScreenToClient)(HWND hWnd, LPPOINT lpPoint);
	static bool __stdcall NewScreenToClient(HWND hWnd, LPPOINT lpPoint);

	static void _fastcall NewCPythonApplicationRenderGame(void* This, void* EDX);
	static bool _fastcall NewCActorInstanceTestActorCollision(void* This, void* EDX, DWORD* rVictim);
	static bool _fastcall NewCInstanceBaseAvoidObject(void* This, void* EDX, DWORD* c_rkBGObj);
	static void _fastcall NewCInstanceBaseBlockMovement(void* This, void* EDX);
	static bool __cdecl NewPyCallClassMemberFunc(PyObject* poClass, const char* c_szFunc, PyObject* poArgs);
	static int _fastcall NewCPythonEventManagerRegisterEventSetFromString(void* This, void* EDX, const string& strScript);
	static void _fastcall NewCPhysicsObjectIncreaseExternalForce(void* This, void* EDX, const D3DVECTOR& c_rvBasePosition, float fForce);
	static bool _fastcall NewCNetworkStreamRecv(void* This, void* EDX, int len, void* pDestBuf);
	static bool _fastcall NewCNetworkStreamSend(void* This, void* EDX, int len, void* pDestBuf);

	//static bool _fastcall NewCNetworkStreamSendAeldra(void* This, void* EDX, int len, void* pDestBuf, bool instant);
	static int _stdcall NewCNetworkStreamSendAeldra(SOCKET s, const char* pDestBuf, int len, int flags);
	static void _fastcall NewCPythonChatAppendChat(void* This, void* EDX, int iType, const char* c_szChat);
	static DWORD* _fastcall NewCResourceManagerGetResourcePointer(void* This, void* EDX, const char* c_szFileName);

	static HRESULT __stdcall NewDirectEndScene(void* This);
	static HRESULT __stdcall NewDirectReset(void* This, D3DPRESENT_PARAMETERS* ppReset);
	static void _fastcall NewCInputKeyboardUpdateKeyboard(void* This, void* EDX);
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	static void Initialize();

	static bool _fastcall NewCInstanceBaseRegisterEffect(void* This, void* EDX, UINT eEftType, const char* c_szEftAttachBone, const char* c_szEftName, bool isCache);
};

Globals::tCNetworkStreamRecv Hooks::nCNetworkStreamRecv = NULL;
Globals::tCNetworkStreamSend Hooks::nCNetworkStreamSend = NULL;
Globals::tCNetworkStreamSendAeldra Hooks::nCNetworkStreamSendAeldra = NULL;
Globals::tCPythonChatAppendChat Hooks::nCPythonChatAppendChat = NULL;
Globals::tCPhysicsObjectIncreaseExternalForce Hooks::nCPhysicsObjectIncreaseExternalForce = NULL;
Globals::tPyCallClassMemberFunc Hooks::nPyCallClassMemberFunc = NULL;
Globals::tCInstanceBaseBlockMovement Hooks::nCInstanceBaseBlockMovement = NULL;
Globals::tCInstanceBaseAvoidObject Hooks::nCInstanceBaseAvoidObject = NULL;
Globals::tCActorInstanceTestActorCollision Hooks::nCActorInstanceTestActorCollision = NULL;
Globals::tCPythonApplicationRenderGame Hooks::nCPythonApplicationRenderGame = NULL;
Globals::tCInputKeyboardUpdateKeyboard Hooks::nCInputKeyboardUpdateKeyboard = NULL;
Globals::tCPythonEventManagerRegisterEventSetFromString Hooks::nCPythonEventManagerRegisterEventSetFromString = NULL;
Globals::tCResourceManagerGetResourcePointer Hooks::nCResourceManagerGetResourcePointer = NULL;
Globals::tDirectEndScene Hooks::nDirectEndScene = NULL;
Globals::tDirectReset Hooks::nDirectReset = NULL;
