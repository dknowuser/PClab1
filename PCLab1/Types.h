//Файл, в котором содержатся описания типов данных short int и float
#ifndef TYPES
#define TYPES
#endif

namespace Custom
{

	//Занимает 2 байта
	union SHORT_INT
	{
		//Значение, хранящееся во всей области
		unsigned short Value;

		//Структура типа
		struct 
		{
			//Значение
			unsigned short Val:15;

			//Знак
			unsigned short Sign:1;
		} Str;
	};

	//Занимает 4 байта
	union FLOAT
	{
		//Значение, хранящееся во всей области
		unsigned int Value;

		//Структура типа
		union
		{
			//Мантисса - всегда кратно 8!!!
			unsigned int Mantissa:32;

			struct {
				//Задаём нужное смещение
				unsigned short BigOffset:16;

				unsigned short smOff1:1;
				unsigned short smOff2:1;
				unsigned short smOff3:1;
				unsigned short smOff4:1;
				unsigned short smOff5:1;
				unsigned short smOff6:1;
				unsigned short smOff7:1;

				//Порядок
				unsigned short Power:8;	

				//Знак
				unsigned short Sign:1;
			} Str;
		} Un;
	};
};