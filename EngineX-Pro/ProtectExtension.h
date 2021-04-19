#pragma once
class ProtectExtension
{
public:
	static string GetMacAdress()
	{
		IP_ADAPTER_INFO		AdapterInfo[32];
		PIP_ADAPTER_INFO	pAdapterInfo;

		DWORD dwSize = sizeof(AdapterInfo);
		DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwSize);
		string address = "";

		for (pAdapterInfo = AdapterInfo; pAdapterInfo; pAdapterInfo = pAdapterInfo->Next)
		{
			for (size_t i = 0; i < 6; i++)
			{
				char Out[10] = { 0 };
				int32_t k = pAdapterInfo->Address[i];
				sprintf_s(Out, "%s%02X", i ? "" : "", k);
				address += Out;
			}
		}
		return address;
	}

	static DWORD GetVolumeId(string volumeLetter)
	{
		DWORD serialNum = 0;

		/*string volumePath = volumeLetter + ":\\";
		GetVolumeInformation(volumePath.c_str(), NULL, 0, &serialNum, NULL, NULL, NULL, 0);*/


		return serialNum;
	}


	static string GetCpuId()
	{
		int cpuinfo[4] = { 0, 0, 0, 0 };
		__cpuid(cpuinfo, 0);
		string id;
		for (int i = 0; i < 4; i++)
		{
			id += to_string(cpuinfo[i]) + "|";
		}

		return id;
	}

	static string GetMachineName()
	{
		TCHAR computerName[1024];
		DWORD size = 1024;
		GetComputerName(computerName, &size);
		return StringExtension::StringFromWChar(computerName);
	}

	static string GetHWID()
	{
		/*HW_PROFILE_INFO hwProfileInfo;
		GetCurrentHwProfile(&hwProfileInfo);
		wstring hwidWString = hwProfileInfo.szHwProfileGuid;
		return StringExtension::StringFromWString(hwidWString);*/
		return"";
	}
};

bool SetAdminPrivilege(char* PrivilegeName) // OK
{
	HANDLE TokenHandle;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &TokenHandle) == 0)
	{
		return 0;
	}

	LUID luid;

	if (LookupPrivilegeValue(0, PrivilegeName, &luid) == 0)
	{
		return 0;
	}

	TOKEN_PRIVILEGES tp;

	memset(&tp, 0, sizeof(tp));

	tp.PrivilegeCount = 1;

	tp.Privileges[0].Luid = luid;

	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (AdjustTokenPrivileges(TokenHandle, 0, &tp, sizeof(tp), 0, 0) == 0)
	{
		return 0;
	}

	return 1;
}
bool GetPhysicalDriveSerialNumber(int PhysicalDriveNumber, char* PhysicalDriveSerial, int PhysicalDriveSerialSize) // OK
{
	char PhysicalDrivePath[MAX_PATH];

	wsprintf(PhysicalDrivePath, "\\\\.\\PhysicalDrive%d", PhysicalDriveNumber);

	HANDLE PhysicalDriveHandle = CreateFile(PhysicalDrivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (PhysicalDriveHandle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD BytesReturned;

	STORAGE_PROPERTY_QUERY StoragePropertyQuery;

	STORAGE_DESCRIPTOR_HEADER StorageDescriptorHeader;

	memset(&StoragePropertyQuery, 0, sizeof(StoragePropertyQuery));

	memset(&StorageDescriptorHeader, 0, sizeof(StorageDescriptorHeader));

	StoragePropertyQuery.PropertyId = StorageDeviceProperty;

	StoragePropertyQuery.QueryType = PropertyStandardQuery;

	if (DeviceIoControl(PhysicalDriveHandle, IOCTL_STORAGE_QUERY_PROPERTY, &StoragePropertyQuery, sizeof(StoragePropertyQuery), &StorageDescriptorHeader, sizeof(StorageDescriptorHeader), &BytesReturned, 0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		return 0;
	}

	BYTE* PhysicalDriveBuff = new BYTE[StorageDescriptorHeader.Size];

	memset(PhysicalDriveBuff, 0, StorageDescriptorHeader.Size);

	if (DeviceIoControl(PhysicalDriveHandle, IOCTL_STORAGE_QUERY_PROPERTY, &StoragePropertyQuery, sizeof(StoragePropertyQuery), PhysicalDriveBuff, StorageDescriptorHeader.Size, &BytesReturned, 0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	if (((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	__try
	{
		strcpy_s(PhysicalDriveSerial, PhysicalDriveSerialSize, (char*)(PhysicalDriveBuff + ((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset));
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 1;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}
}
string GetHardwareId() //OK
{
	char PhysicalDriveSerial[256];

	memset(PhysicalDriveSerial, 0, sizeof(PhysicalDriveSerial));

	for (int n = 0; n < 5; n++)
	{
		if (GetPhysicalDriveSerialNumber(n, PhysicalDriveSerial, sizeof(PhysicalDriveSerial)) != 0)
		{
			break;
		}
	}

	DWORD ComputerHardwareId1 = *(DWORD*)(&PhysicalDriveSerial[0x00]) ^ *(DWORD*)(&PhysicalDriveSerial[0x10]) ^ 0x3AD3B74A;

	DWORD ComputerHardwareId2 = *(DWORD*)(&PhysicalDriveSerial[0x04]) ^ *(DWORD*)(&PhysicalDriveSerial[0x14]) ^ 0x94FDC685;

	DWORD ComputerHardwareId3 = *(DWORD*)(&PhysicalDriveSerial[0x08]) ^ *(DWORD*)(&PhysicalDriveSerial[0x18]) ^ 0xF45BBF4C;

	DWORD ComputerHardwareId4 = *(DWORD*)(&PhysicalDriveSerial[0x0C]) ^ *(DWORD*)(&PhysicalDriveSerial[0x1C]) ^ 0x8941D8E7;

	static char HardwareId[36];

	wsprintf(HardwareId, "%08X-%08X-%08X-%08X", ComputerHardwareId1, ComputerHardwareId2, ComputerHardwareId3, ComputerHardwareId4);

	return string(HardwareId);
}
//std::vector<std::string> GetAllMacAddresses()
//{
//	std::vector<std::string> macs;
//	std::string address;
//
//	// from: https://stackoverflow.com/questions/9034575/c-c-linux-mac-address-of-all-interfaces
//	//  ... just read /sys/class/net/eth0/address
//
//	// NOTE: there may be more than one: /sys/class/net/*/address
//	//  (1) so walk /sys/class/net/* to find the names to read the address of.
//
//	std::vector<std::string> nets = GetAllFiles("/sys/class/net/", false);
//	for (auto it = nets.begin(); it != nets.end(); ++it)
//	{
//		// we don't care about the local loopback interface
//		if (0 == strcmp((*it).substr(-3).c_str(), "/lo"))
//			continue;
//		address.clear();
//		if (ReadFileContents(*it, "address", address))
//		{
//			if (!address.empty())
//			{
//				macs.push_back(address);
//			}
//		}
//	}
//	return macs;
//}