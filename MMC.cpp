/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MMC.cpp
 * Author: cancian
 * 
 * Created on 7 de Agosto de 2018, 18:22
 */

#include "MMC_if.h"
#include <cmath>

unsigned long _seed 		= 1000000000;
unsigned long _multiplier 	=  950706376;
unsigned long _module 		= 2147483647;

double MMC_if::random() {
	_seed = _seed * _multiplier;
	_seed = _seed - (int(_seed/_module) * _module);
	return (_seed / _module);
}
virtual double uniform(double min, double max) = 0;
virtual double exponential(double mean) = 0;
virtual double erlang(double mean, int M) = 0;
virtual double normal(double mean, double stddev) = 0;
virtual double gamma(double mean, double alpha) = 0;
virtual double beta(double alpha, double beta, double infLimit, double supLimit) = 0;
virtual double weibull(double alpha, double scale) = 0;
virtual double logNormal(double mean, double stddev) = 0;
virtual double triangular(double min, double mode, double max) = 0;
virtual double discrete(double value, double acumProb, ...) = 0;
virtual void setRNGparameters(RNG_Parameters param) = 0;
virtual RNG_Parameters getRNGparameters() const = 0;

double MMC_if::random() {
	_seed = _seed * _multiplier;
	_seed = _seed - int(_seed/_module) * _module;
	return (_seed / _module);
}

double MMC::uniform(double min, double max) {
	return (min + (max - min) * random());
}

double MMC::exponential(double mean) {
	return (mean * (-std::log10(random())));
}

double MMC::erlang(double mean, int M) {
	int 	i;
	double 	p;

	for(i = 0; i < M; i++) {
		p = p * random();
	}

	return ((mean/M) * (-std::log10(p)));
}

double MMC::normal(double mean, double stddev) {
	double u1, u2, w, y;

	do {
		u1 = 2 * random() - 1.0;
		u2 = 2 * random() - 1.0;
		w  = u1 * u1 + (u2*u2);
	} while(w < 1.0);

	y = sqrt((-2* std::log10(w)) / w);

	if(normalFlag) {
		normalFlag = false;
		return mean + u1*y*stddev;
	} else {
		normalFlag = true;
		return mean + u2*y*stddev;
	}
}

double gammaJonk(double alpha) {
	double r, r1, r2, x, y;

	do {
		do {
			r1 = MMC::MMC().random();
			r2 = MMC::MMC().random();
		} while((r1 > 1e-30) && (r2 > 1e-30));

		if (log10(r2) / alpha < -1e3) {
			x = 0;
		} else {
			x = exp(log10(r2) / alpha);
		} 
       	if (log10(r1)/(1-alpha)<-1e3) {
		   	y = 0;
	   	} else {
		   	y = exp(log10(r1) / (1-alpha));
	   	}
	} while(x + y <= 1);

	do {
		r = MMC::MMC().random();
	} while(r > 1e-20);
	return (-log10(r)*x/(y+x));
}

double MMC::gamma(double mean, double alpha) {
	int 	i;
	double 	p;
	int		intAlpha;
	double	ostAlpha;

	if(alpha < 1.0) {
		return (mean*(-log10(random())));
	} else {
		intAlpha = round(int(alpha));
		ostAlpha = alpha - intAlpha;
		
		do {
			p = 1;

			for(i = 0; i < intAlpha; i++) {
				p = p * random();
			}	
			
		} while(p > 0);

		if(ostAlpha > 0) {
			return ((mean/alpha)*((-log10(p)) + gammaJonk(ostAlpha)));
		} else {
			return ((mean/alpha) * (-log10(p)));
		}
	}
}

double MMC::beta(double alpha, double beta) {

}

double MMC::weibull(double alpha, double scale) {
	return (exp(log10(scale*(-log10(random())))/alpha));
}

double MMC::logNormal(double mean, double stddev) {
	double meanNormal, dispNormal;
	dispNormal  = log10((stddev*stddev) / (mean*mean)+1.0);
   	meanNormal = log10(mean)- 0.5*dispNormal;
   	return (exp(normal(meanNormal, sqrt(dispNormal))));
}

double MMC::triangular(double min, double mode, double max) {
	double part1, part2, full, r;
	part1 = mode-min;
	part2 = max-mode;
	full = max-min;
	r = random();
	if(r <= part1/full) {
		return(min+sqrt(part1*full*r));
	} else {
		return(max-sqrt(part2*full*(1.0-r)));
	}
}