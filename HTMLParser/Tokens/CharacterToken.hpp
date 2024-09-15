#ifndef CHARTOKEN_H
#define CHARTOKEN_H

#include <string>

#include "HTMLToken.hpp"

class CommentToken : public HTMLToken
{
private:
    char tokenChar;

public:
    CommentToken();
    ~CommentToken();
};

#endif