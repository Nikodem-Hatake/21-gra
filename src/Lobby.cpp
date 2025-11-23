#include <array>
#include "Audio.hpp"
#include "klasy/Gracz.hpp"
#include "OknoGry.hpp"
#include <thread>

int8_t Lobby()
{
	int8_t numerNajechanegoElementu = 0;
	std::array <sf::RectangleShape, 3> przyciskiWLobby;
	std::array <sf::Text, 3> tekstyWLobby
	{OknoGry::czcionka, OknoGry::czcionka, OknoGry::czcionka};
	{
		sf::Vector2f pozycjaPrzycisku(250.f, 60.f);
		sf::Vector2f rozmiarPrzycisku(300.f, 120.f);
		std::array <const char *, 3> teksty
		{
			"ROZPOCZNIJ",
			"USTAWIENIA",
			"WYJDZ"
		};

		for(int8_t i = 0; i < 3; ++ i)
		{
			przyciskiWLobby[i] = OknoGry::UtworzProstokat
			(pozycjaPrzycisku, rozmiarPrzycisku, sf::Color(64, 64, 64), 2.f);

			tekstyWLobby[i].setCharacterSize(32);
			tekstyWLobby[i].setFillColor(sf::Color::Black);
			tekstyWLobby[i].setString(teksty[i]);
			OknoGry::WysrodkujTekst(tekstyWLobby[i], pozycjaPrzycisku, rozmiarPrzycisku);
			pozycjaPrzycisku.y += 180.f;
		}
	}

	std::jthread renderowanieGrafikiWTle([& przyciskiWLobby, & tekstyWLobby]
	{
		OknoGry::okno.setActive(true);
		int8_t i;
		while(OknoGry::okno.isOpen() && Gracz::czyWLobby)
		{
			OknoGry::okno.clear(sf::Color(240, 240, 240));
			for(i = 0; i < 3; ++ i)
			{
				OknoGry::okno.draw(przyciskiWLobby[i]);
				OknoGry::okno.draw(tekstyWLobby[i]);
			}
			OknoGry::okno.display();
		}
		OknoGry::okno.setActive(false);
	});

	while(OknoGry::okno.isOpen())
	{
		switch(OknoGry::ObslugaEventow())
		{
			case OknoGry::Zdarzenia::klikniecieMyszka:
			{
				sf::Vector2f pozycjaPrzycisku;
				sf::Vector2f rozmiarPrzycisku = przyciskiWLobby[0].getSize();
				int8_t numerKliknietegoPrzycisku = 0;
				for(int8_t i = 0; i < 3; ++ i)
				{
					pozycjaPrzycisku = przyciskiWLobby[i].getPosition();
					if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
					{
						numerKliknietegoPrzycisku = i + 1;
						i = 3;
					}
				}

				if(numerKliknietegoPrzycisku)
				{
					Gracz::czyWLobby = false;
					return numerKliknietegoPrzycisku;
				}
				break;
			}
			case OknoGry::Zdarzenia::poruszenieMyszka:
			{
				sf::Vector2f pozycjaPrzycisku;
				sf::Vector2f rozmiarPrzycisku = przyciskiWLobby[0].getSize();
				int8_t numerNajechanegoPrzycisku = 0;
				for(int8_t i = 0; i < 3; ++ i)
				{
					pozycjaPrzycisku = przyciskiWLobby[i].getPosition();
					if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
					{
						numerNajechanegoPrzycisku = i + 1;
						i = 3;
					}
				}

				if(numerNajechanegoPrzycisku)
				{
					-- numerNajechanegoPrzycisku;
					numerNajechanegoElementu = numerNajechanegoPrzycisku;
					przyciskiWLobby[numerNajechanegoPrzycisku].setFillColor(sf::Color(48, 48, 48));
					przyciskiWLobby[numerNajechanegoPrzycisku].setOutlineThickness(5.f);
				}
				else
				{
					przyciskiWLobby[numerNajechanegoElementu].setFillColor(sf::Color(64, 64, 64));
					przyciskiWLobby[numerNajechanegoElementu].setOutlineThickness(2.f);
				}
			}
		}
	}

	return static_cast <int8_t>(3);
}