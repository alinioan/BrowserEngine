#include "DOM/include/Node.hpp"
#include "DOM/include/DataNode.hpp"
#include "DOM/include/TextNode.hpp"
#include "HTMLParser/HTMLTokenizer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

    HTMLTokenizer tokenzier;
    std::ifstream file("test.html");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::vector<HTMLToken*> tokens = tokenzier.tokenizeString(buffer.str());
    std::cout << "\n\n\n";
    for (auto token : tokens)
    {
        if (token->getType() == HTMLToken::TokenType::StartTag || token->getType() == HTMLToken::TokenType::EndTag)
        {
            std::cout << token->getName() << ' ' << token->getType() << '\n';
        }
        else
            std::cout << token->getType() << '\n';
    }

    return 0;
}
