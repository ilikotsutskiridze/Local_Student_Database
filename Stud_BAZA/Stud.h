#pragma once
#include "ABSTRACT.H"

class Stud : public AbstStruct
{
public:
	Dis pred;

	vector<Dis> predmeti;//��� ����������

	void kolneudstud(bool& exit) override;

	void poisk(bool& exit) override;
};