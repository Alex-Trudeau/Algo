/*
 * affichage.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */

#include "affichage.h"

using namespace std;

// Ecriture des lignes par ordre de leur numero
void afficherLignesTrieesNo(std::ofstream & p_fichier, std::vector<Ligne> & p_lignes){

	p_fichier << "==================================" << endl;
	p_fichier << "LIGNES DE LA RTC" << endl;
	p_fichier << "COMPTE = " << p_lignes.size() << endl;
	p_fichier << "==================================" << endl;
	for (unsigned int l = 0; l < p_lignes.size(); l++){
		p_fichier << p_lignes[l] << endl;
	}
}

// Ecriture des stations par ordre de leur numero
void afficherStationsTrieesNo(std::ofstream & p_fichier, std::vector<Station> & p_stations){

	p_fichier << "==================================" << endl;
	p_fichier << "STATIONS DE LA RTC" << endl;
	p_fichier << "COMPTE = " << p_stations.size() << endl;
	p_fichier << "=====================================" << endl;
	for (unsigned int i=0;i < p_stations.size(); i++){
		p_fichier << p_stations[i] << endl;
	}
}

void afficherVoyagesProchaineHeure(std::ofstream & p_fichier, std::vector<Voyage> & p_voyages,
		std::map<std::string,std::vector<Date>> & p_dates){

	// Definition des variables de la date et heure actuelle
	Date currentDate = Date();
	Heure now = Heure();

	// Definition d'une variable pour l'heure future dans une heure
	Heure inOneHour = now.add_secondes(3600);

	// Definition d'un vecteur de voyages opérationnels au courant de la journée
	// et dans la prochaine heure
	vector<Voyage*> voyages2d;

	for (unsigned int v = 0; v < p_voyages.size(); v++){
		vector<Date> dt = p_dates[p_voyages[v].getServiceId()];	// Extraire les dates opérationnels du service_id
		vector<Date>::iterator it = find(dt.begin(), dt.end(), currentDate); // Trouver la date courrante dans les dates de service_id
		if(p_voyages[v].getHeureDepart() > now &&			// Si le départ apres heure actuelle
				p_voyages[v].getHeureFin() < inOneHour &&	// Si la fin avant dans une heure
				it != dt.end()){							// Si le voyage est opérationnel aujourd'hui
			voyages2d.push_back(&p_voyages[v]);				// Ajout dans le vecteur de voyage opérationnel
		}
	}

	sort(voyages2d.begin(),voyages2d.end(), triHeureDep);	// Tri du vecteur de voyages opérationnels selon l'heure de depart

	// Ecriture des voyages de la journée et dans l'heure actuelle
	// en ordre d'heure de départ
	p_fichier << "==================================" << endl;
	p_fichier << "VOYAGES DE LA JOURNÉE DU " << currentDate << endl;
	p_fichier << now << " - " << inOneHour << endl;
	p_fichier << "COMPTE = " << voyages2d.size() << endl;
	p_fichier << "=====================================" << endl;
	for(unsigned int vt = 0; vt < voyages2d.size(); vt++){
		p_fichier << (*voyages2d[vt]) << endl;				// Ecrire le voyage
		for (unsigned int a = 0; a < voyages2d[vt]->getArrets().size(); a++){
			p_fichier << voyages2d[vt]->getArrets()[a] << endl;	// Ecrire les arrets du voyage
		}
	}
}

void tp1(std::ofstream & p_f, std::vector<Ligne> & p_l, std::vector<Station> & p_s,
		std::vector<Voyage> & p_v, std::map<std::string,std::vector<Date>> & p_d){
	afficherLignesTrieesNo(p_f,p_l);
	afficherStationsTrieesNo(p_f,p_s);
	afficherVoyagesProchaineHeure(p_f,p_v,p_d);
}

