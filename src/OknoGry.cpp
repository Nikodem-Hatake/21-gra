#include "klasy/Gracz.hpp"
#include "OknoGry.hpp"

OknoGry::Zdarzenia OknoGry::ObslugaEventow()
{
	if(const std::optional <sf::Event> event = okno.pollEvent())
	{
		if(event -> is <sf::Event::Closed>())
		{
			okno.close();
			return Zdarzenia::zamkniecieOkna;
		}
		else if(const sf::Event::KeyPressed * wcisnietyKlawisz = event -> getIf <sf::Event::KeyPressed>())
		{
			Gracz::wcisnietyKlawisz = wcisnietyKlawisz -> code;
			return Zdarzenia::wcisniecieKlawisza;
		}
		else if(const sf::Event::MouseMoved * poruszenieSieMyszki = event -> getIf <sf::Event::MouseMoved>())
		{
			Gracz::pozycjaMyszki = static_cast <sf::Vector2f>(poruszenieSieMyszki -> position);
			return Zdarzenia::poruszenieMyszka;
		}
		else if(const sf::Event::MouseButtonPressed * klikniecieMyszkaNaEkranie
		= event -> getIf <sf::Event::MouseButtonPressed>())
		{
			return Zdarzenia::klikniecieMyszka;
		}
	}
	return Zdarzenia::nic;
}

__forceinline bool OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce
(sf::Vector2f & pozycjaMiejsca, sf::Vector2f & rozmiarMiejsca)
{
	return (Gracz::pozycjaMyszki.x >= pozycjaMiejsca.x
	&& Gracz::pozycjaMyszki.x <= pozycjaMiejsca.x + rozmiarMiejsca.x
	&& Gracz::pozycjaMyszki.y >= pozycjaMiejsca.y
	&& Gracz::pozycjaMyszki.y <= pozycjaMiejsca.y + rozmiarMiejsca.y);
}

__forceinline sf::RectangleShape OknoGry::UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar)
{
	sf::RectangleShape prostokat(rozmiar);
	prostokat.setPosition(pozycja);
	return prostokat;
}

__forceinline sf::RectangleShape OknoGry::UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar,
sf::Color && kolor)
{
	sf::RectangleShape prostokat(rozmiar);
	prostokat.setFillColor(kolor);
	prostokat.setPosition(pozycja);
	return prostokat;
}

__forceinline sf::RectangleShape OknoGry::UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar,
sf::Color && kolor, float && rozmiarObramowania)
{
	sf::RectangleShape prostokat(rozmiar);
	prostokat.setFillColor(kolor);
	prostokat.setOutlineColor(sf::Color::Black);
	prostokat.setOutlineThickness(rozmiarObramowania);
	prostokat.setPosition(pozycja);
	return prostokat;
}

__forceinline sf::RectangleShape OknoGry::UtworzProstokat(sf::Vector2f & pozycja, sf::Vector2f & rozmiar,
sf::Color && kolor, float && rozmiarObramowania)
{
	sf::RectangleShape prostokat(rozmiar);
	prostokat.setFillColor(kolor);
	prostokat.setOutlineColor(sf::Color::Black);
	prostokat.setOutlineThickness(rozmiarObramowania);
	prostokat.setPosition(pozycja);
	return prostokat;
}

__forceinline sf::Text OknoGry::UtworzTekst(sf::Vector2f && pozycja, unsigned int && rozmiarCzcionki)
{
	sf::Text tekst(OknoGry::czcionka, "", rozmiarCzcionki);
	tekst.setFillColor(sf::Color::Black);
	tekst.setPosition(pozycja);
	return tekst;
}

__forceinline sf::Text OknoGry::UtworzTekst(sf::Vector2f && pozycja,
unsigned int && rozmiarCzcionki, const char * wyswietlanyTekst)
{
	sf::Text tekst(OknoGry::czcionka, wyswietlanyTekst, rozmiarCzcionki);
	tekst.setFillColor(sf::Color::Black);
	tekst.setPosition(pozycja);
	return tekst;
}

__forceinline void OknoGry::WysrodkujTekst(sf::Text & tekst,
sf::Vector2f & pozycjaElementu, sf::Vector2f & rozmiarElementu)
{
	tekst.setOrigin(tekst.getGlobalBounds().size / 2.f
	+ tekst.getLocalBounds().position);
	tekst.setPosition(pozycjaElementu + (rozmiarElementu / 2.f));
}

__forceinline void OknoGry::WysrodkujTekst(sf::Text & tekst,
sf::Vector2f && pozycjaElementu, sf::Vector2f && rozmiarElementu)
{
	tekst.setOrigin(tekst.getGlobalBounds().size / 2.f
	+ tekst.getLocalBounds().position);
	tekst.setPosition(pozycjaElementu + (rozmiarElementu / 2.f));
}