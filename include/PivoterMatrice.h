/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz, Samuel Lavallée et Anthelme Clisson
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"
#include "Pixel.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};


/**
 * @brief pivoter la matrice à 90 degrés vers la gauche ou la droite
 * @param Direction, gauche ou droite
 */
template <typename M>
void PivoterMatrice<M>::pivoterMatrice(Direction direction) {
	int x, y;
	std::unique_ptr<M> copie = matrice_->clone();
	for ( int i = 0; i < matrice_->getHeight(); i++) {
		for (int j = 0; j < matrice_->getWidth(); j++) {

			Coordonnees coo = changerCoordonneesCentreMatrice({ j,i});
			if (direction == Direction::Left) {
				x = coo.y, y = -coo.x;
			}
			else {
				x = -coo.y, y = coo.x;
			}
			coo = recupererCoordonnees({ x, y });
			matrice_->ajouterElement(copie->operator()(i, j), coo.y, coo.x);
		}


	}
}






/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice(): matrice_(nullptr){}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
	Coordonnees centree;

	centree.x = coords.x - matrice_->getWidth()/ 2;
	centree.y = coords.y - matrice_->getHeight()/2;
	return centree;
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
	Coordonnees normale;
	normale.x = coords.x + matrice_->getWidth() / 2;
	normale.y = coords.y +matrice_->getHeight() / 2;
	return normale;

}

/**
 * @brief surcharge de l'opérateur << pour l'affichage d'une matrice pivotée
 * @param ostream, le stream dans lequel afficher
 * @param PivoterMatrice<M>, la matrice pivotée à afficher
 * @return ostream pour appel en cascade
 */
template <typename M>
std::ostream& operator<<(std::ostream& os, PivoterMatrice<M> piv) {
	for (unsigned int i = 0; i < piv.matrice_->getHeight(); i++) {
		for (unsigned int j = 0; j < piv.matrice_->getMatrice()->getWidth(); j++)
			if (j < piv.matrice_->getWidth() - 1) {
				std::cout << piv.matrice_->operator()(i, j) << " | ";
			}
		os << std::endl;
	}
	return os;
}

#endif
