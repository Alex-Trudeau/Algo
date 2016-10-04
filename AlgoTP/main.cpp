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
	}
}

bool triNumeroLigne(const Ligne& l1,const Ligne& l2){
	return l1.getNumero() < l2.getNumero();
}
bool triVoyageId(const Voyage& v1, const Voyage& v2){
	return v1.getId() < v2.getId();
}
int main() {
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;
	vector<Arret> v_arrets;

	importer("TXT/stops.txt", v_stations, true);

	importer("TXT/routes.txt", v_lignes, true);
	sort(v_lignes.begin(),v_lignes.end(),triNumeroLigne);

	importerVoyages("TXT/trips.txt", v_voyages, v_lignes, true);
	sort(v_voyages.begin(),v_voyages.end(),triVoyageId);

	for (int i = 0; i < v_voyages.size(); i++){
		v_voyages[i].getLigne()->addVoyage(&v_voyages[i]);
	}

	//importer("TXT/stop_times.txt", v_arrets, true);



	cout << v_stations.size() << " Stations" << endl;
	cout << v_lignes.size() << " Lignes" << endl;
	cout << v_voyages.size() << " Voyages" << endl;
	cout << v_arrets.size() << " Arrets" << endl;

	//cout << (*v_lignes[0].getVoyages()[0]) << endl;


	// ### Afficher lignes ordre numero
	for (int l = 0; l < v_lignes.size(); l++){
		cout << v_lignes[l] << endl;
	}

	// ### Afficher stations ### Manque ordre numero
	/*for (unsigned int i=0;i < v_stations.size(); i++){
		cout << v_stations[i] << endl;
	}*/

	return 0;
}
