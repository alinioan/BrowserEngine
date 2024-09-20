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
	virtual void appendToTagName(char inputChar);

	// TagToken Methods
	virtual void appendToAttrName(char inputChar);
	virtual void appendToAttrValue(char inputChar);
	virtual void setSelfClosing(bool selfClosing);

	// CommentToken Mthods
	virtual void appendToData(char inputChar);

	// DoctypeToken Methods
	virtual void setForceQuirks(bool forceQuirks);

	// CharacterToken Metohds

protected:
	TokenType type;
};

#endif