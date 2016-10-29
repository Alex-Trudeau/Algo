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

}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){

}

int Reseau::nombreSommets() const{
	return m_lst_adj.size();
}

int Reseau::nombreArcs() const{
	int total = 0;
	for(liste_sommets::const_iterator it = m_lst_adj.begin(); it != m_lst_adj.end(); it++){
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

int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){

}

int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){

}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){

}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
			throw (std::logic_error){

}

bool Reseau::estFortementConnexe() const{

}

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{

}


