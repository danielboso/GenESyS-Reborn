/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Release.cpp
 * Author: cancian
 * 
 * Created on 21 de Agosto de 2018, 16:17
 */

#include "Release.h"
#include "Model.h"
#include "WaitingResource.h"
#include "Queue.h"
#include "Resource.h"
#include "Attribute.h"

Release::Release(Model* model) : ModelComponent(model) {
	_name = "Release " + std::to_string(Util::GenerateNewIdOfType<Release>());
	_resource = (Resource*) _model->getInfrastructure(Util::TypeOf<Resource>(), "Resource 1");
	_verifySymbolsResource("Resource 1");
        
	std::string queueName = _resource->getName() + "_Queue"; // resourceName + "_Queue";
	_verifySymbolsQueue(queueName);

}

Release::Release(const Release& orig) : ModelComponent(orig) {
}

Release::~Release() {
}

std::string Release::show() {
	return ModelComponent::show() +
			",resourceType=" + std::to_string(this->_resourceType) +
			",resource=\"" + this->_resource->getName() + "\"" +
			",quantity=" + this->_quantity;
}

void Release::setPriority(unsigned short _priority) {
	this->_priority = _priority;
}

unsigned short Release::getPriority() const {
	return _priority;
}

void Release::setResourceType(Resource::ResourceType _resourceType) {
	this->_resourceType = _resourceType;
}

Resource::ResourceType Release::getResourceType() const {
	return _resourceType;
}

void Release::setQuantity(std::string _quantity) {
	this->_quantity = _quantity;
}

std::string Release::getQuantity() const {
	return _quantity;
}

void Release::setRule(Resource::ResourceRule _rule) {
	this->_rule = _rule;
}

Resource::ResourceRule Release::getRule() const {
	return _rule;
}

void Release::setSaveAttribute(std::string _saveAttribute) {
	this->_saveAttribute = _saveAttribute;
}

std::string Release::getSaveAttribute() const {
	return _saveAttribute;
}

void Release::_execute(Entity* entity) {
	Resource* resource = nullptr;
	if (this->_resourceType == Resource::ResourceType::rtSET) {
		/* TODO +: not implemented yet */
	} else {
		resource = this->_resource;
	}
	unsigned int quantity = _model->parseExpression(this->_quantity);
	//change to ASSERT??
	//if(_resource->getNumberBusy()< quantity) {
	//	error
	//}
	_resource->release(quantity, _model->getSimulatedTime()); //{releases and sets the 'LastTimeSeized'property}
	//Genesys.Model.SIMAN.EntityAllocationTimeAdd(entity, thisModule.aAllocationType, thisRec.LastTimeSeized);
	_model->traceSimulation(Util::TraceLevel::TL_blockInternal, _model->getSimulatedTime(), entity, this, "Entity frees " + std::to_string(quantity) + " units of resource \"" + resource->getName() + "\"");
	if (_queue->size() > 0) { //  ->getList()->size() > 0) {
		WaitingResource* firstWaiting = (WaitingResource*) _queue->first();//>getList()->first();
		if (firstWaiting->getQuantity() >= quantity) { // entity waiting can seize the resource now
			Event* newEvent = new Event(_model->getSimulatedTime(), firstWaiting->getEntity(), firstWaiting->getComponent());
			_model->getEvents()->insert(newEvent);
			_model->traceSimulation(Util::TraceLevel::TL_blockInternal, _model->getSimulatedTime(), entity, this, "Entity removes entity " + std::to_string(firstWaiting->getEntity()->getId()) + " from queue \"" + _queue->getName() + "\"");
			_queue->removeElement(firstWaiting, _model->getSimulatedTime()); //->getList()->remove(firstWaiting);
		} else {
			_model->traceSimulation(Util::TraceLevel::TL_blockInternal, _model->getSimulatedTime(), entity, this, "Entity " + std::to_string(firstWaiting->getEntity()->getId()) + " remains waiting in queue \"" + _queue->getName() + "\" for " + std::to_string(firstWaiting->getQuantity()) + " instances of resource \"" + resource->getName() + "\"");

		}
	}
	_model->sendEntityToComponent(entity, this->getNextComponents()->first(), 0.0);

}

