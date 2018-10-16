/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Traits.h
 * Author: cancian
 *
 * Created on 14 de Agosto de 2018, 19:36
 */

#ifndef TRAITS_H
#define TRAITS_H

// interfaces
#include "Model.h"
#include "Collector_if.h"
#include "Sampler_if.h"
#include "Fitter_if.h"
#include "ModelChecker_if.h"
#include "Parser_if.h"
#include "Statistics_if.h"
#include "Integrator_if.h"
#include "HypothesisTester_if.h"
#include "ModelPersistence_if.h"
#include "GenesysApplication_if.h"
//#include "ProcessAnalyser_if.h"
//#include "ExperimentDesign_if.h"

// possible implementations
#include "CollectorDanielBoso.h"
#include "CollectorDatafileDanielBoso.h"
#include "SamplerDanielBoso.h"
#include "FitterMyImpl1.h"
#include "ModelCheckerMyImpl1.h"
#include "ParserMyImpl1.h"
#include "IntegratorMyImpl1.h"
#include "IntegratorDiogoImpl.h"
//#include "HypothesisTesterDiogo.h"
#include "ModelPersistenceMyImpl1.h"
#include "StatisticsDanielBoso.h"
//#include "BuildSimpleModel1.h"
#include "ModelChecker_DS2Karla.h"
#include "BuildSimpleModel1.h"
#include "TestInputAnalyserTools.h"
//#include "ProcessAnalyserMyImpl1.h"
//#include "ExperimentDesignMyImpl1.h"

template <typename T>
struct Traits {
	static const bool debugged = true;
	static const Util::TraceLevel traceLevel = Util::TraceLevel::TL_mostDetailed; 
};

template <> struct Traits<GenesysApplication_if> {
	//typedef TestInputAnalyserTools Application;  
	typedef BuildSimpleModel1 Application;  
};

template <> struct Traits<Model> {
};

template <> struct Traits<ModelComponent> {
	typedef CollectorDanielBoso CollectorImplementation;
};

template <> struct Traits<Sampler_if> {
	typedef SamplerDanielBoso Implementation;
	typedef SamplerDanielBoso::MyRNG_Parameters Parameters;
};

template <> struct Traits<Fitter_if> {
	typedef FitterMyImpl1 Implementation;
};

template <> struct Traits<Collector_if> {
	typedef CollectorDatafileDanielBoso Implementation;
	typedef CollectorDanielBoso ModelImplementation; //TEMP
};

template <> struct Traits<ModelChecker_if> {
	typedef ModelChecker_DS2Karla Implementation;
};

template <> struct Traits<Parser_if> {
	typedef ParserMyImpl1 Implementation;
};

template <> struct Traits<Statistics_if> {
	typedef StatisticsDanielBoso Implementation;
};

template <> struct Traits<Integrator_if> {
	typedef IntegratorDiogoImpl Implementation;
};

template <> struct Traits<HypothesisTester_if> {
	//typedef HypothesisTesterMyImpl1 Implementation;
	//typedef HypothesisTesterDiogo Implementation;
};

template <> struct Traits<ModelPersistence_if> {
	typedef ModelPersistenceMyImpl1 Implementation;
};

//template <> struct Traits<ExperimentDesign_if> {
//	typedef ExperimentDesignMyImpl1 Implementation;
	//typedef ProcessAnalyserMyImpl1 ProcessAnalyserImplementation;
//};

//template <> struct Traits<ProcessAnalyser_if> {
//	typedef ProcessAnalyserMyImpl1 Implementation;
//};

#endif /* TRAITS_H */
