#pragma once
class Logger
{
public:
	enum LogType
	{
		MAIN,
		FISH,
		SNIFFER,	
	};

	enum
	{
		RED,
		BLACK,
		BLUE,
		GREEN,
		WHITE,
		PINK,
		YELLOW
	};

	class LogWindow
	{
		enum
		{
			RED,
			BLACK,
			BLUE,
			GREEN,
			WHITE,
			PINK,
			YELLOW
		};
		class LogLine
		{
		public:
			vector< ImColor> colors;
			vector<string> text;
		};
	public:	
		LogWindow()
		{
			logLinesMain.push_back(std::make_shared < LogLine>());
			logLinesFish.push_back(std::make_shared < LogLine>());
			logLinesSniffer.push_back(std::make_shared < LogLine>());
		}

		vector< std::shared_ptr<LogLine>> logLinesMain;
		vector< std::shared_ptr<LogLine>> logLinesFish;
		vector< std::shared_ptr<LogLine>> logLinesSniffer;

		bool                ScrollToBottom;
		LogType CurrentLogs;
	
		ImVec4	GetColor(int color)
		{
			switch (color)
			{
			case RED:
				return ImColor(255, 1, 1, 255);
				break;
			case BLACK:
				return ImColor(1, 1, 1, 255);
				break;
			case GREEN:
				return ImColor(1, 255, 1, 255);
				break;
			case WHITE:
				return ImColor(255, 255, 255, 255);
				break;
			case YELLOW:
				return ImColor(255, 255, 0, 255);
				break;
			case PINK:
				return ImColor(255, 0, 255, 255);
				break;	
			}
		}

		void Clear()
		{
			switch (CurrentLogs)
			{
			case LogType::MAIN:
				logLinesMain.clear();
				logLinesMain.push_back(std::make_shared < LogLine>());
				break;
			case LogType::FISH:
				logLinesFish.clear();
				logLinesFish.push_back(std::make_shared < LogLine>());
				break;
			case LogType::SNIFFER:
				logLinesSniffer.clear();
				logLinesSniffer.push_back(std::make_shared < LogLine>());
				break;
			}
		}

		void Log(LogType type, bool isNewLine, int color, const char* fmt, ...)
		{
			va_list args;

			va_start(args, fmt);
			string  log = StringExtension::StringFormat(fmt, args);
			va_end(args);

			switch (type)
			{
			case LogType::MAIN:
				logLinesMain[logLinesMain.size() - 1]->colors.push_back(GetColor(color));
				logLinesMain[logLinesMain.size() - 1]->text.push_back(log);
				if (isNewLine)
				{
					logLinesMain.push_back(std::make_shared < LogLine>());
				}
				break;
			case LogType::FISH:
				logLinesFish[logLinesFish.size() - 1]->colors.push_back(GetColor(color));
				logLinesFish[logLinesFish.size() - 1]->text.push_back(log);
				if (isNewLine)
				{
					logLinesFish.push_back(std::make_shared < LogLine>());
				}
				break;
			case LogType::SNIFFER:
				logLinesSniffer[logLinesSniffer.size() - 1]->colors.push_back(GetColor(color));
				logLinesSniffer[logLinesSniffer.size() - 1]->text.push_back(log);
				if (isNewLine)
				{
					logLinesSniffer.push_back(std::make_shared < LogLine>());
				}
				break;
			}
			/*va_list args;
			va_start(args, fmt);
			Buf.appendfv(fmt, args);
			va_end(args);*/
			ScrollToBottom = true;
		}

		void Draw(bool* isOpen = NULL)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400));
			if (!ImGui::Begin("Log Window", isOpen))
			{
				ImGui::End();
				return;
			}
			ImGui::RadioButton("Main", (int*)&CurrentLogs, LogType::MAIN); ImGui::SameLine();
			ImGui::RadioButton("Fish", (int*)&CurrentLogs, LogType::FISH); ImGui::SameLine();
#ifdef DEVELOPER_MODE
			ImGui::RadioButton("Sniffer", (int*)&CurrentLogs, LogType::SNIFFER);
#endif
			if (ImGui::Button("Clear"))
			{
				Clear();
			}
			ImGui::SameLine();
			bool copy = ImGui::Button("Copy");
			ImGui::SameLine();
			/*Filter.Draw("Filter", -100.0f);*/
			ImGui::Separator();
			ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			if (copy)
			{
				ImGui::LogToClipboard();
			}

			std::vector< std::shared_ptr< LogLine>>::iterator begin;
			std::vector< std::shared_ptr< LogLine>>::iterator end;
			switch (CurrentLogs)
			{
			case LogType::MAIN:
				begin = logLinesMain.begin();
				end = logLinesMain.end();
				break;
			case LogType::FISH:
				begin = logLinesFish.begin();
				end = logLinesFish.end();
				break;
			case LogType::SNIFFER:
				begin = logLinesSniffer.begin();
				end = logLinesSniffer.end();
				break;
			}
			for (std::vector< std::shared_ptr< LogLine>>::iterator it = begin; it != end; ++it)
			{
				for (int i = 0; i < it->get()->text.size(); i++)
				{
					if(i)
					{
						ImGui::SameLine();
					}
					
					ImGui::TextColored(it->get()->colors[i], it->get()->text[i].c_str());
				}
				/*ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f),"\n");*/
			}
			

			if (ScrollToBottom)
			{
				ImGui::SetScrollHere(1.0f);
			}
				
			ScrollToBottom = false;
			ImGui::EndChild();
			ImGui::End();
		}
	};
private:
	static LogWindow mainLogWindow;
	static bool  isMainLogWindowOpen;
	public:
	
	static void AddString(int window, bool isNewLine, int color, string format, ...)
	{
		va_list args;
		
		va_start(args, format);
		Add(window, isNewLine, color, format.c_str(), args);
		va_end(args);
	}
	static void Add(int window, bool isNewLine, int color, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		/*string frm = StringExtension::StringFormat(format, args);
		format = frm.c_str();*/
		switch (window)
		{
		case MAIN:
			mainLogWindow.Log(LogType::MAIN, isNewLine, color, format, args);
			break;
		case FISH:
			mainLogWindow.Log(LogType::FISH, isNewLine, color, format, args);
			break;
		case SNIFFER:
			mainLogWindow.Log(LogType::SNIFFER, isNewLine, color, format/*, args*/);
			break;
		}	

		va_end(args);
	}
	
	static void Draw()
	{
		mainLogWindow.Draw(&isMainLogWindowOpen);
	}
};

bool  Logger::isMainLogWindowOpen = true;

Logger::LogWindow Logger::mainLogWindow;