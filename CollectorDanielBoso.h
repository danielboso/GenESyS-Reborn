
#ifndef COLLECTORDANIELBOSO_H
#define COLLECTORDANIELBOSO_H

#include <string>
#include "Collector_if.h"

class CollectorDanielBoso : public Collector_if {
public:
	CollectorDanielBoso();
	CollectorDanielBoso(const CollectorDanielBoso& orig);
	~CollectorDanielBoso();
public:
	void clear();
	void addValue(double value);
	double getLastValue();
	unsigned int numElements();

private:
	double _lastValue;
	unsigned int _numElements = 0;
};

#endif /* COLLECTORDANIELBOSO_H */

