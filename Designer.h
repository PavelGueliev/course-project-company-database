#pragma once
#include "Worker.h"
class Designer : public Worker
{
public:
    Designer(std::string n, std::string f, int y, std::string m,
        int w, std::string current) :Worker(n, f, y, m, w, current) {}
    Designer(const Designer& obj) : Worker(obj) {}
    Designer& operator=(const Designer& obj);
    ~Designer() {}
    std::string getInfoToFile();
    Worker* copy() { return new Designer(*this); }
    void copyAdministrator(std::vector<Worker*>* obj, Worker* elem) {}
    void copyManager(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDeveloper(std::vector<Worker*>* obj, Worker* elem) {}
    void copyDesigner(std::vector<Worker*>* obj, Worker* elem) { obj->push_back(elem); }
};
