#pragma once
#include "NODE.H"

class Dis_po_Plan
{
public:
	string discp="";//���������� ����������
	size_t oqenka=0;//������
	size_t semestr=0;//�������
};

class Dis 
{
public:
	string discp="";//���������� ����������
	size_t oqenka=0;//������
};


class AbstStruct
{
public:
	string FIO="";//���
	string kaf="";//�������
	string semestr = "";//�������

	virtual void kolneudstud(bool& exit)=0;//������� ���-�� ��������� ����������, ������� �������������������� ������

	virtual void poisk(bool& exit)=0;//����� �������� ������ �� �� ���
};