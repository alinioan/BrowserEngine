#include <iostream>
#include "include/Node.hpp"

Node::~Node() {
    for (auto node : children) {
        delete node;
    }
}

void Node::add(Node* child) {
    this->children.push_back(child);
}

void Node::recPrettyPrint(Node *node, std::string indent) {
    std::cout << indent << node->toString() << '\n';
    for (auto child : node->getChildern()) {
        recPrettyPrint(child, indent + "\t");
    }
}

void Node::prettyPrint() {
    recPrettyPrint(this, "");
}

std::vector<Node *> Node::getChildern() {
    return this->children;
}

NodeType Node::getType() {
    return this->type;
}

void Node::setChildren(std::vector<Node *> children) {
    this->children = children;
}

void Node::setType(NodeType type) {
    this->type = type;
}
