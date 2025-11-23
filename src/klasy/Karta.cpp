#include "Karta.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>

Karta::Karta(int16_t & wartosc)
{
	this -> wartosc = wartosc;
	this -> graficznaReprezentacjaKarty.setSize({60.f, 100.f});
	if(this -> grafikaKarty.loadFromFile("resources/karty/" + std::to_string(wartosc) + ".png"))
	{
		this -> graficznaReprezentacjaKarty.setTexture(& (this -> grafikaKarty));
	}
	else
	{
		this -> graficznaReprezentacjaKarty.setFillColor(sf::Color(64, 64, 64));
	}
}

int16_t Karta::ZwrocWartosc() const
{
	return this -> wartosc;
}