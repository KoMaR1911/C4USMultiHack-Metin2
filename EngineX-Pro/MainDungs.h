#pragma once
class MainDungs : public IAbstractModuleBase, public Singleton<MainDungs>
{
private:
	enum DungeonType
	{
		DT = 0,
		ATYVA_DT = 1,
		BARIA_175_0 = 2,
	};
public:
	int Phase = 0;

	int Floor2Step = 0;
	vector<D3DVECTOR> Floor2Positions;
	int Floor5Step = 0;
	vector<D3DVECTOR> Floor5Positions;

	void CheckRelogDT()
	{
		if (GameFunctionsCustom::GetMapName() != "metin2_map_deviltower1")
		{
			if (Phase != 0) {
				if (GameFunctionsCustom::PlayerIsInstance()) {
					DWORD DemonTowerGuard = 0;
					switch (Settings::DUNGEON_TYPE) {
					case DungeonType::DT:
						DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20348);
						if (!DemonTowerGuard)
						{
							return;
						}
						GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						break;
					case DungeonType::ATYVA_DT:
						DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20504);
						if (!DemonTowerGuard)
						{
							return;
						}
						GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						break;
					}
				}

			}
			return;
		}
	}

	void DemonTowerStart(int i)
	{
		if (Phase == 0) {
			if (GameFunctionsCustom::GetMapName() == "metin2_map_deviltower1") {
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
				Phase = 1;
			}
			else {
				DWORD DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20348);
				if (!DemonTowerGuard)
				{
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Brak NPC!");
					return;
				}
				GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(i);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				Phase = 1;
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
			}
		}
	}

	void AtyvaDemonTowerStart(int i)
	{
		if (Phase == 0) {
			if (GameFunctionsCustom::GetMapName() == "metin2_map_deviltower1") {
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
				Phase = 1;
			}
			else {
				DWORD DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20504);
				if (!DemonTowerGuard)
				{
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Brak NPC!");
					return;
				}
				GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(i);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
				Phase = 1;
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
			}
		}
	}

	void Dungeon175Start(int i)
	{
		if (Phase == 0) {
			if (GameFunctionsCustom::GetMapName() == "vulcan_cave") {
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
				Phase = 1;
			}
			else {
				DWORD DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20509);
				if (!DemonTowerGuard)
				{
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Brak NPC!");
					return;
				}
				GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(i);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				//Phase = 1;
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
			}
		}
	}

	void OnStart()
	{
		Floor2Positions = {
			D3DVECTOR{13629, 38768, 0}, D3DVECTOR{16983, 37937, 0}, D3DVECTOR{20189, 39168, 0},
			D3DVECTOR{21150, 42453, 0}, D3DVECTOR{20071, 45562, 0}, D3DVECTOR{17547, 46444, 0},
			D3DVECTOR{14887, 46372, 0}, D3DVECTOR{12801, 45006, 0}, D3DVECTOR{11794, 42202, 0},
			D3DVECTOR{12082, 39900, 0}, D3DVECTOR{13664, 38678, 0}
		};
		Floor5Positions = {
			D3DVECTOR{40550, 39705, 0}, D3DVECTOR{41592, 40065, 0}, D3DVECTOR{42419, 41539, 0},
			D3DVECTOR{42347, 43409, 0}, D3DVECTOR{40765, 44955, 0}, D3DVECTOR{38320, 44847, 0},
			D3DVECTOR{37062, 43013, 0}, D3DVECTOR{37278, 41144, 0}, D3DVECTOR{38680, 40317, 0},
			D3DVECTOR{40442, 39705, 0}
		};
		Settings::DUNGEON_BOT_ENABLE = true;
		Logger::Add(Logger::MAIN, true, Logger::WHITE, GameFunctionsCustom::GetMapName().c_str());
		switch (Settings::DUNGEON_TYPE) {
		case DungeonType::DT:
			DemonTowerStart(0);
			break;
		case DungeonType::ATYVA_DT:
			AtyvaDemonTowerStart(1);
			break;
		case DungeonType::BARIA_175_0:
			Dungeon175Start(0);
			break;
		}
	}

	void OnStop()
	{
		Settings::DUNGEON_BOT_ENABLE = false;
		Floor2Step = 0;
		Floor5Step = 0;

	}

	static void Exit175()
	{

	}

	static void Restart()
	{
		switch (Settings::DUNGEON_TYPE) {
		case DungeonType::DT:
			MainDungs::Instance().DemonTowerStart(1);
			break;
		case DungeonType::ATYVA_DT:
			MainDungs::Instance().DemonTowerStart(1);
			break;
		case DungeonType::BARIA_175_0:
			MainDungs::Instance().Dungeon175Start(0);
			Main::Instance().ResetSkillTimer();
			break;
		}
	}

	void Teleport(D3DVECTOR vec)
	{
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, vec);
		int i = 0;
		for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
		{
			bool InDistance = MathExtension::PointInCircle(CharPos, vec, 400);
			if (!InDistance)
			{
				DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
			}
			i++;
		}
	}

	void CheckCoords()
	{
		if (Phase == 0)
		{
			return;
		}
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		bool Floor1 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 16004, 65304, 0 }, 8000);
		if (Floor1 && Phase != 1)
		{
			Phase = 1;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 16004, 65304, 0 });
			return;
		}
		bool Floor2 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 16431, 41912, 0 }, 8000);
		if (Floor2 && Phase != 2)
		{
			Phase = 2;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 2!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 16431, 41912, 0 });
			return;
		}
		bool Floor3 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 17807, 18682, 0 }, 8000);
		if (Floor3 && Phase != 3)
		{
			Floor2Step = 0;
			Phase = 3;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 3!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 17807, 18682, 0 });
			return;
		}
		bool Floor4 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39402, 65544, 0 }, 6500);
		if (Floor4 && Phase != 4)
		{
			Phase = 4;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 4!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 39402, 65544, 0 });
			return;
		}
		bool Floor5 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39572, 42738, 0 }, 6500);
		if (Floor5 && Phase != 5)
		{
			Phase = 5;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 5!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 39572, 42738, 0 });
			return;
		}
		bool Floor6 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39855, 19264, 0 }, 8000);
		if (Floor6 && Phase != 6)
		{
			Floor5Step = 0;
			Phase = 6;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 6!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 39855, 19264, 0 });
			return;
		}
		bool Floor7 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 61675, 66273, 0 }, 6500);
		if (Floor7 && Phase != 7)
		{
			Phase = 7;
			Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 7!");
			DelayActions::Clear();

			Teleport(D3DVECTOR{ 61675, 66273, 0 });
			return;
		}
	}

	void Update175()
	{
		if (GameFunctionsCustom::GetMapName() != "vulcan_cave")
		{
			if (Phase != 0) {
				if (GameFunctionsCustom::PlayerIsInstance()) {
					DWORD DemonTowerGuard = 0;
					switch (Settings::DUNGEON_TYPE) {
					case DungeonType::BARIA_175_0:
						DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20509);
						if (!DemonTowerGuard)
						{
							return;
						}
						GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						break;
					}
				}
			}
			return;
		}
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		DWORD MetinZguby = GameFunctionsCustom::GetCloseObjectByVnum(8087);
		if (MetinZguby)
		{
			Phase = 1;

			D3DVECTOR MobPos;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(MetinZguby), &MobPos);
			if (!MathExtension::PointInCircle(CharPos, MobPos, 400))
			{
				Teleport(MobPos);
			}	
			return;
		}
		DWORD KrwistySmok = GameFunctionsCustom::GetCloseObjectByVnum(2496);
		if (KrwistySmok)
		{
			Phase = 2;

			D3DVECTOR MobPos;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(KrwistySmok), &MobPos);
			if (!MathExtension::PointInCircle(CharPos, MobPos, 400))
			{
				Teleport(MobPos);
			}
			return;
		}
		//Floors
		switch (Phase)
		{
			case 1: {
				break;
			}
			case 2: {
				DWORD KrwistySmok = GameFunctionsCustom::GetCloseObjectByVnum(2496);
				if (!KrwistySmok)
				{
					DWORD Pieczec = GameFunctionsCustom::GetCloseObjectByVnum(20081);
					if (Pieczec)
					{
						GameFunctions::NetworkStreamSendOnClickPacket(Pieczec);
						int GroundSize = GameFunctionsCustom::GetGroundItemList().size();
						if (GroundSize == 0)
						{
							GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
							DelayActions::AppendBlock(false, 5000, &Restart);
						}
					}
				}
				break;
			}
		}
	}

	void UpdateDT()
	{
		//Check relog
		CheckRelogDT();
		//Check Coords
		CheckCoords();
		//Floors
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		switch (Phase) 
		{
			case 1: {
				DWORD MetinTwardosci = GameFunctionsCustom::GetCloseObjectByVnum(8015);
				if (!MetinTwardosci)
				{
					return;
				}
				D3DVECTOR MetinPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(MetinTwardosci), &MetinPos);
				Teleport(MetinPos);
				break;
			}
			case 2: {
				bool InDistance = MathExtension::PointInCircle(CharPos, Floor2Positions[Floor2Step], 400);
				if (InDistance)
				{
					Floor2Step++;
				}
				if (Floor2Step == Floor2Positions.size())
				{
					reverse(Floor2Positions.begin(), Floor2Positions.end());
					Floor2Step = 0;
				}
				if (!InDistance)
				{
					Teleport(Floor2Positions[Floor2Step]);
				}
				break;
			}
			case 3: {
				DWORD KrolDemonow = GameFunctionsCustom::GetCloseObjectByVnum(1091);
				if (!KrolDemonow)
				{
					return;
				}
				D3DVECTOR MobPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(KrolDemonow), &MobPos);
				Teleport(MobPos);
				break;
			}
			case 4: {
				DWORD Metin = GameFunctionsCustom::GetCloseObject(OBJECT_STONE, 10000);
				if (!Metin)
				{
					return;
				}
				D3DVECTOR MetinPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(Metin), &MetinPos);
				Teleport(MetinPos);
				break;
			}
			case 5: {
				//Przeciaganie pieczeci
				int kamien_slot = GameFunctionsCustom::FindItemSlotInInventory(50084);
				if (kamien_slot != -1) {
					DWORD Pieczec = GameFunctionsCustom::GetCloseObjectByVnum(20073);
					if (Pieczec)
					{
						D3DVECTOR MetinPos;
						GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(Pieczec), &MetinPos);
						vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MetinPos);
						int i = 0;
						for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
						{
							bool InDistance = MathExtension::PointInCircle(CharPos, MetinPos, 400);
							if (!InDistance)
							{
								DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
							}
							else {
								GameFunctions::NetworkStreamSendGiveItemPacket(Pieczec, TItemPos{INVENTORY, (WORD)kamien_slot}, 1);
							}
							i++;
						}
					}
				}
				//Bicie
				bool InDistance = MathExtension::PointInCircle(CharPos, Floor5Positions[Floor5Step], 400);
				if (InDistance)
				{
					Floor5Step++;
				}
				if (Floor5Step == Floor5Positions.size())
				{
					reverse(Floor5Positions.begin(), Floor5Positions.end());
					Floor5Step = 0;
				}
				if (!InDistance)
				{
					Teleport(Floor5Positions[Floor5Step]);
				}
				break;
			}
			case 6: {
				DWORD ElitKrolDemonow = GameFunctionsCustom::GetCloseObjectByVnum(1092);
				if (ElitKrolDemonow)
				{
					D3DVECTOR MobPos;
					GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(ElitKrolDemonow), &MobPos);
					Teleport(MobPos);
					return;
				}
				else {
					vector<int> Kowale;
					Kowale.push_back(GameFunctionsCustom::GetCloseObjectByVnum(20074));
					Kowale.push_back(GameFunctionsCustom::GetCloseObjectByVnum(20075));
					Kowale.push_back(GameFunctionsCustom::GetCloseObjectByVnum(20076));
					auto Kowal = std::find_if(begin(Kowale), end(Kowale), [](int n) { return n != 0; });
					Kowale.erase(begin(Kowale), Kowal);
					if (*Kowal != 0) {
						GameFunctions::NetworkStreamSendOnClickPacket(*Kowal);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
						GameFunctions::NetworkStreamSendScriptAnswerPacket(1);
						Phase = 7;
						//int lastSlot = GameFunctionsCustom::GetCharSlotByName(GameFunctions::PlayerGetName());
						//if (lastSlot != -1)
						//{
						//	GameFunctions::NetworkStreamConnectGameServer(lastSlot);
						//	Main::Instance().ResetSkillTimer();
						//}
						//DelayActions::AppendBlock(false, 5000, &Restart);
					}
				}
				break;
			}
			case 7: {
				DWORD Metin = GameFunctionsCustom::GetCloseObject(OBJECT_STONE, 10000);
				if (!Metin)
				{
					return;
				}
				D3DVECTOR MetinPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(Metin), &MetinPos);
				Teleport(MetinPos);
				break;
			}
		}
	}

	void OnUpdate()
	{
		if (Settings::DUNGEON_BOT_ENABLE) 
		{
			if (GameFunctionsCustom::PlayerIsInstance()) {
				switch (Settings::DUNGEON_TYPE) {
				case DungeonType::DT:
					UpdateDT();
					break;
				case DungeonType::ATYVA_DT:
					UpdateDT();
					break;
				case DungeonType::BARIA_175_0:
					Update175();
					break;
				}
			}
		}
	}

	void OnRender()
	{
	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("DungBot", ImVec2(ImGui::GetWindowWidth() - 10, ImGui::GetWindowHeight() - 10), true);
		std::string PhaseText = "Phase:" + to_string(Phase);
		ImGui::Text(PhaseText.c_str());
		if (ImGui::Checkbox("On/Off", &Settings::DUNGEON_BOT_ENABLE)) {
			if (Settings::DUNGEON_BOT_ENABLE == true)
			{
				OnStart();
			}
			else
			{
				OnStop();
			}
		}
		ImGui::RadioButton("DT", &Settings::DUNGEON_TYPE, 0);
		ImGui::RadioButton("ATYVA DT", &Settings::DUNGEON_TYPE, 1);
		ImGui::RadioButton("BARIA 175", &Settings::DUNGEON_TYPE, 2);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(72, "Dungeons");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 72:
			OnTab1();
			break;
		}
	}
};