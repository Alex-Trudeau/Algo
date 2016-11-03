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
	importerTout();
}

bool Gestionnaire::date_est_prise_en_charge(const Date& date) {
	return m_voyages_dates.count(date);
}

bool Gestionnaire::bus_existe(std::string num_ligne) {
	return m_lignes.count(num_ligne);
}

bool Gestionnaire::station_existe(int station_id) {
	return m_stations.count(station_id);
}

Ligne Gestionnaire::getLigne(std::string num_ligne) {
	if(!bus_existe(num_ligne))
		throw logic_error("La ligne n'existe pas");
	return m_lignes.at(num_ligne);
}

Station Gestionnaire::getStation(int station_id) {
	if(!station_existe(station_id))
			throw logic_error("La station n'existe pas");
	return m_stations.at(station_id);
}

// Voyages d'une ligne passant par une station
std::vector<Voyage*> Gestionnaire::trouver_voyages(int station_id, std::string num_ligne){
	if(!bus_existe(num_ligne))
		throw logic_error("Cette ligne n'existe pas");
	if(!station_existe(station_id))
		throw logic_error("Cette station n'existe pas");

	vector<Voyage*> retour;
	vector<Voyage*> v = getStation(station_id).getVoyagesPassants();
	for(auto it = v.begin();it != v.end();++it){
		if((*it)->getLigne()->getNumero() == num_ligne)
			retour.push_back((*it));
	}
	return retour;
}

// Destinations des voyages d'une ligne passant par une station
std::pair<std::string, std::string> Gestionnaire::get_bus_destinations(
		int station_id, std::string num_ligne) {
	if(!bus_existe(num_ligne))
		throw logic_error("Cette ligne n'existe pas");
	if(!station_existe(station_id))
		throw logic_error("Cette station n'existe pas");
	vector<Ligne*> v = getStation(station_id).getLignesPassantes();
	for(auto it = v.begin();it != v.end();++it){
		if((*it)->getNumero() == num_ligne)
			return (*it)->getDestinations();
	}
	return {};
}

std::vector<std::pair<double, Station*> > Gestionnaire::trouver_stations_environnantes(
		Coordonnees coord, double rayon) {
	std::vector<std::pair<double, Station*> > retour;
	for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
		double temp = (*it).second.getCoords()-coord;
		if(temp <= rayon)
			retour.push_back({temp,&(*it).second});
	}
	sort(retour.begin(),retour.end());
	return retour;
}

