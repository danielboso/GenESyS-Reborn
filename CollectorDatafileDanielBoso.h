
#ifndef COLLECTORDATAFILEDANIELBOSO_H
#define COLLECTORDATAFILEDANIELBOSO_H

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
	unsigned int numElements();
public:
	double getValue(unsigned int num);
	std::string getDataFilename();
	void setDataFilename(std::string filename);

private:

};

#endif /* COLLECTORDATAFILEDANIELBOSO_H */

