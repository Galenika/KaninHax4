#pragma once
#include "virtual_table_functions.h"

class center_print_t // *reinterpret_cast<CCenterPrint**>(FindPattern("client.dll", "A1 ? ? ? ? B9 ? ? ? ? FF 50 1C E8")) + 6
{
public:
	void print(char16_t* _str)
	{
		call_virtual_function<void, 3>(this, _str);
	}
};