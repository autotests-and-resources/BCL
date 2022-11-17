#ifndef COORD_H
#define COORD_H

struct Coord
{
	double Lat = 0.;
	double Long = 0.;
	double H = 0.;
};

//!форматы для отображения координат
enum CoordFormat
{
	DEGREES,
	RADIANS,
	DECIMAL
};

#endif // COORD_H
