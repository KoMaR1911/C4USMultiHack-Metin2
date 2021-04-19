#pragma once

#include <Windows.h>

// Получить адрес прыжка, если он есть:
PVOID FollowTheWhiteRabbit(PVOID Address);

// Получить конечный адрес:
PVOID FindHookDestination(PVOID Address);