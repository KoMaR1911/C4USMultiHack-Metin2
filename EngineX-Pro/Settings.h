#pragma once

namespace ns {
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(D3DVECTOR, x, y, z)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImVec4, x, y, z, w)
}

class Settings
{
public:
	static void LoadItemFilter(string name, string folderPath)
	{
		string buffer = "";
		FileExtension::Read(folderPath + name + ".ic", buffer);
		if (buffer == "")
		{
			return;
		}
		nlohmann::json j = nlohmann::json::parse(buffer);
		if (j.find("ITEM_FILTER") != j.end())
		{
			j.at("ITEM_FILTER").get_to(ITEM_PICKUP_SELECTED_LIST);
		}
	}

	static void SaveItemFilter(string name, string folderPath)
	{
		nlohmann::json j = nlohmann::json
		{
			{"ITEM_FILTER", ITEM_PICKUP_SELECTED_LIST},
		};
		string dump = j.dump(4);
		if (FileExtension::CreateDirectoryPath(folderPath.c_str()))
		{
			string filePath = folderPath + name + ".ic";
			FileExtension::Write(filePath, dump);
		}
	}

	static void LoadFarm(string name, string folderPath)
	{
		string buffer = "";
		FileExtension::Read(folderPath + name + ".fc", buffer);
		if (buffer == "")
		{
			return;
		}
		nlohmann::json j = nlohmann::json::parse(buffer);
		std::vector<float> vec_x, vec_y, vec_z;
		if (j.find("FARMBOT_PATH.x") != j.end())
		{
			j.at("FARMBOT_PATH.x").get_to(vec_x);
		}
		if (j.find("FARMBOT_PATH.y") != j.end())
		{
			j.at("FARMBOT_PATH.y").get_to(vec_y);
		}
		if (j.find("FARMBOT_PATH.z") != j.end())
		{
			j.at("FARMBOT_PATH.z").get_to(vec_z);
		}
		cordsMaps.clear();
		for (int i = 0; i < vec_x.size(); i++)
		{
			D3DVECTOR position{ vec_x[i], vec_y[i], vec_z[i]};
			cordsMaps.push_back(position);
		}
	}

	static void SaveFarm(string name, string folderPath)
	{
		nlohmann::json j = nlohmann::json{};
		std::vector<float> vec_x, vec_y, vec_z;
		for (int i = 0; i < cordsMaps.size(); i++)
		{
			vec_x.push_back(cordsMaps[i].x);
			vec_y.push_back(cordsMaps[i].y);
			vec_z.push_back(cordsMaps[i].z);
		}
		j["FARMBOT_PATH.x"] = vec_x;
		j["FARMBOT_PATH.y"] = vec_y;
		j["FARMBOT_PATH.z"] = vec_z;
		string dump = j.dump(4);
		if (FileExtension::CreateDirectoryPath(folderPath.c_str()))
		{
			string filePath = folderPath + name + ".fc";
			FileExtension::Write(filePath, dump);
		}
	}


	static void LoadServerVariables()
	{
		switch (Globals::Server)
		{
			case ServerName::METINPL:
			{
				Settings::FISH_BAIT_LIST.insert(make_pair(make_pair(1, true), make_pair(27798, "Krewetki Słodkowodne")));
				Settings::FISH_KILL_FISH_LIST.insert(make_pair(make_pair(22, true), make_pair(27824, "Weżoglów")));
				Settings::FISH_KILL_FISH_LIST.insert(make_pair(make_pair(23, true), make_pair(27825, "Skaber")));
				Settings::FISH_KILL_FISH_LIST.insert(make_pair(make_pair(24, true), make_pair(27826, "Krab Królewski")));
				Settings::FISH_KILL_FISH_LIST.insert(make_pair(make_pair(25, true), make_pair(27827, "Rak Niebiański")));
				Settings::FISH_DROP_LIST.insert(make_pair(make_pair(42, true), make_pair(27854, "Martwy Weżoglów")));
				Settings::FISH_DROP_LIST.insert(make_pair(make_pair(43, true), make_pair(27855, "Martwy Skaber")));
				Settings::FISH_DROP_LIST.insert(make_pair(make_pair(44, true), make_pair(27856, "Martwy Krab Królewski")));
				Settings::FISH_DROP_LIST.insert(make_pair(make_pair(45, true), make_pair(27857, "Martwy Rak Niebiański")));
				Settings::INVENTORY_PAGE_COUNT = 2;
				break;
			}
			case ServerName::KEVRA:
			{
				Settings::FISH_BAIT_LIST.insert(make_pair(make_pair(1, true), make_pair(27900, "Skorupiak")));
				Settings::FISH_DROP_LIST = {};
				Settings::FISH_KILL_FISH_LIST = {};
				Settings::FISH_SELL_LIST =
				{
					{ make_pair(1, true), make_pair(27803, "Karaś")},
					{ make_pair(2, true), make_pair(27804, "Ryba Mandaryna")},
					{ make_pair(3, true), make_pair(27823, "Złoty Karaś")},
				};
				break;
			}
		}
	}

