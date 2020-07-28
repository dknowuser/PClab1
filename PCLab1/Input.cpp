//����, ���������� ����������� ������� �����

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
	//������, �� �������� ������������ ����� �� �����
	char ch = 'Y';

	while((ch == 'y') || (ch == 'Y'))
	{
		//����� ����
		unsigned short Type = 0;
		std::cout << "�������� ���: 1 - short int, 2 - float:" << std::endl;
		std::cin >> Type;

		if(Type == 1)
		{
			//������� short int
			if(!InputShortInt())
				break;
		}
		else
			if(Type == 2)
			{
				//������� float
				if(!InputFloat())
					break;
			}
			else
			{
				//����� �������� ��������
				std::cout << "������! �������� �������� ���������." << std::endl;
				getch();
				break;
			};

		//����� �� ���������
		std::cout << "���������? (Y/N):" << std::endl;
		std::cout << ">> ";
		std::cin >> ch;
	};
};