#ifndef Audio_hpp
#define Audio_hpp

#include <memory>
#include <SFML/Audio/Music.hpp>

namespace Audio
{
	constinit inline std::unique_ptr <sf::Music> muzykaWTle = nullptr;
	extern __forceinline bool OdtworzUtwor(char & numerOdtwarzanejPiosenki);
}

#endif