	static void Load(string name, string folderPath)
	{
		string buffer = "";
		FileExtension::Read(folderPath  + name + ".mc", buffer);
		
		if (buffer == "")
		{
			return;
		}
		nlohmann::json j = nlohmann::json::parse(buffer);
		/*j.parse(buffer);*/
		if (j.find("PROTECTION_DETECT_PLAYER_WHITE_LIST") != j.end())
		{
			j.at("PROTECTION_DETECT_PLAYER_WHITE_LIST").get_to(PROTECTION_DETECT_PLAYER_WHITE_LIST);
		}
		if (j.find("FISH_KILL_FISH_LIST") != j.end())
		{
			j.at("FISH_KILL_FISH_LIST").get_to(FISH_KILL_FISH_LIST);
		}
		if (j.find("FISH_BAIT_LIST") != j.end())
		{
			j.at("FISH_BAIT_LIST").get_to(FISH_BAIT_LIST);
		}
		if (j.find("FISH_DROP_LIST") != j.end())
		{
			j.at("FISH_DROP_LIST").get_to(FISH_DROP_LIST);
		}
		if (j.find("FISH_SELL_LIST") != j.end())
		{
			j.at("FISH_SELL_LIST").get_to(FISH_SELL_LIST);
		}
		if (j.find("ITEM_PICKUP_SELECTED_LIST") != j.end())
		{
			j.at("ITEM_PICKUP_SELECTED_LIST").get_to(ITEM_PICKUP_SELECTED_LIST);
		}
		if (j.find("MAIN_STONE_DETECT_ENABLE") != j.end())
		{
			j.at("MAIN_STONE_DETECT_ENABLE").get_to(MAIN_STONE_DETECT_ENABLE);
		}
		if (j.find("MAIN_MOBBER_ENABLE") != j.end())
		{
			j.at("MAIN_MOBBER_ENABLE").get_to(MAIN_MOBBER_ENABLE);
		}
		if (j.find("MAIN_ATTACK_ENABLE") != j.end())
		{
			j.at("MAIN_ATTACK_ENABLE").get_to(MAIN_ATTACK_ENABLE);
		}
		if (j.find("MAIN_ROTATION_ENABLE") != j.end())
		{
			j.at("MAIN_ROTATION_ENABLE").get_to(MAIN_ROTATION_ENABLE);
		}
		if (j.find("MAIN_ROTATION_SPEED_VALUE") != j.end())
		{
			j.at("MAIN_ROTATION_SPEED_VALUE").get_to(MAIN_ROTATION_SPEED_VALUE);
		}
		if (j.find("MAIN_SKILL_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_ENABLE").get_to(MAIN_SKILL_ENABLE);
		}
		if (j.find("MAIN_SKILL_1_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_1_ENABLE").get_to(MAIN_SKILL_1_ENABLE);
		}
		if (j.find("MAIN_SKILL_2_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_2_ENABLE").get_to(MAIN_SKILL_2_ENABLE);
		}
		if (j.find("MAIN_SKILL_3_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_3_ENABLE").get_to(MAIN_SKILL_3_ENABLE);
		}
		if (j.find("MAIN_SKILL_4_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_4_ENABLE").get_to(MAIN_SKILL_4_ENABLE);
		}
		if (j.find("MAIN_SKILL_5_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_5_ENABLE").get_to(MAIN_SKILL_5_ENABLE);
		}
		if (j.find("MAIN_SKILL_6_ENABLE") != j.end())
		{
			j.at("MAIN_SKILL_6_ENABLE").get_to(MAIN_SKILL_6_ENABLE);
		}
		if (j.find("MAIN_NOK_ENABLE") != j.end())
		{
			j.at("MAIN_NOK_ENABLE").get_to(MAIN_NOK_ENABLE);
		}
		if (j.find("MAIN_NOP_ENABLE") != j.end())
		{
			j.at("MAIN_NOP_ENABLE").get_to(MAIN_NOP_ENABLE);
		}
		if (j.find("MAIN_WALL_MOB_ENABLE") != j.end())
		{
			j.at("MAIN_WALL_MOB_ENABLE").get_to(MAIN_WALL_MOB_ENABLE);
		}
		if (j.find("MAIN_WALL_OBJECT_ENABLE") != j.end())
		{
			j.at("MAIN_WALL_OBJECT_ENABLE").get_to(MAIN_WALL_OBJECT_ENABLE);
		}
		if (j.find("MAIN_WALL_TERRAIN_ENABLE") != j.end())
		{
			j.at("MAIN_WALL_TERRAIN_ENABLE").get_to(MAIN_WALL_TERRAIN_ENABLE);
		}
		if (j.find("MAIN_WH_ENABLE") != j.end())
		{
			j.at("MAIN_WH_ENABLE").get_to(MAIN_WH_ENABLE);
		}
		if (j.find("MAIN_WH_DISTANCE_VALUE") != j.end())
		{
			j.at("MAIN_WH_DISTANCE_VALUE").get_to(MAIN_WH_DISTANCE_VALUE);
		}
		if (j.find("MAIN_WH_DISTANCE_STEP") != j.end())
		{
			j.at("MAIN_WH_DISTANCE_STEP").get_to(MAIN_WH_DISTANCE_STEP);
		}
		if (j.find("MAIN_WH_TYPE") != j.end())
		{
			j.at("MAIN_WH_TYPE").get_to(MAIN_WH_WEAPON_TYPE);
		}
		if (j.find("MAIN_WAITHACK_RANGE_ENABLE") != j.end())
		{
			j.at("MAIN_WAITHACK_RANGE_ENABLE").get_to(MAIN_WAITHACK_RANGE_ENABLE);
		}
		if (j.find("MAIN_WH_SKILL_COOLDOWN_TIME") != j.end())
		{
			j.at("MAIN_WH_SKILL_COOLDOWN_TIME").get_to(MAIN_WH_SKILL_COOLDOWN_TIME);
		}
		if (j.find("MAIN_WH_TIME") != j.end())
		{
			j.at("MAIN_WH_TIME").get_to(MAIN_WH_TIME);
		}
		if (j.find("MAIN_WH_ATTACK_TYPE") != j.end())
		{
			j.at("MAIN_WH_ATTACK_TYPE").get_to(MAIN_WH_ATTACK_TYPE);
		}
		if (j.find("MAIN_WH_RENDER_ENABLE") != j.end())
		{
			j.at("MAIN_WH_RENDER_ENABLE").get_to(MAIN_WH_RENDER_ENABLE);
		}
		if (j.find("MAIN_WH_SKILL_VALUE") != j.end())
		{
			j.at("MAIN_WH_SKILL_VALUE").get_to(MAIN_WH_SKILL_VALUE);
		}
		if (j.find("MAIN_WH_MONSTER") != j.end())
		{
			j.at("MAIN_WH_MONSTER").get_to(MAIN_WH_MONSTER);
		}
		if (j.find("MAIN_WH_METIN") != j.end())
		{
			j.at("MAIN_WH_METIN").get_to(MAIN_WH_METIN);
		}
		if (j.find("MAIN_WH_BOSS") != j.end())
		{
			j.at("MAIN_WH_BOSS").get_to(MAIN_WH_BOSS);
		}
		if (j.find("MAIN_WH_PLAYER") != j.end())
		{
			j.at("MAIN_WH_PLAYER").get_to(MAIN_WH_PLAYER);
		}
		if (j.find("MAIN_MOB_DETECT_ENABLE") != j.end())
		{
			j.at("MAIN_MOB_DETECT_ENABLE").get_to(MAIN_MOB_DETECT_ENABLE);
		}
		if (j.find("MAIN_POTION_ENABLE") != j.end())
		{
			j.at("MAIN_POTION_ENABLE").get_to(MAIN_POTION_ENABLE);
		}
		if (j.find("MAIN_RED_POTION_ENABLE") != j.end())
		{
			j.at("MAIN_RED_POTION_ENABLE").get_to(MAIN_RED_POTION_ENABLE);
		}
		if (j.find("MAIN_RED_POTION_PERCENTAGE_VALUE") != j.end())
		{
			j.at("MAIN_RED_POTION_PERCENTAGE_VALUE").get_to(MAIN_RED_POTION_PERCENTAGE_VALUE);
		}
		if (j.find("MAIN_RED_POTION_SPEED_VALUE") != j.end())
		{
			j.at("MAIN_RED_POTION_SPEED_VALUE").get_to(MAIN_RED_POTION_SPEED_VALUE);
		}
		if (j.find("MAIN_BLUE_POTION_ENABLE") != j.end())
		{
			j.at("MAIN_BLUE_POTION_ENABLE").get_to(MAIN_BLUE_POTION_ENABLE);
		}
		if (j.find("MAIN_BLUE_POTION_PERCENTAGE_VALUE") != j.end())
		{
			j.at("MAIN_BLUE_POTION_PERCENTAGE_VALUE").get_to(MAIN_BLUE_POTION_PERCENTAGE_VALUE);
		}
		if (j.find("MAIN_BLUE_POTION_SPEED_VALUE") != j.end())
		{
			j.at("MAIN_BLUE_POTION_SPEED_VALUE").get_to(MAIN_BLUE_POTION_SPEED_VALUE);
		}
		if (j.find("MAIN_AUTO_REVIVE_ENABLE") != j.end())
		{
			j.at("MAIN_AUTO_REVIVE_ENABLE").get_to(MAIN_AUTO_REVIVE_ENABLE);
		}
		if (j.find("MAIN_AUTO_REVIVE_PERCENTAGE_VALUE") != j.end())
		{
			j.at("MAIN_AUTO_REVIVE_PERCENTAGE_VALUE").get_to(MAIN_AUTO_REVIVE_PERCENTAGE_VALUE);
		}
		if (j.find("MAIN_CHANNEL_CHANGER_PORT_OFFSET") != j.end())
		{
			j.at("MAIN_CHANNEL_CHANGER_PORT_OFFSET").get_to(MAIN_CHANNEL_CHANGER_PORT_OFFSET);
		}
		if (j.find("MAIN_BOOST_KEY") != j.end())
		{
			j.at("MAIN_BOOST_KEY").get_to(MAIN_BOOST_KEY);
		}
		if (j.find("MAIN_RELOG_KEY") != j.end())
		{
			j.at("MAIN_RELOG_KEY").get_to(MAIN_RELOG_KEY);
		}
		if (j.find("MAIN_GLOBAL_SWITCH_KEY") != j.end())
		{
			j.at("MAIN_GLOBAL_SWITCH_KEY").get_to(MAIN_GLOBAL_SWITCH_KEY);
		}
		if (j.find("MAIN_HIDE_UI_KEY") != j.end())
		{
			j.at("MAIN_HIDE_UI_KEY").get_to(MAIN_HIDE_UI_KEY);
		}
		if (j.find("MAIN_BOOST_SPEED") != j.end())
		{
			j.at("MAIN_BOOST_SPEED").get_to(MAIN_BOOST_SPEED);
		}
		if (j.find("MAIN_WH_DETECT_PLAYER_ENABLE") != j.end())
		{
			j.at("MAIN_WH_DETECT_PLAYER_ENABLE").get_to(MAIN_WH_DETECT_PLAYER_ENABLE);
		}
		if (j.find("ITEM_SLOT_RANDOM_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_RANDOM_ENABLE").get_to(ITEM_SLOT_RANDOM_ENABLE);
		}
		if (j.find("ITEM_SLOT_3_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_3_ENABLE").get_to(ITEM_SLOT_3_ENABLE);
		}
		if (j.find("ITEM_SLOT_4_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_4_ENABLE").get_to(ITEM_SLOT_4_ENABLE);
		}
		if (j.find("ITEM_SLOT_5_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_5_ENABLE").get_to(ITEM_SLOT_5_ENABLE);
		}
		if (j.find("ITEM_SLOT_6_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_6_ENABLE").get_to(ITEM_SLOT_6_ENABLE);
		}
		if (j.find("ITEM_SLOT_7_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_7_ENABLE").get_to(ITEM_SLOT_7_ENABLE);
		}
		if (j.find("ITEM_SLOT_8_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_8_ENABLE").get_to(ITEM_SLOT_8_ENABLE);
		}
		if (j.find("ITEM_SLOT_9_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_9_ENABLE").get_to(ITEM_SLOT_9_ENABLE);
		}
		if (j.find("ITEM_SLOT_10_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_10_ENABLE").get_to(ITEM_SLOT_10_ENABLE);
		}
		if (j.find("ITEM_SLOT_11_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_11_ENABLE").get_to(ITEM_SLOT_11_ENABLE);
		}
		if (j.find("ITEM_SLOT_12_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_12_ENABLE").get_to(ITEM_SLOT_12_ENABLE);
		}
		if (j.find("ITEM_SLOT_13_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_13_ENABLE").get_to(ITEM_SLOT_13_ENABLE);
		}
		if (j.find("ITEM_SLOT_14_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_14_ENABLE").get_to(ITEM_SLOT_14_ENABLE);
		}
		if (j.find("ITEM_SLOT_15_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_15_ENABLE").get_to(ITEM_SLOT_15_ENABLE);
		}
		if (j.find("ITEM_SLOT_16_ENABLE") != j.end())
		{
			j.at("ITEM_SLOT_16_ENABLE").get_to(ITEM_SLOT_16_ENABLE);
		}
		if (j.find("ITEM_SLOT_RANDOM_MIN_TIME") != j.end())
		{
			j.at("ITEM_SLOT_RANDOM_MIN_TIME").get_to(ITEM_SLOT_RANDOM_MIN_TIME);
		}
		if (j.find("ITEM_SLOT_RANDOM_MAX_TIME") != j.end())
		{
			j.at("ITEM_SLOT_RANDOM_MAX_TIME").get_to(ITEM_SLOT_RANDOM_MAX_TIME);
		}
		if (j.find("ITEM_SLOT_3_TIME") != j.end())
		{
			j.at("ITEM_SLOT_3_TIME").get_to(ITEM_SLOT_3_TIME);
		}
		if (j.find("ITEM_SLOT_4_TIME") != j.end())
		{
			j.at("ITEM_SLOT_4_TIME").get_to(ITEM_SLOT_4_TIME);
		}
		if (j.find("ITEM_SLOT_5_TIME") != j.end())
		{
			j.at("ITEM_SLOT_5_TIME").get_to(ITEM_SLOT_5_TIME);
		}
		if (j.find("ITEM_SLOT_6_TIME") != j.end())
		{
			j.at("ITEM_SLOT_6_TIME").get_to(ITEM_SLOT_6_TIME);
		}
		if (j.find("ITEM_SLOT_7_TIME") != j.end())
		{
			j.at("ITEM_SLOT_7_TIME").get_to(ITEM_SLOT_7_TIME);
		}
		if (j.find("ITEM_SLOT_8_TIME") != j.end())
		{
			j.at("ITEM_SLOT_8_TIME").get_to(ITEM_SLOT_8_TIME);
		}
		if (j.find("ITEM_SLOT_9_TIME") != j.end())
		{
			j.at("ITEM_SLOT_9_TIME").get_to(ITEM_SLOT_9_TIME);
		}
		if (j.find("ITEM_SLOT_10_TIME") != j.end())
		{
			j.at("ITEM_SLOT_10_TIME").get_to(ITEM_SLOT_10_TIME);
		}
		if (j.find("ITEM_SLOT_11_TIME") != j.end())
		{
			j.at("ITEM_SLOT_11_TIME").get_to(ITEM_SLOT_11_TIME);
		}
		if (j.find("ITEM_SLOT_12_TIME") != j.end())
		{
			j.at("ITEM_SLOT_12_TIME").get_to(ITEM_SLOT_12_TIME);
		}
		if (j.find("ITEM_SLOT_13_TIME") != j.end())
		{
			j.at("ITEM_SLOT_13_TIME").get_to(ITEM_SLOT_13_TIME);
		}
		if (j.find("ITEM_SLOT_14_TIME") != j.end())
		{
			j.at("ITEM_SLOT_14_TIME").get_to(ITEM_SLOT_14_TIME);
		}
		if (j.find("ITEM_SLOT_15_TIME") != j.end())
		{
			j.at("ITEM_SLOT_15_TIME").get_to(ITEM_SLOT_15_TIME);
		}
		if (j.find("ITEM_SLOT_16_TIME") != j.end())
		{
			j.at("ITEM_SLOT_16_TIME").get_to(ITEM_SLOT_16_TIME);
		}
		if (j.find("ITEM_PICKUP_ENABLE") != j.end())
		{
			j.at("ITEM_PICKUP_ENABLE").get_to(ITEM_PICKUP_ENABLE);
		}
		if (j.find("ITEM_PICKUP_FILTER_ENABLE") != j.end())
		{
			j.at("ITEM_PICKUP_FILTER_ENABLE").get_to(ITEM_PICKUP_FILTER_ENABLE);
		}
		if (j.find("ITEM_PICKUP_DISTANCE") != j.end())
		{
			j.at("ITEM_PICKUP_DISTANCE").get_to(ITEM_PICKUP_DISTANCE);
		}
		if (j.find("ITEM_PICKUP_STEP") != j.end())
		{
			j.at("ITEM_PICKUP_STEP").get_to(ITEM_PICKUP_STEP);
		}
		if (j.find("ITEM_PICKUP_TIME") != j.end())
		{
			j.at("ITEM_PICKUP_TIME").get_to(ITEM_PICKUP_TIME);
		}
		if (j.find("ITEM_PICKUP_TYPE") != j.end())
		{
			j.at("ITEM_PICKUP_TYPE").get_to(ITEM_PICKUP_TYPE);
		}
		if (j.find("FISH_ENABLE") != j.end())
		{
			j.at("FISH_ENABLE").get_to(FISH_ENABLE);
		}
		if (j.find("FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE") != j.end())
		{
			j.at("FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE").get_to(FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE);
		}
		if (j.find("FISH_CAST_TIME_MIN_VALUE") != j.end())
		{
			j.at("FISH_CAST_TIME_MIN_VALUE").get_to(FISH_CAST_TIME_MIN_VALUE);
		}
		if (j.find("FISH_CAST_TIME_MAX_VALUE") != j.end())
		{
			j.at("FISH_CAST_TIME_MAX_VALUE").get_to(FISH_CAST_TIME_MAX_VALUE);
		}
		if (j.find("FISH_ROUND_TIME_MIN_VALUE") != j.end())
		{
			j.at("FISH_ROUND_TIME_MIN_VALUE").get_to(FISH_ROUND_TIME_MIN_VALUE);
		}
		if (j.find("FISH_ROUND_TIME_MAX_VALUE") != j.end())
		{
			j.at("FISH_ROUND_TIME_MAX_VALUE").get_to(FISH_ROUND_TIME_MAX_VALUE);
		}
		if (j.find("FISH_EMERGENCY_RUN_TIME_VALUE") != j.end())
		{
			j.at("FISH_EMERGENCY_RUN_TIME_VALUE").get_to(FISH_EMERGENCY_RUN_TIME_VALUE);
		}
		if (j.find("FISH_CAST_TIME_ENABLE") != j.end())
		{
			j.at("FISH_CAST_TIME_ENABLE").get_to(FISH_CAST_TIME_ENABLE);
		}
		if (j.find("FISH_ROUND_TIME_ENABLE") != j.end())
		{
			j.at("FISH_ROUND_TIME_ENABLE").get_to(FISH_ROUND_TIME_ENABLE);
		}
		if (j.find("FISH_EMERGENCY_RUN_TIME_ENABLE") != j.end())
		{
			j.at("FISH_EMERGENCY_RUN_TIME_ENABLE").get_to(FISH_EMERGENCY_RUN_TIME_ENABLE);
		}
		if (j.find("FISH_DETECT_PLAYER_ENABLE") != j.end())
		{
			j.at("FISH_DETECT_PLAYER_ENABLE").get_to(FISH_DETECT_PLAYER_ENABLE);
		}
		if (j.find("FISH_KILL_TILL_SIZE_ENABLE") != j.end())
		{
			j.at("FISH_KILL_TILL_SIZE_ENABLE").get_to(FISH_KILL_TILL_SIZE_ENABLE);
		}
		if (j.find("FISH_KILL_TILL_SIZE_VALUE") != j.end())
		{
			j.at("FISH_KILL_TILL_SIZE_VALUE").get_to(FISH_KILL_TILL_SIZE_VALUE);
		}
		if (j.find("FISH_USE_FIRST_SLOT_ENABLE") != j.end())
		{
			j.at("FISH_USE_FIRST_SLOT_ENABLE").get_to(FISH_USE_FIRST_SLOT_ENABLE);
		}
		if (j.find("FISH_KILL_FISH_ENABLE") != j.end())
		{
			j.at("FISH_KILL_FISH_ENABLE").get_to(FISH_KILL_FISH_ENABLE);
		}
		if (j.find("FISH_SELL_TRASH_ENABLE") != j.end())
		{
			j.at("FISH_SELL_TRASH_ENABLE").get_to(FISH_SELL_TRASH_ENABLE);
		}
		if (j.find("FISH_SELL_TRASH_AFTER_PERCENTAGE") != j.end())
		{
			j.at("FISH_SELL_TRASH_AFTER_PERCENTAGE").get_to(FISH_SELL_TRASH_AFTER_PERCENTAGE);
		}
		if (j.find("FISH_DROP_TRASH_ENABLE") != j.end())
		{
			j.at("FISH_DROP_TRASH_ENABLE").get_to(FISH_DROP_TRASH_ENABLE);
		}
		if (j.find("FISH_BUY_BAIT_ENABLE") != j.end())
		{
			j.at("FISH_BUY_BAIT_ENABLE").get_to(FISH_BUY_BAIT_ENABLE);
		}
		if (j.find("FISH_BUY_BAIT_SHOP_SLOT") != j.end())
		{
			j.at("FISH_BUY_BAIT_SHOP_SLOT").get_to(FISH_BUY_BAIT_SHOP_SLOT);
		}
		if (j.find("FISH_BUY_BAIT_SHOP_COUNT") != j.end())
		{
			j.at("FISH_BUY_BAIT_SHOP_COUNT").get_to(FISH_BUY_BAIT_SHOP_COUNT);
		}
		if (j.find("FISH_SHOP_CAST_TELEPORT_ENABLE") != j.end())
		{
			j.at("FISH_SHOP_CAST_TELEPORT_ENABLE").get_to(FISH_SHOP_CAST_TELEPORT_ENABLE);
		}
		if (j.find("FISH_STOP_IF_POSITION_CHANGED_ENABLE") != j.end())
		{
			j.at("FISH_STOP_IF_POSITION_CHANGED_ENABLE").get_to(FISH_STOP_IF_POSITION_CHANGED_ENABLE);
		}
		if (j.find("FISH_STOP_IF_INVENTORY_FULL_ENABLE") != j.end())
		{
			j.at("FISH_STOP_IF_INVENTORY_FULL_ENABLE").get_to(FISH_STOP_IF_INVENTORY_FULL_ENABLE);
		}
		if (j.find("FISH_TELEPORT_STEP_RANGE") != j.end())
		{
			j.at("FISH_TELEPORT_STEP_RANGE").get_to(FISH_TELEPORT_STEP_RANGE);
		}
		if (j.find("FARM_ENABLE") != j.end())
		{
			j.at("FARM_ENABLE").get_to(FARM_ENABLE);
		}
		if (j.find("FARM_MOB_ENABLE") != j.end())
		{
			j.at("FARM_MOB_ENABLE").get_to(FARM_MOB_ENABLE);
		}
		if (j.find("FARM_BOSS_ENABLE") != j.end())
		{
			j.at("FARM_BOSS_ENABLE").get_to(FARM_BOSS_ENABLE);
		}
		if (j.find("FARM_METIN_ENABLE") != j.end())
		{
			j.at("FARM_METIN_ENABLE").get_to(FARM_METIN_ENABLE);
		}
		if (j.find("FARM_MINE_ENABLE") != j.end())
		{
			j.at("FARM_MINE_ENABLE").get_to(FARM_MINE_ENABLE);
		}
		if (j.find("FARM_PLANT_ENABLE") != j.end())
		{
			j.at("FARM_PLANT_ENABLE").get_to(FARM_PLANT_ENABLE);
		}
		if (j.find("FARM_DISTANCE") != j.end())
		{
			j.at("FARM_DISTANCE").get_to(FARM_DISTANCE);
		}
		if (j.find("FARM_DROP_WAIT_DELAY") != j.end())
		{
			j.at("FARM_DROP_WAIT_DELAY").get_to(FARM_DROP_WAIT_DELAY);
		}
		if (j.find("FARM_MOVE_TYPE") != j.end())
		{
			j.at("FARM_MOVE_TYPE").get_to(FARM_MOVE_TYPE);
		}
		if (j.find("FARM_RENDER_PATH_ENABLE") != j.end())
		{
			j.at("FARM_RENDER_PATH_ENABLE").get_to(FARM_RENDER_PATH_ENABLE);
		}
		if (j.find("SPAM_NORMAL_ENABLE") != j.end())
		{
			j.at("SPAM_NORMAL_ENABLE").get_to(SPAM_NORMAL_ENABLE);
		}
		if (j.find("SPAM_SHOUT_ENABLE") != j.end())
		{
			j.at("SPAM_SHOUT_ENABLE").get_to(SPAM_SHOUT_ENABLE);
		}
		if (j.find("SPAM_WISPER_ENABLE") != j.end())
		{
			j.at("SPAM_WISPER_ENABLE").get_to(SPAM_WISPER_ENABLE);
		}
		if (j.find("SPAM_NORMAL_TIME") != j.end())
		{
			j.at("SPAM_NORMAL_TIME").get_to(SPAM_NORMAL_TIME);
		}
		if (j.find("SPAM_WHISPER_TIME") != j.end())
		{
			j.at("SPAM_WHISPER_TIME").get_to(SPAM_WHISPER_TIME);
		}
		if (j.find("SPAM_SHOUT_TIME") != j.end())
		{
			j.at("SPAM_SHOUT_TIME").get_to(SPAM_SHOUT_TIME);
		}
		if (j.find("SPAM_NORMAL_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_NORMAL_COLOR_ENABLE").get_to(SPAM_NORMAL_COLOR_ENABLE);
		}
		if (j.find("SPAM_WHISPER_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_WHISPER_COLOR_ENABLE").get_to(SPAM_WHISPER_COLOR_ENABLE);
		}
		if (j.find("SPAM_SHOUT_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_SHOUT_COLOR_ENABLE").get_to(SPAM_SHOUT_COLOR_ENABLE);
		}
		if (j.find("SPAM_NORMAL_RAINBOW_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_NORMAL_RAINBOW_COLOR_ENABLE").get_to(SPAM_NORMAL_RAINBOW_COLOR_ENABLE);
		}
		if (j.find("SPAM_WHISPER_RAINBOW_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_WHISPER_RAINBOW_COLOR_ENABLE").get_to(SPAM_WHISPER_RAINBOW_COLOR_ENABLE);
		}
		if (j.find("SPAM_SHOUT_RAINBOW_COLOR_ENABLE") != j.end())
		{
			j.at("SPAM_SHOUT_RAINBOW_COLOR_ENABLE").get_to(SPAM_SHOUT_RAINBOW_COLOR_ENABLE);
		}
		if (j.find("REFINE_UPGRADE_TYPE") != j.end())
		{
			j.at("REFINE_UPGRADE_TYPE").get_to(REFINE_UPGRADE_TYPE);
		}
		if (j.find("REFINE_UPGRADE_COUNT") != j.end())
		{
			j.at("REFINE_UPGRADE_COUNT").get_to(REFINE_UPGRADE_COUNT);
		}
		if (j.find("REFINE_ITEM_SLOT") != j.end())
		{
			j.at("REFINE_ITEM_SLOT").get_to(REFINE_ITEM_SLOT);
		}
		if (j.find("BUFF_ENABLE") != j.end())
		{
			j.at("BUFF_ENABLE").get_to(BUFF_ENABLE);
		}
		if (j.find("BUFF_SKILL_1_ENABLE") != j.end())
		{
			j.at("BUFF_SKILL_1_ENABLE").get_to(BUFF_SKILL_1_ENABLE);
		}
		if (j.find("BUFF_SKILL_2_ENABLE") != j.end())
		{
			j.at("BUFF_SKILL_2_ENABLE").get_to(BUFF_SKILL_2_ENABLE);
		}
		if (j.find("BUFF_SKILL_3_ENABLE") != j.end())
		{
			j.at("BUFF_SKILL_3_ENABLE").get_to(BUFF_SKILL_3_ENABLE);
		}
		if (j.find("BUFF_SKILL_1_TIME") != j.end())
		{
			j.at("BUFF_SKILL_1_TIME").get_to(BUFF_SKILL_1_TIME);
		}
		if (j.find("BUFF_SKILL_2_TIME") != j.end())
		{
			j.at("BUFF_SKILL_2_TIME").get_to(BUFF_SKILL_2_TIME);
		}
		if (j.find("BUFF_SKILL_3_TIME") != j.end())
		{
			j.at("BUFF_SKILL_3_TIME").get_to(BUFF_SKILL_3_TIME);
		}
		if (j.find("STATUS_ENABLE") != j.end())
		{
			j.at("STATUS_ENABLE").get_to(STATUS_ENABLE);
		}
		if (j.find("PROTECTION_SHOW_WHISPER_LOGS_ENABLE") != j.end())
		{
			j.at("PROTECTION_SHOW_WHISPER_LOGS_ENABLE").get_to(PROTECTION_SHOW_WHISPER_LOGS_ENABLE);
		}
		if (j.find("PROTECTION_SHOW_WHISPER_BALLOON_ENABLE") != j.end())
		{
			j.at("PROTECTION_SHOW_WHISPER_BALLOON_ENABLE").get_to(PROTECTION_SHOW_WHISPER_BALLOON_ENABLE);
		}
		if (j.find("PROTECTION_SHOW_TALK_BALLOON_ENABLE") != j.end())
		{
			j.at("PROTECTION_SHOW_TALK_BALLOON_ENABLE").get_to(PROTECTION_SHOW_TALK_BALLOON_ENABLE);
		}
		if (j.find("PROTECTION_PLAY_WHISPER_BEEP_ENABLE") != j.end())
		{
			j.at("PROTECTION_PLAY_WHISPER_BEEP_ENABLE").get_to(PROTECTION_PLAY_WHISPER_BEEP_ENABLE);
		}
		if (j.find("PROTECTION_PLAY_TALK_BEEP_ENABLE") != j.end())
		{
			j.at("PROTECTION_PLAY_TALK_BEEP_ENABLE").get_to(PROTECTION_PLAY_TALK_BEEP_ENABLE);
		}
		if (j.find("PROTECTION_FLASH_TALK_ICON_ENABLE") != j.end())
		{
			j.at("PROTECTION_FLASH_TALK_ICON_ENABLE").get_to(PROTECTION_FLASH_TALK_ICON_ENABLE);
		}
		if (j.find("PROTECTION_SHOW_TALK_LOGS_ENABLE") != j.end())
		{
			j.at("PROTECTION_SHOW_TALK_LOGS_ENABLE").get_to(PROTECTION_SHOW_TALK_LOGS_ENABLE);
		}
		if (j.find("PROTECTION_RESTORE_WISPER_WINDOW_ENABLE") != j.end())
		{
			j.at("PROTECTION_RESTORE_WISPER_WINDOW_ENABLE").get_to(PROTECTION_RESTORE_WISPER_WINDOW_ENABLE);
		}
		if (j.find("PROTECTION_FLASH_WHISPER_ICON_ENABLE") != j.end())
		{
			j.at("PROTECTION_FLASH_WHISPER_ICON_ENABLE").get_to(PROTECTION_FLASH_WHISPER_ICON_ENABLE);
		}
		if (j.find("PROTECTION_DISABLE_RENDER_ENABLE") != j.end())
		{
			j.at("PROTECTION_DISABLE_RENDER_ENABLE").get_to(PROTECTION_DISABLE_RENDER_ENABLE);
		}
		if (j.find("PROTECTION_DISABLE_UPDATE_ENABLE") != j.end())
		{
			j.at("PROTECTION_DISABLE_UPDATE_ENABLE").get_to(PROTECTION_DISABLE_UPDATE_ENABLE);
		}
		if (j.find("PROTECTION_DISABLE_RENDER_FRAMES_ENABLE") != j.end())
		{
			j.at("PROTECTION_DISABLE_RENDER_FRAMES_ENABLE").get_to(PROTECTION_DISABLE_RENDER_FRAMES_ENABLE);
		}
		if (j.find("PROTECTION_AUTO_LOGIN_ENABLE") != j.end())
		{
			j.at("PROTECTION_AUTO_LOGIN_ENABLE").get_to(PROTECTION_AUTO_LOGIN_ENABLE);
		}
		if (j.find("RADAR_MONSTER_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_MONSTER_SHOW_ENABLE").get_to(RADAR_MONSTER_SHOW_ENABLE);
		}
		if (j.find("RADAR_BOSS_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_BOSS_SHOW_ENABLE").get_to(RADAR_BOSS_SHOW_ENABLE);
		}
		if (j.find("RADAR_NPC_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_NPC_SHOW_ENABLE").get_to(RADAR_NPC_SHOW_ENABLE);
		}
		if (j.find("RADAR_MINING_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_MINING_SHOW_ENABLE").get_to(RADAR_MINING_SHOW_ENABLE);
		}
		if (j.find("RADAR_STONE_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_STONE_SHOW_ENABLE").get_to(RADAR_STONE_SHOW_ENABLE);
		}
		if (j.find("RADAR_PLAYER_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_PLAYER_SHOW_ENABLE").get_to(RADAR_PLAYER_SHOW_ENABLE);
		}
		if (j.find("RADAR_WAYPOINT_SHOW_ENABLE") != j.end())
		{
			j.at("RADAR_WAYPOINT_SHOW_ENABLE").get_to(RADAR_WAYPOINT_SHOW_ENABLE);
		}
		if (j.find("MAIN_WH_RENDER_COLOR") != j.end())
		{
			ns::from_json(j.at("MAIN_WH_RENDER_COLOR"), MAIN_WH_RENDER_COLOR);
		}
		if (j.find("FISH_SHOP_TELEPORT_CORDS") != j.end())
		{
			ns::from_json(j.at("FISH_SHOP_TELEPORT_CORDS"), FISH_SHOP_TELEPORT_CORDS);
		}
		if (j.find("FISH_CAST_TELEPORT_CORDS") != j.end())
		{
			ns::from_json(j.at("FISH_CAST_TELEPORT_CORDS"), FISH_CAST_TELEPORT_CORDS);
		}
		if (j.find("SPAM_NORMAL_COLOR") != j.end())
		{
			ns::from_json(j.at("SPAM_NORMAL_COLOR"), SPAM_NORMAL_COLOR);
		}
		if (j.find("SPAM_WHISPER_COLOR") != j.end())
		{
			ns::from_json(j.at("SPAM_WHISPER_COLOR"), SPAM_WHISPER_COLOR);
		}
		if (j.find("SPAM_SHOUT_COLOR") != j.end())
		{
			ns::from_json(j.at("SPAM_SHOUT_COLOR"), SPAM_SHOUT_COLOR);
		}
		if (j.find("RADAR_MONSTER_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_MONSTER_COLOR"), RADAR_MONSTER_COLOR);
		}
		if (j.find("RADAR_BOSS_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_BOSS_COLOR"), RADAR_BOSS_COLOR);
		}
		if (j.find("RADAR_NPC_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_NPC_COLOR"), RADAR_NPC_COLOR);
		}
		if (j.find("RADAR_MINE_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_MINE_COLOR"), RADAR_MINE_COLOR);
		}
		if (j.find("RADAR_STONE_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_STONE_COLOR"), RADAR_STONE_COLOR);
		}
		if (j.find("RADAR_PLAYER_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_PLAYER_COLOR"), RADAR_PLAYER_COLOR);
		}
		if (j.find("RADAR_WAYPOINT_COLOR") != j.end())
		{
			ns::from_json(j.at("RADAR_WAYPOINT_COLOR"), RADAR_WAYPOINT_COLOR);
		}
		LoadServerVariables();
	}

	static void Save(string name, string folderPath)
	{
		nlohmann::json j = nlohmann::json
		{
			{"PROTECTION_DETECT_PLAYER_WHITE_LIST", PROTECTION_DETECT_PLAYER_WHITE_LIST},
			{"FISH_KILL_FISH_LIST", FISH_KILL_FISH_LIST},
			{ "FISH_BAIT_LIST", FISH_BAIT_LIST },
			{ "FISH_DROP_LIST", FISH_DROP_LIST },
			{ "FISH_SELL_LIST", FISH_SELL_LIST },
			{ "ITEM_PICKUP_SELECTED_LIST", ITEM_PICKUP_SELECTED_LIST },
			{ "MAIN_STONE_DETECT_ENABLE", MAIN_STONE_DETECT_ENABLE },
			{ "MAIN_MOBBER_ENABLE", MAIN_MOBBER_ENABLE },
			{ "MAIN_ATTACK_ENABLE", MAIN_ATTACK_ENABLE },
			{ "MAIN_ROTATION_ENABLE", MAIN_ROTATION_ENABLE },
			{ "MAIN_ROTATION_SPEED_VALUE", MAIN_ROTATION_SPEED_VALUE },
			{ "MAIN_SKILL_ENABLE", MAIN_SKILL_ENABLE },
			{ "MAIN_SKILL_1_ENABLE", MAIN_SKILL_1_ENABLE },
			{ "MAIN_SKILL_2_ENABLE", MAIN_SKILL_2_ENABLE },
			{ "MAIN_SKILL_3_ENABLE", MAIN_SKILL_3_ENABLE },
			{ "MAIN_SKILL_4_ENABLE", MAIN_SKILL_4_ENABLE },
			{ "MAIN_SKILL_5_ENABLE", MAIN_SKILL_5_ENABLE },
			{ "MAIN_SKILL_6_ENABLE", MAIN_SKILL_6_ENABLE },
			{ "MAIN_NOK_ENABLE", MAIN_NOK_ENABLE },
			{ "MAIN_NOP_ENABLE", MAIN_NOP_ENABLE },
			{ "MAIN_WALL_MOB_ENABLE", MAIN_WALL_MOB_ENABLE },
			{ "MAIN_WALL_OBJECT_ENABLE", MAIN_WALL_OBJECT_ENABLE },
			{ "MAIN_WALL_TERRAIN_ENABLE", MAIN_WALL_TERRAIN_ENABLE },
			{ "MAIN_WH_ENABLE", MAIN_WH_ENABLE },
			{ "MAIN_WH_DISTANCE_VALUE", MAIN_WH_DISTANCE_VALUE },
			{ "MAIN_WH_DISTANCE_STEP", MAIN_WH_DISTANCE_STEP },
			{ "MAIN_WH_TYPE", MAIN_WH_WEAPON_TYPE },
			{ "MAIN_WAITHACK_RANGE_ENABLE", MAIN_WAITHACK_RANGE_ENABLE },
			{ "MAIN_WH_SKILL_COOLDOWN_TIME", MAIN_WH_SKILL_COOLDOWN_TIME },
			{ "MAIN_WH_TIME", MAIN_WH_TIME },
			{ "MAIN_WH_ATTACK_TYPE", MAIN_WH_ATTACK_TYPE },
			{ "MAIN_WH_RENDER_ENABLE", MAIN_WH_RENDER_ENABLE },
			{ "MAIN_WH_MONSTER", MAIN_WH_MONSTER },
			{ "MAIN_WH_SKILL_VALUE", MAIN_WH_SKILL_VALUE },
			{ "MAIN_WH_METIN", MAIN_WH_METIN },
			{ "MAIN_WH_BOSS", MAIN_WH_BOSS },
			{ "MAIN_WH_PLAYER", MAIN_WH_PLAYER },
			{ "MAIN_MOB_DETECT_ENABLE", MAIN_MOB_DETECT_ENABLE },
			{ "MAIN_POTION_ENABLE", MAIN_POTION_ENABLE },
			{ "MAIN_RED_POTION_ENABLE", MAIN_RED_POTION_ENABLE },
			{ "MAIN_RED_POTION_PERCENTAGE_VALUE", MAIN_RED_POTION_PERCENTAGE_VALUE },
			{ "MAIN_RED_POTION_SPEED_VALUE", MAIN_RED_POTION_SPEED_VALUE },
			{ "MAIN_BLUE_POTION_ENABLE", MAIN_BLUE_POTION_ENABLE },
			{ "MAIN_BLUE_POTION_PERCENTAGE_VALUE", MAIN_BLUE_POTION_PERCENTAGE_VALUE },
			{ "MAIN_BLUE_POTION_SPEED_VALUE", MAIN_BLUE_POTION_SPEED_VALUE },
			{ "MAIN_AUTO_REVIVE_ENABLE", MAIN_AUTO_REVIVE_ENABLE },
			{ "MAIN_AUTO_REVIVE_PERCENTAGE_VALUE", MAIN_AUTO_REVIVE_PERCENTAGE_VALUE },
			{ "MAIN_CHANNEL_CHANGER_PORT_OFFSET", MAIN_CHANNEL_CHANGER_PORT_OFFSET },
			{ "MAIN_BOOST_KEY", MAIN_BOOST_KEY },
			{ "MAIN_RELOG_KEY", MAIN_RELOG_KEY },
			{ "MAIN_GLOBAL_SWITCH_KEY", MAIN_GLOBAL_SWITCH_KEY },
			{ "MAIN_HIDE_UI_KEY", MAIN_HIDE_UI_KEY },
			{ "MAIN_BOOST_SPEED", MAIN_BOOST_SPEED },
			{ "MAIN_WH_DETECT_PLAYER_ENABLE", MAIN_WH_DETECT_PLAYER_ENABLE },
			{ "ITEM_SLOT_RANDOM_ENABLE", ITEM_SLOT_RANDOM_ENABLE },
			{ "ITEM_SLOT_3_ENABLE", ITEM_SLOT_3_ENABLE },
			{ "ITEM_SLOT_4_ENABLE", ITEM_SLOT_4_ENABLE },
			{ "ITEM_SLOT_5_ENABLE", ITEM_SLOT_5_ENABLE },
			{ "ITEM_SLOT_6_ENABLE", ITEM_SLOT_6_ENABLE },
			{ "ITEM_SLOT_7_ENABLE", ITEM_SLOT_7_ENABLE },
			{ "ITEM_SLOT_8_ENABLE", ITEM_SLOT_8_ENABLE },
			{ "ITEM_SLOT_9_ENABLE", ITEM_SLOT_9_ENABLE },
			{ "ITEM_SLOT_10_ENABLE", ITEM_SLOT_10_ENABLE },
			{ "ITEM_SLOT_11_ENABLE", ITEM_SLOT_11_ENABLE },
			{ "ITEM_SLOT_12_ENABLE", ITEM_SLOT_12_ENABLE },
			{ "ITEM_SLOT_13_ENABLE", ITEM_SLOT_13_ENABLE },
			{ "ITEM_SLOT_14_ENABLE", ITEM_SLOT_14_ENABLE },
			{ "ITEM_SLOT_15_ENABLE", ITEM_SLOT_15_ENABLE },
			{ "ITEM_SLOT_16_ENABLE", ITEM_SLOT_16_ENABLE },
			{ "ITEM_SLOT_RANDOM_MIN_TIME", ITEM_SLOT_RANDOM_MIN_TIME },
			{ "ITEM_SLOT_RANDOM_MAX_TIME", ITEM_SLOT_RANDOM_MAX_TIME },
			{ "ITEM_SLOT_3_TIME", ITEM_SLOT_3_TIME },
			{ "ITEM_SLOT_4_TIME", ITEM_SLOT_4_TIME },
			{ "ITEM_SLOT_5_TIME", ITEM_SLOT_5_TIME },
			{ "ITEM_SLOT_6_TIME", ITEM_SLOT_6_TIME },
			{ "ITEM_SLOT_7_TIME", ITEM_SLOT_7_TIME },
			{ "ITEM_SLOT_8_TIME", ITEM_SLOT_8_TIME },
			{ "ITEM_SLOT_9_TIME", ITEM_SLOT_9_TIME },
			{ "ITEM_SLOT_10_TIME", ITEM_SLOT_10_TIME },
			{ "ITEM_SLOT_11_TIME", ITEM_SLOT_11_TIME },
			{ "ITEM_SLOT_12_TIME", ITEM_SLOT_12_TIME },
			{ "ITEM_SLOT_13_TIME", ITEM_SLOT_13_TIME },
			{ "ITEM_SLOT_14_TIME", ITEM_SLOT_14_TIME },
			{ "ITEM_SLOT_15_TIME", ITEM_SLOT_15_TIME },
			{ "ITEM_SLOT_16_TIME", ITEM_SLOT_16_TIME },
			{ "ITEM_PICKUP_ENABLE", ITEM_PICKUP_ENABLE },
			{ "ITEM_PICKUP_FILTER_ENABLE", ITEM_PICKUP_FILTER_ENABLE },
			{ "ITEM_PICKUP_DISTANCE", ITEM_PICKUP_DISTANCE },
			{ "ITEM_PICKUP_STEP", ITEM_PICKUP_STEP },
			{ "ITEM_PICKUP_TIME", ITEM_PICKUP_TIME },
			{ "ITEM_PICKUP_TYPE", ITEM_PICKUP_TYPE },
			{ "FISH_ENABLE", FISH_ENABLE },
			{ "FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE", FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE },
			{ "FISH_CAST_TIME_MIN_VALUE", FISH_CAST_TIME_MIN_VALUE },
			{ "FISH_CAST_TIME_MAX_VALUE", FISH_CAST_TIME_MAX_VALUE },
			{ "FISH_ROUND_TIME_MIN_VALUE", FISH_ROUND_TIME_MIN_VALUE },
			{ "FISH_ROUND_TIME_MAX_VALUE", FISH_ROUND_TIME_MAX_VALUE },
			{ "FISH_EMERGENCY_RUN_TIME_VALUE", FISH_EMERGENCY_RUN_TIME_VALUE },
			{ "FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE", FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE },
			{ "FISH_CAST_TIME_ENABLE", FISH_CAST_TIME_ENABLE },
			{ "FISH_ROUND_TIME_ENABLE", FISH_ROUND_TIME_ENABLE },
			{ "FISH_EMERGENCY_RUN_TIME_ENABLE", FISH_EMERGENCY_RUN_TIME_ENABLE },
			{ "FISH_DETECT_PLAYER_ENABLE", FISH_DETECT_PLAYER_ENABLE },
			{ "FISH_KILL_TILL_SIZE_ENABLE", FISH_KILL_TILL_SIZE_ENABLE },
			{ "FISH_KILL_TILL_SIZE_VALUE", FISH_KILL_TILL_SIZE_VALUE },
			{ "FISH_USE_FIRST_SLOT_ENABLE", FISH_USE_FIRST_SLOT_ENABLE },
			{ "FISH_KILL_FISH_ENABLE", FISH_KILL_FISH_ENABLE },
			{ "FISH_SELL_TRASH_ENABLE", FISH_SELL_TRASH_ENABLE },
			{ "FISH_SELL_TRASH_AFTER_PERCENTAGE", FISH_SELL_TRASH_AFTER_PERCENTAGE },
			{ "FISH_DROP_TRASH_ENABLE", FISH_DROP_TRASH_ENABLE },
			{ "FISH_BUY_BAIT_ENABLE", FISH_BUY_BAIT_ENABLE },
			{ "FISH_BUY_BAIT_SHOP_SLOT", FISH_BUY_BAIT_SHOP_SLOT },
			{ "FISH_BUY_BAIT_SHOP_COUNT", FISH_BUY_BAIT_SHOP_COUNT },
			{ "FISH_SHOP_CAST_TELEPORT_ENABLE", FISH_SHOP_CAST_TELEPORT_ENABLE },
			{ "FISH_STOP_IF_POSITION_CHANGED_ENABLE", FISH_STOP_IF_POSITION_CHANGED_ENABLE },
			{ "FISH_STOP_IF_INVENTORY_FULL_ENABLE", FISH_STOP_IF_INVENTORY_FULL_ENABLE },
			{ "FISH_TELEPORT_STEP_RANGE", FISH_TELEPORT_STEP_RANGE },
			{ "FARM_ENABLE", FARM_ENABLE },
			{ "FARM_MOB_ENABLE", FARM_MOB_ENABLE },
			{ "FARM_BOSS_ENABLE", FARM_BOSS_ENABLE },
			{ "FARM_METIN_ENABLE", FARM_METIN_ENABLE },
			{ "FARM_MINE_ENABLE", FARM_MINE_ENABLE },
			{ "FARM_PLANT_ENABLE", FARM_PLANT_ENABLE },
			{ "FARM_DISTANCE", FARM_DISTANCE },
			{ "FARM_DROP_WAIT_DELAY", FARM_DROP_WAIT_DELAY },
			{ "FARM_MOVE_TYPE", FARM_MOVE_TYPE },
			{ "FARM_RENDER_PATH_ENABLE", FARM_RENDER_PATH_ENABLE },
			{ "SPAM_NORMAL_ENABLE", SPAM_NORMAL_ENABLE },
			{ "SPAM_SHOUT_ENABLE", SPAM_SHOUT_ENABLE },
			{ "SPAM_WISPER_ENABLE", SPAM_WISPER_ENABLE },
			{ "SPAM_NORMAL_TIME", SPAM_NORMAL_TIME },
			{ "SPAM_WHISPER_TIME", SPAM_WHISPER_TIME },
			{ "SPAM_SHOUT_TIME", SPAM_SHOUT_TIME },
			{ "SPAM_NORMAL_COLOR_ENABLE", SPAM_NORMAL_COLOR_ENABLE },
			{ "SPAM_WHISPER_COLOR_ENABLE", SPAM_WHISPER_COLOR_ENABLE },
			{ "SPAM_SHOUT_COLOR_ENABLE", SPAM_SHOUT_COLOR_ENABLE },
			{ "SPAM_NORMAL_RAINBOW_COLOR_ENABLE", SPAM_NORMAL_RAINBOW_COLOR_ENABLE },
			{ "SPAM_WHISPER_RAINBOW_COLOR_ENABLE", SPAM_WHISPER_RAINBOW_COLOR_ENABLE },
			{ "SPAM_SHOUT_RAINBOW_COLOR_ENABLE", SPAM_SHOUT_RAINBOW_COLOR_ENABLE },
			{ "REFINE_UPGRADE_TYPE", REFINE_UPGRADE_TYPE },
			{ "REFINE_UPGRADE_COUNT", REFINE_UPGRADE_COUNT },
			{ "REFINE_ITEM_SLOT", REFINE_ITEM_SLOT },
			{ "BUFF_ENABLE", BUFF_ENABLE },
			{ "BUFF_SKILL_1_ENABLE", BUFF_SKILL_1_ENABLE },
			{ "BUFF_SKILL_2_ENABLE", BUFF_SKILL_2_ENABLE },
			{ "BUFF_SKILL_3_ENABLE", BUFF_SKILL_3_ENABLE },
			{ "BUFF_SKILL_1_TIME", BUFF_SKILL_1_TIME },
			{ "BUFF_SKILL_2_TIME", BUFF_SKILL_2_TIME },
			{ "BUFF_SKILL_3_TIME", BUFF_SKILL_3_TIME },
			{ "STATUS_ENABLE", STATUS_ENABLE },
			{ "PROTECTION_SHOW_WHISPER_LOGS_ENABLE", PROTECTION_SHOW_WHISPER_LOGS_ENABLE },
			{ "PROTECTION_SHOW_WHISPER_BALLOON_ENABLE", PROTECTION_SHOW_WHISPER_BALLOON_ENABLE },
			{ "PROTECTION_SHOW_TALK_BALLOON_ENABLE", PROTECTION_SHOW_TALK_BALLOON_ENABLE },
			{ "PROTECTION_PLAY_WHISPER_BEEP_ENABLE", PROTECTION_PLAY_WHISPER_BEEP_ENABLE },
			{ "PROTECTION_PLAY_TALK_BEEP_ENABLE", PROTECTION_PLAY_TALK_BEEP_ENABLE },
			{ "PROTECTION_FLASH_TALK_ICON_ENABLE", PROTECTION_FLASH_TALK_ICON_ENABLE },
			{ "PROTECTION_SHOW_TALK_LOGS_ENABLE", PROTECTION_SHOW_TALK_LOGS_ENABLE },
			{ "PROTECTION_RESTORE_WISPER_WINDOW_ENABLE", PROTECTION_RESTORE_WISPER_WINDOW_ENABLE },
			{ "PROTECTION_FLASH_WHISPER_ICON_ENABLE", PROTECTION_FLASH_WHISPER_ICON_ENABLE },
			{ "PROTECTION_DISABLE_RENDER_ENABLE", PROTECTION_DISABLE_RENDER_ENABLE },
			{ "PROTECTION_DISABLE_UPDATE_ENABLE", PROTECTION_DISABLE_UPDATE_ENABLE },
			{ "PROTECTION_DISABLE_RENDER_FRAMES_ENABLE", PROTECTION_DISABLE_RENDER_FRAMES_ENABLE },
			{ "PROTECTION_AUTO_LOGIN_ENABLE", PROTECTION_AUTO_LOGIN_ENABLE },
			{ "RADAR_MONSTER_SHOW_ENABLE", RADAR_MONSTER_SHOW_ENABLE },
			{ "RADAR_BOSS_SHOW_ENABLE", RADAR_BOSS_SHOW_ENABLE },
			{ "RADAR_NPC_SHOW_ENABLE", RADAR_NPC_SHOW_ENABLE },
			{ "RADAR_MINING_SHOW_ENABLE", RADAR_MINING_SHOW_ENABLE },
			{ "RADAR_STONE_SHOW_ENABLE", RADAR_STONE_SHOW_ENABLE },
			{ "RADAR_PLAYER_SHOW_ENABLE", RADAR_PLAYER_SHOW_ENABLE },
			{ "RADAR_WAYPOINT_SHOW_ENABLE", RADAR_WAYPOINT_SHOW_ENABLE },
			
		};
		ns::to_json(j["MAIN_WH_RENDER_COLOR"], MAIN_WH_RENDER_COLOR);
		ns::to_json(j["FISH_SHOP_TELEPORT_CORDS"], FISH_SHOP_TELEPORT_CORDS);
		ns::to_json(j["FISH_CAST_TELEPORT_CORDS"], FISH_CAST_TELEPORT_CORDS);
		ns::to_json(j["SPAM_NORMAL_COLOR"], SPAM_NORMAL_COLOR);
		ns::to_json(j["SPAM_WHISPER_COLOR"], SPAM_WHISPER_COLOR);
		ns::to_json(j["SPAM_SHOUT_COLOR"], SPAM_SHOUT_COLOR);
		ns::to_json(j["RADAR_MONSTER_COLOR"], RADAR_MONSTER_COLOR);
		ns::to_json(j["RADAR_BOSS_COLOR"], RADAR_BOSS_COLOR);
		ns::to_json(j["RADAR_NPC_COLOR"], RADAR_NPC_COLOR);
		ns::to_json(j["RADAR_MINE_COLOR"], RADAR_MINE_COLOR);
		ns::to_json(j["RADAR_STONE_COLOR"], RADAR_STONE_COLOR);
		ns::to_json(j["RADAR_PLAYER_COLOR"], RADAR_PLAYER_COLOR);
		ns::to_json(j["RADAR_WAYPOINT_COLOR"], RADAR_WAYPOINT_COLOR);
		string dump = j.dump(4);
		if (FileExtension::CreateDirectoryPath(folderPath.c_str()))
		{
			string filePath = folderPath + name + ".mc";
			FileExtension::Write(filePath, dump);
		}	
	}

	static void Remove(string name, string folderPath, string extension)
	{
		string path = folderPath + name + "." + extension;
		remove(path.c_str());
	}

	static vector<string>												PROTECTION_DETECT_PLAYER_WHITE_LIST;
	static map< pair<DWORD, bool>, pair<DWORD, string>>					FISH_KILL_FISH_LIST;
	static map< pair<DWORD, bool>, pair<DWORD, string>>					FISH_BAIT_LIST;
	static map< pair<DWORD, bool>, pair<DWORD, string>>					FISH_DROP_LIST;
	static map< pair<DWORD, bool>, pair<DWORD, string>>					FISH_SELL_LIST;
	static map< DWORD, pair<DWORD, DWORD>>								FISH_ROD_REFINE_POINTS;
	static map<DWORD, pair<string, DWORD>>								FISH_COMMAND_LIST;
	static map< pair<DWORD, pair<string, string>>, pair<DWORD, string>> SERVER_INFO_LIST_GLOBAL;
	static map< pair<DWORD, pair<DWORD, string>>, pair<DWORD, string>>	SERVER_INFO_LIST;
	static map< DWORD, pair<string, bool>>								ITEM_PICKUP_SELECTED_LIST;
	static vector<D3DVECTOR> cordsMaps;

	//#################        MAIN

	static bool			MAIN_STONE_DETECT_ENABLE;
	static bool			MAIN_MOBBER_ENABLE;
	static bool			MAIN_ATTACK_ENABLE;
	static bool			MAIN_ROTATION_ENABLE;
	static int			MAIN_ROTATION_SPEED_VALUE;
	static bool			MAIN_SKILL_ENABLE;
	static bool			MAIN_SKILL_1_ENABLE;
	static bool			MAIN_SKILL_2_ENABLE;
	static bool			MAIN_SKILL_3_ENABLE;
	static bool			MAIN_SKILL_4_ENABLE;
	static bool			MAIN_SKILL_5_ENABLE;
	static bool			MAIN_SKILL_6_ENABLE;
	static bool			MAIN_NOK_ENABLE;
	static bool			MAIN_NOP_ENABLE;
	static bool			MAIN_WALL_MOB_ENABLE;
	static bool			MAIN_WALL_OBJECT_ENABLE;
	static bool			MAIN_WALL_TERRAIN_ENABLE;
	static bool			MAIN_WH_ENABLE;
	static int			MAIN_WH_DISTANCE_VALUE;
	static int			MAIN_WH_DISTANCE_STEP;
	static int			MAIN_WH_WEAPON_TYPE;
	static bool			MAIN_WAITHACK_RANGE_ENABLE;
	static int			MAIN_WH_SKILL_COOLDOWN_TIME;
	static int			MAIN_WH_TIME;
	static int			MAIN_WH_ATTACK_TYPE;
	static bool			MAIN_WH_RENDER_ENABLE;
	static ImVec4		MAIN_WH_RENDER_COLOR;
	static int			MAIN_WH_SKILL_VALUE;
	static bool			MAIN_WH_MONSTER;
	static bool			MAIN_WH_METIN;
	static bool			MAIN_WH_BOSS;
	static bool			MAIN_WH_PLAYER;
	static bool			MAIN_MOB_DETECT_ENABLE;
	static bool			MAIN_POTION_ENABLE;
	static bool			MAIN_RED_POTION_ENABLE;
	static int			MAIN_RED_POTION_PERCENTAGE_VALUE;
	static int			MAIN_RED_POTION_SPEED_VALUE;
	static bool			MAIN_BLUE_POTION_ENABLE;
	static int			MAIN_BLUE_POTION_PERCENTAGE_VALUE;
	static int			MAIN_BLUE_POTION_SPEED_VALUE;
	static bool			MAIN_AUTO_REVIVE_ENABLE;
	static int			MAIN_AUTO_REVIVE_PERCENTAGE_VALUE;
	static int			MAIN_CHANNEL_CHANGER_PORT_OFFSET;
	static int			MAIN_BOOST_KEY;
	static int			MAIN_RELOG_KEY;
	static int			MAIN_GLOBAL_SWITCH_KEY;
	static int			MAIN_HIDE_UI_KEY;
	static int			MAIN_BOOST_SPEED;
	static bool			MAIN_WH_DETECT_PLAYER_ENABLE;
	
	//#################        ITEM

	static bool			ITEM_SLOT_RANDOM_ENABLE;
	static bool			ITEM_SLOT_3_ENABLE;
	static bool			ITEM_SLOT_4_ENABLE;
	static bool			ITEM_SLOT_5_ENABLE;
	static bool			ITEM_SLOT_6_ENABLE;
	static bool			ITEM_SLOT_7_ENABLE;
	static bool			ITEM_SLOT_8_ENABLE;
	static bool			ITEM_SLOT_9_ENABLE;
	static bool			ITEM_SLOT_10_ENABLE;
	static bool			ITEM_SLOT_11_ENABLE;
	static bool			ITEM_SLOT_12_ENABLE;
	static bool			ITEM_SLOT_13_ENABLE;
	static bool			ITEM_SLOT_14_ENABLE;
	static bool			ITEM_SLOT_15_ENABLE;
	static bool			ITEM_SLOT_16_ENABLE;
	static float		ITEM_SLOT_RANDOM_MIN_TIME;
	static float		ITEM_SLOT_RANDOM_MAX_TIME;
	static float		ITEM_SLOT_3_TIME;
	static float		ITEM_SLOT_4_TIME;
	static float		ITEM_SLOT_5_TIME;
	static float		ITEM_SLOT_6_TIME;
	static float		ITEM_SLOT_7_TIME;
	static float		ITEM_SLOT_8_TIME;
	static float		ITEM_SLOT_9_TIME;
	static float		ITEM_SLOT_10_TIME;
	static float		ITEM_SLOT_11_TIME;
	static float		ITEM_SLOT_12_TIME;
	static float		ITEM_SLOT_13_TIME;
	static float		ITEM_SLOT_14_TIME;
	static float		ITEM_SLOT_15_TIME;
	static float		ITEM_SLOT_16_TIME;
	static bool			ITEM_PICKUP_ENABLE;
	static bool			ITEM_PICKUP_FILTER_ENABLE;
	static int			ITEM_PICKUP_DISTANCE;
	static int			ITEM_PICKUP_STEP;
	static int			ITEM_PICKUP_TIME;
	static int			ITEM_PICKUP_TYPE;

	//#################        FISH

	static bool			FISH_ENABLE;
	static int			FISH_SUCCESS_PERCENTAGE_VALUE;
	static int			FISH_CAST_TIME_MIN_VALUE;
	static int			FISH_CAST_TIME_MAX_VALUE;
	static int			FISH_ROUND_TIME_MIN_VALUE;
	static int			FISH_ROUND_TIME_MAX_VALUE;
	static int			FISH_EMERGENCY_RUN_TIME_VALUE;
	static bool			FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE;
	static bool			FISH_CAST_TIME_ENABLE;
	static bool			FISH_ROUND_TIME_ENABLE;
	static bool			FISH_EMERGENCY_RUN_TIME_ENABLE;
	static bool			FISH_DETECT_PLAYER_ENABLE;
	static bool			FISH_KILL_TILL_SIZE_ENABLE;
	static float		FISH_KILL_TILL_SIZE_VALUE;
	static bool			FISH_USE_FIRST_SLOT_ENABLE;
	static bool			FISH_KILL_FISH_ENABLE;
	static bool			FISH_SELL_TRASH_ENABLE;
	static int			FISH_SELL_TRASH_AFTER_PERCENTAGE;
	static bool			FISH_DROP_TRASH_ENABLE;
	static bool			FISH_BUY_BAIT_ENABLE;
	static int			FISH_BUY_BAIT_SHOP_SLOT;
	static int			FISH_BUY_BAIT_SHOP_COUNT;
	static bool			FISH_SHOP_CAST_TELEPORT_ENABLE;
	static D3DVECTOR	FISH_SHOP_TELEPORT_CORDS;
	static D3DVECTOR	FISH_CAST_TELEPORT_CORDS;
	static bool			FISH_STOP_IF_POSITION_CHANGED_ENABLE;
	static bool			FISH_STOP_IF_INVENTORY_FULL_ENABLE;
	static int			FISH_TELEPORT_STEP_RANGE;

	//#################        FARM

	static bool			FARM_ENABLE;
	static bool			FARM_MOB_ENABLE;
	static bool			FARM_BOSS_ENABLE;
	static bool			FARM_METIN_ENABLE;
	static bool			FARM_MINE_ENABLE;
	static bool			FARM_PLANT_ENABLE;
	static int			FARM_DISTANCE;
	static float		FARM_DROP_WAIT_DELAY;
	static int			FARM_MOVE_TYPE;
	static bool			FARM_RENDER_PATH_ENABLE;

	//#################        SPAM

	static bool			SPAM_NORMAL_ENABLE;
	static bool			SPAM_SHOUT_ENABLE;
	static bool			SPAM_WISPER_ENABLE;
	static float		SPAM_NORMAL_TIME;
	static float		SPAM_WHISPER_TIME;
	static float		SPAM_SHOUT_TIME;
	static ImVec4		SPAM_NORMAL_COLOR;
	static ImVec4		SPAM_WHISPER_COLOR;
	static ImVec4		SPAM_SHOUT_COLOR;
	static bool			SPAM_NORMAL_COLOR_ENABLE;
	static bool			SPAM_WHISPER_COLOR_ENABLE;
	static bool			SPAM_SHOUT_COLOR_ENABLE;
	static bool			SPAM_NORMAL_RAINBOW_COLOR_ENABLE;
	static bool			SPAM_WHISPER_RAINBOW_COLOR_ENABLE;
	static bool			SPAM_SHOUT_RAINBOW_COLOR_ENABLE;

	//#################        REFINE

	static int			REFINE_UPGRADE_TYPE;
	static int			REFINE_UPGRADE_COUNT;
	static int			REFINE_ITEM_SLOT;

	//#################        BUFF

	static bool			BUFF_ENABLE;
	static bool			BUFF_SKILL_1_ENABLE;
	static bool			BUFF_SKILL_2_ENABLE;
	static bool			BUFF_SKILL_3_ENABLE;
	static float		BUFF_SKILL_1_TIME;
	static float		BUFF_SKILL_2_TIME;
	static float		BUFF_SKILL_3_TIME;

	//#################        STATUS

	static bool			STATUS_ENABLE;


	//#################        PROTECTION

	static bool			PROTECTION_SHOW_WHISPER_LOGS_ENABLE;
	static bool			PROTECTION_SHOW_WHISPER_BALLOON_ENABLE;
	static bool			PROTECTION_SHOW_TALK_BALLOON_ENABLE;
	static bool			PROTECTION_PLAY_WHISPER_BEEP_ENABLE;;
	static bool			PROTECTION_PLAY_TALK_BEEP_ENABLE;
	static bool			PROTECTION_FLASH_TALK_ICON_ENABLE;
	static bool			PROTECTION_SHOW_TALK_LOGS_ENABLE;
	static bool			PROTECTION_RESTORE_WISPER_WINDOW_ENABLE;;
	static bool			PROTECTION_FLASH_WHISPER_ICON_ENABLE;
	static bool			PROTECTION_DISABLE_RENDER_ENABLE;
	static bool			PROTECTION_DISABLE_UPDATE_ENABLE;
	static bool			PROTECTION_DISABLE_RENDER_FRAMES_ENABLE;
	static bool			PROTECTION_AUTO_LOGIN_ENABLE;

	//#################        RADAR

	static ImVec4		RADAR_MONSTER_COLOR;
	static ImVec4		RADAR_BOSS_COLOR;
	static ImVec4		RADAR_NPC_COLOR;
	static ImVec4		RADAR_MINE_COLOR;
	static ImVec4		RADAR_STONE_COLOR;
	static ImVec4		RADAR_PLAYER_COLOR;
	static ImVec4		RADAR_WAYPOINT_COLOR;
	static bool			RADAR_MONSTER_SHOW_ENABLE;
	static bool			RADAR_BOSS_SHOW_ENABLE;
	static bool			RADAR_NPC_SHOW_ENABLE;
	static bool			RADAR_MINING_SHOW_ENABLE;
	static bool			RADAR_STONE_SHOW_ENABLE;
	static bool			RADAR_PLAYER_SHOW_ENABLE;
	static bool			RADAR_WAYPOINT_SHOW_ENABLE;
	static float		RADAR_ZOOM;

	//#################        OTHER

	static bool			GLOBAL_SWITCH_ENABLE;
	static bool			DUNGEON_BOT_ENABLE;
	static int			DUNGEON_TYPE;

	static DWORD		INVENTORY_PAGE_SIZE;
	static DWORD		INVENTORY_PAGE_COUNT;
	
	
};
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

