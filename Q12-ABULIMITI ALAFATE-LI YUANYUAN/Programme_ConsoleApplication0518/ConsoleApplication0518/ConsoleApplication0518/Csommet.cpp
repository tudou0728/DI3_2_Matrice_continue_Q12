#include "Csommet.h"

CSommet::CSommet()
{
	this->eSOMArcNombre=0;
	this->eSOMNumero=0;
	this->eSOMCouleurNumero=0;
	this->SOMRelies=NULL;
}

CSommet::~CSommet()
{	
	if(this->eSOMArcNombre!=0 && this->SOMRelies!= NULL)
	{
		int i=0;
		while(i<this->eSOMArcNombre)
		{
			if(this->SOMRelies[i] != NULL)
			{
				delete this->SOMRelies[i];
				this->SOMRelies[i]=NULL;
			}
			i++;
		}
		delete this->SOMRelies;
		this->SOMRelies=NULL;
	}
}
		
CSommet::CSommet(CSommet &sommet)
{
	this->eSOMArcNombre=sommet.SOMLireSOMArcNombre();
	this->eSOMNumero=sommet.SOMLireSOMNumero();
	this->eSOMCouleurNumero=sommet.SOMLireeSOMColourNumero();
	if(this->eSOMArcNombre != 0)
	{
		this->SOMRelies = new CArc*[this->eSOMArcNombre];
		int i=0;
		while(i<this->eSOMArcNombre)
		{
			this->SOMRelies[i] = new CArc(this->SOMLirSOMReliesElement(i));
			i++;
		}
	}
}

void CSommet::SOMSetSOMNumero(int eNum)
{
	this->eSOMNumero=eNum;
}

void CSommet::SOMSetSOMArcNombre(int eNum)
{
	this->eSOMArcNombre=eNum;
}
	
void CSommet::SOMSetSOMColourNumero(int eNum)
{
	this->eSOMCouleurNumero=eNum;
}

int CSommet::SOMLireSOMNumero()
{
	return this->eSOMNumero;
}
	
int CSommet::SOMLireSOMArcNombre()
{
	return this->eSOMArcNombre;
}

CArc** CSommet::SOMLireSOMRelies()
{
	return this->SOMRelies;
}

int CSommet::SOMLireeSOMColourNumero()
{
	return this->eSOMCouleurNumero;
}

CArc& CSommet::SOMLirSOMReliesElement(int ePos)
{
	return *(this->SOMRelies[ePos]);
}