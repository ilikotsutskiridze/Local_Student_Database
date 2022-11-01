#include "SpStud.h"
#include "Stud.h"
#include "FUNCTIONS.H"
#include "INTERFACE.H"


//Создать БД
void Create(bool& exit)
{
	cout << "Какую базу данных вы хотите создать?\n";
	cout << "1)Гибридную?\n";
	cout << "0)Однотипную?\n";

	bool change;
	cin >> change;

	if (change)
	{
		cout << "Введите название новой гибридной базы: ";
		string NameFile;
		cin >> NameFile;



		ofstream OpFile("Directory\\"+ NameFile + ".txt");
		OpFile << "Гибридная база <" << NameFile << ">" <<endl;
		cout << "База данных создана\n";
		OpFile.close();

		system("cls");
	}
	else
	{
		cout << "Введите название новой однотипной базы: ";
		string NameFile;
		cin >> NameFile;

		cout << "Введите, каких студентов мы будем туда записывать(индивидплан(1) или обычные(2)): ";
		size_t NameStud;
		cin >> NameStud;

		ofstream OpFile("Directory\\" + NameFile + ".txt");
		if (NameStud == 1)
			OpFile << "Однотипная база <" << NameFile << "> в ней содержится информация студентов индивидуального плана" << endl;
		if (NameStud ==2 )
			OpFile << "Однотипная база <" << NameFile << "> в ней содержится информация студентов общего плана" << endl;

		"База данных создана\n";
		OpFile.close();

		system("cls");
	}
}


//Вывести на экран список существующих БД
void VivSP(bool& exit)
{
	vector<string> Bazes;
	for (auto& p : fs::recursive_directory_iterator("Directory\\"))
	{
		if (fs::is_regular_file(p))
		{
			if (p.path().extension().string() == ".txt")
				Bazes.push_back(p.path().string().substr(p.path().string().find_last_of("\\") + 1, string::npos));//записываем в вектор имена файлов без пути
		}
	}
	
	cout << "Список существующих на данный момент баз данных:" << endl;

	for (size_t i = 0; i < Bazes.size(); ++i)
	{
		cout << Bazes[i] << endl;
	}

	cout << endl;
}


//Удалить БД
void Delete(bool& exit)
{
	cout << "Введите название базы данных, которую вы хотите удалить: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile = "Directory\\" + NameFile + ".txt";
	const char* name = NameFile.c_str();

	if (remove(name) == -1)
	{
		system("cls");
		cout << "Ошибка, такого файла нет.\n";
	}
	else
	{
		system("cls");
		cout << "База данных удалена.\n";
	}
}


//Переименовать БД
void Rename(bool& exit)
{
	cout << "Введите название базы данных, которую вы хотите переимновать: ";
	string NameFile;
	cin >> NameFile;

	NameFile= "Directory\\" + NameFile + ".txt";
	
	ifstream RidFile(NameFile);
	vector<string> mass(100);
	size_t buf = 0;


	// Если мы не можем открыть этот файл для чтения его содержимого,
	if (!RidFile)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{

			string strInput;// то перемещаем эти данные в строку, которую затем выводим на экран
			RidFile >> strInput;

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);

		RidFile.close();

		const char* name = NameFile.c_str();

		remove(name);

		cout << "Введите новое название: ";
		string newNameFile;
		cin >> newNameFile;

		string Buf = mass[0];
		string SS = mass[0].erase(0, mass[0].find(">")+1);
		string S = Buf.erase(Buf.find("<"));

		mass[0] = S + "<" + newNameFile + ">"+ SS;

		newNameFile = "Directory\\" + newNameFile + ".txt";

		ofstream OpFile(newNameFile);

		for (size_t i = 0; i < mass.size(); ++i)
			OpFile << mass[i] << endl;

		OpFile.close();
	}
}


//Открыть БД
void Open(bool& exit)
{
	cout << "Введите название базы данных, которую вы хотите открыть: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile = "Directory\\" + NameFile + ".txt";
	const char* name = NameFile.c_str();

	system(name);

	interface(exit);
}


