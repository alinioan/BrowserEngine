#ifndef HTMLTOKEN_H
#define HTMLTOKEN_H

class HTMLToken
{
public:
	enum TokenType
	{
		DOCTYPE,
		StartTag,
		EndTag,
		Comment,
		Character,
		EndOfFile
	};

	HTMLToken();
	~HTMLToken();
	TokenType getType();

	// TagToken Methods
	virtual void appendToTagName(char inputChar) = 0;
	virtual void appendToAttrName(char inputChar) = 0;

protected:
	TokenType type;
};

#endif