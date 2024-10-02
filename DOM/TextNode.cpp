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
