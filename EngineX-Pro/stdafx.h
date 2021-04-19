#include <winsock2.h>
#define _WINSOCK2API_
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <shlobj.h>
#include <direct.h>
#include <vector>
#include "strsafe.h"
#include <map>
#include <stdarg.h>
#include "resource.h"
#include <iomanip>
#include <intrin.h>       
#include <iphlpapi.h>   
#include <mutex>
#include <WinInet.h>
#include <chrono>
#include <thread>
#include <functional>
#include <psapi.h>
#include <regex>
#include <winver.h>
#include <codecvt>
#include <unordered_map>
#include <filesystem>
#pragma comment(lib, "detours.lib")
#include "detours.h"
#include "lazy_importer.hpp"
using namespace std;


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Wininet")

#ifdef _DEBUG
#define DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include "VMProtectSDK.h"
#define DecryptS VMProtectDecryptStringA
#ifdef DEBUG_WAS_DEFINED
#define _DEBUG
#endif

NTSTATUS SYSCALL(DWORD syscall_id, DWORD parameterCount, ...)
{//not for plebs :)
	
}

enum ServerName
{
	METINPL = 1,
	MEDIUMMT2,
	VIDGAR,
	PANGEA,
	SAMIAS2,
	BARIA,
	VALIUM,
	SG2,
	VEDNAR,
	AELDRA,
	ORIGINS2,
	CALLIOPE2,
	ASENIS,
	CLASSIC,
	DEVERIA,
	DRAGON,
	NEVILLA,
	DRAGON2,
	LUNA,
	TASTRIA2,
	WOM,
	ARATHAR,
	EGORIA,
	GLEVIA,
	KEVRA,
	TAMIDIA2021,
	ANORIA2,
	G22,
	CarolineMT2,
	Ernidia
};
//############################################################################
//############################################################################
//############################################################################


//#define DX9
SOCKET socketAeldra;
ServerName SERVER = ServerName::Ernidia;
#define VERSION_ELITE
//#define VERSION_PUBLIC
//#define VERSION_PREMIUM

#ifdef _DEBUG
#define DEVELOPER_MODE
#endif


//#define FISHBOT

//#define NETWORK_MODE

//#define PYTHON_ENABLE


//############################################################################
//############################################################################
//############################################################################
#if defined(PYTHON_ENABLE)
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#pragma comment(lib,"python27.lib")
#define _DEBUG
#else
#include <Python.h>
#pragma comment(lib,"python27.lib")
#endif
#else
typedef unsigned long       PyObject;
typedef unsigned long       PyMethodDef;
typedef int                 Py_ssize_t;
#endif

#define DLL_VERSION "0.1.05 Beta"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_stdlib.h"
#ifdef DX9
#include "ImGui/imgui_impl_dx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#define DirectDevice IDirect3DDevice9*
#define DirectDevice2 LPDIRECT3DDEVICE9
#define DirectTexture LPDIRECT3DTEXTURE9
#define IMGUI_DEFINE_MATH_OPERATORS
#else
#include "ImGui/imgui_impl_dx8.h"
#include <d3d8.h>
#include <d3dx8.h>
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#define DirectDevice IDirect3DDevice8*
#define DirectDevice2 LPDIRECT3DDEVICE8
#define DirectTexture LPDIRECT3DTEXTURE8
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "DynamicTimer.h"


#include "StopWatch.h"
#include "DelayActions.h"


#include "StdV80-110.h"
#include "Defines.h"



#include "TAbstractSingleton.h"
#include "Singleton.h"

#include "PythonExtension.h"
#include "MiscExtension.h"
#include "CryptExtension.h"

#include "MathExtension.h"
#include "MemoryExtension.h"
#include "StringExtension.h"
#include "FileExtension.h"
#include "ProtectExtension.h"
#include "ProcessExtension.h"
#include "PatternScan.h"
//


#include "Json.h"
#include "Device.h"
#include "Globals.h"
#include "Settings.h"
#include "CustomWidgets.h"
#include "CRender.h"
#include"SplashScreen.h"
#include "Logger.h"
#include "popinsmedium.h"
#include "fontawesome.h"
#include "IconsFontAwesome5.h"
#include "MainForm.h"
#include "SimpleIni.h"


//NETWORK
#include "Packet.h"
#include "Network.h"
#include "PacketHandler.h"

#include "GameFunctions.h"
#include "GameFunctionsCustom.h"



#include "IAbstractModuleBase.h"

#include "Main.h"
#include "Protection.h"
#include "PacketSniffer.h"
#include "Fish.h"

#include "Buff.h"
#include "Item.h"
#include "Farm.h"
#include "Status.h"
#include "Spam.h"
#include "AutoTalk.h"
#include "PythonScript.h"
#include "Inventory.h"
#include "MainDungs.h"

#include "Debug.h"
#include "Visuals.h"
#include "Configuration.h"
//Hook Systems
#include "polyhook2/PE/IatHook.hpp"
#include "polyhook2/Virtuals/VFuncSwapHook.hpp"
#include "polyhook2/Virtuals/VTableSwapHook.hpp"
#include "polyhook2/Exceptions/HWBreakPointHook.hpp"
#include "VEH.hpp"
//
#include "HookCore.h"
#include "MainCore.h"
#include "Security.h"
