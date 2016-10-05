/**
 * \file voyage.cpp
 * \brief
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "ContratException.h"
#include "voyage.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

Voyage::Voyage(const std::vector<std::string>& p_l, Ligne* p_ligne) :
		m_id(p_l[2]), m_destination(p_l[3]), m_service_id(p_l[1]), m_ligne(p_ligne) {
}
Arret & Voyage::arretDeLaStation(unsigned int p_num_station) {
	for (unsigned int i = 0; i < m_arrets.size(); i++){
		if( m_arrets[i].getStationId() == p_num_station) {
			return m_arrets[i];
		}

		else {
			// la station est pas dans le voyage
		}
	}
}
std::vector<Arret> Voyage::getArrets() const {
	return m_arrets;
}
const std::string& Voyage::getDestination() const {
	return m_destination;
}
void Voyage::setDestination(const std::string& p_destination) {
	m_destination = p_destination;
}
std::string Voyage::getId() const {
	return m_id;
}
void Voyage::setId(std::string p_id) {
	m_id = p_id;
}
Ligne* Voyage::getLigne() const {
	return m_ligne;
}
void Voyage::setLigne(Ligne* p_ligne) {
	m_ligne = p_ligne;
}
std::string Voyage::getServiceId() const {
	return m_service_id;
}
void Voyage::setServiceId(std::string p_service_id) {
	m_service_id = p_service_id;
}
Heure Voyage::getHeureDepart() const {
	return m_arrets.front().getHeureDepart();
}
Heure Voyage::getHeureFin() const {
	return m_arrets.back().getHeureArrivee();
}
void Voyage::setArrets(std::vector<Arret>& resultat) {
	sort(resultat.begin(),resultat.end());
	m_arrets = resultat;
}
bool Voyage::operator<(const Voyage & p_other) const {
	return (this->getHeureDepart() < p_other.getHeureDepart());
}
bool Voyage::operator>(const Voyage & p_other) const {
	return (this->getHeureDepart() > p_other.getHeureDepart());
}
std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage) {
	return flux << p_voyage.getLigne()->getNumero() << ": Vers " << p_voyage.getDestination() << endl;
}
