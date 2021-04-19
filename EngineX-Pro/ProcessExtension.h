#pragma once
class ProcessExtension
{
public:
	static HANDLE CreateThreadSafe(const LPTHREAD_START_ROUTINE func, const LPVOID lParam)
	{
		const HANDLE hThread = CreateThread(nullptr, 0, nullptr, lParam, CREATE_SUSPENDED, nullptr);
		if (!hThread)
		{
			__fastfail(1);
			return 0;
		}

		CONTEXT threadCtx;
		threadCtx.ContextFlags = CONTEXT_INTEGER;
		GetThreadContext(hThread, &threadCtx);
#ifdef _WIN64
		threadCtx.Rax = reinterpret_cast<decltype(threadCtx.Rax)>(func);
#else
		threadCtx.Eax = reinterpret_cast<decltype(threadCtx.Eax)>(func);
		threadCtx.ContextFlags = CONTEXT_INTEGER;
#endif
		SetThreadContext(hThread, &threadCtx);

		if (ResumeThread(hThread) != 1 || ResumeThread(hThread) != NULL)
		{
			__fastfail(1);
			return 0;
		}

		return hThread;
	}
};

