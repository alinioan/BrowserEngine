#ifndef TAGTOKEN_H
#define TAGTOKEN_H

#include <string>

#include "HTMLToken.hpp"
#include "DataNode.hpp"

class TagToken : public HTMLToken
{
private:
    std::string tagName;
    AttrMap attributes;
    bool selfClosing = false;
    std::string currentAttrName;
    std::string currentAttrValue;

public:
    TagToken(char inputChar, TokenType type);
    ~TagToken();
    void appendToTagName(char inputChar) override;
    void appendToAttrName(char inputChar) override;
    void appendToAttrValue(char inputChar) override;
    void setSelfClosing(bool selfClosing) override;
};

#endif