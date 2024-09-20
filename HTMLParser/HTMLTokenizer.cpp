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

HTMLTokenizer::HTMLTokenizer(std::string input)
{
	cursor = 0;
	this->input = input;
}

HTMLToken *HTMLTokenizer::createToken()
{
	HTMLToken *token;
	TokenizerState returnState;
	for (; cursor < HTMLTokenizer::input.size(); cursor++)
	{
		char nextInputChar = input.at(cursor);
		switch (state)
		{
		case dataState:
			if (nextInputChar == '&')
			{
				state = characterReferenceState;
				returnState = dataState;
			}
			else if (nextInputChar == '>')
				state = tagOpenState;
			else
			{
				cursor++;
				return new CharacterToken(nextInputChar);
			}
			break;
		case characterReferenceState:
			// TODO: implement state
			break;
		case tagOpenState:
			if (nextInputChar == '!')
				state = markupDeclarationOpenState;
			else if (nextInputChar == '/')
				state = endTagOpenState;
			else if (isalpha(nextInputChar))
			{
				state = tagNameState;
				token = new TagToken(nextInputChar, HTMLToken::TokenType::StartTag);
			}
			// unexpected-question-mark-instead-of-tag-name parse error
			else if (nextInputChar == '?')
			{
				token = new CommentToken;
				cursor--;
				state = bogusCommentState;
			}
			break;
		case tagNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				state = beforeAttributeNameState;
			else if (nextInputChar == '/')
				state = selfClosingStartTagState;
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else if (isalpha(nextInputChar))
				token->appendToTagName(nextInputChar);
			else
				token->appendToTagName(nextInputChar);
			break;
		case beforeAttributeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				break;

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
			if (whiteSpaceChars.count(nextInputChar) != 0 || nextInputChar == '/' || nextInputChar == '>')
			{
				cursor--;
				state = afterAttributeNameState;
			}
			else if (nextInputChar == '=')
				state = beforeAttributeValueState;
			else
				token->appendToAttrName(nextInputChar);
			break;
		case afterAttributeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				break;
			if (nextInputChar == '/')
				state = selfClosingStartTagState;
			else if (nextInputChar == '=')
				state = beforeAttributeValueState;
			break;
		case beforeAttributeValueState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
			{
				break;
			}
			if (nextInputChar == '"')
				state = attributeValueDoubleQuotedState;
			else if (nextInputChar == '\'')
				state = attributeValueSingleQuotedState;
			// missing-attribute-value pasere error
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else
			{
				cursor--;
				state = attributeValueUnquotedState;
			}
			break;
		case attributeValueUnquotedState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				state = beforeAttributeNameState;
			else if (nextInputChar == '&')
			{
				returnState = attributeValueUnquotedState;
				state = characterReferenceState;
			}
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else
				token->appendToAttrValue(nextInputChar);
			break;
		case attributeValueSingleQuotedState:
			if (nextInputChar == '\'')
				state = afterAttributeValueQuotedState;
			else if (nextInputChar == '&')
			{
				returnState = attributeValueSingleQuotedState;
				state = characterReferenceState;
			}
			else
				token->appendToAttrValue(nextInputChar);
			break;
		case attributeValueDoubleQuotedState:
			if (nextInputChar == '"')
				state = afterAttributeValueQuotedState;
			else if (nextInputChar == '&')
			{
				returnState = attributeValueDoubleQuotedState;
				state = characterReferenceState;
			}
			else
				token->appendToAttrValue(nextInputChar);
			break;
		case afterAttributeValueQuotedState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				state = beforeAttributeNameState;
			else if (nextInputChar == '/')
				state = selfClosingStartTagState;
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			// missing-whitespace-between-attributes parse error
			else
			{
				cursor--;
				state = beforeAttributeNameState;
			}
			break;
		case selfClosingStartTagState:
			if (nextInputChar == '>')
			{
				token->setSelfClosing(true);
				state = dataState;
				cursor++;
				return token;
			}
			// unexpected-solidus-in-tag parse error
			else
			{
				cursor--;
				state = beforeAttributeNameState;
			}
			break;
		case bogusCommentState:
			if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			token->appendToData(nextInputChar);
			break;
		case markupDeclarationOpenState:
			if (input.substr(cursor, cursor + 2) == "--")
			{
				cursor++;
				token = new CommentToken;
				state = commentStartState;
			}
			if (input.substr(cursor, cursor + 7) == "doctype")
			{
				cursor += 6;
				state = doctypeState;
			}
			// TODO: switch to cdata state
			break;
		case doctypeState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				state = beforeDoctypeNameState;
			else if (nextInputChar == '>')
			{
				cursor--;
				state = beforeDoctypeNameState;
			}
			// missing-whitespace-before-doctype-name parse error
			else
			{
				cursor--;
				state = doctypeNameState;
			}
			break;
		case beforeDoctypeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				break;
			token = new DoctypeToken;
			if (nextInputChar == '>')
			{
				token->setForceQuirks(true);
				state = dataState;
				cursor++;
				return token;	
			}
			else
			{
				token->appendToTagName(nextInputChar);
				state = doctypeNameState;
			}
			break;
		case doctypeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				state = afterDoctypeNameState;
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;	
			}
			else
				token->appendToTagName(nextInputChar);
			break;
		case afterDoctypeNameState:
			if (whiteSpaceChars.count(nextInputChar) != 0)
				break;
			if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;	
			}
			// other doctypes not supported
			token->setForceQuirks(true);
			state = bogusCommentState;
			break;
		case commentStartState:
			if (nextInputChar == '-')
				state = commentStartDashState;
			// abrupt-closing-of-empty-comment parse error
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else
			{
				cursor--;
				state = commentState;
			}
			break;
		case commentStartDashState:
			if (nextInputChar == '-')
				state = commentEndState;
			// abrupt-closing-of-empty-comment parse error
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else
			{
				token->appendToData('-');
				cursor--;
				state = commentState;
			}
			break;
		case commentState:
			if (nextInputChar == '-')
				state = commentEndDashState;
			else
				token->appendToData(nextInputChar);
			break;
		case commentEndDashState:
			if (nextInputChar == '-')
				state = commentEndState;
			else
			{
				token->appendToData('-');
				cursor--;
				state = commentState;
			}
			break;
		case commentEndState:
			if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
			else if (nextInputChar == '!')
				state = commentEndBangState;
			else if (nextInputChar == '-')
				token->appendToData('-');
			else
			{
				token->appendToData('-');
				token->appendToData('-');
				cursor--;
				state = commentState;
			}
			break;
		case commentEndBangState:
			if (nextInputChar == '-')
			{
				token->appendToData('-');
				token->appendToData('-');
				token->appendToData('!');
				state = commentEndDashState;
			}
			else if (nextInputChar == '>')
			{
				state = dataState;
				cursor++;
				return token;
			}
		default:
			break;
		}
	}
	return token;
}
