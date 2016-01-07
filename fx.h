#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>

#pragma once

#define Read(i, d) std::cout << i; std::cin >> d; std::cout
#define Write(i) std::cout << i
#define WriteLn(i) std::cout << i << std::endl
#define Pause() _getch()
#define Randomize() srand(time(0))
#define Localize() setlocale(LC_ALL, "Russian")
#define Lab(i, d) WriteLn("\n#############\n"  << "Лабораторная " << i << "\nЧасть " << d << "\n" << "#############\n");
#define for_each(M) for(int i = 0; i < sizeof(M)/sizeof(M[0]); i++)

#define PI 3.14159f

std::string GenerateSequence(int count, char c){
	std::string s = "";
	for(int i = 0; i < count; i++)
		s.push_back(c);
	return s;
}