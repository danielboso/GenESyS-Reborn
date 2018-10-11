
#ifndef COLLECTORDATAFILEDANIELBOSO_H
#define COLLECTORDATAFILEDANIELBOSO_H

#include <string>
#include <fstream>

#include "CollectorDatafile_if.h"

class CollectorDatafileDanielBoso : public CollectorDatafile_if {
public:
	CollectorDatafileDanielBoso();
	CollectorDatafileDanielBoso(const CollectorDatafileDanielBoso& orig);
	~CollectorDatafileDanielBoso();
public:
	void clear();
	void addValue(double value);
	double getLastValue();
	unsigned long numElements();
public:
	double getValue(unsigned int num) override;
	std::string getDataFilename() override ;
	void setDataFilename(std::string filename) override;

private:
	std::string 	_filename = "";
	double          _lastValue;
	unsigned int    _numElements;
};

#endif /* COLLECTORDATAFILEDANIELBOSO_H */
