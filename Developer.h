#pragma once
#include "Worker.h"
class Developer : public Worker
{
public:
    Developer(std::string n, std::string f, int y, std::string m,
        int w, std::string current) :Worker(n, f, y, m, w, current) {}
    Developer(const Developer& obj) : Worker(obj) {}
    Developer& operator=(const Developer& obj)
    {
        if (this != &obj)
        {
            Worker::operator=(obj);
        }
        return *this;
    }
    ~Developer() {}
    Worker* copy() { return new Developer(*this); }
    std::string getInfoToFile() {
        //(*department)[0] = std::toupper((*department)[0]);
        return "Developer/" + *name + "/" + *department + "/" +
            std::to_string(*year) + "/" + *contactInformation + "/" +
            std::to_string(*workExperience) + "/" + *currentProjects +
            "%";
    }
    void copyAdministrator(std::vector<Worker*>* obj, Worker* elem) {}
    void copyManager(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDeveloper(std::vector<Worker*>* obj, Worker* elem) { obj->push_back(elem); }
    void copyDesigner(std::vector<Worker*>* obj, Worker* elem) {}
};

