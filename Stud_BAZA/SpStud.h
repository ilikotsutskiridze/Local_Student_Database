#pragma once
#include "ABSTRACT.H"

class SpStud : public AbstStruct
{
public:
	Dis_po_Plan pred;

	vector<Dis_po_Plan> predmeti;//все дисциплины
	
	void kolneudstud(bool& exit) override;
	
	void poisk(bool& exit) override;

};