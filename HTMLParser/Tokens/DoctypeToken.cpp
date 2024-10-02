#include "DoctypeToken.hpp"

DoctypeToken::DoctypeToken()
{
    type = DOCTYPE;
}

void DoctypeToken::appendToTagName(char inputChar)
{
    this->name.push_back(towlower(inputChar));
}

void DoctypeToken::setForceQuirks(bool forceQuirks)
{
    this->forceQuirks = forceQuirks;
}
