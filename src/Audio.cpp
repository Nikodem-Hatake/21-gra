#include "Audio.hpp"
#include <string>

__forceinline bool Audio::OdtworzUtwor(char & numerOdtwarzanejPiosenki)
{
	std::string sciezkaDoUtworu = "resources/muzyka w tle/";
	sciezkaDoUtworu.push_back(numerOdtwarzanejPiosenki);
	sciezkaDoUtworu.append(".mp3");
	if(!muzykaWTle -> openFromFile(sciezkaDoUtworu))
	{
		muzykaWTle = nullptr;
		return false;
	}

	muzykaWTle -> play();
	return true;
}