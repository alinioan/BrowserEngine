#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "Tokens/HTMLToken.hpp"

class HTMLTokenizer
{
public:
	HTMLTokenizer(std::string input);
	HTMLTokenizer();
	~HTMLTokenizer() {}
	HTMLToken *createToken();
	std::vector<HTMLToken *> tokenizeString(std::string input);

	void setInput();

private:
	enum TokenizerState
	{
		dataState,
		characterReferenceState,
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
	TokenizerState state{TokenizerState::dataState};
	std::string input;
	size_t cursor;
};

#endif