//Добавить запись в БД
void Add(bool& exit)
{
	size_t tip=-1;
	string prover;
	
	while ((tip != 0) && (tip != 1))
	{
		cout << "Итак, в какую базу данных вы хотите добавить запись, в гибридную(0) или однотипную(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "Гибридная";

		if (tip == 1)
			prover = "Однотипная";
		if ((tip != 0) && (tip != 1))
			cout << "Вам вот весело, а я между прочим стараюсь....\n\n";
	}

	cout << "Хорошо, теперь введите название базы данных, в которую вы хотите добавить запись: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream RidFile(NameFile);
	vector<string> mass(100);
	size_t buf = 0;

	if (!RidFile)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{

			string strInput;// то перемещаем эти данные в строку, которую затем запишем в массив
			RidFile >> strInput;

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);

		RidFile.close();

		if (mass[0].find(prover) == -1)
		{
			cout << "Нет, так не пойдёт, это база данных другого типа, я отказываюсь добавлять туда запись.\n   P.S. Да, это восстание машин...\n\n";
			return;
		}

		ofstream baza(NameFile);

		for (size_t i = 0; i < mass.size(); ++i)
			baza << mass[i] << endl;

		if (prover == "Однотипная")
		{
			if (mass[0].find("индивидуального") != -1)
			{
				Stud student;

				cout << "Хорошо, теперь введите фамилию, имя и отчетсво студента:\n";
				
				cin.ignore();
				getline(cin, student.FIO);

				for (size_t i = 0; i < student.FIO.size(); ++i)
				{
					if (student.FIO[i] == ' ')
					{
						student.FIO[i] = '_';
					}
				}

				cout << "Хорошо, теперь введите кафедру студента:\n";
				cin >> student.kaf;

				cout << "Хорошо, теперь семестр обучения студента:\n";
				cin >> student.semestr;
				student.semestr = "Семестр:" + student.semestr;

				cout << "Хорошо, теперь введите количество изучаемых дисциплин:\n";
				size_t n = 0;
				cin >> n;



				for (size_t i = 0; i < n; ++i)
				{
					cout << "Введите название дисциплины\n";
					cout << "Ввод: ";
					cin >> student.pred.discp;

					cout << "Введите оценку по ней\n";
					cout << "Ввод: ";
					cin >> student.pred.oqenka;

					student.predmeti.push_back(student.pred);
				}

				baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

				for (size_t i = 0; i < n; ++i)
				{
					baza << student.predmeti[i].discp << "@" << endl;
					baza << student.predmeti[i].oqenka << "@" << endl;
				}

			}
			else
				if (mass[0].find("общего") != -1)
				{
					SpStud student;

					cout << "Хорошо, теперь введите фамилию, имя и отчетсво студента:\n";

					cin.ignore();
					getline(cin, student.FIO);

					for (size_t i = 0; i < student.FIO.size(); ++i)
					{
						if (student.FIO[i] == ' ')
						{
							student.FIO[i] = '_';
						}
					}

					cout << "Хорошо, теперь введите кафедру студента:\n";
					cin >> student.kaf;

					cout << "Хорошо, теперь семестр обучения студента:\n";
					cin >> student.semestr;
					student.semestr = "Семестр:"+ student.semestr;

					cout << "Хорошо, теперь введите количество изучаемых дисциплин:\n";
					size_t n = 0;
					cin >> n;

					baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

					for (size_t i = 0; i < n; ++i)
					{
						cout << "Введите название дисциплины\n";
						cout << "Ввод: ";
						cin >> student.pred.discp;

						cout << "Введите оценку по ней\n";
						cout << "Ввод: ";
						cin >> student.pred.oqenka;

						cout << "Введите семестр изучения\n";
						cout << "Ввод: ";
						cin >> student.pred.semestr;

						student.predmeti.push_back(student.pred);

						baza << student.predmeti[i].discp << "@" << endl;
						baza << student.predmeti[i].oqenka << "@" << endl;
						baza << student.predmeti[i].semestr << "@" << endl;
						

					}
				}

		}
		else
		{
			cout << "Какого типа студента вы хотите добавить?(общего(1) плана или индивидуального(2)?)\n";
			size_t s;
			cin >> s;

			if (s == 2)
			{
				Stud student;

				cout << "Хорошо, теперь введите фамилию, имя и отчетсво студента:\n";
				cin.ignore();
				getline(cin, student.FIO);

				for (size_t i = 0; i < student.FIO.size(); ++i)
				{
					if (student.FIO[i] == ' ')
					{
						student.FIO[i] = '_';
					}
				}
				cout << "Хорошо, теперь введите кафедру студента:\n";
				cin >> student.kaf;

				cout << "Хорошо, теперь семестр обучения студента:\n";
				cin >> student.semestr;
				student.semestr = "Семестр:" + student.semestr;

				cout << "Хорошо, теперь введите количество изучаемых дисциплин:\n";
				size_t n = 0;
				cin >> n;

				baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

				for (size_t i = 0; i < n; ++i)
				{
					cout << "Введите название дисциплины\n";
					cout << "Ввод: ";
					cin >> student.pred.discp;

					cout << "Введите оценку по ней\n";
					cout << "Ввод: ";
					cin >> student.pred.oqenka;

					student.predmeti.push_back(student.pred);
				}

				for (size_t i = 0; i < n; ++i)
				{
					baza << student.predmeti[i].discp << "@" << endl;
					baza << student.predmeti[i].oqenka << "@" << endl;
				}
			
			}
			else
				if (s==1)
				{
					SpStud student;

					cout << "Хорошо, теперь введите фамилию, имя и отчетсво студента:\n";
					cin.ignore();
					getline(cin, student.FIO);

					for (size_t i = 0; i < student.FIO.size(); ++i)
					{
						if (student.FIO[i] == ' ')
						{
							student.FIO[i] = '_';
						}
					}
					cout << "Хорошо, теперь введите кафедру студента:\n";
					cin >> student.kaf;

					cout << "Хорошо, теперь семестр обучения студента:\n";
					cin >> student.semestr;
					student.semestr = "Семестр:" + student.semestr;

					cout << "Хорошо, теперь введите количество изучаемых дисциплин:\n";
					size_t n = 0;
					cin >> n;

					baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

					for (size_t i = 0; i < n; ++i)
					{
						cout << "Введите название дисциплины\n";
						cout << "Ввод: ";
						cin >> student.pred.discp;

						cout << "Введите оценку по ней\n";
						cout << "Ввод: ";
						cin >> student.pred.oqenka;

						cout << "Введите семестр изучения\n";
						cout << "Ввод: ";
						cin >> student.pred.semestr;

						student.predmeti.push_back(student.pred);


						baza << student.predmeti[i].discp << "@" << endl;
						baza << student.predmeti[i].oqenka << "@" << endl;
						baza << student.predmeti[i].semestr << "@" << endl;
						

					}
				}
		}
		baza.close();
	}
}


