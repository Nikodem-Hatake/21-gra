#ifndef GraficznaReprezentacjaKarty_hpp
#define GraficznaReprezentacjaKarty_hpp

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class GraficznaReprezentacjaKarty
{
	protected:
	sf::RectangleShape graficznaReprezentacjaKarty;
	sf::Texture grafikaKarty;

	public:
	GraficznaReprezentacjaKarty() = default;
	~GraficznaReprezentacjaKarty() = default;
	sf::RectangleShape * ZwrocGraficznaReprezentacjeKarty();
};

#endif