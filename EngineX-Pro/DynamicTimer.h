#pragma once
class DynamicTimer
{
	static map< string, DWORD> timersList;
public:
	static bool CheckAutoSet(string timerName,DWORD timeMiliseconds)
	{
		if (timersList.count(timerName))
		{
			if (GetTickCount() - timersList[timerName] > timeMiliseconds)
			{
				timersList[timerName] = GetTickCount();
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			timersList.insert(std::make_pair(timerName, GetTickCount()));
			return true;
		}
		
	}

	static bool Check(string timerName, DWORD timeMiliseconds )
	{
		if (timersList.count(timerName))
		{
			if (GetTickCount() - timersList[timerName] > timeMiliseconds)
			{
				
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			timersList.insert(std::make_pair(timerName, GetTickCount()));
			return true;
		}

	}
	static bool SetTick(string timerName )
	{
		if (timersList.count(timerName))
		{

			timersList[timerName] = GetTickCount();
			return true;
		}
		return false;
	}

	static bool IsActive(string timerName, DWORD timeMiliseconds)
	{
		if (timersList.count(timerName))
		{

			if (GetTickCount() - timersList[timerName] > timeMiliseconds)
			{

				return false;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
};

 map< string, DWORD> DynamicTimer::timersList;