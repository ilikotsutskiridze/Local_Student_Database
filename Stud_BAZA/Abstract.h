#pragma once
#include "NODE.H"

class Dis_po_Plan
{
public:
	string discp="";//конкретная дисциплина
	size_t oqenka=0;//оценка
	size_t semestr=0;//семестр
};

class Dis 
{
public:
	string discp="";//конкретная дисциплина
	size_t oqenka=0;//оценка
};


class AbstStruct
{
public:
	string FIO="";//ФИО
	string kaf="";//кафедра
	string semestr = "";//семестр

	virtual void kolneudstud(bool& exit)=0;//Подсчёт кол-ва студентов факультета, имеющих неудовлетворительные оценки

	virtual void poisk(bool& exit)=0;//Поиск студента внутри БД по ФИО
};