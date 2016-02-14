#pragma once
#include "ofMain.h"

#include "LowPassFilter.h"

static const double UndefinedTime = -1.0;

class ofxOneEuroFilter
{
public:
	ofxOneEuroFilter( double freq, double mincutoff = 1.0, double beta_ = 0.0, double dcutoff = 1.0 );
	ofxOneEuroFilter();
	~ofxOneEuroFilter();

	void setup( double freq, double mincutoff = 1.0, double beta_ = 0.0, double dcutoff = 1.0 );
	double filter( double value, double timestamp = UndefinedTime );

private:
	double freq;
	double mincutoff;
	double beta_;
	double dcutoff;
	LowPassFilter * x;
	LowPassFilter * dx;
	double lasttime;

	double alpha( double cutoff );
	void setFrequency( double f );
	void setMinCutoff( double mc );
	void setBeta( double b );
	void setDerivateCutoff( double dc );
};

