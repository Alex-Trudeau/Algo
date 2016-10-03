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
#include "auxiliaires.h"
#include "coordonnees.h"
#include "arret.h"

#include "station.h"
#include "voyage.h"
#include "ligne.h"

using namespace std;

template <typename Object>
void importer(string p_nom_fichier, vector<Object> & p_obj, bool rm_entete){
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier,objs,',',rm_entete);
	for(int i = 0; i < objs.size(); i++){
		p_obj.push_back(Object(objs[i]));
	}
}

int main(){
	vector<Station> v_stations;
	vector<Ligne> v_lignes;

	importer("TXT/stops.txt",v_stations,true);
	importer("TXT/routes.txt",v_lignes,true);


	cout << v_stations.size() << " Stations" << endl;
	cout << v_lignes.size() << " Lignes" << endl;

	return 0;
}
