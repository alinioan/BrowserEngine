#include "DOM/include/Node.hpp"
#include "DOM/include/DataNode.hpp"
#include "DOM/include/TextNode.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Node *root = new DataNode("html");
    Node *head = new DataNode("head");
    Node *body = new DataNode("body");

    head->add(new DataNode("div"));
    head->add(new TextNode("title text"));
    body->add(new DataNode("p"));
    body->add(new DataNode("div"));
    body->add(new DataNode("div"));
    body->add(new TextNode("body text"));

    root->add(head);
    root->add(body);
    root->add(new TextNode("a short text node for testing"));
    

    root->prettyPrint();

    return 0;
}
