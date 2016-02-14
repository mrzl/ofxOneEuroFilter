#include "ofxOneEuroFilter.h"


ofxOneEuroFilter::ofxOneEuroFilter( double freq, double mincutoff /*= 1.0*/, double beta_ /*= 0.0*/, double dcutoff /*= 1.0 */ )
{
	setup( freq, mincutoff, beta_, dcutoff );
}

ofxOneEuroFilter::ofxOneEuroFilter()
{

}

ofxOneEuroFilter::~ofxOneEuroFilter()
{
	delete x;
	delete dx;
}

void ofxOneEuroFilter::setup( double freq, double mincutoff /*= 1.0*/, double beta_ /*= 0.0*/, double dcutoff /*= 1.0 */ )
{
	setFrequency( freq );
	setMinCutoff( mincutoff );
	setBeta( beta_ );
	setDerivateCutoff( dcutoff );
	x = new LowPassFilter( alpha( mincutoff ) );
	dx = new LowPassFilter( alpha( dcutoff ) );
	lasttime = UndefinedTime;
}

double ofxOneEuroFilter::filter( double value, double timestamp /*= UndefinedTime*/ )
{
	// update the sampling frequency based on timestamps
	if( lasttime != UndefinedTime && timestamp != UndefinedTime )
		freq = 1.0 / ( timestamp - lasttime );
	lasttime = timestamp;
	// estimate the current variation per second 
	double dvalue = x->hasLastRawValue() ? ( value - x->lastRawValue() )*freq : 0.0; // FIXME: 0.0 or value?
	double edvalue = dx->filterWithAlpha( dvalue, alpha( dcutoff ) );
	// use it to update the cutoff frequency
	double cutoff = mincutoff + beta_*fabs( edvalue );
	// filter the given value
	return x->filterWithAlpha( value, alpha( cutoff ) );
}

double ofxOneEuroFilter::alpha( double cutoff )
{
	double te = 1.0 / freq;
	double tau = 1.0 / ( 2 * PI * cutoff );
	return 1.0 / ( 1.0 + tau / te );
}

void ofxOneEuroFilter::setFrequency( double f )
{
	if( f <= 0 ) throw std::range_error( "freq should be >0" );
	freq = f;
}

void ofxOneEuroFilter::setMinCutoff( double mc )
{
	if( mc <= 0 ) throw std::range_error( "mincutoff should be >0" );
	mincutoff = mc;
}

void ofxOneEuroFilter::setBeta( double b )
{
	beta_ = b;
}

void ofxOneEuroFilter::setDerivateCutoff( double dc )
{
	if( dc <= 0 ) throw std::range_error( "dcutoff should be >0" );
	dcutoff = dc;
}
