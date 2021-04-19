#include "stdafx.h"
#include "PacketHandler.h"

bool PacketHandler::CheckPacket(BYTE* header)
{
	RECV_HEADER_PACKET recv_header_packet;
	
	if (Network::Peek(sizeof(RECV_HEADER_PACKET), &recv_header_packet))
	{  
		if (Network::GetRecvBufferSize() < recv_header_packet.size)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	if (!Network::Peek(sizeof(BYTE), header))
	{
		return false;
	}

	if (header == (BYTE)HEADER_SEND_NULL)
	{
		return false;
		
	}
	return true;
}

bool PacketHandler::Process()
{
	BYTE header;
	if (!CheckPacket(&header))
	{
		return true;
	}

	switch (header)
	{
	case HEADER_RECV_NULL:
		return false;
	case HEADER_RECV_DLL_HEARTBEAT:
		return PacketHandler::RecvHeartBeatPacket();
	case HEADER_RECV_DLL_AUTH:
		return PacketHandler::RecvAuthPacket();
	default:
		return false;
	}
	
	return true;
}

bool PacketHandler::SendHeartBeatResponse()
{
	SEND_HEARTBEAT_PACKET send_heartbeat_packet;
	send_heartbeat_packet.header = HEADER_SEND_DLL_HEARTBEAT;
	send_heartbeat_packet.size = sizeof(SEND_HEARTBEAT_PACKET);

	if (!Network::Send(sizeof(SEND_HEARTBEAT_PACKET), &send_heartbeat_packet))
	{
		return false;
	}
	return true;
}

bool PacketHandler::RecvHeartBeatPacket()
{
	RECV_HEARTBEAT_PACKET recv_heartbeat_packet;
	if (!Network::Recv(sizeof(RECV_HEARTBEAT_PACKET), &recv_heartbeat_packet))
	{
		return false;
	}
	SendHeartBeatResponse();
	return true;
}

bool PacketHandler::SendAuthPacket()
{
	SEND_AUTH_PACKET send_auth_packet;
	send_auth_packet.header = HEADER_SEND_DLL_AUTH;
	send_auth_packet.size = sizeof(SEND_AUTH_PACKET);
	string hwid = GetHardwareId();
	strncpy(send_auth_packet.hwid, hwid.c_str(), 35);
	if (!Network::Send(sizeof(SEND_AUTH_PACKET), &send_auth_packet))
	{
		return false;
	}
	return true;
}

bool PacketHandler::AddressReceived = false;
bool PacketHandler::RecvAuthPacket()
{
	RECV_AUTH_PACKET recv_auth_packet;
	if (!Network::Recv(sizeof(RECV_AUTH_PACKET), &recv_auth_packet))
	{
		return false;
	}

	Globals::Server = (ServerName)recv_auth_packet.server_id;
	if (Globals::Server == ServerName::METINPL)
	{
		HANDLE process = GetCurrentProcess();
		MEMORY_BASIC_INFORMATION info;
		unsigned char* p = NULL;
		for (p = NULL; VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info); p += info.RegionSize)
		{
			if ((info.State == MEM_COMMIT) && ((info.Type & MEM_MAPPED) || (info.Type & MEM_PRIVATE)) && info.Protect == 0x40) {
				if (info.RegionSize >= 0x02000000) {
					Globals::hEntryBaseAddress = (DWORD)info.BaseAddress;
				}
			}
		}
	}
	else 
	{
		Globals::hEntryBaseAddress = (DWORD)GetModuleHandle(NULL);
	}
	Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamInstance;
	Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonCharacterManagerInstance;
	Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonBackgroundInstance;
	Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCItemManagerInstance;
	Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonItemInstance;
	Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonApplicationInstance;
	Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNonPlayerInstance;
	Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerInstance;
	Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + recv_auth_packet.pCResourceManagerInstance;
	Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + recv_auth_packet.pCActorInstanceTestActorCollision;
	Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonBackgroundGlobalPositionToMapInfo;
	Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseAvoidObject;
	Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseBlockMovement;
	Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseGetInstanceType;
	Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseGetInstanceVirtualNumber;
	Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseGetNameString;
	Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseGetRotation;
	Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseIsDead;
	Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseIsMountingHorse;
	Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseNEW_GetPixelPosition;
	Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseNEW_MoveToDestPixelPositionDirection;
	Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseSCRIPT_SetPixelPosition;
	Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBase__SetAffect;
	Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBase__GetBackgroundHeight;
	Globals::pCItemDataGetName = Globals::hEntryBaseAddress + recv_auth_packet.pCItemDataGetName;
	Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + recv_auth_packet.pCItemManagerGetItemDataPointer;
	Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonBackgroundLocalPositionToGlobalPosition;
	Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamConnect;
	Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStream__DirectEnterMode_Set;
	Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamGetAccountCharacterSlotDataz;
	Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamIsOnline;
	Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamPeek;
	Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamRecv;
	Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamSend;
	Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + recv_auth_packet.pCNetworkStreamSendSequence;
	Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + recv_auth_packet.pCPhysicsObjectIncreaseExternalForce;
	Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonApplicationProcess;
	Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonApplicationRenderGame;
	Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonCharacterManagerGetInstancePtr;
	Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonChatAppendChat;
	Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonEventManagerRegisterEventSetFromString;
	Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamConnectGameServer;
	Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamGetMainActorSkillGroup;
	Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendAddFlyTargetingPacket;
	Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendAttackPacket;
	Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendCharacterStatePacket;
	Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendChatPacket;
	Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendEmoticon;
	Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendExchangeAcceptPacket;
	Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendExchangeItemAddPacket;
	Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendExchangeStartPacket;
	Globals::pCPythonNetworkStreamSendFishingQuitPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendFishingQuitPacket;
	Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendFishingPacket;
	Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendGiveItemPacket;
	Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendItemDropPacketNew;
	Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendItemMovePacket;
	Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendItemPickUpPacket;
	Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendItemUsePacket;
	Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendOnClickPacket;
	Globals::pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendRefinePacket;
	Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendScriptAnswerPacket;
	Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendShootPacket;
	Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendShopBuyPacket;
	Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendShopEndPacket;
	Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendShopSellPacketNew;
	Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendSpecial;
	Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendUseSkillPacket;
	Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendWhisperPacket;
	Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamServerCommand;
	Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNonPlayerGetTable;
	Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerClickSkillSlot;
	Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetItemIndex;
	Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetItemMetinSocket;
	Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetMainCharacterIndex;
	Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetName;
	Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetRace;
	Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetStatus;
	Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerGetTargetVID;
	Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerIsSkillActive;
	Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerIsSkillCoolTime;
	Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerNEW_Fishing;
	Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerNEW_GetMainActorPtr;
	Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerSetAttackKeyState;
	Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayerSetTarget;
	Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayer__OnClickActor;
	Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonPlayer__OnPressActor;
	Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + recv_auth_packet.pPyCallClassMemberFunc;
	Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + recv_auth_packet.pCGraphicBasems_lpd3dDevice;
	Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + recv_auth_packet.pCInputKeyboardUpdateKeyboard;
	Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseIsWaiting;
	Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + recv_auth_packet.pCInstanceBaseSetRotation;
	Globals::pCPythonNetworkStreamSendCommandPacket = Globals::hEntryBaseAddress + recv_auth_packet.pCPythonNetworkStreamSendCommandPacket;

	AddressReceived = true;
	return true;
}