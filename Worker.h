#pragma once
class Worker
{
protected:
    std::string* name;
    std::string* department;
    int* year;
    std::string* contactInformation;
    int* workExperience;
    std::string* currentProjects;

public:
    Worker(std::string n, std::string f, int y, std::string m,
        int exp, std::string os);
    virtual ~Worker();
    Worker& operator=(const Worker& obj);
    Worker(const Worker& obj);
    bool operator<(const Worker& obj)
    {
        return *name < *obj.name;
    }
    std::string* getName() const { return name; }
    std::string* getFabric() const { return department; }
    int* getYear() const { return year; }
    int* getExp() const { return workExperience; }
    virtual std::string getInfoToFile() = 0;
    virtual Worker* copy() = 0;
    virtual void copyAdministrator(std::vector<Worker*>* obj, Worker* elem) = 0;
    virtual void copyManager(std::vector<Worker*>* obj, Worker* elem) = 0;
    virtual void copyDeveloper(std::vector<Worker*>* obj, Worker* elem) = 0;
    virtual void copyDesigner(std::vector<Worker*>* obj, Worker* elem) = 0;
};

