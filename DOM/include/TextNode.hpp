#ifndef __TEXTNODE__
#define __TEXTNODE__

#include <string>
#include "Node.hpp"

class TextNode : public Node {
private:
    std::string text;

public:
    TextNode(std::string text);
    ~TextNode();
    std::string toString();
};


#endif
