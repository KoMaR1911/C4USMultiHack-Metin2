#include "stdafx.h"
#include "CheckHook.h"
//#include "C:\Program Files\VMProtect Lite\Include\C\VMProtectSDK.h"

extern "C" __declspec(dllexport) int dsf75sddc5s4d65c(void) {
	return true;
}

void ErrorTranslator(unsigned int exceptionCode, PEXCEPTION_POINTERS exceptionRecord)
{
	switch (exceptionRecord->ExceptionRecord->ExceptionCode)
	{
		case EXCEPTION_ACCESS_VIOLATION:
			{
				break;
			}
		default:
			{
				throw "1";
			}
	}
}

VEHHook sleepHook;
void __stdcall NewSleep(DWORD miliseconds)
{
	Hooks::screenToClientHwBpHook = std::make_shared<PLH::HWBreakPointHook>((char*)&ScreenToClient, (char*)&Hooks::NewScreenToClient, GetCurrentThread());
	Hooks::screenToClientHwBpHook->hook();
	//Security::Initialize();
	sleepHook.Unhook();
}
void threadHookCheck()
{
	auto bypassXd = LI_FN(GetProcAddress)(LI_FN(GetModuleHandleA)(XOR("ntdll.dll")), XOR("LdrInitializeThunk"));

	if (!bypassXd == NULL)
	{
		printf("offset: %i\n", bypassXd);
		while (true)
		{

			if (FindHookDestination(bypassXd) == NULL)
			{

				printf(XOR("hook LdrInitializeThunk not exist\n"));
				
			}
			else {
				printf(XOR("hook LdrInitializeThunk exist\n"));
				
				
				
			}
		}
	}
}

void Initialize()
{
	while (!MainCore::isInitialized)
	{
		MainCore::Initialize();
	}
}

LPVOID LM_CreateFakeThread(LPVOID Thread)
{
	DWORD ThreadAdresi = 0x40000/*your fake adress xD*/;
	DWORD Old;
	VirtualProtect((LPVOID)ThreadAdresi, 0x100, PAGE_EXECUTE_READWRITE, &Old);
	CONTEXT ctx;
	HANDLE tHand = CreateRemoteThread(GetCurrentProcess(), 0, 0, (LPTHREAD_START_ROUTINE)ThreadAdresi, 0, 0, 0);
	SuspendThread(tHand);
	ctx.ContextFlags = CONTEXT_INTEGER;
	GetThreadContext(tHand, &ctx);
	ctx.Eax = (DWORD)Thread;
	ctx.ContextFlags = CONTEXT_INTEGER;
	SetThreadContext(tHand, &ctx);
	ResumeThread(tHand);
	return (LPVOID)ctx.Eax;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		
		case DLL_PROCESS_ATTACH:
			{
			//HANDLE xd = NULL;

		//	LM_CreateFakeThread(xd);

			DisableThreadLibraryCalls(hModule);
#ifdef DEVELOPER_MODE
				if (Globals::Server != ServerName::AELDRA)
				{
#ifdef _DEBUG
					_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
					//AllocConsole();
					//freopen(XOR("CONOUT$"), "w", stdout);
				}
#endif
			//	HANDLE xd = ProcessExtension::CreateThreadSafe((LPTHREAD_START_ROUTINE)&threadHookCheck, hModule);
				_set_se_translator(ErrorTranslator);
		
				Globals::hModule = hModule;
				MainCore::StartCrack();
				


				/*HANDLE hThread = nullptr;
				NTSTATUS ret = SYSCALL(0xBB, 11, &hThread, THREAD_ALL_ACCESS, 0, (HANDLE)-1, (LPTHREAD_START_ROUTINE)&Initialize, 0, 0, 0, 0, 0, 0);
				if (ret != 0 || hThread == nullptr)
				{
					MessageBoxA(0, "error!", 0, 0);
				}
				CloseHandle(hThread);*/

				HANDLE hThreadInit = ProcessExtension::CreateThreadSafe((LPTHREAD_START_ROUTINE)&Initialize, hModule);
				if (hThreadInit)
				{

					CloseHandle(hThreadInit);
				}

				//HANDLE hThread = nullptr;
				//NTSTATUS ret = SYSCALL(0xBB, 11, &hThread, THREAD_ALL_ACCESS, 0, (HANDLE)-1, (LPTHREAD_START_ROUTINE)&Initialize, 0, 0, 0, 0, 0, 0);
				//if (ret != 0 || hThread == nullptr)
				//{
				//	MessageBoxA(0, "error!", 0, 0);
				//}
				//CloseHandle(hThread);
	
				if (Globals::Server == ServerName::METINPL)
				{

					HANDLE hThreadInit = ProcessExtension::CreateThreadSafe((LPTHREAD_START_ROUTINE)&Initialize, hModule);
		
					if (hThreadInit)
					{
				
						CloseHandle(hThreadInit);
					}
				}
				else
				{
					//sleepHook.Hook((uintptr_t)Sleep, (uintptr_t)NewSleep);
				}
			}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			{

			}
		case DLL_PROCESS_DETACH:

			break;
	}
	return TRUE;

}