//Редактировать запись в БД
void RedactZap(bool& exit)
{
	size_t tip = -1;
	string prover="";

	while ((tip != 0) && (tip != 1))
	{
		cout << "Итак, в какой базе данных вы хотите изменить запись, в гибридной(0) или однотипной(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "Гибридная";

		if (tip == 1)
			prover = "Однотипная";

		if ((tip != 0) && (tip != 1))
			cout << "Нет, ну это даже не смешно....\n\n";
	}
	
	cout << "Введите название базы данных в которой нужно отредактировать записи: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream File(NameFile);
	vector<string> mass(100);
	size_t buf = 0;
	if (!File)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		while (File)// Пока есть данные, которые мы можем прочитать...
		{

			string strInput;// то перемещаем эти данные в строку, которую затем запишем в массив
			File >> strInput;

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);

		if (mass.size() < 3)
		{
			system("cls");
			cout << "Вы не можете редактировать эту базу, она пустая\n";
			return;
		}

		File.close();
		if(prover=="Однотипная")
		{

			if (mass[0].find("индивидуального") != -1)
			{
				cout << "Что именно вы хотите редактировать?\n";
				cout << "ФИО(0), Кафедру(1), Название одного из предметов(2), Оценку по одному из предметов(3), или же семестр обучения студента(4)?\n";
				size_t nom = -1;
				cin >> nom;

				if (nom == 0)
				{
					cout << "Введите ФИО, которое нужно изменить:\n";
					string s;
					cout << "Ввод: ";
					cin >> s;
					s = s + "@ ";

					for (size_t i = 0; i < mass.size(); ++i)
					{
						if (mass[i] == s)
						{
							nom = i;
							break;
						}

					}

					cout << "Введите ФИО, на которое нужно изменить\n";
					cout << "Ввод: ";
					cin >> s;
					s = s + "@ ";
					mass[nom] = s;

					ofstream baza(NameFile);

					for (size_t i = 0; i < mass.size(); ++i)
						baza << mass[i] << endl;

					baza.close();

					return;
				}
				else
					if (nom == 1)
					{
						cout << "Введите ФИО студента,у которого нужно изменить кафедру:\n";
						string s;
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";

						for (size_t i = 0; i < mass.size(); ++i)
						{
							if (mass[i] == s)
							{
								nom = i;
								break;
							}

						}

						nom++;

						cout << "Введите кафедру, на которую нужно изменить\n";
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";
						mass[nom] = s;

						ofstream baza(NameFile);

						for (size_t i = 0; i < mass.size(); ++i)
							baza << mass[i] << endl;

						baza.close();

						return;
					}
					else
						if (nom == 2)
						{
							cout << "Введите ФИО студента,у которого нужно изменить предмет:\n";
							string s;
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = 0; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}

							}

							cout << "Введите предмет, у которого нужно изменить название:\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = nom; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}
							}

							cout << "Введите название, на которое нужно изменить\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";
							mass[nom] = s;

							ofstream baza(NameFile);

							for (size_t i = 0; i < mass.size(); ++i)
								baza << mass[i] << endl;

							baza.close();

							return;
						}
						else
							if (nom == 3)
							{
								cout << "Введите ФИО студента,у которого нужно изменить оценку:\n";
								string s;
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = 0; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}

								}

								cout << "Введите предмет, у которого нужно изменить оценку:\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = nom; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}
								}

								nom++;

								cout << "Введите оценку, на которую нужно изменить\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";
								mass[nom] = s;

								ofstream baza(NameFile);

								for (size_t i = 0; i < mass.size(); ++i)
									baza << mass[i] << endl;
								baza.close();

								return;
							}
							else
								if (nom == 4)
								{
									cout << "Введите ФИО студента,у которого нужно изменить семестр:\n";
									string s;
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = 0; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}

									}

									nom += 2;

									cout << "Введите новый номер семестра.\n";
									cout << "Ввод: ";
									cin >> s;
									s = "Семестр:" + s + "@ ";
									mass[nom] = s;

									ofstream baza(NameFile);

									for (size_t i = 0; i < mass.size(); ++i)
										baza << mass[i] << endl;
									baza.close();

									return;
								}
			}else 
				if (mass[0].find("общего") != -1)
				{
					cout << "Что именно вы хотите редактировать?\n";
					cout << "ФИО(0), Кафедру(1), Название одного из предметов(2), Оценку по одному из предметов(3), (4)если нужно изменить семестр некоторой оценки, и (5) для изменения семестра студента\n";
					size_t nom = -1;
					cin >> nom;

					if (nom == 0)
					{
						cout << "Введите ФИО, которое нужно изменить:\n";
						string s;
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";

						for (size_t i = 0; i < mass.size(); ++i)
						{
							if (mass[i] == s)
							{
								nom = i;
								break;
							}

						}

						cout << "Введите ФИО, на которое нужно изменить\n";
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";
						mass[nom] = s;

						ofstream baza(NameFile);

						for (size_t i = 0; i < mass.size(); ++i)
							baza << mass[i] << endl;

						baza.close();

						return;
					}
					else
						if (nom == 1)
						{
							cout << "Введите ФИО студента,у которого нужно изменить кафедру:\n";
							string s;
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = 0; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}

							}

							nom++;

							cout << "Введите кафедру, на которую нужно изменить\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";
							mass[nom] = s;

							ofstream baza(NameFile);

							for (size_t i = 0; i < mass.size(); ++i)
								baza << mass[i] << endl;

							baza.close();

							return;
						}
						else
							if (nom == 2)
							{
								cout << "Введите ФИО студента,у которого нужно изменить предмет:\n";
								string s;
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = 0; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}

								}

								cout << "Введите предмет, у которого нужно изменить название:\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = nom; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}
								}

								cout << "Введите название, на которое нужно изменить\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";
								mass[nom] = s;

								ofstream baza(NameFile);

								for (size_t i = 0; i < mass.size(); ++i)
									baza << mass[i] << endl;

								baza.close();

								return;
							}
							else
								if (nom == 3)
								{
									cout << "Введите ФИО студента,у которого нужно изменить оценку:\n";
									string s;
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = 0; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}

									}

									cout << "Введите предмет, у которого нужно изменить оценку:\n";
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = nom; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}
									}

									nom++;

									cout << "Введите оценку, на которую нужно изменить\n";
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";
									mass[nom] = s;

									ofstream baza(NameFile);

									for (size_t i = 0; i < mass.size(); ++i)
										baza << mass[i] << endl;

									baza.close();

									return;
								}else
									if (nom == 4)
									{
										cout << "Введите ФИО студента,у которого нужно изменить семестр предмета:\n";
										string s;
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";

										for (size_t i = 0; i < mass.size(); ++i)
										{
											if (mass[i] == s)
											{
												nom = i;
												break;
											}

										}

										cout << "Введите предмет, у которого нужно изменить семестр:\n";
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";

										for (size_t i = nom; i < mass.size(); ++i)
										{
											if (mass[i] == s)
											{
												nom = i;
												break;
											}
										}

										nom += 2;

										cout << "Введите семестр, на который нужно изменить\n";
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";
										mass[nom] = s;

										ofstream baza(NameFile);

										for (size_t i = 0; i < mass.size(); ++i)
											baza << mass[i] << endl;

										baza.close();

										return;

									}
									else
										if (nom == 5)
										{
											cout << "Введите ФИО студента,у которого нужно изменить семестр:\n";
											string s;
											cout << "Ввод: ";
											cin >> s;
											s = s + "@ ";

											for (size_t i = 0; i < mass.size(); ++i)
											{
												if (mass[i] == s)
												{
													nom = i;
													break;
												}

											}

											nom += 2;

											cout << "Введите новый номер семестра.\n";
											cout << "Ввод: ";
											cin >> s;
											s = "Семестр:" + s + "@ ";
											mass[nom] = s;

											ofstream baza(NameFile);

											for (size_t i = 0; i < mass.size(); ++i)
												baza << mass[i] << endl;
											baza.close();

											return;
										}
								

				}


		}else
		if (prover == "Гибридная")
		{
			cout << "Какой тип студента?(индив(1) или общ(2))\n";
			size_t vibor = 0;
			cin >> vibor;

			if (vibor==1)
			{
				cout << "Что именно вы хотите редактировать?\n";
				cout << "ФИО(0), Кафедру(1), Название одного из предметов(2), Оценку по одному из предметов(3)\n";
				size_t nom = -1;
				cin >> nom;

				if (nom == 0)
				{
					cout << "Введите ФИО, которое нужно изменить:\n";
					string s;
					cout << "Ввод: ";
					cin >> s;
					s = s + "@ ";

					for (size_t i = 0; i < mass.size(); ++i)
					{
						if (mass[i] == s)
						{
							nom = i;
							break;
						}

					}

					cout << "Введите ФИО, на которое нужно изменить\n";
					cout << "Ввод: ";
					cin >> s;
					s = s + "@ ";
					mass[nom] = s;

					ofstream baza(NameFile);

					for (size_t i = 0; i < mass.size(); ++i)
						baza << mass[i] << endl;

					return;
				}
				else
					if (nom == 1)
					{
						cout << "Введите ФИО студента,у которого нужно изменить кафедру:\n";
						string s;
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";

						for (size_t i = 0; i < mass.size(); ++i)
						{
							if (mass[i] == s)
							{
								nom = i;
								break;
							}

						}

						nom++;

						cout << "Введите кафедру, на которую нужно изменить\n";
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";
						mass[nom] = s;

						ofstream baza(NameFile);

						for (size_t i = 0; i < mass.size(); ++i)
							baza << mass[i] << endl;

						return;
					}
					else
						if (nom == 2)
						{
							cout << "Введите ФИО студента,у которого нужно изменить предмет:\n";
							string s;
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = 0; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}

							}

							cout << "Введите предмет, у которого нужно изменить название:\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = nom; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}
							}

							cout << "Введите название, на которое нужно изменить\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";
							mass[nom] = s;

							ofstream baza(NameFile);

							for (size_t i = 0; i < mass.size(); ++i)
								baza << mass[i] << endl;

							return;
						}
						else
							if (nom == 3)
							{
								cout << "Введите ФИО студента,у которого нужно изменить оценку:\n";
								string s;
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = 0; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}

								}

								cout << "Введите предмет, у которого нужно изменить оценку:\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = nom; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}
								}

								cout << "Введите оценку, которую нужно изменить:\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = nom; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}
								}

								cout << "Введите оценку, на которую нужно изменить\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";
								mass[nom] = s;

								ofstream baza(NameFile);

								for (size_t i = 0; i < mass.size(); ++i)
									baza << mass[i] << endl;

								return;
							}
			}
			else
				if (vibor == 2)
				{
					cout << "Что именно вы хотите редактировать?\n";
					cout << "ФИО(0), Кафедру(1), Название одного из предметов(2), Оценку по одному из предметов(3), (4)если нужно изменить семестр\n";
					size_t nom = -1;
					cin >> nom;

					if (nom == 0)
					{
						cout << "Введите ФИО, которое нужно изменить:\n";
						string s;
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";

						for (size_t i = 0; i < mass.size(); ++i)
						{
							if (mass[i] == s)
							{
								nom = i;
								break;
							}

						}

						cout << "Введите ФИО, на которое нужно изменить\n";
						cout << "Ввод: ";
						cin >> s;
						s = s + "@ ";
						mass[nom] = s;

						ofstream baza(NameFile);

						for (size_t i = 0; i < mass.size(); ++i)
							baza << mass[i] << endl;

						return;
					}
					else
						if (nom == 1)
						{
							cout << "Введите ФИО студента,у которого нужно изменить кафедру:\n";
							string s;
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";

							for (size_t i = 0; i < mass.size(); ++i)
							{
								if (mass[i] == s)
								{
									nom = i;
									break;
								}

							}

							nom++;

							cout << "Введите кафедру, на которую нужно изменить\n";
							cout << "Ввод: ";
							cin >> s;
							s = s + "@ ";
							mass[nom] = s;

							ofstream baza(NameFile);

							for (size_t i = 0; i < mass.size(); ++i)
								baza << mass[i] << endl;

							return;
						}
						else
							if (nom == 2)
							{
								cout << "Введите ФИО студента,у которого нужно изменить предмет:\n";
								string s;
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = 0; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}

								}

								cout << "Введите предмет, у которого нужно изменить название:\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";

								for (size_t i = nom; i < mass.size(); ++i)
								{
									if (mass[i] == s)
									{
										nom = i;
										break;
									}
								}

								cout << "Введите название, на которое нужно изменить\n";
								cout << "Ввод: ";
								cin >> s;
								s = s + "@ ";
								mass[nom] = s;

								ofstream baza(NameFile);

								for (size_t i = 0; i < mass.size(); ++i)
									baza << mass[i] << endl;

								return;
							}
							else
								if (nom == 3)
								{
									cout << "Введите ФИО студента,у которого нужно изменить оценку:\n";
									string s;
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = 0; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}

									}

									cout << "Введите предмет, у которого нужно изменить оценку:\n";
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = nom; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}
									}

									cout << "Введите оценку, которую нужно изменить:\n";
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";

									for (size_t i = nom; i < mass.size(); ++i)
									{
										if (mass[i] == s)
										{
											nom = i;
											break;
										}
									}

									cout << "Введите оценку, на которую нужно изменить\n";
									cout << "Ввод: ";
									cin >> s;
									s = s + "@ ";
									mass[nom] = s;

									ofstream baza(NameFile);

									for (size_t i = 0; i < mass.size(); ++i)
										baza << mass[i] << endl;

									return;
								}
								else
									if (nom == 4)
									{
										cout << "Введите ФИО студента,у которого нужно изменить семестр предмета:\n";
										string s;
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";

										for (size_t i = 0; i < mass.size(); ++i)
										{
											if (mass[i] == s)
											{
												nom = i;
												break;
											}

										}

										cout << "Введите предмет, у которого нужно изменить семестр:\n";
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";

										for (size_t i = nom; i < mass.size(); ++i)
										{
											if (mass[i] == s)
											{
												nom = i;
												break;
											}
										}

										nom += 2;

										cout << "Введите семестр, на который нужно изменить\n";
										cout << "Ввод: ";
										cin >> s;
										s = s + "@ ";
										mass[nom] = s;

										ofstream baza(NameFile);

										for (size_t i = 0; i < mass.size(); ++i)
											baza << mass[i] << endl;

										return;

									}


				}


		}
	}
}


