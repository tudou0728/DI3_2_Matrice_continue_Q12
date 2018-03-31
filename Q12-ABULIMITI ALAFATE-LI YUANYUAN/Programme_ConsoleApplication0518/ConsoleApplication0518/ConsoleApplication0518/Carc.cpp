#pragma once
#include "Carc.h"

using namespace std;

CArc::CArc()
{
	this->eARCDestination=0;
}

CArc::CArc(int eDest)
{
	this->eARCDestination=eDest;
}

CArc::CArc(CArc &arc)
{
	this->eARCDestination=arc.ARCLireElement();
}

int& CArc::ARCLireElement()
{
	return this->eARCDestination;
}

void CArc::ARCSetElement(int eDest)
{
	this->eARCDestination=eDest;
}