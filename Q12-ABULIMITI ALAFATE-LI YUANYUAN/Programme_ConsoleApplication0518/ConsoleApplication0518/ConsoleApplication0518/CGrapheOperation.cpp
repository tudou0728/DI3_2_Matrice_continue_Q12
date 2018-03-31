#include "CGrapheOperation.h"

void CGrapheOperation::GRAAjouterSommet(CSommetOperation &sommet,int ePos)
{
	int j=0;
	while(j<this->eGRANumero)
	{
		if(this->pGRAsommet[j]->SOMLireSOMNumero() == sommet.SOMLireSOMNumero())
		{
			Cexception a(4);//dejs existe
			throw a;
		}
		j++;
	}
	pGRAsommet=(CSommetOperation**)realloc(pGRAsommet,sizeof(CSommetOperation*)*(eGRANumero+1));
	for(int i=eGRANumero;i>ePos;i--)
	{
		pGRAsommet[i]=pGRAsommet[i-1];
	}
	pGRAsommet[ePos]=new CSommetOperation(sommet);
	this->eGRANumero=this->eGRANumero+1;
}
	
void CGrapheOperation::GRAAjouterArc(int ePart,int eArri)
{
	int j=0;
	CArc partArc=CArc();
	CArc arriArc=CArc();
	CSommetOperation psommet=CSommetOperation();
	CSommetOperation asommet=CSommetOperation();
	partArc.ARCSetElement(ePart);
	arriArc.ARCSetElement(eArri);
	while(j<this->eGRANumero)
	{
		if(ePart == this->pGRAsommet[j]->SOMLireSOMNumero())//chercher partant
		{			
			int c=0;
			while(c<this->eGRANumero)
			{
				if( this->pGRAsommet[c]->SOMLireSOMNumero()== eArri)//chercher arrivant
				{					
					this->pGRAsommet[c]->SOMAjouterAFinSOMRelies(partArc);///ajouter partant dans arrivant
					this->pGRAsommet[j]->SOMAjouterAFinSOMRelies(arriArc);//ajouter arrivant dans partant
					c=this->eGRANumero+1;//pour break
					j=this->eGRANumero+1;//pour break
				}
				c++;
			}
			if(c == this->eGRANumero)//ne trouver pas d'arrivant
			{
				this->pGRAsommet[j]->SOMAjouterAFinSOMRelies(arriArc);//ajouter arrivant dans partant
				asommet.SOMSetSOMNumero(eArri);
				asommet.SOMAjouterAFinSOMRelies(partArc);
				this->GRAAjouterSommet(asommet,this->eGRANumero); 
				j=this->eGRANumero+1;
			}
		}
		j++;
	}
    if(j == this->eGRANumero)//ne trouver pas de partant
	{
		int d=0;
		while(d<this->eGRANumero)
		{
			if(eArri == this->pGRAsommet[d]->SOMLireSOMNumero())
			{
				this->pGRAsommet[d]->SOMAjouterAFinSOMRelies(partArc);
				psommet.SOMSetSOMNumero(ePart);
				psommet.SOMAjouterAFinSOMRelies(arriArc);
				this->GRAAjouterSommet(psommet,this->eGRANumero);
				d=this->eGRANumero+1;
			}
			d++;
		}
		if(d == this->eGRANumero) 
		{
			psommet.SOMSetSOMNumero(ePart);
			psommet.SOMAjouterAFinSOMRelies(arriArc);
			asommet.SOMSetSOMNumero(eArri);
			asommet.SOMAjouterAFinSOMRelies(partArc);
			this->GRAAjouterSommet(psommet,this->eGRANumero);
			this->GRAAjouterSommet(asommet,this->eGRANumero);
		}
	}
}
		
