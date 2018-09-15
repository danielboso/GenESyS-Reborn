

#include "CollectorDanielBoso_if.h"

CollectorDanielBoso::CollectorDanielBoso() {}

CollectorDanielBoso::CollectorDanielBoso(const CollectorDanielBoso& orig) {}

CollectorDanielBoso::~CollectorDanielBoso() {}

void CollectorDanielBoso::clear() {
	_numElements = 0;
}

void CollectorDanielBoso::addValue(double value) {
	_lastValue = value;
	_numElements++;
}

double CollectorDanielBoso::getLastValue() {
	return this->_lastValue;
}

unsigned int CollectorDanielBoso::numElements() {
	return this->_numElements;
}