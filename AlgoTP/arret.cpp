/*
 * arret.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "arret.h"

using namespace std;

namespace tp {

Arret::Arret(const std::vector<std::string>& ligne_gtfs) {

}

const Heure& Arret::getHeureArrivee() const {

}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {

}

const Heure& Arret::getHeureDepart() const {

}

void Arret::setHeureDepart(const Heure& p_heureDepart) {

}

unsigned int Arret::getNumeroSequence() const {

}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {

}

unsigned int Arret::getStationId() const {

}

void Arret::setStationId(unsigned int stationId) {

}

std::string Arret::getVoyageId() const {

}

void Arret::setVoyageId(const std::string& voyageId) {

}

bool Arret::operator<(const Arret & p_other) const {

}

bool Arret::operator>(const Arret & p_other) const {

}

std::ostream & operator<<(std::ostream & flux, const Arret & p_arret) {

}

} // Namespace tp
