#include "include/TextNode.hpp"

TextNode::TextNode(std::string text) {
    this->text = text;
    this->setType(TEXT);
}

TextNode::~TextNode() {}

std::string TextNode::toString() {
    return "TextNode{text=" + text + "}";
}