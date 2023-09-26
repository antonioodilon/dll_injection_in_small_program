#include <Windows.h>
#include <iostream>

DWORD addr_jmp_back_enh_attack;
DWORD addr_jmp_back_inf_health;
DWORD WINAPI ThreadEnhAttack(LPVOID parameter);
DWORD WINAPI ThreadNoEnemyAttack(LPVOID parameter);
bool HookToProcess(void* hook_address, void* function_new_code, int length_hook);
void FirstEnhAttack();
void SecondNoEnemyAttack();

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadNoEnemyAttack, NULL, 0, NULL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadEnhAttack, NULL, 0, NULL);
	}

	return true;
}

DWORD WINAPI ThreadEnhAttack(LPVOID parameter)
{
	int hook_length = 6;
	DWORD hook_addr_enh_attack = 0x004014EB;
	addr_jmp_back_enh_attack = hook_addr_enh_attack + (DWORD)hook_length;
	bool continue_dll_injection = true;

	MessageBox(NULL, L"First DLL injection", L"Antonio's enhanced attack DLL!", 0);

	bool hook_successful = HookToProcess((void*)hook_addr_enh_attack, (void*)FirstEnhAttack, hook_length);

	if (hook_successful)
	{
		MessageBox(NULL, L"First hook sucessful! Enhancing player's attack...", L"Success!", 0);
	}
	else
	{
		MessageBox(NULL, L"Hook failed! Please double-check your source-code.", L"Fail", 0);
	}

	while (continue_dll_injection)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		Sleep(40);
	}

	Sleep(40);
	FreeLibraryAndExitThread((HMODULE)parameter, 0);
}

DWORD WINAPI ThreadNoEnemyAttack(LPVOID parameter)
{
	int hook_length = 6;
	DWORD hook_address = 0x00401539;
	addr_jmp_back_inf_health = hook_address + (DWORD)hook_length;
	bool continue_dll_injection = true;


	MessageBox(NULL, L"Second DLL Injection", L"Antonio's DLL that turns enemy ineffective!", 0);

	bool hook_successful = HookToProcess((void*)hook_address, (void*)SecondNoEnemyAttack, hook_length);

	if (hook_successful)
	{
		MessageBox(NULL, L"Second hook was successful! New functionality makes player unbeatable.", L"Success", 0);
	}
	else
	{
		MessageBox(NULL, L"Hook failed! Please double-check your source-code.", L"Fail", 0);
	}

	while (continue_dll_injection)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		Sleep(40);
	}

	Sleep(40);
	FreeLibraryAndExitThread((HMODULE)parameter, 0);
}

bool HookToProcess(void* hook_address, void* function_new_code, int length_hook)
{
	if (length_hook == 6)
	{
		DWORD old_protection;
		VirtualProtect(hook_address, length_hook, PAGE_EXECUTE_READWRITE, &old_protection);

		DWORD relative_address = ((DWORD)function_new_code - (DWORD)hook_address) - 5;

		// Try to transform this into an array of bytes?
		memset(hook_address, 0x90, length_hook); //0x90 -> NOP
		*(BYTE*)hook_address = 0xE9; // 0XE9 = opcode for jmp instruction
		*(DWORD*)((DWORD)hook_address + 1) = relative_address;

		DWORD temporary;
		VirtualProtect(hook_address, length_hook, old_protection, &temporary);

		return true;
	}
	else
	{
		return false;
	}
}

_declspec(naked) void FirstEnhAttack()
{
	_asm
	{
		pushad
		mov eax, 0x14
		sub dword ptr ss : [ebp - 0x10] , eax
		popad
		jmp[addr_jmp_back_enh_attack]
	}
}

_declspec(naked) void SecondNoEnemyAttack()
{
	_asm
	{
		pushad
		mov eax, dword ptr ss : [ebp - 0x18]
		sub dword ptr ss : [ebp - 0xC] , 0
		popad
		jmp[addr_jmp_back_inf_health]
	}
}