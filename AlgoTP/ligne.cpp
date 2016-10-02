/*
 * ligne.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */
#include "ligne.h"

Ligne::Ligne(const std::vector<std::string>& p_ligne):
	m_id(std::stoi(p_ligne[0])),
	m_numero(p_ligne[2]),
	m_description(p_ligne[4]),
	m_categorie(Ligne::couleurToCategorie(p_ligne[7])),
	m_voyages(std::vector<Voyage*> p_vide){

}

static Ligne::CategorieBus Ligne::couleurToCategorie(std::string p_couleur){
	switch (p_couleur){
	case "97BF0D":
		return CategorieBus::METRO_BUS;
		break;
	case "013888":
		return CategorieBus::LEBUS;
		break;
	case "E04503":
		return CategorieBus::EXPRESS;
		break;
	case "1A171B":
		return CategorieBus::COUCHE_TARD;
		break;
	}
}

static std::string Ligne::categorieToString(CategorieBus p_cat){
	switch (p_cat){
	case CategorieBus::METRO_lS:
		return "METRO_BUS";
		break;
	case CategorieBus::LEBUS:
		return "LEBUS";
		break;
	case CategorieBus::EXPRESS:
		return "EXPRESS";
		break;
	case CategorieBus::COUCHE_TARD:
		return "COUCHE_TARD";
		break;
	}
}

CategorieBus Ligne::getCategorie() const{
	return m_categorie;
}

void Ligne::setCategorie(CategorieBus p_categorie){
	m_categorie = p_categorie;
}

std::pair<std::string, std::string> Ligne::getDestinations() const{
	std::string fst = m_voyages[0].getDestination();
	std::string snd = m_voyages[1].getDestination();
	int i = 2;
	while(i < m_voyages.size() && snd == fst){
		snd = m_voyages[i].getDestination();
		i++;
	}
	return std::pair<std::string, std::string> p(fst,snd);
}

unsigned int Ligne::getId() const{
	return m_id;
}

void Ligne::setId(unsigned int p_id){
	m_id = p_id;
}

const std::string& Ligne::getNumero() const{
	return m_numero;
}

void Ligne::setNumero(const std::string& p_numero){
	m_numero = p_numero;
}

const std::vector<Voyage*>& Ligne::getVoyages() const{
	return m_voyages;
}

void Ligne::setVoyages(const std::vector<Voyage*>& p_voyages){
	m_voyages = p_voyages;
}

void Ligne::addVoyage(Voyage* ptr_voyage){
	m_voyages.push_back(ptr_voyage);
}

const std::string& Ligne::getDescription() const{
	return m_description;
}

void Ligne::setDescription(const std::string& p_description){
	m_description = p_description;
}

friend std::ostream& Ligne::operator <<(std::ostream& f, const Ligne& p_ligne){
	f << categorieToString(m_categorie) << " " << m_id << " : " << (this ->getDestinations())[0] << " - " <<
			(this ->getDestinations())[1] << endl;
	return f;
}



