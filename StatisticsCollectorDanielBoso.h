
#ifndef STATISTICSCOLLECTORDANIELBOSO_H
#define STATISTICSCOLLECTORDANIELBOSO_H

#include "StatisticsDanielBoso.h"
#include "CollectorDanielBoso.h"
#include "ModelInfrastructure.h"

class StatisticsCollectorDanielBoso: public ModelInfrastructure, public StatisticsDanielBoso {
public:
	StatisticsCollectorDanielBoso();
	StatisticsCollectorDanielBoso(std::string name);
	StatisticsCollectorDanielBoso(const StatisticsCollectorDanielBoso& orig);
	virtual ~StatisticsCollectorDanielBoso();
public:
	virtual std::string show();
	
protected: 
	virtual void _loadInstance(std::list<std::string> words);
	virtual std::list<std::string>* _saveInstance();
	virtual bool _verifySymbols(std::string* errorMessage);

private:

};

#endif /* STATISTICSCOLLECTORDANIELBOSO_H */

