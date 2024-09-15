#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

#include "Tokens/HTMLToken.hpp"

class HTMLTokenizer
{
public:
	enum TokenizerState
	{
		dataState,
		charRefInDataState,
		rcdataState,
		rawtextState,
		plaintextState,
		tagOpenState,
		endTagOpenState,
		tagNameState,
		rcdataLessThanSignState,
		rcdataEndTagNameState,
		rawtextLessThanSignState,
		rawtextEndTagNameState,
		beforeAttributeNameState,
		attributeNameState,
		afterAttributeNameState,
		beforeAttributeValueState,
		attributeValueDoubleQuotedState,
		attributeValueSingleQuotedState,
		attributeValueUnquotedState,
		charRefInAttributeValueState,
		afterAttributeValueQuotedState,
		selfClosingStartTagState,
		bogusCommentState,
		markupDeclarationOpenState,
		commentStartState,
		commentStartDashState,
		commentState,
		commentEndDashState,
		commentEndState,
		commentEndBangState,
		doctypeState,
		beforeDoctypeNameState,
		doctypeNameState,
		afterDoctypeNameState,
		bogusDoctypeState,
		cdataSectionState
	};

	HTMLToken *createToken();

private:
	TokenizerState state{TokenizerState::dataState};
	std::string input;
	size_t cursor;
};

#endif