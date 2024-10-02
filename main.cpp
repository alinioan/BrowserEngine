#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "HTMLParser/HTMLTokenizer.hpp"

int main(int argc, char const *argv[])
{
    HTMLTokenizer tokenizer;
    std::ifstream file("test.html");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::stringstream bufferStream;
    bufferStream << file.rdbuf();
    std::string buffer = bufferStream.str();
    std::cout << buffer << std::endl;
    std::vector<HTMLToken*> tokens = tokenizer.tokenizeString(buffer);
    std::cout << tokens.size() << " tokens\n";
    for (auto token : tokens)
    {
        std::cout<<"a";
        if (token->getType() == HTMLToken::TokenType::StartTag || token->getType() == HTMLToken::TokenType::EndTag)
        {
            std::cout << token->getName() << ' ' << token->getType() << '\n';
        }
        else
            std::cout << token->getType() << '\n';
    }



    return 0;
}