std::vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure,
		std::string num_ligne, int station_id, std::string destination) {
	std::vector<Heure> retour;
	std::vector<Voyage*> vDeLigStat = trouver_voyages(station_id, num_ligne);
	std::unordered_map<std::string, Voyage*> voyDate = m_voyages_dates[date];
	for(auto it = vDeLigStat.begin(); it != vDeLigStat.end(); ++it){
		string idVoy = (*it)->getId();
		if(voyDate.count(idVoy)){ 						// && (*it)->getDestination() == destination
			vector<Arret> arrets = (*it)->getArrets();
			for(auto a = arrets.begin(); a != arrets.end(); ++a){
				if((*a).getHeureArrivee() > heure && (*a).getStationId() == station_id){
					retour.push_back((*a).getHeureArrivee());
				}
			}
		}
	}
	sort(retour.begin(),retour.end());
	//cout << c << " Voyages dans la plage horaire" << endl;
	return retour;
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
	m_reseau = Reseau();
	std::unordered_map<std::string, Voyage*> voyDate = m_voyages_dates[date];
	m_reseau.ajouterSommet(num_depart);
	m_reseau.ajouterSommet(num_dest);
	for(auto s = m_stations.begin(); s != m_stations.end(); ++s){
		m_reseau.ajouterSommet((*s).first);
	}

	for(auto v = voyDate.begin(); v != voyDate.end(); ++v){
		vector<Arret> va = (*v).second->getArrets();
		for(auto a = va.begin(); a != va.end()-1; ++a){
			unsigned int u = (*a).getStationId();
			unsigned int v = (*(a+1)).getStationId();
			unsigned int c = (*a).getHeureArrivee()-(*a).getHeureDepart();
			if(m_reseau.arcExiste(u,v)){
				if(m_reseau.getCoutArc(u,v) > c)
					m_reseau.majCoutArc(u,v,c);
			}
			else
				m_reseau.ajouterArc(u,v,c);
		}
	}
	std::vector<std::pair<double, Station*>>env0 = trouver_stations_environnantes(depart,dist_de_marche);
	for(auto e0 = env0.begin(); e0 != env0.end(); ++e0){
		unsigned int v = (*e0).second->getId();
		unsigned int c = (*e0).first*3600/vitesse_de_marche;
		if(m_reseau.arcExiste(0,v)){
			if(m_reseau.getCoutArc(0,v) > c){
				if(m_reseau.getTypeArc(0,v) != 1){
					m_reseau.enleverArc(0,v);
					m_reseau.ajouterArc(0,v,c,1);
				}
				m_reseau.majCoutArc(0,v,c);
			}
		}
		else
			m_reseau.ajouterArc(0,v,c,1);
	}

	std::vector<std::pair<double, Station*>>env1 = trouver_stations_environnantes(dest,dist_de_marche);
	for(auto e1 = env1.begin(); e1 != env1.end(); ++e1){
		unsigned int v = (*e1).second->getId();
		unsigned int c = (*e1).first*3600/vitesse_de_marche;
		if(m_reseau.arcExiste(v,1)){
			if(m_reseau.getCoutArc(v,1) > c){
				if(m_reseau.getTypeArc(v,1) != 1){
					m_reseau.enleverArc(v,1);
					m_reseau.ajouterArc(v,1,c,1);
				}
				m_reseau.majCoutArc(v,1,c);
			}
		}
		else
		m_reseau.ajouterArc(v,1,c,1);
	}
	for(auto s = m_stations.begin(); s != m_stations.end(); ++s){
		std::vector<std::pair<double, Station*>> se = trouver_stations_environnantes((*s).second.getCoords(),dist_transfert);
		for(auto e = se.begin(); e != se.end(); ++e){
			unsigned int u = (*s).first;
			unsigned int v = (*e).second->getId();
			unsigned int c = (*e).first*3600/vitesse_de_marche;
			if(m_reseau.arcExiste(u,v)){
				if(m_reseau.getCoutArc(u,v) > c){
					if(m_reseau.getTypeArc(u,v) != 1){
						m_reseau.enleverArc(u,v);
						m_reseau.ajouterArc(u,v,c,1);
					}
					m_reseau.majCoutArc(u,v,c);
				}
			}
			else
				m_reseau.ajouterArc(u,v,c,1);

			if(m_reseau.arcExiste(v,u)){
				if(m_reseau.getCoutArc(v,u) > c){
					if(m_reseau.getTypeArc(v,u) != 1){
						m_reseau.enleverArc(v,u);
						m_reseau.ajouterArc(v,u,c,1);
					}
					m_reseau.majCoutArc(v,u,c);
				}
			}
			else
				m_reseau.ajouterArc(v,u,c,1);
		}
	}
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
		unsigned int id_station = stoi(objs[i][2]);
		p_arrets[id_voyage].push_back(Arret(objs[i]));

	}

	for (auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
		string id_voyage = (*it).second.getId();
		if(p_arrets.count(id_voyage)){
			sort(p_arrets.at(id_voyage).begin(),p_arrets.at(id_voyage).end());
			m_voyages.at(id_voyage).setArrets(p_arrets.at(id_voyage));
			vector<Arret> va = p_arrets[id_voyage];
			for(auto a = va.begin(); a != va.end(); ++a){
				unsigned int s = (*a).getStationId();
				m_stations.at(s).addVoyage(&(*it).second);
			}
		}
	}

}
void Gestionnaire::importerDatesVoyages(){
	string fichier = m_repertoireGTFS + "calendar_dates.txt";
	vector<vector<string>> objs;
	lireFichier(fichier, objs, ',', true);
	unordered_map<string,vector<Date>> dateService;
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int y = stoi(objs[i][1].substr(0,4));
		unsigned int m = stoi(objs[i][1].substr(4,2));
		unsigned int d = stoi(objs[i][1].substr(6,2));
		string id = objs[i][0];
		dateService[id].push_back(Date(y,m,d));
	}
	for (auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
		string s = (*it).second.getServiceId();
		Voyage v = (*it).second;
		vector<Date> d = dateService[s];
		for(auto dt = d.begin(); dt != d.end(); ++dt){
			m_voyages_dates[*dt].insert({v.getId(),&v});
		}
	}
	/*unordered_map<string,vector<Voyage*>> serviceVoyages;
	for (auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
		string s = (*it).second.getServiceId();
		Voyage v = (*it).second;
		serviceVoyages[s].push_back(&v);
	}
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int y = stoi(objs[i][1].substr(0,4));
		unsigned int m = stoi(objs[i][1].substr(4,2));
		unsigned int d = stoi(objs[i][1].substr(6,2));
		string id = objs[i][0];
		cout << serviceVoyages[id].size() << " voyages pour le service id " << id << endl;
		for(auto it = serviceVoyages[id].begin(); it != serviceVoyages[id].end(); ++it){
			string idVoy = (*it)->getId();
			m_voyages_dates[Date(y,m,d)].insert({idVoy, (*it)});
		}
		//m_voyages_dates[Date(y,m,d)].insert(end,serviceVoyages[id].begin(),);
	}*/
}

void Gestionnaire::importerTout(){
	importerLignes();
	importerStations();
	importerVoyages();
	importerArrets();
	importerDatesVoyages();
}


