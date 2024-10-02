#include "CharacterToken.hpp"

CharacterToken::CharacterToken(const char tokenChar)
{
    type = Character;
    this->tokenChar = tokenChar;
}