#pragma once

class GameFunctions
{
public:
	static DWORD GetVIDByInstance(DWORD* instance)
	{
		DWORD vid = 0;
		if (Globals::Server == ServerName::METINPL)
		{
			TCharacterInstanceMapGlobal m_kAliveInstMap = *(TCharacterInstanceMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonCharacterManagerInstance + 56) + 4));
			for (auto itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
			{
				if (itor->second == instance)
				{
					vid = itor->first;
				}
			}
		}
		else
		{
			TCharacterInstanceMap m_kAliveInstMap;
			switch (Globals::Server)
			{
			case ServerName::AELDRA:
			{
				m_kAliveInstMap = *(TCharacterInstanceMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonCharacterManagerInstance + 44) + 4));
				break;
			}
			case ServerName::CALLIOPE2:
			{
				m_kAliveInstMap = *(TCharacterInstanceMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonCharacterManagerInstance + 36) + 4));
				break;
			}
			default: {
				m_kAliveInstMap = *(TCharacterInstanceMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonCharacterManagerInstance + 32) + 4));
				break;
			}
			}
			for (auto itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
			{
				if (itor->second == instance)
				{
					vid = itor->first;
				}
			}
		}
		return vid;
	}
	//#################################################################################################################################
	static DWORD* CharacterManagerGetInstancePtr(int vid)
	{
		try
		{
			return Globals::CPythonCharacterManagerGetInstancePtr((void*)(Globals::iCPythonCharacterManagerInstance + 4), vid);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool ItemManagerGetItemDataPointer(DWORD dwItemID, DWORD** ppItemData)
	{
		try
		{
			return Globals::CItemManagerGetItemDataPointer((void*)(Globals::iCItemManagerInstance), dwItemID, ppItemData);
		}
		catch (...)
		{
			return false;
		}
	}
	static void ItemSelectItem(DWORD dwItemID)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonItemSelectItem)
			{
				return PythonExtension::CallPythonInteger1(Globals::CythonItemSelectItem, dwItemID);
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static const char* ItemDataGetName(DWORD dwItemID)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonItemGetItemName)
			{
				ItemSelectItem(dwItemID);
				return PythonExtension::GetPythonString0(Globals::CythonItemGetItemName);
			}
			else
			{
				DWORD* pItemData;
				GameFunctions::ItemManagerGetItemDataPointer(dwItemID, &pItemData);
				return Globals::CItemDataGetName(pItemData);
			}
		}
		catch (...)
		{
			return "";
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetMainCharacterIndex()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetMainCharacterIndex)
			{
				return PythonExtension::GetPythonInt(Globals::CythonPlayerGetMainCharacterIndex);
			}
			else
			{
				return GetVIDByInstance(PlayerNEW_GetMainActorPtr());
				//return Globals::CPythonPlayerGetMainCharacterIndex((void*)(Globals::iCPythonPlayerInstance + 4));
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static int PlayerGetStatus(DWORD dwType)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetStatus)
			{
				return PythonExtension::GetPythonInteger1(Globals::CythonPlayerGetStatus, 1);
			}
			else
			{
				return Globals::CPythonPlayerGetStatus((void*)(Globals::iCPythonPlayerInstance + 4), dwType);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetItemIndex(TItemPos cell)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetItemIndex)
			{
				return PythonExtension::GetPythonInteger2(Globals::CythonPlayerGetItemIndex, cell.window_type, cell.cell);
			}
			else
			{
				switch (Globals::Server)
				{
				case ServerName::BARIA:
				{
					typedef DWORD(__thiscall* GetItemIndex)(void* This, TItemPos Cell, char unk);
					GetItemIndex ItemIndex = (GetItemIndex)Globals::pCPythonPlayerGetItemIndex;
					return ItemIndex((void*)(Globals::iCPythonPlayerInstance + 4), cell, '\0');
					break;
				}
				default:
				{
					return Globals::CPythonPlayerGetItemIndex((void*)(Globals::iCPythonPlayerInstance + 4), cell);
					break;
				}
				}
			}
		}
		catch (...)
		{
			return 0;
		}
	}

	static DWORD PlayerGetItemCount(TItemPos cell)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetItemCount)
			{
				return PythonExtension::GetPythonInteger2(Globals::CythonPlayerGetItemCount, cell.window_type, cell.cell);
			}
			else
			{
				return Globals::CPythonPlayerGetItemCount((void*)(Globals::iCPythonPlayerInstance + 4), cell);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################

	static const char* PlayerGetName() 
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetName)
			{
				return PythonExtension::GetPythonString0(Globals::CythonPlayerGetName);
			}
			else
			{
				return Globals::CPythonPlayerGetName((void*)(Globals::iCPythonPlayerInstance + 4));
			}
		}
		catch (...)
		{
			return "";
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetItemMetinSocket(int slot, DWORD dwMetinSocketIndex)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetItemMetinSocket)
			{
				return PythonExtension::GetPythonInteger2(Globals::CythonPlayerGetItemMetinSocket, slot, dwMetinSocketIndex);
			}
			else
			{
				return Globals::CPythonPlayerGetItemMetinSocket((void*)(Globals::iCPythonPlayerInstance), TItemPos(INVENTORY, slot), dwMetinSocketIndex);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static void PlayerGetItemAttribute(TItemPos Cell, DWORD dwAttrSlotIndex, BYTE* pbyType, short* psValue)
	{
		try
		{
			Globals::CPythonPlayerGetItemAttribute((void*)(Globals::iCPythonPlayerInstance), Cell, dwAttrSlotIndex, pbyType, psValue);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetItemMetinSocket(TItemPos cell, DWORD dwMetinSocketIndex)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetItemMetinSocket)
			{
				return PythonExtension::GetPythonInteger3(Globals::CythonPlayerGetItemMetinSocket, cell.window_type, cell.cell, dwMetinSocketIndex);
			}
			else
			{
				return Globals::CPythonPlayerGetItemMetinSocket((void*)(Globals::iCPythonPlayerInstance), cell, dwMetinSocketIndex);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetRace()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetRace)
			{
				return PythonExtension::GetPythonInt(Globals::CythonPlayerGetRace);
			}
			else
			{
				return Globals::CPythonPlayerGetRace((void*)Globals::iCPythonPlayerInstance);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static void PlayerNEW_SetSingleDIKKeyState(int eDIKKey, bool isPress)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerSetSingleDIKKeyState)
			{
				PythonExtension::CallPythonInteger2(Globals::CythonPlayerSetSingleDIKKeyState, eDIKKey, isPress);
			}
			else
			{
				return Globals::CPythonPlayerNEW_SetSingleDIKKeyState((void*)Globals::iCPythonPlayerInstance, eDIKKey, isPress);
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static void PlayerClickSkillSlot(int skillIndex)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerClickSkillSlot)
			{
				PythonExtension::CallPythonInteger1(Globals::CythonPlayerClickSkillSlot, skillIndex);
			}
			else
			{
				Globals::CPythonPlayerClickSkillSlot((void*)Globals::iCPythonPlayerInstance, skillIndex);
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static bool PlayerIsSkillCoolTime(int skillIndex)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerIsSkillCoolTime)
			{
				return PythonExtension::GetPythonInteger1(Globals::CythonPlayerIsSkillCoolTime, skillIndex);
			}
			else
			{
				return Globals::CPythonPlayerIsSkillCoolTime((void*)Globals::iCPythonPlayerInstance, skillIndex);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool PlayerIsSkillActive(DWORD dwSlotIndex)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerIsSkillActive)
			{
				return PythonExtension::GetPythonInteger1(Globals::CythonPlayerIsSkillActive, dwSlotIndex);
			}
			else
			{
				return Globals::CPythonPlayerIsSkillActive((void*)Globals::iCPythonPlayerInstance, dwSlotIndex);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static DWORD PlayerGetTargetVID()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerGetTargetVID)
			{
				return PythonExtension::GetPythonInt(Globals::CythonPlayerGetTargetVID);
			}
			else
			{
				return Globals::CPythonPlayerGetTargetVID((void*)Globals::iCPythonPlayerInstance);
			}
		}
		catch (...)
		{
			return 0;
		}
	}

	static void PlayerSetTarget(DWORD dwVID, BOOL bForceChange = true)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerSetTarget)
			{
				return PythonExtension::CallPythonInteger1(Globals::CythonPlayerSetTarget, dwVID);
			}
			else
			{
				return Globals::CPythonPlayerSetTarget((void*)(Globals::iCPythonPlayerInstance + 4), dwVID, bForceChange);
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static void PlayerSetAttackKeyState(bool state)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerSetAttackKeyState)
			{
				return PythonExtension::CallPythonInteger1(Globals::CythonPlayerSetAttackKeyState, state);
			}
			else
			{
				Globals::CPythonPlayerSetAttackKeyState((void*)Globals::iCPythonPlayerInstance, state);
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static void Player__OnPressActor(DWORD* rkInstMain, DWORD dwPickedActorID, bool isAuto)
	{
		try
		{
			return Globals::CPythonPlayer__OnPressActor((void*)Globals::iCPythonPlayerInstance, rkInstMain, dwPickedActorID, isAuto);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static void Player__OnClickActor(DWORD* rkInstMain, DWORD dwPickedActorID, bool isAuto)
	{
		try
		{
			return Globals::CPythonPlayer__OnClickActor((void*)Globals::iCPythonPlayerInstance, rkInstMain, dwPickedActorID, isAuto);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static DWORD* PlayerNEW_GetMainActorPtr()
	{
		try
		{
			return Globals::CPythonPlayerNEW_GetMainActorPtr((void*)(Globals::iCPythonPlayerInstance + 4));
		}
		catch (...)
		{
			return NULL;
		}
	}
	//#################################################################################################################################
	static void PythonPlayerNEW_Fishing()
	{
		try
		{
			Globals::CPythonPlayerNEW_Fishing((void*)Globals::iCPythonPlayerInstance);
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static void NetworkStreamSendItemUsePacket(TItemPos cell)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendItemUsePacket)
			{
				PythonExtension::CallPythonInteger2(Globals::CythonNetSendItemUsePacket, cell.window_type, cell.cell);
			}
			else
			{
				switch (Globals::Server)
				{
					case ServerName::BARIA:
						{
							typedef bool(__thiscall* SendItemUsePacket)(void* This, TItemPos pos, char unk);
							SendItemUsePacket ItemUse = (SendItemUsePacket)Globals::pCPythonNetworkStreamSendItemUsePacket;
							ItemUse((void*)Globals::iCPythonNetworkStreamInstance, cell, '\0');
							break;
						}
					case ServerName::WOM:
						{
							typedef bool(__thiscall* tCPythonNetworkStreamSendItemUsePacket)(void* This, TItemPos& pos);
							tCPythonNetworkStreamSendItemUsePacket CPythonNetworkStreamSendItemUsePacket = (tCPythonNetworkStreamSendItemUsePacket)(Globals::pCPythonNetworkStreamSendItemUsePacket);
							CPythonNetworkStreamSendItemUsePacket((void*)Globals::iCPythonNetworkStreamInstance, cell);
							break;
						}
					default:
						{
							Globals::CPythonNetworkStreamSendItemUsePacket((void*)Globals::iCPythonNetworkStreamInstance, cell);

							break;
						}
				}
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static void NetworkStreamSendItemUseToItemPacket(TItemPos cell, TItemPos target)
	{
		try
		{
			Globals::CPythonNetworkStreamSendItemUseToItemPacket((void*)Globals::iCPythonNetworkStreamInstance, cell, target);
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static void NetworkStreamSendChatPacket(const char* c_szChat, BYTE byType = CHAT_TYPE_TALKING)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendChatPacket)
			{
				PythonExtension::CallPythonStringInt(Globals::CythonNetSendChatPacket, c_szChat, byType);
			}
			else
			{
				Globals::CPythonNetworkStreamSendChatPacket((void*)Globals::iCPythonNetworkStreamInstance, c_szChat, byType);
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendRefinePacket(BYTE pos, BYTE type)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendRefinePacket)
			{
				PythonExtension::CallPythonInteger2(Globals::CythonNetSendRefinePacket, pos, type);
				return true;
			}
			else
			{
				switch (Globals::Server)
				{
				case ServerName::AELDRA:
				{
					try
					{
						typedef bool(__thiscall* SendRefinePacket)(void* This, BYTE byPos, BYTE byType, bool unk);
						SendRefinePacket sendRefine = (SendRefinePacket)Globals::pCPythonNetworkStreamSendRefinePacket;
						return sendRefine((void*)Globals::iCPythonNetworkStreamInstance, pos, type, 0);
					}
					catch (...)
					{
						return false;
					}
					break;
				}
				case ServerName::CALLIOPE2:
				{
					try
					{
						typedef bool(__thiscall* SendRefinePacket)(void* This, BYTE byPos, BYTE byType, BYTE unk1, BYTE unk2, BYTE unk3, BYTE unk4);
						SendRefinePacket sendRefine = (SendRefinePacket)Globals::pCPythonNetworkStreamSendRefinePacket;
						return sendRefine((void*)Globals::iCPythonNetworkStreamInstance, pos, type, 0, 0, 0, 0);
					}
					catch (...)
					{
						return false;
					}
					break;
				}
				default:
				{
					return Globals::CPythonNetworkStreamSendRefinePacket((void*)Globals::iCPythonNetworkStreamInstance, pos, type);
					break;
				}
				}
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendSendExchangeStartPacket(DWORD vid)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendExchangeStartPacket)
			{
				PythonExtension::CallPythonInteger1(Globals::CythonNetSendExchangeStartPacket, vid);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendExchangeStartPacket((void*)Globals::iCPythonNetworkStreamInstance, vid);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendSendExchangeItemAddPacket(TItemPos ItemPos, BYTE byDisplayPos)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendExchangeItemAddPacket)
			{
				PythonExtension::CallPythonInteger3(Globals::CythonNetSendExchangeItemAddPacket, ItemPos.window_type, ItemPos.window_type, byDisplayPos);
				return true;
			}
			else
			{
				return  Globals::CPythonNetworkStreamSendExchangeItemAddPacket((void*)Globals::iCPythonNetworkStreamInstance, ItemPos, byDisplayPos);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendSendExchangeAcceptPacket()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendExchangeAcceptPacket)
			{
				PythonExtension::CallPython(Globals::CythonNetSendExchangeAcceptPacket);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendExchangeAcceptPacket((void*)Globals::iCPythonNetworkStreamInstance);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendWhisperPacket(const char* name, string s_szChat)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendWhisperPacket)
			{
				PythonExtension::CallPythonString2(Globals::CythonNetSendWhisperPacket, name, s_szChat.c_str());
				return true;
			}
			else
			{
				switch (Globals::Server)
				{
				case ServerName::AELDRA:
				{
					try
					{
						typedef bool(__thiscall* SendWhisperPacket)(void* This, const char* name, const char* c_szChat, bool unk);
						SendWhisperPacket sendWhisper = (SendWhisperPacket)Globals::pCPythonNetworkStreamSendWhisperPacket;
						return sendWhisper((void*)Globals::iCPythonNetworkStreamInstance, name, s_szChat.c_str(), false);
					}
					catch (...)
					{
						return false;
					}
					break;
				}
				default:
				{
					return Globals::CPythonNetworkStreamSendWhisperPacket((void*)Globals::iCPythonNetworkStreamInstance, name, s_szChat.c_str());
					break;
				}
				}
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendItemPickUpPacket(DWORD vid)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendItemPickUpPacket)
			{
				PythonExtension::CallPythonInteger1(Globals::CythonNetSendItemPickUpPacket, vid);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendItemPickUpPacket((void*)Globals::iCPythonNetworkStreamInstance, vid);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendItemDropPacketNew(TItemPos cell, DWORD elk, DWORD count)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendItemDropPacketNew)
			{
				PythonExtension::CallPythonInteger3(Globals::CythonNetSendItemDropPacketNew, cell.window_type, cell.cell, count);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendItemDropPacketNew((void*)Globals::iCPythonNetworkStreamInstance, cell, elk, count);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendOnClickPacket(DWORD vid)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendOnClickPacket)
			{
				PythonExtension::CallPythonInteger1(Globals::CythonNetSendOnClickPacket, vid);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendOnClickPacket((void*)Globals::iCPythonNetworkStreamInstance, vid);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendShopSellPacketNew(BYTE bySlot, WORD byCount)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendShopSellPacketNew)
			{
				PythonExtension::CallPythonInteger2(Globals::CythonNetSendShopSellPacketNew, bySlot, byCount);
				return true;
			}
			else
			{
				switch (Globals::Server)
				{
				case ServerName::METINPL:
				{
					typedef bool(__thiscall* SendShopSellPacketNew)(void* This, BYTE bySlot, WORD byCount, BYTE unk);
					SendShopSellPacketNew SendShopSell = (SendShopSellPacketNew)Globals::pCPythonNetworkStreamSendShopSellPacketNew;
					SendShopSell((void*)Globals::iCPythonNetworkStreamInstance, bySlot, byCount, 1);
					break;
				}
				default:
				{
					return Globals::CPythonNetworkStreamSendShopSellPacketNew((void*)Globals::iCPythonNetworkStreamInstance, bySlot, byCount);
					break;
				}
				}
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendShopBuyPacket(BYTE bPos)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendShopBuyPacket)
			{
				PythonExtension::CallPythonInteger1(Globals::CythonNetSendShopBuyPacket, bPos);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendShopBuyPacket((void*)Globals::iCPythonNetworkStreamInstance, bPos);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendShopEndPacket()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendShopEndPacket)
			{
				PythonExtension::CallPython(Globals::CythonNetSendShopEndPacket);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendShopEndPacket((void*)Globals::iCPythonNetworkStreamInstance);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendGiveItemPacket(DWORD dwTargetVID, TItemPos ItemPos, int iItemCount)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendGiveItemPacket)
			{
				PythonExtension::CallPythonInteger4(Globals::CythonNetSendGiveItemPacket, dwTargetVID, ItemPos.window_type, ItemPos.cell, iItemCount);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendGiveItemPacket((void*)Globals::iCPythonNetworkStreamInstance, dwTargetVID, ItemPos, iItemCount);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendItemMovePacket(TItemPos pos, TItemPos change_pos, BYTE num)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendItemMovePacket)
			{
				PythonExtension::CallPythonInteger5(Globals::CythonNetSendItemMovePacket, pos.window_type, pos.cell, change_pos.window_type, change_pos.cell, num);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendItemMovePacket((void*)Globals::iCPythonNetworkStreamInstance, pos, change_pos, num);
			}
		}
		catch (...)
		{
			return false;
		}
	}	
	//#################################################################################################################################
	static void NetworkStreamConnectGameServer(UINT iChrSlot)
	{
		try
		{
			if (Globals::Server == ServerName::Ernidia)
			{
				typedef void(__thiscall* tCPythonNetworkStreamConnectGameServer)(void* This, UINT iChrSlot, int additional);
				tCPythonNetworkStreamConnectGameServer ConnectGameServer = (tCPythonNetworkStreamConnectGameServer)Globals::pCPythonNetworkStreamConnectGameServer;
				return ConnectGameServer((void*)Globals::iCPythonNetworkStreamInstance, iChrSlot, 0);
			}
			else
			{
				Globals::CPythonNetworkStreamConnectGameServer((void*)Globals::iCPythonNetworkStreamInstance, iChrSlot);
			}
			if (Globals::UsePythonFunctions && Globals::CythonNetDirectEnter)
			{
				switch (Globals::Server)
				{
					case ServerName::METINPL:
					{
						PythonExtension::CallPythonInteger2(Globals::CythonNetDirectEnter, iChrSlot, 0);
						break;
					}
					default:
					{
						PythonExtension::CallPythonInteger1(Globals::CythonNetDirectEnter, iChrSlot);
						break;
					}
				}
			}
			else
			{
#if defined(EGORIA) || defined(SENTHIA)
				Globals::CPythonNetworkStreamConnectGameServer((void*)Globals::iCPythonNetworkStreamInstance, iChrSlot, 0);
#else
				Globals::CPythonNetworkStreamConnectGameServer((void*)Globals::iCPythonNetworkStreamInstance, iChrSlot);
#endif		
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static bool NetworkStreamIsOnline()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetIsConnect)
			{
				return PythonExtension::GetPythonInt(Globals::CythonNetIsConnect);
			}
			else
			{
				return Globals::CNetworkStreamIsOnline((void*)Globals::iCPythonNetworkStreamInstance);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//########################################################################## b nm,                                                                                                                                                                             #######################################################
	static DWORD NetworkStreamGetMainActorSkillGroup()
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetGetMainActorSkillGroup)
			{
				return PythonExtension::GetPythonInt(Globals::CythonNetGetMainActorSkillGroup);
			}
			else
			{
				return Globals::CPythonNetworkStreamGetMainActorSkillGroup((void*)Globals::iCPythonNetworkStreamInstance);
			}
		}
		catch (...)
		{
			return 0;
		}
	}
	//#################################################################################################################################
	static const char* NetworkStreamGetAccountCharacterSlotDataz(UINT iSlot, UINT eType)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetGetAccountCharacterSlotData)
			{
				return PythonExtension::GetPythonString2(Globals::CythonNetGetAccountCharacterSlotData, iSlot, eType);
			}
			else
			{
				return Globals::CNetworkStreamGetAccountCharacterSlotDataz((void*)Globals::iCPythonNetworkStreamInstance, iSlot, eType);
			}
		}
		catch (...)
		{
			return "";
		}
	}
	//#################################################################################################################################
	static bool  NetworkStreamSendCommandPacket(DWORD a1, DWORD a2, const char* a3)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetSendCommandPacket)
			{
				PythonExtension::CallPythonIntIntString(Globals::CythonNetSendCommandPacket, a1, a2, a3);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendCommandPacket((void*)Globals::iCPythonNetworkStreamInstance, a1, a2, a3);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamConnect(DWORD dwAddr, int port, int limitSec = 3)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonNetConnectTCP)
			{
				char szAddr[256];
				{
					BYTE ip[4];
					ip[0] = dwAddr & 0xff; dwAddr >>= 8;
					ip[1] = dwAddr & 0xff; dwAddr >>= 8;
					ip[2] = dwAddr & 0xff; dwAddr >>= 8;
					ip[3] = dwAddr & 0xff; dwAddr >>= 8;

					sprintf(szAddr, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
				}

				PythonExtension::CallPythonStringInt(Globals::CythonNetConnectTCP, szAddr, port);
				return true;
			}
			else
			{
				return Globals::CNetworkStreamConnect((void*)Globals::iCPythonNetworkStreamInstance, dwAddr, port, limitSec);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendScriptAnswerPacket(int iAnswer)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonEventSelectAnswer)
			{
				PythonExtension::CallPythonInteger2(Globals::CythonEventSelectAnswer, 0, iAnswer);
				return true;
			}
			else
			{
				return Globals::CPythonNetworkStreamSendScriptAnswerPacket((void*)Globals::iCPythonNetworkStreamInstance, iAnswer);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static void NetworkStreamServerCommand(const char* c_szCommand)
	{
		try
		{
			return Globals::CPythonNetworkStreamServerCommand((void*)Globals::iCPythonNetworkStreamInstance, c_szCommand);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendFishingPacket(int rot)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendFishingPacket((void*)Globals::iCPythonNetworkStreamInstance, rot);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendFishingQuitPacket(int count, float rot)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendFishingQuitPacket((void*)Globals::iCPythonNetworkStreamInstance, count, rot);
		}
		catch (...)
		{
			return false;
		}
	}

	static bool NetworkStreamSendEmoticon(BYTE emoticon)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendEmoticon((void*)Globals::iCPythonNetworkStreamInstance, emoticon);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendSpecial(int nLen, void* pvBuf)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendSpecial((void*)Globals::iCPythonNetworkStreamInstance, nLen, pvBuf);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendAttackPacket(UINT uMotAttack, DWORD dwVIDVictim)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendAttackPacket((void*)Globals::iCPythonNetworkStreamInstance, uMotAttack, dwVIDVictim);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendUseSkillPacket(DWORD dwSkillIndex, DWORD dwTargetVID)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendUseSkillPacket((void*)Globals::iCPythonNetworkStreamInstance, dwSkillIndex, dwTargetVID);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendAddFlyTargetingPacket(DWORD dwTargetVID, D3DVECTOR& kPPosTarget)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendAddFlyTargetingPacket((void*)Globals::iCPythonNetworkStreamInstance, dwTargetVID, kPPosTarget);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendShootPacket(UINT uSkill)
	{
		try
		{
			return Globals::CPythonNetworkStreamSendShootPacket((void*)Globals::iCPythonNetworkStreamInstance, uSkill);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamRecv(int len, void* pSrcBuf)
	{
		try
		{
			return Globals::CNetworkStreamRecv((void*)Globals::iCPythonNetworkStreamInstance, len, pSrcBuf);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSend(int len, void* pSrcBuf)
	{
		try
		{
			switch (Globals::Server)
			{
			case ServerName::AELDRA:
			{
				typedef bool(__thiscall* NetworkStreamSend)(void* This, int len, void* pDestBuf, bool sendInstant);
				NetworkStreamSend Send = (NetworkStreamSend)Globals::pCNetworkStreamSend;
				return Send((void*)Globals::iCPythonNetworkStreamInstance, len, pSrcBuf, 0);
				break;
			}
			default:
			{
				return Globals::CNetworkStreamSend((void*)Globals::iCPythonNetworkStreamInstance, len, pSrcBuf);
				break;
			}
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	/*static bool NetworkStreamPeek(int nLen, void* pvBuf)
	{
		return Globals::CNetworkStreamPeek((void*)Globals::iCPythonNetworkStreamInstance, nLen, pvBuf);
	}*/
	//#################################################################################################################################
	static bool NetworkStreamSendSequence()
	{
		try
		{
			return Globals::CNetworkStreamSendSequence((void*)Globals::iCPythonNetworkStreamInstance);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendSyncPositionPacket(DWORD dwVictimVID, DWORD dwVictimX, DWORD dwVictimY)
	{
		try
		{
			int uiVictimCount = 1;
			TPacketCGSyncPosition kPacketSync;
			switch (Globals::Server)
			{
			case ServerName::METINPL:
				kPacketSync.header = 0x0D;
				break;
			default:
				kPacketSync.header = 0x8;
				break;
			}
			kPacketSync.wSize = sizeof(kPacketSync) + sizeof(TPacketCGSyncPositionElement) * uiVictimCount;

			if (!GameFunctions::NetworkStreamSend(sizeof(kPacketSync), &kPacketSync))
			{
				return false;
			}

			TPacketCGSyncPositionElement kSyncPos;
			kSyncPos.dwVID = dwVictimVID;
			kSyncPos.lX = dwVictimX;
			kSyncPos.lY = dwVictimY;
			BackgroundLocalPositionToGlobalPosition(kSyncPos.lX, kSyncPos.lY);
			if (!GameFunctions::NetworkStreamSend(sizeof(kSyncPos), &kSyncPos))
			{
				return false;
			}

			return GameFunctions::NetworkStreamSendSequence();
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool NetworkStreamSendCharacterStatePacket(const D3DVECTOR& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg)
	{
		try
		{
			//DWORD xd = PatternScan::FindPattern("55 8B EC 8B 0D ? ? ? ? 5D E9 ? ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ?");
			switch (Globals::Server)
			{
				/*case ServerName::DEVERIA:*/
				case ServerName::ASENIS:
					{
						typedef bool(__thiscall* tCPythonNetworkStreamSendCharacterStatePacket)(void* This, const D3DVECTOR& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg, int unk);
						tCPythonNetworkStreamSendCharacterStatePacket CPythonNetworkStreamSendCharacterStatePacket = (tCPythonNetworkStreamSendCharacterStatePacket)Globals::pCPythonNetworkStreamSendCharacterStatePacket;
						return CPythonNetworkStreamSendCharacterStatePacket((void*)Globals::iCPythonNetworkStreamInstance, c_rkPPosDst, fDstRot, eFunc, uArg, 0);
						break;
					}
				case ServerName::AELDRA:
				{
					TPacketCGStatePacket kPacketMove;
					kPacketMove.header = 0x4E;
					kPacketMove.size = sizeof(kPacketMove);
					kPacketMove.unknown = 0x10;
					LONG c_rkPPosDstX = c_rkPPosDst.x;
					LONG c_rkPPosDstY = c_rkPPosDst.y;
					GameFunctions::BackgroundLocalPositionToGlobalPosition(c_rkPPosDstX, c_rkPPosDstY);
					kPacketMove.lX = c_rkPPosDstX;
					kPacketMove.lY = c_rkPPosDstY;
					kPacketMove.bFunc = eFunc;
					kPacketMove.bArg = uArg;
					kPacketMove.bRot = fDstRot / 5.0f;
					typedef int(__stdcall* ELTimer_GetServerMSec)();
					ELTimer_GetServerMSec GetServerMSec = (ELTimer_GetServerMSec)(Globals::hEntryBaseAddress+ 0x369680);
					kPacketMove.dwTime = GetServerMSec();

					Globals::tCNetworkStreamSendAeldra SendPacket = (Globals::tCNetworkStreamSendAeldra)LI_FN(GetProcAddress)(LI_FN(LoadLibrary)("wsock32.dll"), "send");
					SendPacket(socketAeldra, (const char*)&kPacketMove, sizeof(kPacketMove), NULL);
					break;
				}
				case ServerName::CarolineMT2:
				{
					
					typedef struct command_move
					{
						BYTE        bHeader;
						BYTE        bFunc;
						BYTE        bArg;
						BYTE        bRot;
						LONG        lX;
						LONG        lY;
						DWORD        dwTime;
					} TPacketCGMove;


					TPacketCGMove kStatePacket;
					kStatePacket.bHeader = HEADER_CG_CHARACTER_MOVE;
					kStatePacket.bFunc = eFunc;
					kStatePacket.bArg = uArg;
					kStatePacket.bRot = fDstRot / 5.0f;
					kStatePacket.lX = long(c_rkPPosDst.x);
					kStatePacket.lY = long(c_rkPPosDst.y);

					typedef DWORD(__cdecl* tELTimer_GetServerMSec)();
					tELTimer_GetServerMSec ELTimer_GetServerMSec = (tELTimer_GetServerMSec)(Globals::hEntryBaseAddress + 0xB09B0);  //55 8B EC 8B 0D ? ? ? ? 5D E9 ? ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ? ELTimer_GetServerMSec
					kStatePacket.dwTime = ELTimer_GetServerMSec();

					BackgroundLocalPositionToGlobalPosition(kStatePacket.lX, kStatePacket.lY);
					NetworkStreamSend(sizeof(TPacketCGMove), &kStatePacket);
					return NetworkStreamSendSequence();
					break;
				}
				case ServerName::DEVERIA:
					{
						DWORD address = Globals::pCPythonNetworkStreamSendCharacterStatePacket;
						DWORD* instance = (DWORD*)Globals::iCPythonNetworkStreamInstance;
						__asm
						{
							mov     eax, [address]
							mov     ecx, instance
							push [uArg]
							push [eFunc]
							push[fDstRot]
							movss   xmm2, [c_rkPPosDst]
							call	eax
						}
						break;
					}
				default:
					{
						return Globals::CPythonNetworkStreamSendCharacterStatePacket((void*)Globals::iCPythonNetworkStreamInstance, c_rkPPosDst, fDstRot, eFunc, uArg);
						break;
					}
			}

		}
		catch (...)
		{
			return false;
		}
	}
	
	//#################################################################################################################################
	static void NetworkStream__DirectEnterMode_Set(UINT charSlot)
	{
		try
		{
			return Globals::CNetworkStream__DirectEnterMode_Set((void*)Globals::iCPythonNetworkStreamInstance, charSlot);
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static void SelectInstancePython(DWORD vid)
	{
		try
		{
			PythonExtension::CallPythonInteger1(Globals::CythonChrSelectInstance, vid);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static void InstanceBase__SetAffect(DWORD* instance, UINT eAffect, bool isVisible)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrmgrSetAffect)
			{
				PythonExtension::CallPythonInteger3(Globals::CythonChrmgrSetAffect, GetVIDByInstance(instance), eAffect, isVisible);
			}
			else
			{
				Globals::CInstanceBase__SetAffect(instance, eAffect, isVisible);
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static void InstanceBaseNEW_GetPixelPosition(DWORD* instance, D3DVECTOR* pPixelPosition)
	{
		if (!instance)
		{
			return;
		}
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrGetPixelPosition)//Globals::Server != METINPL)
			{
				*pPixelPosition = PythonExtension::GetPythonD3DVECTOR1(Globals::CythonChrGetPixelPosition, GetVIDByInstance(instance));
			}
			else
			{
				Globals::CInstanceBaseNEW_GetPixelPosition(instance, pPixelPosition);
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static bool InstanceBaseNEW_MoveToDestPixelPositionDirection(DWORD* instance, D3DVECTOR& c_rkPPosDst)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrMoveToDestPosition)
			{
				DWORD vid = GetVIDByInstance(instance);
				PythonExtension::CallPythonInteger3(Globals::CythonChrMoveToDestPosition, vid, c_rkPPosDst.x, c_rkPPosDst.y);
				return true;
			}
			else
			{
				return Globals::CInstanceBaseNEW_MoveToDestPixelPositionDirection(instance, c_rkPPosDst);
			}
		}
		catch (...)
		{
			return false;
		}
		}
	//#################################################################################################################################
	static int InstanceBaseGetInstanceType(DWORD* instance)
	{
		if (!instance)
		{
			return -1;
		}
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrGetInstanceType)
			{
				DWORD vid = GetVIDByInstance(instance);
				return PythonExtension::GetPythonInteger1(Globals::CythonChrGetInstanceType, vid);
			}
			else
			{
				return Globals::CInstanceBaseGetInstanceType(instance);
			}
		}
		catch (...)
		{
			return -1;
		}
	}
	//#################################################################################################################################
	static int InstanceBaseGetVirtualNumber(DWORD* instance)
	{
		if (!instance)
		{
			return -1;
		}
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrGetVirtualNumber)
			{
				DWORD vid = GetVIDByInstance(instance);
				return PythonExtension::GetPythonInteger1(Globals::CythonChrGetVirtualNumber, vid);
			}
			else
			{
				return Globals::CInstanceBaseGetInstanceVirtualNumber(instance);
			}
		}
		catch (...)
		{
			return -1;
		}
	}
	//#################################################################################################################################
	static bool InstanceBaseIsMountingHorse(DWORD* instance)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonPlayerIsMountingHorse)
			{
				return PythonExtension::GetPythonInt(Globals::CythonPlayerIsMountingHorse);
			}
			else
			{
				return Globals::CInstanceBaseIsMountingHorse(instance);
			}
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static const char* InstanceBaseGetNameString(DWORD* instance)
	{
		if (instance)
		{
			try
			{
				if (Globals::UsePythonFunctions && Globals::CythonChrGetNameByVID)
				{
					DWORD vid = GetVIDByInstance(instance);
					return PythonExtension::GetPythonString1(Globals::CythonChrGetNameByVID, vid);
				}
				else
				{
					Globals::CInstanceBaseGetNameString(instance);
				}
			}
			catch (...)
			{
				return "";
			}
		}
		else
		{
			return "";
		}
	}
	//#################################################################################################################################
	static void InstanceBaseSCRIPT_SetPixelPosition(DWORD* instance, float x, float y)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrSetPixelPosition)
			{
				DWORD vid = GetVIDByInstance(instance);
				SelectInstancePython(vid);
				PythonExtension::CallPythonInteger2(Globals::CythonChrSetPixelPosition, x, y);
			}
			else
			{
				DWORD address = Globals::pCInstanceBaseSCRIPT_SetPixelPosition;
				switch (Globals::Server)
				{
				case ServerName::DRAGON:
				case ServerName::DEVERIA:
				case ServerName::VEDNAR:
				case ServerName::CarolineMT2:
				case ServerName::CALLIOPE2:
				case ServerName::ASENIS:
				{
					__asm
					{
						mov     eax, [address]
						mov     ecx, instance
						movss   xmm2, [y]
						movss   xmm1, [x]
						call	eax
					}
					break;
				}
				default:
				{
					Globals::CInstanceBaseSCRIPT_SetPixelPosition(instance, x, y);
					break;
				}
				}
			}
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static const void InstanceSetRotation(DWORD* instance, float fRotation)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrSetRotation)
			{
				DWORD vid = GetVIDByInstance(instance);
				SelectInstancePython(vid);
				PythonExtension::CallPythonFloat1(Globals::CythonChrSetRotation, fRotation);
			}
			else
			{
				DWORD address = Globals::pCInstanceBaseSetRotation;
				switch (Globals::Server)
				{
					case ServerName::DRAGON:
					case ServerName::CALLIOPE2:
						{
							DWORD playerInstance = (DWORD)GameFunctions::PlayerNEW_GetMainActorPtr();
							__asm
							{
								mov     eax, [address]
								mov     ecx, instance
								movss   xmm1, [fRotation]
								call	eax
							}
							break;
						}
					default:
						{
							Globals::CInstanceBaseSetRotation((void*)instance, fRotation);
							break;
						}
				}
			}
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static float InstanceBaseGetRotation(DWORD* instance)
	{
		try
		{
			if (Globals::UsePythonFunctions && Globals::CythonChrGetRotation)
			{
				DWORD vid = GetVIDByInstance(instance);
				SelectInstancePython(vid);
				return 360.0f - PythonExtension::GetPythonFloat(Globals::CythonChrGetRotation);
			}
			else
			{
				float rotation = 0;
				DWORD address = Globals::pCInstanceBaseGetRotation;
				switch (Globals::Server)
				{
					case ServerName::DRAGON:
					case ServerName::DEVERIA:
					case ServerName::VEDNAR:
					case ServerName::CarolineMT2:
					case ServerName::CALLIOPE2:
					case ServerName::ASENIS:
					{
						DWORD playerInstance = (DWORD)GameFunctions::PlayerNEW_GetMainActorPtr();
						__asm
						{
							mov     eax, [address]
							mov     ecx, playerInstance
							call	eax
							movss[rotation], xmm0
						}
						break;
					}
					default:
					{
						rotation = Globals::CInstanceBaseGetRotation(instance);
						break;
					}
				}
				return rotation;
			}
		}
		catch (...)
		{
			return 0.0f;
		}
	}
	//#################################################################################################################################
	static const bool InstanceIsWaiting(DWORD* instance)
	{
		try
		{
			return Globals::CInstanceBaseIsWaiting((void*)instance);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool InstanceBaseIsDead(DWORD* instance)
	{
		if (!instance)
		{
			return false;
		}
		try
		{
			return Globals::CInstanceBaseIsDead(instance);
		}
		catch (...)
		{
			return false;
		}
	}
	//#################################################################################################################################
	static TMobTable* NonPlayerGetTable(int vid)
	{
		try
		{
			return (TMobTable*)Globals::CPythonNonPlayerGetTable((void*)Globals::iCPythonNonPlayerInstance, vid);
		}
		catch (...)
		{
			return NULL;
		}
	}
	//#################################################################################################################################
	static void BackgroundLocalPositionToGlobalPosition(LONG& rLocalX, LONG& rLocalY)
	{
		try
		{
			return Globals::CPythonBackgroundLocalPositionToGlobalPosition((void*)Globals::iCPythonBackgroundInstance, rLocalX, rLocalY);
		}
		catch (...)
		{

		}
	}
	//#################################################################################################################################
	static TMapInfo* BackgroundGlobalPositionToMapInfo(DWORD dwGlobalX, DWORD dwGlobalY)
	{
		try
		{
			switch (Globals::Server)
			{
				case ServerName::WOM:
					{
						typedef TMapInfo* (__thiscall* tCPythonBackgroundGlobalPositionToMapInfo)(void* This, DWORD dwGlobalX, DWORD dwGlobalY,int unk);
						tCPythonBackgroundGlobalPositionToMapInfo CPythonBackgroundGlobalPositionToMapInfo = (tCPythonBackgroundGlobalPositionToMapInfo)(Globals::pCPythonBackgroundGlobalPositionToMapInfo);
						CPythonBackgroundGlobalPositionToMapInfo((void*)Globals::iCPythonBackgroundInstance, dwGlobalX, dwGlobalY,0);
						break;
					}
				default:
					{
						
							return Globals::CPythonBackgroundGlobalPositionToMapInfo((void*)Globals::iCPythonBackgroundInstance, dwGlobalX, dwGlobalY);
						
						break;
					}
			}
		}
		catch (...)
		{
			
		}
		return NULL;
	}
	static bool PyCallClassMemberFunc(PyObject* poClass, const char* c_szFunc, PyObject* poArgs)
	{
		return Globals::PyCallClassMemberFunc(poClass, c_szFunc, poArgs);
	}
	//#################################################################################################################################
	static float GetBackgroundHeight(float x, float y)
	{
		try
		{
			DWORD address = Globals::pCInstanceBase__GetBackgroundHeight;
			float height = 0;
			switch (Globals::Server)
			{
			case ServerName::DRAGON:
			case ServerName::DEVERIA:
			case ServerName::CarolineMT2:
			case ServerName::CALLIOPE2:
			case ServerName::ASENIS:
			{
				DWORD* instance = PlayerNEW_GetMainActorPtr();
				if (instance)
				{
					__asm
					{
						mov     eax, [address]
						mov     ecx, instance
						movss   xmm2, [y]
						movss   xmm1, [x]
						call	eax
						movss[height], xmm0
					}
				}
				break;
			}
			default:
			{
				height = Globals::CInstanceBase__GetBackgroundHeight(x, y);
				break;
			}
			}
			return height;
		}
		catch (...)
		{
			return 0.0f;
		}
	}

	static DWORD* ResourceManagerGetResourcePointer(const char* name)
	{
		try
		{
			return Globals::CResourceManagerGetResourcePointer((void*)Globals::iCResourceManagerInstance, name);
		}
		catch (...)
		{
			return NULL;
		}
	}
	//#################################################################################################################################
	static void ResourceReload(DWORD* instance)
	{
		try
		{
			return Globals::CResourceReload((void*)instance);
		}
		catch (...)
		{
		}
	}
	//#################################################################################################################################
	static DWORD* GraphicImageGetTexturePointer(DWORD* instance)
	{
		try
		{
			return Globals::CGraphicImageGetTexturePointer((void*)instance);
		}
		catch (...)
		{
			return NULL;
		}
	}
	//#################################################################################################################################
	static DirectTexture GraphicTextureGetD3DTexture(DWORD* instance)
	{
		try
		{
			return Globals::CGraphicTextureGetD3DTexture((void*)instance);
		}
		catch (...)
		{
			return NULL;
		}
	}
};

