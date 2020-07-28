//Файл, содержащий определения функций ввода значений типа short int и float,
//их обработки (инвертирования) и вывода на экран результата

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

//Функции для работы с short int
//Функция ввода значения типа short int
bool InputShortInt(void)
{
	int Value;
	std::cout << "Введите значение: ";
	std::cin >> Value;

	if(std::cin.fail())
	{
		std::cout << "Ошибка! Введено неверное значение." << std::endl;
		getch();
		return false;
	};

	if((Value > 32767) || (Value < -32768))
	{
		std::cout << "Ошибка! Введённое значение превышает границы допустимого диапазона." << std::endl;
		getch();
		return false;
	}

	//Сохраняем значение знака
	Custom::SHORT_INT shInt;
	shInt.Value = 0;
	shInt.Str.Sign = (Value < NULL);

	//Сохраняем значение модуля
	Value = abs(Value);

	//Если значение знака - 0, сохраняем модуль как есть.
	//В противном случае инвертируем все биты модуля и прибавляем к ним единицу
	if(shInt.Str.Sign)
	{
		//Инвертируем
		unsigned int Temp = NULL;
		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			Temp |= (!((Value >> i) & 1) << i);

		//Прибавляем единицу
		Temp++;

		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			shInt.Str.Val |= (((Temp >> i) & 1) << i);
	}
	else
	{
		for(unsigned int i = NULL; i < SHORT_SIZE; i++)
			shInt.Str.Val |= (((Value >> i) & 1) << i);
	};

	//Выводим число на экран
	OutputShortInt(&shInt);

	//Производим операцию
	if(!Invert(false, &shInt))
		return false;

	//Выводим число на экран
	OutputShortInt(&shInt);

	std::cout << std::endl;

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//Функция вывода на экран значения типа short int в десятичном и двоичном видах
void OutputShortInt(Custom::SHORT_INT* Number)
{
	//Выводим в десятичном виде
	std::cout << std::endl << "Число в десятичном виде:" << std::endl;

	//Если значение знака равно нулю, выводим число как есть,
	//в противном случае вычитаем единицу и инвертируем
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

	//Выводим в двоичном виде
	std::cout << "Число в двоичном виде:" << std::endl;
	for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
		std::cout << ((Number->Value >> (SHORT_SIZE - i)) & 1);
	std::cout << std::endl;
};
//----------------------------------------------------------------------------------------------------------------
//Функции для работы с float
//Функция ввода значения типа float
//База - 10 - E?
bool InputFloat(void)
{
	//Вводить как обычное число с точкой?
	float Value;
	std::cout << "Введите значение: ";
	std::cin >> Value;

	if(std::cin.fail())
	{
		std::cout << "Ошибка! Введено неверное значение." << std::endl;
		getch();
		return false;
	};

	//Сохраняем значение знака
	Custom::FLOAT flt;
	flt.Value = 0;
	flt.Un.Str.Sign = (Value < 0);
	Value = abs(Value);

	//Сохраняем целую часть
	unsigned int Int = floor(Value);

	//Сохраняем дробную часть
	float Frac = Value - Int;	

	//Приводим дробную часть к двоичному виду
	unsigned int binFrac = 0;
	for(unsigned int i = 0; i < 23; i++)
	{
		Frac *= 2;
		binFrac |= ((int)floor(Frac) << (22 - i));
		if((int)floor(Frac))
			Frac--;
	};

	//Вычисляем порядок
	int Offset = 0;

	//Если число отлично от нуля
	if(Value)
		if(Int > 0)
		{
			//Если целая часть больше нуля, сдвигаем запятую влево
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
			//Если целая часть равна нулю, сдвигаем запятую вправо
			while(!Int)
			{
				Int = (binFrac & (1 << 22)) >> 22;
				binFrac <<= 1;
				Offset--;
			};
		};

	//Сохраняем порядок
	flt.Un.Str.Power = 127 + Offset;

	//Сохраняем мантиссу
	flt.Un.Mantissa |= binFrac;

	//Выводим число на экран
	OutputFloat(&flt);

	//Производим операцию
	if(!Invert(true, &flt))
		return false;

	//Выводим число на экран
	OutputFloat(&flt);

	std::cout << std::endl;

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//Функция вывода на экран значения типа short int в десятичном и двоичном видах
void OutputFloat(Custom::FLOAT* Number)
{
	std::cout << std::endl << "Число в десятичном виде:" << std::endl;

	if(Number->Un.Str.Sign)
		std::cout << '-';

	//Если мантисса и порядок нулевые, выводим 0
	if((Number->Un.Str.Power == 127) && (!Number->Un.Mantissa))
		std::cout << "0.0E0" << std::endl;
	else
	{
		//Выводим единицу в любом случае
		std::cout << "1.";

		//Выводим мантиссу
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

		//Выводим порядок
		std::cout << (Number->Un.Str.Power - 127) << std::endl;
	};


	std::cout << "Число в двоичном виде:" << std::endl;
	for(unsigned int i = 0; i <= FLOAT_SIZE; i++)
		std::cout << ((Number->Value >> (FLOAT_SIZE - i)) & 1);
	std::cout << std::endl;
};
//----------------------------------------------------------------------------------------------------------------
//Функция, инвертирующая значения всех бит кроме тех, количество и номера которых задаются
bool Invert(bool Float, void* Number)
{
	std::cout << std::endl << "На данном шаге будут инвертированы все биты кроме заданных" << std::endl;

	//Число бит, которые не нужно инвертировать
	unsigned short NumBits;

	if(Float)
	{
		//Введено число типа float
		std::cout << "Введите число бит, которые не нужно инвертировать (от 1 до 32): ";
		std::cin >> NumBits;

		if(std::cin.fail() || !NumBits || (NumBits > FLOAT_SIZE + 1))
		{
			std::cout << "Неверное значение параметра" << std::endl;
			getch();
			return false;
		};

		//Если нужно инвертировать хотя бы один бит
		if(NumBits <= FLOAT_SIZE)
		{
			//Сохраняем номера инвертируемых битов
			unsigned int* Bits = new unsigned int[NumBits];

			//Заполняем массив
			for(unsigned int i = 0; i < NumBits; i++)
				Bits[i] = 33;

			std::cout << "Введите номера бит, которые не нужно инвертировать:" << std::endl;

			for(unsigned int i = 0; i < NumBits; i++)
			{
				unsigned int Temp;
				std::cout << i + 1 << "-й бит: ";
				std::cin >> Temp;

				if(std::cin.fail() || (Temp > FLOAT_SIZE))
				{
					std::cout << "Неверное значение параметра" << std::endl;

					//Освобождаем память
					delete[] Bits;
					getch();
					return false;
				};

				//Если данный номер бита уже введён
				if(Find(Bits, Temp, NumBits))
				{
					i--;
					continue;
				};

				Bits[i] = Temp;
			};

			//Производим инвертирование
			Custom::FLOAT* flt = (Custom::FLOAT*)Number;
			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= FLOAT_SIZE; i++)
				//Проверяем, нужно ли инвертировать текущий бит
				if(Find(Bits, i, NumBits))
					//Не нужно
					Out |= (((flt->Value >> i) & 1) << i);
				else
					//Нужно
					Out |= (!((flt->Value >> i) & 1) << i);

			//Освобождаем память
			delete[] Bits;

			//Сохраняем результат
			flt->Value = Out;
		}
		else
		{
			//Инвертируем все биты
			Custom::FLOAT* flt = (Custom::FLOAT*)Number;

			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= FLOAT_SIZE; i++)
					Out |= (!((flt->Value >> i) & 1) << i);

			//Сохраняем результат
			flt->Value = Out;
		};
	}
	else
	{
		//Введено число типа short int
		std::cout << "Введите число бит, которые не нужно инвертировать (от 1 до 16): ";
		std::cin >> NumBits;

		if(std::cin.fail() || !NumBits || (NumBits > SHORT_SIZE + 1))
		{
			std::cout << "Неверное значение параметра" << std::endl;
			getch();
			return false;
		};

		//Если нужно инвертировать хотя бы один бит
		if(NumBits <= SHORT_SIZE)
		{
			//Сохраняем номера инвертируемых битов
			unsigned int* Bits = new unsigned int[NumBits];

			//Заполняем массив
			for(unsigned int i = 0; i < NumBits; i++)
				Bits[i] = 33;

			std::cout << "Введите номера бит, которые не нужно инвертировать:" << std::endl;

			for(unsigned int i = 0; i < NumBits; i++)
			{
				unsigned int Temp;
				std::cout << i + 1 << "-й бит: ";
				std::cin >> Temp;

				if(std::cin.fail() || (Temp > SHORT_SIZE))
				{
					std::cout << "Неверное значение параметра" << std::endl;

					//Освобождаем память
					delete[] Bits;
					getch();
					return false;
				};

				//Если данный номер бита уже введён
				if(Find(Bits, Temp, NumBits))
				{
					i--;
					continue;
				};

				Bits[i] = Temp;
			};

			//Производим инвертирование
			Custom::SHORT_INT* shInt = (Custom::SHORT_INT*)Number;
			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
				//Проверяем, нужно ли инвертировать текущий бит
				if(Find(Bits, i, NumBits))
					//Не нужно
					Out |= (((shInt->Value >> i) & 1) << i);
				else
					//Нужно
					Out |= (!((shInt->Value >> i) & 1) << i);

			//Освобождаем память
			delete[] Bits;

			//Сохраняем результат
			shInt->Value = Out;
		}
		else
		{
			//Инвертируем все биты
			Custom::SHORT_INT* shInt = (Custom::SHORT_INT*)Number;

			unsigned int Out = 0;
			for(unsigned int i = NULL; i <= SHORT_SIZE; i++)
					Out |= (!((shInt->Value >> i) & 1) << i);

			//Сохраняем результат
			shInt->Value = Out;
		};
	};

	return true;
};
//----------------------------------------------------------------------------------------------------------------
//Функция поиска значения в массиве
bool Find(unsigned int* Bits, unsigned int Value, unsigned int Size)
{
	unsigned int Count = 0;
	while((Count < Size) && (Bits[Count] != Value))
		Count++;

	return ((Count < Size) && (Bits[Count] == Value));
};
//----------------------------------------------------------------------------------------------------------------