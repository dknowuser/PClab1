//������������ ������ �1
//������������ ����������� ������������� �������� ��������� ������
//��������� ������ �.�. 5307
//������� 9
//����: short int � float
//��� ��������������: ������������� �������� ���� ��� ����� ���, ���������� � ������ ������� 
//�������� � ����������

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
	//������� �����������
	setlocale(LC_ALL, "Russian");
	std::cout.setf(std::ios::scientific);

	std::cout << "������������ �1" << std::endl;
	std::cout << "������������ ����������� ������������� �������� ��������� ������" << std::endl;
	std::cout << "��������� ������ �.�. 5307" << std::endl;
	std::cout << "������� 9" << std::endl;
	std::cout << "����: short int � float" << std::endl;
	std::cout << "��� ��������������: ������������� �������� ���� ��� ����� ���, ���������� � ������ �������" << std::endl;
	std::cout << "�������� � ����������" << std::endl << std::endl;

	Input();

	return 0;
};