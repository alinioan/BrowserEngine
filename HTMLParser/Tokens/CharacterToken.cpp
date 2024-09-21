#include "HTMLToken.hpp"
#include "CharacterToken.hpp"

CharacterToken::CharacterToken(char tokenChar)
{
    type = Character;
    this->tokenChar = tokenChar;
}