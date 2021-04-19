#pragma once

template <typename T>
class TAbstractSingleton
{
	static T* ms_singleton;

public:
	TAbstractSingleton()
	{
		
		int offset = (int)(T*)1 - (int)(Singleton <T>*) (T*) 1;
		ms_singleton = (T*)((int)this + offset);
	}

	virtual ~TAbstractSingleton()
	{
		
		ms_singleton = 0;
	}

	__forceinline static T& GetSingleton()
	{
		
		return (*ms_singleton);
	}
};

template <typename T> T* TAbstractSingleton <T>::ms_singleton = 0;