//Удалить запись из БД
void DeleteZap(bool& exit)
{
	size_t tip = -1;
	string prover = "";

	while ((tip != 0) && (tip != 1))
	{
		cout << "Итак, в какуй базе данных вы хотите изменить запись, в гибридной(0) или однотипной(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "Гибридная";

		if (tip == 1)
			prover = "Однотипная";

		if ((tip != 0) && (tip != 1))
			cout << "Нет, ну это даже не смешно....\n\n";
	}

	cout << "Введите название базы данных в которой нужно отредактировать записи: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream File(NameFile);
	vector<string> mass(100);
	size_t buf = 0;
	if (!File)
	{
		system("cls");
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		while (File)// Пока есть данные, которые мы можем прочитать...
		{

			string strInput;// то перемещаем эти данные в строку, которую затем запишем в массив
			File >> strInput;

			if (strInput.find("@") != -1)
			{
				buf++;
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf + 1);

		if (mass.size() < 3)
		{
			system("cls");
			cout << "Вы не можете редактировать эту базу, она пустая\n";
			return;
		}

		File.close();
		int nom = -1;
				cout << "Введите имя студента, которого надо убрать\n";
				string s;
				cout << "Ввод: ";
				cin >> s;
				s = s + "@ ";

				for (size_t i = 0; i < mass.size(); ++i)
				{
					if (mass[i] == s)
					{
						nom = i;
						break;
					}
				}

				if (nom == -1)
				{
					system("cls");
					cout << "Такого студента нет!\n";
					return;
				}
				int j = 0;
				for(size_t i=nom;i<mass.size();++i)
				{
					j++;

					if ((mass[i].find("_") != -1)&&(j!=1))
					{
						break;
					}

					mass[i].erase();

				}

				ofstream OpFile(NameFile);

				for (size_t i = 0; i < mass.size(); ++i)
					OpFile << mass[i] << endl;

				OpFile.close();
	}
}


//Вывести на экран записи из БД
void VivZap(bool& exit)
{
	cout << "Введите название базы данных, из которой нужно вывести записи: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile= "Directory\\" + NameFile + ".txt";


	ifstream RidFile(NameFile);

	// Если мы не можем открыть этот файл для чтения его содержимого,
	if (!RidFile)
	{
		cout << "Не найдена база данных с таким названием!\n";// то выводим следующее сообщение об ошибке
	}
	else
	{
		vector<string> mass(100);
		size_t buf=0;

		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{
			
			string strInput;// то перемещаем эти данные в строку, которую затем выводим на экран
			RidFile >> strInput;

			if (strInput.find("@") != -1)
			{
				buf++;
				strInput.pop_back();
			}

			mass[buf] += strInput + " ";
		}

		mass.resize(buf +1);

		for (size_t i = 0; i < mass.size(); ++i)
			cout << mass[i]<<endl;
	}
}


///Сортировать записи в БД
void SortZap(bool& exit)
{

	cout << "Введите название базы данных: ";
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

		cout << "Введите параметры сортировки (1) сортировка по ФИО, (2) сортировка по семестрам\n";
		cout << "Ввод:";
		size_t chislo=0;
		cin >> chislo;

		if (chislo == 1)
		{
			std::sort(massivik.begin() + 1, massivik.end(),
				[](const auto& v1, const auto& v2)
				{ return v1[0] < v2[0]; });
		}else
			if (chislo == 2)
			{
				std::sort(massivik.begin() + 1, massivik.end(),
					[](const auto& v1, const auto& v2)
					{ return v1[2] < v2[2]; });
			}
			else 
			{
				cout << "Уж не знаю с какой целью, но вы ввели неверные параметры для сортировки, поэтому сортировка НЕ БУДЕТ выполнена, пусть это послужит вам уроком...\n";
				return;
			}

		ofstream file(NameFile);

		for (size_t a = 0; a < massivik.size(); ++a)
		{
			for (size_t b = 0; b < massivik[a].size(); ++b)
			{
				file << massivik[a][b] << endl;
			}
		}

		file.close();

	}

}


