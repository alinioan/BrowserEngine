#include <string>
#include <iostream>
#include <set>

#include "HTMLTokenizer.hpp"
#include "Tokens/HTMLToken.hpp"
#include "Tokens/DoctypeToken.hpp"
#include "Tokens/CharacterToken.hpp"
#include "Tokens/CommentToken.hpp"
#include "Tokens/TagToken.hpp"

// In order: tab, line feed, form feed, space
const std::set<char> whiteSpaceChars = {'\t', '\n', '\f', ' '};

HTMLToken *HTMLTokenizer::createToken()
{
	HTMLToken *token;
	for (; cursor < HTMLTokenizer::input.size(); cursor++)
	{
		char nextInputChar = input.at(cursor);
		switch (state)
		{
		case dataState:
			if (nextInputChar == '&')
			{
				// TODO: char refrence state
			}
			else if (nextInputChar == '>')
			{
				state = tagOpenState;
			}
			else
			{
				// TODO: return eof token
			}
			break;
		case tagOpenState:
			if (nextInputChar == '!')
			{
				state = markupDeclarationOpenState;
			}
			else if (nextInputChar == '/')
			{
				state = endTagOpenState;
			}
			else if (isalpha(nextInputChar))
			{
				state = tagNameState;
				token = new TagToken(nextInputChar, HTMLToken::TokenType::StartTag);
			}
			// unexpected-question-mark-instead-of-tag-name parse error
			else if (nextInputChar == '?')
			{
				state = bogusCommentState;
			}
			break;
		case tagNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
			{
				state = beforeAttributeNameState;
			}
			else if (nextInputChar == '/')
			{
				state = selfClosingStartTagState;
			}
			else if (nextInputChar == '>')
			{
				state = dataState;
				return token;
			}
			else if (isalpha(nextInputChar))
			{
				token->appendToTagName(nextInputChar);
			}
			else
			{
				token->appendToTagName(nextInputChar);
			}
			break;
		case beforeAttributeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
			{
				break;
			}
			if (nextInputChar == '/' || nextInputChar == '>')
			{
				cursor--;
				state = afterAttributeNameState;
			}
			// TODO: '='
			else
			{
				cursor--;
				state = attributeNameState;
			}
			break;
		case attributeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0
				|| nextInputChar == '/' || nextInputChar == '>')
			{
				cursor--;
				state = afterAttributeNameState;
			}
			if (nextInputChar == '=') {
				state = beforeAttributeValueState;
				
			}
			break;
		default:
			break;
		}
	}
	return token;
}
