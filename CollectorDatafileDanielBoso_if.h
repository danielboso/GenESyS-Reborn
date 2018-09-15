#ifndef COLLECTORDATAFILEDANIELBOSO_H
#define COLLECTORDATAFILEDANIELBOSO_H

#include "CollectorDanielBoso_if.h"

class CollectorDataFileDanielBoso : public CollectorDatafile_if {
public:
	CollectorDataFileDanielBoso();
	CollectorDataFileDanielBoso(const CollectorDataFileDanielBoso& orig);
	~CollectorDataFileDanielBoso();
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

