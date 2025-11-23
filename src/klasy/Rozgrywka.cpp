#include <forward_list>
#include "Rozgrywka.hpp"
#include <unordered_map>
#include <unordered_set>

bool Rozgrywka::DobierzKarte(Gracz & gracz)
{
	if(gracz.sumaWartosciKart > this -> limitWyniku
	|| this -> kartyDoDobierania.empty())
	{
		return false;
	}

	while(!this -> kartyDoDobierania.empty() && !this -> dostepneKarty[this -> kartyDoDobierania.front()])
	{
		this -> kartyDoDobierania.pop_front();
	}
	if(this -> kartyDoDobierania.empty())
	{
		return false;
	}

	gracz.DokonajRuchu();
	gracz.DodajKarte(this -> kartyDoDobierania.front());
	this -> dostepneKarty[this -> kartyDoDobierania.front()] = false;
	this -> kartyDoDobierania.pop_front();
	return true;
}

void Rozgrywka::DokonajNajlepszegoRuchuJakoPrzeciwnik(Gracz & przeciwnik, Gracz & gracz)
{
	bool czyDobracKarte = false;
	std::unordered_map <RodzajKartySpecjalnej, std::forward_list 
	<std::list <KartaSpecjalna>::iterator>> kartySpecjalnePrzeciwnika;
	{
		//Wype³nianie multimapy kartami specjalnymi jakie posiada przeciwnik oraz ich iteratorami.
		std::list <KartaSpecjalna>::iterator poczatek, koniec = przeciwnik.kartySpecjalne.end();
		for(poczatek = przeciwnik.kartySpecjalne.begin(); poczatek != koniec; ++ poczatek)
		{
			kartySpecjalnePrzeciwnika[poczatek -> ZwrocRodzajKartySpecjalnej()].emplace_front(poczatek);
		}
	}
	
	if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zamienSieOstatniaWylosowanaKartaZGraczem)
	&& this -> limitWyniku < przeciwnik.sumaWartosciKart && przeciwnik.sumaWartosciKart 
	- przeciwnik.karty.back().ZwrocWartosc() + gracz.karty.back().ZwrocWartosc() <= this -> limitWyniku)
	{
		this -> UzyjKartySpecjalnej(przeciwnik, gracz, kartySpecjalnePrzeciwnika
		[RodzajKartySpecjalnej::zamienSieOstatniaWylosowanaKartaZGraczem].front());
	}
	//Sprawdzanie, czy przeciwnik powinien zmieniæ limit wyniku.
	if(przeciwnik.sumaWartosciKart > this -> limitWyniku
	&& przeciwnik.polozoneKartySpecjalneNaStole.size() < 5)
	{
		RodzajKartySpecjalnej jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::nic;
		if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie)
		&& kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte)
		&& przeciwnik.sumaWartosciKart - przeciwnik.karty.back().ZwrocWartosc() <= 17)
		{
			jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie;
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte].front());
		}
		else if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery)
		&& przeciwnik.sumaWartosciKart - 24 >= 0)
		{
			jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery;
		}
		else if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem)
		&& przeciwnik.sumaWartosciKart - 27 >= 0)
		{
			jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem;
		}
		else if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem)
		&& kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte)
		&& przeciwnik.sumaWartosciKart - przeciwnik.karty.back().ZwrocWartosc() <= 27)
		{
			jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem;
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte].front());
		}
		else if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery)
		&& kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte)
		&& przeciwnik.sumaWartosciKart - przeciwnik.karty.back().ZwrocWartosc() <= 24)
		{
			jakaKarteZmianyLimituUzyc = RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery;
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte].front());
		}

		if(jakaKarteZmianyLimituUzyc != RodzajKartySpecjalnej::nic)
		{
			this -> UzyjKartySpecjalnej(przeciwnik, gracz, 
			kartySpecjalnePrzeciwnika[jakaKarteZmianyLimituUzyc].front());
		}
	}
	//Sprawdzanie czy przeciwnik powinien dobraæ kartê.
	if(przeciwnik.sumaWartosciKart < this -> limitWyniku
	&& this -> limitWyniku - przeciwnik.sumaWartosciKart > 4)
	{
		bool czyUzytoKartySpecjalnejDoDobraniaKarty = false;
		int16_t ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku 
		= this -> limitWyniku - przeciwnik.sumaWartosciKart;
		int16_t iloscDostepnychKart = 0;
		std::list <int16_t> jakieKartyPoprawiaWynikPrzeciwnika;
		if(ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku > 11)
		{
			ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku = 11;
		}

		for(int16_t i = 1; i <= ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku; ++ i)
		{
			if(this -> dostepneKarty[i])
			{
				jakieKartyPoprawiaWynikPrzeciwnika.emplace_back(i);
			}
		}

		//U¿ywanie kart specjalnych które mog¹ poprawiæ wynik.
		for(int16_t & jakaKartaPoprawiWynikPrzeciwnika : jakieKartyPoprawiaWynikPrzeciwnika)
		{
			if(jakaKartaPoprawiWynikPrzeciwnika > 1 && jakaKartaPoprawiWynikPrzeciwnika < 8
			&& kartySpecjalnePrzeciwnika.contains(static_cast 
			<RodzajKartySpecjalnej> (jakaKartaPoprawiWynikPrzeciwnika)) &&
			jakaKartaPoprawiWynikPrzeciwnika <= this -> limitWyniku - przeciwnik.sumaWartosciKart)
			{
				czyUzytoKartySpecjalnejDoDobraniaKarty = true;
				this -> UzyjKartySpecjalnej(przeciwnik, gracz, kartySpecjalnePrzeciwnika
				[static_cast <RodzajKartySpecjalnej>(jakaKartaPoprawiWynikPrzeciwnika)].front());
			}
		}
		if(!czyUzytoKartySpecjalnejDoDobraniaKarty && !jakieKartyPoprawiaWynikPrzeciwnika.empty()
		&& kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::dobierzIdealnaKarte))
		{
			czyUzytoKartySpecjalnejDoDobraniaKarty = true;
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::dobierzIdealnaKarte].front());

		}
		else if(!czyUzytoKartySpecjalnejDoDobraniaKarty && !jakieKartyPoprawiaWynikPrzeciwnika.empty()
		&& kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::dobierzIdealnaKarteIZwiekszAtakOPiec))
		{
			czyUzytoKartySpecjalnejDoDobraniaKarty = true;
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::dobierzIdealnaKarteIZwiekszAtakOPiec].front());
		}

		//Sprawdzanie na nowo jakie karty poprawi³iby wynik przeciwnika.
		if(czyUzytoKartySpecjalnejDoDobraniaKarty)
		{
			jakieKartyPoprawiaWynikPrzeciwnika.clear();
			ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku
			= this -> limitWyniku - przeciwnik.sumaWartosciKart;
			if(ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku > 11)
			{
				ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku = 11;
			}

			for(int16_t i = 1; i <= ilePrzeciwnikowiBrakujeDoNajlepszegoWyniku; ++ i)
			{
				if(this -> dostepneKarty[i])
				{
					jakieKartyPoprawiaWynikPrzeciwnika.emplace_back(i);
				}
			}
		}
		//Je¿eli kart jakie mo¿e dobraæ przeciwnik jest wiêcej b¹dŸ tyle samo co po³owa dostêpnych kart
		if((11 - gracz.karty.size() - przeciwnik.karty.size()) / 2
		<= jakieKartyPoprawiaWynikPrzeciwnika.size() && !jakieKartyPoprawiaWynikPrzeciwnika.empty())
		{
			czyDobracKarte = true;
		}
	}
	//Zwiêkszanie ataku w op³acalnej sytuacji dla przeciwnika.
	if((przeciwnik.sumaWartosciKart == this -> limitWyniku
	|| (przeciwnik.sumaWartosciKart < this -> limitWyniku 
	&& this->limitWyniku - przeciwnik.sumaWartosciKart < 4
	&& gracz.sumaWartosciKart != this -> limitWyniku))
	&& przeciwnik.polozoneKartySpecjalneNaStole.size() < 5)
	{
		if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zwiekszAtakODwa))
		{
			while(przeciwnik.polozoneKartySpecjalneNaStole.size() < 5
			&& !kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakODwa].empty())
			{
				this -> UzyjKartySpecjalnej(przeciwnik, gracz, 
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakODwa].front());
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakODwa].pop_front();
			}
		}
		if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zwiekszAtakOJeden))
		{
			while(przeciwnik.polozoneKartySpecjalneNaStole.size() < 5
			&& !kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakOJeden].empty())
			{
				this -> UzyjKartySpecjalnej(przeciwnik, gracz,
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakOJeden].front());
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zwiekszAtakOJeden].pop_front();
			}
		}
	}
	//Zmniejszanie ataku gracza.
	if(((gracz.sumaWartosciKart == this -> limitWyniku && przeciwnik.sumaWartosciKart != this -> limitWyniku)
	|| (gracz.sumaWartosciKart < this -> limitWyniku && this -> limitWyniku - gracz.sumaWartosciKart < 4
	&& przeciwnik.sumaWartosciKart != limitWyniku)) && przeciwnik.polozoneKartySpecjalneNaStole.size() < 5)
	{
		bool czyZmniejszonoAtak = false;
		if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa))
		{
			while(przeciwnik.polozoneKartySpecjalneNaStole.size() < 5
			&& !kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa].empty())
			{
				czyZmniejszonoAtak = true;
				this -> UzyjKartySpecjalnej(przeciwnik, gracz,
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa].front());
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa].pop_front();
			}
		}
		if(kartySpecjalnePrzeciwnika.contains(RodzajKartySpecjalnej::zwiekszAtakOJeden))
		{
			while(przeciwnik.polozoneKartySpecjalneNaStole.size() < 5
			&& !kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden].empty())
			{
				czyZmniejszonoAtak = true;
				this -> UzyjKartySpecjalnej(przeciwnik, gracz,
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden].front());
				kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden].pop_front();
			}
		}

		if(!czyZmniejszonoAtak && kartySpecjalnePrzeciwnika.
		contains(RodzajKartySpecjalnej::usunKartySpecjalnePrzeciwnikaZeStolu))
		{
			this -> UzyjKartySpecjalnej(przeciwnik, gracz,
			kartySpecjalnePrzeciwnika[RodzajKartySpecjalnej::usunKartySpecjalnePrzeciwnikaZeStolu].front());
		}
	}

	if(czyDobracKarte)
	{
		this -> DobierzKarte(przeciwnik);
	}
}

