/*
/*
 * reseau.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */

#include "reseau.h"

using namespace std;

Reseau::Reseau(){
	nb_arcs = 0;
	nb_sommets = 0;
}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error){
	if(!sommetExiste(numero)){
		adj[numero] = liste_arcs();
		nb_sommets++;
	}
	else
		throw std::logic_error("Sommet deja existant");
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error){
	if(sommetExiste(numero)){
		adj.erase(numero);
		nb_sommets--;
	}
	else
		throw std::logic_error("Sommet inexistant");
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type)
			throw (std::logic_error){
	if(sommetExiste(numOrigine)){
		if(sommetExiste(numDest)){
			if(!arcExiste(numOrigine,numDest)){
				adj[numOrigine][numDest] = {cout,type};
				nb_arcs++;
			}
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
	if(arcExiste(numOrigine,numDest)){
		adj[numOrigine].erase(numDest);
		nb_arcs--;
	}
	else
		throw logic_error("Arc inexistant");
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){
	if(arcExiste(numOrigine,numDest))
		adj[numOrigine][numDest].first = cout;
	else
		throw logic_error("Arc inexistant");
}

int Reseau::nombreSommets() const{
	return nb_sommets;
}

int Reseau::nombreArcs() const{
	return nb_arcs;
}

bool Reseau::estVide() const{
	return nb_sommets == 0;
}

bool Reseau::sommetExiste(unsigned int numero) const{
	return (adj.count(numero) != 0);
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if(!sommetExiste(numOrigine))
		throw std::logic_error("Sommet d'origine inexistant");
	if(!sommetExiste(numDest))
		throw std::logic_error("Sommet de destination inexistant");
	if(adj.at(numOrigine).count(numDest) != 0)
		return true;
	return false;
}

int Reseau::getCoutArc(unsigned int numOrig, unsigned int numDest) const throw (std::logic_error){
	if(!arcExiste(numOrig,numDest))
		throw logic_error("Arc inexistant");
	return adj.at(numOrig).at(numDest).first;
}

int Reseau::getTypeArc(unsigned int numOrig, unsigned int numDest) const throw (std::logic_error){
	if(!arcExiste(numOrig,numDest))
		throw logic_error("Arc inexistant");
	return adj.at(numOrig).at(numDest).second;
}

int Reseau::dijkstra(unsigned int numOrig, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){
	if(!chemin.empty())
		throw logic_error("Le chemin fourni n'est pas vide");
	if(!sommetExiste(numOrig) || !sommetExiste(numDest))
		throw logic_error("Un ou les 2 sommets sont invalide");

	unordered_map<unsigned int, unsigned int> d;	// Map des couts
	unordered_map<unsigned int, unsigned int> p;	// Map des predecesseurs
	unordered_map<unsigned int, bool> vis;			// Map de bool de visite
	priority_queue<pii, vector<pii>, greater<pii>> q;	// File priorité sur le cout
	bool destAtteint = false;							// Booleen d'arret de la fonction

	// Initialisation des map
	// Pour tout sommets : Cout = INFINI, predec = NULL et visite = false
	for(it_sommet it = adj.begin(); it != adj.end(); ++it){
		d[(*it).first] = INFINI;
		p[(*it).first] = NULL;
		vis[(*it).first] = false;
	}

	// Modification du noeud de départ et ajout a la file
	d[numOrig] = 0;
	q.push(pii(0,numOrig));

	// Tant que la file n'est pas vide
	while(!q.empty() && !destAtteint){
		// En utilisant la notation u -> v pour les arcs
		// Prendre l'élément 'u' de la file avec cout minimum
		unsigned int u = q.top().second;
		vis[u] = true;
		q.pop();
		// Si le noeud selectionné est celui ciblé
		if(u == numDest){
			destAtteint = true;
			continue;
		}
		for(auto it = adj[u].begin(); it != adj[u].end(); ++it){
			unsigned int v = (*it).first;
			unsigned int w = (*it).second.first;
			unsigned int temp = d[u] + w;
			if(temp < d[v] && !vis[v]){
				d[v] = temp;
				p[v] = u;
				q.push(pii(d[v],v));
			}
		}
	}

	unsigned int cour = numDest;
	while(cour != numOrig){
		unsigned int pred = p[cour];
		chemin.push_back(cour);
		cour = pred;
	}
	chemin.push_back(numOrig);
	std::reverse(chemin.begin(),chemin.end());

	return p[numDest];
}

int Reseau::bellmanFord(unsigned int numOrig, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){
	if(!chemin.empty())
			throw logic_error("Le chemin fourni n'est pas vide");
	typedef pair<unsigned int, unsigned int> poidsPred;

	unordered_map<unsigned int, poidsPred> dp;

	for(it_sommet it = adj.begin(); it != adj.end(); ++it){
		dp[(*it).first] = {INFINI,NULL};
	}

	dp[numOrig].first = 0;

	for(int i = 0 ; i < nombreSommets(); i++){
		int nbRelache = 0;
		for(it_sommet it = adj.begin(); it != adj.end(); ++it){
			unsigned int u = (*it).first;
			for(it_arc it2 = adj[u].begin(); it2 != adj[u].end(); ++it2){
				unsigned int v = (*it2).first;
				unsigned int temp = dp[u].first + adj[u][v].first;
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

	for(it_sommet it = adj.begin(); it != adj.end(); ++it){
		unsigned int u = (*it).first;
		for(it_arc it2 = adj[u].begin(); it2 != adj[u].end(); ++it2){
			unsigned int v = (*it2).first;
			unsigned int temp = dp[u].first + adj[u][v].first;
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
	std::vector<std::vector<unsigned int> > tmp;
	return (getComposantesFortementConnexes(tmp) == 1);
}

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{
	std::stack<unsigned int> pile;

	unordered_map<unsigned int, bool> visite;
	Reseau inv = inverse();

	for(cst_it_sommet it = adj.begin(); it != adj.end(); ++it){
		visite[(*it).first] = false;
	}
	for(cst_it_sommet it = adj.begin(); it != adj.end(); ++it){
		unsigned int i = (*it).first;
		if(!visite.at(i))
			inv.ordreEmpilage(i,visite,pile);
	}

	for(cst_it_sommet it = adj.begin(); it != adj.end(); ++it){
		visite[(*it).first] = false;
	}
	while(!pile.empty()){
		unsigned int v = pile.top();
		pile.pop();

		if(!visite[v]){
			std::vector<unsigned int> res;
			explore(v,visite,res);
			if(!res.empty())
				composantes.push_back(res);
		}
	}
	return composantes.size();
}


Reseau Reseau::inverse() const{
	Reseau inv;

	for(cst_it_sommet it = adj.begin(); it != adj.end(); ++it){
		unsigned int u = (*it).first;
		if(!inv.sommetExiste(u))
			inv.ajouterSommet(u);
		for(cst_it_arc it2 = adj.at(u).begin(); it2 != adj.at(u).end(); ++it2){
			unsigned int v = (*it2).first;
			unsigned int uv = adj.at(u).at(v).first;
			if(!inv.sommetExiste(v))
				inv.ajouterSommet(v);
			if(!inv.arcExiste(u,v))
				inv.ajouterArc(v,u,uv);
		}
	}
	return inv;
}

void Reseau::ordreEmpilage(unsigned int s, unordered_map<unsigned int, bool> &visite, stack<unsigned int> &pile) const{
	visite[s] = true;
	for(cst_it_arc it = adj.at(s).begin(); it != adj.at(s).end(); ++it){
			unsigned int v = (*it).first;
			if(!visite[v])
				ordreEmpilage(v,visite,pile);
		}
	pile.push(s);
}

void Reseau::explore(unsigned int s, unordered_map<unsigned int, bool> &visite, std::vector<unsigned int> &res) const{
	visite[s] = true;
	res.push_back(s);
	for(cst_it_arc it = adj.at(s).begin(); it != adj.at(s).end(); ++it){
		unsigned int v = (*it).first;
		if(!visite[v])
			explore(v,visite,res);
	}
}

