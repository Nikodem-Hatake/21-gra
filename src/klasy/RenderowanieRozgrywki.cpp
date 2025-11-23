#include <chrono>
#include "../OknoGry.hpp"
#include "RenderowanieRozgrywki.hpp"
#include <string>

RenderowanieRozgrywki::RenderowanieRozgrywki()
{
	this -> czyGraczOtworzylEkwipunek = false;
	this -> czyTrwaAnimacja = false;
	this -> czyZatrzymanoGre = false;
	this -> numerNajechanegoPrzyciskuZatrzymaniaGry = 0;
	for(std::unique_ptr <sf::RectangleShape> & przycickZatrzymaniaGry : this -> przyciskiZatrzymaniaGry)
	{
		przycickZatrzymaniaGry = nullptr;
	}
}

void RenderowanieRozgrywki::RenderowanieGrafiki
(Rozgrywka & rozgrywka, Gracz & gracz, Gracz & przeciwnik)
{
	OknoGry::okno.setActive(true);
	int16_t i;
	int8_t etapAnimacji = 0;
	std::chrono::steady_clock::time_point czasDoZakonczeniaAnimacji;
	std::chrono::duration <float, std::milli> czasTrwaniaKlatki;
	std::chrono::steady_clock::time_point czasRozpoczeciaKlatki;
	std::list <Karta>::iterator poczatekKart, koniecKart;
	std::list <KartaSpecjalna>::iterator poczatek, koniec;
	std::unique_ptr <sf::RectangleShape> tloEkwipunkuGracza = nullptr;
	std::unique_ptr <sf::RectangleShape> tloZatrzymanejGry = nullptr;
	std::array <std::unique_ptr <sf::Text>, 2> tekstyZatrzymaniaGry {nullptr, nullptr};
	sf::Text tekstOKlawiszachDoWcisniecia = OknoGry::UtworzTekst({20.f, 564.f}, 16,
	"1 - DOBIERZ KARTE\t2 - NIEDOBIERAJ KARTY\tE - OTWORZ EKWIPUNEK\tESC - ZATRZYMAJ");
	sf::Text tekstDlaSpecjalnejKarty = OknoGry::UtworzTekst({75.f, 285.f}, 16);
	sf::Text tekstSumyWartosciKartGracza = OknoGry::UtworzTekst({70.f, 400.f}, 32);
	sf::Text tekstAtakuGracza = OknoGry::UtworzTekst({70.f, 368.f}, 32);
	sf::Text tekstPoziomuZdrowiaGracza = OknoGry::UtworzTekst({150.f, 368.f}, 32);
	sf::Text tekstSumyWartosciKartPrzeciwnika = OknoGry::UtworzTekst({70.f, 168.f}, 32);
	sf::Text tekstAtakuPrzeciwnika = OknoGry::UtworzTekst({70.f, 200.f}, 32);
	sf::Text tekstPoziomuZdrowiaPrzeciwnika = OknoGry::UtworzTekst({150.f, 200.f}, 32);
	sf::Text tekstOZwyciezcy = OknoGry::UtworzTekst({350.f, 284.f}, 32);

	sf::RectangleShape tloTekstuOSpecjalnejKarcie 
	= OknoGry::UtworzProstokat({70.f, 280.f}, {350.f, 42.f}, sf::Color(128, 128, 128, 240));
	sf::Texture grafikaUkrytejKarty("resources/karty/ukryta karta.png");
	sf::RectangleShape graficznaReprezentacjaUkrytejKarty 
	= OknoGry::UtworzProstokat({70.f, 50.f}, {60.f, 100.f});
	graficznaReprezentacjaUkrytejKarty.setTexture(& grafikaUkrytejKarty);
	sf::Texture grafikaSerca("resources/symbole/poziom zdrowia.png");
	sf::Texture grafikaAtaku("resources/symbole/atak.png");
	sf::RectangleShape graficznaReprezentacjaSercaGracza
	= OknoGry::UtworzProstokat({190.f, 368.f}, {32.f, 32.f});
	graficznaReprezentacjaSercaGracza.setTexture(& grafikaSerca);
	sf::RectangleShape graficznaReprezentacjaAtakuGracza
	= OknoGry::UtworzProstokat({110.f, 368.f}, {32.f, 32.f});
	graficznaReprezentacjaAtakuGracza.setTexture(& grafikaAtaku);
	sf::RectangleShape graficznaReprezentacjaSercaPrzeciwnika
	= OknoGry::UtworzProstokat({190.f, 200.f}, {32.f, 32.f});
	graficznaReprezentacjaSercaPrzeciwnika.setTexture(& grafikaSerca);
	sf::RectangleShape graficznaReprezentacjaAtakuPrzeciwnika
	= OknoGry::UtworzProstokat({110.f, 200.f}, {32.f, 32.f});
	graficznaReprezentacjaAtakuPrzeciwnika.setTexture(& grafikaAtaku);

	while(OknoGry::okno.isOpen() && !Gracz::czyWLobby)
	{
		OknoGry::okno.clear(sf::Color(240, 240, 240));
		czasRozpoczeciaKlatki = std::chrono::steady_clock::now();
		koniecKart = gracz.karty.end();
		for(poczatekKart = gracz.karty.begin(); poczatekKart != koniecKart; ++ poczatekKart)
		{
			OknoGry::okno.draw(* poczatekKart -> ZwrocGraficznaReprezentacjeKarty());
		}
		if(etapAnimacji == 2)	//Je¿eli trwa animacja koñca rundy, poka¿ ods³oniêt¹ kartê przeciwnika.
		{
			OknoGry::okno.draw(* przeciwnik.karty.front().ZwrocGraficznaReprezentacjeKarty());
		}
		else
		{
			OknoGry::okno.draw(graficznaReprezentacjaUkrytejKarty);
		}
		koniecKart = przeciwnik.karty.end();
		for(poczatekKart = ++ przeciwnik.karty.begin(); poczatekKart != koniecKart; ++ poczatekKart)
		{
			OknoGry::okno.draw(* poczatekKart -> ZwrocGraficznaReprezentacjeKarty());
		}

		koniec = gracz.polozoneKartySpecjalneNaStole.end();
		for(poczatek = gracz.polozoneKartySpecjalneNaStole.begin(); poczatek != koniec; ++ poczatek)
		{
			OknoGry::okno.draw(* poczatek -> ZwrocGraficznaReprezentacjeKarty());
		}
		koniec = przeciwnik.polozoneKartySpecjalneNaStole.end();
		for(poczatek = przeciwnik.polozoneKartySpecjalneNaStole.begin(); poczatek != koniec; ++ poczatek)
		{
			OknoGry::okno.draw(* poczatek -> ZwrocGraficznaReprezentacjeKarty());
		}

		tekstSumyWartosciKartGracza.setString(std::to_string(gracz.sumaWartosciKart)
		+ '/' + std::to_string(rozgrywka.limitWyniku));
		if(etapAnimacji == 2)
		{
			tekstSumyWartosciKartPrzeciwnika.setString(std::to_string(przeciwnik.sumaWartosciKart)
			+ '/' + std::to_string(rozgrywka.limitWyniku));
		}
		else
		{
			tekstSumyWartosciKartPrzeciwnika.setString("? + " + std::to_string
			(przeciwnik.sumaWartosciKart - przeciwnik.karty.front().ZwrocWartosc())
			+ '/' + std::to_string(rozgrywka.limitWyniku));
		}

		if(gracz.atak <= 0)
		{
			tekstAtakuGracza.setString("0");
		}
		else
		{
			tekstAtakuGracza.setString(std::to_string(gracz.atak));
		}
		tekstPoziomuZdrowiaGracza.setString(std::to_string(gracz.poziomZdrowia));
		if(przeciwnik.atak <= 0)
		{
			tekstAtakuPrzeciwnika.setString("0");
		}
		else
		{
			tekstAtakuPrzeciwnika.setString(std::to_string(przeciwnik.atak));
		}
		tekstPoziomuZdrowiaPrzeciwnika.setString(std::to_string(przeciwnik.poziomZdrowia));
		OknoGry::okno.draw(tekstOKlawiszachDoWcisniecia);
		OknoGry::okno.draw(tekstSumyWartosciKartGracza);
		OknoGry::okno.draw(tekstSumyWartosciKartPrzeciwnika);
		OknoGry::okno.draw(tekstAtakuGracza);
		OknoGry::okno.draw(tekstAtakuPrzeciwnika);
		OknoGry::okno.draw(tekstPoziomuZdrowiaGracza);
		OknoGry::okno.draw(tekstPoziomuZdrowiaPrzeciwnika);
		OknoGry::okno.draw(graficznaReprezentacjaSercaGracza);
		OknoGry::okno.draw(graficznaReprezentacjaAtakuGracza);
		OknoGry::okno.draw(graficznaReprezentacjaSercaPrzeciwnika);
		OknoGry::okno.draw(graficznaReprezentacjaAtakuPrzeciwnika);

		if(this -> czyTrwaAnimacja)	//Animacja pokazania zwyciêzcy.
		{
			if(!etapAnimacji)
			{
				etapAnimacji = 1;
				czasDoZakonczeniaAnimacji = std::chrono::steady_clock::now() + std::chrono::seconds(3);
				tekstOZwyciezcy.setString("wygrywa...");
			}
			else if(std::chrono::steady_clock::now() > czasDoZakonczeniaAnimacji 
			&& etapAnimacji == 1)
			{
				etapAnimacji = 2;
				czasDoZakonczeniaAnimacji = std::chrono::steady_clock::now() + std::chrono::milliseconds(1500);
				if(rozgrywka.ktoWygral == Zwyciezca::gracz)
				{
					tekstOZwyciezcy.setString("gracz");
				}
				else if(rozgrywka.ktoWygral == Zwyciezca::przeciwnik)
				{
					tekstOZwyciezcy.setString("przeciwnik");
				}
				else
				{
					tekstOZwyciezcy.setString("remis");
				}
			}
			OknoGry::okno.draw(tekstOZwyciezcy);
			if(std::chrono::steady_clock::now() > czasDoZakonczeniaAnimacji
			&& etapAnimacji == 2)
			{
				this -> czyTrwaAnimacja = false;
				etapAnimacji = 0;
			}
		}
		
		if(this -> czyGraczOtworzylEkwipunek)
		{
			if(tloEkwipunkuGracza == nullptr)
			{
				tloEkwipunkuGracza = std::make_unique <sf::RectangleShape>
				(OknoGry::UtworzProstokat({440.f, 100.f}, {340.f, 420.f}, sf::Color(64, 64, 64, 128)));
			}

			OknoGry::okno.draw(* tloEkwipunkuGracza);
			poczatek = gracz.kartySpecjalne.begin();
			koniec = gracz.kartySpecjalne.end();
			for(; poczatek != koniec; ++ poczatek)
			{
				OknoGry::okno.draw(* poczatek -> ZwrocGraficznaReprezentacjeKarty());
				if(poczatek == this -> iteratorNaNajechanaKarteSpecjalna)
				{
					tekstDlaSpecjalnejKarty.setString(poczatek -> ZwrocTekst());
					OknoGry::okno.draw(tloTekstuOSpecjalnejKarcie);
					OknoGry::okno.draw(tekstDlaSpecjalnejKarty);
				}
			}
		}
		else if(tloEkwipunkuGracza != nullptr)	//Oczyszczenie pamiêci z niewyœwietlanego elementu.
		{
			tloEkwipunkuGracza = nullptr;
		}
		if(this -> czyZatrzymanoGre)
		{
			czasDoZakonczeniaAnimacji += std::chrono::milliseconds
			(static_cast <long long>(czasTrwaniaKlatki.count()));	//Zwiêkszanie czasu trwania animacji
			if(tloZatrzymanejGry == nullptr)
			{
				tloZatrzymanejGry = std::make_unique <sf::RectangleShape>
				(OknoGry::UtworzProstokat({0.f, 0.f}, {800.f, 600.f}, sf::Color(64, 64, 64, 64)));
				sf::Vector2f pozycjaPrzycisku({250.f, 120.f});
				sf::Vector2f rozmiarPrzycisku({300.f, 120.f});
				std::array <const char *, 2> tekstyDlaPrzyciskowZatrzymaniaGry
				{
					"WZNOW GRE",
					"WYJDZ"
				};

				for(i = 0; i < 2; ++ i)
				{
					this -> przyciskiZatrzymaniaGry[i] = std::make_unique <sf::RectangleShape>
					(OknoGry::UtworzProstokat(pozycjaPrzycisku, rozmiarPrzycisku, sf::Color(64, 64, 64), 2.f));
					tekstyZatrzymaniaGry[i] = std::make_unique <sf::Text>
					(OknoGry::czcionka, tekstyDlaPrzyciskowZatrzymaniaGry[i], 32);
					tekstyZatrzymaniaGry[i] -> setFillColor(sf::Color::Black);
					OknoGry::WysrodkujTekst(* tekstyZatrzymaniaGry[i],
					this -> przyciskiZatrzymaniaGry[i] -> getPosition(),
					this -> przyciskiZatrzymaniaGry[i] -> getSize());
					pozycjaPrzycisku.y += 180.f;
				}
			}

			OknoGry::okno.draw(* tloZatrzymanejGry);
			for(i = 0; i < 2; ++ i)
			{
				OknoGry::okno.draw(* this -> przyciskiZatrzymaniaGry[i]);
				OknoGry::okno.draw(* tekstyZatrzymaniaGry[i]);
			}
		}
		else if(tloZatrzymanejGry != nullptr)	//Oczyszczenie pamiêci z niewyœwietlanych elementów.
		{
			tloZatrzymanejGry = nullptr;
			for(i = 0; i < 2; ++ i)
			{
				this -> przyciskiZatrzymaniaGry[i] = nullptr;
				tekstyZatrzymaniaGry[i] = nullptr;
			}
		}
		OknoGry::okno.display();
		czasTrwaniaKlatki = std::chrono::steady_clock::now() - czasRozpoczeciaKlatki;
	}
	OknoGry::okno.setActive(false);
}

