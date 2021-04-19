#pragma once
class Security
{
	typedef enum _SECTION_INHERIT {
		ViewShare = 1,
		ViewUnmap = 2
	} SECTION_INHERIT;
private:
	//ntdll
	typedef NTSTATUS(__stdcall* tNtAllocateVirtualMemory)(HANDLE ProcessHandle,PVOID* BaseAddress,ULONG_PTR ZeroBits,PSIZE_T RegionSize,ULONG AllocationType,ULONG Protect);
	typedef NTSTATUS(__stdcall* tNtFreeVirtualMemory)(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG FreeType);
	typedef NTSTATUS(__stdcall* tNtMapViewOfSection)(HANDLE SectionHandle, HANDLE ProcessHandle, PVOID* BaseAddress, ULONG_PTR ZeroBits, SIZE_T CommitSize, PLARGE_INTEGER SectionOffset, PSIZE_T ViewSize, SECTION_INHERIT InheritDisposition, ULONG AllocationType, ULONG Win32Protect);
	typedef NTSTATUS(__stdcall* tNtUnmapViewOfSection)(HANDLE ProcessHandle, PVOID BaseAddress);
	static tNtAllocateVirtualMemory nNtAllocateVirtualMemory;
	static tNtFreeVirtualMemory nNtFreeVirtualMemory;
	static tNtMapViewOfSection nNtMapViewOfSection;
	static tNtUnmapViewOfSection nNtUnmapViewOfSection;
	//user32
	typedef LRESULT(__stdcall* tCallNextHookEx)(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);
	static tCallNextHookEx nCallNextHookEx;
	//kernel32
	typedef BOOL(__stdcall* tGetThreadContext)(HANDLE hThread, LPCONTEXT lpContext);
	static tGetThreadContext nGetThreadContext;
	//other
	typedef HANDLE(__stdcall* tCreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, __drv_aliasesMem LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
	typedef HMODULE(__stdcall* tLoadLibraryA)(LPCSTR lpLibFileName);
	typedef BOOL(__stdcall* tIsDebuggerPresent)();
	static tCreateThread nCreateThread;
	static tLoadLibraryA nLoadLibraryA;
	static tIsDebuggerPresent nIsDebuggerPresent;

	typedef PyObject* (__cdecl* tPy_InitModule4)(const char* name, PyMethodDef* methods, const char* doc, PyObject* self, int apiver);
	static tPy_InitModule4 nPy_InitModule4;

public:

	static HMODULE _stdcall NewLoadLibraryA(LPCTSTR lpLibFileName) {
		return nLoadLibraryA(lpLibFileName);
	}

	static PyObject* _cdecl NewPy_InitModule4(const char* name, PyMethodDef* methods, const char* doc, PyObject* self, int apiver)
	{
#if defined(PYTHON_ENABLE)
		string import_name = PythonExtension::CheckImportNames(name, methods);
		if (import_name != "zipimport")
		{
			if (methods != NULL)
			{
				for (int i = 0;; i++)
				{
					if (methods[i].ml_name == NULL)
					{
						break;
					}
					string add = "" + import_name + methods[i].ml_name;
					PythonExtension::ModulesMap.insert(map< string, DWORD>::value_type((add), (DWORD)methods[i].ml_meth));
				}
			}
		}
#endif
		return nPy_InitModule4(name, methods, doc, self, apiver);
	}

	static BOOL _stdcall NewGetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
	{
		lpContext->Dr0 = 0;
		lpContext->Dr1 = 0;
		lpContext->Dr2 = 0;
		lpContext->Dr3 = 0;
		lpContext->Dr6 = 0;
		lpContext->Dr7 = 0;
		return nGetThreadContext(hThread, lpContext);
	}

	static BOOL _stdcall NewIsDebuggerPresent() {
		return false;
	}
	static void Initialize()
	{
		//HMODULE kernel32Library = GetModuleHandleA("kernel32.dll");
		//LPVOID GetThreadContextAddr = GetProcAddress(kernel32Library, "GetThreadContext");
		//nGetThreadContext = (tGetThreadContext)DetourFunction((PBYTE)GetThreadContextAddr, (PBYTE)NewGetThreadContext);
		//LPVOID IsDebuggerPresentAddr = GetProcAddress(kernel32Library, "IsDebuggerPresent");
		//nIsDebuggerPresent = (tIsDebuggerPresent)DetourFunction((PBYTE)IsDebuggerPresentAddr, (PBYTE)NewIsDebuggerPresent);
		/*HMODULE user32Library = LoadLibraryA("user32");
		HMODULE kernel32Library = LoadLibraryA("kernel32");

		LPVOID LoadLibraryAddr = GetProcAddress(kernel32Library, "LoadLibraryA");
		nLoadLibraryA = (tLoadLibraryA)DetourFunction((PBYTE)LoadLibraryAddr, (PBYTE)NewLoadLibraryA);
		VirtualProtect(LoadLibraryAddr, 5, PAGE_EXECUTE_READ, NULL);
#ifdef PYTHON_ENABLE
		tPy_InitModule4 Py_InitModule4 = (tPy_InitModule4)GetProcAddress(LoadLibraryA("python27"), "Py_InitModule4");
		if (Py_InitModule4 == NULL)
		{
			Py_InitModule4 = (tPy_InitModule4)GetProcAddress(LoadLibraryA("python22"), "Py_InitModule4");
		}
		if (Py_InitModule4 == NULL)
		{
			DWORD pInitModule4 = PatternScan::FindPattern("55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 FC E8 ? ? ? ? 85 C0");
			Py_InitModule4 = (tPy_InitModule4)(pInitModule4);
		}
		if (Py_InitModule4 == NULL)
		{
			DWORD pInitModule4 = PatternScan::FindPattern("55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 ? 8B 45 ? 53 8B 5D ? 89 85 ? ? ? ? 8B 45 ? 56 8B 75");
			Py_InitModule4 = (tPy_InitModule4)(pInitModule4);
		}
		if (Py_InitModule4 == NULL)
		{
			DWORD pInitModule4 = PatternScan::FindPattern("55 8B EC 83 E4 F8 81 EC ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 8B 45 10 53 8B 5D 0C");
			Py_InitModule4 = (tPy_InitModule4)(pInitModule4);
		}
		if (Py_InitModule4 == NULL)
		{
			DWORD pInitModule4 = PatternScan::FindPattern("55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 ? 8B 45 ? 8B 4D ? 53 8B 5D ? 57");
			Py_InitModule4 = (tPy_InitModule4)(pInitModule4);
		}
		nPy_InitModule4 = (tPy_InitModule4)DetourFunction((PBYTE)Py_InitModule4, (PBYTE)NewPy_InitModule4);
#endif
		*/
	}
};

Security::tNtAllocateVirtualMemory Security::nNtAllocateVirtualMemory = NULL;
Security::tNtFreeVirtualMemory Security::nNtFreeVirtualMemory = NULL;
Security::tNtMapViewOfSection Security::nNtMapViewOfSection = NULL;
Security::tNtUnmapViewOfSection Security::nNtUnmapViewOfSection = NULL;
Security::tCallNextHookEx Security::nCallNextHookEx = NULL;
Security::tGetThreadContext Security::nGetThreadContext = NULL;
Security::tCreateThread Security::nCreateThread = NULL;
Security::tLoadLibraryA Security::nLoadLibraryA = NULL;
Security::tIsDebuggerPresent Security::nIsDebuggerPresent = NULL;
Security::tPy_InitModule4 Security::nPy_InitModule4 = NULL;