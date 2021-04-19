#include "stdafx.h"
#include "HookCore.h"

//##################################################################################################################################################
void _fastcall Hooks::NewCPythonApplicationRenderGame(void* This, void* EDX)
{
	if (!Settings::PROTECTION_DISABLE_RENDER_ENABLE)
	{
		Device::pDevice->GetTransform(D3DTS_WORLD, &CRender::WorldStateCopy);
		nCPythonApplicationRenderGame(This);
		for (map< pair<DWORD, DWORD>, pair<bool, std::shared_ptr<IAbstractModuleBase>>> ::iterator itor = MainCore::moduleList.begin(); itor != MainCore::moduleList.end(); itor++)
		{
			if (itor->second.first)
			{
				itor->second.second->OnRender();
			}
		}
	}
	else {
		Device::pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff000000, 1.0f, 0);
	}
}

//##################################################################################################################################################
bool _fastcall Hooks::NewCActorInstanceTestActorCollision(void* This, void* EDX, DWORD* rVictim)
{

	if (Settings::MAIN_WALL_MOB_ENABLE )
	{
		return false;
	}
	else
	{
		return nCActorInstanceTestActorCollision(This, rVictim);
	}
}

//##################################################################################################################################################
bool _fastcall Hooks::NewCInstanceBaseAvoidObject(void* This, void* EDX, DWORD* c_rkBGObj)
{

	if (Settings::MAIN_WALL_OBJECT_ENABLE)
	{
		return false;
	}
	else
	{
		return nCInstanceBaseAvoidObject(This, c_rkBGObj);
	}
}

//##################################################################################################################################################
void _fastcall Hooks::NewCInstanceBaseBlockMovement(void* This, void* EDX)
{

	if (Settings::MAIN_WALL_TERRAIN_ENABLE)
	{
		return;
	}
	else
	{
		return nCInstanceBaseBlockMovement(This);
	}
}

//##################################################################################################
void _fastcall Hooks::NewCPhysicsObjectIncreaseExternalForce(void* This, void* EDX, const D3DVECTOR& c_rvBasePosition, float fForce)
{
	if (!Settings::MAIN_NOK_ENABLE)
	{

		nCPhysicsObjectIncreaseExternalForce(This, c_rvBasePosition, fForce);
	}
	else
	{

	}
	return;
}


//##################################################################################################
bool __cdecl Hooks::NewPyCallClassMemberFunc(PyObject* poClass, const char* c_szFunc, PyObject* poArgs)

