#include "SinWaveTable.h"
#define _USE_MATH_DEFINES
#include <cmath>

// Constructor
// tableSize should be power of 2
SinWaveTable::SinWaveTable(unsigned tableSize = 2048) : TOTAL_SAMPLES(tableSize){
	// contains half a period with a zero added at the last
	this->table = new double[TOTAL_SAMPLES];

	// prepare the content of table
	double halfPeriod = M_PI;
	for(int i = 0; i < TOTAL_SAMPLES; i++){
		this->table[i] = sin(halfPeriod * double(i) / double(TOTAL_SAMPLES));
	}
}

// Destructor
SinWaveTable::~SinWaveTable(){
	delete[] this->table;
}

/**
 * Public methods
*/

// Returns sin(t) using linear interpolation
double inline SinWaveTable::getLinearInterpolation(double t) const{
	return this->getLimitedLinearInterpolation(this->normalizeToQuarterPeriod(t));
}

// Returns sin(t) for 0 <= t < PI, using linear interpolation
// Do not use this function outside the range
double inline SinWaveTable::getLimitedLinearInterpolation(double t) const{
	return this->getDirectLinearInterpolation(t * this->TOTAL_SAMPLES / M_PI);
}

// Returns sin(td) where 0 <= td = t * SAMPLE / PI < SAMPLE, using linear interpolation
// This method may be used only if the SAMPLE number is known and phase is handled
double inline SinWaveTable::getDirectLinearInterpolation(double t) const{
	// sample that is largest and nearest to t
	int nearestMaxSampleNum = int(t);
	double lastSampleValue = this->table[nearestMaxSampleNum];
	double nextSampleValue = this->getNextSampleValue(nearestMaxSampleNum);

	// difference in the phase between of t and floor(t)
	double deltaPhase = t - nearestMaxSampleNum;

	//linear interpolation
	return lastSampleValue + deltaPhase * (nextSampleValue - lastSampleValue);
}

// Returns sin(t) using addition theorem interpolation
double inline SinWaveTable::getAdditionInterpolation(double t) const{
	return this->getLimitedAdditionInterpolation(this->normalizeToQuarterPeriod(t));
}

// Returns sin(t) for 0 <= t < PI, using addition theorem interpolation
// Do not use this function outside the range
double inline SinWaveTable::getLimitedAdditionInterpolation(double t) const{
	return this->getDirectAdditionInterpolation(t * this->TOTAL_SAMPLES / M_PI);
}

// Returns sin(td) where 0 <= td = t * SAMPLE / PI < SAMPLE, using addition theorem interpolation
// This method may be used only if the SAMPLE number is known and phase is handled
double inline SinWaveTable::getDirectAdditionInterpolation(double t) const{
	// sample that is largest and nearest to t
	int nearestMaxSampleNum = int(t);

	// difference in the phase between of t and floor(t)
	double deltaPhase = t - nearestMaxSampleNum;

	// use sin(a + b) = sin(a)cos(b) + cos(a)sin(b)
	return this->table[nearestMaxSampleNum] * calculateCosMaclaurin(deltaPhase) +
		   this->table[this->getCosIndex(nearestMaxSampleNum)] * calculateSinMaclaurin(deltaPhase);
}

/**
* Private methods
*/

// Restricts and converts the time into [0, PI)
double inline SinWaveTable::normalizeToQuarterPeriod(double t) const{
	// restrict or convert the range
	if(t < 0){
		return -this->getLinearInterpolation(-t);
	}

	if(t >= 2 * M_PI){
		return this->getLinearInterpolation(t - M_PI * int(t / M_PI));
	}

	if(t > M_PI){
		return -this->getLinearInterpolation(t - M_PI);
	}

	return t;
}

// Normalize [0, PI) to [0, Samples)
double inline SinWaveTable::normalizeToTable(double t) const{
	return t * this->TOTAL_SAMPLES / M_PI;
}

// gets sin[(i - 1) * PI / Samples]
double inline SinWaveTable::getPrevSampleValue(int i) const{
	if(i){
		return this->table[i - 1];
	}
	return -this->table[1];
}

// gets sin[(i + 1) * PI / Samples]
double inline SinWaveTable::getNextSampleValue(int i) const{
	if(this->TOTAL_SAMPLES - i){
		return this->table[i + 1];
	}
	return 0;
}

// give int u such that cosTable[t] = sinTable[u]
int inline SinWaveTable::getCosIndex(int t) const{
	int index = t + (this->TOTAL_SAMPLES >> 2);
	if(index >= this->TOTAL_SAMPLES) {
		index -= this->TOTAL_SAMPLES;
	}
	return index;
}

/**
* Static methods
*/

// return Maclaurin expansion of sin(x) for small x
double inline SinWaveTable::calculateSinMaclaurin(double x) {
	double x2 = x * x;
	double x3 = x2* x;
	double x5 = x3*x2;
	double x7 = x5*x2;

	return x - x3 / 6. + x5 / 120. + x7 / 5040;
}

// return Maclaurin expansion of cos(x) for small x
double inline SinWaveTable::calculateCosMaclaurin(double x) {
	double x2 = x * x;
	double x4 = x2*x2;
	double x6 = x4*x2;

	return 1 - x2 / 2. + x4 / 24. + x6 / 720.;
}

