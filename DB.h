#pragma once
#include "Designer.h"
#include "Administrator.h"
#include "Developer.h"
#include "Manager.h"
#include "pch.h"
#include <regex>


struct compareProductsByYear
{
public:
    bool operator()(const Worker* p1, const Worker* p2) const
    {
        return *(p1->getYear()) < *(p2->getYear());
    }
};

struct compareProductsBySert
{
public:
    bool operator()(const Worker* p1, const Worker* p2) const
    {
        return *(p1->getExp()) < *(p2->getExp());
    }
};

struct CompareProductFactory {
    bool operator()(const Worker* product, const std::string& department) const {
        return *product->getFabric() < department;
    }

    bool operator()(const std::string& department, const Worker* product) const {
        return department < *product->getFabric();
    }
};

class DB
{
private:
    std::vector <Worker*>* data;
public:
    DB() {
        data = new std::vector <Worker*>();
    }

    DB(const DB& obj) {
        data = new std::vector <Worker*>();

        std::transform(obj.data->begin(), obj.data->end(), obj.data->begin(),
            [&](Worker* elem)
            {
                data->push_back(elem->copy());
                return elem;
            });
    }

    DB& operator=(const DB& obj)
    {
        if (this != &obj)
        {
            std::for_each(data->begin(), data->end(),
                [](Worker* p)
                {
                    delete p;
                });
            data->clear();
            std::transform(obj.data->begin(), obj.data->begin(), obj.data->begin(),
                [&](Worker* elem)
                {
                    data->push_back(elem->copy());
                    return elem;
                });

        }
        return *this;
    }

    void addObject(Worker* obj)
    {
        data->push_back(obj);
    }
    void addObjectByStr(std::string line) {
        std::stringstream ss(line);
        std::string type;
        std::string dat;
        std::getline(ss, type, '/');
        std::vector <std::string> info;
        int exp;
        while (std::getline(ss, dat, '/')) info.push_back(dat);
        std::transform(info[1].begin(), info[1].end(), info[1].begin(),
            [](unsigned char c)
            {
                return std::tolower(c);
            });
        std::istringstream(info[4]) >> exp;
        if (type == "Designer")
            data->push_back(new Designer(info[0], info[1], std::stoi(info[2]),
                info[3], exp, std::regex_replace(info[5], std::regex("[%]"), "")));
        else if (type == "Administrator")
            data->push_back(new Administrator(info[0], info[1], std::stoi(info[2]),
                info[3], exp, std::regex_replace(info[5], std::regex("[%]"), "")));
        else if (type == "Manager")
            data->push_back(new Manager(info[0], info[1], std::stoi(info[2]),
                info[3], exp, std::regex_replace(info[5], std::regex("[%]"), "")));
        else if (type == "Developer")
            data->push_back(new Developer(info[0], info[1], std::stoi(info[2]),
                info[3], exp, std::regex_replace(info[5], std::regex("[%]"), "")));
    }

    ~DB()
    {
        std::for_each(data->begin(), data->end(),
            [](Worker* p)
            {
                delete p;
            });
        delete data;
    }

    void unionDBs(const DB& obj) {
        std::sort(data->begin(), data->end());
        std::sort(obj.getVector()->begin(), obj.getVector()->end());
        std::vector <Worker*>* unionData = new std::vector <Worker*>();
        std::set_union(data->begin(), data->end(), obj.getVector()->begin(), obj.getVector()->end(),
            std::back_inserter(*unionData));
        obj.getVector()->clear();
        delete data;
        auto last = std::unique(unionData->begin(), unionData->end());
        unionData->erase(last, unionData->end());
        data = unionData;
    }

    std::vector <Worker*>* getVector() const { return data; }
    std::vector<Worker*>* takeObjects(Administrator* obj) {
        std::vector <Worker*>* administrators = new std::vector <Worker*>();
        std::for_each(data->begin(), data->end(),
            [&](Worker* elem)
            {
                elem->copyAdministrator(administrators, elem);
            });
        return administrators;
    }

    std::vector<Worker*>* takeObjects(Designer* obj) {
        std::vector <Worker*>* designers = new std::vector <Worker*>();
        std::for_each(data->begin(), data->end(),
            [&](Worker* elem)
            {
                elem->copyDesigner(designers, elem);
            });
        return designers;
    }

    std::vector<Worker*>* takeObjects(Manager* obj) {
        std::vector <Worker*>* managers = new std::vector <Worker*>();
        std::for_each(data->begin(), data->end(),
            [&](Worker* elem)
            {
                elem->copyManager(managers, elem);
            });
        return managers;
    }

