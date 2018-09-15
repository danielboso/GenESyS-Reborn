/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CollectorDatafileMyImpl1.h
 * Author: cancian
 *
 * Created on 30 de Agosto de 2018, 16:53
 */

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

