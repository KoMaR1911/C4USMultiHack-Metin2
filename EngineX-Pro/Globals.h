
#pragma once
#include "xorstr.hpp"

class Globals
{
public:
	//######################################################################################################################################
	static ServerName Server;
	static bool UsePythonFunctions;

	static map<DWORD, TCItemData*> itemProtoList;
	static map<DWORD, const char*> itemProtoNames;
	static map<DWORD, TGroundItemInstance*> groundItemList;

	static DWORD hEntryBaseAddress;
	static DWORD hEntryBaseSize;
	static HMODULE hModule;
	static HWND mainHwnd;

	static vector<D3DVECTOR> farmCoords;


	static PyObject* m_apoPhaseWndGame;
	//###############################   PLAYER

	typedef int (*tPyRun_SimpleStringFlags)(const char* command, int flags);
	typedef char* (*tPyString_AsString)(PyObject* op);
	typedef long (*tPyInt_AsLong)(PyObject* op);
	typedef PyObject* (*tPyTuple_GetItem)(PyObject* op, Py_ssize_t i);
	typedef PyObject* (*tPy_BuildValue)(char* format, ...);

	typedef DWORD(__thiscall* tCPythonPlayerGetRace)(void* This);
	typedef bool(__thiscall* tCPythonPlayerIsSkillCoolTime)(void* This, DWORD dwSlotIndex);
	typedef int(__thiscall* tCPythonPlayerGetStatus)(void* This, DWORD dwType);
	typedef const char* (__thiscall* tCPythonPlayerGetName)(void* This);
	typedef void(__thiscall* tCPythonPlayerClickSkillSlot)(void* This, DWORD dwSlotIndex);
	typedef DWORD(__thiscall* tCPythonPlayerGetItemIndex)(void* This, TItemPos Cell);
	typedef DWORD(__thiscall* tCPythonPlayerGetItemMetinSocket)(void* This, TItemPos Cell, DWORD dwMetinSocketIndex);
	typedef void(__thiscall* tCPythonPlayerGetItemAttribute)(void* This, TItemPos Cell, DWORD dwAttrSlotIndex, BYTE* pbyType, short* psValue);

	typedef void(__thiscall* tCPythonPlayerReviveGlobal)(void* This, int a2, int a3, char* a4);


	typedef void(__thiscall* tCPythonPlayerSetAttackKeyState)(void* This, bool isPress);
	typedef DWORD* (__thiscall* tCPythonPlayerNEW_GetMainActorPtr)(void* This);
	typedef DWORD(__thiscall* tCPythonPlayerGetMainCharacterIndex)(void* This);
	typedef bool(__thiscall* tCPythonPlayerIsSkillActive)(void* This, DWORD dwSlotIndex);
	typedef void(__thiscall* tCPythonPlayerNEW_Fishing)(void* This);
	typedef DWORD(__thiscall* tCPythonPlayerGetTargetVID)(void* This);
	typedef void(__thiscall* tCPythonPlayer__OnClickActor)(void* This, DWORD* rkInstMain, DWORD dwPickedActorID, bool isAuto);
	typedef void(__thiscall* tCPythonPlayer__OnPressActor)(void* This, DWORD* rkInstMain, DWORD dwPickedActorID, bool isAuto);
	typedef void(__thiscall* tCPythonPlayerNEW_SetSingleDIKKeyState)(void* This, int eDIKKey, bool isPress);
	typedef void(__thiscall* tCPythonPlayerSetTarget)(void* This, DWORD dwVID, BOOL bForceChange);

	//############################### NETWORK

	typedef DWORD(__thiscall* tCPythonNetworkStreamGetMainActorSkillGroup)(void* This);
	typedef bool(__thiscall* tCNetworkStreamSendSequence)(void* This);
	/*typedef bool(__thiscall* tCNetworkStreamPeek)(void* This, int len, void* pDestBuf);*/
	typedef bool(__thiscall* tCNetworkStreamRecv)(void* This, int len, void* pDestBuf);

	typedef bool(__thiscall* tCNetworkStreamSend)(void* This, int len, void* pDestBuf);
	//typedef bool(__thiscall* tCNetworkStreamSendAeldra)(void* This, int len, void* pDestBuf, bool instant);
	typedef int(__stdcall* tCNetworkStreamSendAeldra)(SOCKET s, const char* pDestBuf, int len, int flags);
	typedef bool(__thiscall* tCNetworkStreamCheckPacket)(void* This, BYTE* header);

	typedef bool(__thiscall* tCNetworkStreamIsOnline)(void* This);

	typedef void(__thiscall* tCPythonNetworkStreamConnectGameServer)(void* This, UINT iChrSlot);

	typedef bool(__thiscall* tCPythonNetworkStreamSendItemUsePacket)(void* This, TItemPos pos);
	typedef bool(__thiscall* tCPythonNetworkStreamSendItemUseToItemPacket)(void* This, TItemPos pos, TItemPos target_pos);
	typedef bool(__thiscall* tCNetworkStreamConnect)(void* This, DWORD dwAddr, int port, int limitSec);
	typedef void(__thiscall* tCNetworkStream__DirectEnterMode_Set)(void* This, UINT uChrSlotIndex);
	typedef bool(__thiscall* tCPythonNetworkStreamSendItemDropPacketNew)(void* This, TItemPos pos, DWORD elk, DWORD count);
	typedef bool(__thiscall* tCPythonNetworkStreamSendChatPacket)(void* This, const char* c_szChat, BYTE byType);
	typedef bool(__thiscall* tCPythonNetworkStreamSendFishingPacket)(void* This, int iRotation);
	typedef bool(__thiscall* tCPythonNetworkStreamSendFishingQuitPacket)(void* This, int count, float iRotation);
	typedef bool(__thiscall* tCPythonNetworkStreamSendEmoticon)(void* This, BYTE emoticon);
	typedef bool(__thiscall* tCPythonNetworkStreamSendExchangeStartPacket)(void* This, DWORD vid);
	typedef bool(__thiscall* tCPythonNetworkStreamSendExchangeItemAddPacket)(void* This, TItemPos ItemPos, BYTE byDisplayPos);
	typedef bool(__thiscall* tCPythonNetworkStreamSendExchangeAcceptPacket)(void* This);
	typedef bool(__thiscall* tCPythonNetworkStreamSendUseSkillPacket)(void* This, DWORD dwSkillIndex, DWORD dwTargetVID);
	typedef bool(__thiscall* tCPythonNetworkStreamSendAddFlyTargetingPacket)(void* This, DWORD dwTargetVID, D3DVECTOR& kPPosTarget);
	typedef bool(__thiscall* tCPythonNetworkStreamSendShootPacket)(void* This, UINT uSkill);
	typedef bool(__thiscall* tCPythonNetworkStreamSendItemPickUpPacket)(void* This, DWORD vid);
	typedef bool(__thiscall* tCPythonNetworkStreamSendScriptAnswerPacket)(void* This, int iAnswer);
	typedef bool(__thiscall* tCPythonNetworkStreamSendOnClickPacket)(void* This, DWORD vid);
	typedef bool(__thiscall* tCPythonNetworkStreamSendWhisperPacket)(void* This, const char* name, const char* c_szChat);
	typedef bool(__thiscall* tCPythonNetworkStreamSendSpecial)(void* This, int nLen, void* pvBuf);
	typedef bool(__thiscall* tCPythonNetworkStreamSendAttackPacket)(void* This, UINT uMotAttack, DWORD dwVIDVictim);
	typedef bool(__thiscall* tCPythonNetworkStreamSendShopSellPacketNew)(void* This, BYTE bySlot, WORD byCount);
	typedef bool(__thiscall* tCPythonNetworkStreamSendShopBuyPacket)(void* This, BYTE bPos);
	typedef bool(__thiscall* tCPythonNetworkStreamSendShopEndPacket)(void* This);


	typedef bool(__thiscall* tCPythonNetworkStreamSendRefinePacket)(void* This, BYTE byPos, BYTE byType);
	typedef bool(__thiscall* tCPythonNetworkStreamSendItemMovePacket)(void* This, TItemPos pos, TItemPos change_pos, BYTE num);


	typedef bool(__thiscall* tCPythonNetworkStreamSendCharacterStatePacket)(void* This, const D3DVECTOR& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg);

	typedef void(__thiscall* tCPythonNetworkStreamServerCommand)(void* This, const char* c_szCommand);

	typedef bool(__thiscall* tCPythonNetworkStreamSendGiveItemPacket)(void* This, DWORD dwTargetVID, TItemPos ItemPos, int iItemCount);
	//############################### INSTANCE
	typedef bool(__thiscall* tCInstanceBaseIsMountingHorse)(void* This);
	typedef void(__thiscall* tCInstanceBaseNEW_GetPixelPosition)(DWORD* instance, D3DVECTOR* pPixelPosition);
	typedef bool(__thiscall* tCInstanceBaseNEW_MoveToDestPixelPositionDirection)(DWORD* instance, D3DVECTOR& c_rkPPosDst);

	typedef const char* (__thiscall* tCInstanceBaseGetNameString)(void* This);
	typedef int(__thiscall* tCInstanceBaseGetInstanceType)(void* This);


	typedef void(__thiscall* tCInstanceBaseBlockMovement)(void* This);

	typedef void(__thiscall* tCInstanceBase__SetAffect)(void* This, UINT eAffect, bool isVisible);
	typedef bool(__thiscall* tCInstanceBaseIsDead)(void* This);
	typedef bool(__thiscall* tCInstanceBaseAvoidObject)(void* This, const DWORD* c_rkBGObj);
	typedef bool(__thiscall* tCActorInstanceTestActorCollision)(void* This, DWORD* rVictim);
	typedef void(__thiscall* tCInstanceBaseSCRIPT_SetPixelPosition)(void* This, float fx, float fy);
	typedef void(__thiscall* tCInstanceBaseNEW_LookAtDestPixelPosition)(void* This, const D3DVECTOR& c_rkPPosDst);
	typedef int(__thiscall* tCInstanceBaseGetInstanceVirtualNumber)(void* This);

	typedef float(__thiscall* tCInstanceBaseGetRotation)(void* This);
	//############################### CHARACTER MANAGER
	typedef DWORD* (__thiscall* tCPythonCharacterManagerGetInstancePtr)(void* This, DWORD VirtualID);

	//############################### CHARACTER MANAGER

	typedef void(__thiscall* tCPhysicsObjectIncreaseExternalForce)(void* This, const D3DVECTOR& c_rvBasePosition, float fForce);

	typedef const char* (__thiscall* tCItemDataGetName)(void* This);

	typedef bool(__thiscall* tCItemManagerGetItemDataPointer)(void* This, DWORD dwItemID, DWORD** ppItemData);

	typedef bool(__cdecl* tPyCallClassMemberFunc)(PyObject* poClass, const char* c_szFunc, PyObject* poArgs);

	typedef void(__thiscall* tCPythonChatAppendChat)(void* This, int iType, const char* c_szChat);

	typedef void(__thiscall* tCPythonApplicationRenderGame)(void* This);
	typedef bool(__thiscall* tCPythonApplicationProcess)(void* This);

	typedef int(__thiscall* tCPythonEventManagerRegisterEventSetFromString)(void* This, const string& strScript);
	typedef void(__thiscall* tCTerrainLoadMiniMapTexture)(void* This, const char* c_pchMiniMapFileName);
	typedef DWORD* (__thiscall* tCPythonNonPlayerGetTable)(void* This, int vid);


	typedef void(__thiscall* tCPythonBackgroundLocalPositionToGlobalPosition)(void* This, LONG& rLocalX, LONG& rLocalY);
	typedef TMapInfo* (__thiscall* tCPythonBackgroundGlobalPositionToMapInfo)(void* This, DWORD dwGlobalX, DWORD dwGlobalY);
	typedef const char* (__thiscall* tCNetworkStreamGetAccountCharacterSlotDataz)(void* This, UINT iSlot, UINT eType);
	typedef void(__thiscall* tCInputKeyboardUpdateKeyboard)(void* This);



	typedef bool(__thiscall* tCInstanceBaseIsWaiting)(void* This);
	typedef void(__thiscall* tCInstanceBaseSetRotation)(void* This, float fRotation);
	typedef bool(__thiscall* tCPythonNetworkStreamSendCommandPacket)(void* This, DWORD a1, DWORD a2, const char* a3);
	typedef float(__cdecl* tCInstanceBase__GetBackgroundHeight)(float x, float y);

	typedef HRESULT(__stdcall* tDirectEndScene)(void* pDevice);
	typedef HRESULT(__stdcall* tDirectReset)(void* pDevice, D3DPRESENT_PARAMETERS* ppReset);

	typedef DWORD(__thiscall* tCPythonPlayerGetItemCount)(void* This, TItemPos Cell);

	typedef DWORD* (__thiscall* tCResourceManagerGetResourcePointer)(void* This, const char* c_szFileName);
	typedef DWORD* (__thiscall* tCResourceManagerGetTexturePointer)(void* This);
	typedef DirectTexture(__thiscall* tCResourceManagerGetD3DTexture)(void* This);
	typedef void(__thiscall* tCResourceReload)(void* This);

	static DWORD iCPythonApplicationInstance;
	static DWORD iCPythonBackgroundInstance;
	static DWORD iCPythonCharacterManagerInstance;
	static DWORD iCPythonItemInstance;
	static DWORD iCPythonNetworkStreamInstance;
	static DWORD iCPythonNonPlayerInstance;
	static DWORD iCPythonPlayerInstance;
	static DWORD iCResourceManagerInstance;
	static DWORD iCItemManagerInstance;

	static DWORD pCPythonCharacterManagerInstance;
	static DWORD pCPythonBackgroundInstance;
	static DWORD pCPythonItemInstance;
	static DWORD pCPythonApplicationInstance;
	static DWORD pCPythonNetworkStreamInstance;
	static DWORD pCItemManagerInstance;
	static DWORD pCResourceManagerInstance;
	static DWORD pCPythonNonPlayerInstance;




	static DWORD pCActorInstanceTestActorCollision;

	static DWORD pCPythonBackgroundGlobalPositionToMapInfo;
	static DWORD pCPythonBackgroundLocalPositionToGlobalPosition;

	static DWORD pCInstanceBaseAvoidObject;
	static DWORD pCInstanceBaseBlockMovement;
	static DWORD pCInstanceBaseGetInstanceType;
	static DWORD pCInstanceBaseGetInstanceVirtualNumber;
	static DWORD pCInstanceBaseGetNameString;
	static DWORD pCInstanceBaseGetRotation;
	static DWORD pCInstanceBaseIsDead;
	static DWORD pCInstanceBaseIsMountingHorse;
	static DWORD pCInstanceBaseNEW_GetPixelPosition;
	static DWORD pCInstanceBaseNEW_LookAtDestPixelPosition;
	static DWORD pCInstanceBaseNEW_MoveToDestPixelPositionDirection;
	static DWORD pCInstanceBaseSCRIPT_SetPixelPosition;
	static DWORD pCInstanceBase__SetAffect;
	static DWORD pCItemDataGetName;
	static DWORD pCItemManagerGetItemDataPointer;



	static DWORD pCNetworkStreamConnect;
	static DWORD pCNetworkStream__DirectEnterMode_Set;
	static DWORD pCNetworkStreamGetAccountCharacterSlotDataz;
	static DWORD pCNetworkStreamIsOnline;
	static DWORD pCNetworkStreamPeek;
	static DWORD pCNetworkStreamRecv;
	static DWORD pCNetworkStreamSend;
	static DWORD pCNetworkStreamSendSequence;

	static DWORD pCPhysicsObjectIncreaseExternalForce;



	static DWORD pCPythonApplicationProcess;
	static DWORD pCPythonApplicationRenderGame;


	static DWORD pCPythonCharacterManagerGetInstancePtr;
	static DWORD pCPythonChatAppendChat;
	static DWORD pCPythonEventManagerRegisterEventSetFromString;

	static DWORD pCPythonNetworkStreamConnectGameServer;
	static DWORD pCPythonNetworkStreamGetMainActorSkillGroup;

	static DWORD pCPythonNetworkStreamSendAddFlyTargetingPacket;
	static DWORD pCPythonNetworkStreamSendAttackPacket;
	static DWORD pCPythonNetworkStreamSendCharacterStatePacket;
	static DWORD pCPythonNetworkStreamSendChatPacket;
	static DWORD pCPythonNetworkStreamSendEmoticon;
	static DWORD pCPythonNetworkStreamSendExchangeAcceptPacket;
	static DWORD pCPythonNetworkStreamSendExchangeItemAddPacket;
	static DWORD pCPythonNetworkStreamSendExchangeStartPacket;
	static DWORD pCPythonNetworkStreamSendFishingQuitPacket;
	static DWORD pCPythonNetworkStreamSendFishingPacket;
	static DWORD pCPythonNetworkStreamSendGiveItemPacket;
	static DWORD pCPythonNetworkStreamSendItemDropPacketNew;
	static DWORD pCPythonNetworkStreamSendItemMovePacket;
	static DWORD pCPythonNetworkStreamSendItemPickUpPacket;
	static DWORD pCPythonNetworkStreamSendItemUsePacket;
	static DWORD pCPythonNetworkStreamSendItemUseToItemPacket;
	static DWORD pCPythonNetworkStreamSendOnClickPacket;
	static DWORD pCPythonNetworkStreamSendRefinePacket;
	static DWORD pCPythonNetworkStreamSendScriptAnswerPacket;
	static DWORD pCPythonNetworkStreamSendShootPacket;
	static DWORD pCPythonNetworkStreamSendShopBuyPacket;
	static DWORD pCPythonNetworkStreamSendShopEndPacket;
	static DWORD pCPythonNetworkStreamSendShopSellPacketNew;
	static DWORD pCPythonNetworkStreamSendSpecial;
	static DWORD pCPythonNetworkStreamSendUseSkillPacket;
	static DWORD pCPythonNetworkStreamSendWhisperPacket;
	static DWORD pCPythonNetworkStreamServerCommand;
	static DWORD pCPythonNonPlayerGetTable;


	static DWORD pCPythonPlayerReviveGlobal;
	static DWORD pCPythonPlayerClickSkillSlot;
	static DWORD pCPythonPlayerGetItemIndex;
	static DWORD pCPythonPlayerGetItemMetinSocket;
	static DWORD pCPythonPlayerGetItemAttribute;
	static DWORD pCPythonPlayerGetMainCharacterIndex;
	static DWORD pCPythonPlayerGetName;
	static DWORD pCPythonPlayerGetRace;
	static DWORD pCPythonPlayerGetStatus;
	static DWORD pCPythonPlayerGetTargetVID;
	static DWORD pCPythonPlayerInstance;
	static DWORD pCPythonPlayerIsSkillActive;
	static DWORD pCPythonPlayerIsSkillCoolTime;
	static DWORD pCPythonPlayerNEW_Fishing;
	static DWORD pCPythonPlayerNEW_GetMainActorPtr;
	static DWORD pCPythonPlayerNEW_SetSingleDIKKeyState;
	static DWORD pCPythonPlayerSetAttackKeyState;
	static DWORD pCPythonPlayerSetTarget;
	static DWORD pCPythonPlayer__OnClickActor;
	static DWORD pCPythonPlayer__OnPressActor;


