#pragma once

#define SET_NUMBERH(x)			( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)			( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)			( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)			( (WORD)((DWORD)(x) & 0xFFFF) )
#define SET_NUMBERHDW(x)		( (DWORD)((unsigned __int64)(x)>>(DWORD)32) )
#define SET_NUMBERLDW(x)		( (DWORD)((unsigned __int64)(x) & 0xFFFFFFFF) )
#define MAKE_NUMBERW(x,y)		( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERQW(x,y)		( (unsigned __int64)(((DWORD)((y)&0xFFFFFFFF)) | ((DWORD)((x)&0xFFFFFFFF)<<32))  )
#define MAKE_NUMBERDW(x,y)		( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
#define MAKEQWORD(a, b)			((__int64)(((DWORD)((__int64)(a) & 0xffffffff)) | ((__int64)((DWORD)((__int64)(b) & 0xffffffff))) << 32))  
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))   
#define HIDWORD(h)				((DWORD)(__int64(h) >> __int64(32)))

enum
{
	HEADER_SEND_NULL,
	HEADER_SEND_DLL_AUTH = 255,
	HEADER_SEND_DLL_HEARTBEAT = 254,
};

enum
{	
	HEADER_RECV_NULL,
	HEADER_RECV_DLL_AUTH = 255,
	HEADER_RECV_DLL_HEARTBEAT = 254,
};

