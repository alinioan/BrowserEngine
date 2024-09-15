#ifndef CHARTOKEN_H
#define CHARTOKEN_H

#include <string>

#include "HTMLToken.hpp"

class CommentToken : public HTMLToken
{
private:
    std::string data;

public:
    CommentToken();
    ~CommentToken();

};

#endif