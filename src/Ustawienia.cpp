#include <array>
#include "Audio.hpp"
#include "klasy/Gracz.hpp"
#include "OknoGry.hpp"
#include <thread>

void Ustawienia()
{
	bool czyMoznaZmieniacGlosnosc = true;
	int8_t numerNajechanegoElementu = 0;
	std::array <sf::RectangleShape, 2> przyciskiUstawien;
	std::array <sf::Text, 2> tekstyUstawien
	{OknoGry::czcionka, OknoGry::czcionka};
	sf::RectangleShape pasekGlosnosci;
	{
		sf::Vector2f pozycjaPrzycisku(250.f, 60.f);
		sf::Vector2f rozmiarPrzycisku(300.f, 120.f);
		std::array <const char *, 2> teksty
		{
			"ZMIEN POZIOM\nGLOSNOSCI",
			"WYJDZ"
		};
		pasekGlosnosci.setPosition(pozycjaPrzycisku);
		if(Audio::muzykaWTle == nullptr)
		{
			czyMoznaZmieniacGlosnosc = false;
			teksty[0] = "MUZYKA W TLE\nJEST NIEDOSTEPNA";
		}
		else
		{
			pasekGlosnosci.setSize({Audio::muzykaWTle -> getVolume() * 3.f, rozmiarPrzycisku.y});
		}
		pasekGlosnosci.setFillColor(sf::Color::Cyan);

		for(int8_t i = 0; i < 2; ++ i)
		{
			przyciskiUstawien[i] = OknoGry::UtworzProstokat
			(pozycjaPrzycisku, rozmiarPrzycisku, sf::Color(64, 64, 64), 2.f);

			tekstyUstawien[i].setCharacterSize(32);
			tekstyUstawien[i].setFillColor(sf::Color::Black);
			tekstyUstawien[i].setString(teksty[i]);
			OknoGry::WysrodkujTekst(tekstyUstawien[i], pozycjaPrzycisku, rozmiarPrzycisku);
			pozycjaPrzycisku.y += 180.f;
		}
	}

	std::jthread renderowanieGrafikiWTle([& przyciskiUstawien, & tekstyUstawien, & pasekGlosnosci]
	{
		OknoGry::okno.setActive(true);
		int8_t i;
		while(OknoGry::okno.isOpen() && !Gracz::czyWLobby)
		{
			OknoGry::okno.clear(sf::Color(240, 240, 240));
			for(i = 0; i < 2; ++ i)
			{
				OknoGry::okno.draw(przyciskiUstawien[i]);
			}
			OknoGry::okno.draw(pasekGlosnosci);
			for(i = 0; i < 2; ++ i)
			{
				OknoGry::okno.draw(tekstyUstawien[i]);
			}
			OknoGry::okno.display();
		}
		OknoGry::okno.setActive(false);
	});

	while(OknoGry::okno.isOpen() && !Gracz::czyWLobby)
	{
		switch(OknoGry::ObslugaEventow())
		{
			case OknoGry::Zdarzenia::wcisniecieKlawisza:
			{
				if(Gracz::wcisnietyKlawisz == sf::Keyboard::Key::Escape)
				{
					Gracz::czyWLobby = true;
				}
				break;
			}
			case OknoGry::Zdarzenia::klikniecieMyszka:
			{
				sf::Vector2f pozycjaPrzycisku;
				sf::Vector2f rozmiarPrzycisku = przyciskiUstawien[0].getSize();
				int8_t numerKliknietegoPrzycisku = 0;
				for(int8_t i = 0; i < 2; ++ i)
				{
					pozycjaPrzycisku = przyciskiUstawien[i].getPosition();
					if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
					{
						numerKliknietegoPrzycisku = i + 1;
						i = 2;
					}
				}

				if(numerKliknietegoPrzycisku == 1)
				{
					if(Audio::muzykaWTle == nullptr && czyMoznaZmieniacGlosnosc)
					{
						//Wy³¹czenie paska g³oœnoœci.
						czyMoznaZmieniacGlosnosc = false;
						pasekGlosnosci.setSize({0.f, 0.f});
						tekstyUstawien[0].setString("MUZYKA W TLE\nJEST NIEDOSTEPNA");
						OknoGry::WysrodkujTekst(tekstyUstawien[0], 
						przyciskiUstawien[0].getPosition(), przyciskiUstawien[0].getSize());
					}
					else if(czyMoznaZmieniacGlosnosc)
					{
						//Ustawianie poziomu g³oœnoœci na podstawie odleg³oœci 
						//miêdzy klikniêciem myszk¹ a d³ugoœci¹ paska.
						float poziomGlosnosci = (Gracz::pozycjaMyszki.x - pozycjaPrzycisku.x) / 3.f;
						Audio::muzykaWTle -> setVolume(poziomGlosnosci);
						pasekGlosnosci.setSize({poziomGlosnosci * 3.f, rozmiarPrzycisku.y});
					}
				}
				else if(numerKliknietegoPrzycisku == 2)
				{
					Gracz::czyWLobby = true;
				}
				break;
			}
			case OknoGry::Zdarzenia::poruszenieMyszka:
			{
				sf::Vector2f pozycjaPrzycisku;
				sf::Vector2f rozmiarPrzycisku = przyciskiUstawien[0].getSize();
				int8_t numerNajechanegoPrzycisku = 0;
				for(int8_t i = 0; i < 2; ++ i)
				{
					pozycjaPrzycisku = przyciskiUstawien[i].getPosition();
					if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
					{
						numerNajechanegoPrzycisku = i + 1;
						i = 2;
					}
				}
				
				if(numerNajechanegoPrzycisku)
				{
					-- numerNajechanegoPrzycisku;
					numerNajechanegoElementu = numerNajechanegoPrzycisku;
					przyciskiUstawien[numerNajechanegoPrzycisku].setFillColor(sf::Color(48, 48, 48));
					przyciskiUstawien[numerNajechanegoPrzycisku].setOutlineThickness(5.f);
				}
				else
				{
					przyciskiUstawien[numerNajechanegoElementu].setFillColor(sf::Color(64, 64, 64));
					przyciskiUstawien[numerNajechanegoElementu].setOutlineThickness(2.f);
				}
				break;
			}
		}
	}
}