    std::vector<Worker*>* takeObjects(Developer* obj) {
        std::vector <Worker*>* developers = new std::vector <Worker*>();
        std::for_each(data->begin(), data->end(),
            [&](Worker* elem)
            {
                elem->copyDeveloper(developers, elem);
            });
        return developers;
    }

    std::string* getByFabric(std::string nameF) {
        std::string* info = new std::string("");
        std::transform(nameF.begin(), nameF.end(), nameF.begin(),
            [](unsigned char c)
            {
                return std::tolower(c);
            });
        //nameF[0] = std::toupper(nameF[0]);
        std::sort(data->begin(), data->end(), [](const Worker* a, const Worker* b) {
            return *a->getFabric() < *b->getFabric();
            });
        auto range = std::equal_range(data->begin(), data->end(), nameF, CompareProductFactory());
        for (auto it = range.first; it != range.second; ++it)
        {
            *info += (*it)->getInfoToFile() + '\n';
        }
        return info;
    }

    void sortByYear()
    {
        std::sort(data->begin(), data->end(), compareProductsByYear());
    }

    void sortByExperience()
    {
        std::sort(data->begin(), data->end(), compareProductsBySert());
    }

    bool isAllDigits(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](char c) {
            return std::isdigit(c);
            });
    }

    void fillDB(std::string path) {
        std::ifstream input(path);
        if (!input.is_open()) throw "error file path";
        std::string object;
        try
        {
            while (std::getline(input, object))
            {
                std::stringstream ss(object);
                std::string type;
                std::string dat;
                std::getline(ss, type, '/');
                std::vector <std::string> info;
                int sert;
                while (std::getline(ss, dat, '/')) info.push_back(dat);
                if (info.size() != 6) throw "error reading file";
                std::transform(info[1].begin(), info[1].end(), info[1].begin(),
                    [](unsigned char c)
                    {
                        return std::tolower(c);
                    });
                if (isAllDigits(info[4]) != true) throw "error";
                std::istringstream(info[4]) >> sert;
                if (type == "Designer")
                    data->push_back(new Designer(info[0], info[1], std::stoi(info[2]),
                        info[3], sert, std::regex_replace(info[5], std::regex("[%]"), "")));
                else if (type == "Administrator")
                    data->push_back(new Administrator(info[0], info[1], std::stoi(info[2]),
                        info[3], sert, std::regex_replace(info[5], std::regex("[%]"), "")));
                else if (type == "Manager")
                    data->push_back(new Manager(info[0], info[1], std::stoi(info[2]),
                        info[3], sert, std::regex_replace(info[5], std::regex("[%]"), "")));
                else if (type == "Developer")
                    data->push_back(new Developer(info[0], info[1], std::stoi(info[2]),
                        info[3], sert, std::regex_replace(info[5], std::regex("[%]"), "")));
            }
        }
        catch (...) { throw "error reading file. Check your bd!"; }
        input.close();
    }
    void saveDB() {
        std::ofstream output("db.txt");
        std::for_each(data->begin(), data->end(),
            [&](Worker* obj)
            {
                output << obj->getInfoToFile() << '\n';
            });
        output.close();
    }
    void deleteObj(int index) {
        data->erase(data->begin() + index);
    }
    std::string* listOfObjects() {
        std::string* listObjects = new std::string("");
        Administrator* administrator = nullptr;
        std::vector <Worker*>* administrators = takeObjects(administrator);
        Developer* developer = nullptr;
        std::vector <Worker*>* developers = takeObjects(developer);
        Manager* manager = nullptr;
        std::vector <Worker*>* managers = takeObjects(manager);
        Designer* designer = nullptr;
        std::vector <Worker*>* designers = takeObjects(designer);
        std::multimap<int, std::string> statistics;
        statistics.insert(std::pair<int, std::string>{administrators->size(), "Administrator"});
        statistics.insert(std::pair<int, std::string>{developers->size(), "Developer"});
        statistics.insert(std::pair<int, std::string>{managers->size(), "Manager"});
        statistics.insert(std::pair<int, std::string>{designers->size(), "Designer"});
        //std::vector <Product*> a
        std::for_each(statistics.begin(), statistics.end(),
            [&listObjects](std::pair<int, std::string> p)
            {
                *listObjects += p.second + " " + std::to_string(p.first) + '\n';
            });
        delete administrators;
        delete developers;
        delete managers;
        delete designers;
        return listObjects;
    }
};