map< pair<DWORD, pair<string, string>>, pair<DWORD, string>> Settings::SERVER_INFO_LIST_GLOBAL =
{
	{ make_pair(1,  make_pair("Amicicia","CH1")), make_pair(12100, "79.110.92.173") },
	{ make_pair(2,  make_pair("Amicicia","CH2")), make_pair(12200, "79.110.92.176") },
	{ make_pair(3,  make_pair("Amicicia","CH3")), make_pair(12300, "79.110.92.181") },
	{ make_pair(4,  make_pair("Amicicia","CH4")), make_pair(12400, "79.110.92.173") },
	{ make_pair(5,  make_pair("Amicicia","CH5")), make_pair(12500, "79.110.92.176") },
	{ make_pair(6,  make_pair("Amicicia","CH6")), make_pair(12600, "79.110.92.181") },
	{ make_pair(7,  make_pair("Amicicia","CH7")), make_pair(12700, "79.110.92.173") },
	{ make_pair(8,  make_pair("Amicicia","CH8")), make_pair(12800, "79.110.92.176") },
	{ make_pair(9,  make_pair("Amicicia","CH9")), make_pair(12900, "79.110.92.181") },

	{ make_pair(10,  make_pair("Carptura","CH1")), make_pair(12100, "79.110.92.187") },
	{ make_pair(11,  make_pair("Carptura","CH2")), make_pair(12200, "79.110.92.189") },
	{ make_pair(12,  make_pair("Carptura","CH3")), make_pair(12300, "79.110.92.190") },
	{ make_pair(13,  make_pair("Carptura","CH4")), make_pair(12400, "79.110.92.187") },
	{ make_pair(14,  make_pair("Carptura","CH5")), make_pair(12500, "79.110.92.189") },
	{ make_pair(15,  make_pair("Carptura","CH6")), make_pair(12600, "79.110.92.190") },
	{ make_pair(16,  make_pair("Carptura","CH7")), make_pair(12700, "79.110.92.187") },
	{ make_pair(17,  make_pair("Carptura","CH8")), make_pair(12800, "79.110.92.189") },
	{ make_pair(18,  make_pair("Carptura","CH9")), make_pair(12900, "79.110.92.190") },

	{ make_pair(19,  make_pair("Polyphemos","CH1")), make_pair(12100, "79.110.92.201") },
	{ make_pair(20,  make_pair("Polyphemos","CH2")), make_pair(12200, "79.110.92.229") },
	{ make_pair(21,  make_pair("Polyphemos","CH3")), make_pair(12300, "79.110.92.201") },
	{ make_pair(22,  make_pair("Polyphemos","CH4")), make_pair(12400, "79.110.92.229") },
	{ make_pair(23,  make_pair("Polyphemos","CH5")), make_pair(12500, "79.110.92.201") },
	{ make_pair(24,  make_pair("Polyphemos","CH6")), make_pair(12600, "79.110.92.229") },
	{ make_pair(25,  make_pair("Polyphemos","CH7")), make_pair(12700, "79.110.92.126") },
	{ make_pair(26,  make_pair("Polyphemos","CH8")), make_pair(12800, "79.110.92.126") },
	{ make_pair(27,  make_pair("Polyphemos","CH9")), make_pair(12900, "79.110.92.126") },


	{ make_pair(28,  make_pair("Tigerghost","CH1")), make_pair(12100, "79.110.92.207") },
	{ make_pair(29,  make_pair("Tigerghost","CH2")), make_pair(12200, "79.110.92.127") },
	{ make_pair(30,  make_pair("Tigerghost","CH3")), make_pair(12300, "79.110.92.207") },
	{ make_pair(31,  make_pair("Tigerghost","CH4")), make_pair(12400, "79.110.92.127") },
	{ make_pair(32,  make_pair("Tigerghost","CH5")), make_pair(12500, "79.110.92.207") },
	{ make_pair(33,  make_pair("Tigerghost","CH6")), make_pair(12600, "79.110.92.127") },

	{ make_pair(34,  make_pair("Polska","CH1")), make_pair(12101, "79.110.92.116") },
	{ make_pair(35,  make_pair("Polska","CH2")), make_pair(12201, "79.110.92.117") },
	{ make_pair(36,  make_pair("Polska","CH3")), make_pair(12301, "79.110.92.116") },
	{ make_pair(37,  make_pair("Polska","CH4")), make_pair(12401, "79.110.92.117") },
	{ make_pair(38,  make_pair("Polska","CH5")), make_pair(12501, "79.110.92.116") },
	{ make_pair(39,  make_pair("Polska","CH6")), make_pair(12601, "79.110.92.117") },
	{ make_pair(40,  make_pair("Polska","CH7")), make_pair(12701, "79.110.92.172") },
	{ make_pair(41,  make_pair("Polska","CH8")), make_pair(12801, "79.110.92.172") },
	{ make_pair(42,  make_pair("Polska","CH9")), make_pair(12901, "79.110.92.172") },




	{ make_pair(43,  make_pair("Romania","CH1")), make_pair(12100, "79.110.92.75") },
	{ make_pair(44,  make_pair("Romania","CH2")), make_pair(12200, "79.110.92.199") },
	{ make_pair(45,  make_pair("Romania","CH3")), make_pair(12300, "79.110.92.75") },
	{ make_pair(46,  make_pair("Romania","CH4")), make_pair(12400, "79.110.92.199") },
	{ make_pair(47,  make_pair("Romania","CH5")), make_pair(12500, "79.110.92.75") },
	{ make_pair(48,  make_pair("Romania","CH6")), make_pair(12600, "79.110.92.199") },
	{ make_pair(49,  make_pair("Romania","CH7")), make_pair(12700, "79.110.92.26") },
	{ make_pair(50,  make_pair("Romania","CH8")), make_pair(12800, "79.110.92.26") },
	{ make_pair(51,  make_pair("Romania","CH9")), make_pair(12900, "79.110.92.26") },




	{ make_pair(52,  make_pair("Germania","CH1")), make_pair(12100, "79.110.92.188") },
	{ make_pair(53,  make_pair("Germania","CH2")), make_pair(12200, "79.110.92.133") },
	{ make_pair(54,  make_pair("Germania","CH3")), make_pair(12300, "79.110.92.188") },
	{ make_pair(55,  make_pair("Germania","CH4")), make_pair(12400, "79.110.92.133") },
	{ make_pair(56,  make_pair("Germania","CH5")), make_pair(12500, "79.110.92.188") },
	{ make_pair(57,  make_pair("Germania","CH6")), make_pair(12600, "79.110.92.133") },
	{ make_pair(58,  make_pair("Germania","CH7")), make_pair(12700, "79.110.92.131") },
	{ make_pair(59,  make_pair("Germania","CH8")), make_pair(12800, "79.110.92.131") },
	{ make_pair(60,  make_pair("Germania","CH9")), make_pair(12900, "79.110.92.131") },




	{ make_pair(61,  make_pair("Turkiye","CH1")), make_pair(12100, "79.110.92.24") },
	{ make_pair(62,  make_pair("Turkiye","CH2")), make_pair(12200, "79.110.92.135") },
	{ make_pair(63,  make_pair("Turkiye","CH3")), make_pair(12300, "79.110.92.24") },
	{ make_pair(64,  make_pair("Turkiye","CH4")), make_pair(12400, "79.110.92.135") },
	{ make_pair(65,  make_pair("Turkiye","CH5")), make_pair(12500, "79.110.92.24") },
	{ make_pair(66,  make_pair("Turkiye","CH6")), make_pair(12600, "79.110.92.135") },
	{ make_pair(67,  make_pair("Turkiye","CH7")), make_pair(12700, "79.110.92.214") },
	{ make_pair(68,  make_pair("Turkiye","CH8")), make_pair(12800, "79.110.92.214") },
	{ make_pair(69,  make_pair("Turkiye","CH9")), make_pair(12900, "79.110.92.214") },




	{ make_pair(70,  make_pair("Italy","CH1")), make_pair(12101, "79.110.92.128") },
	{ make_pair(71,  make_pair("Italy","CH2")), make_pair(12201, "79.110.92.129") },
	{ make_pair(72,  make_pair("Italy","CH3")), make_pair(12301, "79.110.92.128") },
	{ make_pair(73,  make_pair("Italy","CH4")), make_pair(12401, "79.110.92.129") },
	{ make_pair(74,  make_pair("Italy","CH5")), make_pair(12501, "79.110.92.128") },
	{ make_pair(75,  make_pair("Italy","CH6")), make_pair(12601, "79.110.92.129") },
	{ make_pair(76,  make_pair("Italy","CH7")), make_pair(12701, "79.110.92.88") },
	{ make_pair(77,  make_pair("Italy","CH8")), make_pair(12801, "79.110.92.88") },
	{ make_pair(78,  make_pair("Italy","CH9")), make_pair(12901, "79.110.92.88") },




	{ make_pair(79,  make_pair("Azrael","CH1")), make_pair(12100, "79.110.92.191") },
	{ make_pair(80,  make_pair("Azrael","CH2")), make_pair(12200, "79.110.92.132") },
	{ make_pair(81,  make_pair("Azrael","CH3")), make_pair(12300, "79.110.92.191") },
	{ make_pair(82,  make_pair("Azrael","CH4")), make_pair(12400, "79.110.92.132") },
	{ make_pair(83,  make_pair("Azrael","CH5")), make_pair(12500, "79.110.92.191") },
	{ make_pair(84,  make_pair("Azrael","CH6")), make_pair(12600, "79.110.92.132") },
	{ make_pair(85,  make_pair("Azrael","CH7")), make_pair(12700, "79.110.92.123") },
	{ make_pair(86,  make_pair("Azrael","CH8")), make_pair(12800, "79.110.92.123") },
	{ make_pair(87,  make_pair("Azrael","CH9")), make_pair(12900, "79.110.92.123") },




	{ make_pair(88,  make_pair("Sodalitas","CH1")), make_pair(12100, "79.110.92.182") },
	{ make_pair(89,  make_pair("Sodalitas","CH2")), make_pair(12200, "79.110.92.183") },
	{ make_pair(90,  make_pair("Sodalitas","CH3")), make_pair(12300, "79.110.92.184") },
	{ make_pair(91,  make_pair("Sodalitas","CH4")), make_pair(12400, "79.110.92.182") },
	{ make_pair(92,  make_pair("Sodalitas","CH5")), make_pair(12500, "79.110.92.183") },
	{ make_pair(93,  make_pair("Sodalitas","CH6")), make_pair(12600, "79.110.92.184") },
	{ make_pair(94,  make_pair("Sodalitas","CH7")), make_pair(12700, "79.110.92.182") },
	{ make_pair(95,  make_pair("Sodalitas","CH8")), make_pair(12800, "79.110.92.183") },
	{ make_pair(96,  make_pair("Sodalitas","CH9")), make_pair(12900, "79.110.92.184") },




	{ make_pair(97,  make_pair("Europe","CH1")), make_pair(12100, "79.110.92.136") },
	{ make_pair(98,  make_pair("Europe","CH2")), make_pair(12200, "79.110.92.224") },
	{ make_pair(99,  make_pair("Europe","CH3")), make_pair(12300, "79.110.92.136") },
	{ make_pair(100,  make_pair("Europe","CH4")), make_pair(12400, "79.110.92.224") },
	{ make_pair(101,  make_pair("Europe","CH5")), make_pair(12500, "79.110.92.136") },




	{ make_pair(102,  make_pair("Anima","CH1")), make_pair(12100, "79.110.92.179") },
	{ make_pair(103,  make_pair("Anima","CH2")), make_pair(12200, "79.110.92.180") },
	{ make_pair(104,  make_pair("Anima","CH3")), make_pair(12300, "79.110.92.179") },
	{ make_pair(105,  make_pair("Anima","CH4")), make_pair(12400, "79.110.92.180") },
	{ make_pair(106,  make_pair("Anima","CH5")), make_pair(12500, "79.110.92.179") },
	{ make_pair(107,  make_pair("Anima","CH6")), make_pair(12600, "79.110.92.180") },
	{ make_pair(108,  make_pair("Anima","CH7")), make_pair(12700, "79.110.92.89") },
};
map< pair<DWORD, pair<DWORD, string>>, pair<DWORD, string>> Settings::SERVER_INFO_LIST =
{
	{ make_pair(1,  make_pair(ServerName::VIDGAR,"CH1")), make_pair(60106, "137.74.5.73") },
	{ make_pair(2,  make_pair(ServerName::VIDGAR,"CH2")), make_pair(60206, "137.74.5.73") },
	{ make_pair(3,  make_pair(ServerName::VIDGAR,"CH3")), make_pair(60306, "137.74.5.73") },
	{ make_pair(4,  make_pair(ServerName::VIDGAR,"CH4")), make_pair(60406, "137.74.5.73") },
	{ make_pair(5,  make_pair(ServerName::VIDGAR,"CH5")), make_pair(60506, "137.74.5.73") },
	{ make_pair(6,  make_pair(ServerName::VIDGAR,"CH6")), make_pair(60606, "137.74.5.73") },
	{ make_pair(7,  make_pair(ServerName::VIDGAR,"CH7")), make_pair(60706, "137.74.5.73") },
	{ make_pair(8,  make_pair(ServerName::VIDGAR,"CH8")), make_pair(60806, "137.74.5.73") },

	{ make_pair(9,  make_pair(ServerName::PANGEA,"CH1")), make_pair(41000, "51.77.43.124") },
	{ make_pair(10,  make_pair(ServerName::PANGEA,"CH2")), make_pair(42000, "51.77.43.124") },
	{ make_pair(11,  make_pair(ServerName::PANGEA,"CH3")), make_pair(43000, "51.77.43.124") },
	{ make_pair(12,  make_pair(ServerName::PANGEA,"CH4")), make_pair(44000, "51.77.43.124") },
	{ make_pair(13,  make_pair(ServerName::PANGEA,"CH5")), make_pair(45000, "51.77.43.124") },
	{ make_pair(14,  make_pair(ServerName::PANGEA,"CH6")), make_pair(46000, "51.77.43.124") },

	{ make_pair(15,  make_pair(ServerName::SAMIAS2,"CH1")), make_pair(16211, "54.38.85.102") },
	{ make_pair(16,  make_pair(ServerName::SAMIAS2,"CH2")), make_pair(16221, "54.38.85.102") },
	{ make_pair(17,  make_pair(ServerName::SAMIAS2,"CH3")), make_pair(16231, "54.38.85.102") },
	{ make_pair(18,  make_pair(ServerName::SAMIAS2,"CH4")), make_pair(16241, "54.38.85.102") },
	{ make_pair(19,  make_pair(ServerName::SAMIAS2,"CH5")), make_pair(16251, "54.38.85.102") },
	{ make_pair(20,  make_pair(ServerName::SAMIAS2,"CH6")), make_pair(16261, "54.38.85.102") },

	{ make_pair(21,  make_pair(ServerName::MEDIUMMT2,"CH1")), make_pair(14001, "51.77.56.238") },
	{ make_pair(22,  make_pair(ServerName::MEDIUMMT2,"CH2")), make_pair(14002, "51.77.56.238") },
	{ make_pair(23,  make_pair(ServerName::MEDIUMMT2,"CH3")), make_pair(14003, "51.77.56.238") },
	{ make_pair(24,  make_pair(ServerName::MEDIUMMT2,"CH4")), make_pair(14004, "51.77.56.238") },
	{ make_pair(25,  make_pair(ServerName::MEDIUMMT2,"CH5")), make_pair(14005, "51.77.56.238") },
	{ make_pair(26,  make_pair(ServerName::MEDIUMMT2,"CH6")), make_pair(14006, "51.77.56.238") },


	{ make_pair(27,  make_pair(ServerName::ASENIS,"CH1")), make_pair(51102, "51.77.52.117") },
	{ make_pair(28,  make_pair(ServerName::ASENIS,"CH2")), make_pair(51202, "51.77.52.117") },
	{ make_pair(29,  make_pair(ServerName::ASENIS,"CH3")), make_pair(51302, "51.77.52.117") },
	{ make_pair(30,  make_pair(ServerName::ASENIS,"CH4")), make_pair(51402, "51.77.52.117") },
	{ make_pair(31,  make_pair(ServerName::ASENIS,"CH5")), make_pair(51502, "51.77.52.117") },
	{ make_pair(32,  make_pair(ServerName::ASENIS,"CH6")), make_pair(51602, "51.77.52.117") },

	{ make_pair(33,  make_pair(ServerName::CLASSIC,"CH1")), make_pair(13001, "51.77.56.238") },
	{ make_pair(34,  make_pair(ServerName::CLASSIC,"CH2")), make_pair(13002, "51.77.56.238") },
	{ make_pair(35,  make_pair(ServerName::CLASSIC,"CH3")), make_pair(13003, "51.77.56.238") },
	{ make_pair(36,  make_pair(ServerName::CLASSIC,"CH4")), make_pair(13004, "51.77.56.238") },
	{ make_pair(37,  make_pair(ServerName::CLASSIC,"CH5")), make_pair(13005, "51.77.56.238") },
	{ make_pair(38,  make_pair(ServerName::CLASSIC,"CH6")), make_pair(13006, "51.77.56.238") },



	{ make_pair(39,  make_pair(ServerName::DEVERIA,"CH1")), make_pair(17010, "87.98.237.48") },
	{ make_pair(40,  make_pair(ServerName::DEVERIA,"CH2")), make_pair(17020, "87.98.237.48") },
	{ make_pair(41,  make_pair(ServerName::DEVERIA,"CH3")), make_pair(17030, "87.98.237.48") },
	{ make_pair(42,  make_pair(ServerName::DEVERIA,"CH4")), make_pair(17040, "87.98.237.48") },
	{ make_pair(43,  make_pair(ServerName::DEVERIA,"CH5")), make_pair(17050, "87.98.237.48") },


	{ make_pair(44,  make_pair(ServerName::WOM,"CH1")), make_pair(55101, "51.83.214.65") },
	{ make_pair(45,  make_pair(ServerName::WOM,"CH2")), make_pair(55111, "51.83.214.65") },
	{ make_pair(46,  make_pair(ServerName::WOM,"CH3")), make_pair(55121, "51.83.214.65") },
	{ make_pair(47,  make_pair(ServerName::WOM,"CH4")), make_pair(55131, "51.83.214.65") },
	{ make_pair(48,  make_pair(ServerName::WOM,"CH5")), make_pair(55141, "51.83.214.65") },

	{ make_pair(49,  make_pair(ServerName::AELDRA,"CH1")), make_pair(20014, "51.83.223.169") },
	{ make_pair(50,  make_pair(ServerName::AELDRA,"CH2")), make_pair(20024, "51.83.223.169") },
	{ make_pair(51,  make_pair(ServerName::AELDRA,"CH3")), make_pair(20034, "51.83.223.169") },
	{ make_pair(52,  make_pair(ServerName::AELDRA,"CH4")), make_pair(20044, "51.83.223.169") },
	{ make_pair(53,  make_pair(ServerName::AELDRA,"CH5")), make_pair(20054, "51.83.223.169") },
	{ make_pair(54,  make_pair(ServerName::AELDRA,"CH6")), make_pair(20064, "51.83.223.169") },
	{ make_pair(55,  make_pair(ServerName::AELDRA,"CH7")), make_pair(20074, "51.83.223.169") },

	{ make_pair(56,  make_pair(ServerName::KEVRA,"CH1")), make_pair(30002, "54.38.85.102") },
	{ make_pair(57,  make_pair(ServerName::KEVRA,"CH2")), make_pair(30012, "54.38.85.102") },
	{ make_pair(58,  make_pair(ServerName::KEVRA,"CH3")), make_pair(30022, "54.38.85.102") },
	{ make_pair(59,  make_pair(ServerName::KEVRA,"CH4")), make_pair(30032, "54.38.85.102") },
	{ make_pair(60,  make_pair(ServerName::KEVRA,"CH5")), make_pair(30042, "54.38.85.102") },
	{ make_pair(61,  make_pair(ServerName::KEVRA,"CH6")), make_pair(30052, "54.38.85.102") },
	{ make_pair(62,  make_pair(ServerName::KEVRA,"CH7")), make_pair(30062, "54.38.85.102") },
	{ make_pair(63,  make_pair(ServerName::KEVRA,"CH8")), make_pair(30072, "54.38.85.102") },
};
vector<string>												Settings::PROTECTION_DETECT_PLAYER_WHITE_LIST =
{
	{""}
};

