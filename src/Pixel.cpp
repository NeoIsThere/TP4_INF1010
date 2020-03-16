#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}

void Pixel::operator=(const Pixel &pixel) {
	setRouge(pixel.rouge_);
	setBleu(pixel.bleu_);
	setVert(pixel.vert_);

}

void Pixel::setRouge(int rouge) {
	bool a = (rouge > 255), b = (rouge < 0);
	rouge_= rouge - (rouge - 255) * a - rouge * b;
}

void Pixel::setVert(int vert) {
	bool a = (vert > 255), b = (vert < 0);
	vert_ = vert - (vert - 255) * a - vert * b;
}

void Pixel::setBleu(int bleu) {
	bool a = (bleu > 255), b = (bleu < 0);
	bleu_ = bleu - (bleu - 255) * a - bleu * b;
}
/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }

 
uint8_t Pixel::getBleu() const { return bleu_; }

std::ostream &operator<<(std::ostream &os, Pixel pixel) {
	os << "#" << std::uppercase << std::hex << std::setfill('0')<<std::setw(2)<<int(pixel.getRouge()) << " " << std::setfill('0') << std::setw(2)<< int(pixel.getVert()) << " " << std::setfill('0') << std::setw(2)<<int(pixel.getBleu());

	return os;
	
}

std::istream &operator>>(std::istream &is, Pixel &pixel) {
	int r, v, b;
	is >> r >> v >> b;
	pixel.setRouge(r); 
	pixel.setVert(v); 
	pixel.setBleu(b);
	return is;
}