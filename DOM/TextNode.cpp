#include "TextNode.hpp"

TextNode::TextNode(const std::string &text)
{
	this->text = text;
	this->set_type(TEXT);
}

TextNode::~TextNode()
{
}

std::string TextNode::to_string()
{
	return "TextNode{text=" + text + "}";
}

void TextNode::append_character(const char character)
{
	this->text.push_back(character);
}

TextNode::TextNode(char character)
{
	this->text.push_back(character);
	this->set_type(TEXT);
}