	static DWORD pPyCallClassMemberFunc;
	static DWORD pCGraphicBasems_lpd3dDevice;
	static DWORD pCInputKeyboardUpdateKeyboard;
	//####################################
	static DWORD pCInstanceBaseIsWaiting;
	static DWORD pCInstanceBaseSetRotation;
	static DWORD pCPythonNetworkStreamSendCommandPacket;
	static DWORD pCInstanceBase__GetBackgroundHeight;
	static DWORD pCPythonPlayerGetItemCount;
	static DWORD pCGraphicTextureGetD3DTexture;
	static DWORD pCResourceManagerGetResourcePointer;
	static DWORD pCGraphicImageGetTexturePointer;
	static DWORD pCResourceReload;
	//python only
	//player
	static DWORD CythonPlayerGetStatus;
	static DWORD CythonPlayerGetMainCharacterIndex;
	static DWORD CythonPlayerGetItemIndex;
	static DWORD CythonPlayerGetItemCount;
	static DWORD CythonPlayerGetName;
	static DWORD CythonPlayerGetItemMetinSocket;
	static DWORD CythonPlayerGetRace;
	static DWORD CythonPlayerSetSingleDIKKeyState;
	static DWORD CythonPlayerClickSkillSlot;
	static DWORD CythonPlayerIsSkillCoolTime;
	static DWORD CythonPlayerIsSkillActive;
	static DWORD CythonPlayerGetTargetVID;
	static DWORD CythonPlayerSetTarget;
	static DWORD CythonPlayerSetAttackKeyState;
	static DWORD CythonPlayerIsMountingHorse;
	//chr
	static DWORD CythonChrSelectInstance;
	static DWORD CythonChrGetPixelPosition;
	static DWORD CythonChrMoveToDestPosition;
	static DWORD CythonChrGetInstanceType;
	static DWORD CythonChrGetVirtualNumber;
	static DWORD CythonChrGetNameByVID;
	static DWORD CythonChrSetPixelPosition;
	static DWORD CythonChrSetRotation;
	static DWORD CythonChrGetRotation;
	static DWORD CythonChrmgrSetAffect;
	//net
	static DWORD CythonNetSendItemUsePacket;
	static DWORD CythonNetSendChatPacket;
	static DWORD CythonNetSendRefinePacket;
	static DWORD CythonNetSendExchangeStartPacket;
	static DWORD CythonNetSendExchangeItemAddPacket;
	static DWORD CythonNetSendExchangeAcceptPacket;
	static DWORD CythonNetSendWhisperPacket;
	static DWORD CythonNetSendItemPickUpPacket;
	static DWORD CythonNetSendItemDropPacketNew;
	static DWORD CythonNetSendOnClickPacket;
	static DWORD CythonNetSendShopSellPacketNew;
	static DWORD CythonNetSendShopBuyPacket;
	static DWORD CythonNetSendShopEndPacket;
	static DWORD CythonNetSendGiveItemPacket;
	static DWORD CythonNetSendItemMovePacket;
	static DWORD CythonNetDirectEnter;
	static DWORD CythonNetConnectTCP;
	static DWORD CythonNetIsConnect;
	static DWORD CythonNetGetMainActorSkillGroup;
	static DWORD CythonNetGetAccountCharacterSlotData;
	static DWORD CythonNetSendCommandPacket;
	static DWORD CythonEventSelectAnswer;
	//item
	static DWORD CythonItemSelectItem;
	static DWORD CythonItemGetItemName;
public:
	//#####################################################################################################################################
	/*static tCNetworkStreamPeek CNetworkStreamPeek;*/

	static tCActorInstanceTestActorCollision CActorInstanceTestActorCollision;
	static tCPythonBackgroundGlobalPositionToMapInfo CPythonBackgroundGlobalPositionToMapInfo;
	static tCInstanceBaseAvoidObject CInstanceBaseAvoidObject;
	static tCInstanceBaseBlockMovement CInstanceBaseBlockMovement;
	static tCInstanceBaseGetInstanceType CInstanceBaseGetInstanceType;
	static tCInstanceBaseGetInstanceVirtualNumber CInstanceBaseGetInstanceVirtualNumber;
	static tCInstanceBaseGetNameString CInstanceBaseGetNameString;
	static tCInstanceBaseGetRotation CInstanceBaseGetRotation;
	static tCInstanceBaseIsDead CInstanceBaseIsDead;
	static tCInstanceBaseIsMountingHorse CInstanceBaseIsMountingHorse;
	static tCInstanceBaseNEW_GetPixelPosition CInstanceBaseNEW_GetPixelPosition;
	static tCInstanceBaseNEW_LookAtDestPixelPosition CInstanceBaseNEW_LookAtDestPixelPosition;
	static tCInstanceBaseNEW_MoveToDestPixelPositionDirection CInstanceBaseNEW_MoveToDestPixelPositionDirection;
	static tCInstanceBaseSCRIPT_SetPixelPosition CInstanceBaseSCRIPT_SetPixelPosition;
	static tCInstanceBase__SetAffect CInstanceBase__SetAffect;
	static tCItemManagerGetItemDataPointer CItemManagerGetItemDataPointer;
	static tCPythonBackgroundLocalPositionToGlobalPosition CPythonBackgroundLocalPositionToGlobalPosition;
	static tCNetworkStreamConnect CNetworkStreamConnect;
	static tCNetworkStream__DirectEnterMode_Set CNetworkStream__DirectEnterMode_Set;
	static tCNetworkStreamGetAccountCharacterSlotDataz CNetworkStreamGetAccountCharacterSlotDataz;
	static tCNetworkStreamIsOnline CNetworkStreamIsOnline;
	static tCNetworkStreamRecv CNetworkStreamRecv;
	static tCNetworkStreamSend CNetworkStreamSend;
	static tCNetworkStreamSendSequence CNetworkStreamSendSequence;
	static tCPhysicsObjectIncreaseExternalForce CPhysicsObjectIncreaseExternalForce;
	static tCPythonPlayerReviveGlobal CPythonPlayerReviveGlobal;
	static tCPythonApplicationProcess CPythonApplicationProcess;
	static tCPythonApplicationRenderGame CPythonApplicationRenderGame;
	static tCPythonCharacterManagerGetInstancePtr CPythonCharacterManagerGetInstancePtr;
	static tCPythonChatAppendChat CPythonChatAppendChat;
	static tCPythonEventManagerRegisterEventSetFromString CPythonEventManagerRegisterEventSetFromString;
	static tCPythonNetworkStreamConnectGameServer CPythonNetworkStreamConnectGameServer;
	static tCPythonNetworkStreamGetMainActorSkillGroup CPythonNetworkStreamGetMainActorSkillGroup;
	static tCPythonNetworkStreamSendAddFlyTargetingPacket CPythonNetworkStreamSendAddFlyTargetingPacket;
	static tCPythonNetworkStreamSendAttackPacket CPythonNetworkStreamSendAttackPacket;
	static tCPythonNetworkStreamSendCharacterStatePacket CPythonNetworkStreamSendCharacterStatePacket;
	static tCPythonNetworkStreamSendChatPacket CPythonNetworkStreamSendChatPacket;
	static tCPythonNetworkStreamSendEmoticon CPythonNetworkStreamSendEmoticon;
	static tCPythonNetworkStreamSendExchangeAcceptPacket CPythonNetworkStreamSendExchangeAcceptPacket;
	static tCPythonNetworkStreamSendExchangeItemAddPacket CPythonNetworkStreamSendExchangeItemAddPacket;
	static tCPythonNetworkStreamSendExchangeStartPacket CPythonNetworkStreamSendExchangeStartPacket;
	static tCPythonNetworkStreamSendFishingQuitPacket CPythonNetworkStreamSendFishingQuitPacket;
	static tCPythonNetworkStreamSendFishingPacket CPythonNetworkStreamSendFishingPacket;
	static tCPythonNetworkStreamSendGiveItemPacket CPythonNetworkStreamSendGiveItemPacket;
	static tCPythonNetworkStreamSendItemDropPacketNew CPythonNetworkStreamSendItemDropPacketNew;
	static tCPythonNetworkStreamSendItemMovePacket CPythonNetworkStreamSendItemMovePacket;
	static tCPythonNetworkStreamSendItemPickUpPacket CPythonNetworkStreamSendItemPickUpPacket;
	static tCPythonNetworkStreamSendItemUsePacket CPythonNetworkStreamSendItemUsePacket;
	static tCPythonNetworkStreamSendItemUseToItemPacket CPythonNetworkStreamSendItemUseToItemPacket;
	static tCPythonNetworkStreamSendOnClickPacket CPythonNetworkStreamSendOnClickPacket;
	static tCPythonNetworkStreamSendRefinePacket CPythonNetworkStreamSendRefinePacket;
	static tCPythonNetworkStreamSendScriptAnswerPacket CPythonNetworkStreamSendScriptAnswerPacket;
	static tCPythonNetworkStreamSendShootPacket CPythonNetworkStreamSendShootPacket;
	static tCPythonNetworkStreamSendShopBuyPacket CPythonNetworkStreamSendShopBuyPacket;
	static tCPythonNetworkStreamSendShopEndPacket CPythonNetworkStreamSendShopEndPacket;
	static tCPythonNetworkStreamSendShopSellPacketNew CPythonNetworkStreamSendShopSellPacketNew;
	static tCPythonNetworkStreamSendSpecial CPythonNetworkStreamSendSpecial;
	static tCPythonNetworkStreamSendUseSkillPacket CPythonNetworkStreamSendUseSkillPacket;
	static tCPythonNetworkStreamSendWhisperPacket CPythonNetworkStreamSendWhisperPacket;
	static tCPythonNetworkStreamServerCommand CPythonNetworkStreamServerCommand;
	static tCPythonNonPlayerGetTable CPythonNonPlayerGetTable;
	static tCPythonPlayerClickSkillSlot CPythonPlayerClickSkillSlot;
	static tCPythonPlayerGetName CPythonPlayerGetName;
	static tCPythonPlayerGetItemIndex CPythonPlayerGetItemIndex;
	static tCPythonPlayerGetItemMetinSocket CPythonPlayerGetItemMetinSocket;
	static tCPythonPlayerGetItemAttribute CPythonPlayerGetItemAttribute;
	static tCPythonPlayerGetMainCharacterIndex CPythonPlayerGetMainCharacterIndex;
	static tCPythonPlayerGetRace CPythonPlayerGetRace;
	static tCPythonPlayerGetStatus CPythonPlayerGetStatus;
	static tCPythonPlayerGetTargetVID CPythonPlayerGetTargetVID;
	static tCPythonPlayerIsSkillActive CPythonPlayerIsSkillActive;
	static tCPythonPlayerIsSkillCoolTime CPythonPlayerIsSkillCoolTime;
	static tCPythonPlayerNEW_Fishing CPythonPlayerNEW_Fishing;
	static tCPythonPlayerNEW_GetMainActorPtr CPythonPlayerNEW_GetMainActorPtr;
	static tCPythonPlayerNEW_SetSingleDIKKeyState CPythonPlayerNEW_SetSingleDIKKeyState;
	static tCPythonPlayerSetAttackKeyState CPythonPlayerSetAttackKeyState;
	static tCPythonPlayerSetTarget CPythonPlayerSetTarget;
	static tCPythonPlayer__OnClickActor CPythonPlayer__OnClickActor;
	static tCPythonPlayer__OnPressActor CPythonPlayer__OnPressActor;
	static tCTerrainLoadMiniMapTexture CTerrainLoadMiniMapTexture;
	static tPyCallClassMemberFunc PyCallClassMemberFunc;
	static tCInputKeyboardUpdateKeyboard CInputKeyboardUpdateKeyboard;
	static tCInstanceBaseIsWaiting CInstanceBaseIsWaiting;
	static tCInstanceBaseSetRotation CInstanceBaseSetRotation;
	static tCPythonNetworkStreamSendCommandPacket CPythonNetworkStreamSendCommandPacket;
	static tCInstanceBase__GetBackgroundHeight CInstanceBase__GetBackgroundHeight;
	static tCItemDataGetName CItemDataGetName;
	static tCPythonPlayerGetItemCount CPythonPlayerGetItemCount;
	static tCResourceManagerGetD3DTexture CGraphicTextureGetD3DTexture;
	static tCResourceManagerGetResourcePointer CResourceManagerGetResourcePointer;
	static tCResourceManagerGetTexturePointer CGraphicImageGetTexturePointer;
	static tCResourceReload CResourceReload;
	//#####################################################################################################################################

	static tPyRun_SimpleStringFlags PyRun_SimpleStringFlags;
	static tPyString_AsString PyString_AsString;
	static tPyTuple_GetItem PyTuple_GetItem;
	static tPyInt_AsLong PyInt_AsLong;
	static tPy_BuildValue Py_BuildValue;

	static void ReAddressingInstances();
	static void ReDeclarationInstances();
	static void ReAddressingLocas();
	static void ReDeclarationLocals();

	static void ReAddressingPython();
};
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


ServerName Globals::Server = SERVER;
bool Globals::UsePythonFunctions = false;

map<DWORD, TCItemData*> Globals::itemProtoList;
map<DWORD, TGroundItemInstance*> Globals::groundItemList;
map<DWORD, const char*>  Globals::itemProtoNames;

HMODULE	Globals::hModule = NULL;
DWORD	Globals::hEntryBaseAddress = (DWORD)GetModuleHandle(NULL);
DWORD	Globals::hEntryBaseSize = 0;

HWND Globals::mainHwnd;

vector<D3DVECTOR> Globals::farmCoords;



PyObject* Globals::m_apoPhaseWndGame = NULL;




///###################################################################################################################################################
DWORD Globals::iCItemManagerInstance = NULL;
DWORD Globals::iCPythonItemInstance = NULL;
DWORD Globals::iCPythonApplicationInstance = NULL;
DWORD Globals::iCPythonCharacterManagerInstance = NULL;
DWORD Globals::iCPythonNetworkStreamInstance = NULL;
DWORD Globals::iCPythonPlayerInstance = NULL;
DWORD Globals::iCPythonNonPlayerInstance = NULL;
DWORD Globals::iCPythonBackgroundInstance = NULL;
DWORD Globals::iCResourceManagerInstance = NULL;





//#####################################################################################################################################

DWORD Globals::pCPythonNetworkStreamInstance = NULL;
DWORD Globals::pCPythonBackgroundInstance = NULL;
DWORD Globals::pCItemManagerInstance = NULL;
DWORD Globals::pCPythonItemInstance = NULL;
DWORD Globals::pCPythonApplicationInstance = NULL;
DWORD Globals::pCPythonCharacterManagerInstance = NULL;
DWORD Globals::pCPythonNonPlayerInstance = NULL;
DWORD Globals::pCPythonPlayerInstance = NULL;
DWORD Globals::pCResourceManagerInstance = NULL;

DWORD Globals::pCActorInstanceTestActorCollision = NULL;
DWORD Globals::pCPythonBackgroundGlobalPositionToMapInfo = NULL;
DWORD Globals::pCInstanceBaseAvoidObject = NULL;
DWORD Globals::pCInstanceBaseBlockMovement = NULL;
DWORD Globals::pCInstanceBaseGetInstanceType = NULL;
DWORD Globals::pCInstanceBaseGetInstanceVirtualNumber = NULL;
DWORD Globals::pCInstanceBaseGetNameString = NULL;
DWORD Globals::pCInstanceBaseGetRotation = NULL;
DWORD Globals::pCInstanceBaseIsDead = NULL;
DWORD Globals::pCInstanceBaseIsMountingHorse = NULL;

DWORD Globals::pCInstanceBaseNEW_GetPixelPosition = NULL;
DWORD Globals::pCInstanceBaseNEW_LookAtDestPixelPosition = NULL;;
DWORD Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = NULL;
DWORD Globals::pCInstanceBaseSCRIPT_SetPixelPosition = NULL;;
DWORD Globals::pCInstanceBase__SetAffect = NULL;
DWORD Globals::pCItemDataGetName = NULL;
DWORD Globals::pCItemManagerGetItemDataPointer = NULL;

DWORD Globals::pCPythonBackgroundLocalPositionToGlobalPosition = NULL;
DWORD Globals::pCNetworkStreamConnect = NULL;
DWORD Globals::pCNetworkStream__DirectEnterMode_Set = NULL;
DWORD Globals::pCNetworkStreamGetAccountCharacterSlotDataz = NULL;
DWORD Globals::pCNetworkStreamIsOnline = NULL;
DWORD Globals::pCNetworkStreamPeek = NULL;
DWORD Globals::pCNetworkStreamRecv = NULL;
DWORD Globals::pCNetworkStreamSend = NULL;
DWORD Globals::pCNetworkStreamSendSequence = NULL;
DWORD Globals::pCPhysicsObjectIncreaseExternalForce = NULL;
DWORD Globals::pCPythonPlayerReviveGlobal = NULL;
DWORD Globals::pCPythonApplicationProcess = NULL;
DWORD Globals::pCPythonApplicationRenderGame = NULL;

DWORD Globals::pCPythonCharacterManagerGetInstancePtr = NULL;
DWORD Globals::pCPythonChatAppendChat = NULL;
DWORD Globals::pCPythonEventManagerRegisterEventSetFromString = NULL;;

DWORD Globals::pCPythonNetworkStreamConnectGameServer = NULL;
DWORD Globals::pCPythonNetworkStreamGetMainActorSkillGroup = NULL;

DWORD Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendAttackPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendCharacterStatePacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendChatPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendEmoticon = NULL;
DWORD Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendExchangeStartPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendFishingQuitPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendFishingPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendGiveItemPacket = NULL;;
DWORD Globals::pCPythonNetworkStreamSendItemDropPacketNew = NULL;
DWORD Globals::pCPythonNetworkStreamSendItemMovePacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendItemPickUpPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendItemUsePacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendItemUseToItemPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendOnClickPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendRefinePacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendScriptAnswerPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendShootPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendShopBuyPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendShopEndPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendShopSellPacketNew = NULL;
DWORD Globals::pCPythonNetworkStreamSendSpecial = NULL;;
DWORD Globals::pCPythonNetworkStreamSendUseSkillPacket = NULL;
DWORD Globals::pCPythonNetworkStreamSendWhisperPacket = NULL;;
DWORD Globals::pCPythonNetworkStreamServerCommand = NULL;
DWORD Globals::pCPythonNonPlayerGetTable = NULL;
DWORD Globals::pCPythonPlayerClickSkillSlot = NULL;
DWORD Globals::pCPythonPlayerGetItemIndex = NULL;
DWORD Globals::pCPythonPlayerGetItemMetinSocket = NULL;
DWORD Globals::pCPythonPlayerGetItemAttribute = NULL;
DWORD Globals::pCPythonPlayerGetMainCharacterIndex = NULL;
DWORD Globals::pCPythonPlayerGetName = NULL;
DWORD Globals::pCPythonPlayerGetRace = NULL;
DWORD Globals::pCPythonPlayerGetStatus = NULL;
DWORD Globals::pCPythonPlayerGetTargetVID = NULL;
DWORD Globals::pCPythonPlayerIsSkillActive = NULL;
DWORD Globals::pCPythonPlayerIsSkillCoolTime = NULL;
DWORD Globals::pCPythonPlayerNEW_Fishing = NULL;
DWORD Globals::pCPythonPlayerNEW_GetMainActorPtr = NULL;
DWORD Globals::pCPythonPlayerNEW_SetSingleDIKKeyState = NULL;;
DWORD Globals::pCPythonPlayerSetAttackKeyState = NULL;
DWORD Globals::pCPythonPlayerSetTarget = NULL;
DWORD Globals::pCPythonPlayer__OnClickActor = NULL;
DWORD Globals::pCPythonPlayer__OnPressActor = NULL;

DWORD Globals::pPyCallClassMemberFunc = NULL;
DWORD Globals::pCGraphicBasems_lpd3dDevice = NULL;
DWORD Globals::pCInputKeyboardUpdateKeyboard = NULL;
//Globals::tCNetworkStreamPeek Globals::CNetworkStreamPeek = NULL;
//#############################################
DWORD Globals::pCInstanceBaseIsWaiting = NULL;
DWORD Globals::pCInstanceBaseSetRotation = NULL;
DWORD Globals::pCPythonNetworkStreamSendCommandPacket = NULL;
DWORD Globals::pCInstanceBase__GetBackgroundHeight = NULL;
DWORD Globals::pCPythonPlayerGetItemCount = NULL;
DWORD Globals::pCGraphicTextureGetD3DTexture = NULL;
DWORD Globals::pCResourceManagerGetResourcePointer = NULL;
DWORD Globals::pCGraphicImageGetTexturePointer = NULL;
DWORD Globals::pCResourceReload = NULL;
//python only
//player
DWORD Globals::CythonPlayerGetStatus = NULL;
DWORD Globals::CythonPlayerGetMainCharacterIndex = NULL;
DWORD Globals::CythonPlayerGetItemIndex = NULL;
DWORD Globals::CythonPlayerGetItemCount = NULL;
DWORD Globals::CythonPlayerGetName = NULL;
DWORD Globals::CythonPlayerGetItemMetinSocket = NULL;
DWORD Globals::CythonPlayerGetRace = NULL;
DWORD Globals::CythonPlayerSetSingleDIKKeyState = NULL;
DWORD Globals::CythonPlayerClickSkillSlot = NULL;
DWORD Globals::CythonPlayerIsSkillCoolTime = NULL;
DWORD Globals::CythonPlayerIsSkillActive = NULL;
DWORD Globals::CythonPlayerGetTargetVID = NULL;
DWORD Globals::CythonPlayerSetTarget = NULL;
DWORD Globals::CythonPlayerSetAttackKeyState = NULL;
DWORD Globals::CythonPlayerIsMountingHorse = NULL;
//chr
DWORD Globals::CythonChrSelectInstance = NULL;
DWORD Globals::CythonChrGetPixelPosition = NULL;
DWORD Globals::CythonChrMoveToDestPosition = NULL;
DWORD Globals::CythonChrGetInstanceType = NULL;
DWORD Globals::CythonChrGetVirtualNumber = NULL;
DWORD Globals::CythonChrGetNameByVID = NULL;
DWORD Globals::CythonChrSetPixelPosition = NULL;
DWORD Globals::CythonChrSetRotation = NULL;
DWORD Globals::CythonChrGetRotation = NULL;
DWORD Globals::CythonChrmgrSetAffect = NULL;
//net
DWORD Globals::CythonNetSendItemUsePacket = NULL;
DWORD Globals::CythonNetSendChatPacket = NULL;
DWORD Globals::CythonNetSendRefinePacket = NULL;
DWORD Globals::CythonNetSendExchangeStartPacket = NULL;
DWORD Globals::CythonNetSendExchangeItemAddPacket = NULL;
DWORD Globals::CythonNetSendExchangeAcceptPacket = NULL;
DWORD Globals::CythonNetSendWhisperPacket = NULL;
DWORD Globals::CythonNetSendItemPickUpPacket = NULL;
DWORD Globals::CythonNetSendItemDropPacketNew = NULL;
DWORD Globals::CythonNetSendOnClickPacket = NULL;
DWORD Globals::CythonNetSendShopSellPacketNew = NULL;
DWORD Globals::CythonNetSendShopBuyPacket = NULL;
DWORD Globals::CythonNetSendShopEndPacket = NULL;
DWORD Globals::CythonNetSendGiveItemPacket = NULL;
DWORD Globals::CythonNetSendItemMovePacket = NULL;
DWORD Globals::CythonNetDirectEnter = NULL;
DWORD Globals::CythonNetConnectTCP = NULL;
DWORD Globals::CythonNetIsConnect = NULL;
DWORD Globals::CythonNetGetMainActorSkillGroup = NULL;
DWORD Globals::CythonNetGetAccountCharacterSlotData = NULL;
DWORD Globals::CythonNetSendCommandPacket = NULL;
DWORD Globals::CythonEventSelectAnswer = NULL;
DWORD Globals::CythonItemSelectItem = NULL;
DWORD Globals::CythonItemGetItemName = NULL;

