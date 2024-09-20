#ifndef DOCTYPETOKEN_H
#define DOCTYPETOKEN_H

#include <string>

#include "HTMLToken.hpp"

class DoctypeToken : public HTMLToken
{
private:
    std::string name;
    std::string publicIdentifier;
    std::string systemIdentifier;
    bool forceQuirks = false;
public:
    DoctypeToken();
    ~DoctypeToken();

    void appendToTagName(char inputChar) override;
    void setForceQuirks(bool forceQuirks) override;
};

#endif