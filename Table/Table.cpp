#include "Table.h"
#include <iostream>
//#include <fstream>
//#include <cstdlib>

void main()
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		std::cout << "�������� �������:" << std::endl;
		std::cout << "1. TScanTable" << std::endl;
		std::cout << "2. TSortTable" << std::endl;
		std::cout << "3. TTreeTable" << std::endl;
		std::cout << "4. THashTable" << std::endl;
		std::cout << "0. Exit" << std::endl;
		int n;
		std::cin >> n;
		if (n == 1)
		{
			std::cout << "������� ������ �������:";
			int size, key, val;
			std::cin >> size;
			TScanTable T(size);
			std::cout << "������� �������� ������:";
			std::cin >> key;
			std::cout << "������� �������� ��������:";
			std::cin >> val;
			while(!T.IsFull())
			{
				int random_number = 1 + rand() % key;
				TRecord rec;
				rec.key = random_number;
				random_number = 1 + rand() % val;
				rec.val = random_number;
				T.Insert(rec);
			}
			T.Print();
			std::cout << "Eff: " << T.GetEff() << std::endl;
			T.CLiarEff();
			while (true)
			{
				std::cout << "1. Delete" << std::endl;
				std::cout << "2. Insert" << std::endl;
				std::cout << "3. Find" << std::endl;
				std::cout << "0. Exit" << std::endl;
				int n1;
				std::cin >> n1;
				if (n1 == 1)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					T.Delete(key);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 2)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					std::cout << "������� ��������: ";
					std::cin >> val;
					TRecord rec;
					rec.key = key;
					rec.val = val;
					T.Insert(rec);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 3)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					if (T.Find(key))
						std::cout << "����" << std::endl;
					else
						std::cout << "���" << std::endl;
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 0)
				{
					break;
				}
			}
		}
		if (n == 2)
		{
			std::cout << "������� ������ �������:";
			int size, key, val;
			std::cin >> size;
			TSortTable T(size);
			std::cout << "������� �������� ������:";
			std::cin >> key;
			std::cout << "������� �������� ��������:";
			std::cin >> val;
			while(!T.IsFull())
			{
				int random_number = 1 + rand() % key;
				TRecord rec;
				rec.key = random_number;
				random_number = 1 + rand() % val;
				rec.val = random_number;
				T.Insert(rec);
			}
			T.Print();
			std::cout << "Eff: " << T.GetEff() << std::endl;
			T.CLiarEff();
			while (true)
			{
				std::cout << "1. Delete" << std::endl;
				std::cout << "2. Insert" << std::endl;
				std::cout << "3. Find" << std::endl;
				std::cout << "0. Exit" << std::endl;
				int n1;
				std::cin >> n1;
				if (n1 == 1)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					T.Delete(key);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 2)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					std::cout << "������� ��������: ";
					std::cin >> val;
					TRecord rec;
					rec.key = key;
					rec.val = val;
					T.Insert(rec);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 3)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					if (T.Find(key))
						std::cout << "����" << std::endl;
					else
						std::cout << "���" << std::endl;
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 0)
				{
					break;
				}
			}
		}
		if (n == 3)
		{
			int  size,key, val;
			std::cout << "������� ���������� ������:";
			std::cin >> size;
			TTreeTable T(size);
			std::cout << "������� �������� ������:";
			std::cin >> key;
			std::cout << "������� �������� ��������:";
			std::cin >> val;
			while(!T.IsFull())
			{
				int random_number = 1 + rand() % key;
				TRecord rec;
				rec.key = random_number;
				random_number = 1 + rand() % val;
				rec.val = random_number;
				T.Insert(rec);
			}
			T.Print();
			std::cout << "Eff: " << T.GetEff() << std::endl;
			T.CLiarEff();
			while (true)
			{
				std::cout << "1. Delete" << std::endl;
				std::cout << "2. Insert" << std::endl;
				std::cout << "3. Find" << std::endl;
				std::cout << "4. Print" << std::endl;
				std::cout << "0. Exit" << std::endl;
				int n1;
				std::cin >> n1;
				if (n1 == 1)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					T.Delete(key);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 2)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					std::cout << "������� ��������: ";
					std::cin >> val;
					TRecord rec;
					rec.key = key;
					rec.val = val;
					T.Insert(rec);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 3)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					if (T.Find(key))
						std::cout << "����" << std::endl;
					else
						std::cout << "���" << std::endl;
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 4)
				{
					T.Save("text.txt");
				}
				if (n1 == 0)
				{
					break;
				}
			}
		}
		if (n == 4)
		{
			std::cout << "������� ������ �������:";
			int size, step, key, val;
			std::cin >> size;
			std::cout << "������� ��� �������:";
			std::cin >> step;
			THashTable T(size, step);
			std::cout << "������� �������� ������:";
			std::cin >> key;
			std::cout << "������� �������� ��������:";
			std::cin >> val;
			while(!T.IsFull())
			{
				int random_number = 1 + rand() % key;
				TRecord rec;
				rec.key = random_number;
				random_number = 1 + rand() % val;
				rec.val = random_number;
				T.Insert(rec);
			}
			T.Print();
			std::cout << "Eff: " << T.GetEff() << std::endl;
			T.CLiarEff();
			while (true)
			{
				std::cout << "1. Delete" << std::endl;
				std::cout << "2. Insert" << std::endl;
				std::cout << "3. Find" << std::endl;
				std::cout << "0. Exit" << std::endl;
				int n1;
				std::cin >> n1;
				if (n1 == 1)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					T.Delete(key);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 2)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					std::cout << "������� ��������: ";
					std::cin >> val;
					TRecord rec;
					rec.key = key;
					rec.val = val;
					T.Insert(rec);
					T.Print();
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 3)
				{
					std::cout << "������� ����: ";
					std::cin >> key;
					if (T.Find(key))
						std::cout << "����" << std::endl;
					else
						std::cout << "���" << std::endl;
					std::cout << "Eff: " << T.GetEff() << std::endl;
					T.CLiarEff();
				}
				if (n1 == 0)
				{
					break;
				}
			}
		}
		if (n == 0)
		{
			std::cout << std::endl;
			std::cout << "Thanks!" << std::endl;
			break;
		}
	}
}