Globals::tCActorInstanceTestActorCollision Globals::CActorInstanceTestActorCollision = NULL;
Globals::tCPythonBackgroundGlobalPositionToMapInfo Globals::CPythonBackgroundGlobalPositionToMapInfo = NULL;
Globals::tCInstanceBaseAvoidObject Globals::CInstanceBaseAvoidObject = NULL;
Globals::tCInstanceBaseBlockMovement Globals::CInstanceBaseBlockMovement = NULL;;
Globals::tCInstanceBaseGetInstanceType Globals::CInstanceBaseGetInstanceType = NULL;
Globals::tCInstanceBaseGetInstanceVirtualNumber Globals::CInstanceBaseGetInstanceVirtualNumber = NULL;
Globals::tCInstanceBaseGetNameString Globals::CInstanceBaseGetNameString = NULL;
Globals::tCInstanceBaseGetRotation Globals::CInstanceBaseGetRotation = NULL;
Globals::tCInstanceBaseIsDead Globals::CInstanceBaseIsDead = NULL;
Globals::tCInstanceBaseIsMountingHorse Globals::CInstanceBaseIsMountingHorse = NULL;
Globals::tCInstanceBaseNEW_GetPixelPosition Globals::CInstanceBaseNEW_GetPixelPosition = NULL;
Globals::tCInstanceBaseNEW_LookAtDestPixelPosition Globals::CInstanceBaseNEW_LookAtDestPixelPosition = NULL;
Globals::tCInstanceBaseNEW_MoveToDestPixelPositionDirection Globals::CInstanceBaseNEW_MoveToDestPixelPositionDirection = NULL;
Globals::tCInstanceBaseSCRIPT_SetPixelPosition Globals::CInstanceBaseSCRIPT_SetPixelPosition = NULL;
Globals::tCInstanceBase__SetAffect Globals::CInstanceBase__SetAffect = NULL;
Globals::tCItemDataGetName Globals::CItemDataGetName = NULL;
Globals::tCItemManagerGetItemDataPointer Globals::CItemManagerGetItemDataPointer = NULL;
Globals::tCPythonBackgroundLocalPositionToGlobalPosition Globals::CPythonBackgroundLocalPositionToGlobalPosition = NULL;
Globals::tCNetworkStreamConnect Globals::CNetworkStreamConnect = NULL;
Globals::tCNetworkStream__DirectEnterMode_Set Globals::CNetworkStream__DirectEnterMode_Set = NULL;
Globals::tCNetworkStreamGetAccountCharacterSlotDataz Globals::CNetworkStreamGetAccountCharacterSlotDataz = NULL;
Globals::tCNetworkStreamIsOnline Globals::CNetworkStreamIsOnline = NULL;
Globals::tCNetworkStreamRecv Globals::CNetworkStreamRecv = NULL;
Globals::tCNetworkStreamSend Globals::CNetworkStreamSend = NULL;
Globals::tCNetworkStreamSendSequence Globals::CNetworkStreamSendSequence = NULL;
Globals::tCPhysicsObjectIncreaseExternalForce Globals::CPhysicsObjectIncreaseExternalForce = NULL;
Globals::tCPythonPlayerReviveGlobal Globals::CPythonPlayerReviveGlobal = NULL;
Globals::tCPythonApplicationProcess Globals::CPythonApplicationProcess = NULL;
Globals::tCPythonApplicationRenderGame Globals::CPythonApplicationRenderGame = NULL;
Globals::tCPythonCharacterManagerGetInstancePtr Globals::CPythonCharacterManagerGetInstancePtr = NULL;
Globals::tCPythonChatAppendChat Globals::CPythonChatAppendChat = NULL;
Globals::tCPythonEventManagerRegisterEventSetFromString Globals::CPythonEventManagerRegisterEventSetFromString = NULL;
Globals::tCPythonNetworkStreamConnectGameServer Globals::CPythonNetworkStreamConnectGameServer = NULL;
Globals::tCPythonNetworkStreamGetMainActorSkillGroup Globals::CPythonNetworkStreamGetMainActorSkillGroup = NULL;
Globals::tCPythonNetworkStreamSendAddFlyTargetingPacket Globals::CPythonNetworkStreamSendAddFlyTargetingPacket = NULL;
Globals::tCPythonNetworkStreamSendAttackPacket Globals::CPythonNetworkStreamSendAttackPacket = NULL;
Globals::tCPythonNetworkStreamSendCharacterStatePacket Globals::CPythonNetworkStreamSendCharacterStatePacket = NULL;;
Globals::tCPythonNetworkStreamSendChatPacket Globals::CPythonNetworkStreamSendChatPacket = NULL;
Globals::tCPythonNetworkStreamSendEmoticon Globals::CPythonNetworkStreamSendEmoticon = NULL;
Globals::tCPythonNetworkStreamSendExchangeAcceptPacket Globals::CPythonNetworkStreamSendExchangeAcceptPacket = NULL;
Globals::tCPythonNetworkStreamSendExchangeItemAddPacket Globals::CPythonNetworkStreamSendExchangeItemAddPacket = NULL;
Globals::tCPythonNetworkStreamSendExchangeStartPacket Globals::CPythonNetworkStreamSendExchangeStartPacket = NULL;
Globals::tCPythonNetworkStreamSendFishingQuitPacket Globals::CPythonNetworkStreamSendFishingQuitPacket = NULL;
Globals::tCPythonNetworkStreamSendFishingPacket Globals::CPythonNetworkStreamSendFishingPacket = NULL;
Globals::tCPythonNetworkStreamSendGiveItemPacket Globals::CPythonNetworkStreamSendGiveItemPacket = NULL;
Globals::tCPythonNetworkStreamSendItemDropPacketNew Globals::CPythonNetworkStreamSendItemDropPacketNew = NULL;
Globals::tCPythonNetworkStreamSendItemMovePacket Globals::CPythonNetworkStreamSendItemMovePacket = NULL;
Globals::tCPythonNetworkStreamSendItemPickUpPacket Globals::CPythonNetworkStreamSendItemPickUpPacket = NULL;
Globals::tCPythonNetworkStreamSendItemUsePacket Globals::CPythonNetworkStreamSendItemUsePacket = NULL;
Globals::tCPythonNetworkStreamSendItemUseToItemPacket Globals::CPythonNetworkStreamSendItemUseToItemPacket = NULL;
Globals::tCPythonNetworkStreamSendOnClickPacket Globals::CPythonNetworkStreamSendOnClickPacket = NULL;
Globals::tCPythonNetworkStreamSendRefinePacket Globals::CPythonNetworkStreamSendRefinePacket = NULL;
Globals::tCPythonNetworkStreamSendScriptAnswerPacket Globals::CPythonNetworkStreamSendScriptAnswerPacket = NULL;
Globals::tCPythonNetworkStreamSendShootPacket Globals::CPythonNetworkStreamSendShootPacket = NULL;
Globals::tCPythonNetworkStreamSendShopBuyPacket Globals::CPythonNetworkStreamSendShopBuyPacket = NULL;
Globals::tCPythonNetworkStreamSendShopEndPacket Globals::CPythonNetworkStreamSendShopEndPacket = NULL;
Globals::tCPythonNetworkStreamSendShopSellPacketNew Globals::CPythonNetworkStreamSendShopSellPacketNew = NULL;
Globals::tCPythonNetworkStreamSendSpecial Globals::CPythonNetworkStreamSendSpecial = NULL;
Globals::tCPythonNetworkStreamSendUseSkillPacket Globals::CPythonNetworkStreamSendUseSkillPacket = NULL;
Globals::tCPythonNetworkStreamSendWhisperPacket Globals::CPythonNetworkStreamSendWhisperPacket = NULL;
Globals::tCPythonNetworkStreamServerCommand Globals::CPythonNetworkStreamServerCommand = NULL;
Globals::tCPythonNonPlayerGetTable Globals::CPythonNonPlayerGetTable = NULL;
Globals::tCPythonPlayerClickSkillSlot Globals::CPythonPlayerClickSkillSlot = NULL;
Globals::tCPythonPlayerGetName Globals::CPythonPlayerGetName = NULL;
Globals::tCPythonPlayerGetItemIndex Globals::CPythonPlayerGetItemIndex = NULL;
Globals::tCPythonPlayerGetItemMetinSocket Globals::CPythonPlayerGetItemMetinSocket = NULL;
Globals::tCPythonPlayerGetItemAttribute Globals::CPythonPlayerGetItemAttribute = NULL;
Globals::tCPythonPlayerGetMainCharacterIndex Globals::CPythonPlayerGetMainCharacterIndex = NULL;
Globals::tCPythonPlayerGetRace Globals::CPythonPlayerGetRace = NULL;
Globals::tCPythonPlayerGetStatus Globals::CPythonPlayerGetStatus = NULL;
Globals::tCPythonPlayerGetTargetVID Globals::CPythonPlayerGetTargetVID = NULL;
Globals::tCPythonPlayerIsSkillActive Globals::CPythonPlayerIsSkillActive = NULL;
Globals::tCPythonPlayerIsSkillCoolTime Globals::CPythonPlayerIsSkillCoolTime = NULL;
Globals::tCPythonPlayerNEW_Fishing Globals::CPythonPlayerNEW_Fishing = NULL;
Globals::tCPythonPlayerNEW_GetMainActorPtr Globals::CPythonPlayerNEW_GetMainActorPtr = NULL;
Globals::tCPythonPlayerNEW_SetSingleDIKKeyState Globals::CPythonPlayerNEW_SetSingleDIKKeyState = NULL;
Globals::tCPythonPlayerSetAttackKeyState Globals::CPythonPlayerSetAttackKeyState = NULL;
Globals::tCPythonPlayerSetTarget Globals::CPythonPlayerSetTarget = NULL;
Globals::tCPythonPlayer__OnClickActor Globals::CPythonPlayer__OnClickActor = NULL;
Globals::tCPythonPlayer__OnPressActor Globals::CPythonPlayer__OnPressActor = NULL;
Globals::tCTerrainLoadMiniMapTexture Globals::CTerrainLoadMiniMapTexture = NULL;
Globals::tPyCallClassMemberFunc  Globals::PyCallClassMemberFunc = NULL;
Globals::tCInputKeyboardUpdateKeyboard Globals::CInputKeyboardUpdateKeyboard = NULL;
//################################
Globals::tCInstanceBaseIsWaiting Globals::CInstanceBaseIsWaiting = NULL;
Globals::tCInstanceBaseSetRotation Globals::CInstanceBaseSetRotation = NULL;
Globals::tCPythonNetworkStreamSendCommandPacket Globals::CPythonNetworkStreamSendCommandPacket = NULL;
Globals::tCInstanceBase__GetBackgroundHeight Globals::CInstanceBase__GetBackgroundHeight = NULL;
Globals::tCPythonPlayerGetItemCount Globals::CPythonPlayerGetItemCount = NULL;
Globals::tCResourceManagerGetD3DTexture Globals::CGraphicTextureGetD3DTexture = NULL;
Globals::tCResourceManagerGetResourcePointer Globals::CResourceManagerGetResourcePointer = NULL;
Globals::tCResourceManagerGetTexturePointer Globals::CGraphicImageGetTexturePointer = NULL;
Globals::tCResourceReload Globals::CResourceReload = NULL;
//####Globals::#################################################################################################################################

Globals::tPyRun_SimpleStringFlags Globals::PyRun_SimpleStringFlags = NULL;
Globals::tPyString_AsString Globals::PyString_AsString = NULL;
Globals::tPyTuple_GetItem Globals::PyTuple_GetItem = NULL;
Globals::tPyInt_AsLong Globals::PyInt_AsLong = NULL;
Globals::tPy_BuildValue Globals::Py_BuildValue = NULL;



