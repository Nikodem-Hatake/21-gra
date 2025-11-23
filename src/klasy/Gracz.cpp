#include "Gracz.hpp"
#include <unordered_map>
#include <unordered_set>

void Gracz::DodajKarte(int16_t & wartoscNaKarcie)
{
	sf::Vector2f pozycjaKarty(70.f, 450.f);
	if(!karty.empty())
	{
		pozycjaKarty = karty.back().ZwrocGraficznaReprezentacjeKarty() -> getPosition();
		pozycjaKarty.x += 80.f;
	}

	this -> karty.emplace_back(wartoscNaKarcie);
	this -> karty.back().ZwrocGraficznaReprezentacjeKarty() -> setPosition(pozycjaKarty);
	this -> sumaWartosciKart += wartoscNaKarcie;
}

void Gracz::DodajKarteSpecjalna(RodzajKartySpecjalnej && jakaKartaSpecjalna)
{
	if(this -> kartySpecjalne.size() == 20)
	{
		return;
	}
	this -> kartySpecjalne.emplace_back(jakaKartaSpecjalna);
}

void Gracz::DokonajRuchu()
{
	this -> czyDokonalRuchu = true;
}

Gracz::Gracz()
{
	this -> atak = static_cast <int16_t>(1);
	this -> czyDokonalRuchu = false;
	this -> poziomZdrowia = static_cast <int16_t>(10);
	this -> sumaWartosciKart = static_cast <int16_t>(0);
}

void Gracz::PolozKarteSpecjalnaNaStol(RodzajKartySpecjalnej && jakaKartaSpecjalna)
{
	sf::Vector2f pozycjaKartySpecjalnej;
	if(!polozoneKartySpecjalneNaStole.empty())
	{
		pozycjaKartySpecjalnej = this -> polozoneKartySpecjalneNaStole
		.back().ZwrocGraficznaReprezentacjeKarty() -> getPosition();
		pozycjaKartySpecjalnej.x += 80.f;
	}
	else
	{
		pozycjaKartySpecjalnej = this -> karty.front()
		.ZwrocGraficznaReprezentacjeKarty() -> getPosition();
		if(pozycjaKartySpecjalnej.y == 450.f)	//Je¿eli karta specjalna jest dla gracza
		{
			pozycjaKartySpecjalnej.y = 305.f;
		}
		else
		{
			pozycjaKartySpecjalnej.y = 235.f;
		}
		
	}
	this -> polozoneKartySpecjalneNaStole.emplace_back(jakaKartaSpecjalna);
	this -> polozoneKartySpecjalneNaStole.back().ZwrocGraficznaReprezentacjeKarty()
	-> setPosition(pozycjaKartySpecjalnej);
}

bool Gracz::SprawdzCzyDokonanoRuchu() const
{
	return this -> czyDokonalRuchu;
}

bool Gracz::SprawdzCzyNieposiadaKartSpecjalnych() const
{
	return this -> kartySpecjalne.empty();
}

bool Gracz::SprawdzCzyZyje() const
{
	return static_cast <bool> (this -> poziomZdrowia);
}

void Gracz::UstawPozycjeKartySpecjalnejWEkwipunku()
{
	//Je¿eli karta ma ju¿ pozycje, wróæ.
	if(this -> kartySpecjalne.back().ZwrocGraficznaReprezentacjeKarty() 
	-> getPosition() != sf::Vector2f(0.f, 0.f))
	{
		return;
	}
	sf::Vector2f pozycjaKartyWEkwipunku;
	std::unordered_map <float, std::unordered_set <float>> pozycjeKartWEkwipunku;
	for(KartaSpecjalna & kartaSpecjalna : this -> kartySpecjalne)
	{
		pozycjaKartyWEkwipunku = kartaSpecjalna.ZwrocGraficznaReprezentacjeKarty() -> getPosition();
		pozycjeKartWEkwipunku[pozycjaKartyWEkwipunku.x].emplace(pozycjaKartyWEkwipunku.y);
	}

	pozycjaKartyWEkwipunku.x = 460.f;
	pozycjaKartyWEkwipunku.y = 120.f;
	while(pozycjeKartWEkwipunku[pozycjaKartyWEkwipunku.x].contains(pozycjaKartyWEkwipunku.y))
	{
		pozycjaKartyWEkwipunku.x += 80.f;
		if(pozycjaKartyWEkwipunku.x == 780.f)
		{
			pozycjaKartyWEkwipunku.x = 460.f;
			pozycjaKartyWEkwipunku.y += 80.f;
		}
	}
	this -> kartySpecjalne.back().ZwrocGraficznaReprezentacjeKarty() -> setPosition(pozycjaKartyWEkwipunku);
}

void Gracz::ZresetujDokonanieRuchu()
{
	this -> czyDokonalRuchu = false;
}

void Gracz::ZresetujStatystykiNaPoczatekRundy()
{
	this -> atak = 1;
	this -> karty.clear();
	this -> polozoneKartySpecjalneNaStole.clear();
	this -> sumaWartosciKart = 0;
}

std::list <KartaSpecjalna>::iterator Gracz::ZwrocIteratorNaKoniecKartSpecjalnych()
{
	return this -> kartySpecjalne.end();
}

std::list <KartaSpecjalna>::iterator Gracz::ZwrocIteratorNaPoczatekKartSpecjalnych()
{
	return this -> kartySpecjalne.begin();
}