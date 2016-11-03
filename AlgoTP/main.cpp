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
#include <algorithm>
#include "reseau.h"
#include "gestionnaire.h"

using namespace std;

struct addresse{
	string addresse;
	Coordonnees coord;
};

std::string tempsTraitement(Heure p_hrDepart){
	return ("Chargement des données terminé en " + std::to_string(Heure()-p_hrDepart) + " secondes");
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
			cout << "À une distance de " << (*s).first << "km" << endl;
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
	vector<Heure> hrs = g.trouver_horaire(Date(a,m,j),Heure(hr,min,sec),noBus,noStation,"");
	cout << Date(a,m,j) << Heure(hr,min,sec) << noBus << noStation << endl;
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
		getline(cin,cD);
		if(!cD.empty()){
			istringstream stream(cD);
			stream >> d;
			if( d < carnet.size() && d > 0)
				valide = true;
		}
		if(!valide)
			cout << "Choix invalide" << endl;
	}
	valide = false;
	while(!valide){
		cout << "Choisir votre point d'arrivé" << endl;
		printCarnetAdd(carnet);

		cin.ignore();
		getline(cin,cA);
		if(!cA.empty()){
			istringstream stream(cA);
			stream >> ar;
			if( ar < carnet.size() && ar > 0)
				valide = true;
		}
		if(!valide)
			cout << "Choix invalide" << endl;
	}
	Coordonnees dep = carnet[d].coord;
	Coordonnees arr = carnet[ar].coord;

	cout << "Entrez la date désirée" << endl;
	cin.ignore();
	a = entreeDonneeDefaut(dDef.getAn(),"annee");
	m = entreeDonneeDefaut(dDef.getMois(),"mois");
	j = entreeDonneeDefaut(dDef.getJour(),"jour");
	cout << "Entrez l'heure de début désirée" << endl;
	hr = entreeDonneeDefaut(hDef.getHeure(),"heure");
	min = entreeDonneeDefaut(hDef.getMin(),"minutes");
	sec = entreeDonneeDefaut(hDef.getSec(),"secondes");

	cout << "Initialisation du réseau ...." << endl;

	cout << "Recherche du plus court chemin" << endl;
	/* ------------------------------------------------------------------------------- */




}

int main() {
	Heure start = Heure();
	string chemin = "/home/xub-msi/Test/";

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
			break;
		default:
			fin = true;
			cout << "Au revoir!" << endl;
			break;
		}
	}


	/*Reseau rs = Reseau();
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
	*/
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
