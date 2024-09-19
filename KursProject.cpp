// KursProject.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "KursProject.h"
#include "DB.h"


DB* db = new DB();

KURSPROJECT_API void fillDB(const char* path)
{
    db->fillDB(path);
}

KURSPROJECT_API void deleteDB()
{
    delete db;
}

KURSPROJECT_API void getListsOfObjects(char* output, int* len)
{
    std::string* listObjects = db->listOfObjects();
    strncpy_s(output, *len, listObjects->c_str(), *len);
    delete listObjects;
}

KURSPROJECT_API void getObjectsByFabric(const char* name, int* len, char* output)
{
    std::string* info = db->getByFabric(name);
    if ((info->length()) > *len) throw "";
    strncpy_s(output, *len, info->c_str(), *len);
    delete info;
}

KURSPROJECT_API void saveData()
{
    db->saveDB();
}

KURSPROJECT_API void getLenData(int* len)
{
    std::string n = "";
    std::vector <Worker*>* data = db->getVector();
    std::for_each(data->begin(), data->end(),
        [&n](Worker* obj)
        {
            n += obj->getInfoToFile() + '\n';
        });
    *len = (n.length() + 1);
}

KURSPROJECT_API void getData(char* output, int* len)
{
    std::string n = "";
    std::vector <Worker*>* data = db->getVector();
    std::for_each(data->begin(), data->end(),
        [&n](Worker* obj)
        {
            n += obj->getInfoToFile() + '\n';
        });
    strncpy_s(output, *len, n.c_str(), *len);
}

KURSPROJECT_API void sortByYear() { db->sortByYear(); }

KURSPROJECT_API void sortByExperience() { db->sortByExperience(); }

KURSPROJECT_API void getLenObjects(const char* name, int* value)
{
    std::string* info = db->getByFabric(name);
    *value = (info->length() + 1);
    delete info;
}

KURSPROJECT_API void getLenLists(int* value)
{
    std::string* listObjects = db->listOfObjects();
    *value = (listObjects->length() + 1);
    delete listObjects;
}

KURSPROJECT_API void CheckLeaks(wchar_t** s_array, int& s_len)        //Запись утечек в файл и парсинг
{
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        short* ii = new short(92);
        CoTaskMemFree(*s_array);
        HANDLE hLogFile;
        hLogFile = CreateFile(L"log.txt", GENERIC_WRITE,
            FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, hLogFile);
        _CrtDumpMemoryLeaks();
        CloseHandle(hLogFile);
        std::wifstream in(L"log.txt");
        std::wstring  ws((std::istreambuf_iterator<wchar_t >(in)), std::istreambuf_iterator<wchar_t>());
        wchar_t* n_sarr = (wchar_t*)CoTaskMemAlloc((ws.size() + 1) * sizeof(wchar_t*));
        ZeroMemory((n_sarr), (ws.size() + 1) * sizeof(wchar_t));
        StringCchCatW(n_sarr, ws.size() + 1, ws.data());

        *s_array = n_sarr;
        s_len = ws.size() + 1;
}

KURSPROJECT_API void unionBD(const char* path)
{
    DB dbBuff;
    dbBuff.fillDB(path);
    db->unionDBs(dbBuff);
}

KURSPROJECT_API void addElem(const char* input) { db->addObjectByStr(input); }