#include <string>

#include "CommentToken.hpp"

CommentToken::CommentToken()
{
    type = Comment;
}

void CommentToken::appendToData(char inputChar)
{
    data.push_back(inputChar);
}
