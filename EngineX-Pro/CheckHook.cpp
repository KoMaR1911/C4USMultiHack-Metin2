#include "stdafx.h"
#include "CheckHook.h"

#define GetAbsolutePtr(InstrPtr, AddrOffset) (*(PVOID*)((PBYTE)InstrPtr + (AddrOffset)))
#define Relative2Absolute(InstrPtr, AddrOffset, InstrLength) (PVOID)((SIZE_T)InstrPtr + (*(PLONG)((PBYTE)InstrPtr + AddrOffset)) + InstrLength)

PVOID FollowTheWhiteRabbit(PVOID Address) {
#ifdef _X86_
    // Проверка на сплайсинг через jmp (0xE9):
    if (*(PBYTE)Address == 0xE9) return Relative2Absolute(Address, 1, 5);

    // Проверка на push -> ret:
    if (*(PBYTE)Address == 0x68 && *((PBYTE)Address + 5) == 0xC3) return GetAbsolutePtr(Address, 1);

    // Проверка на mov eax, Addr -> jmp eax:
    if (*(PBYTE)Address == 0xB8 && *(PWORD)((PBYTE)Address + 5) == 0xE0FF) return GetAbsolutePtr(Address, 1);

    // Проверка на jmp cs:Address:
    if (*(PWORD)Address == 0xFF2E) return GetAbsolutePtr(Address, 2);
#endif

#ifdef _AMD64_
    // Проверка на сплайсинг через jmp (0xE9):
    if (*(PBYTE)Address == 0xE9) return Relative2Absolute(Address, 1, 5);

    // Проверка на mov rax, Addr -> jmp rax:
    if (*(PWORD)Address == 0xB849 && *(PWORD)((PBYTE)Address + 10) == 0xE0FF) return GetAbsolutePtr(Address, 2);

    // Проверка на jmp cs:Address:
    if (*(PWORD)Address == 0x25FF && *(PULONG)((PBYTE)Address + 2) == 0x00000000) return GetAbsolutePtr(Address, 6);

    // Проверка на jmp [rip + 0xNNNNNNNN]:
    if (*(PWORD)Address == 0x25FF && *(PULONG)((PBYTE)Address + 2) != 0x00000000) return Relative2Absolute(Address, 2, 6);

    // Проверка на mov rax, Address -> push rax -> ret:
    if (*(PWORD)Address == 0xB848 && *(PWORD)((PBYTE)Address + 10) == 0xC350) return GetAbsolutePtr(Address, 2);
#endif

    return NULL; // The rabbit's hole has no end...
}

PVOID FindHookDestination(PVOID Address) {
    PVOID JumpTo = FollowTheWhiteRabbit(Address);
    if (JumpTo == NULL) return NULL;

    do {
        PVOID Trampoline = FollowTheWhiteRabbit(JumpTo);
        if (Trampoline == NULL) return JumpTo;
        JumpTo = Trampoline;
    } while (JumpTo);
    return JumpTo;
}