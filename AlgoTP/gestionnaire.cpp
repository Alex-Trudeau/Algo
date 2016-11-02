#include "gestionnaire.h"

using namespace std;

Gestionnaire::Gestionnaire(std::string chemin_dossier) :
	m_repertoireGTFS(chemin_dossier){
	vector<string> f_names = {"routes","trips","stop_times","stops","calendar_dates"};
	for(auto it = f_names.begin(); it != f_names.end(); ++it){
		ifstream fichier(chemin_dossier+(*it)+".txt");
		if(!fichier.good())
			throw logic_error((*it)+".txt n'existe pas dans le chemin spécifié");
	}
	importerLignes();
	importerStations();
	importerVoyages();
	importerArrets();
}

bool Gestionnaire::date_est_prise_en_charge(const Date& date) {
	return (m_voyages_dates.count(date));
}

bool Gestionnaire::bus_existe(std::string num_ligne) {

}

bool Gestionnaire::station_existe(int station_id) {

}

Ligne Gestionnaire::getLigne(std::string num_ligne) {

}

Station Gestionnaire::getStation(int station_id) {
	cout << m_stations[station_id].getLignesPassantes().size();
}

std::pair<std::string, std::string> Gestionnaire::get_bus_destinations(
		int station_id, std::string num_ligne) {

}

std::vector<std::pair<double, Station*> > Gestionnaire::trouver_stations_environnantes(
		Coordonnees coord, double rayon) {

}

std::vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure,
		std::string numero_ligne, int station_id, std::string destination) {

}

bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut,
		bool considerer_transfert) {

}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
		std::vector<std::vector<unsigned int> >& composantes,
		bool considerer_transfert) {

}

std::vector<unsigned int> Gestionnaire::plus_court_chemin(Date date,
		Heure heure_depart, Coordonnees depart, Coordonnees destination) {

}

void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart,
		Heure heure_fin, Coordonnees depart, Coordonnees dest,
		double dist_de_marche, double dist_transfert) {

}

void Gestionnaire::importerLignes(){
	string fichier = m_repertoireGTFS + "routes.txt";
	vector<vector<string>> objs;
	lireFichier(fichier, objs, ',', true);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int id = stoi(objs[i][0]);
		string no = objs[i][2];
		if(!m_lignes.count(no))
			m_lignes.insert({no,Ligne(objs[i])});
		m_idNoLigne.insert({id,no});
	}
}
void Gestionnaire::importerStations(){
	string fichier = m_repertoireGTFS + "stops.txt";
	vector<vector<string>> objs;
	lireFichier(fichier, objs, ',', true);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int id = stoi(objs[i][0]);
		m_stations.insert({id, Station(objs[i])});
	}
}
void Gestionnaire::importerVoyages(){
	string fichier = m_repertoireGTFS + "trips.txt";
	vector<vector<string>> objs;
	lireFichier(fichier, objs, ',', true);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int id_l = stoi(objs[i][0]);
		string no_l = m_idNoLigne.at(id_l);
		string id_v = objs[i][2];
		m_voyages.insert({id_v, Voyage(objs[i],&m_lignes.at(no_l))});
		m_lignes.at(no_l).addVoyage(&m_voyages.at(id_v));
	}
}
void Gestionnaire::importerArrets(){
	string fichier = m_repertoireGTFS + "stop_times.txt";
	vector<vector<string>> objs;
	unordered_map<string,vector<Arret>> p_arrets;
	lireFichier(fichier, objs, ',', true);
	for (unsigned int i = 0; i < objs.size(); i++) {
		string id_voyage = objs[i][0];
		p_arrets[id_voyage].push_back(Arret(objs[i]));
	}
	for (auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
		string id_voyage = (*it).second.getId();
		if(p_arrets.count(id_voyage)){
			sort(p_arrets.at(id_voyage).begin(),p_arrets.at(id_voyage).end());
			m_voyages.at(id_voyage).setArrets(p_arrets.at(id_voyage));
		}
	}
}
void Gestionnaire::importerDatesVoyages(){
	string fichier = m_repertoireGTFS + "calendar_dates.txt";
	vector<vector<string>> objs;
	lireFichier(fichier, objs, ',', true);
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int y = stoul(objs[i][1].substr(0,4));
		unsigned int m = stoul(objs[i][1].substr(4,2));
		unsigned int d = stoul(objs[i][1].substr(6,2));
		string id_voyage = objs[i][0];
		m_voyages_dates[Date(y,m,d)].push_back(&m_voyages.at(id_voyage));
	}
}
void Gestionnaire::importerTout(){
	importerLignes();
	importerStations();
	importerVoyages();
	importerArrets();
	importerDatesVoyages();
}



