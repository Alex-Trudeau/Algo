/*
 * main.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "ContratException.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "arret.h"
#include "station.h"
#include "voyage.h"
#include "ligne.h"

using namespace std;

template<typename Object>
void importer(string p_nom_fichier, vector<Object> & p_obj, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (int i = 0; i < objs.size(); i++) {
		p_obj.push_back(Object(objs[i]));
	}
}

void importerVoyages(string p_nom_fichier, vector<Voyage> & p_voyages, vector<Ligne> & p_lignes, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (int i = 0; i < objs.size(); i++) {
		unsigned int id_ligne = stoi(objs[i][0]);

		vector<Ligne>::iterator it = find_if(p_lignes.begin(),p_lignes.end(),[id_ligne](const Ligne& lig){return lig.getId() == id_ligne;});
		p_voyages.push_back(Voyage(objs[i],&(*it)));
		(*it).addVoyage(&(p_voyages.back()));
	}
}

int main() {
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;

	importer("TXT/stops.txt", v_stations, true);
	importer("TXT/routes.txt", v_lignes, true);
	importerVoyages("TXT/trips.txt", v_voyages, v_lignes, true);

	cout << v_stations.size() << " Stations" << endl;
	cout << v_lignes.size() << " Lignes" << endl;
	cout << v_voyages.size() << " Voyages" << endl;

	for (int i = 0; i < v_lignes.size(); i++){
		cout << "#################################" << endl;
		cout << v_lignes[i] << endl;
		cout << "#################################" << endl;
		/*vector<Voyage*> voyages = v_lignes[i].getVoyages();

		for(int j =0 ; j< voyages.size(); j++){
			cout << voyages[j] << endl;
		}*/
	}

	return 0;
}
