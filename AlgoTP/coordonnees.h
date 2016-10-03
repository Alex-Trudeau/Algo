//
// Created by prtos on 29/04/16.
//

#ifndef RTC_COORDONNEES_H
#define RTC_COORDONNEES_H

#include <stdexcept>
#include <iostream>
#include <sstream>

namespace tp {

#define M_PI    3.1415926535897932384626433832795
#define M_EARTH_RADIUS 6371.0

/*!
 * \class Coordonnees
 * \brief Cette classe permet de représenter les coordonnées GPS d'un endroit
 */
class Coordonnees {

public:

    Coordonnees(double latitude, double longitude);

    double getLatitude() const ;

    void setLatitude(double latitude) ;

    double getLongitude() const ;

    void setLongitude(double longitude) ;

    static bool is_valide_coord(double p_latitude, double p_longitude) ;

    double operator- (const Coordonnees & other) const;

    friend std::ostream & operator<<(std::ostream & flux, const Coordonnees & p_coord);

    double degre_to_radian(double p_deg);

private:
    double m_latitude;
    double m_longitude;
};

}

#endif //RTC_COORDONNEES_H
