#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <string>

#include "HTMLToken.hpp"
#include "Node.hpp"

class TextNode : public Node {
private:
    std::string text;

public:
    TextNode(const std::string &text);
    TextNode(char character);

    ~TextNode() override;
    std::string to_string() override;
    void append_character(char character) override;
};


#endif
