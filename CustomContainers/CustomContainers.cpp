// CustomContainers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CStack.h"

using namespace std;

int main()
{
	CStack<int> stk = { 1,2,3,4,5,6 };
	//stk.Push(5);
	//stk.Push(7);
	stk.Pop();
	//stk = { 5,6,7 };
	cout << stk.Top();
    //std::cout << "Hello World!\n";
	//func();
}