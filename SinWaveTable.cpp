#include "SinWaveTable.h"

#define _USE_MATH_DEFINES
#include <cmath>


// Constructor
SinWaveTable::SinWaveTable(unsigned int tableSize = 1024) : TOTAL_SAMPLES(tableSize){
	// contains half a period with a zero added at the last
	this->table = new double[TOTAL_SAMPLES];

	this->shrinkDomainCoeff = .5 * M_PI / this->TOTAL_SAMPLES;
	this->expandDomainCoeff = 2. * this->TOTAL_SAMPLES / M_PI;

	// prepare the content of table
	double quadPeriod = 0.5 * M_PI;
	for(int i = 0; i < TOTAL_SAMPLES; i++){
		this->table[i] = preciseSin(quadPeriod * double(i) / double(TOTAL_SAMPLES));
	}
}

// Destructor
SinWaveTable::~SinWaveTable(){
	delete[] this->table;
}

/**
 * Public methods
 */

// Returns sin(t) using quadratic interpolation
double SinWaveTable::getQuadraticInterpolation(double t) const{
	bool isSignFlipped = false;
	double td = this->normalizeToQuarterPeriod(t, &isSignFlipped);
	if(isSignFlipped){
		return -this->getLimitedQuadraticInterpolation(td);
	}
	return this->getLimitedQuadraticInterpolation(td);
}

// Returns sin(t) for 0 <= t < PI/2, using quadratic interpolation
// Do not use this function outside the range
double SinWaveTable::getLimitedQuadraticInterpolation(double t) const{
	return this->getDirectQuadraticInterpolation(t * this->expandDomainCoeff);
}

// Returns sin(tc) where 0 <= t = tc * SAMPLE / PI < SAMPLE, using quadratic interpolation
// This method may be used only if the SAMPLE number is known and phase is handled
double SinWaveTable::getDirectQuadraticInterpolation(double t) const{
	// sample that is largest and nearest to t
	int nearestMaxSampleNum = int(t);

	// difference in the phase between of t and floor(t)
	double deltaPhase = t - nearestMaxSampleNum;

	double last = this->table[nearestMaxSampleNum];
	double next = this->getNextSampleValue(nearestMaxSampleNum);
	double prev = this->getPrevSampleValue(nearestMaxSampleNum);

	// use quadratic interpolation
	return 0.5 * deltaPhase * ((deltaPhase + 1.) * next + (deltaPhase - 1.) * prev - 2. * deltaPhase * last) + last;
}

/**
 * Private methods
 */

// Restricts and converts the time into [0, PI / 2)
// Stores true for the second pointer's content if the resultant sign should be flipped
double SinWaveTable::normalizeToQuarterPeriod(double t, bool* isSignFliped){
	// filp the sign of t and sin if t < 0
	// i.e. sin(-t) = -sin(t)
	if(t < 0){
		*isSignFliped ^= 1;
		return normalizeToQuarterPeriod(-t, isSignFliped);
	}

	// if t is greater than the table's range
	if(t > 0.5 * M_PI) {
		// if t is outside half a period
		if(t > M_PI){
			// if t is outside a period
			if(t >= 2 * M_PI){
				return normalizeToQuarterPeriod(t - 2 * M_PI * int(t / (2 * M_PI)), isSignFliped);
			}

			// sin(a) = -sin(a - pi)
			*isSignFliped ^= 1;
			return normalizeToQuarterPeriod(t - M_PI, isSignFliped);
		}
		// sin(t) = sin(pi - t)
		return normalizeToQuarterPeriod(M_PI - t, isSignFliped);
	}

	// if t is in [0, pi/4), return as it is
	return t;
}

// Normalize [0, PI) to [0, Samples)
double SinWaveTable::normalizeToTable(double t) const{
	return t * this->TOTAL_SAMPLES / M_PI;
}

// gets previous sample's value
double SinWaveTable::getPrevSampleValue(int i) const{
	if(i){
		return this->table[i - 1];
	}
	// as -sin(t) = sin(t)
	return -this->table[1];
}

// gets next sample's value
double SinWaveTable::getNextSampleValue(int i) const{
	if(this->TOTAL_SAMPLES - i){
		return this->table[i + 1];
	}
	// as next element after the end of the table is
	// sin(pi / 2) == 1.
	return 1.;
}

// calculate precise sin(t) with Maclaurin expansion
double SinWaveTable::preciseSin(double t){
	bool negSign = false;
	double normalizedT = normalizeToQuarterPeriod(t, &negSign);
	double tSquare = normalizedT * normalizedT;

	double result = 0;
	double tPower = normalizedT;
	double factorial = 1;

	// compute Maclaurin expansion
	for(int i = 1; i <= PREC_SIN_TAYLOR_EXPANSION_ORDER; i++){
		result += tPower / factorial;
		tPower *= - tSquare;
		factorial *= (i << 1) * ((i << 1) + 1);
	}

	return negSign? -result : result;
}
