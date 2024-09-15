#include <string>

#include "HTMLToken.hpp"
#include "TagToken.hpp"

TagToken::TagToken(char inputChar, TokenType type)
{
    this->type = type;
    this->tagName.push_back(inputChar);
    currentAttrName = "";
    currentAttrValue = "";
}

void TagToken::appendToTagName(char inputChar)
{
    tagName.push_back(inputChar);
}

void TagToken::appendToAttrName(char inputChar)
{
    currentAttrName.push_back(inputChar);
}