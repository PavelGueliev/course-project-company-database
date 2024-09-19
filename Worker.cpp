#include "pch.h"
#include "Worker.h"

Worker::Worker(const Worker& obj)
{
    name = new std::string(*obj.name);
    department = new std::string(*obj.department);
    year = new int(*obj.year);
    contactInformation = new std::string(*obj.contactInformation);
    workExperience = new int(*obj.workExperience);
    currentProjects = new std::string(*obj.currentProjects);
}

Worker& Worker::operator=(const Worker& obj)
{
    if (this != &obj)
    {
        *name = *obj.name;
        *department = *obj.department;
        *year = *obj.year;
        *contactInformation = *obj.contactInformation;
        *workExperience = *obj.workExperience;
        *currentProjects = *obj.currentProjects;
    }
    return *this;
}

Worker::~Worker()
{
    delete name; delete department;
    delete year; delete contactInformation;
    delete workExperience; delete currentProjects;
}

Worker::Worker(std::string n, std::string f, int y, std::string m,
    int workexperience, std::string current)
{
    name = new std::string(n);
    department = new std::string(f);
    year = new int(y);
    contactInformation = new std::string(m);
    workExperience = new int(workexperience);
    currentProjects = new std::string(current);
}