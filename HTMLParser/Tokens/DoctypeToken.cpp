#include "HTMLToken.hpp"
#include "DoctypeToken.hpp"

void DoctypeToken::appendToTagName(char inputChar)
{
    this->name.push_back(towlower(inputChar));
}

void DoctypeToken::setForceQuirks(bool forceQuirks)
{
    this->forceQuirks = forceQuirks;
}
