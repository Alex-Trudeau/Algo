/*
 * reseau.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */

#include "reseau.h"

using namespace std;

Reseau::Reseau(){}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error){
	if(!sommetExiste(numero))
		m_lst_adj[numero] = liste_arcs();
	else
		throw std::logic_error("Sommet deja existant");
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error){
	if(sommetExiste(numero))
		m_lst_adj.erase(numero);
	else
		throw std::logic_error("Sommet inexistant");
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type)
			throw (std::logic_error){
	if(sommetExiste(numOrigine)){
		if(sommetExiste(numDest)){
			if(!arcExiste(numOrigine,numDest))
				m_lst_adj[numOrigine][numDest] = {cout,type};
			else
				throw std::logic_error("Arc deja existant");
		}
		else
			throw std::logic_error("Sommet de destination inexistant");
	}
	else
		throw std::logic_error("Sommet d'origine inexistant");
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error){
	if(arcExiste(numOrigine,numDest))
		m_lst_adj[numOrigine].erase(numDest);
	else
		throw logic_error("Arc inexistant");
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){
	if(arcExiste(numOrigine,numDest))
		m_lst_adj[numOrigine][numDest].first = cout;
	else
		throw logic_error("Arc inexistant");
}

int Reseau::nombreSommets() const{
	return m_lst_adj.size();
}

int Reseau::nombreArcs() const{
	int total = 0;
	for(cst_it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); it++){
		total +=(*it).second.size();
	}
	return total;
}

bool Reseau::estVide() const{
	return nombreSommets() == 0;
}

bool Reseau::sommetExiste(unsigned int numero) const{
	return (m_lst_adj.count(numero) > 0);
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if(sommetExiste(numOrigine)){
		if(m_lst_adj.at(numOrigine).count(numDest) > 0)
			return true;
	}
	return false;
}

int Reseau::getCoutArc(unsigned int numOrig, unsigned int numDest) const throw (std::logic_error){
	int retour;
	if(arcExiste(numOrig,numDest))
		retour = m_lst_adj.at(numOrig).at(numDest).first;
	else
		throw logic_error("Arc inexistant");
	return retour;
}

int Reseau::getTypeArc(unsigned int numOrig, unsigned int numDest) const throw (std::logic_error){
	int retour;
	if(arcExiste(numOrig,numDest))
		retour = m_lst_adj.at(numOrig).at(numDest).second;
	else
		throw logic_error("Arc inexistant");
	return retour;
}

int Reseau::dijkstra(unsigned int numOrig, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){
	if(!chemin.empty())
		throw logic_error("Le chemin fourni n'est pas vide");

	typedef pair<unsigned int, bool> poidsVisite;

	unordered_map<unsigned int, poidsVisite> visite;

	for(it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
		visite[(*it).first] = {INFINI,false};
	}

	visite[numOrig].first = 0;

	for(it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
		unsigned int u = NULL;
		unsigned int du = INFINI;

		for(unordered_map<unsigned int, poidsVisite>::iterator it2 = visite.begin(); it2 != visite.end(); ++it2){
			if((*it2).second.second == false && (*it2).second.first < du)
			{
				u = (*it2).first;
				du = (*it2).second.first;
			}
		}
		if(u == NULL)
			throw logic_error("Ne peut trouver de chemin");

		visite[u].second = true;
		chemin.push_back(u);

		if(u == numDest)
			return visite[u].first;

		for(it_arcs it3 = m_lst_adj[u].begin(); it3 != m_lst_adj[u].end(); ++it3){
			unsigned int temp = visite[u].first + (*it3).second.first;
			if(temp < visite[(*it3).first].first)
				visite[(*it3).first].first = temp;
		}
	}
	if(visite[numDest].first != INFINI)
		return visite[numDest].first;
	return NULL;
}

int Reseau::bellmanFord(unsigned int numOrig, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){
	if(!chemin.empty())
			throw logic_error("Le chemin fourni n'est pas vide");
	typedef pair<unsigned int, unsigned int> poidsPred;

	unordered_map<unsigned int, poidsPred> dp;

	for(it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
		dp[(*it).first] = {INFINI,NULL};
	}

	dp[numOrig].first = 0;

	for(int i = 0 ; i < nombreSommets(); i++){
		int nbRelache = 0;
		for(it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
			unsigned int u = (*it).first;
			for(it_arcs it2 = m_lst_adj[u].begin(); it2 != m_lst_adj[u].end(); ++it2){
				unsigned int v = (*it2).first;
				unsigned int temp = dp[u].first + m_lst_adj[u][v].first;
				if(temp < dp[v].first){
					dp[v].first = temp;
					dp[v].second = u;
					nbRelache++;
				}
			}
		}
		if(nbRelache == 0)
			break;
	}

	for(it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
		unsigned int u = (*it).first;
		for(it_arcs it2 = m_lst_adj[u].begin(); it2 != m_lst_adj[u].end(); ++it2){
			unsigned int v = (*it2).first;
			unsigned int temp = dp[u].first + m_lst_adj[u][v].first;
			if(temp < dp[v].first)
				return NULL;
		}
	}

	if(dp[numDest].first != INFINI){
		int p = numDest;
		while(p != numOrig){
			chemin.push_back(p);
			p = dp[p].second;
		}
		chemin.push_back(numOrig);
		std::reverse(chemin.begin(),chemin.end());
		return dp[numDest].first;
	}
	return NULL;
}

bool Reseau::estFortementConnexe() const{
	Reseau inv;

	for(cst_it_sommet_adj it = m_lst_adj.begin(); it != m_lst_adj.end(); ++it){
		unsigned int u = (*it).first;
		if(!inv.sommetExiste(u))
			inv.ajouterSommet(u);
		for(cst_it_arcs it2 = m_lst_adj.at(u).begin(); it2 != m_lst_adj.at(u).end(); ++it2){
			unsigned int v = (*it2).first;
			unsigned int uv = m_lst_adj.at(u).at(v).first;
			if(!inv.sommetExiste(v))
				inv.ajouterSommet(v);
			if(!inv.arcExiste(u,v))
				inv.ajouterArc(u,v,uv);
		}
	}

}

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{

}
