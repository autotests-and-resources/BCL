#ifndef TRANSFORM_COORDS_H
#define TRANSFORM_COORDS_H

//#include <math.h>
# define M_PI		3.141592653589793238462643383279502884L /* pi */

class TransformCoords
{
public:
	struct Degrees
	{
		int degrees = 0;
		int minutes = 0;
		double seconds = 0.;
	};

	static double degreesToRadians(Degrees degrees) {
		return degreesToRadians(degrees.degrees, degrees.minutes, degrees.seconds);
	}

	static double degreesToRadians(int degrees, int minites, double seconds)
	{
		double rad = (degrees + (minites + seconds / 60) / 60) * M_PI / 180;
		return rad;
	}

	static Degrees decimalDegreesAsStruct(double decimal_degrees)
	{
		Degrees degrees;
		degrees.degrees = int(decimal_degrees);
		double minutes = 60 * (decimal_degrees - degrees.degrees);
		degrees.minutes = int(minutes);
		degrees.seconds = 60 * (minutes - degrees.minutes);
		return degrees;
	}

	static double decimalDegreesToRadians(double decimal_degrees) {
		return decimal_degrees * M_PI / 180;
	}

	static Degrees radiansToDegrees(double radians)
	{
		double decimal_degrees = radiansToDecimalDegrees(radians);
		Degrees degrees = decimalDegreesAsStruct(decimal_degrees);
		return degrees;
	}

	static double radiansToDecimalDegrees(double radians) {
		return radians * 180 / M_PI;
	}
};

#endif // TRANSFORM_COORDS_H
