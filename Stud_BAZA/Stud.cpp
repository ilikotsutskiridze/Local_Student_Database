#include "Stud.h"

void Stud::kolneudstud(bool& exit)
{
	cout << "Введите название базы данных, из которой будет произведен поиск двоечников ;) : ";
	string NameFile;
	cin >> NameFile;

	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream RidFile(NameFile);
	string strInput;
	vector<string> mass(100);
	size_t buf = 0;
	vector<vector<string>> massivik;

	if (!RidFile)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		int j = -1, k = -1;

		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{
			RidFile >> strInput;// то перемещаем эти данные в строку, которую затем запишем в массив

			if (strInput.find("_") != -1)
			{
				j++;
				k++;
			}

			if ((k != -1) || (!(RidFile)))
			{
				mass.resize(buf + 1);
				massivik.push_back(mass);
				k = -1;
				mass.clear();
				buf = -1;
				mass.resize(100);
			}

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);
		RidFile.close();

		size_t kolNed = 0;

		string name0 = "0", name1 = "1", name2 = "2";

			
		for (size_t a = 1; a < massivik.size(); ++a)
		{
			if (unsigned char(massivik[a][massivik[a].size() - 2][0]) > 47 && unsigned char(massivik[a][massivik[a].size() - 2][0]) < 58)
			{
				for (size_t b = 4; b < massivik[a].size(); b += 3)
				{
					if (massivik[a][b].find(name0) != -1)
					{
						kolNed++;
						break;
					}

					if (massivik[a][b].find(name1) != -1)
					{
						kolNed++;
						break;
					}

					if (massivik[a][b].find(name2) != -1)
					{
						kolNed++;
						break;
					}
				}
				
			}
			else
			{
				for (size_t b = 4; b < massivik[a].size(); b += 2)
				{
					if (massivik[a][b].find(name0) != -1)
					{
						kolNed++;
						break;
					}

					if (massivik[a][b].find(name1) != -1)
					{
						kolNed++;
						break;
					}

					if (massivik[a][b].find(name2) != -1)
					{
						kolNed++;
						break;
					}
				}
				
			};
			
		}
		cout << "Всего в данной БД студентов с неудовлетворительными оценками: " << kolNed << endl;
	}
}

void Stud::poisk(bool& exit)
{
	cout << "Введите название базы данных, в которой будет произведён поиск студента по фамилии: ";
	string NameFile;
	cin >> NameFile;

	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream RidFile(NameFile);
	string strInput;
	vector<string> mass(100);
	size_t buf = 0;
	vector<vector<string>> massivik;

	if (!RidFile)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		int j = -1, k = -1;

		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{
			RidFile >> strInput;// то перемещаем эти данные в строку, которую затем запишем в массив

			if (strInput.find("_") != -1)
			{
				j++;
				k++;
			}

			if ((k != -1) || (!(RidFile)))
			{
				mass.resize(buf + 1);
				massivik.push_back(mass);
				k = -1;
				mass.clear();
				buf = -1;
				mass.resize(100);
			}

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);
		RidFile.close();

		string name = "";
		cout << "Введите ФИО студента:";
		cin.ignore();
		getline(cin, name);

		for (size_t i = 0; i < name.size(); ++i)
		{
			if (name[i] == ' ')
			{
				name[i] = '_';
			}
		}


		vector<vector<string>> Gmassivik;


		for (size_t a = 1; a < massivik.size(); ++a)
		{

			for (size_t b = 0; b < massivik[a].size(); ++b)
			{
				if (massivik[a][b].find(name) != -1)
				{
					Gmassivik.push_back(massivik[a]);
					break;
				}
			}
		}
		if (Gmassivik.size() != 0)
		{
			cout << "Студент найден! Вот его данные:\n";

			for (size_t a = 0; a < Gmassivik.size(); ++a)
			{
				for (size_t b = 0; b < Gmassivik[a].size(); ++b)
				{
					cout << Gmassivik[a][b] << endl;
				}
			}
		}
		else
			cout << "Боюсь, такого студента в базе нет\n";
	}
}