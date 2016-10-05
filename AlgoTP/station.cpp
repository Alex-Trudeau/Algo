/**
 * \file station.cpp
 * \brief
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "station.h"

using namespace std;

Station::Station(const std::vector<std::string>& p_ligne):
	m_id(std::stoi(p_ligne[0])),m_nom(p_ligne[1]),
	m_description(p_ligne[2]),m_coords(Coordonnees(std::stod(p_ligne[3]),std::stod(p_ligne[4]))),
	m_voyages_passants(std::vector<Voyage*>()){

}

std::ostream& operator<<(std::ostream& flux, const Station& p_station){
	return  flux << p_station.m_id << " - " << p_station.m_nom;
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
	std::vector<Ligne*> test;
	for(int i =0 ; i < m_voyages_passants.size(); i++){

		test.push_back(m_voyages_passants[i]->getLigne());

	}

	return test;
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
	return m_voyages_passants;
}

void Station::addVoyage(Voyage* ptr_voyage){
	m_voyages_passants.push_back(ptr_voyage);
}

double Station::distance(const Station& p_station) const{
	return this->getCoords()-p_station.getCoords();
}