void RenderowanieRozgrywki::RozpocznijAnimacje()
{
	this -> czyTrwaAnimacja = true;
}

bool RenderowanieRozgrywki::SprawdzCzyOtworzonoEkwipunek() const
{
	return this -> czyGraczOtworzylEkwipunek;
}

bool RenderowanieRozgrywki::SprawdzCzyTrwaAnimacja() const
{
	return this -> czyTrwaAnimacja;
}

bool RenderowanieRozgrywki::SprawdzCzyZatrzymanoGre() const
{
	return this -> czyZatrzymanoGre;
}

void RenderowanieRozgrywki::SprawdzGdzieKliknietoMyszkaPodczasZatrzymaniaGry()
{
	if(this -> przyciskiZatrzymaniaGry.back() == nullptr)	//Sprawdzenie, czy przyciski s¹ wyrenderowane.
	{
		return;
	}
	else if(this -> numerNajechanegoPrzyciskuZatrzymaniaGry == 1)
	{
		this -> czyZatrzymanoGre = false;
	}
	else if(this -> numerNajechanegoPrzyciskuZatrzymaniaGry == 2)	//Wyjœcie do lobby.
	{
		Gracz::czyWLobby = true;
	}
}

void RenderowanieRozgrywki::UstawIteratorNaNajechanaKarteSpecjalna(Gracz & gracz)
{
	bool czyNajechanoNaKarte = false;
	std::list <KartaSpecjalna>::iterator poczatek = gracz.kartySpecjalne.begin();
	std::list <KartaSpecjalna>::iterator koniec = gracz.kartySpecjalne.end();
	sf::Vector2f rozmiarKartySpecjalnej = poczatek -> ZwrocGraficznaReprezentacjeKarty() -> getSize();
	sf::Vector2f pozycjaKartySpecjalnej;

	for(; poczatek != koniec; ++ poczatek)
	{
		pozycjaKartySpecjalnej = poczatek -> ZwrocGraficznaReprezentacjeKarty() -> getPosition();
		if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaKartySpecjalnej, rozmiarKartySpecjalnej))
		{
			czyNajechanoNaKarte = true;
			this -> iteratorNaNajechanaKarteSpecjalna = poczatek;
			poczatek = koniec;
			-- poczatek;
		}
	}

	if(!czyNajechanoNaKarte)
	{
		this -> iteratorNaNajechanaKarteSpecjalna = koniec;
	}
}

