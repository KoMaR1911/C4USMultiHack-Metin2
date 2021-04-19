#pragma once
class MiscExtension
{



	//uint32_t Misc::CRC32(const std::string &fp)
	//{
	//	boost::crc_32_type crc;
	//	std::vector<char> buffer(4096);
	//	std::ifstream stream(fp, std::ios::in | std::ios::binary);
	//	if (!stream) throw std::ifstream::failure("Could not open file for CRC calculation: " + fp);
	//	do {
	//		stream.read(&buffer[0], buffer.size());
	//		size_t BYTE_cnt = static_cast<size_t>(stream.gcount());
	//		crc.process_bytes(&buffer[0], BYTE_cnt);
	//	} while (stream);
	//	return crc.checksum();
	//}
public:
	static BOOL ShowBalloon(HWND hWnd, const char* title, const char* text, HICON hIcon)
	{
		BOOL bRes = FALSE;
		if (hWnd != NULL)
		{
			NOTIFYICONDATA nfidata = { sizeof(NOTIFYICONDATA) };
			nfidata.cbSize = sizeof(nfidata);
			nfidata.hWnd = hWnd;
			nfidata.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PNG4), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
			nfidata.uFlags = NIF_ICON | NIF_INFO | NIF_TIP;
			if (hIcon)
			{
				nfidata.hBalloonIcon = hIcon;		
			}
			nfidata.uVersion = NOTIFYICON_VERSION_4;
			nfidata.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
			nfidata.hBalloonIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PNG4));
			nfidata.uTimeout = 500;
			//nfidata.hBalloonIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDB_PNG1));;
			/*nfidata.dwInfoFlags = NIIF_INFO;*/
			StringCchCopy(nfidata.szInfo, ARRAYSIZE(nfidata.szInfo), text);
			StringCchCopy(nfidata.szInfoTitle, ARRAYSIZE(nfidata.szInfoTitle), title);
			bRes = Shell_NotifyIcon(NIM_ADD, &nfidata);
			
		}
		return bRes;
	}
	//string GetActiveWindowTitle()
	//{
	//	char wnd_title[256];
	//	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	//	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	//	return wnd_title;
	//}
	
	static void OpenWebiste(string site)
	{
		/*ShellExecute(0, 0, site.c_str(), 0, 0, SW_SHOW);*/
		system(("start "+ site).c_str());
	}

	static void PlayAlerSound()
	{
		PlaySound("SystemAsterisk", NULL, SND_SYNC);
	}
	

	static BOOL UpdateBalloon(HWND hWnd, const char* title, const char* text, HICON hIcon)
	{
		BOOL bRes = FALSE;
		if (hWnd != NULL)
		{
			NOTIFYICONDATA nfidata = { sizeof(NOTIFYICONDATA) };
			nfidata.cbSize = sizeof(nfidata);
			nfidata.hWnd = hWnd;

			nfidata.uFlags = NIF_ICON | NIF_INFO | NIF_TIP;
			if (hIcon)
			{
				nfidata.hBalloonIcon = hIcon;
				nfidata.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
			}
			nfidata.uVersion = NOTIFYICON_VERSION_4;
			//nfidata.hBalloonIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDB_PNG1));
			nfidata.uTimeout = 500;
			//nfidata.hBalloonIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDB_PNG1));;
			nfidata.dwInfoFlags = NIIF_INFO;
			StringCchCopy(nfidata.szInfo, ARRAYSIZE(nfidata.szInfo), text);
			StringCchCopy(nfidata.szInfoTitle, ARRAYSIZE(nfidata.szInfoTitle), title);
			bRes = Shell_NotifyIcon(NIM_MODIFY, &nfidata);

		}
		return bRes;
	}
	static HWND FindTopWindow(DWORD pid)
	{
		std::pair<HWND, DWORD> params = { 0, pid };

		// Enumerate the windows using a lambda to process each window
		BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			auto pParams = (std::pair<HWND, DWORD>*)(lParam);

			DWORD processId;
			if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
			{
				// Stop enumerating
				SetLastError(-1);
				pParams->first = hwnd;
				return FALSE;
			}

			// Continue enumerating
			return TRUE;
		}, (LPARAM)&params);

		if (!bResult && GetLastError() == -1 && params.first)
		{
			return params.first;
		}

		return 0;
	}

	static std::string RandomString(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}
	static int RandomInt(int min, int max)
	{
		static bool first = true;
		if (first)
		{
			srand(time(NULL));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}


	static float RandomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;

		float range = max - min;
		return (random * range) + min;
	}


	struct EnumWindowsCallbackArgs 
	{
		EnumWindowsCallbackArgs(DWORD p) : pid(p) { }
		const DWORD pid;
		std::vector<HWND> handles;
	};

	static BOOL CALLBACK EnumWindowsCallback(HWND hnd, LPARAM lParam)
	{
		EnumWindowsCallbackArgs* args = (EnumWindowsCallbackArgs*)lParam;

		DWORD windowPID;
		(void)::GetWindowThreadProcessId(hnd, &windowPID);
		if (windowPID == args->pid) {
			args->handles.push_back(hnd);
		}

		return TRUE;
	}
	static std::vector<HWND> GetToplevelWindows()
	{
		EnumWindowsCallbackArgs args(::GetCurrentProcessId());
		if (::EnumWindows(&EnumWindowsCallback, (LPARAM)&args) == FALSE) {
			// XXX Log error here
			return std::vector<HWND>();
		}
		return args.handles;
	}

	static string CurrentDateTime()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}
	static string CurrentDateTimeShort()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%X", &tstruct);

		return buf;
	}



	static SYSTEMTIME GetServerTime()
	{

		// Clear output buffer
		SYSTEMTIME sysTime;
		SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));

		// Open connection
		HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (!hInternetSession)
			return sysTime;

		HINTERNET hInternetFile = InternetOpenUrl(hInternetSession,
			"http://google.pl", 0, 0,            /////L"http://time.windows.com", 0, 0,
			INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


		if (!hInternetFile)
		{
			InternetCloseHandle(hInternetSession);
			return sysTime;
		}

		// Query date time in format systemtime
		DWORD dwSize = sizeof(SYSTEMTIME);
		if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE |
			HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
		{
			InternetCloseHandle(hInternetSession);
			InternetCloseHandle(hInternetFile);
			return sysTime;
		}

		// Clean up ...
		InternetCloseHandle(hInternetFile);
		InternetCloseHandle(hInternetSession);
		return sysTime;
	}


	
	static int CountDistanceTwoPoints(D3DVECTOR startPoint, D3DVECTOR endPoint)
	{
		// Calculating distance 
		return sqrt(pow(endPoint.x - startPoint.x, 2) +
			pow(endPoint.y - startPoint.y, 2) * 1.0);
	}
	static int CountDistanceTwoPoints(int x1, int y1, int x2, int y2)
	{
		// Calculating distance 
		return sqrt(pow(x2 - x1, 2) +
			pow(y2 - y1, 2) * 1.0);
	}

	static float AngleBetweenTwoPoints(float x1, float y1, float x2, float y2)
	{



		//static const double TWOPI = 6.2831853071795865;
		//static const double RAD2DEG = 57.2957795130823209;
		//// if (a1 = b1 and a2 = b2) throw an error 
		//double theta = atan2(x2 - x1, y2 - y2);
		//if (theta < 0.0)
		//	theta += TWOPI;
		//return RAD2DEG * theta;



		/*float dot = x1 * x2 + y1 * y2; 
		float det = x1 * y2 - y1 * x2;      
		float angle = atan2(det, dot);*/

	

		/*float a = x1 * x2 + y1 * y2;
		float b = std::sqrt(x1 * x1 + y1 * y1);
		float c = std::sqrt(x2 * x2 + y2 * y2);
		float angle = std::acos(a / (b * c));*/

		
		float angle = (float)atan2(y2 - y1, x2 - x1) * (float)(180 / 3.14159265358979323846);
		/*if (angle < 0)
		{
			angle += 360;
		}*/


		return angle;
	}
	static D3DVECTOR GetPercentPointBetweenTwoPoints(double x1, double y1, double x2,double y2, double percent)
	{
		double m = percent;
		double n = 100 - percent;
		// Applying section formula 
		double x = ((n * x1) + (m * x2)) /
			(m + n);
		double y = ((n * y1) + (m * y2)) /
			(m + n);
		return D3DVECTOR{ (float)x,(float)y,0 };
	
	}
	static D3DVECTOR GetPercentPointBetweenTwoPoints(D3DVECTOR pointStart, D3DVECTOR pointEnd, double percent)
	{
		double m = percent;
		double n = 100 - percent;
		// Applying section formula 
		double x = ((n * pointStart.x) + (m * pointEnd.x)) /
			(m + n);
		double y = ((n * pointStart.y) + (m * pointEnd.y)) /
			(m + n);
		double z = ((n * pointStart.z) + (m * pointEnd.z)) /
			(m + n);
		return D3DVECTOR{ (float)x,(float)y,(float)z };

	}
	static vector<D3DVECTOR> DivideTwoPointsByDistance(DWORD distance, D3DVECTOR pointStart , D3DVECTOR pointEnd)
	{
		vector<D3DVECTOR> points;
		int distanceTwoPoints = CountDistanceTwoPoints(pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);
		if (distanceTwoPoints <= distance)
		{
			points.push_back(pointEnd);
			return points;
		}
		else
		{
			int steps = distanceTwoPoints / distance;
			double singleStepPercent = (distance * 100) / distanceTwoPoints;
			for (int i = 1; i < steps + 1; i++)
			{
				points.push_back(GetPercentPointBetweenTwoPoints(pointStart, pointEnd, i * singleStepPercent));
			}
			if (steps * distance == distanceTwoPoints)
			{

			}
			else
			{
				points.push_back(pointEnd);
			}


		}

		return points;
		
	}

	//static string randomMac()
	//{
	//	 char letterAssign(int x)
	//	{
	//		char l;
	//		if (x == 10) l = 'A';
	//		if (x == 11) l = 'B';
	//		if (x == 12) l = 'C';
	//		if (x == 13) l = 'D';
	//		if (x == 14) l = 'E';
	//		if (x == 15) l = 'F';

	//		return l;
	//	}
	//	std::string mac;
	//	for (int i = 0; i < 12; i++)
	//	{
	//		if (i > 0 ? (i) % 2 == 0 : 0) mac += "::";

	//		int x = rand() % 16;
	//		if (x > 9)
	//		{
	//			char letter = letterAssign(x);
	//			mac += letter;
	//		}
	//		else
	//		{
	//			mac += std::to_string(x);
	//		}
	//	}
	//	return mac;
	//}
};

