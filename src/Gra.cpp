#include "klasy/RenderowanieRozgrywki.hpp"
#include "klasy/Rozgrywka.hpp"
#include "OknoGry.hpp"
#include <thread>

void Gra()
{
	Gracz gracz;
	Gracz przeciwnik;
	Rozgrywka rozgrywka;
	RenderowanieRozgrywki renderowanieRozgrywki;
	rozgrywka.UtworzIWylosujTalie();
	rozgrywka.WstepnieWylosujDwieKartyDlaGraczy(gracz, przeciwnik);
	for(int8_t i = 0; i < 2; ++ i)
	{
		gracz.DodajKarteSpecjalna(rozgrywka.WylosujKarteSpecjalna());
		gracz.UstawPozycjeKartySpecjalnejWEkwipunku();
		przeciwnik.DodajKarteSpecjalna(rozgrywka.WylosujKarteSpecjalna());
	}
	std::jthread renderowanieGrafikiWTle([&]
	{
		renderowanieRozgrywki.RenderowanieGrafiki(rozgrywka, gracz, przeciwnik);
	});

	bool czyPrzeciwnikMozeWykonacRuch = false;
	bool czyZakonczylaSieRunda = false;
	while(OknoGry::okno.isOpen() && !Gracz::czyWLobby)
	{
		switch(OknoGry::ObslugaEventow())
		{
			case OknoGry::Zdarzenia::wcisniecieKlawisza:
			{
				switch(Gracz::wcisnietyKlawisz)
				{
					case sf::Keyboard::Key::Num1:
					{
						if(czyZakonczylaSieRunda || renderowanieRozgrywki.SprawdzCzyZatrzymanoGre()
						|| renderowanieRozgrywki.SprawdzCzyOtworzonoEkwipunek())
						{
							break;
						}
						else if(rozgrywka.DobierzKarte(gracz))
						{
							czyPrzeciwnikMozeWykonacRuch = true;
						}
						break;
					}
					case sf::Keyboard::Key::Num2:
					{
						if(czyZakonczylaSieRunda || renderowanieRozgrywki.SprawdzCzyZatrzymanoGre()
						|| renderowanieRozgrywki.SprawdzCzyOtworzonoEkwipunek())
						{
							break;
						}
						czyPrzeciwnikMozeWykonacRuch = true;
						break;
					}
					case sf::Keyboard::Key::E:
					{
						if(renderowanieRozgrywki.SprawdzCzyZatrzymanoGre())
						{
							break;
						}
						renderowanieRozgrywki.ZmienStatusOtwarciaEkwipunku();
						break;
					}
					case sf::Keyboard::Key::Escape:
					{
						renderowanieRozgrywki.ZmienStatusZatrzymaniaGry();
						break;
					}
				}
				break;
			}
			case OknoGry::Zdarzenia::poruszenieMyszka:
			{
				if(renderowanieRozgrywki.SprawdzCzyZatrzymanoGre())
				{
					renderowanieRozgrywki.UstawNumerNaNajechanyPrzyciskZatrzymaniaGry();
				}
				else if(renderowanieRozgrywki.SprawdzCzyOtworzonoEkwipunek())
				{
					if(gracz.SprawdzCzyNieposiadaKartSpecjalnych())
					{
						break;
					}
					renderowanieRozgrywki.UstawIteratorNaNajechanaKarteSpecjalna(gracz);
				}
				break;
			}
			case OknoGry::Zdarzenia::klikniecieMyszka:
			{
				if(renderowanieRozgrywki.SprawdzCzyZatrzymanoGre())
				{
					renderowanieRozgrywki.SprawdzGdzieKliknietoMyszkaPodczasZatrzymaniaGry();
				}
				else if(czyZakonczylaSieRunda)
				{
					break;
				}
				else if(renderowanieRozgrywki.SprawdzCzyOtworzonoEkwipunek())
				{
					if(gracz.SprawdzCzyNieposiadaKartSpecjalnych())
					{
						break;
					}

					std::list <KartaSpecjalna>::iterator poczatek = gracz.ZwrocIteratorNaPoczatekKartSpecjalnych();
					std::list <KartaSpecjalna>::iterator koniec = gracz.ZwrocIteratorNaKoniecKartSpecjalnych();
					sf::Vector2f pozycjaPrzycisku;
					sf::Vector2f rozmiarPrzycisku = poczatek -> ZwrocGraficznaReprezentacjeKarty() -> getSize();
					std::list <KartaSpecjalna>::iterator wybranaKartaSpecjalna = koniec;
					for(; poczatek != koniec; ++ poczatek)
					{
						pozycjaPrzycisku = poczatek -> ZwrocGraficznaReprezentacjeKarty() -> getPosition();
						if(OknoGry::SprawdzCzyMyszkaNajechalaDaneMiejsce(pozycjaPrzycisku, rozmiarPrzycisku))
						{
							wybranaKartaSpecjalna = poczatek;
							poczatek = koniec;
							-- poczatek;
						}
					}

					if(wybranaKartaSpecjalna == koniec)
					{
						break;
					}
					rozgrywka.UzyjKartySpecjalnej(gracz, przeciwnik, wybranaKartaSpecjalna);
				}
				break;
			}
		}

		
		if(czyPrzeciwnikMozeWykonacRuch)	//Ruch przeciwnika
		{
			rozgrywka.DokonajNajlepszegoRuchuJakoPrzeciwnik(przeciwnik, gracz);
			//Je¿eli przeciwnik niedokona³ ¿adnego ruchu który móg³by przeszkodziæ graczowi
			//oraz gracz niedokona³ ¿adnego ruchu który móg³by przeszkodziæ przeciwnikowi.
			if(!przeciwnik.SprawdzCzyDokonanoRuchu() && !gracz.SprawdzCzyDokonanoRuchu())
			{
				czyZakonczylaSieRunda = true;
				rozgrywka.SprawdzKtoWygral(gracz, przeciwnik);
				renderowanieRozgrywki.RozpocznijAnimacje();
			}
			gracz.ZresetujDokonanieRuchu();
			przeciwnik.ZresetujDokonanieRuchu();
			czyPrzeciwnikMozeWykonacRuch = false;
		}
		else if(czyZakonczylaSieRunda && !renderowanieRozgrywki.SprawdzCzyTrwaAnimacja())	//Reset rundy
		{
			rozgrywka.ObsluzZwyciezce(gracz, przeciwnik);
			rozgrywka.UtworzIWylosujTalie();
			gracz.ZresetujStatystykiNaPoczatekRundy();
			przeciwnik.ZresetujStatystykiNaPoczatekRundy();
			rozgrywka.WstepnieWylosujDwieKartyDlaGraczy(gracz, przeciwnik);
			gracz.DodajKarteSpecjalna(rozgrywka.WylosujKarteSpecjalna());
			gracz.UstawPozycjeKartySpecjalnejWEkwipunku();
			przeciwnik.DodajKarteSpecjalna(rozgrywka.WylosujKarteSpecjalna());
			rozgrywka.ZresetujLimitWyniku();
			czyZakonczylaSieRunda = false;
			if(!gracz.SprawdzCzyZyje() || !przeciwnik.SprawdzCzyZyje())
			{
				Gracz::czyWLobby = true;
				return;
			}
		}
	}
	Gracz::czyWLobby = true;
}