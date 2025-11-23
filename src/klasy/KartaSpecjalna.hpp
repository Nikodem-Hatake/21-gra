#ifndef KartaSpecjalna_hpp
#define KartaSpecjalna_hpp

#include <cstdint>
#include "GraficznaReprezentacjaKarty.hpp"

enum struct RodzajKartySpecjalnej : int8_t
{
	dobierzIdealnaKarte,
	dobierzIdealnaKarteIZwiekszAtakOPiec,
	dobierzKarteOWartosciDwa = 2,
	dobierzKarteOWartosciTrzy = 3,
	dobierzKarteOWartosciCztery = 4,
	dobierzKarteOWartosciPiec = 5,
	dobierzKarteOWartosciSzesc = 6,
	dobierzKarteOWartosciSiedem = 7,
	odrzucOstatniaWylosowanaKarte,
	usunKartySpecjalnePrzeciwnikaZeStolu,
	zamienSieOstatniaWylosowanaKartaZGraczem,
	zmienLimitWynikuNaSiedemnascie,
	zmienLimitWynikuNaDwadziesciaCztery,
	zmienLimitWynikuNaDwadziesciaSiedem,
	zmniejszAtakPrzeciwnikaOJeden,
	zmniejszAtakPrzeciwnikaODwa,
	zwiekszAtakOJeden,
	zwiekszAtakODwa,
	nic
};

class KartaSpecjalna : public GraficznaReprezentacjaKarty
{
	private:
	const char * tekstOSpecjalnejKarcie;
	//Dodatkowa statystyka karty mówi¹ca o tym np. o ile zwieksza/zmniejsza atak, 
	//jak¹ kartê dobiera itp (statystyka zale¿y od rodzaju karty).
	int16_t wartoscKartySpecjalnej;
	RodzajKartySpecjalnej jakaKartaSpecjalna;

	public:
	KartaSpecjalna(RodzajKartySpecjalnej & jakaKartaSpecjalna);
	~KartaSpecjalna() = default;
	RodzajKartySpecjalnej ZwrocRodzajKartySpecjalnej() const;
	const char * ZwrocTekst() const;
	int16_t ZwrocWartoscKartySpecjalnej() const;
};

#endif