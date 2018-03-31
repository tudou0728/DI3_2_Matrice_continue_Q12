#pragma once
#include"Cfichier.h"
#include<Windows.h>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		char q='a';
		while(q != 'q')
		{
			for(int i=1;i<argc;i++)
			{
				//lire fichier
				cout<<"1-Lire fichier:"<<"\n";
				CGrapheOperation *graphe = new CGrapheOperation();
				CFichier fichier=CFichier();
				graphe=&(fichier.FICLireFichier(argv[i]));
				cout<<"Le r¨¦sultat est:"<<"\n";

				//affichier le graphe
				graphe->GRAAffichier();
				cout<<"*************Cette operation est fini********************"<<"\n";
				cout<<"\n";

				//colorier
				int eCouleurNombre=0;
				cout<<"2-Vous voulez combien de couleur pour colorier ce graphe?"<<"\n";
				cin>>eCouleurNombre;
				cout<<"----------Le resultat:----------"<<"\n";
				if(graphe->GRAExisteColoration(*(graphe),eCouleurNombre))
				{
					cout<<"(Vrai)-ce graphe peut etre colorie par "<<eCouleurNombre<<" couleurs"<<"\n";
				}
				else
				{
					cout<<"(Faute)-ce graphe ne peut pas etre colorie par "<<eCouleurNombre<<" couleurs"<<"\n";
				}
				for(int i=0;i<graphe->GRALireNumero();i++)
				{
					cout<<graphe->GRALireSommet(i).SOMLireeSOMColourNumero()<<"\n";
				}
				cout<<"*************Cette operation est fini********************"<<"\n";
				cout<<"\n";
				delete graphe;
				graphe=NULL;
			}						
			cout<<"Quitter(q) ou continuer(c)?"<<"\n";
			cin>>q;
		}
		cout<<"------------------Ce projet est fini-----------------------"<<"\n";
	}
	catch(Cexception a)
	{
		if(a.CEXLireErreur() == 1)
		{ a.CEXOuvreFile();}
		if(a.CEXLireErreur() == 2)
		{ a.CEXFileType();}
		if(a.CEXLireErreur() == 3)
		{ a.CEXErreurGeneral();}
		if(a.CEXLireErreur() == 4)
		{ a.CEXRepeter();}
		Sleep(5000);
	}
	exit(1);
}