void Rozgrywka::ObsluzZwyciezce(Gracz & gracz, Gracz & przeciwnik)
{
	if(this -> ktoWygral == Zwyciezca::gracz)
	{
		if(gracz.atak <= 0)
		{
			return;
		}
		else if(przeciwnik.poziomZdrowia - gracz.atak <= 0)
		{
			przeciwnik.poziomZdrowia = 0;
		}
		else
		{
			przeciwnik.poziomZdrowia -= gracz.atak;
		}
	}
	else if(this -> ktoWygral == Zwyciezca::przeciwnik)
	{
		if(przeciwnik.atak <= 0)
		{
			return;
		}
		else if(gracz.poziomZdrowia - przeciwnik.atak <= 0)
		{
			gracz.poziomZdrowia = 0;
		}
		else
		{
			gracz.poziomZdrowia -= przeciwnik.atak;
		}
	}
}

Rozgrywka::Rozgrywka()
{
	this -> generatorLosowychLiczb.seed((std::random_device())());
	this -> limitWyniku = 21;
}

void Rozgrywka::SprawdzKtoWygral(Gracz & gracz, Gracz & przeciwnik)
{
	if(gracz.sumaWartosciKart == przeciwnik.sumaWartosciKart)
	{
		this -> ktoWygral = Zwyciezca::remis;
	}
	else if((gracz.sumaWartosciKart > przeciwnik.sumaWartosciKart
	&& gracz.sumaWartosciKart > this -> limitWyniku)
	|| (gracz.sumaWartosciKart < przeciwnik.sumaWartosciKart
	&& przeciwnik.sumaWartosciKart <= this -> limitWyniku))
	{
		this -> ktoWygral = Zwyciezca::przeciwnik;
	}
	else
	{
		this -> ktoWygral = Zwyciezca::gracz;
	}
}

