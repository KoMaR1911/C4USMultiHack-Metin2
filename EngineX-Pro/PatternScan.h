#pragma once
#include <dbghelp.h>
#include <stdio.h>
#pragma comment(lib, "dbghelp.lib")
class PatternScan
{
public:

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getBYTE( x )    (getBits(x[0]) << 4 | getBits(x[1]))

	static DWORD FindPattern(const char* pPattern)
	{
		DWORD xd = NULL;
		DWORD xdA = NULL;
		DWORD xdB = NULL;
		HMODULE hMod = GetModuleHandleA(NULL);
		if (hMod)
		{
			PIMAGE_NT_HEADERS NtHeader = ImageNtHeader(hMod);
			WORD NumSections = NtHeader->FileHeader.NumberOfSections;
			PIMAGE_SECTION_HEADER Section = IMAGE_FIRST_SECTION(NtHeader);
			for (WORD i = 0; i < 1; i++)
			{
			//	printf("%-8s\t%x\t%x\t%x\n", Section->Name, Section->VirtualAddress,
				//	Section->PointerToRawData, Section->SizeOfRawData);
				DWORD xd = Section->VirtualAddress;
				DWORD xdA = Section->PointerToRawData;
				DWORD xdB = Section->SizeOfRawData;

				Section++;
			}
		}
		HMODULE handle = GetModuleHandle(NULL);
		PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(handle);
		PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS((LONG)handle + pDsHeader->e_lfanew);
		PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
		DWORD base = xd;
		DWORD size = xdB;

		unsigned int count = 0;
		return	PatternScan::Search(base, size, (unsigned char*)pPattern, count);
	}

	static DWORD FindPatternGlobal(const char* pPattern, DWORD base, DWORD size)
	{
		unsigned int count = 0;
		return	PatternScan::Search(base, size, (unsigned char*)pPattern, count);
	}

	static DWORD FindPattern2(std::string moduleName, std::string pattern)
	{
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo; 
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getBYTE(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;    //one ?
			}
			else
			{
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}
		return NULL;
	}

	static DWORD Search(DWORD base, DWORD size, unsigned char* pattern, unsigned int& instances)
	{

		unsigned char* code = (unsigned char*)base;
		int patternLength = strlen((char*)pattern);

		if (pattern[0] == ' ')
			return NULL;



		for (unsigned int i(0); i < size; i++)
		{
			for (int j(0), k(0); j < patternLength && (i + k < size); k++)
			{
				unsigned char tempChar[3];
				memset(tempChar, 0, sizeof(tempChar));

				if (pattern[j] == (unsigned char)'?')
				{
					j += 2;
					continue;
				}

				sprintf((char*)tempChar, "%02X", code[(i + k)]);

				if (tempChar[0] != pattern[j] ||
					tempChar[1] != pattern[j + 1])
					break;

				j += 3;

				if (j > (patternLength - 2))
				{
					DWORD pointerLoc = (base + i + 1);

					instances++;

					--pointerLoc;


					return pointerLoc;
				}
			}
		}

		return NULL;
	}
	
};

