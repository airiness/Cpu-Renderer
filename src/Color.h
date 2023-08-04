#pragma once
#include <cstdint>

class Color
{
public:
	Color(uint32_t data) : mData(data) {}
	~Color() = default;

	const uint32_t Data() const { return mData; };

	static Color White() { return 0xffffffffu; }
	static Color Black() { return 0xff000000u; }
	static Color Red() { return 0xffff0000u; }
	static Color Green() { return 0xff00ff00u; }
	static Color Blue() { return 0xff0000ffu; }
	static Color Yellow() { return 0xffffff00u; }
	static Color Cyan() { return 0xff00ffffu; }
	static Color Gray() { return 0xffddddddu; }
	static Color Pink() { return 0xffffc0cbu; }
	static Color DeepSkyBlue() { return 0xff00bfffu; }
	static Color Orange() { return 0xffffa500u; }
	static Color Gold() { return 0xffffd700u; }
	static Color Purple() { return 0xff800080u; }
	static Color Olive() { return 0xff808000u; }
private:
	uint32_t mData;
};