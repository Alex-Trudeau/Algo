/*
 * voyage.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "ContratException.h"
#include "voyage.h"
#include <sstream>
#include <iostream>

using namespace std;

Voyage::Voyage(const std::vector<std::string>& p_l, Ligne* p_ligne) :
		m_id(p_l[2]), m_destination(p_l[3]), m_service_id(1), m_ligne(p_ligne) {
}
Arret & Voyage::arretDeLaStation(unsigned int p_num_station) {
	// Pas sure
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
	return m_arrets.front().m_heure_depart;
}
Heure Voyage::getHeureFin() const {
	return m_arrets.back().m_heure_arrivee;
}
void Voyage::setArrets(std::vector<Arret>& resultat) {
	for (int i = 0; i < resultat.size(); i++) {
		for (int j = 0; j < resultat.size(); j++){
			if(resultat[i] < resultat[j]){
				Arret tmp;
				tmp = resultat[i];
				resultat[i] = resultat[j];
				resultat[j] = tmp;
			}
		}
	}
}
bool Voyage::operator<(const Voyage & p_other) const {
	return (this->getHeureDepart() < p_other.getHeureDepart());
}
bool Voyage::operator>(const Voyage & p_other) const {
	return (this->getHeureDepart() > p_other.getHeureDepart());
}
std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage) {
	flux << p_voyage.m_ligne->m_numero << ": Vers " << p_voyage.m_destination << endl;
}
