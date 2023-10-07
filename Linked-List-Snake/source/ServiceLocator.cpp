#include "../header/ServiceLocator.h"

ServiceLocator::ServiceLocator()
{
	createServices();
}

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::createServices()
{
}

void ServiceLocator::initialize()
{
}

void ServiceLocator::update()
{
}

void ServiceLocator::render()
{
}

void ServiceLocator::clearAllServices()
{
}

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

void ServiceLocator::deleteServiceLocator() { delete(this); }