//"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
void Globals::ReAddressingInstances()
{
	switch (Globals::Server)
	{
	case ServerName::METINPL:
	{
		HANDLE process = GetCurrentProcess();
		MEMORY_BASIC_INFORMATION info;
		unsigned char* p = NULL;
		for (p = NULL; VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info); p += info.RegionSize)
		{
			if ((info.State == MEM_COMMIT) && ((info.Type & MEM_MAPPED) || (info.Type & MEM_PRIVATE)) && info.Protect == 0x40)
			{
				if (info.RegionSize >= 0x02000000)
				{
					Globals::hEntryBaseAddress = (DWORD)info.BaseAddress;
					Globals::hEntryBaseSize = (DWORD)info.RegionSize;
				}
			}
		}
		//"[1]A1 ? ? ? ? 8B 10 81 C1 ? ? ? ? 51 50 8B 82 ? ? ? ? FF D0 D9 44 24";
		//"[1]A1 ? ? ? ? D9 6C 24";
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x21f8380; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x21f4ee4; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x21f4ee0; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x21f4edc; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x21f845c; // [100 ] [1 / 1]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x21fa6dc; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x21f4eec; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x21f4ed8; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x21f8418; // [100 ] [1 / 1]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x2201738;
		break;
	}
	case ServerName::ORIGINS2:
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x1d02bd0; // [98 ] [54 / 55]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x1cffe70; // [100 ] [26 / 26]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x1cffe60; // [88 ] [15 / 17]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x1cffe7c; // [100 ] [32 / 32]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x1d02c58; // [100 ] [3 / 3]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x1D055AC;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x1cffe64; // [100 ] [13 / 13]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x1cffe6c; // [100 ] [66 / 66]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x1d02c14; // [100 ] [5 / 5]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x1D08AE4;
		break;
	}
	case ServerName::CALLIOPE2:
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x37ee28; // [100 ] [97 / 97]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x37ee44; // [98 ] [81 / 82]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x37ee34; // [95 ] [39 / 41]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x37ee64; // [100 ] [46 / 46]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x3b6ee4; // [100 ] [4 / 4]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x37F2F0;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x37ee50; // [100 ] [17 / 17]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x37ee5c; // [99 ] [103 / 104]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x37ee38; // [100 ] [5 / 5]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x34148C;
		break;
	}
	case ServerName::MEDIUMMT2:
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x3ef29c; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x3ecf1c; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x3ecf0c; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x3ecf24; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x3ef304; // [100 ] [1 / 1]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x3f1330; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x3ecf10; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x3ecf18; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x3ef2e0; // [100 ] [1 / 1]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x3F3A94;
		break;
	}

	case ServerName::ASENIS:
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x37cc2a0; // [100 ] [103 / 103]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x37cc2cc; // [98 ] [76 / 77]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x37cc2b0; // [95 ] [40 / 42]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x38374e8; // [100 ] [41 / 41]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x383750c; // [100 ] [5 / 5]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x37D39C0;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x38374d8; // [100 ] [7 / 7]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x38374e0; // [100 ] [103 / 103]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x37cc2c0; // [100 ] [5 / 5]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x370ACCC;
		break;
	}

	case ServerName::CLASSIC:
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x44cb4c; // [100 ] [98 / 98]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x44a91c; // [98 ] [78 / 79]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x44a90c; // [95 ] [41 / 43]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x44a924; // [97 ] [47 / 48]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x44cb5c; // [100 ] [3 / 3]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x44EB88;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x44a910; // [100 ] [3 / 3]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x44a918; // [100 ] [106 / 106]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x44cb38; // [100 ] [3 / 3]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x450EEC;
		break;
	}
	case ServerName::VALIUM://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x285cf50; // [100 ] [103 / 103]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x285aadc; // [100 ] [88 / 88]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x285aacc; // [100 ] [40 / 40]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x285aae8; // [100 ] [48 / 48]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x285d040; // [100 ] [7 / 7]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x285F180; // [98 ] [74 / 75]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x285aad0; // [100 ] [6 / 6]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x285aad8; // [100 ] [120 / 120]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x285cf88; // [100 ] [4 / 4]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x28615A4;
		break;
	}
	case ServerName::DEVERIA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x357adc; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x35b7b0; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x357ae4; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x35b7c4; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x35B7F4; // [100 ] [4 / 4]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x358048; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x35b7d8; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x35b7d0; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x357af0; // [100 ] [1 / 1]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x2DF2AC;
		break;
	}
	case ServerName::DRAGON://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x2492f58; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x249c330; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x2492f60; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x249c344; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x249c37c; // [100 ] [1 / 1]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x24940E0;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x249c354; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x249c34c; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x2492f68; // [100 ] [7 / 7]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x2409A44;
		break;
	}
	case ServerName::DRAGON2://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x27e6784; // [100 ] [105 / 105]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x27e4400; // [100 ] [91 / 91]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x27e43f0; // [100 ] [42 / 42]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x27e4408; // [100 ] [58 / 58]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x27e67ac; // [100 ] [7 / 7]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x27E88E8; // [100 ] [59 / 59]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x27e43f4; // [100 ] [6 / 6]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x27e43fc; // [100 ] [135 / 135]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x27e6768; // [100 ] [4 / 4]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x27EAD64;
		break;
	}
	case ServerName::NEVILLA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x124e85c; // [100 ] [103 / 103]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x124e874; // [98 ] [84 / 85]					
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x124e860; // [95 ] [41 / 43]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x1252bc4; // [97 ] [45 / 46]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x1252be4; // [100 ] [4 / 4]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x124F0E8;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x1252bc0; // [100 ] [8 / 8]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x1252bb0; // [100 ] [106 / 106]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x124e86c; // [100 ] [3 / 3]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x11CFB7C;
		break;
	}
	case ServerName::LUNA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x236bc4c; // [100 ] [110 / 110]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x23683d8; // [98 ] [80 / 81]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x23683c4; // [95 ] [41 / 43]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x23683e0; // [100 ] [52 / 52]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x236bcf0; // [100 ] [4 / 4]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x236dde0; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x23683c8; // [100 ] [3 / 3]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x23683d4; // [99 ] [107 / 108]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x236bd5c; // [100 ] [6 / 6]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x23702B4;
		break;
	}
	case ServerName::G22:
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x171a3a4; // [100 ] [100 / 100]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x171a3cc; // [100 ] [60 / 60]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x171a3ac; // [100 ] [16 / 16]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x171a404; // [100 ] [47 / 47]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x171fab0; // [100 ] [3 / 3]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x171faf4; // [100 ] [35 / 35]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x171a3f4; // [100 ] [1 / 1]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x171a3fc; // [100 ] [98 / 98]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x171a3c0; // [100 ] [4 / 4]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x1722cfc; // [100 ] [2 / 2]
		break;
	}
	case ServerName::CarolineMT2://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x38ee70; // [100 ] [94 / 94]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x3c9770; // [100 ] [61 / 61]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x38ee78; // [100 ] [15 / 15]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x3c9784; // [100 ] [44 / 44]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x3c97b4; // [100 ] [3 / 3]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x38f3e8; // [100 ] [35 / 35]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x3c9798; // [100 ] [1 / 1]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x3c9790; // [100 ] [92 / 92]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x38ee84; // [100 ] [5 / 5]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x31436c; // [100 ] [2 / 2]
		break;
	}
	case ServerName::TASTRIA2://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x14F7A24; // [100 ] [110 / 110]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x14F7A58; // [98 ] [80 / 81]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x14F7A38; // [95 ] [41 / 43]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x14F7A90; // [100 ] [52 / 52]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x14FA048; // [100 ] [4 / 4]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x14FA094; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x14F7A80; // [100 ] [3 / 3]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x14F7A88; // [99 ] [107 / 108]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x14F7A40; // [100 ] [6 / 6]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x14FE5F4;
		break;
	}
	case ServerName::PANGEA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x328e984; // [100 ] [101 / 101]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x328e9b0; // [100 ] [66 / 66]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x328e990; // [100 ] [16 / 16]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x328ea08; // [100 ] [48 / 48]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x32aca90; // [100 ] [3 / 3]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x32acaa4; // [100 ] [35 / 35]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x328e9f8; // [100 ] [1 / 1]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x328ea00; // [100 ] [105 / 105]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x328e998; // [100 ] [7 / 7]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x32afe3c; // [100 ] [2 / 2]
		break;
	}
	case ServerName::BARIA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x28f115c; // [100 ] [100 / 100]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x28ed3ec; // [100 ] [89 / 89]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x28ed3dc; // [100 ] [42 / 42]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x28ed3f4; // [100 ] [49 / 49]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x28f1260; // [100 ] [7 / 7]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x28f39c0; // [100 ] [57 / 57]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x28ed3e0; // [100 ] [7 / 7]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x28ed3e8; // [100 ] [123 / 123]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x28f1644; // [100 ] [3 / 3]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x28f6ff4; // [100 ] [2 / 2]
		break;
	}
	case ServerName::WOM://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x1584474; // [100 ] [84 / 84]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x1581fa8; // [98 ] [73 / 74]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x1581f98; // [33 ] [1 / 3]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x1581fb0; // [100 ] [32 / 32]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x1584474; // [100 ] [5 / 5]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x158652C;
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x1581f9c; // [100 ] [4 / 4]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x1581fa4; // [98 ] [83 / 84]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x1584458; // [100 ] [5 / 5]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x15891BC;
		break;
	}
	case ServerName::ARATHAR://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x2cd0900; // [100 ] [103 / 103]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x2cc073c; // [100 ] [89 / 89]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x2cc072c; // [100 ] [41 / 41]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x2cc0744; // [100 ] [58 / 58]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x2cd0a64; // [100 ] [7 / 7]
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x2344e20; // [100 ] [74 / 74]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x2cc0730; // [100 ] [7 / 7]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x2cc0738; // [100 ] [127 / 127]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x2cd0a1c; // [100 ] [4 / 4]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x2CD506C;
		break;
	}
	case ServerName::EGORIA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x3af9538; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x3af9564; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x3af9548; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x3af9580; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x3B38E44;
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x3afa868; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x3af9570; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x3af9578; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x3af9558; // [100 ] [1 / 1]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x3A3B114;
		break;
	}
	case ServerName::AELDRA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x21D09F4; // [100 ] [1 / 1]
		pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x21D0B18; // [100 ] [1 / 1]
		pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x21D0A48; // [100 ] [1 / 1]
		pCItemManagerInstance = Globals::hEntryBaseAddress + 0x21D0AE0; // [100 ] [1 / 1]
		pCPythonItemInstance = Globals::hEntryBaseAddress + 0x21D389C;
		pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x21D38B0; // [100 ] [1 / 1]
		pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x21D0AE4; // [100 ] [1 / 1]
		pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x21D0B48; // [100 ] [1 / 1]
		pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x21D0ACC; // [100 ] [1 / 1]
		pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x21D9A48;
		break;
	}
	case ServerName::GLEVIA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x311aee4; // [100 ] [102 / 102]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x311b0bc; // Rate: 100
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x311af08; // Rate: 100
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x311b154; // Rate: 100
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x3123854; // Rate: 100
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x3123898; // Rate: 100
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x311b144; // Rate: 100
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x311b14c; // Rate: 100
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x311af0c; // Rate: 100
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x3128724; // Rate: 100
		break;
	}
	case ServerName::KEVRA://"CPythonGraphic::SetViewport(%d, %d, %d, %d) - Error"
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x672784; // [100 ] [102 / 102]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x6729fc; // [100 ] [89 / 89]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x6727e0; // [100 ] [41 / 41]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x672a80; // [100 ] [49 / 49]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x678990; // [100 ] [7 / 7]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x678a08; // [100 ] [58 / 58]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x672a6c; // [100 ] [6 / 6]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x672a74; // [100 ] [121 / 121]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x672954; // [100 ] [3 / 3]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x67e41c; // [100 ] [2 / 2]
		break;
	}
	case ServerName::Ernidia:
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x28aa030; // [100 ] [115 / 115]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x28a0cac; // [100 ] [90 / 90]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x28a0c9c; // [100 ] [46 / 46]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x28a0cb4; // [100 ] [50 / 50]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x28aa070; // [100 ] [7 / 7]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x28AC338; // [100 ] [58 / 58]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x28a0ca0; // [100 ] [16 / 16]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x28a0ca8; // [100 ] [119 / 119]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x28aa1d4; // [100 ] [3 / 3]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x28AE7FC;
		break;
	}
	case ServerName::TAMIDIA2021:
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x551a70; // [99 ] [258 / 259]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x55d880; // [98 ] [187 / 189]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x551a78; // [93 ] [97 / 104]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x55d890; // [97 ] [137 / 140]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x55d8c0; // [100 ] [14 / 14]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x551f10; // [98 ] [122 / 124]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x55d8a0; // [95 ] [21 / 22]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x55d898; // [99 ] [281 / 283]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x551a80; // [100 ] [16 / 16]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x51512c; // [75 ] [3 / 4]

		break;
	}
	case ServerName::ANORIA2:
	{
		Globals::pCPythonNetworkStreamInstance = Globals::hEntryBaseAddress + 0x550950; // [100 ] [349 / 349]
		Globals::pCPythonCharacterManagerInstance = Globals::hEntryBaseAddress + 0x550994; // [98 ] [285 / 288]
		Globals::pCPythonBackgroundInstance = Globals::hEntryBaseAddress + 0x550964; // [92 ] [132 / 143]
		Globals::pCItemManagerInstance = Globals::hEntryBaseAddress + 0x5509bc; // [100 ] [181 / 181]
		Globals::pCPythonItemInstance = Globals::hEntryBaseAddress + 0x58a604; // [100 ] [18 / 18]
		Globals::pCPythonApplicationInstance = Globals::hEntryBaseAddress + 0x55123c; // [96 ] [194 / 201]
		Globals::pCPythonNonPlayerInstance = Globals::hEntryBaseAddress + 0x5509a4; // [100 ] [55 / 55]
		Globals::pCPythonPlayerInstance = Globals::hEntryBaseAddress + 0x5509b0; // [99 ] [379 / 382]
		Globals::pCResourceManagerInstance = Globals::hEntryBaseAddress + 0x550988; // [100 ] [21 / 21]
		Globals::pCGraphicBasems_lpd3dDevice = Globals::hEntryBaseAddress + 0x501A9C;
		break;
	}
	}
}