void Rozgrywka::UtworzIWylosujTalie()
{
	this -> dostepneKarty.fill(true);
	this -> kartyDoDobierania.clear();
	std::uniform_int_distribution <int16_t> zakresWartosciKart(1, 11);
	std::unordered_set <int16_t> wartosciKartDoDobrania;
	wartosciKartDoDobrania.reserve(11);
	int16_t i = 0, wylosowanaWartoscKarty, iloscProbWylosowania = 0;

	for(; i < 11; ++ i, iloscProbWylosowania = 1)
	{
		wylosowanaWartoscKarty = zakresWartosciKart(this -> generatorLosowychLiczb);
		while(wartosciKartDoDobrania.contains(wylosowanaWartoscKarty)
		&& iloscProbWylosowania < 11)
		{
			++ iloscProbWylosowania;
			wylosowanaWartoscKarty = zakresWartosciKart(this -> generatorLosowychLiczb);
		}

		if(wartosciKartDoDobrania.contains(wylosowanaWartoscKarty))
		{
			int16_t j = 1;
			while(wartosciKartDoDobrania.contains(j))
			{
				++ j;
			}
			wylosowanaWartoscKarty = j;
		}
		wartosciKartDoDobrania.emplace(wylosowanaWartoscKarty);
		this -> kartyDoDobierania.emplace_back(wylosowanaWartoscKarty);
	}
}

