#pragma once
class MemoryExtension
{
public:
	static DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize)
	{
		DWORD dwErrorCode = 0;
		DWORD dwOldProtect = 0;
		// ----
		int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
		// ----
		if (iRes == 0)
		{
			dwErrorCode = GetLastError();
			return dwErrorCode;
		}
		// ----
		memcpy(lpBuf, lpAddress, uSize);
		// ----
		DWORD dwBYTEs = 0;
		// ----
		iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBYTEs);
		// ----
		if (iRes == 0)
		{
			dwErrorCode = GetLastError();
			return dwErrorCode;
		}
		// ----
		return 0x00;
	};
	static DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
	{
		DWORD dwErrorCode = 0;
		DWORD dwOldProtect = 0;
		// ----
		int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
		// ----
		if (iRes == 0)
		{
			dwErrorCode = GetLastError();
			return dwErrorCode;
		}
		// ----
		memcpy(lpAddress, lpBuf, uSize);
		// ----
		DWORD dwBytes = 0;
		// ----
		iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);
		// ----
		if (iRes == 0)
		{
			dwErrorCode = GetLastError();
			return dwErrorCode;
		}
		// ----
		return 0x00;
	}

	static void MemSet(DWORD Addr, int mem, int size)
	{
		DWORD OldProtect;
		VirtualProtect((LPVOID)Addr, size, PAGE_EXECUTE_READWRITE, &OldProtect);

		memset((void*)Addr, mem, size);

		VirtualProtect((LPVOID)Addr, size, OldProtect, &OldProtect);
	}

	static void SetMemory(DWORD Addr, void* mem, int size)
	{

		DWORD OldProtect;
		VirtualProtect((LPVOID)Addr, size, PAGE_EXECUTE_READWRITE, &OldProtect);

		memcpy((void*)Addr, mem, size);

		VirtualProtect((LPVOID)Addr, size, OldProtect, &OldProtect);

	}

	static void JmpHook(DWORD FuncOffset, DWORD JmpOffset)
	{
		DWORD OldProtect;
		VirtualProtect((LPVOID)JmpOffset, 4, PAGE_EXECUTE_READWRITE, &OldProtect);
		*(DWORD*)(JmpOffset) = 0xE9;
		*(DWORD*)(JmpOffset + 1) = FuncOffset - (JmpOffset + 5);
	}


	static DWORD SetByte(const LPVOID dwOffset, const BYTE btValue)
	{
		return WriteMemory(dwOffset, (LPVOID)&btValue, sizeof(BYTE));
	}
	//---------------------------------------------------------------------------

	static DWORD GetByte(const LPVOID dwOffset, BYTE& btValue)
	{
		return ReadMemory(dwOffset, (LPVOID)btValue, sizeof(BYTE));
	}
	//---------------------------------------------------------------------------

	static DWORD SetWord(const LPVOID dwOffset, const WORD wValue)
	{
		return WriteMemory(dwOffset, (LPVOID)&wValue, sizeof(WORD));
	}
	//---------------------------------------------------------------------------

	static DWORD GetWord(const LPVOID dwOffset, WORD& wValue)
	{
		return ReadMemory(dwOffset, (LPVOID)wValue, sizeof(WORD));
	}
	//---------------------------------------------------------------------------

	static DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue)
	{
		return WriteMemory(dwOffset, (LPVOID)&dwValue, sizeof(DWORD));
	}
	//---------------------------------------------------------------------------

	static DWORD GetDword(const LPVOID dwOffset, DWORD& dwValue)
	{
		return ReadMemory(dwOffset, (LPVOID)dwValue, sizeof(DWORD));
	}
	//---------------------------------------------------------------------------

	static DWORD SetFloat(const LPVOID dwOffset, float fValue)
	{
		return WriteMemory(dwOffset, &fValue, sizeof(float));
	}
	//---------------------------------------------------------------------------

	static DWORD GetFloat(const LPVOID dwOffset, float& fValue)
	{
		return ReadMemory(dwOffset, &fValue, sizeof(float));
	}
	//---------------------------------------------------------------------------

	static DWORD SetDouble(const LPVOID dwOffset, double dValue)
	{
		return WriteMemory(dwOffset, &dValue, sizeof(double));
	}
	//---------------------------------------------------------------------------

	static DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
	{
		BYTE btBuf[5];
		DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
		// ----
		btBuf[0] = 0xE9;
		memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
		// ----
		return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
	}
	//---------------------------------------------------------------------------

	static DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
	{
		BYTE btBuf[6];
		DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
		// ----
		btBuf[0] = 0x0F;
		btBuf[1] = 0x8F;
		memcpy((LPVOID)&btBuf[2], (LPVOID)&dwShift, sizeof(ULONG_PTR));
		// ----
		return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
	}
	//---------------------------------------------------------------------------

	static DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
	{
		BYTE btBuf[6];
		DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
		// ----
		btBuf[0] = 0x0F;
		btBuf[1] = 0x87;
		memcpy((LPVOID)&btBuf[2], (LPVOID)&dwShift, sizeof(ULONG_PTR));
		// ----
		return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
	}
	//---------------------------------------------------------------------------

	static DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
	{
		BYTE btBuf[5];
		DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
		// ----
		btBuf[0] = cmd;
		memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
		// ----
		return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
	}
	//---------------------------------------------------------------------------

	static DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
	{
		BYTE* lpBuf = new BYTE[wCount];
		// ----
		memset(lpBuf, btValue, wCount);
		// ----
		return WriteMemory(dwAddress, (LPVOID)lpBuf, wCount);
	}
	//---------------------------------------------------------------------------

	static DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
	{
		BYTE btBuf[5];
		// ----
		DWORD dwShift = (ULONG_PTR)dwMyFuncOffset - ((ULONG_PTR)dwJmpOffset + 5);
		// ----
		btBuf[0] = cmd;
		// ----
		memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
		// ----
		return WriteMemory(dwJmpOffset, (LPVOID)btBuf, sizeof(btBuf));
	}
	//---------------------------------------------------------------------------

	static void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
	{
		*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset - (dwJmpOffset + 5);
	}


	static bool ErasePEHeader(HMODULE hModule)
	{
		if ((DWORD)hModule == 0) return 0;
		DWORD IMAGE_NT_HEADER = *(int*)((DWORD)hModule + 60);
		for (int i = 0; i < 0x108; i++)
			*(BYTE*)(IMAGE_NT_HEADER + i) = 0;
		for (int i = 0; i < 120; i++)
			*(BYTE*)((DWORD)hModule + i) = 0;
		return 1;
	}
};

