
#include <math.h>
#include <list>;

#include "StatisticsDanielBoso.h"
#include "CollectorDanielBoso.h"
#include "fstream"

StatisticsDanielBoso::StatisticsDanielBoso() {}

StatisticsDanielBoso::StatisticsDanielBoso(const StatisticsDanielBoso& orig) {}

StatisticsDanielBoso::~StatisticsDanielBoso() {}

unsigned int StatisticsDanielBoso::numElements() {
    _collector->numElements();
}

double StatisticsDanielBoso::min() {
    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    std::getline(ifstream, value);
    double min = std::stod(value);
	while(std::getline(ifstream, value)) {
        if(min > std::stod(value)) {
            min = std::stod(value);
        }
    }
    return min;
}

double StatisticsDanielBoso::max() {
    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    std::getline(ifstream, value);
    double max = std::stod(value);
	while(std::getline(ifstream, value)) {
        if(max < std::stod(value)) {
            max = std::stod(value);
        }
    }
    return max;
}

double calculate_average(double averageBefore, double nextNumber, int n) {
    return ((averageBefore*(n - 1) + nextNumber)/n);
}

double StatisticsDanielBoso::average() {
    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    std::getline(ifstream, value);
    int n = 1;
    double averageBefore = std::stod(value);
	while(std::getline(ifstream, value)) {
        averageBefore = calculate_average(averageBefore, std::stod(value), n);
        n++;
    }
    return averageBefore;
}

int compare(const void *a, const void *b) {
    if(*(double*)a > *(double*)b) {
        return 1;
    } else if (*(double*)a < *(double*)b) {
        return -1;
    } else {
        return 0;
    }
 }

double StatisticsDanielBoso::mode() {
    std::list<double>* listDoubles;

    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    double averageBefore = std::stod(value);

	while(std::getline(ifstream, value)) {
        listDoubles->push_back(std::stod(value));
    }

    qsort(listDoubles, (size_t)listDoubles->size, sizeof(double), compare);

    double modeValue = listDoubles->front();
    unsigned int numberValues = 1;

    double tempModeValue = modeValue;
    unsigned int tempValues = numberValues;

    while(!listDoubles->empty()) {
        double value = listDoubles->front();
        
        if(value == tempValues) {
            tempValues++;
        } else {
            if (numberValues < tempValues) {
                modeValue = tempModeValue;
                numberValues = tempValues;
                tempModeValue = value;
                tempValues = 1;
            }
        }
    }

    return modeValue;
}

double StatisticsDanielBoso::mediane() {
    std::list<double>* listDoubles;

    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    double averageBefore = std::stod(value);

	while(std::getline(ifstream, value)) {
        listDoubles->push_back(std::stod(value));
    }

    qsort(listDoubles, (size_t)listDoubles->size, sizeof(double), compare);

    std::list<double>::iterator it = listDoubles->begin();

    if(listDoubles->size() % 2 == 0) {
        double number1;
        double number2;
        std::advance(it, (listDoubles->size())/2);
        number1 = *it;
        std::advance(it, ((listDoubles->size())/2)+1);
        number2 = *it;
        return number1 + number2 / 2;
    } else {
        std::advance(it, (listDoubles->size()+1)/2);
        return *it;
    }

}

double calculate_variance(std::ifstream &input, unsigned int nValue) {
    std::string value;
    if(std::getline(input, value)) {
        return (nValue-1)*calculate_variance(input, nValue--)/nValue;
    }
    return 0;
}

double StatisticsDanielBoso::variance() {
    double average = StatisticsDanielBoso::average();
    unsigned int nValue = _collector->numElements();
    
}

double StatisticsDanielBoso::stddeviation() {
    return sqrt(StatisticsDanielBoso::variance()/_collector->numElements()-1);
}

double StatisticsDanielBoso::variationCoef() {
    return sqrt(StatisticsDanielBoso::variance())/StatisticsDanielBoso::average();
}

double StatisticsDanielBoso::halfWidthConfidenceInterval(double confidencelevel) {}

unsigned int StatisticsDanielBoso::newSampleSize(double confidencelevel, double halfWidth) {}

double StatisticsDanielBoso::quartil(unsigned short num) {
    unsigned int position = 0.25 * (_collector->numElements() + 1);
    return 0; //_collector->getValue(position));
}

double StatisticsDanielBoso::decil(unsigned short num) {
    unsigned int position = 0.1 * (_collector->numElements() + 1);
    return 0; //_collector->getValue(position);
}

double StatisticsDanielBoso::centil(unsigned short num) {
    unsigned int position = 0.01 * (_collector->numElements() + 1);
    return 0; //(CollectorDanielBoso*)_collector->getValue(position);
}

void StatisticsDanielBoso::setHistogramNumClasses(unsigned short num) {
   _histogramNumClasses = num;
}

unsigned short StatisticsDanielBoso::histogramNumClasses() {
     unsigned int numSamples = _collector->numElements();
    
    if(numSamples < 30) {
        // Root
       return sqrt(numSamples);
    } else {
        // Sturges
        return 3.322 * log(numSamples)+1;
    }
}

double StatisticsDanielBoso::histogramClassLowerLimit(unsigned short classNum) {
    double lowerLimit = 0;
    for(int i = 1; i <= classNum; i++) {
        lowerLimit += _histogramNumClasses;
    }
    return lowerLimit;
}

unsigned int StatisticsDanielBoso::histogramClassFrequency(unsigned short classNum) {
    double lowerLimitClass = StatisticsDanielBoso::histogramClassLowerLimit(0);
    double upperLimitClass = lowerLimitClass + _histogramNumClasses;
    unsigned int frequency = 0;

    std::list<double>* listDoubles;

    std::ifstream ifstream;
    //ifstream.open();
    std::string value;
    double averageBefore = std::stod(value);

	while(std::getline(ifstream, value)) {
        listDoubles->push_back(std::stod(value));
    }

    qsort(listDoubles, (size_t)listDoubles->size, sizeof(double), compare);

    std::list<double>::iterator it = listDoubles->begin();

    unsigned int numberSamples = _collector->numElements();
    for(int i = 0; i < numberSamples; i++) {
        std::advance(it, i);
        if(*it > lowerLimitClass && *it <= upperLimitClass) {
            frequency++;
        } else if(*it > upperLimitClass) {
            break;
        }

    }
    return frequency;
}

Collector_if* StatisticsDanielBoso::getCollector() {
	return this->_collector;
}

void StatisticsDanielBoso::setCollector(Collector_if* collector) {
    _collector = collector;
}