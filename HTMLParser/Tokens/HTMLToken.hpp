#ifndef HTMLTOKEN_H
#define HTMLTOKEN_H

#include <string>
#include <map>

typedef std::map<std::string, std::string> AttrMap;

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

	HTMLToken() {}
	~HTMLToken() {}

	TokenType getType() { return type; }
	virtual void appendToTagName(char inputChar) {}
	virtual std::string getName() { return ""; }

	// TagToken Methods
	virtual void appendToAttrName(char inputChar) {}
	virtual void appendToAttrValue(char inputChar) {}
	virtual void setSelfClosing(bool selfClosing) {}
	virtual AttrMap getAttributes() { return *(new AttrMap); }
	virtual bool isSelfClosing() { return false; }

	// CommentToken Methods
	virtual void appendToData(char inputChar) {}

	// DoctypeToken Methods
	virtual void setForceQuirks(bool forceQuirks) {}

	// CharacterToken Metohds

protected:
	TokenType type;
};

#endif