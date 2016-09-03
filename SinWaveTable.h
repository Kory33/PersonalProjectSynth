#pragma once

class SinWaveTable{
private:
	const int TOTAL_SAMPLES;
	double* table;

	double inline normalizeToQuarterPeriod(double t) const;
	double normalizeToTable(double t) const;
	double getPrevSampleValue(int i) const;
	double getNextSampleValue(int i) const;
	int getCosIndex(int t) const;
	static double calculateSinMaclaurin(double x);
	static double calculateCosMaclaurin(double x);
public:
	explicit SinWaveTable(unsigned tableSize);
	double inline getLinearInterpolation(double t) const;
	double inline getLimitedLinearInterpolation(double t) const;
	double inline getDirectLinearInterpolation(double t) const;
	double inline getAdditionInterpolation(double t) const;
	double inline getLimitedAdditionInterpolation(double t) const;
	double inline getDirectAdditionInterpolation(double t) const;
	~SinWaveTable();
};

