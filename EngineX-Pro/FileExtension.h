#pragma once
class FileExtension
{
public:
	static string GetAppDataDirectory()
	{
		char szPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
		{
			return string(szPath);
		}
		return "";
	}
	static string GetCommonDataDirectory()
	{
		char szPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath)))
		{
			return string(szPath);
		}
		return "";
	}
	static string GetDirectoryPathFromFilePatch(string filePath)
	{
		string directory;
		const size_t last_slash_idx = filePath.rfind('\\');
		if (std::string::npos != last_slash_idx)
		{
			directory = filePath.substr(0, last_slash_idx);
		}
		return directory;
	}

	static string GetCurrentExeDirectory()
	{
		const unsigned long maxDir = 260;
		char currentDir[maxDir];
		/*GetCurrentDirectory(maxDir, (LPWSTR)currentDir);*/
		return string(currentDir);
	}

	static int ReadFileSize(const char* filename, int* read)
	{
		ifstream file(filename, ios::binary | ios::ate);
		return file.tellg();
	}

	static char* ReadAllBytes(const char* filename, int* read)
	{
		ifstream ifs(filename, ios::binary | ios::ate);
		ifstream::pos_type pos = ifs.tellg();
		int length = pos;
		char* pChars = new char[length];
		ifs.seekg(0, ios::beg);
		ifs.read(pChars, length);
		ifs.close();
		*read = length;
		return pChars;
	}
	static vector<char> ReadAllBytes(char const* filename)
	{
		ifstream ifs(filename, ios::binary | ios::ate);
		ifstream::pos_type pos = ifs.tellg();

		std::vector<char>  result(pos);

		ifs.seekg(0, ios::beg);
		ifs.read(&result[0], pos);

		return result;
	}

	static bool CreateDirectoryPath(const char* path)
	{
		if (CreateDirectory(path, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	static void Read(const std::string& filepath, std::string& buffer)
	{
		std::ifstream fin(filepath.c_str());
		getline(fin, buffer, char(-1));
		fin.close();
	}
	static void Write(const std::string& file_name, void* data, int size)
	{
		std::ofstream out(file_name.c_str());
		out.write(reinterpret_cast<char*>(data), size);
		out.close();
	}
	static void Write(const std::string& file_name, std::string& data)
	{
		
		std::ofstream out(file_name.c_str());
		out << data;
		out.close();
	}
	static void Append(const std::string& file_name, std::string& data)
	{
		std::ofstream out;
		out.open(file_name, std::ios_base::app);
		out << data;

		out.close();
	}
	static void Read(const std::string& file_name, void* data, int size)
	{
		std::ifstream in(file_name.c_str());
		in.read(reinterpret_cast<char*>(data), size);
		in.close();
	}
	static void ReadDirectory(const std::string& name, vector<string>& v) 
	{
		std::string pattern(name);
		pattern.append("*");
		WIN32_FIND_DATAA data;
		HANDLE hFind;
		if ((hFind = FindFirstFileA(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) 
		{
			do
			{
				v.push_back(data.cFileName);
			} while (FindNextFileA(hFind, &data) != 0);
			FindClose(hFind);
		}
	}
	static string GetExtensionFilePath(string path)
	{
		
		std::string::size_type idx;
		idx = path.rfind('.');
		if (idx != std::string::npos)
		{
			std::string extension = path.substr(idx + 1);
			return extension;
		}
		else
		{
			return "";
		}
	}
	static vector<string> GetDirectoryFiles(string folderPath ,string selectedExtension  =""   /*format "exe"*/)
	{

		vector<string> names;
		string search_path = folderPath + "/*.*";
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{

				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					if (selectedExtension != "" && GetExtensionFilePath(fd.cFileName) != selectedExtension)
					{

					}
					else
					{
						string name = StringExtension::ReplaceString(fd.cFileName, "." + selectedExtension, "");
						names.push_back(StringExtension::ASCIIToUTF8(name));
					}
					
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return names;

	}
};

