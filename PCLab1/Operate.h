//����, ���������� ���������� ������� ����� �������� ���� short int � float,
//�� ��������� (��������������) � ������ �� ����� ����������

#ifndef OPERATE
#define OPERATE
#endif

#ifndef TYPES
#include "Types.h"
#endif

//������� ��� ������ � short int
//������� ����� �������� ���� short int
bool InputShortInt(void);

//������� ������ �� ����� �������� ���� short int � ���������� � �������� �����
void OutputShortInt(Custom::SHORT_INT* Number);

//������� ��� ������ � float
//������� ����� �������� ���� float
bool InputFloat(void);

//������� ������ �� ����� �������� ���� short int � ���������� � �������� �����
void OutputFloat(Custom::FLOAT* Number);

//�������, ������������� �������� ���� ��� ����� ���, ���������� � ������ ������� ��������
bool Invert(bool Float, void* Number);

//������� ������ �������� � �������
bool Find(unsigned int* Bits, unsigned int Value, unsigned int Size);