void RenderowanieRozgrywki::UstawNumerNaNajechanyPrzyciskZatrzymaniaGry()
{
	if(this -> przyciskiZatrzymaniaGry.back() == nullptr)	//Sprawdzenie, czy przyciski s¹ wyrenderowane.
	{
		return;
	}
	sf::Vector2f pozycjaPrzycisku;
	sf::Vector2f rozmiarPrzycisku = this -> przyciskiZatrzymaniaGry[0] -> getSize();
	int8_t numerNajechanegoElementu = 0;
	for(int8_t i = 0; i < 2; ++ i)
	{
		pozycjaPrzycisku = this -> przyciskiZatrzymaniaGry[i] -> getPosition();
		if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
		{
			numerNajechanegoElementu = i + 1;
			i = 2;
		}
	}

	if(numerNajechanegoElementu)
	{
		numerNajechanegoElementu;
		this -> numerNajechanegoPrzyciskuZatrzymaniaGry = numerNajechanegoElementu;
		this -> przyciskiZatrzymaniaGry[this -> numerNajechanegoPrzyciskuZatrzymaniaGry - 1]
		-> setFillColor(sf::Color(48, 48, 48));
		this -> przyciskiZatrzymaniaGry[this -> numerNajechanegoPrzyciskuZatrzymaniaGry - 1]
		-> setOutlineThickness(5.f);
	}
	else if(this->numerNajechanegoPrzyciskuZatrzymaniaGry)
	{
		this -> przyciskiZatrzymaniaGry[this -> numerNajechanegoPrzyciskuZatrzymaniaGry - 1]
		-> setFillColor(sf::Color(64, 64, 64));
		this -> przyciskiZatrzymaniaGry[this -> numerNajechanegoPrzyciskuZatrzymaniaGry - 1]
		-> setOutlineThickness(2.f);
		this -> numerNajechanegoPrzyciskuZatrzymaniaGry = 0;
	}
}

void RenderowanieRozgrywki::ZmienStatusOtwarciaEkwipunku()
{
	if(this -> czyGraczOtworzylEkwipunek)
	{
		this -> czyGraczOtworzylEkwipunek = false;
	}
	else
	{
		this -> czyGraczOtworzylEkwipunek = true;
	}
}

void RenderowanieRozgrywki::ZmienStatusZatrzymaniaGry()
{
	if(this -> czyZatrzymanoGre)
	{
		this -> czyZatrzymanoGre = false;
	}
	else
	{
		this -> czyZatrzymanoGre = true;
	}
}