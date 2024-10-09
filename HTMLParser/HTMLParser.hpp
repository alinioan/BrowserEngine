#ifndef HTMLPARSERH
#define HTMLPARSERH

#include <vector>
#include <string>

#include "Document.hpp"
#include "Node.hpp"
#include "HTMLTokenizer.hpp"
#include "Tokens/HTMLToken.hpp"

class HTMLParser
{
private:
    enum InsertionMode
    {
        initialMode,
        beforeHTMLMode,
        beforeHeadMode,
        inHeadMode,
        inHeadNoscriptMode,
        afterHeadMode,
        inBodyMode,
        textMode,
        inTableMode,
        inTableTextMode,
        inCaptionMode,
        inColumnGroupMode,
        inTableBodyMode,
        inRowMode,
        inCellMode,
        inSelectMode,
        inSelect_inTableMode,
        inForeignContentMode,
        afterBodyMode,
        inFramesetMode,
        afterFramesetMode,
        afterAfterBodyMode,
        afterAfterFramesetMode
    };
    HTMLTokenizer tokenizer;
    InsertionMode state;
    std::vector<Node *> open_elements;
    Document document;

    Node * insert_data_node(HTMLToken *token, Node *crt_node);

public:
    HTMLParser();
    ~HTMLParser();
    Document create_document(const std::string &input);
    Node *creatNodeFromToken(HTMLToken *token);
};

#endif
