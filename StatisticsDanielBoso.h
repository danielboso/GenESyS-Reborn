
#ifndef STATISTICSDANIELBOSO_H
#define STATISTICSDANIELBOSO_H

#include "Statistics_if.h"
#include "CollectorDanielBoso.h"
//#include "Collector_if.h"
//#include "Traits.h"

class StatisticsDanielBoso : public Statistics_if {
public:
	StatisticsDanielBoso();
	StatisticsDanielBoso(const StatisticsDanielBoso& orig);
	virtual ~StatisticsDanielBoso();
public:
	Collector_if* getCollector();
	void setCollector(Collector_if* collector);
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
	Collector_if* _collector = new CollectorDanielBoso();
	/* TODO:  WTF? Why the next lines do not compile? */
	//Collector_if* _collector = new Traits<ModelComponent>::CollectorImplementation();
	//Collector_if* _collector = new Traits<Collector_if>::ModelImplementation();

};

#endif /* STATISTICSDANIELBOSO_H */