void Rozgrywka::UzyjKartySpecjalnej(Gracz & gracz, Gracz & przeciwnik, 
std::list <KartaSpecjalna>::iterator & wybranaKarta)
{
	bool czyUdaloSieUzycKarty = false;
	switch(wybranaKarta -> ZwrocRodzajKartySpecjalnej())
	{
		case RodzajKartySpecjalnej::dobierzIdealnaKarte:
		case RodzajKartySpecjalnej::dobierzIdealnaKarteIZwiekszAtakOPiec:
		{
			czyUdaloSieUzycKarty = true;
			int16_t sumaWartosciKartGracza = gracz.sumaWartosciKart;
			if(sumaWartosciKartGracza > this -> limitWyniku
			|| this -> kartyDoDobierania.empty())
			{
				break;
			}
			
			int16_t najlepszaKarta = this -> limitWyniku - sumaWartosciKartGracza;
			if(najlepszaKarta < 1)	//Je¿eli niema po co dobieraæ najlepszej karty, wróæ.
			{
				break;
			}
			else if(najlepszaKarta > 11)
			{
				najlepszaKarta = 11;
			}

			while(najlepszaKarta && !this -> dostepneKarty[najlepszaKarta])
			{
				-- najlepszaKarta;
			}
			if(!najlepszaKarta)	//Je¿eli niema dostêpnej najlepszej dla gracza karty, wróæ.
			{
				break;
			}

			gracz.DodajKarte(najlepszaKarta);
			this -> dostepneKarty[najlepszaKarta] = false;
			gracz.atak += wybranaKarta -> ZwrocWartoscKartySpecjalnej();
			break;
		}
		case RodzajKartySpecjalnej::dobierzKarteOWartosciDwa:
		case RodzajKartySpecjalnej::dobierzKarteOWartosciTrzy:
		case RodzajKartySpecjalnej::dobierzKarteOWartosciCztery:
		case RodzajKartySpecjalnej::dobierzKarteOWartosciPiec:
		case RodzajKartySpecjalnej::dobierzKarteOWartosciSzesc:
		case RodzajKartySpecjalnej::dobierzKarteOWartosciSiedem:
		{
			int16_t wybranaDoDobraniaKarta = wybranaKarta -> ZwrocWartoscKartySpecjalnej();
			if(!this -> dostepneKarty[wybranaDoDobraniaKarta])
			{
				break;
			}
			
			czyUdaloSieUzycKarty = true;
			gracz.DodajKarte(wybranaDoDobraniaKarta);
			this -> dostepneKarty[wybranaDoDobraniaKarta] = false;
			break;
		}
		case RodzajKartySpecjalnej::odrzucOstatniaWylosowanaKarte:
		{
			if(gracz.karty.size() == 1)
			{
				break;
			}

			czyUdaloSieUzycKarty = true;
			int16_t wartoscOstatniejWylosowanejKarty = gracz.karty.back().ZwrocWartosc();
			this -> dostepneKarty[wartoscOstatniejWylosowanejKarty] = true;
			this -> kartyDoDobierania.emplace_back(wartoscOstatniejWylosowanejKarty);
			gracz.sumaWartosciKart -= wartoscOstatniejWylosowanejKarty;
			gracz.karty.pop_back();
			break;
		}
		case RodzajKartySpecjalnej::usunKartySpecjalnePrzeciwnikaZeStolu:
		{
			czyUdaloSieUzycKarty = true;
			if(przeciwnik.polozoneKartySpecjalneNaStole.empty())
			{
				break;
			}

			RodzajKartySpecjalnej rodzajKartySpecjalnejPrzeciwnika;
			for(const KartaSpecjalna & kartaSpecjalnaPrzeciwnika : przeciwnik.polozoneKartySpecjalneNaStole)
			{
				rodzajKartySpecjalnejPrzeciwnika = kartaSpecjalnaPrzeciwnika.ZwrocRodzajKartySpecjalnej();
				if(rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem)
				{
					this -> limitWyniku = 21;
				}
				else if(rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa)
				{
					gracz.atak += kartaSpecjalnaPrzeciwnika.ZwrocWartoscKartySpecjalnej();
				}
				else if(rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zwiekszAtakOJeden
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zwiekszAtakODwa)
				{
					przeciwnik.atak -= kartaSpecjalnaPrzeciwnika.ZwrocWartoscKartySpecjalnej();
				}
			}

			przeciwnik.polozoneKartySpecjalneNaStole.clear();
			break;
		}
		case RodzajKartySpecjalnej::zamienSieOstatniaWylosowanaKartaZGraczem:
		{
			if(gracz.karty.size() == 1 || przeciwnik.karty.size() == 1)
			{
				break;
			}

			czyUdaloSieUzycKarty = true;
			int16_t wartoscOstatniejKartyGracza = gracz.karty.back().ZwrocWartosc();
			int16_t wartoscOstatniejKartyPrzeciwnika = przeciwnik.karty.back().ZwrocWartosc();
			gracz.sumaWartosciKart -= wartoscOstatniejKartyGracza;
			przeciwnik.sumaWartosciKart -= wartoscOstatniejKartyPrzeciwnika;
			gracz.karty.pop_back();
			przeciwnik.karty.pop_back();
			gracz.DodajKarte(wartoscOstatniejKartyPrzeciwnika);
			przeciwnik.DodajKarte(wartoscOstatniejKartyGracza);
			break;
		}
		case RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie:
		case RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery:
		case RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem:
		{
			if(gracz.polozoneKartySpecjalneNaStole.size() == 5)
			{
				break;
			}

			czyUdaloSieUzycKarty = true;
			RodzajKartySpecjalnej rodzajKartySpecjalnejPrzeciwnika;
			std::list <KartaSpecjalna>::iterator poczatek = przeciwnik.polozoneKartySpecjalneNaStole.begin();
			std::list <KartaSpecjalna>::iterator koniec = przeciwnik.polozoneKartySpecjalneNaStole.end();
			std::list <KartaSpecjalna>::iterator jakaKarteSpecjalnaPrzeciwnikaUsunac = koniec;
			for(; poczatek != koniec; ++ poczatek)
			{
				rodzajKartySpecjalnejPrzeciwnika = poczatek -> ZwrocRodzajKartySpecjalnej();
				if(rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem)
				{
					jakaKarteSpecjalnaPrzeciwnikaUsunac = poczatek;
					poczatek = koniec;
					-- poczatek;
				}
			}
			if(jakaKarteSpecjalnaPrzeciwnikaUsunac != koniec)
			{
				przeciwnik.polozoneKartySpecjalneNaStole.erase(jakaKarteSpecjalnaPrzeciwnikaUsunac);
				//Przesuwanie wszystkich po³o¿onych kart przeciwnika na lewo.
				if(!przeciwnik.polozoneKartySpecjalneNaStole.empty())
				{
					sf::Vector2f pozycjaKartySpecjalnej = przeciwnik.karty.front()
					.ZwrocGraficznaReprezentacjeKarty() -> getPosition();
					if(pozycjaKartySpecjalnej.y == 450.f)	//Je¿eli karta specjalna jest gracza
					{
						pozycjaKartySpecjalnej.y = 305.f;
					}
					else
					{
						pozycjaKartySpecjalnej.y = 235.f;
					}
					for(KartaSpecjalna & polozonaKartaSpecjalna : przeciwnik.polozoneKartySpecjalneNaStole)
					{
						polozonaKartaSpecjalna.ZwrocGraficznaReprezentacjeKarty()
						-> setPosition(pozycjaKartySpecjalnej);
						pozycjaKartySpecjalnej.x += 80.f;
					}
				}
			}

			poczatek = gracz.polozoneKartySpecjalneNaStole.begin();
			koniec = gracz.polozoneKartySpecjalneNaStole.end();
			jakaKarteSpecjalnaPrzeciwnikaUsunac = koniec;
			for(; poczatek != koniec; ++ poczatek)
			{
				rodzajKartySpecjalnejPrzeciwnika = poczatek -> ZwrocRodzajKartySpecjalnej();
				if(rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaSiedemnascie
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaCztery
				|| rodzajKartySpecjalnejPrzeciwnika == RodzajKartySpecjalnej::zmienLimitWynikuNaDwadziesciaSiedem)
				{
					jakaKarteSpecjalnaPrzeciwnikaUsunac = poczatek;
					poczatek = koniec;
					-- poczatek;
				}
			}
			if(jakaKarteSpecjalnaPrzeciwnikaUsunac != koniec)
			{
				gracz.polozoneKartySpecjalneNaStole.erase(jakaKarteSpecjalnaPrzeciwnikaUsunac);
			}

			this -> limitWyniku = wybranaKarta -> ZwrocWartoscKartySpecjalnej();
			gracz.PolozKarteSpecjalnaNaStol(wybranaKarta -> ZwrocRodzajKartySpecjalnej());
			break;
		}
		case RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaOJeden:
		case RodzajKartySpecjalnej::zmniejszAtakPrzeciwnikaODwa:
		{
			if(gracz.polozoneKartySpecjalneNaStole.size() == 5)
			{
				break;
			}
			
			czyUdaloSieUzycKarty = true;
			int16_t oIleZmniejszycAtakPrzeciwnika = wybranaKarta -> ZwrocWartoscKartySpecjalnej();
			przeciwnik.atak -= oIleZmniejszycAtakPrzeciwnika;
			gracz.PolozKarteSpecjalnaNaStol(wybranaKarta -> ZwrocRodzajKartySpecjalnej());
			break;
		}
		case RodzajKartySpecjalnej::zwiekszAtakOJeden:
		case RodzajKartySpecjalnej::zwiekszAtakODwa:
		{
			if(gracz.polozoneKartySpecjalneNaStole.size() == 5)
			{
				break;
			}

			czyUdaloSieUzycKarty = true;
			int16_t oIleZwiekszycAtak = wybranaKarta -> ZwrocWartoscKartySpecjalnej();
			gracz.atak += oIleZwiekszycAtak;
			gracz.PolozKarteSpecjalnaNaStol(wybranaKarta -> ZwrocRodzajKartySpecjalnej());
			break;
		}
	}

	if(czyUdaloSieUzycKarty)
	{
		gracz.DokonajRuchu();
		gracz.kartySpecjalne.erase(wybranaKarta);
	}
}

void Rozgrywka::WstepnieWylosujDwieKartyDlaGraczy(Gracz & gracz, Gracz & przeciwnik)
{
	sf::Vector2f pozycjaKarty(70.f, 50.f);
	for(int16_t i = 0; i < 2; ++ i)
	{
		this -> DobierzKarte(gracz);
		this -> DobierzKarte(przeciwnik);
		//Wstêpne ustawienie pocz¹tkowej pozycji kart przeciwnika na ekranie.
		przeciwnik.karty.back().ZwrocGraficznaReprezentacjeKarty() -> setPosition(pozycjaKarty);
		pozycjaKarty.x += 80.f;
	}
}

RodzajKartySpecjalnej Rozgrywka::WylosujKarteSpecjalna()
{
	std::uniform_int_distribution <int16_t> zakresKartSpecjalnych(0, 17);
	return static_cast <RodzajKartySpecjalnej> (zakresKartSpecjalnych(this -> generatorLosowychLiczb));
}

void Rozgrywka::ZresetujLimitWyniku()
{
	this -> limitWyniku = 21;
}