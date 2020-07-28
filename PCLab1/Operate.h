//Файл, содержащий объявления функций ввода значений типа short int и float,
//их обработки (инвертирования) и вывода на экран результата

#ifndef OPERATE
#define OPERATE
#endif

#ifndef TYPES
#include "Types.h"
#endif

//Функции для работы с short int
//Функция ввода значения типа short int
bool InputShortInt(void);

//Функция вывода на экран значения типа short int в десятичном и двоичном видах
void OutputShortInt(Custom::SHORT_INT* Number);

//Функции для работы с float
//Функция ввода значения типа float
bool InputFloat(void);

//Функция вывода на экран значения типа short int в десятичном и двоичном видах
void OutputFloat(Custom::FLOAT* Number);

//Функция, инвертирующая значения всех бит кроме тех, количество и номера которых задаются
bool Invert(bool Float, void* Number);

//Функция поиска значения в массиве
bool Find(unsigned int* Bits, unsigned int Value, unsigned int Size);