/*
 * arret.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "arret.h"

using namespace std;

Arret::Arret(const std::vector<std::string>& p_l):
	m_heure_arrivee(p_l[1]),
	m_heure_depart(p_l[2]),
	m_station_id(p_l[3]),
	m_numero_sequence(p_l[4]){


}

const Heure& Arret::getHeureArrivee() const {
	return m_heure_arrivee;
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {
	m_heure_arrivee = p_heureArrivee;
}

const Heure& Arret::getHeureDepart() const {
	return m_heure_depart;
}

void Arret::setHeureDepart(const Heure& p_heureDepart) {
	m_heure_depart = p_heureDepart;
}

unsigned int Arret::getNumeroSequence() const {
	return m_numero_sequence;
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {
	m_numero_sequence = p_numeroSequence;
}

unsigned int Arret::getStationId() const {
	return m_station_id;
}

void Arret::setStationId(unsigned int p_stationId) {
	m_station_id = p_stationId;
}

std::string Arret::getVoyageId() const {
	return m_voyage_id;
}

void Arret::setVoyageId(const std::string& p_voyageId) {
	m_voyage_id = p_voyageId;
}

bool Arret::operator<(const Arret & p_other) const {
	// Pas fait
}

bool Arret::operator>(const Arret & p_other) const {
	// Pas fait
}

std::ostream & operator<<(std::ostream & flux, const Arret & p_arret) {
	// Pas fait
}