#pragma pack(push, 1)
typedef struct RECV_AUTH_PACKET
{
	BYTE header;
	DWORD size;
	WORD  server_id;
	DWORD pCPythonNetworkStreamInstance;
	DWORD pCPythonCharacterManagerInstance;
	DWORD pCPythonBackgroundInstance;
	DWORD pCItemManagerInstance;
	DWORD pCPythonItemInstance;
	DWORD pCPythonApplicationInstance;
	DWORD pCPythonNonPlayerInstance;
	DWORD pCPythonPlayerInstance;
	DWORD pCResourceManagerInstance;
	DWORD pCActorInstanceTestActorCollision;
	DWORD pCPythonBackgroundGlobalPositionToMapInfo;
	DWORD pCInstanceBaseAvoidObject;
	DWORD pCInstanceBaseBlockMovement;
	DWORD pCInstanceBaseGetInstanceType;
	DWORD pCInstanceBaseGetInstanceVirtualNumber;
	DWORD pCInstanceBaseGetNameString;
	DWORD pCInstanceBaseGetRotation;
	DWORD pCInstanceBaseIsDead;
	DWORD pCInstanceBaseIsMountingHorse;
	DWORD pCInstanceBaseNEW_GetPixelPosition;
	DWORD pCInstanceBaseNEW_MoveToDestPixelPositionDirection;
	DWORD pCInstanceBaseSCRIPT_SetPixelPosition;
	DWORD pCInstanceBase__SetAffect;
	DWORD pCInstanceBase__GetBackgroundHeight;
	DWORD pCItemDataGetName;
	DWORD pCItemManagerGetItemDataPointer;
	DWORD pCPythonBackgroundLocalPositionToGlobalPosition;
	DWORD pCNetworkStreamConnect;
	DWORD pCNetworkStream__DirectEnterMode_Set;
	DWORD pCNetworkStreamGetAccountCharacterSlotDataz;
	DWORD pCNetworkStreamIsOnline;
	DWORD pCNetworkStreamPeek;
	DWORD pCNetworkStreamRecv;
	DWORD pCNetworkStreamSend;
	DWORD pCNetworkStreamSendSequence;
	DWORD pCPhysicsObjectIncreaseExternalForce;
	DWORD pCPythonApplicationProcess;
	DWORD pCPythonApplicationRenderGame;
	DWORD pCPythonCharacterManagerGetInstancePtr;
	DWORD pCPythonChatAppendChat;
	DWORD pCPythonEventManagerRegisterEventSetFromString;
	DWORD pCPythonNetworkStreamConnectGameServer;
	DWORD pCPythonNetworkStreamGetMainActorSkillGroup;
	DWORD pCPythonNetworkStreamSendAddFlyTargetingPacket;
	DWORD pCPythonNetworkStreamSendAttackPacket;
	DWORD pCPythonNetworkStreamSendCharacterStatePacket;
	DWORD pCPythonNetworkStreamSendChatPacket;
	DWORD pCPythonNetworkStreamSendEmoticon;
	DWORD pCPythonNetworkStreamSendExchangeAcceptPacket;
	DWORD pCPythonNetworkStreamSendExchangeItemAddPacket;
	DWORD pCPythonNetworkStreamSendExchangeStartPacket;
	DWORD pCPythonNetworkStreamSendFishingQuitPacket;
	DWORD pCPythonNetworkStreamSendFishingPacket;
	DWORD pCPythonNetworkStreamSendGiveItemPacket;
	DWORD pCPythonNetworkStreamSendItemDropPacketNew;
	DWORD pCPythonNetworkStreamSendItemMovePacket;
	DWORD pCPythonNetworkStreamSendItemPickUpPacket;
	DWORD pCPythonNetworkStreamSendItemUsePacket;
	DWORD pCPythonNetworkStreamSendOnClickPacket;
	DWORD pCPythonNetworkStreamSendRefinePacket;
	DWORD pCPythonNetworkStreamSendScriptAnswerPacket;
	DWORD pCPythonNetworkStreamSendShootPacket;
	DWORD pCPythonNetworkStreamSendShopBuyPacket;
	DWORD pCPythonNetworkStreamSendShopEndPacket;
	DWORD pCPythonNetworkStreamSendShopSellPacketNew;
	DWORD pCPythonNetworkStreamSendSpecial;
	DWORD pCPythonNetworkStreamSendUseSkillPacket;
	DWORD pCPythonNetworkStreamSendWhisperPacket;
	DWORD pCPythonNetworkStreamServerCommand;
	DWORD pCPythonNonPlayerGetTable;
	DWORD pCPythonPlayerClickSkillSlot;
	DWORD pCPythonPlayerGetItemIndex;
	DWORD pCPythonPlayerGetItemMetinSocket;
	DWORD pCPythonPlayerGetMainCharacterIndex;
	DWORD pCPythonPlayerGetName;
	DWORD pCPythonPlayerGetRace;
	DWORD pCPythonPlayerGetStatus;
	DWORD pCPythonPlayerGetTargetVID;
	DWORD pCPythonPlayerIsSkillActive;
	DWORD pCPythonPlayerIsSkillCoolTime;
	DWORD pCPythonPlayerNEW_Fishing;
	DWORD pCPythonPlayerNEW_GetMainActorPtr;
	DWORD pCPythonPlayerSetAttackKeyState;
	DWORD pCPythonPlayerSetTarget;
	DWORD pCPythonPlayer__OnClickActor;
	DWORD pCPythonPlayer__OnPressActor;
	DWORD pCGraphicTextureGetD3DTexture;
	DWORD pCResourceManagerGetResourcePointer;
	DWORD pCGraphicImageGetTexturePointer;
	DWORD pPyCallClassMemberFunc;
	DWORD pCGraphicBasems_lpd3dDevice;
	DWORD pCInputKeyboardUpdateKeyboard;
	DWORD pCInstanceBaseIsWaiting;
	DWORD pCInstanceBaseSetRotation;
	DWORD pCPythonNetworkStreamSendCommandPacket;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RECV_HEADER_PACKET
{
	BYTE header;
	DWORD size;
};

typedef struct SEND_AUTH_PACKET
{
	BYTE header;
	DWORD size;
	char hwid[35];
};

typedef struct SEND_HEARTBEAT_PACKET
{
	BYTE header;
	DWORD size;
};


typedef struct RECV_HEARTBEAT_PACKET
{
	BYTE header;
	DWORD size;
};
#pragma pack(pop)