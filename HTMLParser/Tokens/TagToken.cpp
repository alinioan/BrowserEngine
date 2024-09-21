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

TagToken::~TagToken()
{
    
}

void TagToken::appendToTagName(char inputChar)
{
    tagName.push_back(inputChar);
}

void TagToken::appendToAttrName(char inputChar)
{
    currentAttrName.push_back(tolower(inputChar));
}

void TagToken::appendToAttrValue(char inputChar)
{
    currentAttrValue.push_back(inputChar);
}

void TagToken::setSelfClosing(bool selfClosing)
{
    this->selfClosing = selfClosing;
}