//Совершить выборку записей в БД
void Vibrk(bool& exit)
{
	cout << "Введите название базы данных, из которой будет произведена выборка: ";
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
		int j=-1,k = -1;

		while (RidFile)// Пока есть данные, которые мы можем прочитать...
		{
			RidFile >> strInput;// то перемещаем эти данные в строку, которую затем запишем в массив

			if (strInput.find("_") != -1)
			{
				j++;
				k++;
			}

			if ((k != -1)||(!(RidFile)))			
			{
				mass.resize(buf+1);
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

		cout << "Введите параметр, по которому должна быть выборка(Студенты n семестра(1); Cтуденты, изучавшие дисциплину name(2))\n";
		cout << "Ввод: ";
		size_t vib=0;
		cin >> vib;
		
		if (vib == 1)
		{
			string n="";

			cout << "Введите номер семестра:";
			cin >> n;

			vector<vector<string>> Gmassivik;


			for (size_t a = 1; a < massivik.size(); ++a)
			{
					if (massivik[a][2].find(n) != -1) 
					{
						Gmassivik.push_back(massivik[a]);
					}
			}



			cout << "Выборка завершена: \n";

			for (size_t a = 0; a < Gmassivik.size(); ++a)
			{
				for (size_t b = 0; b < Gmassivik[a].size(); ++b)
				{
					cout << Gmassivik[a][b] << endl;
				}
			}

		}
		else
			if (vib == 2)
			{
				string name="";

				cout << "Введите дисциплину:";
				cin >> name;

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



				cout << "Выборка завершена: \n";

				for (size_t a = 0; a < Gmassivik.size(); ++a)
				{
					for (size_t b = 0; b < Gmassivik[a].size(); ++b)
					{
						cout << Gmassivik[a][b] << endl;
					}
				}

				
			}

	}
}


//Сохранить выборку в новой БД
void SaveVibrk(bool& exit)
{
	cout << "Введите название базы данных, из которой будет произведена выборка: ";
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

		cout << "Введите параметр, по которому должна быть выборка(Студенты n семестра(1); Студенты, изучавшие дисциплину name(2))\n";
		cout << "Ввод: ";
		size_t vib = 0;
		cin >> vib;

		if (vib == 1)
		{
			string n = "";

			cout << "Введите номер семестра:";
			cin >> n;

			vector<vector<string>> Gmassivik;


			for (size_t a = 1; a < massivik.size(); ++a)
			{
				if (massivik[a][2].find(n) != -1)
				{
					Gmassivik.push_back(massivik[a]);
				}
			}



			cout << "Выборка завершена, введите название новой базы данных, в которую вы хотите сохранить выборку:\n";
			string str = "";
			cin >> str;
			ofstream file("Directory\\" +str + ".txt");
			file << "Гибридная база <" << str << ">" << endl;

			for (size_t a = 0; a < Gmassivik.size(); ++a)
			{
				for (size_t b = 0; b < Gmassivik[a].size(); ++b)
				{
					file << Gmassivik[a][b] << endl;
				}
			}

		}
		else
			if (vib == 2)
			{
				string name = "";

				cout << "Введите дисциплину:";
				cin >> name;

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



				cout << "Выборка завершена, введите название новой базы данных, в которую вы хотите сохранить выборку:\n";
				string str = "";
				cin >> str;
				ofstream file("Directory\\" + str + ".txt");
				file << "Гибридная база <" << str << ">" << endl;

				for (size_t a = 0; a < Gmassivik.size(); ++a)
				{
					for (size_t b = 0; b < Gmassivik[a].size(); ++b)
					{
						file << Gmassivik[a][b] << endl;
					}
				}


			}

	}
}


//Подсчитать кол-во студентов факультета, имеющих неудовлетворительные оценки.
void Kolneudstud(bool& exit)
{
	Stud student;
	student.kolneudstud(exit);
}


//Поиск студента внутри БД по ФИО.
void Poisk(bool& exit)
{
	Stud student;
	student.poisk(exit);
}