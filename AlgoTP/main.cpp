/**
 * \file main.cpp
 * \brief Programme principal
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include "ContratException.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "arret.h"
#include "station.h"
#include "voyage.h"
#include "ligne.h"
#include "traitementDonnees.h"
#include "affichage.h"
#include "reseau.h"

using namespace std;

int main() {
	Heure start = Heure();
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;
	map<string,vector<Arret>> v_arrets;
	map<string,vector<Date>> v_datesVoyage;

	// Importation de tous les fichiers nécessaires
	//importer(v_stations, v_lignes, v_voyages, v_arrets, v_datesVoyage);

	// Affichage du temps d'exécution du chargement des données
	cout << tempsTraitement(start) << endl;

	// TP1
	//ofstream ecriture;
	//ecriture.open("FichierSortie.txt");
	//tp1(ecriture,v_lignes,v_stations,v_voyages,v_datesVoyage);
	//ecriture.close();	// Fermer le fichier d'écriture

	// TP2
	Reseau rs = Reseau();
	rs.ajouterSommet(1);
	rs.ajouterSommet(2);
	rs.ajouterSommet(3);
	rs.ajouterSommet(4);
	rs.ajouterSommet(5);
	rs.ajouterSommet(6);
	rs.ajouterSommet(7);
	rs.ajouterSommet(8);
	rs.ajouterSommet(9);
	rs.ajouterSommet(10);
	rs.ajouterSommet(11);
	rs.ajouterSommet(12);

	rs.ajouterArc(1,2,1);
	rs.ajouterArc(2,3,1);
	rs.ajouterArc(2,4,1);
	rs.ajouterArc(2,5,1);
	rs.ajouterArc(3,6,1);
	rs.ajouterArc(5,2,1);
	rs.ajouterArc(5,6,1);
	rs.ajouterArc(6,3,1);
	rs.ajouterArc(5,7,1);
	rs.ajouterArc(6,8,1);
	rs.ajouterArc(7,8,1);
	rs.ajouterArc(7,10,1);
	rs.ajouterArc(8,11,1);
	rs.ajouterArc(9,7,1);
	rs.ajouterArc(10,9,1);
	rs.ajouterArc(11,12,1);
	rs.ajouterArc(12,10,1);

	cout << rs.nombreSommets() << " && " << rs.nombreArcs() << endl;
	vector<vector<unsigned int>> v_ret;
	int nbCompos = rs.getComposantesFortementConnexes(v_ret);
	cout << nbCompos << endl;
	for(int i = 0; i < nbCompos; i++){
		cout << i << " : {" ;
		for(unsigned int j =0; j < v_ret[i].size() ; j++){
			cout << v_ret[i][j] << ", ";
		}
		cout << endl;
	}
	/*vector<unsigned int> retour;

	int valeur = rs.bellmanFord(1,12,retour);

	cout << "Le chemin le plus court est :" <<endl;

	for(int i =0; i< retour.size(); ++i){
		cout << retour[i];
	}

	cout << endl;
	cout << "et de valeur :" << valeur << endl;*/
	return 0;
}