map< pair<DWORD, bool>, pair<DWORD, string>>				Settings::FISH_KILL_FISH_LIST =
{
	{ make_pair(0, false), make_pair(27987, "Małż") },
	{ make_pair(1, true), make_pair(27803, "Karaś")},	
	{ make_pair(2, true), make_pair(27804, "Ryba Mandaryna")},
	{ make_pair(3, true), make_pair(27805, "Duży Karaś")},
	{ make_pair(4, true), make_pair(27806, "Karp")},
	{ make_pair(5, true), make_pair(27807, "Losoś")},
	{ make_pair(6, true), make_pair(27808, "Amur")},
	{ make_pair(7, true), make_pair(27809, "Pstrag")},
	{ make_pair(8, true), make_pair(27810, "Węgorz")},
	{ make_pair(9, true), make_pair(27811, "Teczowy Pstrąg")},
	{ make_pair(10, true), make_pair(27812, "Rzeczny Pstrąg")},
	{ make_pair(11, true), make_pair(27813, "Krasnopiórka")},
	{ make_pair(12, true), make_pair(27814, "Okoń")},
	{ make_pair(13, true), make_pair(27815, "Tenchi")},
	{ make_pair(14, true), make_pair(27816, "Sum")},
	{ make_pair(15, true), make_pair(27817, "Piskorz")},
	{ make_pair(16, true), make_pair(27818, "Ryba Lotosu")},
	{ make_pair(17, true), make_pair(27819, "Słodka Ryba")},
	{ make_pair(18, true), make_pair(27820, "Gromadnik")},
	{ make_pair(19, true), make_pair(27821, "Shiri")},
	{ make_pair(20, true), make_pair(27822, "Lustrzany Karp")},
	{ make_pair(21, true), make_pair(27823, "Złoty Karał")},
};

