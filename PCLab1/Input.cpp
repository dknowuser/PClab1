//Файл, содержащий определение функции ввода

#ifndef INPUT
#include "Input.h"
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

#ifndef OPERATE
#include "Operate.h"
#endif

void Input(void)
{
	//Символ, по которому производится выход из цикла
	char ch = 'Y';

	while((ch == 'y') || (ch == 'Y'))
	{
		//Выбор типа
		unsigned short Type = 0;
		std::cout << "Выберите тип: 1 - short int, 2 - float:" << std::endl;
		std::cin >> Type;

		if(Type == 1)
		{
			//Выбрали short int
			if(!InputShortInt())
				break;
		}
		else
			if(Type == 2)
			{
				//Выбрали float
				if(!InputFloat())
					break;
			}
			else
			{
				//Ввели неверное значение
				std::cout << "Ошибка! Неверное значение параметра." << std::endl;
				getch();
				break;
			};

		//Нужно ли повторить
		std::cout << "Повторить? (Y/N):" << std::endl;
		std::cout << ">> ";
		std::cin >> ch;
	};
};