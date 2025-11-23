#ifndef Rozgrywka_hpp
#define Rozgrywka_hpp

#include <deque>
#include "Gracz.hpp"
#include <list>
#include <random>

enum struct Zwyciezca : int8_t
{
	gracz,
	przeciwnik,
	remis
};

class Rozgrywka	//Klasa do obs³ugi rozgrywki.
{
	private:
	std::mt19937 generatorLosowychLiczb;
	std::deque <int16_t> kartyDoDobierania;
	std::array <bool, 12> dostepneKarty;
	volatile int16_t limitWyniku;
	Zwyciezca ktoWygral;
	friend class RenderowanieRozgrywki;

	public:
	bool DobierzKarte(Gracz & gracz);
	void DokonajNajlepszegoRuchuJakoPrzeciwnik(Gracz & przeciwnik, Gracz & gracz);
	void ObsluzZwyciezce(Gracz & gracz, Gracz & przeciwnik);
	Rozgrywka();
	~Rozgrywka() = default;
	void SprawdzKtoWygral(Gracz & gracz, Gracz & przeciwnik);
	void UtworzIWylosujTalie();
	void UzyjKartySpecjalnej(Gracz & gracz, Gracz & przeciwnik, 
	std::list <KartaSpecjalna>::iterator & wybranaKarta);
	void WstepnieWylosujDwieKartyDlaGraczy(Gracz & gracz, Gracz & przeciwnik);
	RodzajKartySpecjalnej WylosujKarteSpecjalna();
	void ZresetujLimitWyniku();
};

#endif