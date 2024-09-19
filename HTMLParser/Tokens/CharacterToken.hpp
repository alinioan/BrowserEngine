#ifndef CHARTOKEN_H
#define CHARTOKEN_H

#include <string>

#include "HTMLToken.hpp"

class CharacterToken : public HTMLToken
{
private:
    char tokenChar;

public:
    CharacterToken(char tokenChar);
    ~CharacterToken();
};

#endif