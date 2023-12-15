#include "Education.h"

std::string Faculty::getCallbackData() const 
{ 
    return alias;
}

std::string Faculty::getName() const 
{ 
    return name;
}

std::string Level::getCallbackData() const 
{ 
    return std::to_string(id);
}

std::string Level::getName() const 
{ 
    return studyLevelName;
}

std::string Group::getCallbackData() const 
{ 
    return std::to_string(groupId);
}

std::string Group::getName() const 
{ 
    return groupName;
}

std::string Program::getCallbackData() const 
{ 
    return studyProgramId;
}

std::string Program::getName() const 
{ 
    return year;
}

unsigned int Program::getId() const 
{ 
    return id;
}

std::string Program::getProgramName() const 
{ 
    return programName;
}

