#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <string>
#include "Node.hpp"

class TextNode : public Node {
private:
    std::string text;

public:
    TextNode(const std::string &text);
    ~TextNode() override;
    std::string to_string() override;
};


#endif
