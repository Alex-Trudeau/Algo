/**
 * \file main.cpp
 * \brief Programme principal
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "reseau.h"
#include "gestionnaire.h"

using namespace std;

struct addresse{
	string addresse;
	Coordonnees coord;
};

std::string tempsTraitement(int p_hrDepart){
	return ("Chargement des données terminé en " + std::to_string((clock()-p_hrDepart)/double(CLOCKS_PER_SEC)) + " secondes");
}

int menu(){
	int retour;
	cout << string(20, '-') << endl;
	cout << "Menu" << endl;
	cout << "1 - Stations à proximité" << endl;
	cout << "2 - Consulter horaire du bus" << endl;
	cout << "3 - Itinéraire" << endl;
	cout << "4 - Stats de connectivité" << endl;
	cout << string(20, '-') << endl;
	cout << "Sélectionner une option en indiquant un chiffre ou autre chose pour quitter:";
	cin >> retour;
	return retour;
}

void stationsProximite(Gestionnaire & g){
	double lat, lon, ray;
	bool valide = false;
	while(!valide){
		cout << "Entrez vos coordonnees GPS" << endl;
		cout << "Latitude: ";
		cin >> lat;
		cout << "Longitude: ";
		cin >> lon;
		if(Coordonnees::is_valide_coord(lat,lon))
			valide = true;
		else{
			cout << "Coordonnees invalides! Appuyer sur une touche pour continuer." << endl;
			cin.ignore();
			cin.get();
		}
	}
	cout << "Entrer un rayon (en Km) pour la recherche: ";
	cin >> ray;
	std::vector<std::pair<double, Station*>> stations = g.trouver_stations_environnantes(Coordonnees(lat,lon),ray);
	if(stations.size() == 0){
		cout << "Aucune station dans le rayon spécifié" << endl;
	}
	else{
		for(auto s = stations.begin(); s != stations.end(); ++s){
			cout << "À une distance de " << (*s).first << "km:" << endl;
			cout << (*s).second->getId() << " - " << (*s).second->getDescription() << endl;
		}
	}
}

template<typename T>
void entreeDonnee(string msg, T & retour){
	cout << msg << ": ";
	cin >> retour;
}

template<typename T>
T entreeDonneeDefaut(T def, string msg){
	cout << msg << " [défaut=" << def << "] : ";
	T retour = def;
	string input;
	cin.clear();
	getline(cin, input);
	if(!input.empty()){
		istringstream stream(input);
		stream >> retour;
	}
	return retour;
}

void horaireBus(Gestionnaire & g){
	unsigned int a,m,j,hr,min,sec,noStation;
	string noBus;
	Date dDef = Date();
	Heure hDef = Heure();
	cout << "Entrez la date désirée" << endl;
	cin.ignore();
	a = entreeDonneeDefaut(dDef.getAn(),"annee");
	m = entreeDonneeDefaut(dDef.getMois(),"mois");
	j = entreeDonneeDefaut(dDef.getJour(),"jour");
	cout << "Entrez l'heure de début désirée" << endl;
	hr = entreeDonneeDefaut(hDef.getHeure(),"heure");
	min = entreeDonneeDefaut(hDef.getMin(),"minutes");
	sec = entreeDonneeDefaut(hDef.getSec(),"secondes");
	entreeDonnee("Entrez le numéro de bus", noBus);
	entreeDonnee("Entrez le numéro de station", noStation);
	Ligne l = g.getLigne(noBus);
	Station s = g.getStation(noStation);
	std::pair<std::string, std::string> dests = g.get_bus_destinations(noStation, noBus);
	vector<Heure> hrs;
	if (dests.second == "")
		hrs = g.trouver_horaire(Date(a,m,j),Heure(hr,min,sec),noBus,noStation,dests.first);
	else{
		cout << "Choisir une destination" << endl;
		cout << "1 - " << dests.first << endl;
		cout << "2 - " << dests.second << endl;
		int choix;
		entreeDonnee("Entrez le numéro correspondant:",choix);
		if(choix == 1)
			hrs = g.trouver_horaire(Date(a,m,j),Heure(hr,min,sec),noBus,noStation,dests.first);
		else
			hrs = g.trouver_horaire(Date(a,m,j),Heure(hr,min,sec),noBus,noStation,dests.second);
	}
	cout << l;
	cout << s.getId() << " - " << s.getDescription() << "\n" <<  endl;
	for(auto it = hrs.begin(); it != hrs.end(); ++it){
		cout << (*it) << endl;
	}
}

void printCarnetAdd(vector<addresse> carnet){
	cout << "Carnet d'adresse" << endl;
	int compteur = 1;
	for(auto it = carnet.begin(); it != carnet.end(); ++it){
		cout << compteur << " - " << (*it).addresse << ": " << (*it).coord << endl;
		compteur ++;
	}
	cout << "sélectionner une addresse en indiquant son numéro: ";
}

void itineraire(Gestionnaire & g, vector<addresse> carnet){
	int d,ar;
	string cD,cA;

	unsigned int a,m,j,hr,min,sec;
	Date dDef = Date();
	Heure hDef = Heure();

	bool valide = false;
	while(!valide){
		cout << "Choisir votre point de départ" << endl;
		printCarnetAdd(carnet);
		cin.ignore();
		cin.clear();
		getline(cin,cD);
		if(!cD.empty()){
			istringstream stream(cD);
			stream >> d;
			if( d <= (int)carnet.size() && d > 0)
				valide = true;
		}
		if(!valide)
			cout << "Choix invalide" << endl;
	}
	valide = false;
	while(!valide){
		cout << "Choisir votre point d'arrivé" << endl;
		printCarnetAdd(carnet);

		cin.clear();
		getline(cin,cA);
		if(!cA.empty()){
			istringstream stream(cA);
			stream >> ar;
			if( ar <= (int)carnet.size() && ar > 0 && ar != d)
				valide = true;
		}
		if(!valide)
			cout << "Choix invalide" << endl;
	}
	Coordonnees dep = carnet[d-1].coord;
	Coordonnees arr = carnet[ar-1].coord;

	cout << "Entrez la date désirée" << endl;
	a = entreeDonneeDefaut(dDef.getAn(),"annee");
	m = entreeDonneeDefaut(dDef.getMois(),"mois");
	j = entreeDonneeDefaut(dDef.getJour(),"jour");
	cout << "Entrez l'heure de début désirée" << endl;
	hr = entreeDonneeDefaut(hDef.getHeure(),"heure");
	min = entreeDonneeDefaut(hDef.getMin(),"minutes");
	sec = entreeDonneeDefaut(hDef.getSec(),"secondes");
	if(!g.date_est_prise_en_charge(Date(a,m,j)))
		throw logic_error("Date non prise en charge par le reseau");
	vector<unsigned int> ch = g.plus_court_chemin(Date(a,m,j),Heure(hr,min,sec),dep,arr);
	for(auto it = ch.begin(); it != ch.end(); ++it){
		if((*it) == 0 || (*it) == 1)
			cout << (*it) << " - " << endl;
		else
			cout << (*it) << " - " << g.getStation((*it)).getDescription() << endl;
	}
}

void reseauFortementConnexe(Gestionnaire & g){
	unsigned int a,m,j,hr,min,sec;
	Date dDef = Date();
	Heure hDef = Heure();

	cout << "Entrez la date désirée" << endl;
	cin.ignore();
	a = entreeDonneeDefaut(dDef.getAn(),"annee");
	m = entreeDonneeDefaut(dDef.getMois(),"mois");
	j = entreeDonneeDefaut(dDef.getJour(),"jour");
	cout << "Entrez l'heure de début désirée" << endl;
	hr = entreeDonneeDefaut(hDef.getHeure(),"heure");
	min = entreeDonneeDefaut(hDef.getMin(),"minutes");
	sec = entreeDonneeDefaut(hDef.getSec(),"secondes");
	if(!g.date_est_prise_en_charge(Date(a,m,j)))
		throw logic_error("Date non prise en charge par le reseau");
	g.reseau_est_fortement_connexe(Date(a,m,j),Heure(hr,min,sec),true);
	g.reseau_est_fortement_connexe(Date(a,m,j),Heure(hr,min,sec),false);
}

int main() {
	int start = clock();
	string chemin = "";

	vector<addresse> carnet;
	carnet.push_back(addresse({"3475 avenue maricourt, Québec",Coordonnees(46.760074,-71.319867)}));
	carnet.push_back(addresse({"2325 vie étudiante, Québec",Coordonnees(46.778398,-71.26853)}));
	carnet.push_back(addresse({"Cineplex odéon sainte-foy",Coordonnees(46.785923,-71.354046)}));
	carnet.push_back(addresse({"Pavillon pouliot",Coordonnees(46.776635,-71.270671)}));
	carnet.push_back(addresse({"2476, avenue des lisieux, québec",Coordonnees(46.857245,-71.206804)}));
	carnet.push_back(addresse({"Pavillon desjardins",Coordonnees(46.778808,-71.270014)}));

	cout << "Bienvenue dans l'application RTC" << endl;

	Gestionnaire g = Gestionnaire(chemin);
	cout << tempsTraitement(start) << endl;

	// Boucle sur le menu tant que le choix est entre 1,2,3 ou 4
	bool fin = false;
	while(!fin){
		int choix = menu();
		switch (choix){
		case 1:
			stationsProximite(g);
			break;
		case 2:
			horaireBus(g);
			break;
		case 3:
			itineraire(g,carnet);
			break;
		case 4:
			reseauFortementConnexe(g);
			break;
		default:
			fin = true;
			cout << "Au revoir!" << endl;
			break;
		}
	}

	// Test composantes fortements connexes
	/*	std::vector<std::vector<unsigned int> > result;
	g.composantes_fortement_connexes(Date(2016,10,5),Heure(20,0,0),result,false);
	cout << result.size() << " Composantes" << endl;*/

	// Test option 1
	/*Coordonnees test = Coordonnees(46.778808,-71.270014);
	std::vector<std::pair<double, Station*>> stations = g.trouver_stations_environnantes(test,0.5);
	if(stations.size() == 0){
		cout << "Aucune station dans le rayon spécifié" << endl;
	}
	else{
		for(auto s = stations.begin(); s != stations.end(); ++s){
			cout << "À une distance de " << (*s).first << "km:" << endl;
			cout << (*s).second->getId() << " - " << (*s).second->getDescription() << endl;
		}
	}*/

	// Test option 2
	/*Ligne l = g.getLigne("800");
	Station s = g.getStation(1515);

	cout << l;
	std::pair<std::string, std::string> dests = g.get_bus_destinations(1515, "800");
	vector<Heure> hrs;
	if (dests.second == "")
		hrs = g.trouver_horaire(Date(2016,10,5),Heure(20,0,0),"800",1515,dests.first);
	else{
		cout << "Choisir une destination" << endl;
		cout << "1 - " << dests.first << endl;
		cout << "2 - " << dests.second << endl;
		int choix;
		entreeDonnee("Entrez le numéro correspondant:",choix);
		if(choix == 1)
			hrs = g.trouver_horaire(Date(2016,10,5),Heure(20,0,0),"800",1515,dests.first);
		else
			hrs = g.trouver_horaire(Date(2016,10,5),Heure(20,0,0),"800",1515,dests.second);
	}
	cout << s.getId() << " - " << s.getDescription() << "\n" <<  endl;
	for(auto it = hrs.begin(); it != hrs.end(); ++it){
		cout << (*it) << endl;
	}*/

	// Test option 3
	/*Coordonnees dep = carnet[5].coord;
	Coordonnees arr = carnet[0].coord;
	vector<unsigned int> ch = g.plus_court_chemin(Date(2016,10,5),Heure(20,0,0),dep,arr);
	for(auto it = ch.begin(); it != ch.end(); ++it){
		if((*it) == 0 || (*it) == 1)
			cout << (*it) << " - " << endl;
		else
			cout << (*it) << " - " << g.getStation((*it)).getDescription() << endl;
	}*/

	// Test option 4
	/*	g.reseau_est_fortement_connexe(Date(2016,10,5),Heure(8,0,0),true);
	g.reseau_est_fortement_connexe(Date(2016,10,5),Heure(8,0,0),false);*/

	return 0;
}
