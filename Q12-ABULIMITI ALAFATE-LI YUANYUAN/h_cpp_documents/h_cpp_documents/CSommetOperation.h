#include "Csommet.h"

class CSommetOperation: public CSommet 
{
	public:
		void SOMAjouterAFinSOMRelies(CArc &arc);
		void SOMModifierSOMRelies(CArc &arc,int ePos);
		void SOMSupprimerSOMRelies(int ePos);
		void SOMSupprimerSOMReliesElement(int eElement);

		int SOMReliesCouleurNombre(int* epCouleur);		
};