{
	if (StringExtension::Equals(c_szFunc, "Update") ||
		StringExtension::Equals(c_szFunc, "OnRender") ||
		StringExtension::Equals(c_szFunc, "DownEvent") ||

		StringExtension::Equals(c_szFunc, "Render") ||
		StringExtension::Equals(c_szFunc, "OnMouseOverIn") ||
		StringExtension::Equals(c_szFunc, "OnMouseOverOut") ||
		StringExtension::Equals(c_szFunc, "ShowToolTip") ||
		StringExtension::Equals(c_szFunc, "HideToolTip") ||
		StringExtension::Equals(c_szFunc, "OnEndFrame") ||
		StringExtension::Equals(c_szFunc, "OnKeyFrame")
		)
	{

		return nPyCallClassMemberFunc(poClass, c_szFunc, poArgs);
	}

	if (StringExtension::Equals(c_szFunc, "SetLoginPhase"))
	{

	}
	if (StringExtension::Equals(c_szFunc, "RefreshStatus"))
	{
		if (Globals::m_apoPhaseWndGame == NULL)
		{
			Globals::m_apoPhaseWndGame = poClass;
		}
	}
	/*	if (StringExtension::Equals(c_szFunc, "SetLoadingPhase") && Settings::ProtectionShowWisperLogs)
		{
			return true;
		}
	if (StringExtension::Equals(c_szFunc, "LoadData")&&Settings::ProtectionShowWisperLogs)
	{
		__SetProgress(0)

		return true;
	}*/
	if (StringExtension::Equals(c_szFunc, "BINARY_ServerCommand_Run"))
	{

		const char* com = Globals::PyString_AsString(Globals::PyTuple_GetItem(poArgs, 0));

		Logger::Add(Logger::MAIN, true, Logger::WHITE, com);
	}
	if (StringExtension::Equals(c_szFunc, "OnRecvWhisper"))
	{
		try {
			int type = Globals::PyInt_AsLong(Globals::PyTuple_GetItem(poArgs, 0));
			const char* name = Globals::PyString_AsString(Globals::PyTuple_GetItem(poArgs, 1));
			const char* line = Globals::PyString_AsString(Globals::PyTuple_GetItem(poArgs, 2));
		}
		catch (...)
		{
			//printf("wrong \n");
		}

		if (Settings::PROTECTION_SHOW_WHISPER_LOGS_ENABLE)
		{
		//	Logger::Add(Logger::MAIN, true, Logger::WHITE, line);		
		}
		if (Settings::PROTECTION_SHOW_WHISPER_BALLOON_ENABLE)
		{
			string title = StringExtension::StringFormat("Whisper[%s]", GameFunctionsCustom::PlayerGetName());
			//MiscExtension::UpdateBalloon(Globals::mainHwnd, title.c_str(), line, NULL);
		}
		if (Settings::PROTECTION_PLAY_WHISPER_BEEP_ENABLE)
		{
			//HANDLE hThread = nullptr;
			//NTSTATUS ret = SYSCALL(0xBB, 11, &hThread, THREAD_ALL_ACCESS, 0, (HANDLE)-1, (LPTHREAD_START_ROUTINE)MiscExtension::PlayAlerSound, 0, 0, 0, 0, 0, 0);
			//if (ret != 0 || hThread == nullptr)
			//{
			//	MessageBox(0, "error!2", 0, 0);
			//}
			//CloseHandle(hThread);
			CreateThread(0, NULL, (LPTHREAD_START_ROUTINE)MiscExtension::PlayAlerSound, NULL, NULL, NULL);
		}
		if (Settings::PROTECTION_RESTORE_WISPER_WINDOW_ENABLE)
		{
			ShowWindow(Globals::mainHwnd, SW_RESTORE);
		}
		if (Settings::PROTECTION_FLASH_WHISPER_ICON_ENABLE)
		{
			FLASHWINFO fi;
			fi.cbSize = sizeof(FLASHWINFO);
			fi.hwnd = Globals::mainHwnd;
			fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;;
			fi.uCount = 3;
			fi.dwTimeout = 0;
			FlashWindowEx(&fi);
		}
	}
	return nPyCallClassMemberFunc(poClass, c_szFunc, poArgs);
}

