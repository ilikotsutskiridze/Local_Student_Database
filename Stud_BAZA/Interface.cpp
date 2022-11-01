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
	cout << "1) ������� ��\n";
	cout << "2) ������� �� ����� ������ ������������ ��\n";
	cout << "3) ������� ��\n";
	cout << "4) ������������� ��\n";
	cout << "5) ������� ��\n";
	cout << "6) �������� ������ � ��\n";
	cout << "7) ������������� ������ � ��\n";
	cout << "8) ������� ������ �� ��\n";
	cout << "9) ������� �� ����� ������ �� ��\n";
	cout << "10) ����������� ������ � ��\n";
	cout << "11) ��������� ������� ������� � ��\n";
	cout << "12) ��������� ������� � ����� ��\n";
	cout << "13) ������� ���-�� ��������� ����������, ������� �������������������� ������\n";
	cout << "14) ����� �������� ������ �� �� ���\n";
	cout << "0) ��������� ���������.\n";

	size_t vd = 0;

	cout << "\n����: ";
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