void Globals::ReAddressingLocas()
{
	switch (Globals::Server)
	{
	case ServerName::METINPL:
	{
		HANDLE process = GetCurrentProcess();
		MEMORY_BASIC_INFORMATION info;
		unsigned char* p = NULL;
		for (p = NULL; VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info); p += info.RegionSize)
		{
			if ((info.State == MEM_COMMIT) && ((info.Type & MEM_MAPPED) || (info.Type & MEM_PRIVATE)) && info.Protect == 0x40)
			{
				if (info.RegionSize >= 0x02000000)
				{
					Globals::hEntryBaseAddress = (DWORD)info.BaseAddress;
					Globals::hEntryBaseSize = (DWORD)info.RegionSize;
				}
			}
		}
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x1C87410; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x76ed0; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x54cb0; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x54c70; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x599e0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x59a30; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x58f50; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x734f0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x56b50; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x56620; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x733e0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x72f30; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x73370; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x6A570;
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x3a7c70; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x3aa400; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x76e10; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x432a50; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1ec740; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1ea7a0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x4328c0; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x432870; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x432f00; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x432f30; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x432fa0; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x3cdef0; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x1c6c50; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x1c60e0; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x84240; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x14f4e0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x9b090; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1ea880; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1ec690; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x2023b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x201ee0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1fbd80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1FBF80;
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x211840; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x200ed0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x200e10; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x200ca0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x206d50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x206ec0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x222680; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x2228b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x222b40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x222410; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x1fe280; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x201280; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x202330; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x222210; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x222190; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x2222f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x201f60; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x1fbf10; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1FDAA0;
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1eda90; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xe6e30; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x11fed0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xf07f0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xf0d30; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xefaf0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xf0350; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0xefc60; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xf0310; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1072f0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xf2690; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xf2660; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x108030; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xef5a0; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x108FA0;
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x107350; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x107880; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x1079e0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x435bf0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x41E0D0; // [100 ] [1 / 1] 0x41E0D0 0x47eb30;
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x448ae0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x46c140; // [100 ] [1 / 1]
		//pCPythonApplicationOnUIRender = Globals::hEntryBaseAddress + 0x414b50; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x433780; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x72df0; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x73410; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x550A0;
		break;
	}

	case ServerName::Ernidia:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x1C87410;
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x1ade7e0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x1ab5660; // [100 ] [1 / 1]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x1ab56a0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x1ab44c0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x1ab4570; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x1ab4480; // [100 ] [2 / 2]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x1ad8e00; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x1ab5420; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x1ab5010; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x1ad8d40; // [100 ] [3 / 3]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x1ad8620; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x1ad8cc0; // [100 ] [1 / 1]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x1ace700; // [100 ] [1 / 1]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x1c7c3f0; // [100 ] [2 / 2]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x1c8c670; // [75 ] [3 / 4]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x1adce20; // [100 ] [1 / 1]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x1c2ede0; // [100 ] [1 / 1]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1bcbb00; // [100 ] [1 / 1]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1bcaee0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x1c2efb0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x1c2f020; // [100 ] [2 / 2]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x1c2f200; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x1c2f270; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x1c2f2f0; // [100 ] [1 / 1]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1ca5e40; // [100 ] [1 / 1]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x1ba7190; // [100 ] [1 / 1]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x1ba6a60; // [100 ] [1 / 1]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x1ae8be0; // [100 ] [30 / 30]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x1b5a820; // [100 ] [1 / 1]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1af6ef0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1BCB060;
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1bcb280; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x1bd55d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x1bd4cd0; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1bd4d30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1bd6e30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x1bcaa50; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x1bd51c0; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x1bd5060; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x1bd4fe0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x1bd6460; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x1bd64c0; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x1be8780; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x1be8800; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x1be89b0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x1be8530; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x1bd54f0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x1bd52f0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x1bd5650; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x1be8ba0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x1be8b40; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x1be8cb0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x1bd4a20; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x1bd4e90; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1bd6f50; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1bcd5e0; // [100 ] [14 / 14]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x1b0dac0; // [100 ] [4 / 4]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1b3a550; // [100 ] [2 / 2]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1b133c0; // [100 ] [7 / 7]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1b13680; // [100 ] [3 / 3]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1b12a40; // [100 ] [2 / 2]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x1b12c70; // [100 ] [3 / 3]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x1b12cd0; // [100 ] [2 / 2]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x1b12ee0; // [100 ] [4 / 4]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1b1b350; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1b14450; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1b14480; // [100 ] [2 / 2]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x1b1ad50; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1b12380; // [100 ] [14 / 14]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x1b1c360; // [100 ] [2 / 2]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x1b1b0c0; // [100 ] [3 / 3]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x1b1b630; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x1b1b440; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1c38cc0; // [100 ] [16 / 16]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1c32520; // [100 ] [22 / 22]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1c38a70; // [100 ] [3 / 3]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1cdd2d0; // [100 ] [1 / 1]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x1c2f830; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x1ad8170; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x1ad8e40; // [100 ] [1 / 1]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x1ab8640; // [100 ] [1 / 1]

		break;
	}

	case ServerName::ORIGINS2:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x41cb10; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x19c750; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x41c6d0; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x174c10; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x173910; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x173a10; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x1738b0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x196190; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x174960; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x174510; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x1960c0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x1954e0; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x196050; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x188fb0; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x40f3e0; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x4238a0; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x19a240; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x3b1b60; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x319f80; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x319210; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x3b1df0; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x3b1e60; // [100 ] [2 / 2]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x3b20c0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x3b2140; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x3B21D0;
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x439bc0; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x2c8ab0; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x2c8850; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x1aae40; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x245d00; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1c4620; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x3193a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x319630; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x32ac70; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x32a3e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x32a440; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x32d380; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x66ae; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x32a8b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x32a790; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x32a700; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x32bab0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x32BB10;
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x18787; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x3441b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x3443b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x343df0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x32ab90; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x32a990; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x32acf0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x344600; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x3445a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x344730;
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x329eb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x32a5a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x32d540; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x31cbf0; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x1e3340; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x215bf0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1eef00; // [100 ] [1 / 1]
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1ef070; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1ee2c0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x1738b0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x426190; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x1ee850; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x2047a0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1f02a0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1f02d0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x204080;
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1ed760; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x205e60; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x204470; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x204a80; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x204880; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x3b63f0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x3a37b0; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x3cb040; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x486c20; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x3b2920; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x194f20; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x1961d0; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x178ac0; // [100 ] [1 / 1]
		break;
	}
	case ServerName::CALLIOPE2:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x17b9d0; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x854D0;
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x17b540; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x69dd0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x6e070; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x6e090; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x6d210; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x76120; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x6b990; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x6b580; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x76040; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x75cc0; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x75fe0; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x73100; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x17f390; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x17d450; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x85400; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x12f860; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xad870; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0xad090; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x12fa30; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x12fa70; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x12fc70; // [100 ] [2 / 2]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x12fcb0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x69d20; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x191e00; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x7c450; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x7bff0; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x88b50; // [100 ] [21 / 21] 
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x8f870; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x95b30; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0xad180; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x6d2a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xb74b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xb7010; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xb45e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xb47b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xad960; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xb6560; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xb64e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xb63e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xb9670; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xb96d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xbd7c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xbdb20; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xbdd40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xbd600; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xb55f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xb67f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xb73b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xbd420; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xbd3d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xbd520; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xb70a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xb4740; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xb5120; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xae440; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xc0a40; // [82 ] [14 / 17]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xd08d0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xC2B30;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xc3060; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xc20d0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xc25d0; // [100 ] [2 / 2]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x9ab30; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xc25a0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xc6f20; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xc3e70; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xc3e50; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xc7700; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xc1dd0; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xc7fb0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xc6f60; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xc71e0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xc7280; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x879d0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x133810; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x135020; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1b9ac0; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x1399c0; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x75c00; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x76070; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x6a0d0; // [100 ] [1 / 1]
		break;
	}
	case ServerName::MEDIUMMT2:
	{
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x19b30; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x1309a0; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0xa490; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0xba40; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0xbbe0; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0xbb70; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x16780; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0xc120; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0xc300; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x16790; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x16100; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x16840; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x134f0; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x126a70; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x135ee0; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x19d90; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0xe0220; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x872e0; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x86ac0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0xe0340; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0xe03b0; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0xe03d0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0xe05f0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0xb6090; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x147120; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x6b140; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x6b840; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x1ec50; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x4eb30; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x280c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x868a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x86bc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x939c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x92f80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x930d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x93250; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x86e50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x93740; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x93870; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x938e0; // [100 ] [1 / 1]
		//pCPythonNetworkStreamSendFishingQuitPacket = Globals::hEntryBaseAddress + (null); 
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x93960; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x93a50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x97070; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x970e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x97210; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x97260; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x942b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + 0x94690; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x946c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x94770; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x97600; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x97670; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x97730; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x947b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x948e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x94940; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x87830; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x2ee20; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x3c9c0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x32230;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x32290; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x32480; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x32490; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x32570; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x32730; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x36b40; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x32bd0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x32c00; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x35f70; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x32fc0; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x373c0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x366f0; // [100 ] [1 / 1]
		//pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + (null); 
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x36cd0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0xe3cd0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0xd5f90; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0xf26e0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x183f20; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0xe0c90; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x15e40; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x168e0; // [100 ] [1 / 1]
		//pCPythonNetworkStreamSendCommandPacket = Globals::hEntryBaseAddress + (null); 
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0xeb60; // [100 %] [1 / 1]
		break;
	}
	case ServerName::ASENIS:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x199410; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x625e0; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x45870; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x45850; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x48da0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x48dc0; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x3c8e0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x53a20; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x46c80; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x46920; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x53940; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x535c0; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x538e0; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x508c0; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x19d160; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x19b0c0; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x624f0; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x14a320; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x8c720; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x8bec0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x14a440; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x14a480; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x14a690; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x14a6d0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x14a720; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1af980; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x5ad70; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x5a3d0; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x660c0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x6ce40; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x71c80; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x8bfb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x8c660; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x98900; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x98480; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x95940; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x95b20; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x8c810; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x97a90; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x97a10; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x978b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x9a9a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x9aa00; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xa1d10; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xa1e80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xa1fd0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xa1b30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x96960; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x97cf0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x98820; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xa1980; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xa1930; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xa1a80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x98500; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x95ab0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x963f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x8d570; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xa5140; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xb5ec0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xAABB0;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x19d250; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xaa1e0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x3c8e0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0xaa240; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xaa6d0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xae610; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xabaa0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xaba80; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xaede0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xa9ee0; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xaf5b0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xae650; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xaeb00; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xae970; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x65930; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x14ea70; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1533c0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1db7e0; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x157d70; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x53500; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x53970; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x45b40; // [100 ] [1 / 1]

		break;
	}
	case ServerName::PANGEA:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x2221a0; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x129170; // [100 ] [1 / 1]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x221cb0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0xf7610; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0xf8780; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0xf89c0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0xf88f0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x105290; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0xf8e50; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0xf9cd0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x1052a0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x104c30; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x105350; // [100 ] [1 / 1]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x103480; // [100 ] [1 / 1]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x217560; // [100 ] [1 / 1]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x2255e0; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x129530; // [100 ] [1 / 1]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x1c4890; // [100 ] [1 / 1]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1581b0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x157880; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x1c49b0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x1c4a20; // [100 ] [1 / 1]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x1c4c30; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x1c4c70; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x1c4cf0; // [100 ] [1 / 1]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x23e150; // [100 ] [1 / 1]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x120df0; // [100 ] [1 / 1]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x121540; // [100 ] [1 / 1]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x12ee40; // [100 ] [1 / 1]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x136270; // [100 ] [1 / 1]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x13f240; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x157660; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x157980; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x163c80; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x163e10; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1640b0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1B3790;
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x157cc0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x164680; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x164740; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x164830; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x1648c0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x1649b0; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x167e70; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x167ef0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x168050; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x1680b0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x165270; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x1656f0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x1657d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x168840; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x1688c0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x168990; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x165820; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x165930; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1659a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x158530; // [100 ] [1 / 1]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x16b840; // [100 ] [1 / 1]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x178520; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x16e290; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x16e2f0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x16e380; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x16e390; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x16e450; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x16e6f0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1723d0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x16eb40; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x16eb70; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x171a60; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x16eef0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x172c60; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x171f80; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x172460; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x172560; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1ee8f0; // [100 ] [1 / 1]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1cdd90; // [100 ] [1 / 1]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1d10e0; // [100 ] [1 / 1]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x275560; // [100 ] [1 / 1]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x1e3e10; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x104970; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x1053f0; // [100 ] [1 / 1]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0xfce90; // [100 ] [1 / 1]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x1d0cb0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x16e150; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x16e0d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x1681a0; // [100 ] [1 / 1]
		break;
	}
	case ServerName::CLASSIC:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x660b0; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x73090; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x17da80; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x64cb0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x65f80; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x66120; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x660b0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x704b0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x664f0; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x666d0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x704c0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x6fe30; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x70570; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x6eb70; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x173b00; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x182fc0; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x732f0; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x12cda0; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xd6600; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0xd5dd0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x12cec0; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x12cf30; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x12d130; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x12d170; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x16c5f0; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1939e0; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0xc2880; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0xc2f80; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x781b0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xa62d0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x80e60; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0xd5bc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0xd5ee0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xe1850; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xe0e50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xe0fa0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xe10f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xd6170; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xe15e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xe1700; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xe1770; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xe17f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xe18e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xe4c50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xe4cc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xe4df0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xe4e40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xe2140; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xe24e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xe2590; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xe51e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xe5250; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xe5310; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xe25d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xe26d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xe2730; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xd6b50; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x87990; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x941d0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x89C90;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x89cf0; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x89ee0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x89ef0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x89fd0; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x8a190; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x8e3b0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x8a630; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x8a660; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x8d920; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x8aa20; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x8ec30; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x8df60; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x8e4f0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x8e540; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x130850; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x123370; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x13f260; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1d0b30; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x12d810; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x6fb70; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x70610; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x68c50; // [100 ] [1 / 1]
		break;
	}
	case ServerName::VALIUM:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x1d0740; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0xac760; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x98e50; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x98e90; // [100 ] [4 / 4]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x97ae0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x97ba0; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x97ac0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0xa7220; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x98c10; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x98860; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0xa7160; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0xa6a20; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0xa70e0; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0xa1290; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x1c6e00; // [100 ] [4 / 4]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x1d4940; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0xaa8b0; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x195e70; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x144d00; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x144100; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x196060; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x1960a0; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x1962b0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x1962f0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x196340; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1e0140; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x127c90; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x1275c0; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0xb4490; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xfa0d0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0xbe350; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x144280; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1444a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x14e310; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x14d9d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x14da40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x14ffa0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x143c80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x14df00; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x14dda0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x14dd20; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x14f0f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x14f180; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x15ba00; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x15ba80; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x15bde0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x15b7c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x14e230; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x14e030; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x14e390; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x15bfe0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x15bf80; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x15c110; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x14d5f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x14dbd0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1500c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1463b0; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xc9540; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xdf810; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xcc120; // [100 ] [1 / 1]
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xcc3e0; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xcb800; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xcba30; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xcbc90; // [83 ] [5 / 6] 
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0xcba90; // [100 ] [2 / 2][1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xd4100; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xcd1f0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xcd220; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xd3a70; // [100 ] [2 / 2]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xcb090; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xd50f0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xd3e70; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xd43d0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xd41f0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x5cd10; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x18ecc0; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1952B0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x211620; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x196840; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0xa6560; // [100 ] [6 / 6]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0xa7260; // [100 ] [4 / 4]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x9c010; // [100 ] [4 / 4]
	}
	case ServerName::DEVERIA:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x198e40; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x78b10; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x5eca0; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x5ec80; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x61cc0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x61ce0; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x61690; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x6b1c0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x5ff20; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x5fbe0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x6b0e0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x6ad60; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x6b080; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x67c10; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x5ef80; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x19cb60; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x19ac20; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x78a20; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x14a240; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xa08f0; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0xa00e0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x14a430; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x14a470; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x14a680; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x14a6c0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x14a710; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1ae740; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x71500; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x70b40; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x7c0a0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x82cc0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x882e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0xa01c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0xa0840; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xa9d50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xa98c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xa7160; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xa7350; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xa09e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xa8fb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xa8f30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xa8dc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xabcd0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xabd30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xafa70; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xafc30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xafd60; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xaf8b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xa8070; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + 0xAC2F0;
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xa91f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xa9c70; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xaf6e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xaf680; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xaf800; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xa9930; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xa72e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xa7b70; // [100 ] [2 / 2]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xa13d0; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xb2c70; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xcddf0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xB4550;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xb4880; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xb3c30; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xb40d0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x8d730; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xb40a0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xb8010; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xb54a0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xb5480; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xb8830; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xb3920; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xb9070; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xb8050; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xb8520; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xb8390; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x7b870; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x150b90; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x15A050;
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1d9300; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x156a50; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x6aca0; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x6b110; // [100 ] [1 / 1]
		break;
	}
	case ServerName::DRAGON:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x2f6e70; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0xce080; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x90440; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x90420; // [100 ] [1 / 1] 
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x93860; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x93880; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x805b0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0xa6ac0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x91680; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x91320; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0xa69e0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0xa65a0; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0xa6980; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0xa1340; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x2fd490; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x39980c; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0xcdf90; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x25ce60; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x510AE0;
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x110290;
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x25cfd0; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x25d040; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x25d250; // [100 ] [1 / 1] 
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x25D290; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x25d310; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x322400; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0xc4e40; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0xc4480; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0xd50d0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xdeeb0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0xea6a0; // [100 ] [3 / 3]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x110370; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x110180; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x11BF40;
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x11bb50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1190e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1192c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x110bf0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x11b0e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x11b060; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x11aef0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x11df40; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x11dfa0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x128250; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x1283d0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x128520; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x128030; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x11a0c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x11b370; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x11bef0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x127e80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x127e30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x127f80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x11BBD0;
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x119250; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x119b60; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x111c90; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x12B930; // [28 ] [2 / 7]
		//##########pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x12b930; // [71 ] [5 / 7]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x143210; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1350D0;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1353f0; // [66 ] [2 / 3]
		//########pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x2fd570; // [33 ] [1 / 3]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x134690; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x805b0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0xf2be0; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x134bc0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x13a5d0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1360e0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1360c0; // [100 ] [1 / 1] 
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x13ae60; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x134370; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x13b690; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x13a660; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x13ab50; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x13a9c0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x2985b0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x2684a0; // [100 ] [2 / 2]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x26c9d0; // [100 ] [5 / 5]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x36FB30;
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x2743f0; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0xa64d0; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0xa6a10; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x90760; // [100 ] [1 / 1]
		break;
	}
	case ServerName::G22:
	{
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x11baa50; // Rate: 66
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x11a1ff0; // Rate: 100
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x11a2000; // Rate: 100
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0xde3a70; // Rate: 66
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x11a30e0; // Rate: 88
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x11ac500; // Rate: 100
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x11a37e0; // Rate: 100
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x11a3980; // Rate: 75
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x11ac510; // Rate: 100
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x11abf60; // Rate: 100
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x11ac5c0; // Rate: 100
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0xe4c190; // Rate: 50
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x11aaed0; // Rate: 50
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x1281d70; // Rate: 50
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x12cade0; // Rate: 50
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x128dfa0; // Rate: 64
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x11bab70; // Rate: 85
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x123f100; // Rate: 76
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x11e1d90; // Rate: 100
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x11e14b0; // Rate: 100
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x123f340; // Rate: 100
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x123f380; // Rate: 100
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x123f5a0; // Rate: 100
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x1241860; // Rate: 100
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x129d4e0; // Rate: 100
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x11b3090; // Rate: 100
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x11b3720; // Rate: 100
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x11be830; // Rate: 100
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x11c4b70; // Rate: 100
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x11cbae0; // Rate: 60
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x11e12d0; // Rate: 100
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x11e1590; // Rate: 50
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x11ee810; // Rate: 100
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x11eddc0; // Rate: 75
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x11ee070; // Rate: 87
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x11ee200; // Rate: 100
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x11e1820; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x11ee590; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x11ee6c0; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x11ee730; // Rate: 100
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x11ee7b0; // Rate: 100
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x11ee8a0; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x11f48f0; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x11f4960; // Rate: 80
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x11f4ab0; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x11f4b10; // Rate: 100
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x11ef3c0; // Rate: 100
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x11ef850; // Rate: 100
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x11ef930; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x11f53d0; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x11f5450; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x11f5520; // Rate: 100
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x11efba0; // Rate: 100
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x11efc10; // Rate: 100
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x11e1e50; // Rate: 100
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x11f7f30; // Rate: 80
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1203640; // Rate: 100
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x11f9cd0; // Rate: 100
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x11f9d30; // Rate: 66
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x127fc10; // Rate: 50
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xde2000; // Rate: 50
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x11a30e0; // Rate: 50
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x11fa050; // Rate: 75
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x11fa220; // Rate: 100
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x11fcda0; // Rate: 50
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1282340; // Rate: 50
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x11fa720; // Rate: 100
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x11fa750; // Rate: 100
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x11fcfe0; // Rate: 100
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x11faac0; // Rate: 100
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x11fe130; // Rate: 100
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x11fd600; // Rate: 100
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x11fd9a0; // Rate: 100
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1181780; // Rate: 92
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1245250; // Rate: 87
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1246610; // Rate: 70
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x12ca9e0; // Rate: 100
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x12567d0; // Rate: 100
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x11abbf0; // Rate: 100
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x11ac670; // Rate: 100
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x11a60a0; // Rate: 100
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x1246350; // Rate: 100
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x11f9b50; // Rate: 100
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x11f9ac0; // Rate: 83
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x11f4c10; // Rate: 100

		break;
	}
	case ServerName::DRAGON2:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x311be0; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x178130; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x311850; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x1553f0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x1542a0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x154350; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x154260; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x172520; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x155170; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x154dc0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x172460; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x171d40; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x1723e0; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x166a40; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x1580D0;
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x3062b0; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x317610; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x176600; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x2bcf60; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x257e50; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x257260; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x2bd140; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x2bd1b0; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x2BD3F0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x2bd400; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x2bd480; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x32c400; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x230810; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x230110; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x184aa0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x1e7640; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1925f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x2573e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x2575d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x2618e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x261050; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x2610b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x262ef0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x256de0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x261540; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x2613e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x261360; // [100 ] [1 / 1]
		//pCPythonNetworkStreamSendFishingQuitPacket = Globals::hEntryBaseAddress + (null); 
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x262700; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x262760; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x271340; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x2713c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x271570; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x271100; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x261800; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + 0x262880; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x261600; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x261960; // [100 ] [1 / 1]
		//pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + (null); 
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x271700; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x271890; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x260da0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x261210; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x263010; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x2599b0; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x1aab80; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1c4f20; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1b07e0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1b0aa0; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1afef0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x1b0120; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x1b0180; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x1b0380; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1b9600; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1b17e0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1b1810; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x1b9000; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1af840; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x1ba5d0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x1b9370; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x1b98e0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x1b96f0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x2c15f0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x2B30E0; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x2d0ee0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x36A960;
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x2bd9c0; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x171890; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x172560; // [100 ] [1 / 1]
		//pCPythonNetworkStreamSendCommandPacket = Globals::hEntryBaseAddress + (null); 
		break;
	}
	case ServerName::NEVILLA:
	{

		break;
	}
	case ServerName::LUNA:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x19b1d0; // [100 ] [3 / 3]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0xaec10; // [100 ] [1 / 1]
		//pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + (null); 
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0xa1db0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0xa3060; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0xa3370; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x5c4e0; // [83 ] [5 / 6]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0xac400; // [100 ] [3 / 3]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0xa3780; // [80 ] [4 / 5]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0xa3910; // [80 ] [4 / 5]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0xac410; // [66 ] [2 / 3]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0xabe60; // [100 ] [2 / 2]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0xac4c0; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0xaabb0; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x191a80; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x19f300; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0xaed30; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x15e850; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x118c80; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1183d0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x15ea80; // [100 ] [3 / 3]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x15eac0; // [100 ] [4 / 4]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x15eca0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x15ed10; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x15ed60; // [100 ] [1 / 1] 
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1a9ac0; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x1075b0; // [100 ] [2 / 2]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x107c30; // [100 ] [18 / 18]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0xb2c50; // [91 ] [21 / 23]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xed5d0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0xbb650; // [100 ] [3 / 3]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x118110; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1184b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x123410;
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x1235b0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1237f0; // [100 ] [6 / 6]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x123950; // [100 ] [7 / 7]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x118740; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x123cd0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x123e00; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x123e70; // [75 ] [3 / 4]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x123f00; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x123ff0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x127b10; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x127b80; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x127cb0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x127d10; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x124980; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x125020; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x125100; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x128440; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x1284d0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x1285c0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x1251e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x1252f0; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x198830; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x118d50; // [100 ] [9 / 9]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xc0d60; // [100 ] [1 / 1]
		//pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xa3370; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xdcc90; // [100 ] [2 / 2]
		//pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + (null); 
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xc2e30; // [50 ] [2 / 4]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xc3000; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x5c4e0; // [100 ] [2 / 2]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0xf40c0; // [100 ] [3 / 3]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xc32a0; // [100 ] [2 / 2]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xc5fa0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xc37f0; // [100 ] [2 / 2]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xc3820; // [100 ] [2 / 2]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xc61e0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xc3b90; // [100 ] [11 / 11]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xc7210; // [100 ] [2 / 2]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xc6680; // [100 ] [3 / 3]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xc6b70; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xc6bb0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1397e0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x15fd60; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x171230; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1d9ee0; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x15f260; // [100 ] [2 / 2]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0xabbf0; // [100 ] [1 / 1]
		//pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0xac180; // [33 ] [1 / 3]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0xac560; // [66 ] [2 / 3]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0xa6170; // [100 ] [1 / 1]
		break;
	}
	case ServerName::TASTRIA2:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x285e30; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x1771e0; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x285a40; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x158bb0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x159c30; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x159df0; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x159d60; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x1646c0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x15a2d0; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x15a4b0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x1646d0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x164060; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x164780; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x161a80; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x15cec0; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x27b1d0; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x2890d0; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x177330; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x212720; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1a4520; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1a3c90; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x2128f0; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x212960; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x212b70; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x212bb0; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x212c30; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x2a0cc0; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x16edd0; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x16f520; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x17ba90; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x182ae0; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x18b6c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1a3a80; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1a3d90; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x1b0b80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x1b0c90; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1b0e00; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1b0f70; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x1a4040; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x1b1440; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x1b1570; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x1b15f0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x1b1680; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x1b1770; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x1b4eb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x1b4f20; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x1b5060; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x1b50c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x1b20a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + 0x1b24a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x1b24e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x1b25c0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x1b5510; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x1b5590; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x1b5660; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x1b2610; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x1b2710; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1b2780; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1a48a0; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x1b8e50; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1cb730; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1C0BF0;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1c0c50; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1c0e40; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x1c0e50; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x1c0f10; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x1c10d0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1c4f80; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1c15a0; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1c15d0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1c1990; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x1c5910; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x1c4b30; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x24b510; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x1c5150; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x239f20; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x21b670; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x21dda0; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x2d86c0; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x2308d0; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x163da0; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x164820; // [100 ] [1 / 1]
		pCResourceReload = Globals::hEntryBaseAddress + 0x21D9B0;
		pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x1C0A20;
		pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x1C0990;
		pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x1B51C0;
		break;
	}
	case ServerName::WOM:
	{

		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x364c70; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x25FD40; // [100 ] [1 / 1]
		//pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + (null); 
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x250950; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x251a10; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x251b00; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x251aa0; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x25d4d0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x25cc40; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x252170; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x25d4e0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x25cf10; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x25d570; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x25b770; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x359F50; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x369d50; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x25FDD0; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x3278e0; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x2d7c40; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x2d6c10; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x327a20; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x327aa0; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x327ce0; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x327d20; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x327d70; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x377310; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x2c3da0; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x2c4500; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x265ab0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x2a2650; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x26f170; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x2d6a20; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x2D6D00; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x2e41b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x2e4330; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x2e4630; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x2e4790; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x2d6fb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x2e49b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x2e4a70; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x2e4b50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x2e4c40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x2e4d30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x2e88d0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x2e8950; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x2e8a80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x2e8ae0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x2e5610; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x2e5ae0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x2e5bc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x2e8f30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x2e8fb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x2e90b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x2e5cb0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x2e5dc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x2e5e30; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x2d8990; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x2792c0; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x2880e0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x27D460;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x27d4a0; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x27d510; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x27d520; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x27D5E0; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x27d7e0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x281750; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x27dc80; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x27dca0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x280df0; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x27e080; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x281f10; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x281380; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x2817d0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x2818c0; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x32d730; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x31e1d0; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x323520; // [100 ] [1 / 1]0x32DC70
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x3b0420; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x3294c0; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x251f00; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x25d620; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x254b30; // [100 ] [1 / 1]
		break;
	}
	case ServerName::ARATHAR:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x24f25f0; // [100 ] [4 / 4]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x234ad00; // [75 ] [3 / 4]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x2323e00; // [100 ] [2 / 2]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x2323e40; // [100 ] [5 / 5]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x2322c50; // [100 ] [3 / 3]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x2322d00; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x2322be0; // [100 ] [7 / 7]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x2344fe0; // [100 ] [9 / 9]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x2323bc0; // [100 ] [9 / 9]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x2323800; // [100 ] [14 / 14]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x2344f20; // [100 ] [25 / 25]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x23447e0; // [100 ] [10 / 10]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x2344ea0; // [100 ] [4 / 4]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x23393c0; // [100 ] [5 / 5]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x24e6bd0; // [100 ] [8 / 8]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x24f7d50; // [100 ] [11 / 11]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x23490c0; // [100 ] [4 / 4]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x249c5b0; // [100 ] [6 / 6]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x242d900; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x242cce0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x249c790; // [100 ] [3 / 3]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x249c800; // [100 ] [6 / 6]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x249ca50; // [100 ] [6 / 6]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x249cad0; // [100 ] [86 / 86]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x2509670; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x2406ab0; // [100 ] [4 / 4]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x2406380; // [100 ] [20 / 20]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x2357e10; // [52 ] [30 / 57]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x23bd1a0; // [66 ] [2 / 3]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x2364e90; // [75 ] [3 / 4]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x242ce60; // [100 ] [3 / 3]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x242d080; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x2437930; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x2436fb0; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x2437010; // [100 ] [11 / 11]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x24391b0; // [100 ] [8 / 8]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x242c860; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x24374a0; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x2437340; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x24372c0; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x24387c0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x2438820; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x2449770; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x2449860; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x2449a10; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x2449530; // [100 ] [5 / 5]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x2437760; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x2437560; // [100 ] [4 / 4]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x24379b0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x2449c00; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x2449ba0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x2449d30; // [100 ] [2 / 2]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x2436af0; // [100 ] [3 / 3]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x2437170; // [100 ] [6 / 6]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x24392d0; // [100 ] [3 / 3]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x242f570; // [100 ] [12 / 12]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x237db10; // [100 ] [10 / 10]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x2399120; // [100 ] [5 / 5]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x2384070; // [83 ] [10 / 12]
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x2384330; // [100 ] [5 / 5]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x2383850; // [100 ] [3 / 3]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x2383a80; // [71 ] [5 / 7]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x2383ae0; // [100 ] [4 / 4]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x2383ce0; // [83 ] [5 / 6]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x238d1d0; // [100 ] [3 / 3]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x23851f0; // [100 ] [4 / 4]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x2385220; // [100 ] [3 / 3]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x238cab0; // [100 ] [3 / 3]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x2383150; // [88 ] [15 / 17]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x238e270; // [100 ] [3 / 3]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x238cf20; // [80 ] [4 / 5]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x238d540; // [100 ] [3 / 3]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x238d2c0; // [100 ] [3 / 3]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x24a2720; // [100 ] [5 / 5]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x24925c0; // [90 ] [9 / 10]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x24b1060; // [100 ] [2 / 2]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x2549eb0; // [100 ] [1 / 1]
	//	pCPythonApplicationOnUIRender = Globals::hEntryBaseAddress + 0x240c5e0; // [100 ] [2 / 2]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x249d010; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x2344330; // [100 ] [6 / 6]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x2345020; // [100 ] [5 / 5]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x23275f0; // [100 ] [4 / 4]
		break;
	}
	case ServerName::EGORIA:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x2e4a80; // [100 ] [1 / 1]
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0xb5e90; // [100 ] [1 / 1]
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x72fe0; // [100 ] [1 / 1]
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x72fc0; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x76970; // [100 ] [1 / 1]
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x76990; // [100 ] [1 / 1]
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x62f50; // [100 ] [1 / 1]
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x8f2d0; // [100 ] [1 / 1]
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x74680; // [100 ] [1 / 1]
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x74310; // [100 ] [1 / 1]
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x8f1f0; // [100 ] [1 / 1]
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x8ede0; // [100 ] [1 / 1]
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x8f190; // [100 ] [1 / 1]
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x89080; // [100 ] [1 / 1]
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x2e95c0; // [100 ] [1 / 1]
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x2e7030; // [100 ] [1 / 1]
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0xb5da0; // [100 ] [1 / 1]
		pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x27c670; // [100 ] [1 / 1]
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x102110; // [100 ] [1 / 1]
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1018b0; // [100 ] [1 / 1]
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x27c790; // [100 ] [1 / 1]
		pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x27c800; // [100 ] [1 / 1]
		pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x27ca10; // [100 ] [1 / 1]
		pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x27ca50; // [100 ] [1 / 1]
		pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x27cad0; // [100 ] [1 / 1]
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x303210; // [100 ] [1 / 1]
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0xac530; // [100 ] [1 / 1]
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0xabb90; // [100 ] [1 / 1]
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0xbe0c0; // [100 ] [1 / 1]
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xc9390; // [100 ] [1 / 1]
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0xd57b0; // [100 ] [1 / 1]
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1019a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x102050; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x110990; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x1105a0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x10cbc0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x10cd90; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x102200; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x10fbd0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x10fb50; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x10f9e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x112ad0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x112b30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x123210; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x123390; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x1234e0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x122ff0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x10ea80; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x10fe30; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x110940; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x122e40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x122df0; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x122f40; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x110620; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x10cd20; // [100 ] [1 / 1]
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x10e510; // [100 ] [1 / 1]
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x103650; // [100 ] [1 / 1]
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x126930; // [100 ] [1 / 1]
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1402a0; // [100 ] [1 / 1]
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1311B0;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1314f0; // [100 ] [1 / 1]
		pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1307d0; // [100 ] [1 / 1]
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x130cf0; // [100 ] [1 / 1]
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x130830; // [100 ] [1 / 1]
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x130cc0; // [100 ] [1 / 1]
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x136e20; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x132070; // [100 ] [1 / 1]
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x132050; // [100 ] [1 / 1]
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x137600; // [100 ] [1 / 1]
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1304d0; // [100 ] [1 / 1]
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x137df0; // [100 ] [1 / 1]
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x136e60; // [100 ] [1 / 1]
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x1370f0; // [100 ] [1 / 1]
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x137190; // [100 ] [1 / 1]
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x2a37d0; // [100 ] [1 / 1]
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x283e50; // [100 ] [1 / 1]
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x289d00; // [100 ] [1 / 1]
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x338b50; // [100 ] [1 / 1]
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x291c70; // [100 ] [1 / 1]
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x8ed20; // [100 ] [1 / 1]
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x8f220; // [100 ] [1 / 1]
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x732f0; // [100 ] [1 / 1]
		pCResourceReload = Globals::hEntryBaseAddress + 0x289A40;
		pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x131430;
		pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x131560;
		pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x123100;
		break;
	}
	case ServerName::AELDRA:
	{
		pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x3EFE70;
		pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x2B1EB0;
		pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x28E920;
		pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x28E930;
		pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x28FAA0;
		pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x28FC20;
		pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x28FBC0;
		pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x29C6E0;
		pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x290050;
		pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x290260;
		pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x29C6F0;
		pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x29C080;
		pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x29C7A0;
		pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x29AEC0;
		pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x3E1320;
		pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x2B1FC0;
		pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x2F2940;
		pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x2F21B0;
		pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x379D60;
		pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x4107A0;
		pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x2A8BA0;
		pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x2B6A60;
		pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x2C9E30;
		pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x2D76D0;
		pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x2F1F90;
		pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x2F22B0;
		pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x30E800;
		pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x30F560;
		pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x2F24B0;
		pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x30F890;
		pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x30F990;
		pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x30FB40;
		pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x30FBF0;
		pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x30FD50;
		pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x316470;
		pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x316580;
		pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x316920;
		pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x3169D0;
		pCPythonNetworkStreamSendRefinePacket = Globals::hEntryBaseAddress + 0x3115F0;
		pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x311A70;
		pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x311CF0;
		pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x30FA90;
		pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x3173E0;
		pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x317510;
		pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x312050;
		pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x3120F0;
		pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x2F2C30;
		pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x31A5B0;
		pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x32B750;
		pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x31E440;
		pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x31E4C0;
		pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x31E680;
		pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x31E6B0;
		pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x323390;
		pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x31EDA0;
		pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x31EDD0;
		pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x322860;
		pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x323CB0;
		pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x322F00;
		pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x3A19D0;
		pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x37FD60;
		pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x38B1F0;
		pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x441580;
		pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x398D90;
		pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x29BDC0;
		pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x29C840;
		pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x292F10;
		pCItemDataGetName = Globals::hEntryBaseAddress + 0x3D6AB0;
		pCResourceReload = Globals::hEntryBaseAddress + 0x38AE20;
		pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x316BC0;
		pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x31E2A0;
		pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x31E5C0;
		pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x31F240;
		pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x31E1D0;
		pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x3244E0;
		pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x323430;
		pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x2A7E60;
		pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x311080;
		break;
	}
	case ServerName::CarolineMT2:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x249700; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x786b0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x5eeb0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x5ee90; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x61f20; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x61f40; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x618f0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x6ac90; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x60180; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x5fe40; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x6abb0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x6a830; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x6ab50; // [100 ] [1 / 1]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x67da0; // [100 ] [1 / 1]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x1b03d0; // [100 ] [1 / 1]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x1ae490; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x785c0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x15e240; // [100 ] [1 / 1]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xa04f0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x9fcc0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x15e430; // [100 ] [1 / 1]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x15e470; // [100 ] [1 / 1]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x15e490; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x15e6c0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x15e710; // [100 ] [1 / 1]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x1c22e0; // [100 ] [1 / 1]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x71080; // [100 ] [1 / 1]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x706c0; // [100 ] [1 / 1]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x7bc00; // [100 ] [1 / 1]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x828b0; // [100 ] [1 / 1]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x87ea0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x9fda0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0xa0440; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xaaa30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xaa630; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xa7d80; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xa7f70; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xa05e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xa9cd0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xa9c50; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xa9ae0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xaca40; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xacaa0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xb25d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xb2790; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xb28c0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xb2410; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xa8d10; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xa9f10; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xaa9e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xb2240; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xb21e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xb2360; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xaa6a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xa7f00; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xa8790; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xa0fd0; // [100 ] [1 / 1]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xb5890; // [100 ] [1 / 1]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xd0eb0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xb7640; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xb74c0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xb6850; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0xb6d10; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x8d2f0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xb6ce0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xbac60; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xb80e0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xb80c0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xbb480; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xb6540; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xbbcc0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xbaca0; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xbb170; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xbafe0; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x7b3d0; // [100 ] [1 / 1]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1648e0; // [100 ] [1 / 1]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x17f1d0; // [100 ] [2 / 2]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x1ecbb0; // [100 ] [1 / 1]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x16a5a0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x6a770; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x6abe0; // [100 ] [1 / 1]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x5f190; // [100 ] [1 / 1]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x1657a0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0xb73f0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0xb7530; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0xb24f0; // [100 ] [1 / 1]
		break;
	}
	case ServerName::BARIA:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x23ab160; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x1ea7a40; // [100 ] [1 / 1]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x20424b0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x20424e0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x1e837d0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x1e83880; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x1e83730; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x1ea1df0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x1e847b0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x1e84400; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x1ea1d30; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x1ea1610; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x1ea1cb0; // [100 ] [1 / 1]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x1e96c80; // [100 ] [1 / 1]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x2037a70; // [100 ] [1 / 1]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x2047a80; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x1ea5e20; // [100 ] [1 / 1]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x1fe98a0; // [100 ] [1 / 1]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1f7c280; // [100 ] [1 / 1]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1f7b680; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x1fe9a70; // [100 ] [1 / 1]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x1fe9ae0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x1fe9cf0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x1fe9d30; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x1fe9db0; // [100 ] [1 / 1]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x2058ab0; // [100 ] [1 / 1]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x1f59670; // [100 ] [1 / 1]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x1f58ee0; // [100 ] [1 / 1]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x1eb2fc0; // [100 ] [1 / 1]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x1f17270; // [100 ] [1 / 1]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1ebff50; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1f7b810; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1f7ba20; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x1f85c40; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x1f853a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x1f85411; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x1f87780; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x1f7b200; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x1f858a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x1f85740; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x1f856c0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x1f869d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x1f86a30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x1f9a300; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x1f9a3f0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x1f9a590; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x1f9a0b0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x1f85b60; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x1f85960; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x1f85cc0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x1f9a7b0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x1f9a750; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x1f9a8e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x1f850e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x1f85570; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x1f878a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1f7dd90; // [100 ] [1 / 1]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x1ed53b0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x1ef7ec0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x1edc620; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x1edc8e0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1edbd40; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x1f529a0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x1edbfd0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x1edc1e0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x1ee4550; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x1edd600; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x1edd630; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x1ee3f30; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1edb640; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x1ee5660; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x1ee42a0; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x1ee4820; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x1ee4640; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1ff1f00; // [100 ] [1 / 1]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1fed040; // [100 ] [1 / 1]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x2000c50; // [100 ] [1 / 1]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x20970a0; // [100 ] [1 / 1]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x1fea2f0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x1ea1160; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x1ea1e30; // [100 ] [1 / 1]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x1e88d80; // [100 ] [1 / 1]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x1ff1be0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x1edc820; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x1edc930; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x1f9a210; // [100 ] [1 / 1]
		break;
	}
	case ServerName::GLEVIA:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x31eac0; // Rate: 100
		//Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x2c0c80a; // Rate: 100
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x1af240; // Rate: 100
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x31e6d0; // Rate: 100
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x31e700; // Rate: 100
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x160710; // Rate: 100
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x1607c0; // Rate: 100
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x1606b0; // Rate: 100
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x181730; // Rate: 100
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x161600; // Rate: 100
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x161210; // Rate: 100
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x181670; // Rate: 100
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x180f80; // Rate: 100
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x1815f0; // Rate: 100
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x174e40; // Rate: 100
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x313e40; // Rate: 100
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x321de0; // Rate: 100
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x1ad640; // Rate: 100
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x2ba810; // Rate: 50
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x2ba910; // Rate: 50
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x210cc0; // Rate: 100
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x20ff20; // Rate: 100
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x2baaa0; // Rate: 100
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x2bacb0; // Rate: 100
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x2bacf0; // Rate: 100
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x2baa30; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x2bad70; // Rate: 100
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x338f20; // Rate: 100
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x19f1f0; // Rate: 100
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x19ef40; // Rate: 100
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x1bb1f0; // Rate: 100
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x1c9430; // Rate: 100
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x1c8290; // Rate: 100
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1daf70; // Rate: 100
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x2100a0; // Rate: 100
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x2102c0; // Rate: 100
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x21b810; // Rate: 100
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x21aeb0; // Rate: 100
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x21af10; // Rate: 100
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x21af11; // Rate: 100
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x21cc40; // Rate: 100
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x20faa0; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x21b410; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x21b240; // Rate: 100
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x21b1c0; // Rate: 100
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x21c540; // Rate: 100
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x21c650; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x22fc00; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x22fc80; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x22fe40; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x22f990; // Rate: 100
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x21b6d0; // Rate: 100
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x21b4d0; // Rate: 100
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x21b890; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x230030; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x22ffd0; // Rate: 100
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x230160; // Rate: 100
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x21aab0; // Rate: 100
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x21b070; // Rate: 100
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x21ce80; // Rate: 100
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x2121a0; // Rate: 100
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x234ca0; // Rate: 100
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x259210; // Rate: 100
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x244ee0; // Rate: 100
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x2451c0; // Rate: 100
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x244670; // Rate: 100
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x2448a0; // Rate: 100
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x244900; // Rate: 100
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x244b00; // Rate: 100
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x24cac0; // Rate: 100
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x245fb0; // Rate: 100
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x245fe0; // Rate: 100
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x24c4c0; // Rate: 100
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x243fc0; // Rate: 100
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x24da30; // Rate: 100
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x24c830; // Rate: 100
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x24cdc0; // Rate: 100
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x24cbd0; // Rate: 100
		//Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x8ad70; // Rate: 100
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x70450; // [100 ] [1 / 1]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x2c1370; // [100 ] [1 / 1]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x2e9770; // [100 ] [1 / 1]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x370a60; // Rate: 100
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x2d65a0; // Rate: 100
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x180ad0; // Rate: 100
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x181770; // Rate: 100
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x164de0; // Rate: 100
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x2c6e30; // Rate: 100
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x2450e0; // Rate: 100
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x245210; // Rate: 100
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x22fb00; // Rate: 100
		break;
	}
	case ServerName::KEVRA:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x340a70; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x180670; // [100 ] [1 / 1]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x1157f0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x115830; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x113f30; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x113fe0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x113df0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x1394d0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x1155b0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x115110; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x139410; // [100 ] [1 / 1]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x1389c0; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x139390; // [100 ] [1 / 1]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x12b4c0; // [100 ] [1 / 1]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x333070; // [100 ] [1 / 1]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x344650; // [100 ] [1 / 1]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x17e780; // [100 ] [1 / 1]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x2b9390; // [100 ] [1 / 1]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0x1f86e0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x1f7a60; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x2b95d0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x2b9640; // [100 ] [1 / 1]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x2b9890; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x2b98e0; // [100 ] [1 / 1]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x2b9970; // [100 ] [1 / 1]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x3638a0; // [100 ] [1 / 1]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x160d00; // [100 ] [1 / 1]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x1605d0; // [100 ] [1 / 1]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x18d700; // [100 ] [1 / 1]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x19cb60; // [100 ] [1 / 1]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x1b33a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x1f7c00; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x1f7e20; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0x205ea0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0x204d70; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0x204dd0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0x208e80; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0x1f7560; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0x2052a0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0x205140; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0x2050c0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0x206c30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0x206c90; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x218040; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x218130; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x2182e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x217df0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0x205bd0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0x2053d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0x205f20; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x2184d0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x218470; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x2186e0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0x204ac0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0x204f30; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0x208fa0; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0x1fada0; // [100 ] [1 / 1]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x21ef80; // [100 ] [1 / 1]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x240680; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0x2278e0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x227e10; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x226ca0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x226ed0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x226F30;
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x227150; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x231cf0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x228d60; // [100 ] [1 / 1]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x228d90; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x2316d0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x226550; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x233350; // [100 ] [1 / 1]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x231a40; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x231fc0; // [100 ] [1 / 1]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x231de0; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x2e8160; // [100 ] [1 / 1]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x2c3e80; // [100 ] [1 / 1]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x2c6a90; // [100 ] [1 / 1]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x3A7CD0;
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x2dc940; // [100 ] [1 / 1]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x138510; // [100 ] [1 / 1]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x139510; // [100 ] [1 / 1]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x11c8f0; // [100 ] [1 / 1]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x2c65b0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0x227ae0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x227e60; // [100 ] [1 / 1]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x217f50; // [100 ] [1 / 1]
		break;
	}
	case ServerName::TAMIDIA2021:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x2bbc20;  // [60 ] [3 / 5]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0x767a0; // [80 ] [4 / 5]
		Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress + 0x5df90; // [100 ] [6 / 6]
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x5df70; // [77 ] [7 / 9]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x60e00; // [100 ] [7 / 7]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x60e20; // [100 ] [11 / 11]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x60810; // [87 ] [14 / 16]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x68be0; // [82 ] [14 / 17]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x5f080; // [93 ] [15 / 16]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x5ed40; // [84 ] [11 / 13]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x68b00; // [100 ] [23 / 23]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x68780; // [100 ] [12 / 12]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x68aa0; // [100 ] [12 / 12]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x65d30; // [60 ] [6 / 10]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x2bed90; // [90 ] [20 / 22]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x2bd640; // [80 ] [8 / 10]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0x766b0; // [81 ] [9 / 11]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x272a40; // [93 ] [15 / 16]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xa0070; // [100 ] [8 / 8]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0x9f890; // [100 ] [1 / 1]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x272c30; // [100 ] [23 / 23]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x272c70; // [100 ] [22 / 22]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x272e80; // [64 ] [11 / 17]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x2649b0; // [80 ] [4 / 5]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x272f10; // [98 ] [53 / 54]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x2d07b0; // [100 ] [21 / 21]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x6ee70; // [100 ] [5 / 5]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x6e4e0; // [100 ] [27 / 27]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0x79f10; // [91 ] [56 / 61]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0x80f70; // [100 ] [13 / 13]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0x85c70; // [100 ] [11 / 11]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0x9f970; // [100 ] [14 / 14]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0x9ffc0; // [100 ] [13 / 13]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xa9b00; // [66 ] [4 / 6]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xa9730; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xa6dd0; // [100 ] [15 / 15]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xa6fb0; // [100 ] [12 / 12]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xa0160; // [100 ] [4 / 4]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xa8e70; // [100 ] [14 / 14]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xa8df0; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xa8d00; // [100 ] [21 / 21]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xabab0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xabb10; // [100 ] [2 / 2]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0xaf510; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0xaf6d0; // [100 ] [6 / 6]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0xaf800; // [100 ] [8 / 8]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0xaf350; // [100 ] [11 / 11]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xa7ee0; // [100 ] [17 / 17]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xa90b0; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xa9ab0; // [100 ] [8 / 8]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0xaf180; // [100 ] [5 / 5]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0xaf120; // [100 ] [11 / 11]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0xaf2a0; // [100 ] [5 / 5]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xa9790; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xa6f40; // [100 ] [18 / 18]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xa7870; // [100 ] [12 / 12]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xa0b50; // [100 ] [78 / 78]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0xb2780; // [53 ] [8 / 15]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0xbea90; // [100 ] [7 / 7]
		Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + 0xb4400; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0xb4280; // [55 ] [5 / 9]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0xb3640; // [100 ] [5 / 5]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x60810; // [100 ] [6 / 6]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x8adb0; // [100 ] [9 / 9]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0xb3ab0; // [100 ] [20 / 20]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0xb7920; // [50 ] [6 / 12]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0xb4e00; // [100 ] [12 / 12]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0xb4de0; // [100 ] [14 / 14]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0xb8120; // [100 ] [2 / 2]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0xb3330; // [100 ] [33 / 33]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0xb8920; // [100 ] [5 / 5]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0xb7960; // [100 ] [9 / 9]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0xb7e10; // [100 ] [2 / 2]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0xb7c80; // [100 ] [1 / 1]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x796c0; // [94 ] [16 / 17]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x277470; // [98 ] [63 / 64]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x2786e0; // [100 ] [4 / 4]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x2fa220; // [100 ] [1 / 1]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x27d120; // [100 ] [14 / 14]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x686c0; // [100 ] [12 / 12]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x68b30; // [100 ] [5 / 5]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x5e270; // [100 ] [6 / 6]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x278400; // [83 ] [5 / 6]
		Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + 0xb41a0; // [100 ] [1 / 1]
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0xb42f0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0xaf430; // [100 ] [5 / 5]
		break;
	}
	case ServerName::ANORIA2:
	{
		Globals::pCActorInstanceTestActorCollision = Globals::hEntryBaseAddress + 0x217390; // [100 ] [2 / 2]
		Globals::pCPythonBackgroundGlobalPositionToMapInfo = Globals::hEntryBaseAddress + 0xab830; // [100 ] [1 / 1]
		//Globals::pCInstanceBaseAvoidObject = Globals::hEntryBaseAddress +  0x216F50; 
		Globals::pCInstanceBaseBlockMovement = Globals::hEntryBaseAddress + 0x7dcc0; // [60 ] [3 / 5]
		Globals::pCInstanceBaseGetInstanceType = Globals::hEntryBaseAddress + 0x81300; // [100 ] [6 / 6]
		Globals::pCInstanceBaseGetInstanceVirtualNumber = Globals::hEntryBaseAddress + 0x81320; // [100 ] [6 / 6]
		Globals::pCInstanceBaseGetNameString = Globals::hEntryBaseAddress + 0x80d20; // [72 ] [13 / 18]
		Globals::pCInstanceBaseGetRotation = Globals::hEntryBaseAddress + 0x90110; // [71 ] [10 / 14]
		Globals::pCInstanceBaseIsDead = Globals::hEntryBaseAddress + 0x7f4e0; // [83 ] [5 / 6]
		Globals::pCInstanceBaseIsMountingHorse = Globals::hEntryBaseAddress + 0x7f1b0; // [71 ] [10 / 14]
		Globals::pCInstanceBaseNEW_GetPixelPosition = Globals::hEntryBaseAddress + 0x90030; // [100 ] [14 / 14]
		Globals::pCInstanceBaseNEW_MoveToDestPixelPositionDirection = Globals::hEntryBaseAddress + 0x8fc20; // [100 ] [7 / 7]
		Globals::pCInstanceBaseSCRIPT_SetPixelPosition = Globals::hEntryBaseAddress + 0x8ffd0; // [100 ] [10 / 10]
		Globals::pCInstanceBase__SetAffect = Globals::hEntryBaseAddress + 0x891d0; // [60 ] [3 / 5]
		Globals::pCItemDataGetName = Globals::hEntryBaseAddress + 0x21c1b0; // [80 ] [20 / 25]
		Globals::pCItemManagerGetItemDataPointer = Globals::hEntryBaseAddress + 0x219c20; // [85 ] [12 / 14]
		Globals::pCPythonBackgroundLocalPositionToGlobalPosition = Globals::hEntryBaseAddress + 0xab760; // [60 ] [6 / 10]
		Globals::pCNetworkStreamConnect = Globals::hEntryBaseAddress + 0x1b6490; // [71 ] [15 / 21]
		Globals::pCNetworkStream__DirectEnterMode_Set = Globals::hEntryBaseAddress + 0xec830; // [100 ] [5 / 5]
		Globals::pCNetworkStreamGetAccountCharacterSlotDataz = Globals::hEntryBaseAddress + 0xebfa0; // [100 ] [5 / 5]
		Globals::pCNetworkStreamIsOnline = Globals::hEntryBaseAddress + 0x1b6660; // [100 ] [20 / 20]
		Globals::pCNetworkStreamPeek = Globals::hEntryBaseAddress + 0x1b66d0; // [100 ] [15 / 15]
		Globals::pCNetworkStreamRecv = Globals::hEntryBaseAddress + 0x1b68d0; // [76 ] [10 / 13]
		Globals::pCNetworkStreamSend = Globals::hEntryBaseAddress + 0x1b6910; // [81 ] [13 / 16]
		Globals::pCNetworkStreamSendSequence = Globals::hEntryBaseAddress + 0x1b6990; // [77 ] [37 / 48]
		Globals::pCPhysicsObjectIncreaseExternalForce = Globals::hEntryBaseAddress + 0x235990; // [100 ] [16 / 16]
		Globals::pCPythonApplicationProcess = Globals::hEntryBaseAddress + 0x9d010; // [100 ] [7 / 7]
		Globals::pCPythonApplicationRenderGame = Globals::hEntryBaseAddress + 0x9c660; // [100 ] [39 / 39]
		Globals::pCPythonCharacterManagerGetInstancePtr = Globals::hEntryBaseAddress + 0xb2870; // [100 ] [91 / 91]
		Globals::pCPythonChatAppendChat = Globals::hEntryBaseAddress + 0xbb810; // [87 ] [7 / 8]
		Globals::pCPythonEventManagerRegisterEventSetFromString = Globals::hEntryBaseAddress + 0xc7d50; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamConnectGameServer = Globals::hEntryBaseAddress + 0xec090; // [87 ] [7 / 8]
		Globals::pCPythonNetworkStreamGetMainActorSkillGroup = Globals::hEntryBaseAddress + 0xec770; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xfc850; // [50 ] [1 / 2]
		//Globals::pCPythonNetworkStreamSendAddFlyTargetingPacket = Globals::hEntryBaseAddress + 0xfc8e0; // [50 ] [1 / 2]
		Globals::pCPythonNetworkStreamSendAttackPacket = Globals::hEntryBaseAddress + 0xfc470; // [100 ] [10 / 10]
		Globals::pCPythonNetworkStreamSendCharacterStatePacket = Globals::hEntryBaseAddress + 0xf9b80; // [100 ] [13 / 13]
		Globals::pCPythonNetworkStreamSendChatPacket = Globals::hEntryBaseAddress + 0xf9d50; // [93 ] [15 / 16]
		Globals::pCPythonNetworkStreamSendEmoticon = Globals::hEntryBaseAddress + 0xec910; // [88 ] [8 / 9]
		Globals::pCPythonNetworkStreamSendExchangeAcceptPacket = Globals::hEntryBaseAddress + 0xfb9f0; // [100 ] [12 / 12]
		Globals::pCPythonNetworkStreamSendExchangeItemAddPacket = Globals::hEntryBaseAddress + 0xfb970; // [100 ] [14 / 14]
		Globals::pCPythonNetworkStreamSendExchangeStartPacket = Globals::hEntryBaseAddress + 0xfb860; // [95 ] [21 / 22]
		Globals::pCPythonNetworkStreamSendFishingPacket = Globals::hEntryBaseAddress + 0xfec60; // [87 ] [7 / 8]
		Globals::pCPythonNetworkStreamSendGiveItemPacket = Globals::hEntryBaseAddress + 0xfecc0; // [100 ] [7 / 7]
		Globals::pCPythonNetworkStreamSendItemDropPacketNew = Globals::hEntryBaseAddress + 0x105ab0; // [92 ] [13 / 14]
		Globals::pCPythonNetworkStreamSendItemMovePacket = Globals::hEntryBaseAddress + 0x105ca0; // [66 ] [8 / 12]
		Globals::pCPythonNetworkStreamSendItemPickUpPacket = Globals::hEntryBaseAddress + 0x105ea0; // [93 ] [14 / 15]
		Globals::pCPythonNetworkStreamSendItemUsePacket = Globals::hEntryBaseAddress + 0x1058a0; // [100 ] [9 / 9]
		Globals::pCPythonNetworkStreamSendOnClickPacket = Globals::hEntryBaseAddress + 0xfa9d0; // [93 ] [15 / 16]
		Globals::pCPythonNetworkStreamSendScriptAnswerPacket = Globals::hEntryBaseAddress + 0xfbc60; // [100 ] [11 / 11]
		Globals::pCPythonNetworkStreamSendShootPacket = Globals::hEntryBaseAddress + 0xfc800; // [100 ] [10 / 10]
		Globals::pCPythonNetworkStreamSendShopBuyPacket = Globals::hEntryBaseAddress + 0x1056c0; // [90 ] [10 / 11]
		Globals::pCPythonNetworkStreamSendShopEndPacket = Globals::hEntryBaseAddress + 0x105640; // [100 ] [8 / 8]
		Globals::pCPythonNetworkStreamSendShopSellPacketNew = Globals::hEntryBaseAddress + 0x1057f0; // [100 ] [3 / 3]
		Globals::pCPythonNetworkStreamSendSpecial = Globals::hEntryBaseAddress + 0xfc4e0; // [100 ] [6 / 6]
		Globals::pCPythonNetworkStreamSendUseSkillPacket = Globals::hEntryBaseAddress + 0xf9ce0; // [88 ] [15 / 17]
		Globals::pCPythonNetworkStreamSendWhisperPacket = Globals::hEntryBaseAddress + 0xfa530; // [100 ] [6 / 6]
		Globals::pCPythonNetworkStreamServerCommand = Globals::hEntryBaseAddress + 0xed870; // [100 ] [80 / 80]
	//	Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x81320; // [46 ] [12 / 26]
		Globals::pCPythonNonPlayerGetTable = Globals::hEntryBaseAddress + 0x108780; // [53 ] [14 / 26]
		Globals::pCPythonPlayerClickSkillSlot = Globals::hEntryBaseAddress + 0x127940; // [92 ] [13 / 14]
		//Globals::pCPythonPlayerGetItemIndex = Globals::hEntryBaseAddress + (null); 
		Globals::pCPythonPlayerGetItemMetinSocket = Globals::hEntryBaseAddress + 0x11a9d0; // [100 ] [5 / 5]
		Globals::pCPythonPlayerGetMainCharacterIndex = Globals::hEntryBaseAddress + 0x1198a0; // [62 ] [5 / 8]
		Globals::pCPythonPlayerGetName = Globals::hEntryBaseAddress + 0x119ec0; // [100 ] [11 / 11]
		Globals::pCPythonPlayerGetRace = Globals::hEntryBaseAddress + 0x119a00; // [66 ] [12 / 18]
		Globals::pCPythonPlayerGetStatus = Globals::hEntryBaseAddress + 0x119e90; // [100 ] [13 / 13]
		Globals::pCPythonPlayerGetTargetVID = Globals::hEntryBaseAddress + 0x11ff10; // [77 ] [7 / 9]
		Globals::pCPythonPlayerIsSkillActive = Globals::hEntryBaseAddress + 0x11b690; // [90 ] [9 / 10]
		Globals::pCPythonPlayerIsSkillCoolTime = Globals::hEntryBaseAddress + 0x11b670; // [92 ] [12 / 13]
		Globals::pCPythonPlayerNEW_Fishing = Globals::hEntryBaseAddress + 0x1206e0; // [100 ] [6 / 6]
		Globals::pCPythonPlayerNEW_GetMainActorPtr = Globals::hEntryBaseAddress + 0x1195a0; // [100 ] [43 / 43]
		Globals::pCPythonPlayerSetAttackKeyState = Globals::hEntryBaseAddress + 0x120f30; // [90 ] [10 / 11]
		Globals::pCPythonPlayerSetTarget = Globals::hEntryBaseAddress + 0x11ff40; // [100 ] [8 / 8]
		Globals::pCPythonPlayer__OnClickActor = Globals::hEntryBaseAddress + 0x120400; // [50 ] [2 / 4]
		Globals::pCPythonPlayer__OnPressActor = Globals::hEntryBaseAddress + 0x120270; // [100 ] [2 / 2]
		Globals::pCGraphicTextureGetD3DTexture = Globals::hEntryBaseAddress + 0x1dd4a0; // [96 ] [27 / 28]
		Globals::pCResourceManagerGetResourcePointer = Globals::hEntryBaseAddress + 0x1be3c0; // [92 ] [65 / 70]
		Globals::pCGraphicImageGetTexturePointer = Globals::hEntryBaseAddress + 0x1c12b0; // [93 ] [14 / 15]
		Globals::pPyCallClassMemberFunc = Globals::hEntryBaseAddress + 0x26dc70; // [100 ] [8 / 8]
		Globals::pCInputKeyboardUpdateKeyboard = Globals::hEntryBaseAddress + 0x1c7ca0; // [100 ] [11 / 11]
		Globals::pCInstanceBaseIsWaiting = Globals::hEntryBaseAddress + 0x8fb60; // [85 ] [6 / 7]
		Globals::pCInstanceBaseSetRotation = Globals::hEntryBaseAddress + 0x90060; // [100 ] [7 / 7]
		Globals::pCInstanceBase__GetBackgroundHeight = Globals::hEntryBaseAddress + 0x7dff0; // [100 ] [3 / 3]
		Globals::pCResourceReload = Globals::hEntryBaseAddress + 0x1c0fb0; // [100 ] [5 / 5]
		//Globals::pCPythonPlayerGetItemCount = Globals::hEntryBaseAddress + (null); 
		Globals::pCPythonPlayerGetItemAttribute = Globals::hEntryBaseAddress + 0x11aa70; // [100 ] [4 / 4]
		Globals::pCPythonNetworkStreamSendItemUseToItemPacket = Globals::hEntryBaseAddress + 0x1059a0; // [100 ] [8 / 8]
	}
	}

}

