#ifndef __NODE__
#define __NODE__

#include <vector>
#include <string>

enum NodeType {
    DATA,
    TEXT
};

class Node {
private:    
    std::vector<Node *> children;
    NodeType type;

    void recPrettyPrint(Node *node, std::string indent);
    
public:
    ~Node();
    virtual std::string toString() = 0;
    void add(Node *child);
    void prettyPrint();
    std::vector<Node *> getChildern();
    NodeType getType();
    void setChildren(std::vector<Node *> children);
    void setType(NodeType type);
};

#endif