void Release::_loadInstance(std::list<std::string> words) {

}

std::list<std::string>* Release::_saveInstance() {
	std::list<std::string>* words = new std::list<std::string>();
	return words;

}

void Release::setQueueName(std::string _queueName) {
	if (_queue->getName() != _queueName) {
            Queue* queueNewName = _verifySymbolsQueue(_queueName);
            if(queueNewName != nullptr){ // there is another queue with the same name
                if (!_queue->isLinked()) { // no one else uses it. It can be removed
                    _model->getInfrastructures(Util::TypeOf<Queue>())->remove(_queue);
                    _queue->~Queue();
                } else { // there is another one using the queue with old name. Let it there
                    _queue->removeLink();
                }
                    _queue = queueNewName;
                    _queue->addLink();
		}
	}
        //else: there is no queue with the new name and _verifySymbolsQueue(_queueName) created;
}

void Release::setResourceName(std::string _resourceName) {
    if (_resource->getName() != _resourceName) {
        Resource* resourceWithTheNewName = _verifySymbolsResource(_resourceName);
        if (resourceWithTheNewName != nullptr){ // there is another resource with the same name
            if (!_resource->isLinked()) { // no one else uses it. It can be removed   
                _model->getInfrastructures(Util::TypeOf<Resource>())->remove(_resource);
                _resource->~Resource();
            } else { // there is another one using the resource with old name. Let it there
                _resource->removeLink();
            }
            _resource = resourceWithTheNewName;
            _resource->addLink();

        }
        //else: there is no resource with the new name and _verifySymbolsResource(_resourceName) created;
    }
}

std::string Release::getResourceName() const {
	return _resource->getName();
}

std::string Release::getQueueName() const {
	return _queue->getName();
}


bool Release::_verifySymbols(std::string* errorMessage) {
        
    /* Checking Resource */
    //Quando Seize tiver mais de um Resource: fazer a chamada a seguir dentro de um loop para cada resource.
    _verifySymbolsResource(_resource->getName());

    /* Checking Queue */
    _verifySymbolsQueue(_queue->getName());

    /* Checking Attribute */
    if (((Attribute*) _model->getInfrastructure(Util::TypeOf<Attribute>(), _saveAttribute)) == nullptr) { // there is no Attribute with the  name
        Attribute* newAttribute = new Attribute();
        newAttribute->setName(_saveAttribute);
        _model->getInfrastructures(Util::TypeOf<Attribute>())->insert(newAttribute);
    }

    /*Checking Quantity*/
    bool result = true;
    this->_model->parseExpression(getQuantity(), &result, errorMessage);
    return result;

}


Resource* Release::_verifySymbolsResource(std::string _resourceName) {
    Resource* resourceBeenChecked = (Resource*) _model->getInfrastructure(Util::TypeOf<Resource>(), _resourceName);
    if (resourceBeenChecked == nullptr) { // there is no resource with the  name
        if (!_resource->isLinked()) { // no one else uses it. Only change the name
                _resource->setName(_resourceName);
        } else { // it is linked. Create a new one
                _resource = new Resource(_model);
                _resource->setName(_resourceName);
        }
        _model->getInfrastructures(Util::TypeOf<Resource>())->insert(_resource);
    } 
    return resourceBeenChecked;
}

Queue* Release::_verifySymbolsQueue(std::string _queueName){
    Queue* queueBeenChecked = (Queue*) _model->getInfrastructure(Util::TypeOf<Queue>(), _queueName);
    if (queueBeenChecked == nullptr) { // there is no queue with the new name
            if (!_queue->isLinked()) { // no one else uses it. Only change the name
                    _queue->setName(_queueName);
            } else { // it is linked. Create a new one
                    _queue = new Queue();
                    _queue->setName(_queueName);
            }
            
        _model->getInfrastructures(Util::TypeOf<Queue>())->insert(_queue);
    } 
    return queueBeenChecked;
}