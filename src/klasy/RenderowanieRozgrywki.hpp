#ifndef RenderowanieRozgrywki_hpp
#define RenderowanieRozgrywki_hpp

#include <array>
#include "Rozgrywka.hpp"

class RenderowanieRozgrywki
{
	private:
	std::array <std::unique_ptr <sf::RectangleShape>, 2> przyciskiZatrzymaniaGry;
	std::list <KartaSpecjalna>::iterator iteratorNaNajechanaKarteSpecjalna;
	volatile int8_t numerNajechanegoPrzyciskuZatrzymaniaGry;
	volatile bool czyGraczOtworzylEkwipunek;
	volatile bool czyTrwaAnimacja;
	volatile bool czyZatrzymanoGre;

	public:
	RenderowanieRozgrywki();
	~RenderowanieRozgrywki() = default;
	void RenderowanieGrafiki(Rozgrywka & rozgrywka, Gracz & gracz, Gracz & przeciwnik);
	void RozpocznijAnimacje();
	bool SprawdzCzyOtworzonoEkwipunek() const;
	bool SprawdzCzyTrwaAnimacja() const;
	bool SprawdzCzyZatrzymanoGre() const;
	void SprawdzGdzieKliknietoMyszkaPodczasZatrzymaniaGry();
	void UstawIteratorNaNajechanaKarteSpecjalna(Gracz & gracz);
	void UstawNumerNaNajechanyPrzyciskZatrzymaniaGry();
	void ZmienStatusOtwarciaEkwipunku();
	void ZmienStatusZatrzymaniaGry();
};

#endif