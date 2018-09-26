
#ifndef STATISTICSDANIELBOSO_H
#define STATISTICSDANIELBOSO_H

#include "Statistics_if.h"
#include "CollectorDatafileDanielBoso.h"

class StatisticsDanielBoso : public Statistics_if {
public:
	StatisticsDanielBoso();
	StatisticsDanielBoso(const StatisticsDanielBoso& orig);
	virtual ~StatisticsDanielBoso();
public:
	CollectorDatafileDanielBoso* getCollector();
	void setCollector(CollectorDatafileDanielBoso* collector);
public:
	unsigned int numElements();
	double min();
	double max();
	double average();
	double mode();
	double mediane();
	double variance();
	double stddeviation();
	double variationCoef();
	double halfWidthConfidenceInterval(double confidencelevel);
	unsigned int newSampleSize(double confidencelevel, double halfWidth);
	double quartil(unsigned short num);
	double decil(unsigned short num);
	double centil(unsigned short num);
	void setHistogramNumClasses(unsigned short num);
	unsigned short histogramNumClasses();
	double histogramClassLowerLimit(unsigned short classNum);
	unsigned int histogramClassFrequency(unsigned short classNum);
private:
	CollectorDatafileDanielBoso* _collector = new CollectorDatafileDanielBoso();
	unsigned short _histogramNumClasses;

};

#endif /* STATISTICSDANIELBOSO_H */

