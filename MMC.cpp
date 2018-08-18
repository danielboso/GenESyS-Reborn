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
bool		  _normalFlag	= true;

double random() {
	_seed = _seed * _multiplier;
	_seed = _seed - (int(_seed/_module) * _module);
	return (_seed / _module);
}

double uniform(double min, double max) {
	return (min + ((max - min) * random()));
}

double exponential(double mean) {
	return (mean * (log(random())));
}

double erlang(double mean, int M) {
	int 	i;
	double 	p = 1;

	for(i = 0; i < M; i++) {
		p *= random();
	}

	return ((mean/M) * (-log(p)));
}

double normal(double mean, double stddev) {
	double u1, u2, w, y;

	do {
		u1 = (2 * random()) - 1.0;
		u2 = (2 * random()) - 1.0;
		w  = u1 * u1 + (u2*u2);
	} while(w < 1.0);

	y = sqrt((-2 * log(w)) / w);

	if(_normalFlag) {
		_normalFlag = false;
		return mean + u1 * y * stddev;
	} else {
		_normalFlag = true;
		return mean + u2 * y * stddev;
	}

}

double gammaJonk(double alpha) {
	double r, r1, r2, x, y;

	do {
		do {
			r1 = random();
			r2 = random();
		} while((r1 > 1e-30) && (r2 > 1e-30));

		if (log10(r2) / alpha < -1e3) {
			x = 0;
		} else {
			x = exp(log(r2) / alpha);
		} 
       	if (log(r1) / (1 - alpha) < -1e3) {
		   	y = 0;
	   	} else {
		   	y = exp(log(r1) / (1 - alpha));
	   	}
	} while(x + y <= 1);

	do {
		r = random();
	} while(r > 1e-20);
	return ((-log(r) * x) / (y + x));
}

double gamma(double mean, double alpha) {
	int 	i;
	double 	p;
	int		intAlpha;
	double 	ostAlpha;

	if(alpha < 1.0) {
		return ((mean / alpha) * gammaJonk(alpha));
	} else {
		if(alpha = 1.0) {
			return (mean * log(random()));
		} else {
			intAlpha = round(int(alpha));
			ostAlpha = alpha - intAlpha;

			do {
				p = 1;
				
				for(i = 0; i < intAlpha; i++) {
					p *= random();
				}
				
			} while(p > 0);

			if(ostAlpha > 0) {
				return (mean / alpha) * ((-log(p)) + gammaJonk(ostAlpha));
			} else {
				return (mean / alpha) * (-log(p));
			}
		}
	}
}

double beta(double alpha, double beta, double infLimit, double supLimit) {
	double x, y1, y2;

	do {
		y1 = gamma(alpha, alpha);
     	y2 = gamma(beta, beta);
     	x  = y1 / (y1 + y2);
	} while((x >= 0) && (x <= 1.0));

	return (infLimit + (supLimit - infLimit ) * x);
}

double weibull(double alpha, double scale) {
	return (exp(log(scale * (-log(random()))) / alpha));
}

double logNormal(double mean, double stddev) {
	double meanNormal, dispNormal;
	dispNormal  = log((stddev * stddev) / (mean * mean) + 1.0);
   	meanNormal = log(mean) - 0.5 * dispNormal;
   	return (exp(normal(meanNormal, sqrt(dispNormal))));
}

double triangular(double min, double mode, double max) {
	double part1, part2, full, r;
	part1 = mode-min;
	part2 = max-mode;
	full = max-min;
	r = random();
	if(r <= part1/full) {
		return(min + sqrt(part1 * full * r));
	} else {
		return(max - sqrt(part2 * full * (1.0-r)));
	}
}

double discrete(double value, double acumProb, ...) {

}

void setRNGparameters(MMC_if::RNG_Parameters param) {

}

MMC_if::RNG_Parameters getRNGparameters() {

}