int _fastcall Hooks::NewCPythonEventManagerRegisterEventSetFromString(void* This, void* EDX, const string& strScript)
{
	const char* str_base = strScript.c_str();
	switch (Globals::Server)
	{
		case ServerName::METINPL:
			{
				if (Settings::FISH_ENABLE)
				{
					if (StringExtension::Contains(strScript.c_str(), "[QUESTION 1;Uszlachetnienie|2;"))
					{
						cout << "Passed" << endl;
						return -1;
					}
					if (StringExtension::Contains(strScript.c_str(), "[COLOR256 r;255|g;230|b;186]Rybak:[COLOR256 r;196|g;196|b;196][ENTER]Czy chcesz"))
					{
						cout << "Passed" << endl;
						return -1;
					}
					if (StringExtension::Contains(strScript.c_str(), "Ryba[ENTER]niemrawo szarpie na haczyku. Co chcesz z n"))
					{
						cout << "Pokroic huja" << endl;
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
						return -1;
					}
					if (StringExtension::Contains(strScript.c_str(), "[COLOR256 r;255|g;230|b;186]Rybak:[COLOR256 r;196|g;196|b;196][ENTER]Hej, uda"))
					{
						cout << "Passed" << endl;
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						return -1;
					}
					cout << strScript << endl;
				}		
			}
			break;
		case ServerName::SAMIAS2:
			if (StringExtension::Contains(strScript.c_str(), "Kontrola obecności"))
			{
				if (StringExtension::Contains(strScript.c_str(), "Wybierz cyfrę '1'"))
				{
					if (StringExtension::Contains(strScript.c_str(), "1;1"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
					}
					if (StringExtension::Contains(strScript.c_str(), "2;1"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(2);
					}
					if (StringExtension::Contains(strScript.c_str(), "3;1"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(3);
					}
					if (StringExtension::Contains(strScript.c_str(), "4;1"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(4);
					}
				}
				if (StringExtension::Contains(strScript.c_str(), "Wybierz cyfrę '2'"))
				{
					if (StringExtension::Contains(strScript.c_str(), "1;2"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
					}
					if (StringExtension::Contains(strScript.c_str(), "2;2"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(2);
					}
					if (StringExtension::Contains(strScript.c_str(), "3;2"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(3);
					}
					if (StringExtension::Contains(strScript.c_str(), "4;2"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(4);
					}
				}
				if (StringExtension::Contains(strScript.c_str(), "Wybierz cyfrę '3'"))
				{
					if (StringExtension::Contains(strScript.c_str(), "1;3"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
					}
					if (StringExtension::Contains(strScript.c_str(), "2;3"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(2);
					}
					if (StringExtension::Contains(strScript.c_str(), "3;3"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(3);
					}
					if (StringExtension::Contains(strScript.c_str(), "4;3"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(4);
					}
				}
				if (StringExtension::Contains(strScript.c_str(), "Wybierz cyfrę '4'"))
				{
					if (StringExtension::Contains(strScript.c_str(), "1;4"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
					}
					if (StringExtension::Contains(strScript.c_str(), "2;4"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(2);
					}
					if (StringExtension::Contains(strScript.c_str(), "3;4"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(3);
					}
					if (StringExtension::Contains(strScript.c_str(), "4;4"))
					{
						GameFunctions::NetworkStreamSendScriptAnswerPacket(4);
					}
				}
				return -1;
			}
			break;
	}
	return nCPythonEventManagerRegisterEventSetFromString(This, strScript);
}

//##################################################################################################
bool _fastcall Hooks::NewCNetworkStreamRecv(void* This, void* EDX, int len, void* pDestBuf)
{
	bool ret;
	ret = nCNetworkStreamRecv(This, len, pDestBuf);
	BYTE* destBuf = (BYTE*)pDestBuf;

	BYTE header;
	memcpy(&header, destBuf, sizeof(header));
	switch (Globals::Server)
	{
	//case ServerName::VIDGAR:
	//	if (header == HEADER_GC_ITEM_GROUND_DEL && len == sizeof(TPacketGCItemGroundDel))
	//	{
	//		TPacketGCItemGroundDel	packet_item_ground_del;
	//		memcpy(&packet_item_ground_del, destBuf, sizeof(TPacketGCItemGroundDel));
	//		if (Globals::groundItemList.count(packet_item_ground_del.vid))
	//		{
	//			Globals::groundItemList.erase(packet_item_ground_del.vid);
	//		}
	//	}
	//	if (header == HEADER_GC_ITEM_GROUND_ADD && len == 58)
	//	{
	//		TPacketGCItemGroundAdd packet_item_ground_add;
	//		memcpy(&packet_item_ground_add, destBuf, sizeof(TPacketGCItemGroundAdd));
	//		/*__GlobalPositionToLocalPosition(packet_item_ground_add.lX, packet_item_ground_add.lY);*/

	//		TGroundItemInstance* pGroundItemInstance = new TGroundItemInstance();
	//		GameFunctionsCustom::GlobalPositionToLocalPosition(packet_item_ground_add.lX, packet_item_ground_add.lY);
	//		pGroundItemInstance->Instance = NULL;
	//		pGroundItemInstance->dwVirtualNumber = packet_item_ground_add.dwVnum;
	//		pGroundItemInstance->v3EndPosition.x = packet_item_ground_add.lX;
	//		pGroundItemInstance->v3EndPosition.y = -packet_item_ground_add.lY;
	//		pGroundItemInstance->v3EndPosition.z = packet_item_ground_add.lZ;
	//		pGroundItemInstance->v3RotationAxis = D3DVECTOR{ 0, 0, 0 };
	//		pGroundItemInstance->qEnd = D3DXQUATERNION{ 0, 0, 0,0 };
	//		pGroundItemInstance->v3Center = D3DVECTOR{ 0, 0, 0 };
	//		pGroundItemInstance->ThingInstance = NULL;
	//		pGroundItemInstance->dwStartTime = 0;
	//		pGroundItemInstance->dwEndTime = 0;
	//		pGroundItemInstance->eDropSoundType = 0;
	//		pGroundItemInstance->stOwnership = "";
	//		Globals::groundItemList.insert(std::make_pair(packet_item_ground_add.dwVID, pGroundItemInstance));
	//	}
	//	if (header == HEADER_GC_ITEM_OWNERSHIP) {
	//		TPacketGCItemOwnership packet_item_ownership;
	//		memcpy(&packet_item_ownership, destBuf, sizeof(TPacketGCItemOwnership));
	//		if (Globals::groundItemList.count(packet_item_ownership.dwVID))
	//		{
	//			Globals::groundItemList[packet_item_ownership.dwVID]->stOwnership = string(packet_item_ownership.szName);
	//		}
	//	}
	//	break;
	case ServerName::PANGEA:
		/*if (header == 0x32 && len == 8)
		{
			TPacketGCFishingPangea packetGCFishingPangea;
			memcpy(&packetGCFishingPangea, destBuf, sizeof(TPacketGCFishingPangea));
			DWORD vid = GameFunctions::PlayerGetMainCharacterIndex();
			if (packetGCFishingPangea.subheader == 2 && packetGCFishingPangea.vid == vid)
			{
				Fish::Instance().AppendCastDirect(packetGCFishingPangea.count);
			}
		}*/
		if (header == 0xA5 && len == 133)
		{
#ifdef FISHBOT			
			typedef struct packet_fishing_pangea_NEW
			{
				BYTE header;


				DWORD vid;
				char anim[40];

			};
			packet_fishing_pangea_NEW packet_fishing_pangea;
			memcpy(&packet_fishing_pangea, destBuf, sizeof(packet_fishing_pangea_NEW));
			if (GameFunctions::PlayerGetMainCharacterIndex() == packet_fishing_pangea.vid)
			{
				/*Logger::Add(Logger::FISH, true, Logger::WHITE, packet_fishing_pangea.anim);*/
				Fish::Instance().ParseMessage(packet_fishing_pangea.anim);

			}
#endif
		}
		break;
	case ServerName::KEVRA:
	{
		//if (header == 0x59 && len >= 11)
		//{
		//	TPacketGCFishingKevra packet;
		//	memcpy(&packet, destBuf, sizeof(TPacketGCFishingKevra));
		//	if (packet.subheader == 2 && packet.info == GameFunctions::PlayerGetMainCharacterIndex())
		//	{
		//		Fish::Instance().AppendCastDirect(packet.click_count);
		//	}
		//}
		//break;
	}
	case ServerName::METINPL:
		if (header == 42 && len >= sizeof(TPacketGCFishing) && Settings::FISH_ENABLE)
		{
			TPacketGCFishingGlobal packetGCFishing;
			memcpy(&packetGCFishing, destBuf, sizeof(TPacketGCFishingGlobal));
			//if (/*packetGCFishing.subheader == 3 || packetGCFishing.subheader == 4 ||*/ packetGCFishing.subheader == 5 && packetGCFishing.info == GameFunctions::PlayerGetMainCharacterIndex())
			//{
			//	return false;
			//}
			if (packetGCFishing.subheader == 2 && packetGCFishing.info == GameFunctions::PlayerGetMainCharacterIndex())
			{
				Fish::Instance().AppendCastDirect(1);
				return false;
			}
		}
		break;
	}
#ifdef DEVELOPER_MODE
	if (len > 1)
	{
		try 
		{
			PacketSniffer::Instance().ProcessRecvPacket(len, pDestBuf, (DWORD)_ReturnAddress() - Globals::hEntryBaseAddress);
		}
		catch (...)
		{
			printf("Packet parse Error!\n");
		}
	}
#endif
	return ret;
}

static char hwid[39] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static string hwid1;
static string hwid2;
static string hwid3;
//##################################################################################################################################################
bool _fastcall Hooks::NewCNetworkStreamSend(void* This, void* EDX, int len, void* pDestBuf)
{
	try
	{
		BYTE header;
		memcpy(&header, pDestBuf, sizeof(header));
		switch (Globals::Server)
		{
		case ServerName::WOM:
		{
			if (header == 0x6C && len == 1286)
			{
				char mac[22];
				int i, tp;
				for (i = 0; i < 6; i++)
				{
					tp = rand() % 256;

					_snprintf(mac, 22, "%02X::%02X::%02X::%02X::%02X::%02X", rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256);

				}
				strncpy((char*)pDestBuf + 1, &mac[0], 22);
			}
		}

		case ServerName::VIDGAR:
			if (header == HEADER_CG_LOGIN3 && len == 361)
			{
				strncpy((char*)pDestBuf + 70, hwid1.c_str(), 43);
				strncpy((char*)pDestBuf + 167, hwid2.c_str(), 43);
				strncpy((char*)pDestBuf + 264, hwid3.c_str(), 43);
			}
			break;
		case ServerName::VALIUM:
			if (header == HEADER_CG_LOGIN3 && len == 140)
			{
				strncpy((char*)pDestBuf + 91, StringExtension::ToUpper(MiscExtension::RandomString(32)).c_str(), 32);
			}
			break;
		case ServerName::SG2:
			if (hwid[0] == NULL)
			{
				for (int i = 0; i < 39; i++)
				{
					if (MiscExtension::RandomInt(0, 1))
					{
						hwid[i] = MiscExtension::RandomInt(0x41, 0x46);
					}
					else
					{
						hwid[i] = MiscExtension::RandomInt(0x30, 0x39);
					}
				}
			}
			if (header == 0x6D && len == 93)
			{
				for (int i = 0; i < 39; i++)
				{
					if (MiscExtension::RandomInt(0, 1))
					{
						MemoryExtension::MemSet((DWORD)pDestBuf + 53 + i, hwid[i], 1);
					}
					else
					{
						MemoryExtension::MemSet((DWORD)pDestBuf + 53 + i, hwid[i], 1);
					}
				}

			}
			if (header == 0x6F && len == 106)
			{
				for (int i = 0; i < 39; i++)
				{
					if (MiscExtension::RandomInt(0, 1))
					{
						MemoryExtension::MemSet((DWORD)pDestBuf + 66 + i, hwid[i], 1);
					}
					else
					{
						MemoryExtension::MemSet((DWORD)pDestBuf + 66 + i, hwid[i], 1);
					}
				}
			}

			if (header == 0xF1 && len == 67)
			{
				char u[3] = { 0x62, 0x69, 0x6e };
				int o = 0;
				for (int i = 14; i < 17; i++)
				{

					MemoryExtension::MemSet((DWORD)pDestBuf + i, (int)u[o], 1);
				}
			}
			break;
		}
		bool ret = nCNetworkStreamSend(This, len, pDestBuf);
		BYTE* destBuf = (BYTE*)pDestBuf;
		PacketSniffer::Instance().ProcessSendPacket(len, pDestBuf, (DWORD)_ReturnAddress() - Globals::hEntryBaseAddress);
		return ret;
	}
	catch (...)
	{
	}
}

int _stdcall Hooks::NewCNetworkStreamSendAeldra(SOCKET s, const char* pDestBuf, int len, int flags)
{
	try
	{
		socketAeldra = s;
		BYTE* recvBuff = new BYTE[len];
		memcpy(recvBuff, pDestBuf, len);
		string packetHex = StringExtension::MakeHexString((BYTE*)pDestBuf, len, true, true);
		packetHex = StringExtension::ReplaceString(packetHex, "50 00 0B 00 00 00 08", "50 00 0B 00 00 00 10");
		std::vector<char> bytes = StringExtension::HexToBytes(packetHex);
		const char* data = reinterpret_cast<const char*>(bytes.data());
		int ret = nCNetworkStreamSendAeldra(s, data, len, flags);
		BYTE* destBuf = (BYTE*)pDestBuf;
	#ifdef DEVELOPER_MODE
		PacketSniffer::Instance().ProcessSendPacket(len, (void*)data, (DWORD)_ReturnAddress() - Globals::hEntryBaseAddress);
	#endif
		return ret;
	}
	catch (...)
	{
		return true;
	}
}

//##################################################################################################################################################
void _fastcall Hooks::NewCPythonChatAppendChat(void* This, void* EDX, int iType, const char* c_szChat)
{
	if (iType == CHAT_TYPE_TALKING)
	{
		if (Settings::PROTECTION_SHOW_TALK_BALLOON_ENABLE)
		{
			string title = StringExtension::StringFormat("Normal[%s]", GameFunctionsCustom::PlayerGetName());
			MiscExtension::UpdateBalloon(Globals::mainHwnd, title.c_str(), c_szChat, NULL);
		}
		if (Settings::PROTECTION_PLAY_TALK_BEEP_ENABLE)
		{
			CreateThread(0, NULL, (LPTHREAD_START_ROUTINE)MiscExtension::PlayAlerSound, NULL, NULL, NULL);
		}
		if (Settings::PROTECTION_FLASH_TALK_ICON_ENABLE)
		{
			FLASHWINFO fi;
			fi.cbSize = sizeof(FLASHWINFO);
			fi.hwnd = Globals::mainHwnd;
			fi.dwFlags = FLASHW_ALL;
			fi.uCount = 3;
			fi.dwTimeout = 0;
			FlashWindowEx(&fi);
		}
		if (Settings::PROTECTION_SHOW_TALK_LOGS_ENABLE)
		{
			Logger::Add(Logger::MAIN, true, Logger::WHITE, c_szChat);		
		}	
	}
#ifdef FISHBOT
	Fish::Instance().ParseMessage(c_szChat);
#endif
	nCPythonChatAppendChat(This, iType, c_szChat);
}

void _fastcall Hooks::NewCInputKeyboardUpdateKeyboard(void* This, void* EDX) 
{
	if (MainForm::IsInitialized && MainForm::SideBarIsOpen) 
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard || io.WantTextInput)
		{
			return;
		}
	}
	nCInputKeyboardUpdateKeyboard(This);
}

DWORD* _fastcall Hooks::NewCResourceManagerGetResourcePointer(void* This, void* EDX, const char* c_szFileName)
{
	Fish::Instance().ParseMessage(c_szFileName);
	//printf("Resource File: %s\n", c_szFileName);
	return nCResourceManagerGetResourcePointer(This, c_szFileName);
}

std::shared_ptr<PLH::HWBreakPointHook> Hooks::screenToClientHwBpHook;
bool __stdcall Hooks::NewScreenToClient(HWND hWnd, LPPOINT lpPoint)
{
	auto protObj = Hooks::screenToClientHwBpHook->getProtectionObject();
	if (!MainCore::isInitialized)
	{
		Globals::mainHwnd = hWnd;
		MainCore::Initialize();
	}
	else
	{
		Hooks::screenToClientHwBpHook->unHook();
	}
	return ScreenToClient(hWnd, lpPoint);
}

PLH::VFuncMap directxVFuncs;
std::unique_ptr<PLH::VFuncSwapHook> endSceneAndResetHook = nullptr;
HRESULT __stdcall Hooks::NewDirectEndScene(void* This)
{
	HRESULT ret = ((Globals::tDirectEndScene)directxVFuncs.at(EndSceneIndex))(This);
	if (Device::pDevice != NULL)
	{
		if (!MainForm::IsInitialized)
		{
			MainForm::Initialize();
		}
		else
		{
			MainCore::UpdateLoop();
			MainForm::Menu();
		}
	}
	return ret;
}

HRESULT __stdcall Hooks::NewDirectReset(void* This, D3DPRESENT_PARAMETERS* ppReset)
{
#ifdef DX9
	ImGui_ImplDX9_InvalidateDeviceObjects();
#else
	ImGui_ImplDX8_InvalidateDeviceObjects();
#endif	
	HRESULT ret = ((Globals::tDirectReset)directxVFuncs.at(ResetIndex))(This, ppReset);
#ifdef DX9
	ImGui_ImplDX9_CreateDeviceObjects();
#else
	ImGui_ImplDX8_CreateDeviceObjects();
#endif	
	return ret;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Hooks::Initialize()
{
	//DirectX
	PLH::VFuncMap redirect = { {(uint16_t)EndSceneIndex, (uint64_t)Hooks::NewDirectEndScene},  {(uint16_t)ResetIndex, (uint64_t)Hooks::NewDirectReset} };
	endSceneAndResetHook = std::make_unique<PLH::VFuncSwapHook>((char*)Device::pDevice, redirect, &directxVFuncs);
	endSceneAndResetHook->hook();
	//Game Hook
	switch (Globals::Server)
	{
		case ServerName::PANGEA:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			//nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
			break;
		}
		case ServerName::ASENIS:
		case ServerName::BARIA:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			//nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
			break;
		}
		case ServerName::VEDNAR:
		case ServerName::MEDIUMMT2:
		case ServerName::ORIGINS2:
		case ServerName::CALLIOPE2:
		case ServerName::CLASSIC:
		case ServerName::VALIUM:
		case ServerName::DEVERIA:
		case ServerName::LUNA:
		case ServerName::DRAGON:
		case ServerName::DRAGON2:
		case ServerName::G22:
		{
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			break;
		}
		case ServerName::CarolineMT2:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			//nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
			break;
		}
		case ServerName::NEVILLA:
		case ServerName::TASTRIA2:
		case ServerName::ARATHAR:
		case ServerName::EGORIA:
		case ServerName::Ernidia:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
		nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			//nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			break;
		}
		case ServerName::GLEVIA:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			//nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
			break;
		}
		case ServerName::WOM:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			break;
		}
		case ServerName::KEVRA:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
		//	nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
		//	nCResourceManagerGetResourcePointer = (Globals::tCResourceManagerGetResourcePointer)DetourFunction((PBYTE)Globals::CResourceManagerGetResourcePointer, (PBYTE)NewCResourceManagerGetResourcePointer);
			break;
		}
		case ServerName::TAMIDIA2021:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			//nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			//nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
		}
		case ServerName::AELDRA:
		{
			//nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			//nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			//nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			//nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCNetworkStreamSendAeldra = (Globals::tCNetworkStreamSendAeldra)DetourFunction((PBYTE)LI_FN(GetProcAddress)(LI_FN(LoadLibrary)("wsock32.dll"), "send"), (PBYTE)NewCNetworkStreamSendAeldra);
			//nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			//nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			//nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			//nCPythonChatAppendChat = (Globals::tCPythonChatAppendChat)DetourFunction((PBYTE)Globals::CPythonChatAppendChat, (PBYTE)NewCPythonChatAppendChat);
			break;
		}
		case ServerName::METINPL:
		{
			nCInstanceBaseAvoidObject = (Globals::tCInstanceBaseAvoidObject)DetourFunction((PBYTE)Globals::CInstanceBaseAvoidObject, (PBYTE)NewCInstanceBaseAvoidObject);
			nCInstanceBaseBlockMovement = (Globals::tCInstanceBaseBlockMovement)DetourFunction((PBYTE)Globals::CInstanceBaseBlockMovement, (PBYTE)NewCInstanceBaseBlockMovement);
			nCActorInstanceTestActorCollision = (Globals::tCActorInstanceTestActorCollision)DetourFunction((PBYTE)Globals::CActorInstanceTestActorCollision, (PBYTE)NewCActorInstanceTestActorCollision);
			nCPhysicsObjectIncreaseExternalForce = (Globals::tCPhysicsObjectIncreaseExternalForce)DetourFunction((PBYTE)Globals::CPhysicsObjectIncreaseExternalForce, (PBYTE)NewCPhysicsObjectIncreaseExternalForce);
			nCInputKeyboardUpdateKeyboard = (Globals::tCInputKeyboardUpdateKeyboard)DetourFunction((PBYTE)Globals::CInputKeyboardUpdateKeyboard, (PBYTE)NewCInputKeyboardUpdateKeyboard);
			nCNetworkStreamRecv = (Globals::tCNetworkStreamRecv)DetourFunction((PBYTE)Globals::CNetworkStreamRecv, (PBYTE)NewCNetworkStreamRecv);
			nCNetworkStreamSend = (Globals::tCNetworkStreamSend)DetourFunction((PBYTE)Globals::CNetworkStreamSend, (PBYTE)NewCNetworkStreamSend);
			nCPythonApplicationRenderGame = (Globals::tCPythonApplicationRenderGame)DetourFunction((PBYTE)Globals::CPythonApplicationRenderGame, (PBYTE)NewCPythonApplicationRenderGame);
			nPyCallClassMemberFunc = (Globals::tPyCallClassMemberFunc)DetourFunction((PBYTE)Globals::PyCallClassMemberFunc, (PBYTE)NewPyCallClassMemberFunc);
			nCPythonEventManagerRegisterEventSetFromString = (Globals::tCPythonEventManagerRegisterEventSetFromString)DetourFunction((PBYTE)Globals::CPythonEventManagerRegisterEventSetFromString, (PBYTE)NewCPythonEventManagerRegisterEventSetFromString);
			break;
		}
	}
}
