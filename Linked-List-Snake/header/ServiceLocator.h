#pragma once

class ServiceLocator
{
private:
    ServiceLocator();
    ~ServiceLocator();

    void createServices();
    void clearAllServices();

public:
    static ServiceLocator* getInstance();

    void initialize();
    void update();
    void render();
    void deleteServiceLocator();
};