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
#include <map>
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

void importerArrets(string p_nom_fichier, map<string,vector<Arret>> & p_arrets, bool rm_entete){
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);

	for (int i = 0; i < objs.size(); i++) {
		p_arrets[objs[i][0]].push_back(Arret(objs[i]));
	}
}

bool triStationId(const Station& s1, const Station& s2){
	return s1.getId() < s2.getId();
}
bool triLigneNumero(const Ligne& l1,const Ligne& l2){
	return l1.getNumero() < l2.getNumero();
}
bool triVoyageId(const Voyage& v1, const Voyage& v2){
	return v1.getId() < v2.getId();
}
bool triArretNumSeq(const Arret& a1, const Arret& a2){
	return a1.getNumeroSequence() < a2.getNumeroSequence();
}
int main() {
	Heure start = Heure();
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;
	map<string,vector<Arret>> v_arrets;

	importer("TXT/stops.txt", v_stations, true);
	sort(v_stations.begin(),v_stations.end(),triStationId);

	importer("TXT/routes.txt", v_lignes, true);
	sort(v_lignes.begin(),v_lignes.end(),triLigneNumero);

	importerVoyages("TXT/trips.txt", v_voyages, v_lignes, true);
	sort(v_voyages.begin(),v_voyages.end(),triVoyageId);
	for (unsigned int i = 0; i < v_voyages.size(); i++){
		v_voyages[i].getLigne()->addVoyage(&v_voyages[i]);
	}

	importerArrets("TXT/stop_times.txt", v_arrets, true);
	for (unsigned int a = 0; a < v_voyages.size(); a++){
		if(v_arrets.count(v_voyages[a].getId()))
			v_voyages[a].setArrets(v_arrets[v_voyages[a].getId()]);
	}

	cout << "Chargement des données terminé en " << Heure()-start << " secondes" << endl;
	// ### Afficher lignes ordre numero ### ok
	cout << "==================================" << endl;
	cout << "LIGNES DE LA RTC" << endl;
	cout << "COMPTE = " << v_lignes.size() << endl;
	cout << "==================================" << endl;
	for (unsigned int l = 0; l < v_lignes.size(); l++){
		cout << v_lignes[l] << endl;
	}

	// ### Afficher stations ordre numero ### ok
	cout << "==================================" << endl;
	cout << "STATIONS DE LA RTC" << endl;
	cout << "COMPTE = " << v_stations.size() << endl;
	cout << "=====================================" << endl;
	for (unsigned int i=0;i < v_stations.size(); i++){
		cout << v_stations[i] << endl;
	}

	//cout << "==================================" << endl;
	//cout << "VOYAGES DE LA JOURNÉE DU " << currentDate << endl;
	//cout << heureActuel << " - " << HeureActuel+1 << endl;
	//cout << "COMPTE = " << v_stations.size() << endl;
	//cout << "=====================================" << endl;


	return 0;
}
