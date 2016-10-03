/*
 * station.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */
#include "station.h"

using namespace std;

namespace tp {

Station::Station(const std::vector<std::string>& p_ligne):
	m_id(std::stoi(p_ligne[0])),m_nom(p_ligne[1]),
	m_description(p_ligne[3]),m_coords(std::stod(p_ligne[4]),std::stod(p_ligne[5])),
	m_voyages_passants(std::vector<Voyage*>()){
	// INIT VECTEUR VOYAGE
}

std::ostream& operator<<(std::ostream& flux, const Station& p_station){
	// AFFICHER QUOI??
}

const Coordonnees& Station::getCoords() const{
	return m_coords;
}

void Station::setCoords(const Coordonnees& p_coords){
	m_coords = p_coords;
}

const std::string& Station::getDescription() const{
	return m_description;
}

void Station::setDescription(const std::string& p_description){
	m_description = p_description;
}

std::vector<Ligne*> Station::getLignesPassantes() const{
	// PAS SUR POUR TOUT SUITE
}

const std::string& Station::getNom() const{
	return m_nom;
}

void Station::setNom(const std::string& p_nom){
	m_nom = p_nom;
}

unsigned int Station::getId() const{
	return m_id;
}

void Station::setId(unsigned int p_id){
	m_id = p_id;
}

const std::vector<Voyage*> & Station::getVoyagesPassants() const{
	// PAS SUR POUR TOUT SUITE
}

void Station::addVoyage(Voyage* ptr_voyage){
	// PAS SUR POUR TOUT SUITE
}

double Station::distance(const Station& p_station) const{
	return this->getCoords()-p_station.getCoords();
}


} // fin namespace tp