void CGrapheOperation::GRAModifierSommetNumero(int eSommet,int eMSommet)
{
	int i=0;
	while(i<this->eGRANumero)
	{
		if(this->pGRAsommet[i]->SOMLireSOMNumero() == eMSommet)
		{
			Cexception a(4); 
			throw a;
		}
		if(this->pGRAsommet[i]->SOMLireSOMNumero() == eSommet)
		{
			this->pGRAsommet[i]->SOMSetSOMNumero(eMSommet);
			break;
		}
		i++;
	}
	if(i == this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	int m=0;
	while(m<this->eGRANumero)
	{
		int n=0;
		while(n<this->pGRAsommet[m]->SOMLireSOMArcNombre())
		{
			if(this->pGRAsommet[m]->SOMLirSOMReliesElement(n).ARCLireElement() ==eSommet)
			{
				this->pGRAsommet[m]->SOMLirSOMReliesElement(n).ARCSetElement(eMSommet);
			}
			n++;
		}
		int q=0;
		while(q<this->pGRAsommet[m]->SOMLireSOMArcNombre())
		{
			if(this->pGRAsommet[m]->SOMLirSOMReliesElement(q).ARCLireElement() ==eSommet)
			{
				this->pGRAsommet[m]->SOMLirSOMReliesElement(q).ARCSetElement(eMSommet);
			}
			q++;
		}
		m++;
	}
}
	
void CGrapheOperation::GRAModifierSommet(CSommetOperation &sommet,int ePos)
{
	delete pGRAsommet[ePos];
	pGRAsommet[ePos]=&(sommet);
}

void CGrapheOperation::GRAModifierArc(int ePart,int eArri,int eMArri)
{
	int m=0;
	int eMArriverPos=0;
	while(m<this->eGRANumero) 
	{
		if(this->pGRAsommet[m]->SOMLireSOMNumero() == eMArri)
		{
			eMArriverPos=m;
			m=this->eGRANumero+1;
		}
		m++;
	}
	if(m == this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	int i=0;
	while(i<this->eGRANumero)
	{
		if(this->pGRAsommet[i]->SOMLireSOMNumero() == ePart) 
		{
			int j=0;
			while(j<this->pGRAsommet[i]->SOMLireSOMArcNombre())
			{
				if(this->pGRAsommet[i]->SOMLirSOMReliesElement(j).ARCLireElement() == eArri) 
				{
					this->pGRAsommet[i]->SOMLirSOMReliesElement(j).ARCSetElement(eMArri); 
					break;
				}
				j++;
			}
			break;
		}
		i++;
	}
	if(i==this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	CArc arc=CArc(ePart);
	this->pGRAsommet[eMArriverPos]->SOMAjouterAFinSOMRelies(arc); 
	int eArriverPos=0;
	while(eArriverPos<this->eGRANumero)
	{
		if(this->pGRAsommet[eArriverPos]->SOMLireSOMNumero() == eArri) 
		{
			this->pGRAsommet[eArriverPos]->SOMSupprimerSOMReliesElement(ePart);
			break;
		}
		eArriverPos++;
	}
	if(eArriverPos==this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
}

void CGrapheOperation::GRASupprimerSommet(int eElement)
{
	int q=0;
	while(q<this->eGRANumero)
	{
		if(this->pGRAsommet[q]->SOMLireSOMNumero() == eElement)
		{
			break;
		}
		q++;
	}
	if(q>=this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	int m=0;
	while(m<this->eGRANumero)
	{
		for(int n=0;n<this->pGRAsommet[m]->SOMLireSOMArcNombre();n++)
		{
			if(this->pGRAsommet[m]->SOMLirSOMReliesElement(n).ARCLireElement() ==eElement)
			{
				this->pGRAsommet[m]->SOMSupprimerSOMRelies(n);
			}
		}
		m++;
	}

	int ePos=0;
	while(ePos<this->eGRANumero)
	{
		if(this->pGRAsommet[ePos]->SOMLireSOMNumero() == eElement)
		{
			break;
		}
		ePos++;
	}
	for(int i=ePos;i<eGRANumero;i++)
	{
		pGRAsommet[i]=pGRAsommet[i+1];
	}
	pGRAsommet=(CSommetOperation**)realloc(pGRAsommet,sizeof(CSommetOperation*)*(eGRANumero-1));
	eGRANumero--;
}

void CGrapheOperation::GRASupprimerArc(int ePart,int eArri)
{
	int ePartPos=0;
	int eArriPos=0;
	while(this->pGRAsommet[ePartPos]->SOMLireSOMNumero() != ePart)
	{
		ePartPos++;
	}
	if(ePartPos >= this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	while(this->pGRAsommet[eArriPos]->SOMLireSOMNumero() != eArri)
	{
		eArriPos++;
	}
	if(eArriPos >= this->eGRANumero)
	{
		Cexception a(3); 
		throw a;
	}
	this->GRALireSommet(ePartPos).SOMSupprimerSOMReliesElement(eArri);
	this->GRALireSommet(eArriPos).SOMSupprimerSOMReliesElement(ePart);	
}

bool CGrapheOperation::GRAExisteColoration(CGrapheOperation& graphe,int eCouleurNombre)
{
	int eSommetNombre=graphe.GRALireNumero();
	if(graphe.GRAGrapheCouleurNombre(graphe) == eSommetNombre)
	{
		return true; //si deja colorier tous les sommets
	}
	else 
	{
		int j=0;
		while(j<eSommetNombre)
		{
			if(graphe.GRALireSommet(j).SOMLireeSOMColourNumero() == 0) 
			{
				graphe.GRAColorierSommet(graphe,j,eCouleurNombre);//colorier les sommet
			}
			j++;
		}
	}
	if(graphe.GRAGrapheCouleurNombre(graphe)==eSommetNombre)//detecter si tous les sommet sont deja colories
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CGrapheOperation::GRAGrapheCouleurNombre(CGrapheOperation& graphe)//calculer combien de sommets qui sont deja colories
{
	int j=0;
	int eNombre=0;
	while(j<graphe.GRALireNumero())
	{
		if(graphe.GRALireSommet(j).SOMLireeSOMColourNumero() !=0)
		{
			eNombre++;
		}
		j++;
	}
	return eNombre;
}

bool CGrapheOperation::GRAColorierSommet(CGrapheOperation& graphe,int ePos,int eCouleurNombre)
{
	if(graphe.GRALireSommet(ePos).SOMLireSOMArcNombre() != 0)//si il n'y a pas d'arc
	{
		int *epCouleur=new int[graphe.GRALireSommet(ePos).SOMLireSOMArcNombre()];//查找与其相连的点的颜色
		for(int p=0;p<graphe.GRALireSommet(ePos).SOMLireSOMArcNombre();p++)
		{
			epCouleur[p]=graphe.GRALireSommetCoulour(graphe.GRALireSommet(ePos).SOMLirSOMReliesElement(p).ARCLireElement());
		}
		int eCouleurCount=graphe.GRALireSommet(ePos).SOMReliesCouleurNombre(epCouleur);
		if(eCouleurCount== eCouleurNombre)//detcter si tous les couleurs sont deja utilises
		{
			delete []epCouleur;
			return false;
		}
		else
		{
			for(int u=1;u<=eCouleurNombre;u++)//colorier le sommet
			{
				int v=0;
				for(v;v<graphe.GRALireSommet(ePos).SOMLireSOMArcNombre();v++)
				{
					if(epCouleur[v] == u)
					{
						break;
					}
				}
				if(v == graphe.GRALireSommet(ePos).SOMLireSOMArcNombre()) 
				{
					graphe.GRALireSommet(ePos).SOMSetSOMColourNumero(u);
					if(graphe.GRAExisteColoration(graphe,eCouleurNombre))
					{
						delete []epCouleur;
						return true;
					}
					else
					{
						graphe.GRALireSommet(ePos).SOMSetSOMColourNumero(0);
					}
				}
			}
		}
		delete [] epCouleur;
	}
	else
	{
		graphe.GRALireSommet(ePos).SOMSetSOMColourNumero(1);
	}
}

int* CGrapheOperation::GRASommetRelieCouleur(CGrapheOperation& graphe,int ePos) 
{
	int *epCouleur=new int[graphe.GRALireSommet(ePos).SOMLireSOMArcNombre()]; 
	if(graphe.GRALireSommet(ePos).SOMLireSOMArcNombre() != 0)
	{
		for(int p=0;p<graphe.GRALireSommet(ePos).SOMLireSOMArcNombre();p++)
		{
			epCouleur[p]=graphe.GRALireSommetCoulour(graphe.GRALireSommet(ePos).SOMLirSOMReliesElement(p).ARCLireElement());
		}
		return epCouleur;
	}
	else
	{
		return NULL;
	}
}