void Globals::ReAddressingPython()
{
	//player
	CythonPlayerGetStatus = PythonExtension::ModulesMap["playerGetStatus"];
	CythonPlayerGetMainCharacterIndex = PythonExtension::ModulesMap["playerGetMainCharacterIndex"];
	CythonPlayerGetItemIndex = PythonExtension::ModulesMap["playerGetItemIndex"];
	CythonPlayerGetItemIndex = PythonExtension::ModulesMap["playerGetItemCount"];
	CythonPlayerGetName = PythonExtension::ModulesMap["playerGetName"];
	CythonPlayerGetItemMetinSocket = PythonExtension::ModulesMap["playerGetItemMetinSocket"];
	CythonPlayerGetRace = PythonExtension::ModulesMap["playerGetRace"];
	CythonPlayerSetSingleDIKKeyState = PythonExtension::ModulesMap["playerSetSingleDIKKeyState"];
	CythonPlayerClickSkillSlot = PythonExtension::ModulesMap["playerClickSkillSlot"];
	CythonPlayerIsSkillCoolTime = PythonExtension::ModulesMap["playerIsSkillCoolTime"];
	CythonPlayerIsSkillActive = PythonExtension::ModulesMap["playerIsSkillActive"];
	CythonPlayerGetTargetVID = PythonExtension::ModulesMap["playerGetTargetVID"];
	CythonPlayerSetTarget = PythonExtension::ModulesMap["playerSetTarget"];
	CythonPlayerSetAttackKeyState = PythonExtension::ModulesMap["playerSetAttackKeyState"];
	CythonPlayerIsMountingHorse = PythonExtension::ModulesMap["playerIsMountingHorse"];
	//chr
	CythonChrSelectInstance = PythonExtension::ModulesMap["chrSelectInstance"];
	CythonChrGetPixelPosition = PythonExtension::ModulesMap["chrGetPixelPosition"];
	CythonChrMoveToDestPosition = PythonExtension::ModulesMap["chrMoveToDestPosition"];
	CythonChrGetInstanceType = PythonExtension::ModulesMap["chrGetInstanceType"];
	CythonChrGetVirtualNumber = PythonExtension::ModulesMap["chrGetVirtualNumber"];
	CythonChrGetNameByVID = PythonExtension::ModulesMap["chrGetNameByVID"];
	CythonChrSetPixelPosition = PythonExtension::ModulesMap["chrSetPixelPosition"];
	CythonChrSetRotation = PythonExtension::ModulesMap["chrSetRotation"];
	CythonChrGetRotation = PythonExtension::ModulesMap["chrGetRotation"];
	CythonChrmgrSetAffect = PythonExtension::ModulesMap["chrmgrSetAffect"];
	//net
	CythonNetSendItemUsePacket = PythonExtension::ModulesMap["netSendItemUsePacket"];
	CythonNetSendChatPacket = PythonExtension::ModulesMap["netSendChatPacket"];
	CythonNetSendRefinePacket = PythonExtension::ModulesMap["netSendRefinePacket"];
	CythonNetSendExchangeStartPacket = PythonExtension::ModulesMap["netSendExchangeStartPacket"];
	CythonNetSendExchangeItemAddPacket = PythonExtension::ModulesMap["netSendExchangeItemAddPacket"];
	CythonNetSendExchangeAcceptPacket = PythonExtension::ModulesMap["netSendExchangeAcceptPacket"];
	CythonNetSendWhisperPacket = PythonExtension::ModulesMap["netSendWhisperPacket"];
	CythonNetSendItemPickUpPacket = PythonExtension::ModulesMap["netSendItemPickUpPacket"];
	CythonNetSendItemDropPacketNew = PythonExtension::ModulesMap["netSendItemDropPacketNew"];
	CythonNetSendOnClickPacket = PythonExtension::ModulesMap["netOnClickPacket"];
	CythonNetSendShopSellPacketNew = PythonExtension::ModulesMap["netSendShopSellPacketNew"];
	CythonNetSendShopBuyPacket = PythonExtension::ModulesMap["netSendShopBuyPacket"];
	CythonNetSendShopEndPacket = PythonExtension::ModulesMap["netSendShopEndPacket"];
	CythonNetSendGiveItemPacket = PythonExtension::ModulesMap["netSendGiveItemPacket"];
	CythonNetSendItemMovePacket = PythonExtension::ModulesMap["netSendItemMovePacket"];
	CythonNetDirectEnter = PythonExtension::ModulesMap["netDirectEnter"];
	CythonNetConnectTCP = PythonExtension::ModulesMap["netConnectTCP"];
	CythonNetIsConnect = PythonExtension::ModulesMap["netIsConnect"];
	CythonNetGetMainActorSkillGroup = PythonExtension::ModulesMap["netGetMainActorSkillGroup"];
	CythonNetGetAccountCharacterSlotData = PythonExtension::ModulesMap["netGetAccountCharacterSlotDataString"];
	CythonNetSendCommandPacket = PythonExtension::ModulesMap["netSendCommandPacket"];
	//event
	CythonEventSelectAnswer = PythonExtension::ModulesMap["eventSelectAnswer"];
	//item
	CythonItemSelectItem = PythonExtension::ModulesMap["itemSelectItem"];
	CythonItemGetItemName = PythonExtension::ModulesMap["itemGetItemName"];
}

