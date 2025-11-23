#include "KartaSpecjalna.hpp"

KartaSpecjalna::KartaSpecjalna(RodzajKartySpecjalnej & jakaKartaSpecjalna)
{
	this -> jakaKartaSpecjalna = jakaKartaSpecjalna;
	this -> graficznaReprezentacjaKarty.setSize({60.f, 60.f});
	const char * sciezkaDoObrazka;

	switch(jakaKartaSpecjalna)
	{
		case RodzajKartySpecjalnej::dobierzIdealnaKarte:
		{
			sciezkaDoObrazka = "resources/karty/dobierz idealna karte.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz najlepsza dla\nciebie karte z talii";
			this -> wartoscKartySpecjalnej = 0;
			break;
		}
		case RodzajKartySpecjalnej::dobierzIdealnaKarteIZwiekszAtakOPiec:
		{
			sciezkaDoObrazka = "resources/karty/dobierz idealna karte i zwieksz atak o 5.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz najlepsza dla ciebie karte z"
			"\ntalii i zwieksz atak o 5";
			this -> wartoscKartySpecjalnej = 5;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciDwa:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 2.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 2";
			this -> wartoscKartySpecjalnej = 2;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciTrzy:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 3.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 3";
			this -> wartoscKartySpecjalnej = 3;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciCztery:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 4.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 4";
			this -> wartoscKartySpecjalnej = 4;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciPiec:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 5.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 5";
			this -> wartoscKartySpecjalnej = 5;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciSzesc:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 6.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 6";
			this -> wartoscKartySpecjalnej = 6;
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciSiedem:
		{
			sciezkaDoObrazka = "resources/karty/dobierz karte o wartosci 7.png";
			this -> tekstOSpecjalnejKarcie = "Dobierz karte o wartosci 7";
			this -> wartoscKartySpecjalnej = 7;
			break;
		}
		case RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte:
		{
			sciezkaDoObrazka = "resources/karty/odrzuc ostatnia wylosowana karte.png";
			this -> tekstOSpecjalnejKarcie = "Odrzuc ostatnia twoja karte";
			this -> wartoscKartySpecjalnej = 0;
			break;
		}
		case RodzajKartySpecjalnej::usunKartySpecjalnePrzeciwnikaZeStolu:
		{
			sciezkaDoObrazka = "resources/karty/usun karty specjalne przeciwnika ze stolu.png";
			this -> tekstOSpecjalnejKarcie = "Usun polozone przez przeciwnika karty\nspecjalne ze stolu";
			this -> wartoscKartySpecjalnej = 0;
			break;
		}
		case RodzajKartySpecjalnej::zamienSieOstatniaWylosowanaKartaZGraczem:
		{
			sciezkaDoObrazka = "resources/karty/zamien sie ostatnia wylosowana karta z graczem.png";
			this -> tekstOSpecjalnejKarcie = "Zamien sie ostatnia wylosowana karta z"
			"\nprzeciwnikiem rozna od pierwszej karty";
			this -> wartoscKartySpecjalnej = 0;
			break;
		}
		case RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie:
		{
			sciezkaDoObrazka = "resources/karty/zmien limit wyniku na 17.png";
			this -> tekstOSpecjalnejKarcie = "Zmien limit wyniku gry na 17";
			this -> wartoscKartySpecjalnej = 17;
			break;
		}
		case RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery:
		{
			sciezkaDoObrazka = "resources/karty/zmien limit wyniku na 24.png";
			this -> tekstOSpecjalnejKarcie = "Zmien limit wyniku gry na 24";
			this -> wartoscKartySpecjalnej = 24;
			break;
		}
		case RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem:
		{
			sciezkaDoObrazka = "resources/karty/zmien limit wyniku na 27.png";
			this -> tekstOSpecjalnejKarcie = "Zmien limit wyniku gry na 27";
			this -> wartoscKartySpecjalnej = 27;
			break;
		}
		case RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden:
		{
			sciezkaDoObrazka = "resources/karty/zmniejsz atak przeciwnika o 1.png";
			this -> tekstOSpecjalnejKarcie = "Zmniejsz atak przeciwnika o 1";
			this -> wartoscKartySpecjalnej = 1;
			break;
		}
		case RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa:
		{
			sciezkaDoObrazka = "resources/karty/zmniejsz atak przeciwnika o 2.png";
			this -> tekstOSpecjalnejKarcie = "Zmniejsz atak przeciwnika o 2";
			this -> wartoscKartySpecjalnej = 2;
			break;
		}
		case RodzajKartySpecjalnej::zwiekszAtakOJeden:
		{
			sciezkaDoObrazka = "resources/karty/zwieksz atak o 1.png";
			this -> tekstOSpecjalnejKarcie = "Zwieksz atak o 1";
			this -> wartoscKartySpecjalnej = 1;
			break;
		}
		case RodzajKartySpecjalnej::zwiekszAtakODwa:
		{
			sciezkaDoObrazka = "resources/karty/zwieksz atak o 2.png";
			this -> tekstOSpecjalnejKarcie = "Zwieksz atak o 2";
			this -> wartoscKartySpecjalnej = 2;
			break;
		}
	}

	if(this -> grafikaKarty.loadFromFile(sciezkaDoObrazka))
	{
		this -> graficznaReprezentacjaKarty.setTexture(& (this -> grafikaKarty));
	}
	else
	{
		this -> graficznaReprezentacjaKarty.setFillColor(sf::Color(64, 64, 64));
	}
}

RodzajKartySpecjalnej KartaSpecjalna::ZwrocRodzajKartySpecjalnej() const
{
	return this -> jakaKartaSpecjalna;
}

const char * KartaSpecjalna::ZwrocTekst() const
{
	return this -> tekstOSpecjalnejKarcie;
}

int16_t KartaSpecjalna::ZwrocWartoscKartySpecjalnej() const
{
	return this -> wartoscKartySpecjalnej;
}