#ifndef Karta_hpp
#define Karta_hpp

#include <cstdint>
#include "GraficznaReprezentacjaKarty.hpp"

class Karta : public GraficznaReprezentacjaKarty
{
	private:
	int16_t wartosc;

	public:
	Karta(int16_t & wartosc);
	~Karta() = default;
	int16_t ZwrocWartosc() const;
};

#endif