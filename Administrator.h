#pragma once
#include "Worker.h"
class Administrator :
    public Worker
{
public:
    Administrator(std::string n, std::string f, int y, std::string m,
        int w, std::string current) :Worker(n, f, y, m, w, current) {}
    Administrator(const Administrator& obj) : Worker(obj) {}
    Administrator& operator=(const Administrator& obj)
    {
        if (this != &obj)
        {
            Worker::operator=(obj);
        }
        return *this;
    }
    ~Administrator() {}
    Worker* copy() { return new Administrator(*this); }
    std::string getInfoToFile() {
        return "Administrator/" + *name + "/" + *department + "/" +
            std::to_string(*year) + "/" + *contactInformation + "/" +
            std::to_string(*workExperience) + "/" + *currentProjects +
            "%";
    }
    void copyAdministrator(std::vector<Worker*>* obj, Worker* elem) { obj->push_back(elem); }
    void copyManager(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDeveloper(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDesigner(std::vector<Worker*>* obj, Worker* elem) {}
};

