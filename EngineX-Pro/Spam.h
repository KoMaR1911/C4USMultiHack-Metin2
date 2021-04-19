#pragma once
class Spam : public IAbstractModuleBase, public Singleton<Spam>
{

	template<typename T>
	inline T Clamp(float v, T mn, T mx)
	{
		return (v < mn) ? mn : (v > mx) ? mx : v;
	}

	string GetTextColor(ImVec4 col,string text)
	{

		float f[4] = { col.x, col.y, col.z, col.w };
		int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };
		char buf[16];
		ImFormatString(buf, IM_ARRAYSIZE(buf), "%02X%02X%02X%02X", Clamp(i[3], 0, 255), Clamp(i[0], 0, 255), Clamp(i[1], 0, 255), Clamp(i[2], 0, 255));

		string color = "|c";
		color += buf;
		color += text;
		color += "|H|h";
		return color;

	}


	string  shoutTextMessage = string(500, '\0');
	string  whisperTextMessage = string(500, '\0');
	string  normalTextMessage = string(500, '\0');
	float wisperTimeLoop = 0;

public:

	void OnRender()
	{
	}

	void OnStart()
	{
		
		
	}

	void OnStop()
	{
	}

	void OnUpdate()
	{
		if (Settings::SPAM_NORMAL_ENABLE)
		{
			
			if (strlen(normalTextMessage.c_str()))
			{
				if (DynamicTimer::CheckAutoSet("SpamNormal", Settings::SPAM_NORMAL_TIME * 1000))
				{

					string text = "";
					if (Settings::SPAM_NORMAL_COLOR_ENABLE)
					{
						text += GetTextColor(Settings::SPAM_NORMAL_COLOR, normalTextMessage.c_str());
					}
#ifdef DEVELOPER_MODE
					else if (Settings::SPAM_NORMAL_RAINBOW_COLOR_ENABLE)
					{
						for (int i = 0; i < strlen(normalTextMessage.c_str()); i++)
						{
							string str = "";
							char letter = +normalTextMessage[i];
							str += letter;
							text += GetTextColor(ImColor(MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), 255), str);
						}
					}
#endif
					else
					{
						text += normalTextMessage.c_str();
					}


					GameFunctions::NetworkStreamSendChatPacket(StringExtension::UTF8ToASCII(text).c_str(), CHAT_TYPE_TALKING);

				}

			}
		}
		if (Settings::SPAM_SHOUT_ENABLE)
		{
			if (strlen(shoutTextMessage.c_str()))
			{
				if (DynamicTimer::CheckAutoSet("SpamShout", Settings::SPAM_SHOUT_TIME * 1000))
				{

					string text = "";


					if (Settings::SPAM_SHOUT_COLOR_ENABLE)
					{
						text += GetTextColor(Settings::SPAM_SHOUT_COLOR, shoutTextMessage.c_str());
					}
#ifdef DEVELOPER_MODE
					else if (Settings::SPAM_SHOUT_RAINBOW_COLOR_ENABLE)
					{
						for (int i = 0; i < strlen(shoutTextMessage.c_str()); i++)
						{
							string str = "";
							char letter = +shoutTextMessage[i];
							str += letter;
							text += GetTextColor(ImColor(MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), 255), str);
						}
					}
#endif
					else
					{
						text += shoutTextMessage.c_str();
					}

					
					GameFunctions::NetworkStreamSendChatPacket(StringExtension::UTF8ToASCII(text).c_str(), CHAT_TYPE_SHOUT);

				}
			}
		}
		if (Settings::SPAM_WISPER_ENABLE)
		{
			if (strlen(whisperTextMessage.c_str()))
			{
				if (DynamicTimer::CheckAutoSet("SpamWhisper", wisperTimeLoop * 1000 ))
				{
					map<DWORD, DWORD*> playerList = GameFunctionsCustom::GetObjectList(OBJECT_PC);
					DWORD targetNumber = 0;
					for (map<DWORD, DWORD*>::iterator itor = playerList.begin(); itor != playerList.end(); itor++)
					{
						DWORD vid = itor->first;

						string text = "";
						if (Settings::SPAM_WHISPER_COLOR_ENABLE)
						{
							text += GetTextColor(Settings::SPAM_WHISPER_COLOR, whisperTextMessage.c_str());
						}
#ifdef DEVELOPER_MODE
						else if (Settings::SPAM_WHISPER_RAINBOW_COLOR_ENABLE)
						{
							for (int i = 0; i < strlen(whisperTextMessage.c_str()); i++)
							{
								string str = "";
								char letter = +whisperTextMessage[i];
								str += letter;
								text += GetTextColor(ImColor(MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), MiscExtension::RandomInt(0, 255), 255), str);
							}
						}
#endif
						else
						{
							text += whisperTextMessage.c_str();
						}
						
						
						const char* name = GameFunctions::InstanceBaseGetNameString(itor->second);


						DelayActions::Append((Settings::SPAM_WHISPER_TIME * targetNumber), GameFunctions::NetworkStreamSendWhisperPacket, name, StringExtension::UTF8ToASCII(text));
						
#ifdef DEVELOPER_MODE					
						if (Globals::m_apoPhaseWndGame != NULL)
						{
							DelayActions::Append((Settings::SPAM_WHISPER_TIME* targetNumber),&GameFunctions::PyCallClassMemberFunc,Globals::m_apoPhaseWndGame, "OnRecvWhisper", Globals::Py_BuildValue("(iss)", 0, name, StringExtension::UTF8ToASCII(text).c_str()));
						}
#endif					
						
						targetNumber++;

					}
					wisperTimeLoop = Settings::SPAM_WHISPER_TIME * targetNumber;

				}
			}
		}

	}

	void OnTab1()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("WhisperBorder", ImVec2(ImGui::GetWindowWidth() - 10, 90), true);
		ImGui::Checkbox("Whisper", &Settings::SPAM_WISPER_ENABLE); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputFloat("Time (s.ms)", &Settings::SPAM_WHISPER_TIME, 0.100, 1); ImGui::SameLine(); ImGui::ColorEdit4("##SpamWhisperColor", (float*)&Settings::SPAM_WHISPER_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox("Text Color", &Settings::SPAM_WHISPER_COLOR_ENABLE);
		{
			Settings::SPAM_WHISPER_RAINBOW_COLOR_ENABLE = false;
		};
#ifdef DEVELOPER_MODE
		ImGui::SameLine();
		if (ImGui::Checkbox("Rainbow Color", &Settings::SPAM_WHISPER_RAINBOW_COLOR_ENABLE))
		{
			Settings::SPAM_WHISPER_COLOR_ENABLE = false;
		};
#endif
		ImGui::PushItemWidth(400); ImGui::InputText("Text", &whisperTextMessage[0], whisperTextMessage.size());
		ImGui::EndChild();
		ImGui::PopStyleVar();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("NormalBorder", ImVec2(ImGui::GetWindowWidth() - 10, 90), true);
		ImGui::Checkbox("Normal", &Settings::SPAM_NORMAL_ENABLE); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputFloat("Time (s.ms)", &Settings::SPAM_NORMAL_TIME, 0.100, 1);
		ImGui::SameLine();
		ImGui::ColorEdit4("##SpamNormalColor", (float*)&Settings::SPAM_NORMAL_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox("Text Color", &Settings::SPAM_NORMAL_COLOR_ENABLE);
		{
			Settings::SPAM_NORMAL_RAINBOW_COLOR_ENABLE = false;
		};
#ifdef DEVELOPER_MODE
		ImGui::SameLine();
		if (ImGui::Checkbox("Rainbow Color", &Settings::SPAM_NORMAL_RAINBOW_COLOR_ENABLE))
		{
			Settings::SPAM_NORMAL_COLOR_ENABLE = false;
		};
#endif
		ImGui::PushItemWidth(400); ImGui::InputText("Text", &normalTextMessage[0], normalTextMessage.size());
		ImGui::EndChild();
		ImGui::PopStyleVar();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("ShoutBorder", ImVec2(ImGui::GetWindowWidth() - 10, 90), true); ImGui::SameLine();
		ImGui::Checkbox("Shout", &Settings::SPAM_SHOUT_ENABLE); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputFloat("Time (s.ms)", &Settings::SPAM_SHOUT_TIME, 0.100, 1);
		ImGui::SameLine();
		ImGui::ColorEdit4("##SpamShoutColor", (float*)&Settings::SPAM_SHOUT_COLOR, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox("Text Color", &Settings::SPAM_SHOUT_COLOR_ENABLE);
		{
			Settings::SPAM_SHOUT_RAINBOW_COLOR_ENABLE = false;
		};
#ifdef DEVELOPER_MODE
		ImGui::SameLine();
		if (ImGui::Checkbox("Rainbow Color", &Settings::SPAM_SHOUT_RAINBOW_COLOR_ENABLE))
		{
			Settings::SPAM_SHOUT_COLOR_ENABLE = false;
		};
#endif
		ImGui::PushItemWidth(400); ImGui::InputText("Text", &shoutTextMessage[0], shoutTextMessage.size());
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void OnTabs()
	{
		MainForm::AddTab(33, "Spam");
	}

	void OnMenu()
	{
		switch (MainForm::CurTabOpen)
		{
		case 33:
			OnTab1();
			break;
		}
	}
};

