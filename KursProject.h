// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the KURSPROJECT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// KURSPROJECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KURSPROJECT_EXPORTS
#define KURSPROJECT_API __declspec(dllexport)
#else
#define KURSPROJECT_API __declspec(dllimport)
#endif

extern "C" KURSPROJECT_API void fillDB(const char* path);
extern "C" KURSPROJECT_API void deleteDB();
extern "C" KURSPROJECT_API void getListsOfObjects(char* output, int* len);
extern "C" KURSPROJECT_API void getLenLists(int* value);
extern "C" KURSPROJECT_API void getObjectsByFabric(const char* name, int* len, char* output);
extern "C" KURSPROJECT_API void getLenObjects(const char* name, int* value);
extern "C" KURSPROJECT_API void saveData();
extern "C" KURSPROJECT_API void getData(char* output, int* len);
extern "C" KURSPROJECT_API void getLenData(int* len);
extern "C" KURSPROJECT_API void sortByYear();
extern "C" KURSPROJECT_API void sortByExperience();
extern "C" KURSPROJECT_API void addElem(const char* input);
extern "C" KURSPROJECT_API void CheckLeaks(wchar_t** s_array, int& s_len);
extern "C" KURSPROJECT_API void unionBD(const char* path);