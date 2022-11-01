#include "SpStud.h"
#include "Stud.h"
#include "FUNCTIONS.H"
#include "INTERFACE.H"


//������� ��
void Create(bool& exit)
{
	cout << "����� ���� ������ �� ������ �������?\n";
	cout << "1)���������?\n";
	cout << "0)����������?\n";

	bool change;
	cin >> change;

	if (change)
	{
		cout << "������� �������� ����� ��������� ����: ";
		string NameFile;
		cin >> NameFile;



		ofstream OpFile("Directory\\"+ NameFile + ".txt");
		OpFile << "��������� ���� <" << NameFile << ">" <<endl;
		cout << "���� ������ �������\n";
		OpFile.close();

		system("cls");
	}
	else
	{
		cout << "������� �������� ����� ���������� ����: ";
		string NameFile;
		cin >> NameFile;

		cout << "�������, ����� ��������� �� ����� ���� ����������(�����������(1) ��� �������(2)): ";
		size_t NameStud;
		cin >> NameStud;

		ofstream OpFile("Directory\\" + NameFile + ".txt");
		if (NameStud == 1)
			OpFile << "���������� ���� <" << NameFile << "> � ��� ���������� ���������� ��������� ��������������� �����" << endl;
		if (NameStud ==2 )
			OpFile << "���������� ���� <" << NameFile << "> � ��� ���������� ���������� ��������� ������ �����" << endl;

		"���� ������ �������\n";
		OpFile.close();

		system("cls");
	}
}


//������� �� ����� ������ ������������ ��
void VivSP(bool& exit)
{
	vector<string> Bazes;
	for (auto& p : fs::recursive_directory_iterator("Directory\\"))
	{
		if (fs::is_regular_file(p))
		{
			if (p.path().extension().string() == ".txt")
				Bazes.push_back(p.path().string().substr(p.path().string().find_last_of("\\") + 1, string::npos));//���������� � ������ ����� ������ ��� ����
		}
	}
	
	cout << "������ ������������ �� ������ ������ ��� ������:" << endl;

	for (size_t i = 0; i < Bazes.size(); ++i)
	{
		cout << Bazes[i] << endl;
	}

	cout << endl;
}


//������� ��
void Delete(bool& exit)
{
	cout << "������� �������� ���� ������, ������� �� ������ �������: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile = "Directory\\" + NameFile + ".txt";
	const char* name = NameFile.c_str();

	if (remove(name) == -1)
	{
		system("cls");
		cout << "������, ������ ����� ���.\n";
	}
	else
	{
		system("cls");
		cout << "���� ������ �������.\n";
	}
}


