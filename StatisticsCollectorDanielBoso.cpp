
#include "StatisticsCollectorDanielBoso.h"
#include "fstream";

std::list<std::string>* _words;

StatisticsCollectorDanielBoso::StatisticsCollectorDanielBoso() : ModelInfrastructure(typeid (this).name()) {}

StatisticsCollectorDanielBoso::StatisticsCollectorDanielBoso(std::string name) : ModelInfrastructure(typeid (this).name()) {
	_name = name;
}

StatisticsCollectorDanielBoso::StatisticsCollectorDanielBoso(const StatisticsCollectorDanielBoso& orig) : ModelInfrastructure(orig) {}

StatisticsCollectorDanielBoso::~StatisticsCollectorDanielBoso() {}

std::string StatisticsCollectorDanielBoso::show() {
	return ModelInfrastructure::show();
}

void StatisticsCollectorDanielBoso::_loadInstance(std::list<std::string> words) {
    _words = &words;
}

std::list<std::string>* StatisticsCollectorDanielBoso::_saveInstance() {
	std::list<std::string>* words = new std::list<std::string>();
	return words;
}

bool StatisticsCollectorDanielBoso::_verifySymbols(std::string* errorMessage) {}