void Globals::ReDeclarationInstances()
{
	if (!GetModuleHandle("python27.dll"))
	{
		switch (Globals::Server)
		{
		case ServerName::EGORIA:
			break;
		case ServerName::GLEVIA:
			break;
		case ServerName::TASTRIA2:
			break;
		default:
		{
			Globals::PyRun_SimpleStringFlags = (tPyRun_SimpleStringFlags)PatternScan::FindPattern("55 8B EC 83 EC ? 68 ? ? ? ? E8 ? ? ? ? 83 C4 ? 89 45 ? 83 7D ? ? 75 ? 83 C8");
			Globals::PyString_AsString = (tPyString_AsString)PatternScan::FindPattern("55 8B EC 8B 45 ? 8B 48 ? 8B 51 ? 81 E2 ? ? ? ? 75 ? 8B 45 ? 50 E8 ? ? ? ? 83 C4 ? EB ? 8B 45");
			Globals::PyTuple_GetItem = (tPyTuple_GetItem)PatternScan::FindPattern("55 8B EC 8B 45 ? 8B 48 ? 8B 51 ? 81 E2 ? ? ? ? 75 ? 6A ? 68 ? ? ? ? E8 ? ? ? ? 83 C4 ? 33 C0");
			Globals::PyInt_AsLong = (tPyInt_AsLong)PatternScan::FindPattern("55 8B EC 83 EC ? 83 7D ? ? 74 ? 8B 45 ? 8B 48 ? 8B 51 ? 81 E2 ? ? ? ? 74 ? 8B 45 ? 8B 40 ? E9 ? ? ? ? 83 7D ? ? 74 ? 8B 4D ? 8B 51 ? 8B 42 ? 89 45");
			Globals::Py_BuildValue = (tPy_BuildValue)PatternScan::FindPattern("");
			break;
		}
		}
	}
	else
	{
		Globals::PyRun_SimpleStringFlags = (tPyRun_SimpleStringFlags)GetProcAddress(GetModuleHandle("python27.dll"), "PyRun_SimpleString");
		Globals::PyString_AsString = (tPyString_AsString)GetProcAddress(GetModuleHandle("python27.dll"), "PyString_AsString");
		Globals::PyTuple_GetItem = (tPyTuple_GetItem)GetProcAddress(GetModuleHandle("python27.dll"), "PyTuple_GetItem");
		Globals::PyInt_AsLong = (tPyInt_AsLong)GetProcAddress(GetModuleHandle("python27.dll"), "PyInt_AsLong");
		Globals::Py_BuildValue = (tPy_BuildValue)GetProcAddress(GetModuleHandle("python27.dll"), "Py_BuildValue");

	}
	if (pCPythonCharacterManagerInstance != NULL)
	{
		Globals::iCPythonCharacterManagerInstance = *reinterpret_cast<DWORD*>(pCPythonCharacterManagerInstance);
	}
	if (pCResourceManagerInstance != NULL)
	{
		Globals::iCResourceManagerInstance = *reinterpret_cast<DWORD*>(pCResourceManagerInstance);
	}
	if (pCPythonPlayerInstance != NULL)
	{
		Globals::iCPythonPlayerInstance = *reinterpret_cast<DWORD*>(pCPythonPlayerInstance);
		printf(XOR("PlayerInstance: 0x%x\n"), Globals::iCPythonPlayerInstance);
	}
	if (pCPythonNonPlayerInstance != NULL)
	{
		Globals::iCPythonNonPlayerInstance = *reinterpret_cast<DWORD*>(pCPythonNonPlayerInstance);
	}
	if (pCPythonNetworkStreamInstance != NULL)
	{
		Globals::iCPythonNetworkStreamInstance = *reinterpret_cast<DWORD*>(pCPythonNetworkStreamInstance);
	}
	if (pCItemManagerInstance != NULL)
	{
		Globals::iCItemManagerInstance = *reinterpret_cast<DWORD*>(pCItemManagerInstance);
	}
	if (pCPythonItemInstance != NULL)
	{
		Globals::iCPythonItemInstance = *reinterpret_cast<DWORD*>(pCPythonItemInstance);
	}
	if (pCPythonApplicationInstance != NULL)
	{
		Globals::iCPythonApplicationInstance = *reinterpret_cast<DWORD*>(pCPythonApplicationInstance);
	}
	if (pCPythonBackgroundInstance != NULL)
	{
		Globals::iCPythonBackgroundInstance = *reinterpret_cast<DWORD*>(pCPythonBackgroundInstance);
	}
}

