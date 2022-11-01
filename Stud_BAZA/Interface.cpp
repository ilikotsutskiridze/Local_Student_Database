#include "INTERFACE.H"
#include "FUNCTIONS.H"

void vipoln(size_t s, bool& exit)
{
	if (s == 1)
		Create(exit);

	if (s == 2)
		VivSP(exit);

	if (s == 3)
		Delete(exit);

	if (s == 4)
		Rename(exit);

	if (s == 5)
		Open(exit);

	if (s == 6)
		Add(exit);

	if (s == 7)
		RedactZap(exit);

	if (s == 8)
		DeleteZap(exit);

	if (s == 9)
		VivZap(exit);
									
	if (s == 10)
		SortZap(exit);

	if (s == 11)
		Vibrk(exit);

	if (s == 12)
		SaveVibrk(exit);

	if (s == 13)
		Kolneudstud(exit);

	if (s == 14)
		Poisk(exit);
}

void interface(bool& exit)
{
	cout << "1) Создать БД\n";
	cout << "2) Вывести на экран список существующих БД\n";
	cout << "3) Удалить БД\n";
	cout << "4) Переименовать БД\n";
	cout << "5) Открыть БД\n";
	cout << "6) Добавить запись в БД\n";
	cout << "7) Редактировать запись в БД\n";
	cout << "8) Удалить запись из БД\n";
	cout << "9) Вывести на экран записи из БД\n";
	cout << "10) Сортировать записи в БД\n";
	cout << "11) Совершить выборку записей в БД\n";
	cout << "12) Сохранить выборку в новой БД\n";
	cout << "13) Подсчёт кол-ва студентов факультета, имеющих неудовлетворительные оценки\n";
	cout << "14) Поиск студента внутри БД по ФИО\n";
	cout << "0) Завершить программу.\n";

	size_t vd = 0;

	cout << "\nВвод: ";
	cin >> vd;
	system("cls");

	if (vd == 0)
	{
		exit = 0;
		return;
	}
	else
		vipoln(vd, exit);
}