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
	virtual void appendToTagName(char inputChar);
	virtual void appendToAttrName(char inputChar);
	virtual void appendToAttrValue(char inputChar);
	virtual void setSelfClosing(bool selfClosing);

	// CommentToken Mthods
	virtual void appendToData(char inputChar);

	// DoctypeToken Methods

	// CharacterToken Metohds

protected:
	TokenType type;
};

#endif