map<DWORD, pair<DWORD, DWORD>>				Settings::FISH_ROD_REFINE_POINTS =
{
	{27400, make_pair(1, 10)},
	{27410, make_pair(2, 20)},
	{27420, make_pair(3, 40)},
	{27430, make_pair(4, 80)},
	{27440, make_pair(5, 120)},
	{27450, make_pair(6, 140)},
	{27460, make_pair(7, 160)},
	{27470, make_pair(8, 180)},
	{27480, make_pair(9, 200)},
	{27490, make_pair(10, 220)},
	{27510, make_pair(11, 240)},
	{27520, make_pair(12, 260)},
	{27530, make_pair(13, 280)},
	{27540, make_pair(14, 300)},
	{27550, make_pair(15, 320)},
	{27560, make_pair(16, 340)},
	{27570, make_pair(17, 360)},
	{27580, make_pair(18, 380)},
	{27590, make_pair(19, 400)},
	{27600, make_pair(20, 420)},
};
//##########################################################################################
map< pair<DWORD, bool>, pair<DWORD, string>>				Settings::FISH_BAIT_LIST =
{
	{ make_pair(2, true), make_pair(27802, "Drobne Ryby")},
	{ make_pair(3, true), make_pair(27801, "Robak")},
	{ make_pair(4, true), make_pair(27800, "Papka")},

};
map< pair<DWORD, bool>, pair<DWORD, string>>				Settings::FISH_DROP_LIST =
{

	{ make_pair(1, false), make_pair(50002, "Złoty Pierścień") },
	{ make_pair(2, false), make_pair(70201, "Wybielacz") },
	{ make_pair(3, false), make_pair(70202, "Biała Farba Do Włosów") },
	{ make_pair(4, false), make_pair(70203, "Blond Farba Do Włosów") },
	{ make_pair(5, false), make_pair(70204, "Czerw.Farba Do Włosów") },
	{ make_pair(6, false), make_pair(70205, "Brązowa Farba Do Włosów") },
	{ make_pair(7, false), make_pair(70206, "Czarna Farba Do Włosów") },

	{ make_pair(8, false), make_pair(50043, "Klucz Nimfy Wodnej") },
	{ make_pair(9, false), make_pair(70050, "Symb. Króla Przepowiedni") },
	{ make_pair(10, false), make_pair(70048, "Peleryna Maskująca") },
	{ make_pair(11, false), make_pair(50009, "Srebny Klucz") },


	{ make_pair(12, false), make_pair(50008, "Złoty Klucz") },
	{ make_pair(13, false), make_pair(70049, "Pierścień Lucy") },
	{ make_pair(14, false), make_pair(70051, "Rękawica Króla Przepowiedni") },

	{ make_pair(16, false), make_pair(80008, "Bryła Złota") },
	{ make_pair(17, false), make_pair(27799, "Rybia Ość") },
	{ make_pair(18, false), make_pair(27990, "Kawałek Kamienia") },
	{ make_pair(19, false), make_pair(27987, "Małż") },
	{ make_pair(20, false), make_pair(27833, "Martwy Karaś") },
	{ make_pair(21, false), make_pair(27834, "Martwa Ryba Mandaryna") },
	{ make_pair(22, false), make_pair(27835, "Martwy Duży Karś") },
	{ make_pair(23, false), make_pair(27836, "Martwy Karp") },
	{ make_pair(24, false), make_pair(27837, "Martwy Łosoś") },

	{ make_pair(26, false), make_pair(27838, "Martwy Amur") },
	{ make_pair(27, false), make_pair(27839, "Martwy Pstrąg") },
	{ make_pair(28, false), make_pair(27840, "Martwy Węgorz") },
	{ make_pair(29, false), make_pair(27841, "Martwy Tęczowy Pstrąg") },
	{ make_pair(30, false), make_pair(27842, "Martwy Rzeczny Pstrąg") },
	{ make_pair(31, false), make_pair(27843, "Martwa Krasnopiórka") },
	{ make_pair(32, false), make_pair(27844, "Martwy Okoń") },
	{ make_pair(33, false), make_pair(27845, "Martwa Tenchi") },
	{ make_pair(34, false), make_pair(27846, "Martwy Sum") },
	{ make_pair(35, false), make_pair(27847, "Martwy Piskorz") },
	{ make_pair(36, false), make_pair(27848, "Martwa Ryba Lotosu") },
	{ make_pair(37, false), make_pair(27849, "Martwa Słodka Ryba") },
	{ make_pair(38, false), make_pair(27850, "Martwy Gromadnik") },
	{ make_pair(39, false), make_pair(27851, "Martwa Shiri") },
	{ make_pair(40, false), make_pair(27852, "Martwy Lustrzany Karp") },
	{ make_pair(41, false), make_pair(27853, "Martwy Złoty Karaś") },
};
map< pair<DWORD, bool>, pair<DWORD, string>>				Settings::FISH_SELL_LIST =
{

	{ make_pair(1, true), make_pair(50002, "Złoty Pierścień") },
	{ make_pair(2, true), make_pair(70201, "Wybielacz") },
	{ make_pair(3, true), make_pair(70202, "Biała Farba Do Włosów") },
	{ make_pair(4, true), make_pair(70203, "Blond Farba Do Włosów") },
	{ make_pair(5, true), make_pair(70204, "Czerw.Farba Do Włosów") },
	{ make_pair(6, true), make_pair(70205, "Brązowa Farba Do Włosów") },
	{ make_pair(7, true), make_pair(70206, "Czarna Farba Do Włosów") },

	{ make_pair(8, true), make_pair(50043, "Klucz Nimfy Wodnej") },
	{ make_pair(9, true), make_pair(70050, "Symb. Króla Przepowiedni") },
	{ make_pair(10, true), make_pair(70048, "Peleryna Maskująca") },
	{ make_pair(11, true), make_pair(50009, "Srebny Klucz") },


	{ make_pair(12, true), make_pair(50008, "Złoty Klucz") },
	{ make_pair(13, true), make_pair(70049, "Pierścień Lucy") },
	{ make_pair(14, true), make_pair(70051, "Rękawica Króla Przepowiedni") },

	{ make_pair(16, true), make_pair(80008, "Bryła Złota") },
	{ make_pair(17, true), make_pair(27799, "Rybia Ość") },
	{ make_pair(18, true), make_pair(27990, "Kawałek Kamienia") },
	{ make_pair(19, false), make_pair(27987, "Małż") },
	{ make_pair(20, true), make_pair(27833, "Martwy Karaś") },
	{ make_pair(21, true), make_pair(27834, "Martwa Ryba Mandaryna") },
	{ make_pair(22, true), make_pair(27835, "Martwy Duży Karś") },
	{ make_pair(23, true), make_pair(27836, "Martwy Karp") },

	{ make_pair(25, true), make_pair(27837, "Martwy Łosoś") },
	{ make_pair(26, true), make_pair(27838, "Martwy Amur") },
	{ make_pair(27, true), make_pair(27839, "Martwy Pstrąg") },
	{ make_pair(28, true), make_pair(27840, "Martwy Węgorz") },
	{ make_pair(29, true), make_pair(27841, "Martwy Tęczowy Pstrąg") },
	{ make_pair(30, true), make_pair(27842, "Martwy Rzeczny Pstrąg") },
	{ make_pair(31, true), make_pair(27843, "Martwa Krasnopiórka") },
	{ make_pair(32, true), make_pair(27844, "Martwy Okoń") },
	{ make_pair(33, true), make_pair(27845, "Martwa Tenchi") },
	{ make_pair(34, true), make_pair(27846, "Martwy Sum") },
	{ make_pair(35, true), make_pair(27847, "Martwy Piskorz") },
	{ make_pair(36, true), make_pair(27848, "Martwa Ryba Lotosu") },
	{ make_pair(37, true), make_pair(27849, "Martwa Słodka Ryba") },
	{ make_pair(38, false), make_pair(27850, "Martwy Gromadnik") },
	{ make_pair(39, true), make_pair(27851, "Martwa Shiri") },
	{ make_pair(40, true), make_pair(27852, "Martwy Lustrzany Karp") },
	{ make_pair(41, true), make_pair(27853, "Martwy Złoty Karaś") },
};
map<DWORD, pair<string, DWORD>>								Settings::FISH_COMMAND_LIST
{
	// { 6, make_pair("Nacisnij 1 razy spacje", 1) },
	// { 7, make_pair("Nacisnij 2 razy spacje", 2) },
	// { 8, make_pair("Nacisnij 3 razy spacje", 3) },
	// { 9, make_pair("Nacisnij 4 razy spacje", 4) },
	// { 10, make_pair("Nacisnij 5 razy spacje", 5) },
	// { 11, make_pair("Naciśnij 1 razy", 1) },
	// { 12, make_pair("Naciśnij 2 razy", 2) },
	// { 13, make_pair("Naciśnij 3 razy", 3) },
	// { 14, make_pair("Naciśnij 4 razy", 4) },
	// { 15, make_pair("Naciśnij 5 razy", 5) },
	// { 16, make_pair("Kliknij 1 razy", 1) },
	// { 17, make_pair("Kliknij 2 razy", 2) },
	// { 18, make_pair("Kliknij 3 razy", 3) },
	// { 19, make_pair("Kliknij 4 razy", 4) },
	// { 20, make_pair("Kliknij 5 razy", 5) },
	// { 21, make_pair("ile jest niebieskich kulek (1)", 1) },
	// { 22, make_pair("ile jest niebieskich kulek (2)", 2) },
	// { 23, make_pair("ile jest niebieskich kulek (3)", 3) },
	// { 24, make_pair("ile jest niebieskich kulek (4)", 4) },
	// { 25, make_pair("ile jest niebieskich kulek (5)", 5) },
	// { 26, make_pair("Kliknij 1 razy spację, aby spróbować wyłowić rybę", 1) },
	// { 27, make_pair("Kliknij 2 razy spację, aby spróbować wyłowić rybę", 2) },
	// { 28, make_pair("Kliknij 3 razy spację, aby spróbować wyłowić rybę", 3) },
	// { 29, make_pair("Kliknij 4 razy spację, aby spróbować wyłowić rybę", 4) },
	// { 30, make_pair("Kliknij 5 razy spację, aby spróbować wyłowic rybę", 5) },
	// { 31, make_pair("1x|h|r aby wyłowić", 1) },
	// { 32, make_pair("2x|h|r aby wyłowić", 2) },
	// { 33, make_pair("3x|h|r aby wyłowić", 3) },
	// { 34, make_pair("4x|h|r aby wyłowić", 4) },
	// { 35, make_pair("5x|h|r aby wyłowić", 5) },
	// { 36, make_pair("Zatnij rybę 1 razy", 1) },
	// { 37, make_pair("Zatnij rybę 2 razy", 2) },
	// { 38, make_pair("Zatnij rybę 3 razy", 3) },
	// { 39, make_pair("Zatnij rybę 4 razy", 4) },
	// { 40, make_pair("Zatnij rybę 5 razy", 5) },
	// { 41, make_pair("Wylosowano: 1", 1) },
	// { 42, make_pair("Wylosowano: 2", 2) },
	// { 43, make_pair("Wylosowano: 3", 3) },
	// { 44, make_pair("Wylosowano: 4", 4) },
	// { 45, make_pair("Wylosowano: 5", 5) },
	// { 46, make_pair("liczba to... 1", 1) },
	// { 47, make_pair("liczba to... 2", 2) },
	// { 48, make_pair("liczba to... 3", 3) },
	// { 49, make_pair("liczba to... 4", 4) },
	// { 50, make_pair("liczba to... 5", 5) },
	// { 51, make_pair("użyj spacji 1", 1) },
	// { 52, make_pair("użyj spacji 2", 2) },
	// { 53, make_pair("użyj spacji 3", 3) },
	// { 54, make_pair("użyj spacji 4", 4) },
	// { 55, make_pair("użyj spacji 5", 5) },
	 { 56, make_pair("nij: 1", 1) },
	 { 57, make_pair("nij: 2", 2) },
	 { 58, make_pair("nij: 3", 3) },
	 { 59, make_pair("nij: 4", 4) },
	 { 60, make_pair("nij: 5", 5) },

	 { 61, make_pair("nij: J", 1) },
	 { 62, make_pair("nij: D", 2) },
	 { 63, make_pair("nij: T", 3) },
	 { 64, make_pair("nij: C", 4) },
	 { 65, make_pair("nij: P", 5) },
	//{ 66, make_pair("hohfcthbhy.sub", 1) },
	//{ 67, make_pair("klnbahqfuk.sub", 1) },
	//{ 68, make_pair("zqsdlotxlt.sub", 1) },
	//{ 69, make_pair("gkxegfenjh.sub", 1) },
	//{ 70, make_pair("gulnvvwzbm.sub", 2) },
	//{ 71, make_pair("blsvtqsbdr.sub", 2) },
	//{ 72, make_pair("cfqdfqfnpl.sub", 2) },
	//{ 73, make_pair("znvtfvjjlg.sub", 2) },
	//{ 74, make_pair("addjvbzupo.sub", 3) },
	//{ 75, make_pair("wxzcbjqoau.sub", 3) },
	//{ 76, make_pair("izpjrgxwmk.sub", 3) },
	//{ 77, make_pair("ulvnibygka.sub", 3) },
	// { 78, make_pair("mdscnufuca.sub", 4) },
	// { 79, make_pair("egyfkgjofh.sub", 4) },
	// { 80, make_pair("volexihnrf.sub", 4) },
	// { 81, make_pair("okgeihgbod.sub", 4) },
	// { 82, make_pair("mbiuatlxoc.sub", 5) },
	// { 83, make_pair("aehpjaevyo.sub", 5) },
	// { 84, make_pair("hmmngdctvb.sub", 5) },
	// { 85, make_pair("frwikxzsrn.sub", 5) },
	 { 86, make_pair("piscis_unum.mse", 1) },
	 { 87, make_pair("piscis_duo.mse", 2) },
	 { 88, make_pair("piscis_tribus.mse", 3) },
	 { 89, make_pair("piscis_quattuor.mse", 4) },
	 { 90, make_pair("piscis_quinque.mse", 5) },

	 { 91, make_pair("nij 1 raz/y przycisk spacji by wy", 1) },
	 { 92, make_pair("nij 2 raz/y przycisk spacji by wy", 2) },
	 { 93, make_pair("nij 3 raz/y przycisk spacji by wy", 3) },
	 { 94, make_pair("nij 4 raz/y przycisk spacji by wy", 4) },
	 { 95, make_pair("nij 5 raz/y przycisk spacji by wy", 5) },
	 { 96, make_pair("nij 1x spacj", 1) },
	 { 97, make_pair("nij 2x spacj", 2) },
	 { 98, make_pair("nij 3x spacj", 3) },
	 { 99, make_pair("nij 4x spacj", 4) },
	 { 100, make_pair("nij 5x spacj", 5) },
	 { 101, make_pair("nij 1x spacj", 1) },
	 { 102, make_pair("nij 2x spacj", 2) },
	 { 103, make_pair("nij 3x spacj", 3) },
	 { 104, make_pair("nij 4x spacj", 4) },
	 { 105, make_pair("nij 5x spacj", 5) },
	 { 106, make_pair("nawalaj w te spacje 1 razy", 1) },
	 { 107, make_pair("nawalaj w te spacje 2 razy", 2) },
	 { 108, make_pair("nawalaj w te spacje 3 razy", 3) },
	 { 109, make_pair("nawalaj w te spacje 4 razy", 4) },
	 { 110, make_pair("nawalaj w te spacje 5 razy", 5) },


	 { 111, make_pair("|cFF68BB411x|h|r aby", 1) },
	 { 112, make_pair("|cFF68BB412x|h|r aby", 2) },
	 { 113, make_pair("|cFF68BB413x|h|r aby", 3) },
	 { 114, make_pair("|cFF68BB414x|h|r aby", 4) },
	 { 115, make_pair("|cFF68BB415x|h|r aby", 5) },
 };