//������������� ��
void Rename(bool& exit)
{
	cout << "������� �������� ���� ������, ������� �� ������ ������������: ";
	string NameFile;
	cin >> NameFile;

	NameFile= "Directory\\" + NameFile + ".txt";
	
	ifstream RidFile(NameFile);
	vector<string> mass(100);
	size_t buf = 0;


	// ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������,
	if (!RidFile)
	{
		system("cls");
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{

			string strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� �� �����
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

		cout << "������� ����� ��������: ";
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


//������� ��
void Open(bool& exit)
{
	cout << "������� �������� ���� ������, ������� �� ������ �������: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile = "Directory\\" + NameFile + ".txt";
	const char* name = NameFile.c_str();

	system(name);

	interface(exit);
}


//�������� ������ � ��
void Add(bool& exit)
{
	size_t tip=-1;
	string prover;
	
	while ((tip != 0) && (tip != 1))
	{
		cout << "����, � ����� ���� ������ �� ������ �������� ������, � ���������(0) ��� ����������(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "���������";

		if (tip == 1)
			prover = "����������";
		if ((tip != 0) && (tip != 1))
			cout << "��� ��� ������, � � ����� ������ ��������....\n\n";
	}

	cout << "������, ������ ������� �������� ���� ������, � ������� �� ������ �������� ������: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream RidFile(NameFile);
	vector<string> mass(100);
	size_t buf = 0;

	if (!RidFile)
	{
		system("cls");
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{

			string strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������
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
			cout << "���, ��� �� �����, ��� ���� ������ ������� ����, � ����������� ��������� ���� ������.\n   P.S. ��, ��� ��������� �����...\n\n";
			return;
		}

		ofstream baza(NameFile);

		for (size_t i = 0; i < mass.size(); ++i)
			baza << mass[i] << endl;

		if (prover == "����������")
		{
			if (mass[0].find("���������������") != -1)
			{
				Stud student;

				cout << "������, ������ ������� �������, ��� � �������� ��������:\n";
				
				cin.ignore();
				getline(cin, student.FIO);

				for (size_t i = 0; i < student.FIO.size(); ++i)
				{
					if (student.FIO[i] == ' ')
					{
						student.FIO[i] = '_';
					}
				}

				cout << "������, ������ ������� ������� ��������:\n";
				cin >> student.kaf;

				cout << "������, ������ ������� �������� ��������:\n";
				cin >> student.semestr;
				student.semestr = "�������:" + student.semestr;

				cout << "������, ������ ������� ���������� ��������� ���������:\n";
				size_t n = 0;
				cin >> n;



				for (size_t i = 0; i < n; ++i)
				{
					cout << "������� �������� ����������\n";
					cout << "����: ";
					cin >> student.pred.discp;

					cout << "������� ������ �� ���\n";
					cout << "����: ";
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
				if (mass[0].find("������") != -1)
				{
					SpStud student;

					cout << "������, ������ ������� �������, ��� � �������� ��������:\n";

					cin.ignore();
					getline(cin, student.FIO);

					for (size_t i = 0; i < student.FIO.size(); ++i)
					{
						if (student.FIO[i] == ' ')
						{
							student.FIO[i] = '_';
						}
					}

					cout << "������, ������ ������� ������� ��������:\n";
					cin >> student.kaf;

					cout << "������, ������ ������� �������� ��������:\n";
					cin >> student.semestr;
					student.semestr = "�������:"+ student.semestr;

					cout << "������, ������ ������� ���������� ��������� ���������:\n";
					size_t n = 0;
					cin >> n;

					baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

					for (size_t i = 0; i < n; ++i)
					{
						cout << "������� �������� ����������\n";
						cout << "����: ";
						cin >> student.pred.discp;

						cout << "������� ������ �� ���\n";
						cout << "����: ";
						cin >> student.pred.oqenka;

						cout << "������� ������� ��������\n";
						cout << "����: ";
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
			cout << "������ ���� �������� �� ������ ��������?(������(1) ����� ��� ���������������(2)?)\n";
			size_t s;
			cin >> s;

			if (s == 2)
			{
				Stud student;

				cout << "������, ������ ������� �������, ��� � �������� ��������:\n";
				cin.ignore();
				getline(cin, student.FIO);

				for (size_t i = 0; i < student.FIO.size(); ++i)
				{
					if (student.FIO[i] == ' ')
					{
						student.FIO[i] = '_';
					}
				}
				cout << "������, ������ ������� ������� ��������:\n";
				cin >> student.kaf;

				cout << "������, ������ ������� �������� ��������:\n";
				cin >> student.semestr;
				student.semestr = "�������:" + student.semestr;

				cout << "������, ������ ������� ���������� ��������� ���������:\n";
				size_t n = 0;
				cin >> n;

				baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

				for (size_t i = 0; i < n; ++i)
				{
					cout << "������� �������� ����������\n";
					cout << "����: ";
					cin >> student.pred.discp;

					cout << "������� ������ �� ���\n";
					cout << "����: ";
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

					cout << "������, ������ ������� �������, ��� � �������� ��������:\n";
					cin.ignore();
					getline(cin, student.FIO);

					for (size_t i = 0; i < student.FIO.size(); ++i)
					{
						if (student.FIO[i] == ' ')
						{
							student.FIO[i] = '_';
						}
					}
					cout << "������, ������ ������� ������� ��������:\n";
					cin >> student.kaf;

					cout << "������, ������ ������� �������� ��������:\n";
					cin >> student.semestr;
					student.semestr = "�������:" + student.semestr;

					cout << "������, ������ ������� ���������� ��������� ���������:\n";
					size_t n = 0;
					cin >> n;

					baza << endl << student.FIO + "@" << endl << student.kaf + "@" << endl << student.semestr + "@" << endl;

					for (size_t i = 0; i < n; ++i)
					{
						cout << "������� �������� ����������\n";
						cout << "����: ";
						cin >> student.pred.discp;

						cout << "������� ������ �� ���\n";
						cout << "����: ";
						cin >> student.pred.oqenka;

						cout << "������� ������� ��������\n";
						cout << "����: ";
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


//������������� ������ � ��
void RedactZap(bool& exit)
{
	size_t tip = -1;
	string prover="";

	while ((tip != 0) && (tip != 1))
	{
		cout << "����, � ����� ���� ������ �� ������ �������� ������, � ���������(0) ��� ����������(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "���������";

		if (tip == 1)
			prover = "����������";

		if ((tip != 0) && (tip != 1))
			cout << "���, �� ��� ���� �� ������....\n\n";
	}
	
	cout << "������� �������� ���� ������ � ������� ����� ��������������� ������: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream File(NameFile);
	vector<string> mass(100);
	size_t buf = 0;
	if (!File)
	{
		system("cls");
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		while (File)// ���� ���� ������, ������� �� ����� ���������...
		{

			string strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������
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
			cout << "�� �� ������ ������������� ��� ����, ��� ������\n";
			return;
		}

		File.close();
		if(prover=="����������")
		{

			if (mass[0].find("���������������") != -1)
			{
				cout << "��� ������ �� ������ �������������?\n";
				cout << "���(0), �������(1), �������� ������ �� ���������(2), ������ �� ������ �� ���������(3), ��� �� ������� �������� ��������(4)?\n";
				size_t nom = -1;
				cin >> nom;

				if (nom == 0)
				{
					cout << "������� ���, ������� ����� ��������:\n";
					string s;
					cout << "����: ";
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

					cout << "������� ���, �� ������� ����� ��������\n";
					cout << "����: ";
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
						cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
						string s;
						cout << "����: ";
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

						cout << "������� �������, �� ������� ����� ��������\n";
						cout << "����: ";
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
							cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
							string s;
							cout << "����: ";
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

							cout << "������� �������, � �������� ����� �������� ��������:\n";
							cout << "����: ";
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

							cout << "������� ��������, �� ������� ����� ��������\n";
							cout << "����: ";
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
								cout << "������� ��� ��������,� �������� ����� �������� ������:\n";
								string s;
								cout << "����: ";
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

								cout << "������� �������, � �������� ����� �������� ������:\n";
								cout << "����: ";
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

								cout << "������� ������, �� ������� ����� ��������\n";
								cout << "����: ";
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
									cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
									string s;
									cout << "����: ";
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

									cout << "������� ����� ����� ��������.\n";
									cout << "����: ";
									cin >> s;
									s = "�������:" + s + "@ ";
									mass[nom] = s;

									ofstream baza(NameFile);

									for (size_t i = 0; i < mass.size(); ++i)
										baza << mass[i] << endl;
									baza.close();

									return;
								}
			}else 
				if (mass[0].find("������") != -1)
				{
					cout << "��� ������ �� ������ �������������?\n";
					cout << "���(0), �������(1), �������� ������ �� ���������(2), ������ �� ������ �� ���������(3), (4)���� ����� �������� ������� ��������� ������, � (5) ��� ��������� �������� ��������\n";
					size_t nom = -1;
					cin >> nom;

					if (nom == 0)
					{
						cout << "������� ���, ������� ����� ��������:\n";
						string s;
						cout << "����: ";
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

						cout << "������� ���, �� ������� ����� ��������\n";
						cout << "����: ";
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
							cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
							string s;
							cout << "����: ";
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

							cout << "������� �������, �� ������� ����� ��������\n";
							cout << "����: ";
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
								cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
								string s;
								cout << "����: ";
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

								cout << "������� �������, � �������� ����� �������� ��������:\n";
								cout << "����: ";
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

								cout << "������� ��������, �� ������� ����� ��������\n";
								cout << "����: ";
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
									cout << "������� ��� ��������,� �������� ����� �������� ������:\n";
									string s;
									cout << "����: ";
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

									cout << "������� �������, � �������� ����� �������� ������:\n";
									cout << "����: ";
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

									cout << "������� ������, �� ������� ����� ��������\n";
									cout << "����: ";
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
										cout << "������� ��� ��������,� �������� ����� �������� ������� ��������:\n";
										string s;
										cout << "����: ";
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

										cout << "������� �������, � �������� ����� �������� �������:\n";
										cout << "����: ";
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

										cout << "������� �������, �� ������� ����� ��������\n";
										cout << "����: ";
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
											cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
											string s;
											cout << "����: ";
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

											cout << "������� ����� ����� ��������.\n";
											cout << "����: ";
											cin >> s;
											s = "�������:" + s + "@ ";
											mass[nom] = s;

											ofstream baza(NameFile);

											for (size_t i = 0; i < mass.size(); ++i)
												baza << mass[i] << endl;
											baza.close();

											return;
										}
								

				}


		}else
		if (prover == "���������")
		{
			cout << "����� ��� ��������?(�����(1) ��� ���(2))\n";
			size_t vibor = 0;
			cin >> vibor;

			if (vibor==1)
			{
				cout << "��� ������ �� ������ �������������?\n";
				cout << "���(0), �������(1), �������� ������ �� ���������(2), ������ �� ������ �� ���������(3)\n";
				size_t nom = -1;
				cin >> nom;

				if (nom == 0)
				{
					cout << "������� ���, ������� ����� ��������:\n";
					string s;
					cout << "����: ";
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

					cout << "������� ���, �� ������� ����� ��������\n";
					cout << "����: ";
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
						cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
						string s;
						cout << "����: ";
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

						cout << "������� �������, �� ������� ����� ��������\n";
						cout << "����: ";
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
							cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
							string s;
							cout << "����: ";
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

							cout << "������� �������, � �������� ����� �������� ��������:\n";
							cout << "����: ";
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

							cout << "������� ��������, �� ������� ����� ��������\n";
							cout << "����: ";
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
								cout << "������� ��� ��������,� �������� ����� �������� ������:\n";
								string s;
								cout << "����: ";
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

								cout << "������� �������, � �������� ����� �������� ������:\n";
								cout << "����: ";
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

								cout << "������� ������, ������� ����� ��������:\n";
								cout << "����: ";
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

								cout << "������� ������, �� ������� ����� ��������\n";
								cout << "����: ";
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
					cout << "��� ������ �� ������ �������������?\n";
					cout << "���(0), �������(1), �������� ������ �� ���������(2), ������ �� ������ �� ���������(3), (4)���� ����� �������� �������\n";
					size_t nom = -1;
					cin >> nom;

					if (nom == 0)
					{
						cout << "������� ���, ������� ����� ��������:\n";
						string s;
						cout << "����: ";
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

						cout << "������� ���, �� ������� ����� ��������\n";
						cout << "����: ";
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
							cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
							string s;
							cout << "����: ";
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

							cout << "������� �������, �� ������� ����� ��������\n";
							cout << "����: ";
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
								cout << "������� ��� ��������,� �������� ����� �������� �������:\n";
								string s;
								cout << "����: ";
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

								cout << "������� �������, � �������� ����� �������� ��������:\n";
								cout << "����: ";
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

								cout << "������� ��������, �� ������� ����� ��������\n";
								cout << "����: ";
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
									cout << "������� ��� ��������,� �������� ����� �������� ������:\n";
									string s;
									cout << "����: ";
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

									cout << "������� �������, � �������� ����� �������� ������:\n";
									cout << "����: ";
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

									cout << "������� ������, ������� ����� ��������:\n";
									cout << "����: ";
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

									cout << "������� ������, �� ������� ����� ��������\n";
									cout << "����: ";
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
										cout << "������� ��� ��������,� �������� ����� �������� ������� ��������:\n";
										string s;
										cout << "����: ";
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

										cout << "������� �������, � �������� ����� �������� �������:\n";
										cout << "����: ";
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

										cout << "������� �������, �� ������� ����� ��������\n";
										cout << "����: ";
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


//������� ������ �� ��
void DeleteZap(bool& exit)
{
	size_t tip = -1;
	string prover = "";

	while ((tip != 0) && (tip != 1))
	{
		cout << "����, � ����� ���� ������ �� ������ �������� ������, � ���������(0) ��� ����������(1)?\n";
		cin >> tip;
		if (tip == 0)
			prover = "���������";

		if (tip == 1)
			prover = "����������";

		if ((tip != 0) && (tip != 1))
			cout << "���, �� ��� ���� �� ������....\n\n";
	}

	cout << "������� �������� ���� ������ � ������� ����� ��������������� ������: ";
	string NameFile;
	cin >> NameFile;
	NameFile = "Directory\\" + NameFile + ".txt";

	ifstream File(NameFile);
	vector<string> mass(100);
	size_t buf = 0;
	if (!File)
	{
		system("cls");
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		while (File)// ���� ���� ������, ������� �� ����� ���������...
		{

			string strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������
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
			cout << "�� �� ������ ������������� ��� ����, ��� ������\n";
			return;
		}

		File.close();
		int nom = -1;
				cout << "������� ��� ��������, �������� ���� ������\n";
				string s;
				cout << "����: ";
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
					cout << "������ �������� ���!\n";
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


//������� �� ����� ������ �� ��
void VivZap(bool& exit)
{
	cout << "������� �������� ���� ������, �� ������� ����� ������� ������: ";
	string NameFile;
	cin >> NameFile;
	cout << endl;
	NameFile= "Directory\\" + NameFile + ".txt";


	ifstream RidFile(NameFile);

	// ���� �� �� ����� ������� ���� ���� ��� ������ ��� �����������,
	if (!RidFile)
	{
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		vector<string> mass(100);
		size_t buf=0;

		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{
			
			string strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� �� �����
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


///����������� ������ � ��
void SortZap(bool& exit)
{

	cout << "������� �������� ���� ������: ";
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
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		int j = -1, k = -1;

		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{
			RidFile >> strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������

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

		cout << "������� ��������� ���������� (1) ���������� �� ���, (2) ���������� �� ���������\n";
		cout << "����:";
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
				cout << "�� �� ���� � ����� �����, �� �� ����� �������� ��������� ��� ����������, ������� ���������� �� ����� ���������, ����� ��� �������� ��� ������...\n";
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


//��������� ������� ������� � ��
void Vibrk(bool& exit)
{
	cout << "������� �������� ���� ������, �� ������� ����� ����������� �������: ";
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
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		int j=-1,k = -1;

		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{
			RidFile >> strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������

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

		cout << "������� ��������, �� �������� ������ ���� �������(�������� n ��������(1); C�������, ��������� ���������� name(2))\n";
		cout << "����: ";
		size_t vib=0;
		cin >> vib;
		
		if (vib == 1)
		{
			string n="";

			cout << "������� ����� ��������:";
			cin >> n;

			vector<vector<string>> Gmassivik;


			for (size_t a = 1; a < massivik.size(); ++a)
			{
					if (massivik[a][2].find(n) != -1) 
					{
						Gmassivik.push_back(massivik[a]);
					}
			}



			cout << "������� ���������: \n";

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

				cout << "������� ����������:";
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



				cout << "������� ���������: \n";

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


//��������� ������� � ����� ��
void SaveVibrk(bool& exit)
{
	cout << "������� �������� ���� ������, �� ������� ����� ����������� �������: ";
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
		cout << "�� ������� ���� ������ � ����� ���������!\n";// �� ������� ��������� ��������� �� ������
	}
	else
	{
		int j = -1, k = -1;

		while (RidFile)// ���� ���� ������, ������� �� ����� ���������...
		{
			RidFile >> strInput;// �� ���������� ��� ������ � ������, ������� ����� ������� � ������

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

		cout << "������� ��������, �� �������� ������ ���� �������(�������� n ��������(1); ��������, ��������� ���������� name(2))\n";
		cout << "����: ";
		size_t vib = 0;
		cin >> vib;

		if (vib == 1)
		{
			string n = "";

			cout << "������� ����� ��������:";
			cin >> n;

			vector<vector<string>> Gmassivik;


			for (size_t a = 1; a < massivik.size(); ++a)
			{
				if (massivik[a][2].find(n) != -1)
				{
					Gmassivik.push_back(massivik[a]);
				}
			}



			cout << "������� ���������, ������� �������� ����� ���� ������, � ������� �� ������ ��������� �������:\n";
			string str = "";
			cin >> str;
			ofstream file("Directory\\" +str + ".txt");
			file << "��������� ���� <" << str << ">" << endl;

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

				cout << "������� ����������:";
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



				cout << "������� ���������, ������� �������� ����� ���� ������, � ������� �� ������ ��������� �������:\n";
				string str = "";
				cin >> str;
				ofstream file("Directory\\" + str + ".txt");
				file << "��������� ���� <" << str << ">" << endl;

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


//���������� ���-�� ��������� ����������, ������� �������������������� ������.
void Kolneudstud(bool& exit)
{
	Stud student;
	student.kolneudstud(exit);
}


//����� �������� ������ �� �� ���.
void Poisk(bool& exit)
{
	Stud student;
	student.poisk(exit);
}