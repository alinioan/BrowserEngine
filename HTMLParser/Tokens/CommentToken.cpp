#include <string>

#include "CommentToken.hpp"
#include "HTMLToken.hpp"

CommentToken::CommentToken()
{

}

void CommentToken::appendToData(char inputChar)
{
    data.push_back(inputChar);
}
