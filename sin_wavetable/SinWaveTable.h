#pragma once

#define PREC_SIN_TAYLOR_EXPANSION_ORDER 30
class SinWaveTable{
private:
	const int TOTAL_SAMPLES;
	double* table;
	double shrinkDomainCoeff;
	double expandDomainCoeff;
	double normalizeToTable(double t) const;
	double getPrevSampleValue(int i) const;
	double getNextSampleValue(int i) const;

	static double normalizeToQuarterPeriod(double t, bool* isSignFliped);
	static double preciseSin(double t);
public:
	explicit SinWaveTable(unsigned int tablesize);
	double getQuadraticInterpolation(double t) const;
	double getLimitedQuadraticInterpolation(double t) const;
	double getDirectQuadraticInterpolation(double t) const;
	~SinWaveTable();
};

