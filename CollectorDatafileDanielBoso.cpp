
#include "CollectorDatafileDanielBoso.h"

CollectorDatafileDanielBoso::CollectorDatafileDanielBoso() { }

CollectorDatafileDanielBoso::CollectorDatafileDanielBoso(const CollectorDatafileDanielBoso& orig) { }

CollectorDatafileDanielBoso::~CollectorDatafileDanielBoso() { }

void CollectorDatafileDanielBoso::clear() {
    std::ofstream ofstream;
    ofstream.open(_filename);
    ofstream.clear();
    _numElements = 0;
}

void CollectorDatafileDanielBoso::addValue(double value) {
    std::ofstream ofstream;
	ofstream.open(_filename);
	ofstream << value << std::endl;
	//ofstream.close;

    _lastValue = value;
    _numElements++;
}

double CollectorDatafileDanielBoso::getLastValue() {
    return _lastValue;
}

unsigned long CollectorDatafileDanielBoso::numElements() {
    return _numElements;
}

double CollectorDatafileDanielBoso::getValue(unsigned int num) {
    std::ifstream ifstream;
    int i = 0;
    std::string value;
	while(std::getline(ifstream, value)) {
        i++;

        if(i == num) {
            return std::stod(value);
        }
    }
}

std::string CollectorDatafileDanielBoso::getDataFilename() {
    return _filename;
}

void CollectorDatafileDanielBoso::setDataFilename(std::string filename) {
    _filename = filename;
}