map< DWORD, pair<string, bool>>								Settings::ITEM_PICKUP_SELECTED_LIST;

vector<D3DVECTOR> Settings::cordsMaps;
//#################        MAIN

 bool		Settings::MAIN_STONE_DETECT_ENABLE = false;
 bool		Settings::MAIN_MOBBER_ENABLE = false;
 bool		Settings::MAIN_ATTACK_ENABLE = false;
 bool		Settings::MAIN_ROTATION_ENABLE = false;
 int		Settings::MAIN_ROTATION_SPEED_VALUE = 30;
 bool		Settings::MAIN_SKILL_ENABLE = false;
 bool		Settings::MAIN_NOK_ENABLE = false;
 bool		Settings::MAIN_NOP_ENABLE = false;
 bool		Settings::MAIN_WALL_MOB_ENABLE = false;
 bool		Settings::MAIN_WALL_OBJECT_ENABLE = false;
 bool		Settings::MAIN_WALL_TERRAIN_ENABLE = false;
 bool		Settings::MAIN_MOB_DETECT_ENABLE = false;
 bool		Settings::MAIN_POTION_ENABLE = false;
 bool		Settings::MAIN_RED_POTION_ENABLE = false;
 bool		Settings::MAIN_BLUE_POTION_ENABLE = false;
 int		Settings::MAIN_RED_POTION_PERCENTAGE_VALUE = 80;
 int		Settings::MAIN_RED_POTION_SPEED_VALUE = 100;
 int		Settings::MAIN_BLUE_POTION_PERCENTAGE_VALUE = 80;
 int		Settings::MAIN_BLUE_POTION_SPEED_VALUE = 100;
 bool		Settings::MAIN_AUTO_REVIVE_ENABLE = false;
 int		Settings::MAIN_AUTO_REVIVE_PERCENTAGE_VALUE = 60;
 int		Settings::MAIN_CHANNEL_CHANGER_PORT_OFFSET = 0;
 bool		Settings::MAIN_SKILL_1_ENABLE = false;
 bool		Settings::MAIN_SKILL_2_ENABLE = false;
 bool		Settings::MAIN_SKILL_3_ENABLE = false;
 bool		Settings::MAIN_SKILL_4_ENABLE = false;
 bool		Settings::MAIN_SKILL_5_ENABLE = false;
 bool		Settings::MAIN_SKILL_6_ENABLE = false;
 bool		Settings::MAIN_WH_ENABLE = false;
 int		Settings::MAIN_WH_DISTANCE_VALUE = 3000;
 int		Settings::MAIN_WH_DISTANCE_STEP = 1000;
 int		Settings::MAIN_WH_WEAPON_TYPE = 0;
 int		Settings::MAIN_WH_SKILL_COOLDOWN_TIME = 25;
 bool		Settings::MAIN_WAITHACK_RANGE_ENABLE = false;
 int		Settings::MAIN_WH_TIME = 50;
 int		Settings::MAIN_WH_ATTACK_TYPE = 0;
 bool		Settings::MAIN_WH_DETECT_PLAYER_ENABLE = false;
 int		Settings::MAIN_BOOST_KEY = VK_SHIFT;
 int		Settings::MAIN_RELOG_KEY = VK_F11;
 int		Settings::MAIN_GLOBAL_SWITCH_KEY = VK_F1;
 int		Settings::MAIN_HIDE_UI_KEY = VK_F12;
 int		Settings::MAIN_WH_SKILL_VALUE = 35;
 bool		Settings::MAIN_WH_MONSTER = true;
 bool		Settings::MAIN_WH_METIN = true;
 bool		Settings::MAIN_WH_BOSS = true;
 bool		Settings::MAIN_WH_PLAYER = false;
 int		Settings::MAIN_BOOST_SPEED = 47;
 ImVec4		Settings::MAIN_WH_RENDER_COLOR = ImColor(255, 0, 0, 255);
 bool		Settings::MAIN_WH_RENDER_ENABLE = false;

