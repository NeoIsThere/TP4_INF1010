/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz, Samuel Lavallée et Anthelme Clisson
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>



template <typename T> class Matrice {

public:
  Matrice();
  // Destructeur
  ~Matrice() = default;
  T operator()(const size_t &posY, const size_t &posX) const;
  // Lecture du fichier
  bool chargerDepuisFichier(const std::string &nomFichier);
  bool lireElement(const std::string &elementFichier, const size_t &posY,
                   const size_t &posX);
  // Remplir un matrice
  bool ajouterElement(T element, const size_t &posY, const size_t &posX);
  // Faire une copie
  std::unique_ptr<Matrice<T>> clone() const;
  // Setters
  void setHeight(size_t height);
  void setWidth(size_t width);
  // Getters
  size_t getHeight() const;
  size_t getWidth() const;

private:
  std::vector<std::vector<T>> elements_;
  size_t height_;
  size_t width_;
};

namespace {
static constexpr int CAPACITE_MATRICE = 100;
}

/**
 * @brief surcharge opérateur () pour donner élément à la position spécifiée
 * @param posX, la colonne de l'élément
 * @param posY, la ligne de l'élément
 * @return élément
 */
template<typename T>
T  Matrice<T>::operator()(const size_t& posY, const size_t& posX) const {
	if (posX >= width_ || posY >= height_) {
		return T();
	}
	return elements_[posY][posX];
}

/**
 * @brief ajouter un élément à la position spécifiée 
 * @param posX, la colonne de l'élément
 * @param posY, la ligne de l'élément
 * @param element, l'élément à ajouter
 * @return élément
 */
template<typename T>
bool  Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX) {
	if (0 <= posX < width_ && 0 < posY < height_) {
		elements_[posY][posX] = element;
		return true;
	}
	return false;
}

/**
 * @brief lire un élément à ajouter à partir d'un stringstream
 * @param string, stream duquel lire élément
 * @param posY, la ligne où ajouter l'élément
 * @param posX, la colonne où ajouter l'élément
 * @return true si la lecture et l'ajout se sont bien passés false sinon
 */
template<typename T>
bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX) {
	std::istringstream ss(elementFichier);
	T extrait;
	if (ss >> extrait) {
		
		return ajouterElement(extrait, posY, posX);
	}
	
	return false;
}

/**
 * @brief ouvrir le fichier à lire et envoyer chaque ligne à la fonction lireElement
 * @param string, nom du fichier à lire
 * @return true si les envoies se sont bien passés false sinon
 */
template<typename T>
bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) {
	std::ifstream fichier(nomFichier);
	if (fichier.is_open()) {
		std::string str;
		int taille = 0;
		while (!fichier.eof()) {
			fichier >> str;
			if (str == "L") {
				++taille;
			}
		}

		for (int i = 0; i < taille; i++) {
			elements_[i].resize(taille);
		}

		width_ = height_ = taille;

		fichier.clear();
		fichier.seekg(0, std::ios::beg);
		std::string line;
		int y = 0;
		std::getline(fichier, line);
		for (int i = 0; i < taille; i++) {
			for (int j = 0; j < taille; j++) {
				std::getline(fichier, line);
				lireElement(line, y, j);
			}
			++y;
			std::getline(fichier, line);
		}

		return true;
	}
	std::cout << "fichier introuvable";
	return false;
}
		
		
	

/**
 * @brief retourne copie allouée dynamiquement de l'objet courant
 * @return la copie
 */
template<typename T>
std::unique_ptr<Matrice<T>> Matrice<T>::clone() const {
	Matrice<T> copie;
	copie.height_ = height_;
	copie.width_ = width_;
	copie.elements_ = elements_;
	return std::make_unique < Matrice<T>>(copie);
}

/**
 * @brief ajuster le nombre de lignes 
 * @param height, le nombre de lignes qu'on veut
 */
template<typename T>
void Matrice<T>::setHeight(size_t height) {
	bool a = (height > CAPACITE_MATRICE);
	bool b = (height < 0);
	height_ = height - (height - CAPACITE_MATRICE) * a - height * b;
	elements_.resize(height);
	

}

/**
 * @brief ajuster le nombre de colonnes
 * @param height, le nombre de colonnes qu'on veut
 */
template<typename T>
void Matrice<T>::setWidth(size_t width){
	bool a = (width > CAPACITE_MATRICE);
	bool b = (width < 0);
	width_ = width - (width - CAPACITE_MATRICE) * a - width * b;
	for (int i = 0; i < elements_.size(); i++)
		elements_[i].resize(width_);
}


/**
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice():elements_(CAPACITE_MATRICE), height_(0), width_(0){

}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getHeight() const {
  return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getWidth() const {
  return width_;
}

#endif
