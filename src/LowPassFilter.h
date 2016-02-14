#pragma once

#include <stdexcept>

class LowPassFilter
{
public:
	LowPassFilter( double alpha, double initval = 0.0 );
	~LowPassFilter();

	void setAlpha( double alpha );
	double filter( double value );
	double filterWithAlpha( double value, double alpha );
	bool hasLastRawValue( void );
	double lastRawValue( void );

private:
	double y, a, s;
	bool isInitialized;
};

