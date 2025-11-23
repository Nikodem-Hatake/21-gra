#ifndef OknoGry_hpp
#define OknoGry_hpp

#include <cstdint>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace OknoGry
{
	enum struct Zdarzenia : int8_t
	{
		zamkniecieOkna,
		klikniecieMyszka,
		poruszenieMyszka,
		wcisniecieKlawisza,
		nic
	};

	inline sf::RenderWindow okno(sf::VideoMode({800, 600}), "21", sf::Style::Close);
	inline const sf::Font czcionka("resources/czcionki/czcionka.ttf");
	extern Zdarzenia ObslugaEventow();
	extern __forceinline bool SprawdzCzyMyszkaNajechalaDaneMiejsce
	(sf::Vector2f & pozycjaMiejsca, sf::Vector2f & rozmiarMiejsca);
	extern __forceinline sf::RectangleShape UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar);
	extern __forceinline sf::RectangleShape UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar,
	sf::Color && kolor);
	extern __forceinline sf::RectangleShape UtworzProstokat(sf::Vector2f && pozycja, sf::Vector2f && rozmiar,
	sf::Color && kolor, float && rozmiarObramowania);
	extern __forceinline sf::RectangleShape UtworzProstokat(sf::Vector2f & pozycja, sf::Vector2f & rozmiar,
	sf::Color && kolor, float && rozmiarObramowania);
	extern __forceinline sf::Text UtworzTekst(sf::Vector2f && pozycja, unsigned int && rozmiarCzcionki);
	extern __forceinline sf::Text UtworzTekst(sf::Vector2f && pozycja, unsigned int && rozmiarCzcionki,
	const char * wyswietlanyTekst);
	extern __forceinline void WysrodkujTekst(sf::Text & tekst,
	sf::Vector2f & pozycjaElementu, sf::Vector2f & rozmiarElementu);
	extern __forceinline void WysrodkujTekst(sf::Text & tekst,
	sf::Vector2f && pozycjaElementu, sf::Vector2f && rozmiarElementu);
};

#endif