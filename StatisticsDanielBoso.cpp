
#include "StatisticsDanielBoso.h"

StatisticsDanielBoso::StatisticsDanielBoso() {}

StatisticsDanielBoso::StatisticsDanielBoso(const StatisticsDanielBoso& orig) {}

StatisticsDanielBoso::~StatisticsDanielBoso() {}

unsigned int StatisticsDanielBoso::numElements() {
    _collector->numElements();
}

double StatisticsDanielBoso::min() {}

double StatisticsDanielBoso::max() {}

double StatisticsDanielBoso::average() {}

double StatisticsDanielBoso::mode() {}

double StatisticsDanielBoso::mediane() {}

double StatisticsDanielBoso::variance() {}

double StatisticsDanielBoso::stddeviation() {}

double StatisticsDanielBoso::variationCoef() {}

double StatisticsDanielBoso::halfWidthConfidenceInterval(double confidencelevel) {}

unsigned int StatisticsDanielBoso::newSampleSize(double confidencelevel, double halfWidth) {}

double StatisticsDanielBoso::quartil(unsigned short num) {}

double StatisticsDanielBoso::decil(unsigned short num) {}

double StatisticsDanielBoso::centil(unsigned short num) {}

void StatisticsDanielBoso::setHistogramNumClasses(unsigned short num) {}

unsigned short StatisticsDanielBoso::histogramNumClasses() {}

double StatisticsDanielBoso::histogramClassLowerLimit(unsigned short classNum) {}

unsigned int StatisticsDanielBoso::histogramClassFrequency(unsigned short classNum) {}

Collector_if* StatisticsDanielBoso::getCollector() {
	return this->_collector;
}

void StatisticsDanielBoso::setCollector(Collector_if* collector) {
    _collector = collector;
}