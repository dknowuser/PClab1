//����, � ������� ���������� �������� ����� ������ short int � float
#ifndef TYPES
#define TYPES
#endif

namespace Custom
{

	//�������� 2 �����
	union SHORT_INT
	{
		//��������, ���������� �� ���� �������
		unsigned short Value;

		//��������� ����
		struct 
		{
			//��������
			unsigned short Val:15;

			//����
			unsigned short Sign:1;
		} Str;
	};

	//�������� 4 �����
	union FLOAT
	{
		//��������, ���������� �� ���� �������
		unsigned int Value;

		//��������� ����
		union
		{
			//�������� - ������ ������ 8!!!
			unsigned int Mantissa:32;

			struct {
				//����� ������ ��������
				unsigned short BigOffset:16;

				unsigned short smOff1:1;
				unsigned short smOff2:1;
				unsigned short smOff3:1;
				unsigned short smOff4:1;
				unsigned short smOff5:1;
				unsigned short smOff6:1;
				unsigned short smOff7:1;

				//�������
				unsigned short Power:8;	

				//����
				unsigned short Sign:1;
			} Str;
		} Un;
	};
};