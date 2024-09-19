#include "pch.h"
#include "Designer.h"

std::string Designer::getInfoToFile() {
   // (*department)[0] = std::toupper((*department)[0]);
    return "Designer/" + *name + "/" + *department + "/" +
        std::to_string(*year) + "/" + *contactInformation + "/" +
        std::to_string(*workExperience) + "/" + *currentProjects +
        "%";
}

Designer& Designer::operator=(const Designer& obj)
{
    if (this != &obj)
    {
        Worker::operator=(obj);
    }
    return *this;
}

