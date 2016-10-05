/**
 * \file coordonnees.cpp
 * \brief Implantation de la classe Coordonnees
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "coordonnees.h"
#include "ContratException.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
/**
 * \brief Constructeur avec paramètre
 * Création d'un objet coordonnes à partir des données passé en paramètre.
 * \param[in] p_latitude
 * \param[in] p_longitude
 * \pre les coordonnées sont valide selon la fonction is_valide_coord
 * \post m_latitude prend la valeur de p_latitude
 * \post m_longitude prend la valeur de p_longitude
 */
Coordonnees::Coordonnees(double p_latitude, double p_longitude) :
		m_latitude(p_latitude), m_longitude(p_longitude) {
	PRECONDITION(is_valide_coord(p_latitude, p_longitude));
	POSTCONDITION(m_latitude == p_latitude);
	POSTCONDITION(m_longitude == p_longitude);
}
/**
 * \brief Accesseur de la latitude
 * \return la latitude
 */
double Coordonnees::getLatitude() const {
	return m_latitude;
}
/**
 * \brief Ajuste la latitude
 * \param[in] p_latitude
 */
void Coordonnees::setLatitude(double p_latitude) {
	m_latitude = p_latitude;
}
/**
 * \brief Accesseur de la longitude
 * \return la longitude
 */
double Coordonnees::getLongitude() const {
	return m_longitude;
}
/**
 * \brief Ajuste la lagitude
 * \param[in] p_longitude
 */
void Coordonnees::setLongitude(double p_longitude) {
	m_longitude = p_longitude;
}
/**
 * \brief Validation des coordonnées
 * \param[in] p_latitude
 * \param[in] p_longitude
 * \return boolean si valide ou pas
 */
bool Coordonnees::is_valide_coord(double p_latitude, double p_longitude) {
	if (p_latitude >= -90 && p_latitude <= 90 && p_longitude >= -180
			&& p_longitude <= 180)
		return true;
	else
		return false;
}

double Coordonnees::operator-(const Coordonnees & p_other) const {
	double d_lat = abs(this->getLatitude() - p_other.getLatitude());
	double d_lon = abs(this->getLongitude() - p_other.getLongitude());
	double a = asin(
			sqrt(
					pow(sin(d_lat / 2), 2)
							+ cos(this->getLatitude())
									* cos(p_other.getLatitude())
									* pow(sin(d_lon / 2), 2)));
	return 2 * M_EARTH_RADIUS * a;
}
/**
 * \brief Operator << qui permet d'affiche les informations que l'on veut de l'objet
 * \return p_flux
 */
std::ostream & operator<<(std::ostream & p_flux, const Coordonnees & p_coord) {
	p_flux << p_coord.m_latitude << ", " << p_coord.m_longitude;
	return p_flux;
}
