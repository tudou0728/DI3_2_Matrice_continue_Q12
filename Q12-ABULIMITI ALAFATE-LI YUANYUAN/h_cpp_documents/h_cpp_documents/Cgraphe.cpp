#include"Cgraphe.h"

CGraphe::CGraphe()
{
	this->eGRANumero=0;
	this->pGRAsommet=NULL;
}

CGraphe::~CGraphe()
{
	int i=this->eGRANumero - 1;
	while(i>=0 && this->eGRANumero !=0)
	{
		if(this->pGRAsommet[i] != NULL)
		{
			delete this->pGRAsommet[i];
			this->pGRAsommet[i]=NULL;
		}
		i--;
	}
	delete this->pGRAsommet;
	this->pGRAsommet=NULL;
}

CGraphe::CGraphe(CGraphe& graphe)
{
	this->eGRANumero=graphe.GRALireNumero();
	if(this->eGRANumero != 0)
	{
		this->pGRAsommet=new CSommetOperation*[this->eGRANumero];
		int i=0;
		while(i<this->eGRANumero)
		{
			this->pGRAsommet[i]=new CSommetOperation(graphe.GRALireSommet(i));
			i++;
		}
	}
	else
	{
		this->pGRAsommet=NULL;
	}
}
		
int& CGraphe::GRALireNumero()
{
	return this->eGRANumero;
}

CSommetOperation& CGraphe::GRALireSommet(int ePos)
{
	return *(this->pGRAsommet[ePos]);
}

int CGraphe::GRALireSommetCoulour(int eSommetNumero)
{
	int ePos=0;
	while(ePos<this->eGRANumero)
	{
		if(this->pGRAsommet[ePos]->SOMLireSOMNumero() == eSommetNumero)
		{
			break;
		}
		ePos++;
	}
	return (this->pGRAsommet[ePos]->SOMLireeSOMColourNumero());
}

void CGraphe::GRASetNumero(int eNumero)
{
	this->eGRANumero=eNumero;
}
		
void CGraphe::GRASetsommet(int eNumero)
{
	this->pGRAsommet=new CSommetOperation*[eNumero];
	for(int i=0;i<eNumero;i++)
	{
		this->pGRAsommet[i]=new CSommetOperation();
	}
}

void CGraphe::GRAAffichier()
{
	cout<<"NBSommets="<<this->eGRANumero<<"\n";
	int eArcCount=0;
	int **peTemp; 
    int eLig = eGRANumero+1;
    int eCol = eGRANumero+1;
    peTemp = new int*[eLig];
	for (int i=0; i<eLig; i++)
	{
		peTemp[i] = new int[eCol];
	}
 
	for (int i=0; i<eLig; i++)
	{
		for (int j=0; j<eCol; j++)
		{
			peTemp[i][j] = 0;    
		}
	}
	for(int i=0;i<eGRANumero;i++)
	{
		peTemp[0][i+1]=pGRAsommet[i]->SOMLireSOMNumero();
		peTemp[i+1][0]=pGRAsommet[i]->SOMLireSOMNumero();
	}
	for(int m=0;m<this->eGRANumero;m++)
	{
		int a=0;
		while(a<this->pGRAsommet[m]->SOMLireSOMArcNombre())
		{
			int eFin=this->pGRAsommet[m]->SOMLirSOMReliesElement(a).ARCLireElement();
			int ePos=0;
			while(ePos<this->eGRANumero)
			{
				if(this->pGRAsommet[ePos]->SOMLireSOMNumero() == eFin)
				{
					peTemp[m+1][ePos+1]=1;
					peTemp[ePos+1][m+1]=1;
					break;
				}
				else
				{
					ePos++;
				}
			}
			a++;
		}
	}
	for (int x=1;x<=this->eGRANumero;x++)
	{
		for(int y=1;y<=x;y++)
		{
			if(peTemp[x][y] == 1)
			{
				eArcCount++;
			}
		}
	}
	cout<<"NBArcs="<<eArcCount<<"\n";
	cout<<"colonne <=> d¨¦but ligne <=> destination  "<<"\n";
	for(int c=0;c<=eGRANumero;c++)
	{
		for(int d=0;d<=eGRANumero;d++)
		{
			cout<<peTemp[c][d]<<"\t";
		}
		cout<<"\n";
	}

	for (int i=0; i<eLig; i++)
	{
		delete[] peTemp[i];
	}
	delete[] peTemp;
}
