#include "CSommetOperation.h"


void CSommetOperation::SOMAjouterAFinSOMRelies(CArc &arc)
{
	int eLireArcNombre=this->eSOMArcNombre;
	int eExist=0;
	for(int j=0;j<eLireArcNombre;j++)
	{
		if(this->SOMRelies[j]->ARCLireElement() == arc.ARCLireElement()) 
		{
			eExist=1;
		}
	}
	if(eExist == 0)
	{
		if(eLireArcNombre != 0)
		{
			this->SOMRelies=(CArc**)realloc(this->SOMRelies,(eLireArcNombre+1)*sizeof(CArc*));		
		}
		else
		{
			this->SOMRelies=new CArc*[1];
		}
		this->SOMRelies[eLireArcNombre]=new CArc(arc);
		this->eSOMArcNombre ++;
	}
}

void CSommetOperation::SOMModifierSOMRelies(CArc &arc,int ePos)
{
	int i=arc.ARCLireElement();
	this->SOMRelies[ePos]->ARCSetElement(i);
}

void CSommetOperation::SOMSupprimerSOMRelies(int ePos)
{
	int eLireArcNombre=this->eSOMArcNombre;
	if(ePos >= eLireArcNombre)
	{
		Cexception a(5);
		throw a;
	}
	int i=ePos;
	while(i<eLireArcNombre-1)
	{
		this->SOMRelies[i]->ARCSetElement(this->SOMRelies[i+1]->ARCLireElement());
		i++;
	}
	this->SOMRelies=(CArc**)realloc(this->SOMRelies,(eLireArcNombre-1)*sizeof(CArc*));
	this->eSOMArcNombre --;
}

void CSommetOperation::SOMSupprimerSOMReliesElement(int eElement)
{
	int eLireArcNombre=this->eSOMArcNombre;
	int ePos=0;
	while(ePos<eLireArcNombre && this->SOMRelies[ePos]->ARCLireElement() != eElement)
	{
		ePos++;
	}
	if(ePos == eLireArcNombre)
	{
		Cexception a(3);
		throw a;
	}
	this->SOMSupprimerSOMRelies(ePos);
}

int CSommetOperation::SOMReliesCouleurNombre(int* epCouleur)
{
	if(epCouleur == NULL)
	{
		return 0;
	}
	else
	{
		int eCouleurCount=0; 
		for(int q=0;q<this->SOMLireSOMArcNombre();q++)
		{
			int s=0;
			for(s=0;s<q;s++)
			{
				if(epCouleur[q] == epCouleur[s] )
				{
					break;
				}
			}
			if(s==q && epCouleur[q]!=0)
			{
				eCouleurCount++;
			}
		}
		return eCouleurCount;
	}
}

