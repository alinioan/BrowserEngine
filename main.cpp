#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Document.hpp"
#include "HTMLParser.hpp"
#include "HTMLParser/HTMLTokenizer.hpp"

int main(int argc, char const *argv[])
{
    HTMLTokenizer tokenizer;
    std::ifstream file("../test.html");
    std::stringstream bufferStream;
    bufferStream << file.rdbuf();
    std::string buffer = bufferStream.str();
    std::cout << buffer << std::endl;
    std::vector<HTMLToken*> tokens = tokenizer.tokenizeString(buffer);
    std::cout << tokens.size() << " tokens\n";
    HTMLParser parser;
    Document document = parser.create_document(buffer);
    document.get_root()->pretty_print();
    return 0;
}
