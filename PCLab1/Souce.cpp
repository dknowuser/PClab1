//Лабораторная работа №1
//Исследование внутреннего представления форматов различных данных
//Выполнила Марчук Л.Б. 5307
//Вариант 9
//Типы: short int и float
//Вид преобразования: Инвертировать значения всех бит кроме тех, количество и номера которых 
//задаются с клавиатуры

#ifndef SOURCE
#define SOURCE 
#endif

#ifndef _INC_CONIO
#include <conio.h>
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef TYPES
#include "Types.h"
#endif

#ifndef INPUT
#include "Input.h"
#endif

int main(void)
{
	//Выводим приветствие
	setlocale(LC_ALL, "Russian");
	std::cout.setf(std::ios::scientific);

	std::cout << "Лабораторная №1" << std::endl;
	std::cout << "Исследование внутреннего представления форматов различных данных" << std::endl;
	std::cout << "Выполнила Марчук Л.Б. 5307" << std::endl;
	std::cout << "Вариант 9" << std::endl;
	std::cout << "Типы: short int и float" << std::endl;
	std::cout << "Вид преобразования: Инвертировать значения всех бит кроме тех, количество и номера которых" << std::endl;
	std::cout << "задаются с клавиатуры" << std::endl << std::endl;

	Input();

	return 0;
};