void Globals::ReDeclarationLocals()
{
	if (pPyCallClassMemberFunc != NULL)
	{
		PyCallClassMemberFunc = (tPyCallClassMemberFunc)(pPyCallClassMemberFunc);
	}
	if (pCNetworkStreamRecv != NULL)
	{
		CNetworkStreamRecv = (tCNetworkStreamRecv)(Globals::pCNetworkStreamRecv);
	}
	if (pCNetworkStreamSend != NULL)
	{
		CNetworkStreamSend = (tCNetworkStreamSend)(Globals::pCNetworkStreamSend);
	}
	if (pCPythonNetworkStreamSendItemUsePacket != NULL)
	{
		CPythonNetworkStreamSendItemUsePacket = (tCPythonNetworkStreamSendItemUsePacket)(Globals::pCPythonNetworkStreamSendItemUsePacket);
	}
	if (pCPythonNetworkStreamSendItemUseToItemPacket != NULL)
	{
		CPythonNetworkStreamSendItemUseToItemPacket = (tCPythonNetworkStreamSendItemUseToItemPacket)(Globals::pCPythonNetworkStreamSendItemUseToItemPacket);
	}
	if (pCPythonPlayerNEW_Fishing != NULL)
	{
		CPythonPlayerNEW_Fishing = (tCPythonPlayerNEW_Fishing)(Globals::pCPythonPlayerNEW_Fishing);
	}
	if (pCPythonChatAppendChat != NULL)
	{
		CPythonChatAppendChat = (tCPythonChatAppendChat)(Globals::pCPythonChatAppendChat);
	}
	if (pCPythonPlayerSetAttackKeyState != NULL)
	{
		CPythonPlayerSetAttackKeyState = (tCPythonPlayerSetAttackKeyState)(Globals::pCPythonPlayerSetAttackKeyState);
	}
	if (pCPythonNetworkStreamSendFishingPacket != NULL)
	{
		CPythonNetworkStreamSendFishingPacket = (tCPythonNetworkStreamSendFishingPacket)(Globals::pCPythonNetworkStreamSendFishingPacket);
	}
	if (pCPythonNetworkStreamSendFishingQuitPacket != NULL)
	{
		CPythonNetworkStreamSendFishingQuitPacket = (tCPythonNetworkStreamSendFishingQuitPacket)(Globals::pCPythonNetworkStreamSendFishingQuitPacket);
	}
	if (pCPythonNetworkStreamSendEmoticon != NULL)
	{
		CPythonNetworkStreamSendEmoticon = (tCPythonNetworkStreamSendEmoticon)(Globals::pCPythonNetworkStreamSendEmoticon);
	}
	if (pCPythonNetworkStreamSendItemPickUpPacket != NULL)
	{
		CPythonNetworkStreamSendItemPickUpPacket = (tCPythonNetworkStreamSendItemPickUpPacket)(pCPythonNetworkStreamSendItemPickUpPacket);;
	}
	if (pCPythonPlayerNEW_GetMainActorPtr != NULL)
	{
		CPythonPlayerNEW_GetMainActorPtr = (tCPythonPlayerNEW_GetMainActorPtr)(pCPythonPlayerNEW_GetMainActorPtr);
	}
	if (pCInstanceBaseIsMountingHorse != NULL)
	{
		CInstanceBaseIsMountingHorse = (tCInstanceBaseIsMountingHorse)(pCInstanceBaseIsMountingHorse);
	}
	if (pCPythonNetworkStreamSendChatPacket != NULL)
	{
		CPythonNetworkStreamSendChatPacket = (tCPythonNetworkStreamSendChatPacket)(pCPythonNetworkStreamSendChatPacket);
	}
	if (pCPythonPlayerIsSkillCoolTime != NULL)
	{
		CPythonPlayerIsSkillCoolTime = (tCPythonPlayerIsSkillCoolTime)(pCPythonPlayerIsSkillCoolTime);
	}
	if (pCPythonPlayerClickSkillSlot != NULL)
	{
		CPythonPlayerClickSkillSlot = (tCPythonPlayerClickSkillSlot)(pCPythonPlayerClickSkillSlot);
	}
	if (pCPythonCharacterManagerGetInstancePtr != NULL)
	{
		CPythonCharacterManagerGetInstancePtr = (tCPythonCharacterManagerGetInstancePtr)(pCPythonCharacterManagerGetInstancePtr);
	}
	if (pCPythonNetworkStreamSendChatPacket != NULL)
	{
		CPythonNetworkStreamSendChatPacket = (tCPythonNetworkStreamSendChatPacket)(pCPythonNetworkStreamSendChatPacket);
	}
	if (pCPythonPlayerGetTargetVID != NULL)
	{
		CPythonPlayerGetTargetVID = (tCPythonPlayerGetTargetVID)(pCPythonPlayerGetTargetVID);
	}
	if (pCInstanceBaseGetNameString != NULL)
	{
		CInstanceBaseGetNameString = (tCInstanceBaseGetNameString)(pCInstanceBaseGetNameString);
	}
	if (pCPythonPlayerGetItemMetinSocket != NULL)
	{
		CPythonPlayerGetItemMetinSocket = (tCPythonPlayerGetItemMetinSocket)(pCPythonPlayerGetItemMetinSocket);
	}
	if (pCPythonPlayerGetItemAttribute != NULL)
	{
		CPythonPlayerGetItemAttribute = (tCPythonPlayerGetItemAttribute)(pCPythonPlayerGetItemAttribute);
	}
	if (pCInstanceBaseGetInstanceType != NULL)
	{
		CInstanceBaseGetInstanceType = (tCInstanceBaseGetInstanceType)(pCInstanceBaseGetInstanceType);
	}
	if (pCPythonNetworkStreamSendExchangeStartPacket != NULL)
	{
		CPythonNetworkStreamSendExchangeStartPacket = (tCPythonNetworkStreamSendExchangeStartPacket)(pCPythonNetworkStreamSendExchangeStartPacket);
	}
	if (pCPythonNetworkStreamSendExchangeItemAddPacket != NULL)
	{
		CPythonNetworkStreamSendExchangeItemAddPacket = (tCPythonNetworkStreamSendExchangeItemAddPacket)(pCPythonNetworkStreamSendExchangeItemAddPacket);
	}
	if (pCPythonNetworkStreamSendExchangeAcceptPacket != NULL)
	{
		CPythonNetworkStreamSendExchangeAcceptPacket = (tCPythonNetworkStreamSendExchangeAcceptPacket)(pCPythonNetworkStreamSendExchangeAcceptPacket);
	}
	if (pCPythonPlayerGetMainCharacterIndex != NULL)
	{
		CPythonPlayerGetMainCharacterIndex = (tCPythonPlayerGetMainCharacterIndex)(pCPythonPlayerGetMainCharacterIndex);
	}
	if (pCPythonNetworkStreamSendUseSkillPacket != NULL)
	{
		CPythonNetworkStreamSendUseSkillPacket = (tCPythonNetworkStreamSendUseSkillPacket)(pCPythonNetworkStreamSendUseSkillPacket);
	}
	if (pCPythonNetworkStreamSendAddFlyTargetingPacket != NULL)
	{
		CPythonNetworkStreamSendAddFlyTargetingPacket = (tCPythonNetworkStreamSendAddFlyTargetingPacket)(pCPythonNetworkStreamSendAddFlyTargetingPacket);
	}
	if (pCPythonNetworkStreamSendShootPacket != NULL)
	{
		CPythonNetworkStreamSendShootPacket = (tCPythonNetworkStreamSendShootPacket)(pCPythonNetworkStreamSendShootPacket);
	}
	if (pCPythonPlayerGetStatus != NULL)
	{
		CPythonPlayerGetStatus = (tCPythonPlayerGetStatus)(pCPythonPlayerGetStatus);
	}
	if (pCInstanceBaseNEW_MoveToDestPixelPositionDirection != NULL)
	{
		CInstanceBaseNEW_MoveToDestPixelPositionDirection = (tCInstanceBaseNEW_MoveToDestPixelPositionDirection)(pCInstanceBaseNEW_MoveToDestPixelPositionDirection);
	}
	if (pCInstanceBaseNEW_GetPixelPosition != NULL)
	{
		CInstanceBaseNEW_GetPixelPosition = (tCInstanceBaseNEW_GetPixelPosition)(pCInstanceBaseNEW_GetPixelPosition);
	}
	if (pCPhysicsObjectIncreaseExternalForce != NULL)
	{
		CPhysicsObjectIncreaseExternalForce = (tCPhysicsObjectIncreaseExternalForce)(pCPhysicsObjectIncreaseExternalForce);
	}
	if (pCPythonPlayerGetName != NULL)
	{
		CPythonPlayerGetName = (tCPythonPlayerGetName)(pCPythonPlayerGetName);
	}
	if (pCPythonPlayerGetRace != NULL)
	{
		CPythonPlayerGetRace = (tCPythonPlayerGetRace)(pCPythonPlayerGetRace);
	}
	if (pCPythonPlayerGetItemIndex != NULL)
	{
		CPythonPlayerGetItemIndex = (tCPythonPlayerGetItemIndex)(pCPythonPlayerGetItemIndex);
	}
	if (pCItemDataGetName != NULL)
	{
		CItemDataGetName = (tCItemDataGetName)(pCItemDataGetName);
	}
	if (pCItemManagerGetItemDataPointer != NULL)
	{
		CItemManagerGetItemDataPointer = (tCItemManagerGetItemDataPointer)(pCItemManagerGetItemDataPointer);
	}
	if (pCPythonNetworkStreamSendItemDropPacketNew != NULL)
	{
		CPythonNetworkStreamSendItemDropPacketNew = (tCPythonNetworkStreamSendItemDropPacketNew)(pCPythonNetworkStreamSendItemDropPacketNew);
	}
	if (pCPythonNetworkStreamSendScriptAnswerPacket != NULL)
	{
		CPythonNetworkStreamSendScriptAnswerPacket = (tCPythonNetworkStreamSendScriptAnswerPacket)(pCPythonNetworkStreamSendScriptAnswerPacket);
	}
	if (pCPythonNetworkStreamSendOnClickPacket != NULL)
	{
		CPythonNetworkStreamSendOnClickPacket = (tCPythonNetworkStreamSendOnClickPacket)(pCPythonNetworkStreamSendOnClickPacket);
	}
	if (pCPythonPlayerReviveGlobal != NULL)
	{
		CPythonPlayerReviveGlobal = (tCPythonPlayerReviveGlobal)(pCPythonPlayerReviveGlobal);
	}
	if (pCInstanceBaseBlockMovement != NULL)
	{
		CInstanceBaseBlockMovement = (tCInstanceBaseBlockMovement)(pCInstanceBaseBlockMovement);
	}
	if (pCPythonPlayerIsSkillActive != NULL)
	{
		CPythonPlayerIsSkillActive = (tCPythonPlayerIsSkillActive)(pCPythonPlayerIsSkillActive);
	}
	if (pCPythonNetworkStreamSendItemMovePacket != NULL)
	{
		CPythonNetworkStreamSendItemMovePacket = (tCPythonNetworkStreamSendItemMovePacket)(pCPythonNetworkStreamSendItemMovePacket);
	}
	if (pCNetworkStreamSendSequence != NULL)
	{
		CNetworkStreamSendSequence = (tCNetworkStreamSendSequence)(pCNetworkStreamSendSequence);
	}
	if (pCPythonNetworkStreamSendCharacterStatePacket != NULL)
	{
		CPythonNetworkStreamSendCharacterStatePacket = (tCPythonNetworkStreamSendCharacterStatePacket)(pCPythonNetworkStreamSendCharacterStatePacket);
	}
	if (pCPythonNetworkStreamConnectGameServer != NULL)
	{
		CPythonNetworkStreamConnectGameServer = (tCPythonNetworkStreamConnectGameServer)(pCPythonNetworkStreamConnectGameServer);
	}
	if (pCNetworkStreamIsOnline != NULL)
	{
		CNetworkStreamIsOnline = (tCNetworkStreamIsOnline)(pCNetworkStreamIsOnline);
	}
	if (pCPythonApplicationRenderGame != NULL)
	{
		CPythonApplicationRenderGame = (tCPythonApplicationRenderGame)(pCPythonApplicationRenderGame);
	}
	if (pCPythonNetworkStreamGetMainActorSkillGroup != NULL)
	{
		CPythonNetworkStreamGetMainActorSkillGroup = (tCPythonNetworkStreamGetMainActorSkillGroup)(pCPythonNetworkStreamGetMainActorSkillGroup);
	}
	if (pCPythonNetworkStreamSendWhisperPacket != NULL)
	{
		CPythonNetworkStreamSendWhisperPacket = (tCPythonNetworkStreamSendWhisperPacket)(pCPythonNetworkStreamSendWhisperPacket);
	}
	if (pCPythonNetworkStreamSendSpecial != NULL)
	{
		CPythonNetworkStreamSendSpecial = (tCPythonNetworkStreamSendSpecial)(pCPythonNetworkStreamSendSpecial);
	}
	if (pCPythonNetworkStreamSendAttackPacket != NULL)
	{
		CPythonNetworkStreamSendAttackPacket = (tCPythonNetworkStreamSendAttackPacket)(pCPythonNetworkStreamSendAttackPacket);
	}
	if (pCInstanceBase__SetAffect != NULL)
	{
		CInstanceBase__SetAffect = (tCInstanceBase__SetAffect)(pCInstanceBase__SetAffect);
	}
	if (pCInstanceBaseAvoidObject != NULL)
	{
		CInstanceBaseAvoidObject = (tCInstanceBaseAvoidObject)(pCInstanceBaseAvoidObject);
	}
	if (pCPythonPlayer__OnPressActor != NULL)
	{
		CPythonPlayer__OnPressActor = (tCPythonPlayer__OnPressActor)(pCPythonPlayer__OnPressActor);
	}
	if (pCPythonPlayer__OnClickActor != NULL)
	{
		CPythonPlayer__OnClickActor = (tCPythonPlayer__OnClickActor)(pCPythonPlayer__OnClickActor);
	}
	if (pCInstanceBaseIsDead != NULL)
	{
		CInstanceBaseIsDead = (tCInstanceBaseIsDead)(pCInstanceBaseIsDead);
	}
	if (pCActorInstanceTestActorCollision != NULL)
	{
		CActorInstanceTestActorCollision = (tCActorInstanceTestActorCollision)(pCActorInstanceTestActorCollision);
	}
	if (pCInstanceBaseSCRIPT_SetPixelPosition != NULL)
	{
		CInstanceBaseSCRIPT_SetPixelPosition = (tCInstanceBaseSCRIPT_SetPixelPosition)(pCInstanceBaseSCRIPT_SetPixelPosition);
	}
	if (pCPythonPlayerNEW_SetSingleDIKKeyState != NULL)
	{
		CPythonPlayerNEW_SetSingleDIKKeyState = (tCPythonPlayerNEW_SetSingleDIKKeyState)(pCPythonPlayerNEW_SetSingleDIKKeyState);
	}

	if (pCPythonEventManagerRegisterEventSetFromString != NULL)
	{
		CPythonEventManagerRegisterEventSetFromString = (tCPythonEventManagerRegisterEventSetFromString)(pCPythonEventManagerRegisterEventSetFromString);
	}
	if (pCPythonApplicationProcess != NULL)
	{
		CPythonApplicationProcess = (tCPythonApplicationProcess)(pCPythonApplicationProcess);
	}
	if (pCInstanceBaseNEW_LookAtDestPixelPosition != NULL)
	{
		CInstanceBaseNEW_LookAtDestPixelPosition = (tCInstanceBaseNEW_LookAtDestPixelPosition)(pCInstanceBaseNEW_LookAtDestPixelPosition);
	}
	if (pCPythonNetworkStreamServerCommand != NULL)
	{
		CPythonNetworkStreamServerCommand = (tCPythonNetworkStreamServerCommand)(pCPythonNetworkStreamServerCommand);
	}
	if (pCInstanceBaseGetRotation != NULL)
	{
		CInstanceBaseGetRotation = (tCInstanceBaseGetRotation)(pCInstanceBaseGetRotation);
	}
	if (pCPythonPlayerSetTarget != NULL)
	{
		CPythonPlayerSetTarget = (tCPythonPlayerSetTarget)(pCPythonPlayerSetTarget);
	}
	if (pCPythonNonPlayerGetTable != NULL)
	{
		CPythonNonPlayerGetTable = (tCPythonNonPlayerGetTable)(pCPythonNonPlayerGetTable);
	}
	if (pCPythonBackgroundLocalPositionToGlobalPosition != NULL)
	{
		CPythonBackgroundLocalPositionToGlobalPosition = (tCPythonBackgroundLocalPositionToGlobalPosition)(pCPythonBackgroundLocalPositionToGlobalPosition);
	}
	if (pCPythonBackgroundGlobalPositionToMapInfo != NULL)
	{
		CPythonBackgroundGlobalPositionToMapInfo = (tCPythonBackgroundGlobalPositionToMapInfo)(pCPythonBackgroundGlobalPositionToMapInfo);
	}
	if (pCNetworkStreamGetAccountCharacterSlotDataz != NULL)
	{
		CNetworkStreamGetAccountCharacterSlotDataz = (tCNetworkStreamGetAccountCharacterSlotDataz)(pCNetworkStreamGetAccountCharacterSlotDataz);
	}
	if (pCNetworkStreamConnect != NULL)
	{
		CNetworkStreamConnect = (tCNetworkStreamConnect)(pCNetworkStreamConnect);
	}
	if (pCNetworkStream__DirectEnterMode_Set != NULL)
	{
		CNetworkStream__DirectEnterMode_Set = (tCNetworkStream__DirectEnterMode_Set)(pCNetworkStream__DirectEnterMode_Set);
	}
	if (pCPythonNetworkStreamSendRefinePacket != NULL)
	{
		CPythonNetworkStreamSendRefinePacket = (tCPythonNetworkStreamSendRefinePacket)(pCPythonNetworkStreamSendRefinePacket);
	}
	if (pCPythonNetworkStreamSendShopSellPacketNew != NULL)
	{
		CPythonNetworkStreamSendShopSellPacketNew = (tCPythonNetworkStreamSendShopSellPacketNew)(pCPythonNetworkStreamSendShopSellPacketNew);
	}
	if (pCPythonNetworkStreamSendShopBuyPacket != NULL)
	{
		CPythonNetworkStreamSendShopBuyPacket = (tCPythonNetworkStreamSendShopBuyPacket)(pCPythonNetworkStreamSendShopBuyPacket);
	}
	if (pCPythonNetworkStreamSendShopEndPacket != NULL)
	{
		CPythonNetworkStreamSendShopEndPacket = (tCPythonNetworkStreamSendShopEndPacket)(pCPythonNetworkStreamSendShopEndPacket);
	}
	if (pCPythonNetworkStreamSendGiveItemPacket != NULL)
	{
		CPythonNetworkStreamSendGiveItemPacket = (tCPythonNetworkStreamSendGiveItemPacket)(pCPythonNetworkStreamSendGiveItemPacket);
	}
	if (pCInstanceBaseGetInstanceVirtualNumber != NULL)
	{
		CInstanceBaseGetInstanceVirtualNumber = (tCInstanceBaseGetInstanceVirtualNumber)(pCInstanceBaseGetInstanceVirtualNumber);
	}
	if (pCInputKeyboardUpdateKeyboard != NULL)
	{
		CInputKeyboardUpdateKeyboard = (tCInputKeyboardUpdateKeyboard)(pCInputKeyboardUpdateKeyboard);
	}
	if (pCInstanceBaseIsWaiting != NULL)
	{
		CInstanceBaseIsWaiting = (tCInstanceBaseIsWaiting)(pCInstanceBaseIsWaiting);
	}
	if (pCInstanceBaseSetRotation != NULL)
	{
		CInstanceBaseSetRotation = (tCInstanceBaseSetRotation)(pCInstanceBaseSetRotation);
	}
	if (pCPythonNetworkStreamSendCommandPacket != NULL)
	{
		CPythonNetworkStreamSendCommandPacket = (tCPythonNetworkStreamSendCommandPacket)(pCPythonNetworkStreamSendCommandPacket);
	}
	if (pCInstanceBase__GetBackgroundHeight != NULL)
	{
		CInstanceBase__GetBackgroundHeight = (tCInstanceBase__GetBackgroundHeight)(pCInstanceBase__GetBackgroundHeight);
	}
	if (pCPythonPlayerGetItemCount != NULL)
	{
		CPythonPlayerGetItemCount = (tCPythonPlayerGetItemCount)(pCPythonPlayerGetItemCount);
	}
	if (pCResourceManagerGetResourcePointer != NULL)
	{
		CResourceManagerGetResourcePointer = (tCResourceManagerGetResourcePointer)(pCResourceManagerGetResourcePointer);
	}
	if (pCGraphicImageGetTexturePointer != NULL)
	{
		CGraphicImageGetTexturePointer = (tCResourceManagerGetTexturePointer)(pCGraphicImageGetTexturePointer);
	}
	if (pCGraphicTextureGetD3DTexture != NULL)
	{
		CGraphicTextureGetD3DTexture = (tCResourceManagerGetD3DTexture)(pCGraphicTextureGetD3DTexture);
	}
	if (pCResourceReload != NULL)
	{
		CResourceReload = (tCResourceReload)(pCResourceReload);
	}
}

//#####################################################################################################################################}

