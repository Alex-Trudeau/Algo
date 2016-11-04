#include "gestionnaire.h"

using namespace std;

Gestionnaire::Gestionnaire(std::string chemin_dossier) :
	m_repertoireGTFS(chemin_dossier){
	vector<string> f_names = {"routes","trips","stop_times","stops","calendar_dates"};
	for(auto it = f_names.begin(); it != f_names.end(); ++it){
		string dir = chemin_dossier+(*it)+".txt";
		ifstream fichier(dir);
		if(!fichier.good())
			throw logic_error((*it)+".txt n'existe pas dans le chemin spécifié");
	}
	importerTout();

	vector<Voyage*> v = m_stations.at(1515).getVoyagesPassants();
	cout << v.size() << endl;

}

bool Gestionnaire::date_est_prise_en_charge(const Date& date) {
	return m_voyages_date.count(date);
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
	string d1 = "";
	string d2 = "";
	vector<Voyage*> v = getStation(station_id).getVoyagesPassants();

	for(auto it = v.begin();it != v.end();++it){
		if((*it)->getLigne()->getNumero() == num_ligne){
			if(d1 == "")
				d1 = (*it)->getDestination();
			else if (d1 != (*it)->getDestination()){
				d2 = (*it)->getDestination();
				return {d1,d2};
			}
		}
	}
	return {d1,d2};
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
	std::unordered_map<std::string, Voyage*> voyDate = m_voyages_date[date];
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
	return retour;
}

bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut,
		bool considerer_transfert) {
	Heure heure_fin = heure_debut.add_secondes(interval_planification_en_secondes);
	Coordonnees fake = Coordonnees(46,-71);
	if(considerer_transfert){
		initialiser_reseau(date,heure_debut,heure_fin,fake,fake,0.0,distance_max_transfert);
		int estCon = m_reseau.estFortementConnexe();
		if(estCon)
			cout << "Avec les arêtes de transfert, le réseau est fortement connexe." << endl;
		else
			cout << "Avec les arêtes de transfert, le réseau n'est pas fortement connexe." << endl;
		return estCon;
	}
	else{
		initialiser_reseau(date,heure_debut,heure_fin,fake,fake,0.0,0.0);
		int estCon = m_reseau.estFortementConnexe();
		if(estCon)
			cout << "Sans les arêtes de transfert, le réseau est fortement connexe." << endl;
		else
			cout << "Sans les arêtes de transfert, le réseau n'est pas fortement connexe." << endl;
		return estCon;
	}
}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
		std::vector<std::vector<unsigned int> >& composantes,
		bool considerer_transfert) {

}

std::vector<unsigned int> Gestionnaire::plus_court_chemin(Date date,
		Heure heure_depart, Coordonnees depart, Coordonnees destination) {
	Heure heure_fin = heure_depart.add_secondes(interval_planification_en_secondes);
	cout << "Initialisation du réseau ...." << endl;
	initialiser_reseau(date,heure_depart,heure_fin,depart,destination,distance_max_initiale,distance_max_transfert);
	cout << "Recherche du plus court chemin" << endl;
	vector<unsigned int> chemin;
	//m_reseau.dijkstra(num_depart,num_dest,chemin);
	m_reseau.bellmanFord(num_depart,num_dest,chemin);
	/*for(int i = 0; i < chemin.size(); i++){
		if(chemin[i] == 1)
			cout << chemin[i] << " - " << endl;
		else{
			int u = chemin[i];
			int v = chemin[i+1];
			int t = m_reseau.getTypeArc(u,v);
			string typ;
			if(t==0)
				typ = "BUS";
			else
				typ = "Pied";
			cout << u << " - " << v << " (" << typ << ")" << endl;
		}
	}*/
	return chemin;
}

