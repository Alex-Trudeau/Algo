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

using namespace std;

int main() {
	Heure start = Heure();
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;
	map<string,vector<Arret>> v_arrets;
	map<string,vector<Date>> v_datesVoyage;

	// Importation de tous les fichiers nécessaires
	importer(v_stations, v_lignes, v_voyages, v_arrets, v_datesVoyage);

	// Affichage du temps d'exécution du chargement des données
	cout << tempsTraitement(start) << endl;

	// TP1
	ofstream ecriture;
	ecriture.open("FichierSortie.txt");
	tp1(ecriture,v_lignes,v_stations,v_voyages,v_datesVoyage);
	ecriture.close();	// Fermer le fichier d'écriture

	// TP2





	return 0;
}
