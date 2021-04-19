#pragma once

template <typename T> class Singleton
{
	static T* ms_singleton;

public:
	Singleton()
	{
		
		int offset = (int)(T*)1 - (int)(Singleton <T>*) (T*) 1;
		ms_singleton = (T*)((int)this + offset);
	}

	virtual ~Singleton()
	{
	
		ms_singleton = 0;
	}

	__forceinline static T& Instance()
	{
		
		return (*ms_singleton);
	}

	__forceinline static T* InstancePtr()
	{
		return (ms_singleton);
	}

	__forceinline static T& instance()
	{
		
		return (*ms_singleton);
	}
};

template <typename T> T* Singleton <T>::ms_singleton = 0;


