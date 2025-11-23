#include "Audio.hpp"
#include <chrono>
#include "klasy/Gracz.hpp"
#include "OknoGry.hpp"
#include <thread>

extern void Gra();
extern int8_t Lobby();
extern void Ustawienia();

int main()
{
	OknoGry::okno.setVerticalSyncEnabled(true);
	OknoGry::okno.setActive(false);
	std::jthread odtwarzanieMuzykiWTle([]
	{
		char numerOdtwarzanejPiosenki = '1';
		Audio::muzykaWTle = std::make_unique <sf::Music>();
		Audio::muzykaWTle -> setVolume(50.f);
		if(!Audio::OdtworzUtwor(numerOdtwarzanejPiosenki))
		{
			return;
		}

		while(OknoGry::okno.isOpen())
		{
			if(Audio::muzykaWTle -> getStatus() == sf::SoundSource::Status::Stopped)
			{
				++ numerOdtwarzanejPiosenki;
				if(numerOdtwarzanejPiosenki == '5')
				{
					numerOdtwarzanejPiosenki = '1';
				}
				if(!Audio::OdtworzUtwor(numerOdtwarzanejPiosenki))
				{
					return;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});

	while(OknoGry::okno.isOpen())
	{
		switch(Lobby())
		{
			case 1:
			{
				Gra();
				break;
			}
			case 2:
			{
				Ustawienia();
				break;
			}
			case 3:
			{
				OknoGry::okno.close();
				break;
			}
		}
	}
}