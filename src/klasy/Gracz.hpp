#ifndef Gracz_hpp
#define Gracz_hpp

#include <cstdint>
#include "Karta.hpp"
#include "KartaSpecjalna.hpp"
#include <list>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class Gracz
{
	private:
	std::list <Karta> karty;
	std::list <KartaSpecjalna> polozoneKartySpecjalneNaStole;
	std::list <KartaSpecjalna> kartySpecjalne;
	int16_t atak;
	int16_t poziomZdrowia;
	int16_t sumaWartosciKart;
	bool czyDokonalRuchu;
	friend class RenderowanieRozgrywki;
	friend class Rozgrywka;

	public:
	static inline volatile bool czyWLobby = true;
	static inline sf::Vector2f pozycjaMyszki;
	static inline sf::Keyboard::Key wcisnietyKlawisz;
	void DodajKarte(int16_t & wartoscNaKarcie);
	void DodajKarteSpecjalna(RodzajKartySpecjalnej && jakaKartaSpecjalna);
	void DokonajRuchu();
	Gracz();
	~Gracz() = default;
	void PolozKarteSpecjalnaNaStol(RodzajKartySpecjalnej && jakaKartaSpecjalna);
	bool SprawdzCzyDokonanoRuchu() const;
	bool SprawdzCzyNieposiadaKartSpecjalnych() const;
	bool SprawdzCzyZyje() const;
	void UstawPozycjeKartySpecjalnejWEkwipunku();
	void ZresetujDokonanieRuchu();
	void ZresetujStatystykiNaPoczatekRundy();
	std::list <KartaSpecjalna>::iterator ZwrocIteratorNaKoniecKartSpecjalnych();
	std::list <KartaSpecjalna>::iterator ZwrocIteratorNaPoczatekKartSpecjalnych();
};

#endif