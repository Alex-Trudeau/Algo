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

using namespace std;

template<typename Object>
void importer(string p_nom_fichier, vector<Object> & p_obj, bool rm_entete) {
	vector<vector<string>> objs;
	lireFichier(p_nom_fichier, objs, ',', rm_entete);
	for (unsigned int i = 0; i < objs.size(); i++) {
		p_obj.push_back(Object(objs[i]));
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
int main() {
	Heure start = Heure();
	vector<Station> v_stations;
	vector<Ligne> v_lignes;
	vector<Voyage> v_voyages;
	map<string,vector<Arret>> v_arrets;
	map<string,vector<Date>> v_datesVoyage;

	// Importation des stations du fichier stops.txt
	importer("stops.txt", v_stations, true);
	sort(v_stations.begin(),v_stations.end(),triStationId);	// Tri des stations selon id

	// Importation des lignes du fichier routes.txt
	importer("routes.txt", v_lignes, true);
	sort(v_lignes.begin(),v_lignes.end(),triLigneNumero);	// Tri des lignes selon numero

	// Importation des voyages du fichier trips.txt
	importerVoyages("trips.txt", v_voyages, v_lignes, true);
	sort(v_voyages.begin(),v_voyages.end(),triVoyageId);	// Tri des voyages selon id
	for (unsigned int i = 0; i < v_voyages.size(); i++){	// Ajout des voyages dans les lignes
		v_voyages[i].getLigne()->addVoyage(&v_voyages[i]);
	}

	// Importation des arrets du fichier stop_times.txt
	importerArrets("stop_times.txt", v_arrets, true);
	for (unsigned int a = 0; a < v_voyages.size(); a++){	// Modification des arrets des voyages
		if(v_arrets.count(v_voyages[a].getId()))
			v_voyages[a].setArrets(v_arrets[v_voyages[a].getId()]);
	}

	// Importation des dates du fichier calendar_dates.txt
	importerDates("calendar_dates.txt", v_datesVoyage, true);

	// Affichage du temps d'exécution du chargement des données
	cout << "Chargement des données terminé en " << Heure()-start << " secondes" << endl;

	// Ouverture d'un fichier texte pour écriture
	ofstream ecriture;
	ecriture.open("FichierSortie.txt");

	// Ecriture des lignes par ordre de leur numero
	ecriture << "==================================" << endl;
	ecriture << "LIGNES DE LA RTC" << endl;
	ecriture << "COMPTE = " << v_lignes.size() << endl;
	ecriture << "==================================" << endl;
	for (unsigned int l = 0; l < v_lignes.size(); l++){
		ecriture << v_lignes[l] << endl;
	}

	// Ecriture des stations par ordre de leur numero
	ecriture << "==================================" << endl;
	ecriture << "STATIONS DE LA RTC" << endl;
	ecriture << "COMPTE = " << v_stations.size() << endl;
	ecriture << "=====================================" << endl;
	for (unsigned int i=0;i < v_stations.size(); i++){
		ecriture << v_stations[i] << endl;
	}

	// Definition des variables de la date et heure actuelle
	Date currentDate = Date();
	Heure now = Heure();
	// Definition d'une variable pour l'heure future dans une heure
	Heure inOneHour = now.add_secondes(3600);
	// Definition d'un vecteur de voyages opérationnels au courant de la journée
	// et dans la prochaine heure
	vector<Voyage*> voyages2d;
	// Ecriture des voyages de la journée et dans l'heure actuelle
	// en ordre d'heure de départ
	ecriture << "==================================" << endl;
	ecriture << "VOYAGES DE LA JOURNÉE DU " << currentDate << endl;
	ecriture << now << " - " << inOneHour << endl;
	ecriture << "COMPTE = " << v_stations.size() << endl;
	ecriture << "=====================================" << endl;
	for (unsigned int v = 0; v < v_voyages.size(); v++){
		vector<Date> dt = v_datesVoyage[v_voyages[v].getServiceId()];	// Extraire les dates opérationnels du service_id
		vector<Date>::iterator it = find(dt.begin(), dt.end(), currentDate); // Trouver la date courrante dans les dates de service_id
		if(v_voyages[v].getHeureDepart() > now &&			// Si le départ apres heure actuelle
				v_voyages[v].getHeureFin() < inOneHour &&	// Si la fin avant dans une heure
				it != dt.end()){							// Si le voyage est opérationnel aujourd'hui
			voyages2d.push_back(&v_voyages[v]);				// Ajout dans le vecteur de voyage opérationnel
		}
	}
	sort(voyages2d.begin(),voyages2d.end(), triHeureDep);	// Tri du vecteur de voyages opérationnels selon l'heure de depart
	for(unsigned int vt = 0; vt < voyages2d.size(); vt++){
		ecriture << (*voyages2d[vt]) << endl;				// Ecrire le voyage
		for (unsigned int a = 0; a < voyages2d[vt]->getArrets().size(); a++){
			ecriture << voyages2d[vt]->getArrets()[a] << endl;	// Ecrire les arrets du voyage
		}
	}

	ecriture.close();	// Fermer le fichier d'écriture
	return 0;
}
