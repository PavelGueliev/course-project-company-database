#pragma once
#include "Worker.h"

class Manager : public Worker
{
public:
    Manager(std::string n, std::string f, int y, std::string m,
        int w, std::string current) :Worker(n, f, y, m, w, current) {}
    Manager(const Manager& obj) : Worker(obj) {}
    Manager& operator=(const Manager& obj)
    {
        if (this != &obj)
        {
            Manager::operator=(obj);
        }
        return *this;
    }
    ~Manager() {}
    Worker* copy() { return new Manager(*this); }
    std::string getInfoToFile() {
        //(*department)[0] = std::toupper((*department)[0]);
        return "Manager/" + *name + "/" + *department + "/" +
            std::to_string(*year) + "/" + *contactInformation + "/" +
            std::to_string(*workExperience) + "/" + *currentProjects +
            "%";
    }
    void copyAdministrator(std::vector<Worker*>* obj, Worker* elem) {}
    void copyManager(std::vector<Worker*>* obj, Worker* elem) { obj->push_back(elem); }
    void copyDeveloper(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDesigner(std::vector<Worker*>* obj, Worker* elem) {}
};

