/*
 * coordonnees.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "coordonnees.h"
#include <sstream>
#include <cmath>

Coordonnees::Coordonnees(double p_latitude, double p_longitude):
	m_latitude(p_latitude),m_longitude(p_longitude){
	// DOIT PAS SE FAIRE SI COORDONNEES MAUVAISES
}

double Coordonnees::getLatitude() const {
	return m_latitude;
}

void Coordonnees::setLatitude(double p_latitude) {
	m_latitude = p_latitude;
}

double Coordonnees::getLongitude() const {
	return m_longitude;
}

void Coordonnees::setLongitude(double p_longitude) {
	m_longitude = p_longitude;
}

//static bool Coordonnees::is_valide_coord(double p_latitude, double p_longitude) {
//	if (p_latitude >= 0 && p_latitude <= 90 && p_longitude >= -180 && p_longitude <= 180)
//		return true;
//	else
//		return false;
//}

//double Coordonnees::operator- (const Coordonnees & p_other) const {
//	double d_lat = abs(this->getLatitude() - p_other.getLatitude());
//	double d_lon = abs(this->getLongitude() - p_other.getLongitude());
//	double a = asin(sqrt(pow(sin(d_lat / 2), 2) + cos(this->getLatitude()) * cos(p_other.getLatitude()) * pow(sin(d_lon / 2), 2)));
//	return 2 * earth_radius_km * a;
//}

//friend std::ostream & Coordonnees::operator<<(std::ostream & p_flux, const Coordonnees & p_coord){
	// QU'EST-CE QUI FAUT AFFICHER???
//}

double Coordonnees::degre_to_radian(double p_deg){
	return (p_deg * M_PI / 180.0);
}
