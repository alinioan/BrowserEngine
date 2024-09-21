#ifndef COMMENTTOKEN_H
#define COMMENTTOKEN_H

#include <string>

#include "HTMLToken.hpp"

class CommentToken : public HTMLToken
{
private:
    std::string data;

public:
    CommentToken();
    ~CommentToken() {}
    void appendToData(char inputChar) override;
};

#endif