#include <Windows.h>
#include <iostream>
#include "Bitset.h"
#include "Assert.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	AomiLibrary::Bitset<65> bitset;
	std::cout << bitset << std::endl;

	bitset.Flip(0);
	bitset.Flip(2);
	bitset.Flip();
	bitset.Set(true);
	bitset.Flip(64);
	std::cout << bitset << std::endl;

	ASSERT_MSG(false, "メッセージだよ");

	(void)getchar();
	return 0;
}

