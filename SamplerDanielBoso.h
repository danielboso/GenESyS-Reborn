#ifndef SAMPLERMYIMPL1_H
#define SAMPLERMYIMPL1_H

#include "Sampler_if.h"

class SamplerDanielBoso : public Sampler_if {
public:

	class MyRNG_Parameters : public RNG_Parameters {
	public:
		unsigned int seed;
		unsigned int module;
		unsigned int multiplier;
	};
public:
	SamplerDanielBoso();
	SamplerDanielBoso(const SamplerDanielBoso& orig);
	~SamplerDanielBoso();
public: // probability distributions
	double random();
	double sampleUniform(double min, double max);
	double sampleExponential(double mean);
	double sampleErlang(double mean, int M);
	double sampleNormal(double mean, double stddev);
	double sampleGamma(double mean, double alpha);
	double sampleBeta(double alpha, double beta, double infLimit, double supLimit);
	double sampleWeibull(double alpha, double scale);
	double sampleLogNormal(double mean, double stddev);
	double sampleTriangular(double min, double mode, double max);
	double sampleDiscrete(int count, ...);
public:
	void setRNGparameters(RNG_Parameters* param);
	RNG_Parameters* getRNGparameters() const;
private:
	MyRNG_Parameters* _param = new MyRNG_Parameters();
};

#endif /* SAMPLERMYIMPL1_H */
