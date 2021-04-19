#pragma once


class GameFunctionsCustom
{
public:
	//#################################################################################################################################
	static int GetWindowWidth()
	{
		RECT rc;
		GetClientRect(Globals::mainHwnd, &rc);
		int windowWidth = rc.right - rc.left;
		int windowHeight = (rc.bottom - rc.top);
		return windowWidth;
	}
	//#################################################################################################################################
	static int GetWindowHeight()
	{
		RECT rc;
		GetClientRect(Globals::mainHwnd, &rc);
		int windowHeight = (rc.bottom - rc.top);
		return windowHeight - 60;
	}
	//#################################################################################################################################
	static int GetHpProcentageStatus()
	{
		int hp = GameFunctions::PlayerGetStatus(POINT_HP);
		int maxHp = GameFunctions::PlayerGetStatus(POINT_MAX_HP);
		return (hp * 100) / maxHp;
	}
	//#################################################################################################################################
	static int GetMpProcentageStatus()
	{
		int mp = GameFunctions::PlayerGetStatus(POINT_SP);
		int maxMp = GameFunctions::PlayerGetStatus(POINT_MAX_SP);
		return (mp * 100) / maxMp;
	}
	//#################################################################################################################################
	static int FindItemSlotInInventoryByName(const char* itemName)
	{
		for (int i = 0; i > (45 * 5); i++)
		{
			int vnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (vnum == 0)
			{
				continue;
			}
			DWORD* cItemData = NULL;
			GameFunctions::ItemManagerGetItemDataPointer(i, &cItemData);
			if (cItemData)
			{
				const char* name = "";
				name = GameFunctions::ItemDataGetName(vnum);
				if (StringExtension::Equals(itemName, name))
				{
					return i;
				}
			}
		}
		return -1;
	}
	//
	static void ItemSplitter(int item_slot, int packs, int count)
	{
		int current_pack = 0;
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			int current_vnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (current_vnum == 0)
			{
				GameFunctions::NetworkStreamSendItemMovePacket(TItemPos(INVENTORY, item_slot), TItemPos(INVENTORY, i), count);
				current_pack++;
			}
			if (current_pack == packs)
			{
				break;
			}
		}
	}
	//#################################################################################################################################
	static const char* PlayerGetName()
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance)
		{
			GameFunctions::InstanceBaseGetNameString(instance);
		}
		else
		{
			return NULL;
		}
	}
	static string PlayerGetNameString()
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance)
		{
			return string(GameFunctions::InstanceBaseGetNameString(instance));
		}
		else
		{
			return "";
		}
	}
	static int GetCharSlotByName(string playerName)
	{
		for (int i = 0; i < 8; i++)
		{
			string slotName;
			if (Globals::Server == ServerName::METINPL)
			{
				slotName = GameFunctions::NetworkStreamGetAccountCharacterSlotDataz(i, 0);
			}
			else
			{
				slotName = GameFunctions::NetworkStreamGetAccountCharacterSlotDataz(i, 1);
			}
			if (slotName != "" && slotName == playerName)
			{
				return i;
			}
		}
		return -1;
	}
	//#################################################################################################################################
	static bool PlayerIsInstance()
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	static int	InstanceGetInstanceTypeByVID(DWORD vid)
	{
		DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (pTargetInstance != NULL)
		{
			return	GameFunctions::InstanceBaseGetInstanceType(pTargetInstance);
		}
		else
		{
			return -1;
		}

	}
	//#################################################################################################################################
	static bool InstanceIsDead(DWORD vid)
	{
		DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (pTargetInstance != NULL)
		{
			return	GameFunctions::InstanceBaseIsDead(pTargetInstance);
		}
		else
		{
			return true;
		}
	}
	//#################################################################################################################################
	static bool PlayerIsDead()
	{
		DWORD* ptr = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (ptr)
		{
			return GameFunctions::InstanceBaseIsDead(ptr);
		}
		else
		{
			return true;
		}
	}
	//#################################################################################################################################
	static void PlayerRevive()
	{
		switch (Globals::Server)
		{
			case ServerName::METINPL:
			{
				GameFunctions::NetworkStreamSendCommandPacket(5, 1, "");
				break;
			}
			case ServerName::ORIGINS2:
			{
				GameFunctions::NetworkStreamSendChatPacket("/zhcedqrmoacnwtkr", CHAT_TYPE_TALKING);
				break;
			}
			default:
			{
				GameFunctions::NetworkStreamSendChatPacket("/restart_here", CHAT_TYPE_TALKING);
				break;
			}
		}
	}
	//#################################################################################################################################
	static bool PlayerIsMountingHorse()
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance)
		{
			return GameFunctions::InstanceBaseIsMountingHorse(instance);
		}
		else
		{
			return false;
		}
	}
	//#################################################################################################################################
	static bool PlayerCanRefineRod()
	{
		if ( GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4)) == 27600)
		{

			return false;
		}
		else
		{
			return true;
		}
	}
	static bool PlayerIsRodEquipped()
	{

		if (GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4)) == 27400 || GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4)) == 27600)
		{
			
			return true;
		}
		else if (GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4)) > 27400 && GameFunctions::PlayerGetItemIndex(TItemPos(EQUIPMENT, 4)) < 27600)
		{
			return true;
		}
		
		else
		{
			return false;
		}

	}
	//#################################################################################################################################
	static bool PlayerIsPickAxeEquipped()
	{
		return true;
	}
	//#################################################################################################################################
	static bool PlayerIsBowEquipped()
	{
		return true;
	}
	//#################################################################################################################################
	static bool PlayerIsWeaponEquipped()
	{
		return true;
	}

	//#################################################################################################################################
	static D3DVECTOR PlayerGetPixelPosition()
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance)
		{
			D3DVECTOR d3Vector;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(instance, &d3Vector);

			return d3Vector;
		}
		else
		{
			return D3DVECTOR{ 0, 0, 0 };
		}
	}
	//#################################################################################################################################
	static void MountHorse()
	{
		if (Globals::Server == ServerName::METINPL)
		{
			GameFunctions::NetworkStreamSendCommandPacket(25, 0, "");
		}
		else
		{
			GameFunctions::NetworkStreamSendChatPacket("/ride", CHAT_TYPE_TALKING);
		}
	}
	//#################################################################################################################################
	static void UnMountHorse()
	{
		if (Globals::Server == ServerName::METINPL)
		{
			GameFunctions::NetworkStreamSendCommandPacket(43, 0, "");
		}
		else
		{
			GameFunctions::NetworkStreamSendChatPacket("/unmount", CHAT_TYPE_TALKING);
		}
	}
	//#################################################################################################################################
	static void UseAllItemVnumInInventory(int vnum)
	{
		for (int i = 0; i < (45 * 5); i++)
		{
			if (vnum == GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i)))
			{
				GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, i));
			}
		}
	}
	//#################################################################################################################################
	static DWORD GetCloseObject(int objectType, DWORD dis = 20000UL)
	{
		map<DWORD, DWORD*> closestNPC = GameFunctionsCustom::GetObjectList(objectType, dis);
		if (closestNPC.size() == 0)
		{
			return 0;
		}
		DWORD distance = 1000 * 1000;
		DWORD lastVid = 0;
		for (map<DWORD, DWORD*>::iterator itor = closestNPC.begin(); itor != closestNPC.end(); itor++)
		{
			DWORD objDistance = GameFunctionsCustom::PlayerGetCharacterDistance(itor->first);
			if (objDistance < distance)
			{
				distance = objDistance;
				lastVid = itor->first;
			}
		}
		return lastVid;
	}
	//#################################################################################################################################
	static DWORD GetCloseObjectByVnum(int vnum)
	{
		map<DWORD, DWORD*> closestObjects = GameFunctionsCustom::GetObjectList(OBJECT_NPC | OBJECT_MOB | OBJECT_MINE | OBJECT_STONE | OBJECT_BOSS);
		if (closestObjects.size() == 0)
		{
			return 0;
		}
		DWORD distance = 1000 * 1000;
		DWORD lastVid = 0;
		for (map<DWORD, DWORD*>::iterator itor = closestObjects.begin(); itor != closestObjects.end(); itor++)
		{
			DWORD mob_vnum = GameFunctions::InstanceBaseGetVirtualNumber(itor->second);
			if (mob_vnum != vnum) {
				continue;
			}
			DWORD objDistance = GameFunctionsCustom::PlayerGetCharacterDistance(itor->first);
			if (objDistance < distance)
			{
				distance = objDistance;
				lastVid = itor->first;
			}
		}
		return lastVid;
	}
	//#################################################################################################################################
	/*static DWORD GetCloseObjectByName(int objectType)
	{
		map<DWORD, DWORD*> closestNPC = GameFunctionsCustom::GetObjectList(objectType);
		if (closestNPC.size() == 0)
		{
			return 0;
	}
		map<DWORD, float> sortList;
		map<DWORD, DWORD*>::iterator itor;
		DWORD distance = 1000 * 1000;
		DWORD lastVid = 0;
		for (map<DWORD, DWORD*>::iterator itor = closestNPC.begin(); itor != closestNPC.end(); itor++)
		{
			DWORD mineDistance = GameFunctionsCustom::PlayerGetCharacterDistance(itor->first);
			if (mineDistance < distance)
			{
				distance = mineDistance;
				lastVid = itor->first;
			}


		}

		return lastVid;
	}*/
	//#################################################################################################################################
	static void UseAllFishVnumInInventoryTillSize(int vnum)
	{
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			if (vnum == GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i)))
			{

				if (((double)(GameFunctions::PlayerGetItemMetinSocket(i, 0) / 100)) < Settings::FISH_KILL_TILL_SIZE_VALUE)
				{
					GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, i));
				}

			}
		}
	}
	// #################################################################################################################################
	static vector<DWORD> FindItemSlotsInInventory(int vnum)
	{
		vector<DWORD> slots;
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (vnum == currentVnum)
			{
				slots.push_back(i);
			}

		}
		return slots;
	}
	//#################################################################################################################################
	static vector<DWORD> FindItemSlotsInInventory(DWORD vnumFrom, DWORD vnumTo)
	{
		vector<DWORD> slots;
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			int currentVnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (currentVnum > vnumFrom - 1 && currentVnum < vnumTo + 1)
			{
				slots.push_back(i);
			}

		}
		return slots;
	}
	//#################################################################################################################################
	static int FindItemSlotInInventory(int vnum)
	{
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			int current_vnum = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (vnum == current_vnum)
			{
				return i;
			}

		}
		return -1;
	}
	//#################################################################################################################################
	//NEED TO FIX ITEM SIZE MORE THEN 1 SLOT GIVE 0
	static bool IsFullInventory()
	{
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			DWORD itemIndex = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (!itemIndex)
			{

				return false;
			}
			else
			{

			}
		}
		return true;
	}
	//#################################################################################################################################

	static DWORD InventoryEquippedPercentage()
	{
		DWORD emptySlots = 0;
		for (int i = 0; i < (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT); i++)
		{
			DWORD itemIndex = GameFunctions::PlayerGetItemIndex(TItemPos(INVENTORY, i));
			if (!itemIndex)
			{
				emptySlots++;

			}
			else
			{

			}
		}
		return ((((Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT) - emptySlots) * 100) / (Settings::INVENTORY_PAGE_SIZE * Settings::INVENTORY_PAGE_COUNT));
	}
	//#################################################################################################################################
	static float PlayerGetCharacterDistance(int vid)
	{
		DWORD* pMainInstance = GameFunctions::PlayerNEW_GetMainActorPtr();
		DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (pMainInstance != NULL && pTargetInstance != NULL)
		{
			return GameFunctionsCustom::InstanceBaseGetDistance(pMainInstance, pTargetInstance);
		}
		else
		{
			return -1;
		}

	}
	//#################################################################################################################################
	static const char* InstanceGetNameByVID(int vid)
	{
		DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (pTargetInstance != NULL)
		{
			return GameFunctions::InstanceBaseGetNameString(pTargetInstance);
		}
		else
		{
			return NULL;
		}
	}
	static string  InstanceGetNameStringByVID(int vid)
	{
		DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (pTargetInstance != NULL)
		{
			return string(GameFunctions::InstanceBaseGetNameString(pTargetInstance));
		}
		else
		{
			return "";
		}
	}
	//#################################################################################################################################
	static bool PlayerMoveToDestPixelPositionDirection(D3DVECTOR d3dVector)
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (instance != NULL)
		{
			return GameFunctions::InstanceBaseNEW_MoveToDestPixelPositionDirection(instance, d3dVector);
		}
		else
		{
			return NULL;
		}
	}
	//#################################################################################################################################
	static bool PlayerIsMoreLessPosition(D3DVECTOR d3dVectorTarget)
	{
		return PlayerGetDistance(d3dVectorTarget) < 400;
	}
	//#################################################################################################################################
	static bool PlayerIsMoreLessPosition(DWORD vid)
	{
		D3DVECTOR d3VectorTarget;
		DWORD* target = GameFunctions::CharacterManagerGetInstancePtr(vid);
		if (target == NULL)
		{
			return false;
		}
		GameFunctions::InstanceBaseNEW_GetPixelPosition(target, &d3VectorTarget);
		return PlayerGetDistance(d3VectorTarget) < 400;
	}
	//#################################################################################################################################
	static int GetCharacterVidByName(const char* name)
	{
		map<DWORD, DWORD*> objectList = GetObjectList(OBJECT_PC);
		for (map<DWORD, DWORD*>::iterator itor = objectList.begin(); itor != objectList.end(); itor++)
		{

			DWORD* instance = itor->second;

			if (StringExtension::Equals(name, GameFunctions::InstanceBaseGetNameString(instance)))
			{
				return itor->first;
			}

		}
		return 0;
	}
	//#################################################################################################################################
	static int GetNPCVidByName(const char* name)
	{
		map<DWORD, DWORD*> playersList = GetObjectList(OBJECT_NPC);
		for (map<DWORD, DWORD*>::iterator itor = playersList.begin(); itor != playersList.end(); itor++)
		{

			DWORD* instance = itor->second;

			if (StringExtension::Equals(name, GameFunctions::InstanceBaseGetNameString(instance)))
			{
				return itor->first;
			}

		}
		return 0;
	}
	//#################################################################################################################################
	static DWORD* GetCharacterInstanceByName(const char* name)
	{
		map<DWORD, DWORD*> playersList = GetObjectList(OBJECT_PC);
		for (map<DWORD, DWORD*>::iterator itor = playersList.begin(); itor != playersList.end(); itor++)
		{

			DWORD* instance = itor->second;

			if (StringExtension::Equals(name, GameFunctions::InstanceBaseGetNameString(instance)))
			{
				return instance;
			}

		}
		return NULL;
	}

	//#################################################################################################################################
	static DWORD GetCharacterVIDByName(const char* name)
	{
		map<DWORD, DWORD*> playersList = GetObjectList(OBJECT_PC);
		for (map<DWORD, DWORD*>::iterator itor = playersList.begin(); itor != playersList.end(); itor++)
		{

			DWORD* instance = itor->second;

			if (StringExtension::Equals(name, GameFunctions::InstanceBaseGetNameString(instance)))
			{
				return itor->first;
			}

		}
		return 0;
	}
	//#################################################################################################################################
	static int GetObjectListCount(int objectType, DWORD distance = 20000)
	{
		return GetObjectList(objectType, distance).size();
	}


	//#################################################################################################################################
	static map<DWORD, DWORD*> GetObjectList(int objectType, DWORD distance = 20000)
	{
		map<DWORD, DWORD*> objectList;
		if (Globals::Server == ServerName::METINPL)
		{
			TCharacterInstanceMapGlobal m_kAliveInstMap = *(TCharacterInstanceMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonCharacterManagerInstance + 56) + 4));
			for (auto itor = m_kAliveInstMap.begin(); itor != m_kAliveInstMap.end(); itor++)
			{
				DWORD iIndex = itor->first;
				DWORD* instance = itor->second;
				if (instance == NULL || instance == GameFunctions::PlayerNEW_GetMainActorPtr() || GameFunctions::InstanceBaseIsDead(instance))
				{
					continue;
				}
				DWORD instanceDistance = GameFunctionsCustom::InstanceBaseGetDistance(GameFunctions::PlayerNEW_GetMainActorPtr(), instance);
				if (instanceDistance > distance)
				{
					continue;
				}
				int instanceType = GameFunctions::InstanceBaseGetInstanceType(instance);

				if (objectType & OBJECT_ALL)
				{
					objectList.insert(std::make_pair(iIndex, instance));
				}
				if (objectType & OBJECT_MOB)
				{
					if (instanceType == TYPE_ENEMY && !GameFunctionsCustom::InstanceIsBoss(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_STONE)
				{
					if (instanceType == TYPE_STONE)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_BOSS)
				{
					if (instanceType == TYPE_ENEMY && GameFunctionsCustom::InstanceIsBoss(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_PC)
				{
					if (instanceType == TYPE_PC)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_MINE)
				{
					if (instanceType == TYPE_NPC && GameFunctionsCustom::InstanceIsResource(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_NPC)
				{
					if (instanceType == TYPE_NPC)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
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
				DWORD iIndex = itor->first;
				DWORD* instance = itor->second;
				if (instance == NULL || instance == GameFunctions::PlayerNEW_GetMainActorPtr() || GameFunctions::InstanceBaseIsDead(instance))
				{
					continue;
				}
				DWORD instanceDistance = GameFunctionsCustom::InstanceBaseGetDistance(GameFunctions::PlayerNEW_GetMainActorPtr(), instance);
				if (instanceDistance > distance)
				{
					continue;
				}
				int instanceType = GameFunctions::InstanceBaseGetInstanceType(instance);

				if (objectType & OBJECT_ALL)
				{
					objectList.insert(std::make_pair(iIndex, instance));
				}
				if (objectType & OBJECT_MOB)
				{
					if (instanceType == TYPE_ENEMY && !GameFunctionsCustom::InstanceIsBoss(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_STONE)
				{
					if (instanceType == TYPE_STONE)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_BOSS)
				{
					if (instanceType == TYPE_ENEMY && GameFunctionsCustom::InstanceIsBoss(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_PC)
				{
					if (instanceType == TYPE_PC)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_MINE)
				{
					if (instanceType == TYPE_NPC && GameFunctionsCustom::InstanceIsResource(instance))
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
				if (objectType & OBJECT_NPC)
				{
					if (instanceType == TYPE_NPC)
					{
						objectList.insert(std::make_pair(iIndex, instance));
					}
				}
			}
		}
		return objectList;
	}
	//#################################################################################################################################
	static bool DetectPlayer(vector<string> whiteListNames)
	{
		if (Globals::Server == ServerName::VALIUM)
		{
			return false;
		}

		string widnowTitle = "";
		int counter = 0;
		map<DWORD, DWORD*> playersList = GameFunctionsCustom::GetObjectList(OBJECT_PC);
		for (map<DWORD, DWORD*>::iterator itor = playersList.begin(); itor != playersList.end(); itor++)
		{
			string playerName(GameFunctions::InstanceBaseGetNameString(itor->second));
			if (std::find(whiteListNames.begin(), whiteListNames.end(), playerName) != whiteListNames.end())
			{
				continue;
			}
			counter++;
			widnowTitle += " " + playerName;
		}
		SetWindowTextA(Globals::mainHwnd, widnowTitle.c_str());
		return counter > 0 ? true : false;
	}

	//#################################################################################################################################
	static map<DWORD, TGroundItemInstance*> GetGroundItemList()
	{
		map<DWORD, TGroundItemInstance*> vidList;
		if (Globals::Server == ServerName::METINPL)
		{
			string player_name = GameFunctions::InstanceBaseGetNameString(GameFunctions::PlayerNEW_GetMainActorPtr());
			TGroundItemInstanceMapGlobal m_GroundItemInstanceMap = *(TGroundItemInstanceMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonItemInstance + 28) + 4));
			for (TGroundItemInstanceMapGlobal::iterator itor = m_GroundItemInstanceMap.begin(); itor != m_GroundItemInstanceMap.end(); itor++)
			{
				string ownerShip = GetStr((DWORD)itor->second->stOwnership);
				if (ownerShip == "" || ownerShip == player_name)
				{
					vidList.insert(std::make_pair(itor->first, (TGroundItemInstance*)itor->second));
				}
			}
		}
		else
		{
			string player_name = GameFunctions::InstanceBaseGetNameString(GameFunctions::PlayerNEW_GetMainActorPtr());
			TGroundItemInstanceMap m_GroundItemInstanceMap = *(TGroundItemInstanceMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonItemInstance + 4) + 4));
			for (TGroundItemInstanceMap::iterator itor = m_GroundItemInstanceMap.begin(); itor != m_GroundItemInstanceMap.end(); itor++)
			{
				string ownerShip = "";
				try
				{
					ownerShip = itor->second->stOwnership;
				}
				catch (...)
				{

				}
				if (ownerShip == "" || ownerShip == player_name)
				{
					vidList.insert(std::make_pair(itor->first, itor->second));
				}
			}
		}
		return vidList;
	}

	static bool IsGroundItemsCanPickup()
	{
		if (Globals::Server == ServerName::METINPL)
		{
			string player_name = GameFunctions::InstanceBaseGetNameString(GameFunctions::PlayerNEW_GetMainActorPtr());
			TGroundItemInstanceMapGlobal m_GroundItemInstanceMap = *(TGroundItemInstanceMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonItemInstance + 28) + 4));
			for (TGroundItemInstanceMapGlobal::iterator itor = m_GroundItemInstanceMap.begin(); itor != m_GroundItemInstanceMap.end(); itor++)
			{
				string ownerShip = GetStr((DWORD)itor->second->stOwnership);
				if (ownerShip == "" || ownerShip == player_name)
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			string player_name = GameFunctions::InstanceBaseGetNameString(GameFunctions::PlayerNEW_GetMainActorPtr());
			TGroundItemInstanceMap m_GroundItemInstanceMap = *(TGroundItemInstanceMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCPythonItemInstance + 4) + 4));
			for (TGroundItemInstanceMap::iterator itor = m_GroundItemInstanceMap.begin(); itor != m_GroundItemInstanceMap.end(); itor++)
			{
				string ownerShip = itor->second->stOwnership;
				if (ownerShip == "" || ownerShip == player_name)
				{
					return true;
				}
			}
			return false;
		}
	}
	//#################################################################################################################################
	static map<DWORD, TCItemData*> GetItemProtoList()
	{
		map<DWORD, TCItemData*> itemsList;
		if (Globals::Server == ServerName::METINPL)
		{
			TItemMapGlobal m_ItemMap = *(TItemMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCItemManagerInstance + 28) + 4));
			for (TItemMapGlobal::iterator itor = m_ItemMap.begin(); itor != m_ItemMap.end(); itor++)
			{
				TCItemData inst{ itor->second->m_ItemTable };
				itemsList.insert(std::make_pair(itor->first, &inst));
			}
		}
		else
		{
			TItemMap m_ItemMap = *(TItemMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCItemManagerInstance + 4) + 4));
			for (TItemMap::iterator itor = m_ItemMap.begin(); itor != m_ItemMap.end(); itor++)
			{
				itemsList.insert(std::make_pair(itor->first, itor->second));
			}
		}
		return itemsList;
	}
	//#################################################################################################################################
	static map<DWORD, const char*> GetItemProtoNames()
	{
		map<DWORD, const char*> itemsList;
		if (Globals::Server == ServerName::METINPL)
		{
			TItemMapGlobal m_ItemMap = *(TItemMapGlobal*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCItemManagerInstance + 28) + 4));
			for (TItemMapGlobal::iterator itor = m_ItemMap.begin(); itor != m_ItemMap.end(); itor++)
			{
				//itemsList.insert(std::make_pair(itor->first, (const char*)itor->second + 297));
				itemsList.insert(std::make_pair(itor->first, GameFunctions::ItemDataGetName(itor->first)));
			}
			return itemsList;
		}
		else
		{
			TItemMap m_ItemMap;
			switch (Globals::Server)
			{
				default:
				{
					m_ItemMap = *(TItemMap*)(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(Globals::iCItemManagerInstance + 4) + 4));
					break;
				}
			}
			for (TItemMap::iterator itor = m_ItemMap.begin(); itor != m_ItemMap.end(); itor++)
			{
				switch (Globals::Server)
				{
					case ServerName::AELDRA:
					{
						itemsList.insert(std::make_pair(itor->first, GameFunctions::ItemDataGetName(itor->first)));
						break;
					}
					default:
					{
						itemsList.insert(std::make_pair(itor->first, GameFunctions::ItemDataGetName(itor->first)));
						break;
					}
				}
			}
			return itemsList;
		}
	}
	//#################################################################################################################################
	static float InstanceBaseGetDistance(DWORD* instance, DWORD* pkTargetInst)
	{
		D3DVECTOR d3VectorInstance;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(instance, &d3VectorInstance);
		D3DVECTOR d3VectorTargetInst;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(pkTargetInst, &d3VectorTargetInst);
		return MiscExtension::CountDistanceTwoPoints(d3VectorInstance.x, d3VectorInstance.y, d3VectorTargetInst.x, d3VectorTargetInst.y);
	}
	//#################################################################################################################################
	static float PlayerGetDistance(D3DVECTOR d3VectorTargetInst)
	{
		DWORD* instance = GameFunctions::PlayerNEW_GetMainActorPtr();
		D3DVECTOR d3VectorInstance;
		if (instance == NULL)
		{
			return 0;
		}
		GameFunctions::InstanceBaseNEW_GetPixelPosition(instance, &d3VectorInstance);
		return MiscExtension::CountDistanceTwoPoints(d3VectorInstance.x, d3VectorInstance.y, d3VectorTargetInst.x, d3VectorTargetInst.y);
	}

	//#################################################################################################################################
	static void PlayerShowTargetArrow(DWORD vidTarget, DWORD targetType)
	{
		DWORD* ptr = GameFunctions::PlayerNEW_GetMainActorPtr();
		DWORD* ptrTar = GameFunctions::CharacterManagerGetInstancePtr(vidTarget);
		D3DVECTOR main;
		D3DVECTOR tar;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(ptr, &main);
		GameFunctions::InstanceBaseNEW_GetPixelPosition(ptrTar, &tar);
		DWORD angle = (int)MiscExtension::AngleBetweenTwoPoints(main.x, main.y, tar.x, tar.y);
		angle += 90;
		string u;
		if (Globals::Server == ServerName::METINPL)
		{
			u = "DetectObject " + to_string(GameFunctions::PlayerGetMainCharacterIndex()) + " " + to_string(targetType) + " " + to_string(angle);
		}
		else
		{
			u = "StoneDetect " + to_string(GameFunctions::PlayerGetMainCharacterIndex()) + " " + to_string(targetType) + " " + to_string(angle);
		}
		GameFunctions::NetworkStreamServerCommand(u.c_str());
	}
	//#################################################################################################################################
	static void Boost()
	{
		static int BoostCount = 0;
		DWORD* pCharInstance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (pCharInstance != 0)
		{
			if (GameFunctions::InstanceIsWaiting(pCharInstance))
			{
				return;
			}
				
			D3DVECTOR Position;
			D3DVECTOR newPosition;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(pCharInstance, &Position);
			float rotation = 0;
			rotation = GameFunctionsCustom::PlayerGetRotation();

			int xx = Settings::MAIN_BOOST_SPEED * sin(rotation * 0.017453);
			int yy = Settings::MAIN_BOOST_SPEED * cos(rotation * 0.017453);
			int x = Position.x;
			int y = Position.y;
			newPosition.x = x + xx;
			newPosition.y = y - yy;

			GameFunctions::InstanceBaseSCRIPT_SetPixelPosition(pCharInstance, newPosition.x, newPosition.y);
			if (BoostCount >= 1)
			{
				BoostCount = 0;
				GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, rotation, 1, 0);
			}
			else
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, rotation, 0, 0);
				BoostCount++;
			}
		}
	}
	//#################################################################################################################################
	static bool InstanceIsResource(DWORD* instance)
	{
		DWORD mob_vnum = GameFunctions::InstanceBaseGetVirtualNumber(instance);
		switch (mob_vnum)
		{
		case 20047:
		case 20048:
		case 20049:
		case 20050:
		case 20051:
		case 20052:
		case 20053:
		case 20054:
		case 20055:
		case 20056:
		case 20057:
		case 20058:
		case 20059:
		case 30301:
		case 30302:
		case 30303:
		case 30304:
		case 30305:
		case 30306:
			return true;
		}

		return false;
	}
	//#################################################################################################################################
	static bool InstanceIsResource(DWORD tartgetVID)
	{
		DWORD mob_vnum = GameFunctions::InstanceBaseGetVirtualNumber(GameFunctions::CharacterManagerGetInstancePtr(tartgetVID));
		switch (mob_vnum)
		{
		case 20047:
		case 20048:
		case 20049:
		case 20050:
		case 20051:
		case 20052:
		case 20053:
		case 20054:
		case 20055:
		case 20056:
		case 20057:
		case 20058:
		case 20059:
		case 30301:
		case 30302:
		case 30303:
		case 30304:
		case 30305:
		case 30306:
			return true;
		}

		return false;
	}

	static int GetObjectRank(DWORD mob_vnum)
	{
		BYTE bRank = 0;
		switch (Globals::Server)
		{
		case ServerName::SAMIAS2:
		{
			DWORD* mob_info = (DWORD*)GameFunctions::NonPlayerGetTable(mob_vnum);
			if (mob_info != NULL)
			{
				BYTE* rankPtr = reinterpret_cast<BYTE*>(mob_info);
				rankPtr += 128;
				bRank = *(BYTE*)rankPtr;
			}
			break;
		}
		case ServerName::KEVRA:
		{
			DWORD* mob_info = (DWORD*)GameFunctions::NonPlayerGetTable(mob_vnum);
			if (mob_info != NULL)
			{
				BYTE* rankPtr = reinterpret_cast<BYTE*>(mob_info);
				rankPtr += 0x7F;
				bRank = *(BYTE*)rankPtr;
			}
			break;
		}
		case ServerName::CALLIOPE2:
		{
			DWORD* mob_info = (DWORD*)GameFunctions::NonPlayerGetTable(mob_vnum);
			if (mob_info != NULL)
			{
				BYTE* rankPtr = reinterpret_cast<BYTE*>(mob_info);
				rankPtr += 55;
				bRank = *(BYTE*)rankPtr;
			}
			break;
		}
		default:
		{
			TMobTable* mob_info = GameFunctions::NonPlayerGetTable(mob_vnum);
			if (mob_info != NULL)
			{
				bRank = mob_info->bRank;
			}
			break;
		}
		}
		return bRank;
	}
	//#################################################################################################################################
	static bool InstanceIsBoss(DWORD* instance)
	{
		DWORD mob_vnum = GameFunctions::InstanceBaseGetVirtualNumber(instance);
		BYTE bRank = GetObjectRank(mob_vnum);
		if (bRank >= 4 && bRank < 10)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//#################################################################################################################################
	static void SendPacket(string packet)
	{
		std::vector<char>  bytes = StringExtension::HexToBytes(packet);
		const char* data = reinterpret_cast<const char*>(bytes.data());
		GameFunctions::NetworkStreamSend(bytes.size(), (void*)data);
		GameFunctions::NetworkStreamSendSequence();
	}
	//#################################################################################################################################
	static D3DVECTOR GetTempPosition(D3DVECTOR DestPos, int& count)
	{
		D3DVECTOR PlayerPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &PlayerPos);
		int distance_x = abs(DestPos.x - PlayerPos.x);
		int distance_y = abs(DestPos.y - PlayerPos.y);
		int squared = sqrt((distance_x * distance_x) + (distance_y * distance_y));
		if (squared < 180)
		{
			count = 1;
		}

		else
		{
			count = squared / 180;
		}

		return D3DVECTOR{ PlayerPos.x + (DestPos.x - PlayerPos.x) / count, PlayerPos.y + (DestPos.y - PlayerPos.y) / count };
	}

	static DirectTexture GetD3DTexture(const char* name)
	{
		if (name != NULL) {
			DWORD* resourcePointer = GameFunctions::ResourceManagerGetResourcePointer(name);
			if (resourcePointer != NULL)
			{
				DWORD* texturePointer = GameFunctions::GraphicImageGetTexturePointer(resourcePointer);
				if (texturePointer != NULL)
				{
					DirectTexture d3dPointer = GameFunctions::GraphicTextureGetD3DTexture(texturePointer);
					if (d3dPointer != NULL)
					{
						return d3dPointer;
					}
					else
					{
						GameFunctions::ResourceReload(resourcePointer);
						DirectTexture d3dPointer = GameFunctions::GraphicTextureGetD3DTexture(texturePointer);
						if (d3dPointer != NULL)
						{
							return d3dPointer;
						}
					}
				}
				return NULL;
			}
			return NULL;
		}
		else
		{
			return NULL;
		}
	}

	//#################################################################################################################################
	static float PlayerGetRotation()
	{
		float frotation = 180.0f - GameFunctions::InstanceBaseGetRotation(GameFunctions::PlayerNEW_GetMainActorPtr());

		return frotation;
	}
	//#################################################################################################################################
	static void Teleport(D3DVECTOR TempPos) 
	{
		static int BoostCount = 0;
		DWORD* pCharInstance = GameFunctions::PlayerNEW_GetMainActorPtr();
		if (pCharInstance && TempPos.x > 0 && TempPos.y > 0) 
		{
			GameFunctions::InstanceBaseSCRIPT_SetPixelPosition(pCharInstance, TempPos.x, TempPos.y);
			if (BoostCount >= 1)
			{
				BoostCount = 0;
				GameFunctions::NetworkStreamSendCharacterStatePacket(TempPos, GameFunctionsCustom::PlayerGetRotation(), 1, 0);
			}
			else 
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(TempPos, GameFunctionsCustom::PlayerGetRotation(), 0, 0);
				BoostCount++;
			}
		}
	}
	//###############################################################################################################################
	static void UseSkillSlot(int skillIndex)
	{
		bool playerUsingHorse = GameFunctionsCustom::PlayerIsMountingHorse();
		if (playerUsingHorse)
		{
			DelayActions::Append(0, &GameFunctionsCustom::UnMountHorse);
			DelayActions::Append(500, &GameFunctions::PlayerClickSkillSlot, skillIndex);
		}
		else
		{
			DelayActions::Append(0, &GameFunctions::PlayerClickSkillSlot, skillIndex);
		}
		if (playerUsingHorse)
		{
			DelayActions::Append(1500, &GameFunctionsCustom::MountHorse);
		}
	}
	//###############################################################################################################################
	static bool PlayerDirectEnter()
	{
		if (!GameFunctions::NetworkStreamIsOnline())
		{

			int lastSlot = GameFunctionsCustom::GetCharSlotByName(GameFunctions::PlayerGetName());
			if (lastSlot != -1)
			{
				GameFunctions::NetworkStreamConnectGameServer(lastSlot);
			}


			
			return true;
		}
		return false;
	}
	//#################################################################################################################################
	static float GetDegreeFromDirection(int dir)
	{
		if (dir < 0)
			return 0.0f;

		if (dir >= 8)
			return 0.0f;

		static float s_dirRot[8] =
		{
			+45.0f * 4,
			+45.0f * 3,
			+45.0f * 2,
			+45.0f,
			+0.0f,
			360.0f - 45.0f,
			360.0f - 45.0f * 2,
			360.0f - 45.0f * 3,
		};

		return s_dirRot[dir];
	}
	//#################################################################################################################################
	static int GetDirectionFromDegree(int angle)
	{
		if (angle < 0)
			return 0;

		if (angle > 360)
			return 0;
		if (angle > 0 && angle <= 45)
		{
			return 6;
		}
		if (angle > 45 && angle <= 90)
		{
			return 7;
		}
		if (angle > 90 && angle <= 135)
		{
			return 0;
		}
		if (angle > 135 && angle <= 180)
		{
			return 1;
		}
		if (angle > 180 && angle <= 225)
		{
			return 2;
		}
		if (angle > 225 && angle <= 270)
		{
			return 3;
		}
		if (angle > 270 && angle <= 315)
		{
			return 4;
		}
		if (angle > 315 && angle <= 360)
		{
			return 5;
		}
		return 0;
	}
	//#################################################################################################################################
	static void LookAtDestPixelPosition(DWORD vidTarget)
	{
		DWORD* mainPtr = GameFunctions::PlayerNEW_GetMainActorPtr();
		DWORD* tarPtr = GameFunctions::CharacterManagerGetInstancePtr(vidTarget);
		D3DVECTOR main;
		D3DVECTOR tar;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(mainPtr, &main);
		GameFunctions::InstanceBaseNEW_GetPixelPosition(tarPtr, &tar);
		int angle = (int)MiscExtension::AngleBetweenTwoPoints(main.x, main.y, tar.x, tar.y);
		
		if (angle < 0)
		{
			angle = -angle;
			angle += 90;
		}
		else
		{
			
			if (angle >=  0 && angle <45)
			{
				angle = 80;
			}

			if (angle >= 45 && angle < 90)
			{
				angle = 60;
			}
			if (angle >= 90 && angle < 135)
			{
				angle = 20;
			}
			if (angle >= 135 && angle < 181)
			{
				angle = 330;
			}
		}
	
		GameFunctions::InstanceSetRotation(GameFunctions::PlayerNEW_GetMainActorPtr(), angle);
	}
	//#################################################################################################################################
	static void LookAtDestPixelPosition(D3DVECTOR tar)
	{
		DWORD* mainPtr = GameFunctions::PlayerNEW_GetMainActorPtr();
		
		D3DVECTOR main;
	
		GameFunctions::InstanceBaseNEW_GetPixelPosition(mainPtr, &main);
	
		int angle = (int)MiscExtension::AngleBetweenTwoPoints(main.x, main.y, tar.x, tar.y);
		if (angle < 0)
		{
			angle = -angle;
			angle += 90;
		}
		else
		{

			if (angle >= 0 && angle < 45)
			{
				angle = 80;
			}

			if (angle >= 45 && angle < 90)
			{
				angle = 60;
			}
			if (angle >= 90 && angle < 135)
			{
				angle = 20;
			}
			if (angle >= 135 && angle < 181)
			{
				angle = 330;
			}
		}
		
		
		GameFunctions::InstanceSetRotation(GameFunctions::PlayerNEW_GetMainActorPtr(), angle);
		
	}

	static bool NetworkStreamSendAttackPacket(UINT uMotAttack, DWORD dwVIDVictim)
	{
		if (Globals::Server == ServerName::AELDRA)
		{
			MemoryExtension::MemSet(Globals::pCPythonNetworkStreamSendOnClickPacket + 0x42, 0x50, 1);
			GameFunctions::NetworkStreamSendOnClickPacket(dwVIDVictim);
			MemoryExtension::MemSet(Globals::pCPythonNetworkStreamSendOnClickPacket + 0x42, 0x53, 1);
			return true;
		}
		if (Globals::Server == ServerName::WOM)
		{
			GameFunctions::NetworkStreamSendAttackPacket(uMotAttack, dwVIDVictim);
			return true;
		}
		else {
			TPacketCGAttack kPacketAtk;
			switch (Globals::Server)
			{
			case ServerName::SAMIAS2:
				kPacketAtk.header = 0x3A;
				break;
			case ServerName::METINPL:
				kPacketAtk.header = 0x52;
				break;
			case ServerName::CALLIOPE2:
				kPacketAtk.header = -112;
				break;
			case ServerName::TASTRIA2:
				kPacketAtk.header = 124;
				break;
			case ServerName::KEVRA:
				kPacketAtk.header = 0x3A;
				break;
			default:
				kPacketAtk.header = HEADER_CG_ATTACK;
				break;
			}
			kPacketAtk.bType = uMotAttack;
			kPacketAtk.dwVictimVID = dwVIDVictim;

			if (Globals::Server == ServerName::ORIGINS2 || Globals::Server == ServerName::CLASSIC )
			{
				if (!GameFunctions::NetworkStreamSendSpecial(sizeof(kPacketAtk), &kPacketAtk))
				{
					return false;
				}

				return true;
			}
			else 
			{
				if (!GameFunctions::NetworkStreamSendSpecial(sizeof(kPacketAtk), &kPacketAtk))
				{
					return false;
				}

				return GameFunctions::NetworkStreamSendSequence();
			}
		}
	}

	static string GetMapName()
	{
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		LONG GlobalX = CharPos.x;
		LONG GlobalY = CharPos.y;
		GameFunctions::BackgroundLocalPositionToGlobalPosition(GlobalX, GlobalY);
		switch (Globals::Server)
		{
		case ServerName::METINPL:
			return GetStr((DWORD)(TMapInfoGlobal*)GameFunctions::BackgroundGlobalPositionToMapInfo(GlobalX, GlobalY)->name);
			break;
		default:
			return GetStr((DWORD)GameFunctions::BackgroundGlobalPositionToMapInfo(GlobalX, GlobalY)->name);
			break;
		}
	}

	static void GlobalPositionToLocalPosition(LONG& rGlobalX, LONG& rGlobalY)
	{
		D3DVECTOR charpos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &charpos);
		LONG GlobalX = charpos.x;
		LONG GlobalY = charpos.y;
		GameFunctions::BackgroundLocalPositionToGlobalPosition(GlobalX, GlobalY);
		LONG BaseX = GlobalX - charpos.x;
		LONG BaseY = GlobalY - charpos.y;
		rGlobalX -= BaseX;
		rGlobalY -= BaseY;
	}
	//#################################################################################################################################
	static DWORD IsMapHaveInstance(DWORD* instanceContain)
	{
		map<DWORD, DWORD*> playersList = GetObjectList(OBJECT_ALL);
		for (map<DWORD, DWORD*>::iterator itor = playersList.begin(); itor != playersList.end(); itor++)
		{

			DWORD* instance = itor->second;

			if (instanceContain == instance)
			{
				return true;
			}

		}
		return false;
	}
};

