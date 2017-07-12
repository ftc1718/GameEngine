#include "game.h"

int main()
{
	Game game;
	game.start();
	return 0;
}

//#include <iostream>
//#include <functional>
//
//void print_hello() { std::cout << "hello" << std::endl; }
//
//int main()
//{
//	std::function<void()> func = [&]()
//	{ std::cout << "hello" << std::endl; };
//	std::function<void()> f = func;
//	f();
//	std::cin.get();
//	return 0;
//}