//#################        ITEM

 bool		Settings::ITEM_SLOT_RANDOM_ENABLE = true;
 bool		Settings::ITEM_SLOT_3_ENABLE = false;
 bool		Settings::ITEM_SLOT_4_ENABLE = false;
 bool		Settings::ITEM_SLOT_5_ENABLE = false;
 bool		Settings::ITEM_SLOT_6_ENABLE = false;
 bool		Settings::ITEM_SLOT_7_ENABLE = false;
 bool		Settings::ITEM_SLOT_8_ENABLE = false;
 bool		Settings::ITEM_SLOT_9_ENABLE = false;
 bool		Settings::ITEM_SLOT_10_ENABLE = false;
 bool		Settings::ITEM_SLOT_11_ENABLE = false;
 bool		Settings::ITEM_SLOT_12_ENABLE = false;
 bool		Settings::ITEM_SLOT_13_ENABLE = false;
 bool		Settings::ITEM_SLOT_14_ENABLE = false;
 bool		Settings::ITEM_SLOT_15_ENABLE = false;
 bool		Settings::ITEM_SLOT_16_ENABLE = false;
 float		Settings::ITEM_SLOT_RANDOM_MIN_TIME = 0.050;
 float		Settings::ITEM_SLOT_RANDOM_MAX_TIME = 0.100;
 float		Settings::ITEM_SLOT_3_TIME = 1.500;
 float		Settings::ITEM_SLOT_4_TIME = 1.500;
 float		Settings::ITEM_SLOT_5_TIME = 1.500;
 float		Settings::ITEM_SLOT_6_TIME = 1.500;
 float		Settings::ITEM_SLOT_7_TIME = 1.500;
 float		Settings::ITEM_SLOT_8_TIME = 1.500;
 float		Settings::ITEM_SLOT_9_TIME = 1.500;
 float		Settings::ITEM_SLOT_10_TIME = 1.500;
 float		Settings::ITEM_SLOT_11_TIME = 1.500;
 float		Settings::ITEM_SLOT_12_TIME = 1.500;
 float		Settings::ITEM_SLOT_13_TIME = 1.500;
 float		Settings::ITEM_SLOT_14_TIME = 1.500;
 float		Settings::ITEM_SLOT_15_TIME = 1.500;
 float		Settings::ITEM_SLOT_16_TIME = 1.500;
 bool		Settings::ITEM_PICKUP_ENABLE = false;
 bool		Settings::ITEM_PICKUP_FILTER_ENABLE = false;
 int		Settings::ITEM_PICKUP_TIME = 900;
 int		Settings::ITEM_PICKUP_DISTANCE = 5000;
 int		Settings::ITEM_PICKUP_STEP = 1500;
 int		Settings::ITEM_PICKUP_TYPE = 0;


