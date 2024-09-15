#ifndef DOCTYPETOKEN_H
#define DOCTYPETOKEN_H

#include <string>

#include "HTMLToken.hpp"

class TagToken : public HTMLToken
{
private:
    std::string name;
    std::string publicIdentifier;
    std::string systemIdentifier;
    bool forceQuirks = false;
public:
    TagToken();
    ~TagToken();
};

#endif