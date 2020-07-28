//����, ���������� ����������� ������� ����� �������� ���� short int � float,
//�� ��������� (��������������) � ������ �� ����� ����������

#ifndef OPERATE
#include "Operate.h"
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

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#define SHORT_SIZE 15
#define STRLEN 80
#define FLOAT_SIZE 31

//������� ��� ������ � short int
//������� ����� �������� ���� short int
bool InputShortInt(void)
{
	int Value;
	std::cout << "������� ��������: ";
	std::cin >> Value;

	if(std::cin.fail())
	{
		std::cout << "������! ������� �������� ��������." << std::endl;
		getch();
		return false;
	};

	if((Value > 32767) || (Value < -32768))
	{
		std::cout << "������! �������� �������� ��������� ������� ����������� ���������." << std::endl;
		getch();
		return false;
	}

	//��������� �������� �����
	Custom::SHORT_INT shInt;
	shInt.Value = 0;
	shInt.Str.Sign = (Value < NULL);

	//��������� �������� ������
	Value = abs(Value);

	//���� �������� ����� - 0, ��������� ������ ��� ����.
	//� ��������� ������ ����������� ��� ���� ������ � ���������� � ��� �������
	if(shInt.Str.Sign)
	{
		//�����������
		unsigned int Temp = NULL;
		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			Temp |= (!((Value >> i) & 1) << i);

		//���������� �������
		Temp++;

		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			shInt.Str.Val |= (((Temp >> i) & 1) << i);
	}
	else
	{
		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			shInt.Str.Val |= (((Value >> i) & 1) << i);
	};

	//������� ����� �� �����
	OutputShortInt(&shInt);

	//���������� ��������
	if(!Invert(false, &shInt))
		return false;

	//������� ����� �� �����
	OutputShortInt(&shInt);

	std::cout << std::endl;

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//������� ������ �� ����� �������� ���� short int � ���������� � �������� �����
void OutputShortInt(Custom::SHORT_INT* Number)
{
	//������� � ���������� ����
	std::cout << std::endl << "����� � ���������� ����:" << std::endl;

	//���� �������� ����� ����� ����, ������� ����� ��� ����,
	//� ��������� ������ �������� ������� � �����������
	if(Number->Str.Sign)
	{
		std::cout << '-';
		unsigned int Temp = Number->Str.Val;
		unsigned int Out = NULL;

		if(!Temp)
		{
			Temp = 32767;
			Out |= 32768;
		}
		else
			Temp--;
		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			Out |= (!((Temp >> i) & 1) << i);

		std::cout << Out << std::endl;
	}
	else
		std::cout << Number->Str.Val << std::endl;

	//������� � �������� ����
	std::cout << "����� � �������� ����:" << std::endl;
	for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
		std::cout << ((Number->Value >> (SHORT_SIZE - i)) & 1);
	std::cout << std::endl;
};
//----------------------------------------------------------------------------------------------------------------
//������� ��� ������ � float
//������� ����� �������� ���� float
//���� - 10 - E?
bool InputFloat(void)
{
	//������� ��� ������� ����� � ������?
	float Value;
	std::cout << "������� ��������: ";
	std::cin >> Value;

	if(std::cin.fail())
	{
		std::cout << "������! ������� �������� ��������." << std::endl;
		getch();
		return false;
	};

	//��������� �������� �����
	Custom::FLOAT flt;
	flt.Value = 0;
	flt.Un.Str.Sign = (Value < 0);
	Value = abs(Value);

	//��������� ����� �����
	unsigned int Int = floor(Value);

	//��������� ������� �����
	float Frac = Value - Int;	

	//�������� ������� ����� � ��������� ����
	unsigned int binFrac = 0;
	for(unsigned int i = 0; i < 23; i++)
	{
		Frac *= 2;
		binFrac |= ((int)floor(Frac) << (22 - i));
		if((int)floor(Frac))
			Frac--;
	};

	//��������� �������
	int Offset = 0;

	//���� ����� ������� �� ����
	if(Value)
		if(Int > 0)
		{
			//���� ����� ����� ������ ����, �������� ������� �����
			while(Int > 1)
			{
				binFrac >>= 1;
				binFrac |= (Int & 1) << 22;
				Int >>= 1;
				Offset++;
			};
		}
		else
		{
			//���� ����� ����� ����� ����, �������� ������� ������
			while(!Int)
			{
				Int = (binFrac & (1 << 22)) >> 22;
				binFrac <<= 1;
				Offset--;
			};
		};

	//��������� �������
	flt.Un.Str.Power = 127 + Offset;

	//��������� ��������
	flt.Un.Mantissa |= binFrac;

	//������� ����� �� �����
	OutputFloat(&flt);

	//���������� ��������
	if(!Invert(true, &flt))
		return false;

	//������� ����� �� �����
	OutputFloat(&flt);

	std::cout << std::endl;

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//������� ������ �� ����� �������� ���� short int � ���������� � �������� �����
void OutputFloat(Custom::FLOAT* Number)
{
	std::cout << std::endl << "����� � ���������� ����:" << std::endl;

	if(Number->Un.Str.Sign)
		std::cout << '-';

	//���� �������� � ������� �������, ������� 0
	if((Number->Un.Str.Power == 127) && (!Number->Un.Mantissa))
		std::cout << "0.0E0" << std::endl;
	else
	{
		//������� ������� � ����� ������
		std::cout << "1.";

		//������� ��������
		float Mantissa = 0;
		for(unsigned int i = 0; i < 23; i++)
			Mantissa += ((Number->Un.Mantissa >> (22 - i)) & 1) * pow(0.5, i + 1);
		
		for(unsigned int i = 0; i < 23; i++)
		{
			Mantissa *= 10;
			unsigned short Temp = floor(Mantissa);
			std::cout << Temp;
			Mantissa -= Temp;
		};
		
		std::cout << 'E';

		//������� �������
		std::cout << (Number->Un.Str.Power - 127) << std::endl;
	};


	std::cout << "����� � �������� ����:" << std::endl;
	for(unsigned int i = 0; i <= FLOAT_SIZE; i++)
		std::cout << ((Number->Value >> (FLOAT_SIZE - i)) & 1);
	std::cout << std::endl;
};
//----------------------------------------------------------------------------------------------------------------
//�������, ������������� �������� ���� ��� ����� ���, ���������� � ������ ������� ��������
bool Invert(bool Float, void* Number)
{
	std::cout << std::endl << "�� ������ ���� ����� ������������� ��� ���� ����� ��������" << std::endl;

	//����� ���, ������� �� ����� �������������
	unsigned short NumBits;

	if(Float)
	{
		//������� ����� ���� float
		std::cout << "������� ����� ���, ������� �� ����� ������������� (�� 1 �� 32): ";
		std::cin >> NumBits;

		if(std::cin.fail() || !NumBits || (NumBits > FLOAT_SIZE + 1))
		{
			std::cout << "�������� �������� ���������" << std::endl;
			getch();
			return false;
		};

		//���� ����� ������������� ���� �� ���� ���
		if(NumBits <= FLOAT_SIZE)
		{
			//��������� ������ ������������� �����
			unsigned int* Bits = new unsigned int[NumBits];

			//��������� ������
			for(unsigned int i = 0; i < NumBits; i++)
				Bits[i] = 33;

			std::cout << "������� ������ ���, ������� �� ����� �������������:" << std::endl;

			for(unsigned int i = 0; i < NumBits; i++)
			{
				unsigned int Temp;
				std::cout << i + 1 << "-� ���: ";
				std::cin >> Temp;

				if(std::cin.fail() || (Temp > FLOAT_SIZE))
				{
					std::cout << "�������� �������� ���������" << std::endl;

					//����������� ������
					delete[] Bits;
					getch();
					return false;
				};

				//���� ������ ����� ���� ��� �����
				if(Find(Bits, Temp, NumBits))
				{
					i--;
					continue;
				};

				Bits[i] = Temp;
			};

			//���������� ��������������
			Custom::FLOAT* flt = (Custom::FLOAT*)Number;
			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= FLOAT_SIZE; i++)
				//���������, ����� �� ������������� ������� ���
				if(Find(Bits, i, NumBits))
					//�� �����
					Out |= (((flt->Value >> i) & 1) << i);
				else
					//�����
					Out |= (!((flt->Value >> i) & 1) << i);

			//����������� ������
			delete[] Bits;

			//��������� ���������
			flt->Value = Out;
		}
		else
		{
			//����������� ��� ����
			Custom::FLOAT* flt = (Custom::FLOAT*)Number;

			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= FLOAT_SIZE; i++)
					Out |= (!((flt->Value >> i) & 1) << i);

			//��������� ���������
			flt->Value = Out;
		};
	}
	else
	{
		//������� ����� ���� short int
		std::cout << "������� ����� ���, ������� �� ����� ������������� (�� 1 �� 16): ";
		std::cin >> NumBits;

		if(std::cin.fail() || !NumBits || (NumBits > SHORT_SIZE + 1))
		{
			std::cout << "�������� �������� ���������" << std::endl;
			getch();
			return false;
		};

		//���� ����� ������������� ���� �� ���� ���
		if(NumBits <= SHORT_SIZE)
		{
			//��������� ������ ������������� �����
			unsigned int* Bits = new unsigned int[NumBits];

			//��������� ������
			for(unsigned int i = 0; i < NumBits; i++)
				Bits[i] = 33;

			std::cout << "������� ������ ���, ������� �� ����� �������������:" << std::endl;

			for(unsigned int i = 0; i < NumBits; i++)
			{
				unsigned int Temp;
				std::cout << i + 1 << "-� ���: ";
				std::cin >> Temp;

				if(std::cin.fail() || (Temp > SHORT_SIZE))
				{
					std::cout << "�������� �������� ���������" << std::endl;

					//����������� ������
					delete[] Bits;
					getch();
					return false;
				};

				//���� ������ ����� ���� ��� �����
				if(Find(Bits, Temp, NumBits))
				{
					i--;
					continue;
				};

				Bits[i] = Temp;
			};

			//���������� ��������������
			Custom::SHORT_INT* shInt = (Custom::SHORT_INT*)Number;
			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
				//���������, ����� �� ������������� ������� ���
				if(Find(Bits, i, NumBits))
					//�� �����
					Out |= (((shInt->Value >> i) & 1) << i);
				else
					//�����
					Out |= (!((shInt->Value >> i) & 1) << i);

			//����������� ������
			delete[] Bits;

			//��������� ���������
			shInt->Value = Out;
		}
		else
		{
			//����������� ��� ����
			Custom::SHORT_INT* shInt = (Custom::SHORT_INT*)Number;

			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
					Out |= (!((shInt->Value >> i) & 1) << i);

			//��������� ���������
			shInt->Value = Out;
		};
	};

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//������� ������ �������� � �������
bool Find(unsigned int* Bits, unsigned int Value, unsigned int Size)
{
	unsigned int Count = 0;
	while((Count < Size) && (Bits[Count] != Value))
		Count++;

	return ((Count < Size) && (Bits[Count] == Value));
};
//----------------------------------------------------------------------------------------------------------------