//#################       FARM

bool		Settings::FARM_ENABLE = false;
bool		Settings::FARM_MOB_ENABLE = false;
bool		Settings::FARM_BOSS_ENABLE = false;
bool		Settings::FARM_METIN_ENABLE = true;
bool		Settings::FARM_MINE_ENABLE = false;
bool		Settings::FARM_PLANT_ENABLE = false;
int			Settings::FARM_DISTANCE = 3000;
float		Settings::FARM_DROP_WAIT_DELAY = 7.0;
int			Settings::FARM_MOVE_TYPE = 0;
bool		Settings::FARM_RENDER_PATH_ENABLE = false;

//#################        SPAM

bool		Settings::SPAM_NORMAL_ENABLE = false;
bool		Settings::SPAM_SHOUT_ENABLE = false;
bool		Settings::SPAM_WISPER_ENABLE = false;
float		Settings::SPAM_NORMAL_TIME = 5.0;
float		Settings::SPAM_WHISPER_TIME = 0.500;
float		Settings::SPAM_SHOUT_TIME = 7.0;
ImVec4		Settings::SPAM_NORMAL_COLOR = ImColor(255, 0, 102);
ImVec4		Settings::SPAM_WHISPER_COLOR = ImColor(255, 0, 102);
ImVec4		Settings::SPAM_SHOUT_COLOR = ImColor(255, 0, 102);
bool		Settings::SPAM_NORMAL_COLOR_ENABLE = false;
bool		Settings::SPAM_WHISPER_COLOR_ENABLE = false;
bool		Settings::SPAM_SHOUT_COLOR_ENABLE = false;
bool		Settings::SPAM_NORMAL_RAINBOW_COLOR_ENABLE = false;
bool		Settings::SPAM_WHISPER_RAINBOW_COLOR_ENABLE = false;
bool		Settings::SPAM_SHOUT_RAINBOW_COLOR_ENABLE = false;

//#################        STATUS

bool		Settings::STATUS_ENABLE = false;

//#################        BUFF

bool		Settings::BUFF_ENABLE = false;
bool		Settings::BUFF_SKILL_1_ENABLE = false;
bool		Settings::BUFF_SKILL_2_ENABLE = false;
bool		Settings::BUFF_SKILL_3_ENABLE = false;
float		Settings::BUFF_SKILL_1_TIME = 11.0;
float		Settings::BUFF_SKILL_2_TIME = 11.0;
float		Settings::BUFF_SKILL_3_TIME = 11.0;

//#################        FISH

bool		Settings::FISH_ENABLE = false;
int			Settings::FISH_SUCCESS_PERCENTAGE_VALUE = 0;
int			Settings::FISH_CAST_TIME_MIN_VALUE = 150;
int			Settings::FISH_CAST_TIME_MAX_VALUE = 250;
int			Settings::FISH_ROUND_TIME_MIN_VALUE = 9000;
int			Settings::FISH_ROUND_TIME_MAX_VALUE = 10000;
int			Settings::FISH_EMERGENCY_RUN_TIME_VALUE = 40500;
bool		Settings::FISH_DETECT_PLAYER_ENABLE = false;
bool		Settings::FISH_STOP_IF_POSITION_CHANGED_ENABLE = false;
bool		Settings::FISH_STOP_IF_INVENTORY_FULL_ENABLE = true;
bool		Settings::FISH_USE_FIRST_SLOT_ENABLE = false;
bool		Settings::FISH_KILL_FISH_ENABLE = false;
bool		Settings::FISH_SELL_TRASH_ENABLE = false;
bool		Settings::FISH_DROP_TRASH_ENABLE = false;
int			Settings::FISH_SELL_TRASH_AFTER_PERCENTAGE = 60;
bool		Settings::FISH_BUY_BAIT_ENABLE = false;;
int			Settings::FISH_BUY_BAIT_SHOP_SLOT = 8;
int			Settings::FISH_BUY_BAIT_SHOP_COUNT = 10;
bool		Settings::FISH_SHOP_CAST_TELEPORT_ENABLE = false;
D3DVECTOR	Settings::FISH_SHOP_TELEPORT_CORDS = { 0, 0, 0 };;
D3DVECTOR	Settings::FISH_CAST_TELEPORT_CORDS = { 0, 0, 0 };;
bool		Settings::FISH_SUCCESS_PERCENTAGE_VALUE_ENABLE = false;
bool		Settings::FISH_CAST_TIME_ENABLE = true;
bool		Settings::FISH_ROUND_TIME_ENABLE = true;
bool		Settings::FISH_EMERGENCY_RUN_TIME_ENABLE = true;
bool		Settings::FISH_KILL_TILL_SIZE_ENABLE = false;
float		Settings::FISH_KILL_TILL_SIZE_VALUE = 10;
int			Settings::FISH_TELEPORT_STEP_RANGE = 1800;

//#################        PROTECTION

bool		Settings::PROTECTION_SHOW_WHISPER_LOGS_ENABLE = false;
bool		Settings::PROTECTION_SHOW_WHISPER_BALLOON_ENABLE = false;
bool		Settings::PROTECTION_SHOW_TALK_BALLOON_ENABLE = false;
bool		Settings::PROTECTION_PLAY_WHISPER_BEEP_ENABLE = false;
bool		Settings::PROTECTION_PLAY_TALK_BEEP_ENABLE = false;
bool		Settings::PROTECTION_RESTORE_WISPER_WINDOW_ENABLE = false;
bool		Settings::PROTECTION_FLASH_WHISPER_ICON_ENABLE = false;
bool		Settings::PROTECTION_FLASH_TALK_ICON_ENABLE = false;
bool		Settings::PROTECTION_SHOW_TALK_LOGS_ENABLE = false;
bool		Settings::PROTECTION_DISABLE_UPDATE_ENABLE = false;
bool		Settings::PROTECTION_DISABLE_RENDER_ENABLE = false;
bool		Settings::PROTECTION_DISABLE_RENDER_FRAMES_ENABLE = false;
bool		Settings::PROTECTION_AUTO_LOGIN_ENABLE = false;

//#################        RADAR

ImVec4		Settings::RADAR_MONSTER_COLOR = ImVec4(255, 0, 0, 255);
ImVec4		Settings::RADAR_BOSS_COLOR = ImColor(255, 64, 0);
ImVec4		Settings::RADAR_NPC_COLOR = ImVec4(0, 255, 0, 255);
ImVec4		Settings::RADAR_MINE_COLOR = ImColor(255, 0, 102);
ImVec4		Settings::RADAR_STONE_COLOR = ImVec4(0, 0, 255, 255);
ImVec4		Settings::RADAR_PLAYER_COLOR = ImVec4(239, 255, 0, 255);
ImVec4		Settings::RADAR_WAYPOINT_COLOR = ImColor(43, 211, 120, 255);
bool		Settings::RADAR_MONSTER_SHOW_ENABLE = true;
bool		Settings::RADAR_BOSS_SHOW_ENABLE = true;
bool		Settings::RADAR_NPC_SHOW_ENABLE = true;
bool		Settings::RADAR_MINING_SHOW_ENABLE = true;
bool		Settings::RADAR_STONE_SHOW_ENABLE = true;
bool		Settings::RADAR_PLAYER_SHOW_ENABLE = true;
bool		Settings::RADAR_WAYPOINT_SHOW_ENABLE = true;
float		Settings::RADAR_ZOOM = 1.0;

//#################        REFINE

int			Settings::REFINE_UPGRADE_TYPE = 0;
int			Settings::REFINE_UPGRADE_COUNT = 1;
int			Settings::REFINE_ITEM_SLOT = 1;

//#################        OTHER

bool		Settings::GLOBAL_SWITCH_ENABLE = false;
bool		Settings::DUNGEON_BOT_ENABLE = false;
int			Settings::DUNGEON_TYPE = 0;
DWORD		Settings::INVENTORY_PAGE_SIZE = 45;
DWORD		Settings::INVENTORY_PAGE_COUNT = 4;