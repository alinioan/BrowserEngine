#include <iostream>
#include "Node.hpp"

Node::~Node()
{
    for (const auto node : children)
    {
        delete node;
    }
}

void Node::add(Node *child)
{
    this->children.push_back(child);
}

void Node::rec_pretty_print(Node *node, const std::string &indent)
{
    std::cout << indent << node->to_string() << '\n';
    for (auto child : node->get_children())
    {
        rec_pretty_print(child, indent + "\t");
    }
}

void Node::pretty_print()
{
    rec_pretty_print(this, "");
}

std::vector<Node *> Node::get_children()
{
    return this->children;
}

NodeType Node::get_type() const
{
    return this->type;
}

void Node::set_children(const std::vector<Node *> &children)
{
    this->children = children;
}

void Node::set_type(const NodeType type)
{
    this->type = type;
}
