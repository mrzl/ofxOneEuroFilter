#include "LowPassFilter.h"

LowPassFilter::LowPassFilter( double alpha, double initval )
{
	y = s = initval;
	setAlpha( alpha );
	isInitialized = false;
}


LowPassFilter::~LowPassFilter()
{
}

void LowPassFilter::setAlpha( double alpha ) {
	if( alpha <= 0.0 || alpha > 1.0 ) {
		throw std::range_error( "alpha should be in (0.0., 1.0]" );
	}
	a = alpha;
}

double LowPassFilter::filter( double value )
{
	double result;
	if( isInitialized )
		result = a * value + ( 1.0 - a ) * s;
	else {
		result = value;
		isInitialized = true;
	}
	y = value;
	s = result;
	return result;
}

double LowPassFilter::filterWithAlpha( double value, double alpha )
{
	setAlpha( alpha );
	return filter( value );
}

bool LowPassFilter::hasLastRawValue( void )
{
	return isInitialized;
}

double LowPassFilter::lastRawValue( void )
{
	return y;
}
