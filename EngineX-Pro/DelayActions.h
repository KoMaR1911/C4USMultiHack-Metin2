#pragma once



//#################################################################################################################################
class DelayActions
{
public:
	class IAction
	{
	public:
		virtual ~IAction() {}

		virtual void Call() = 0;
		virtual bool IsReady() = 0;
		virtual bool IsEnded() = 0;
		virtual bool IsWaitAfter() = 0;
		virtual bool IsWaitBlock() = 0;
		virtual DWORD* GetFunctionPtr() = 0;
		virtual bool IsUniqueEquals(string uniqueString) = 0;
	};
	template <class T, class... Args>
	//#################################################################################################################################
	class Action : public IAction
	{
		enum Status
		{
			WAITING,
			READY,
			ENDED
		};
		std::function<typename std::result_of<T(Args...)>::type()> task;
		DWORD miliseconds;
		DWORD startTickCount;
		DWORD* functionPointer;
		Status status;
		bool isWaitAfter;
		bool isWaitBlock;
		string uniqueString;
	public:
		//#################################################################################################################################
		Action(bool isWaitBlock, bool isWaitAfter, string uniqueString, DWORD miliseconds, T&& function, Args&&... args)
		{
			this->miliseconds = miliseconds;
			this->task = (std::bind(std::forward<T>(function), std::forward<Args>(args)...));
			this->startTickCount = GetTickCount();
			this->functionPointer = (DWORD*)function;
			this->isWaitAfter = isWaitAfter;
			this->isWaitBlock = isWaitBlock;
			this->status = Status::WAITING;
			this->uniqueString = uniqueString;
		}
		//#################################################################################################################################
		virtual  ~Action()override
		{
			this->miliseconds = 0;
			this->startTickCount = 0;
			this->functionPointer = NULL;
			this->isWaitAfter = NULL;
			this->isWaitBlock = NULL;
			this->uniqueString = "";
		}
		//#################################################################################################################################
		virtual bool IsWaitAfter() override
		{
			return this->isWaitAfter;
		}
		//#################################################################################################################################
		virtual bool IsWaitBlock() override
		{
			return this->isWaitBlock;
		}
		//#################################################################################################################################
		virtual bool IsReady() override
		{
			if (!isWaitAfter && (GetTickCount() - startTickCount) >= miliseconds && this->status == Status::WAITING)
			{
				this->status = Status::READY;
				return true;
			}
			else if (isWaitAfter && this->status == Status::WAITING)
			{
				this->status = Status::READY;
				return true;
			}
			else
			{
				return false;
			}
		}
		//#################################################################################################################################
		virtual bool IsEnded() override
		{
			if (!isWaitAfter && status == Status::ENDED)
			{
				return true;
			}
			else if (isWaitAfter && status == Status::ENDED)
			{
				if ((GetTickCount() - startTickCount) >= miliseconds)
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
				return false;
			}
		}
		//#################################################################################################################################
		virtual DWORD* GetFunctionPtr() override
		{
			return functionPointer;
		}
		//#################################################################################################################################
		virtual bool IsUniqueEquals(string uniqueString) override
		{
			if (this->uniqueString == "")
			{
				return false;
			}
			else if (this->uniqueString == uniqueString)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//#################################################################################################################################
		virtual void Call() override
		{
			task();
			if (isWaitAfter)
			{
				startTickCount = GetTickCount();
			}

			this->status = Status::ENDED;
		}
	};

private:
	static std::vector< std::shared_ptr<IAction>>  actionsList;
public:
	template <class T, class... Args>
	static  std::shared_ptr<IAction> MakeSharedPtr(bool isWaitBlock, bool isWaitAfter, string uniqueString, DWORD miliseconds, T&& function, Args&&... args)
	{
		return std::make_shared<Action<T, Args...>>(isWaitBlock, isWaitAfter, uniqueString, miliseconds, function, args...);
	}
	//#################################################################################################################################
	template <class T, class... Args>
	static bool  Append(int miliseconds, T&& function, Args&&... args)
	{

		actionsList.push_back(MakeSharedPtr(false, false, "", miliseconds, function, args...));
		return true;
	}
	//#################################################################################################################################
	template <class T, class... Args>
	static bool  AppendBlock(bool isBlockAfter, int miliseconds, T&& function, Args&&... args)
	{
		for (std::vector< std::shared_ptr<IAction>>::iterator it = actionsList.begin(); it != actionsList.end(); ++it)
		{
			if (it->get()->GetFunctionPtr() == (DWORD*)function && it->get()->IsWaitBlock())
			{
				return false;
			}
		}
		actionsList.push_back(MakeSharedPtr(true, isBlockAfter, "", miliseconds, function, args...));
		return true;
	}
	//#################################################################################################################################
	template <class T, class... Args>
	static bool  AppendBlockUnique(bool isBlockAfter,  int miliseconds, string uniqueString,T&& function, Args&&... args)
	{
		for (std::vector< std::shared_ptr<IAction>>::iterator it = actionsList.begin(); it != actionsList.end(); ++it)
		{
			if (it->get()->GetFunctionPtr() == (DWORD*)function && it->get()->IsWaitBlock() && it->get()->IsUniqueEquals(uniqueString))
			{
				return false;
			}
		}
		actionsList.push_back(MakeSharedPtr(true, true, uniqueString, miliseconds, function, args...));
		return true;
	}
	//#################################################################################################################################
	static bool Update()
	{

		std::vector< std::shared_ptr<IAction>> temp(actionsList);


		for (std::vector< std::shared_ptr<IAction>>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			if (it->get()->IsReady())
			{
				it->get()->Call();
			}
		}
		std::vector< std::shared_ptr<IAction>>::iterator it = actionsList.begin();
		while (it != actionsList.end())
		{

			if (it->get()->IsEnded())
			{
				it->get()->~IAction();
				/*  delete it->get();*/
				it = actionsList.erase(it);
			}
			else {
				++it;
			}
		}
		return true;
	}
	//#################################################################################################################################
	static void Clear()
	{
		for (std::vector< std::shared_ptr<IAction>>::iterator it = actionsList.begin(); it != actionsList.end(); ++it)
		{

			it->get()->~IAction();

		}
		actionsList.clear();
	}
};
//#################################################################################################################################
std::vector< std::shared_ptr<DelayActions::IAction>> DelayActions::actionsList;