void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart,
		Heure heure_fin, Coordonnees depart, Coordonnees dest,
		double dist_de_marche, double dist_transfert) {
	m_reseau = Reseau();
	std::unordered_map<std::string, Voyage*> voyDate = m_voyages_date[date];
	std::vector<unsigned int> stations;

	// Ajout des 2 sommets fictifs
	if(dist_de_marche != 0.0){
		m_reseau.ajouterSommet(num_depart);
		m_reseau.ajouterSommet(num_dest);

		// Ajout des arcs de départ aux stations environnantes
		std::vector<std::pair<double, Station*>> stEnv0 = trouver_stations_environnantes(depart, dist_de_marche);
		for(auto s = stEnv0.begin(); s != stEnv0.end(); ++s){
			unsigned int u = num_depart;
			unsigned int v = (*s).second->getId();
			if(!m_reseau.sommetExiste(v)){
				m_reseau.ajouterSommet(v);
				stations.push_back(v);
			}
			unsigned int c = (*s).first*3600/vitesse_de_marche;
			//unsigned int c = (*s).first*1000;
			m_reseau.ajouterArc(u,v,c,1);
		}


		// Ajout des arcs de l'arrivée aux stations environnantes
		std::vector<std::pair<double, Station*>> stEnv1 = trouver_stations_environnantes(dest, dist_de_marche);
		for(auto s = stEnv1.begin(); s != stEnv1.end(); ++s){
			unsigned int v = num_dest;
			unsigned int u = (*s).second->getId();
			if(!m_reseau.sommetExiste(u)){
				m_reseau.ajouterSommet(u);
				stations.push_back(u);
			}
			unsigned int c = (*s).first*3600/vitesse_de_marche;
			//unsigned int c = (*s).first*1000;
			m_reseau.ajouterArc(u,v,c,1);
		}
	} // Fin if dist_marche != 0

	// Ajout des arcs des voyages de la journée concernée
	for(auto id = voyDate.begin(); id != voyDate.end(); ++id){
		string idV = (*id).first;
		Voyage v = m_voyages.at(idV);
		vector<Arret> va = v.getArrets();
		for(unsigned int a = 0; a != va.size()-1; a++){
			if(va[a].getHeureDepart() > heure_depart && va[a].getHeureDepart() < heure_fin){
				unsigned int u = va[a].getStationId();
				unsigned int v = va[a+1].getStationId();
				unsigned int c;
				if(!m_reseau.sommetExiste(u)){
					m_reseau.ajouterSommet(u);
					stations.push_back(u);
				}
				if(!m_reseau.sommetExiste(v)){
					m_reseau.ajouterSommet(v);
					stations.push_back(v);
				}
				if(va[a+1].getHeureDepart()-va[a].getHeureDepart() <= 0)
					c = 30;
				else
					c = va[a+1].getHeureDepart()-va[a].getHeureDepart();

				//c = (m_stations.at(v).getCoords()-m_stations.at(u).getCoords())*1000;
				if(m_reseau.arcExiste(u,v)){
					if(m_reseau.getCoutArc(u,v) > (int)c)
						m_reseau.majCoutArc(u,v,c);
				}
				else
					m_reseau.ajouterArc(u,v,c);
			}
		}
	}

	if(dist_transfert != 0.0)
	{
		// Ajout des arcs de transfert entre stations
		for(auto s = stations.begin(); s != stations.end(); ++s){
			std::vector<std::pair<double, Station*>> se = trouver_stations_environnantes(m_stations.at(*s).getCoords(),dist_transfert);
			for(auto e = se.begin(); e != se.end(); ++e){
				unsigned int u = (*s);
				unsigned int v = (*e).second->getId();
				unsigned int c = (*e).first*3600/vitesse_de_marche;
				//unsigned int c = (*e).first*1000;
				if(!m_reseau.sommetExiste(v))
					continue;
				if(m_reseau.arcExiste(u,v)){
					if(m_reseau.getCoutArc(u,v) > (int)c && m_reseau.getTypeArc(u,v) == 1)
						m_reseau.majCoutArc(u,v,c);
				}
				else
					m_reseau.ajouterArc(u,v,c,1);
			}
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
	unordered_map<string,vector<string>> vServiceId;
	for(auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
		Voyage v = (*it).second;
		vServiceId[v.getServiceId()].push_back(v.getId());
	}
	for (unsigned int i = 0; i < objs.size(); i++) {
		unsigned int y = stoi(objs[i][1].substr(0,4));
		unsigned int m = stoi(objs[i][1].substr(4,2));
		unsigned int d = stoi(objs[i][1].substr(6,2));
		string id = objs[i][0];
		for(auto v = vServiceId[id].begin();v != vServiceId[id].end();++v){
			m_voyages_date[Date(y,m,d)].insert({(*v),&m_voyages.at(*v)});
		}
		//m_voyages_date[Date(y,m,d)].insert({id,vServiceId[id]});
	}
	/*unordered_map<string,vector<Date>> dateService;
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
	}*/
}

void Gestionnaire::importerTout(){
	importerLignes();
	importerStations();
	importerVoyages();
	importerArrets();
	importerDatesVoyages();
}


