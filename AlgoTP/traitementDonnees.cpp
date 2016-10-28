/*
 * traitementDonnees.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */
#include "traitementDonnees.h"

using namespace std;

void importerStations(string p_nom_fichier, vector<Station> & p_obj, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (unsigned int i = 0; i < objs.size(); i++) {
		p_obj.push_back(Station(objs[i]));
	}
}

void importerLignes(string p_nom_fichier, vector<Ligne> & p_obj, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (unsigned int i = 0; i < objs.size(); i++) {
		p_obj.push_back(Ligne(objs[i]));
	}
}

void importerVoyages(string p_nom_fichier, vector<Voyage> & p_voyages, vector<Ligne> & p_lignes, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int id_ligne = stoi(objs[i][0]);

		vector<Ligne>::iterator it = find_if(p_lignes.begin(),p_lignes.end(),[id_ligne](const Ligne& lig){return lig.getId() == id_ligne;});
		p_voyages.push_back(Voyage(objs[i],&(*it)));
	}
}

void importerArrets(string p_nom_fichier, map<string,vector<Arret>> & p_arrets, bool rm_entete){
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);

	for (unsigned int i = 0; i < objs.size(); i++) {
		p_arrets[objs[i][0]].push_back(Arret(objs[i]));
	}
}

void importerDates(string p_nom_fichier, map<string,vector<Date>> & p_dates, bool rm_entete){
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int y = stoul(objs[i][1].substr(0,4));
		unsigned int m = stoul(objs[i][1].substr(4,2));
		unsigned int d = stoul(objs[i][1].substr(6,2));
		p_dates[objs[i][0]].push_back(Date(y,m,d));
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

bool triHeureDep(const Voyage* v1, const Voyage* v2){
	return v1->getHeureDepart() < v2->getHeureDepart();
}

void importer(std::vector<Station> & p_s, std::vector<Ligne> & p_l, std::vector<Voyage> & p_v,
		std::map<std::string,std::vector<Arret>> & p_a, std::map<std::string,std::vector<Date>> & p_d){
		// Importation des stations du fichier stops.txt
		importerStations("stops.txt", p_s, true);
		sort(p_s.begin(),p_s.end(),triStationId);	// Tri des stations selon id

		// Importation des lignes du fichier routes.txt
		importerLignes("routes.txt", p_l, true);
		sort(p_l.begin(),p_l.end(),triLigneNumero);	// Tri des lignes selon numero

		// Importation des voyages du fichier trips.txt
		importerVoyages("trips.txt", p_v, p_l, true);
		sort(p_v.begin(),p_v.end(),triVoyageId);	// Tri des voyages selon id
		for (unsigned int i = 0; i < p_v.size(); i++){	// Ajout des voyages dans les lignes
			p_v[i].getLigne()->addVoyage(&p_v[i]);
		}

		// Importation des arrets du fichier stop_times.txt
		importerArrets("stop_times.txt", p_a, true);
		for (unsigned int a = 0; a < p_v.size(); a++){	// Modification des arrets des voyages
			if(p_a.count(p_v[a].getId()))
				p_v[a].setArrets(p_a[p_v[a].getId()]);
		}

		// Importation des dates du fichier calendar_dates.txt
		importerDates("calendar_dates.txt", p_d, true);
}

std::string tempsTraitement(Heure p_hrDepart){
	return ("Chargement des données terminé en " + std::to_string(Heure()-p_hrDepart) + " secondes");
}
