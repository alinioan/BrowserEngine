#include <string>

#include "HTMLParser.hpp"

#include <set>

#include "TagToken.hpp"
#include "Node.hpp"
#include "DataNode.hpp"
#include "TextNode.hpp"

std::set<std::string> valid_open_tags = {"address", "article", "aside", "blockquote", "center",
    "details", "dialog", "dir", "div", "dl", "fieldset", "figcaption", "figure", "footer",
    "header", "hgroup", "main", "menu", "nav", "ol", "p", "search", "section", "summary", "ul"};

std::set<std::string> valid_close_tags = {"address", "article", "aside", "blockquote", "button", "center",
    "details", "dialog", "dir", "div", "dl", "fieldset", "figcaption", "figure", "footer",
    "header", "hgroup", "listing", "main", "menu", "nav", "ol", "pre", "search", "section",
    "summary", "ul"};

std::set<std::string> header_tags = {"h1", "h2", "h3", "h4", "h5", "h6"};

HTMLParser::HTMLParser()
{
}

HTMLParser::~HTMLParser()
{
}

Node *HTMLParser::insert_data_node(HTMLToken *token, Node *crt_node)
{
    Node *new_node = new DataNode(token);
    open_elements.push_back(new_node);
    if (crt_node != nullptr)
        crt_node->add(new_node);
    else
        document.set_root(new_node);
    return new_node;
}

Document HTMLParser::create_document(const std::string &input)
{
    state = initialMode;
    Node *crt_node = nullptr;
    std::vector<HTMLToken *> tokens = tokenizer.tokenizeString(input);
    for (int cursor = 0; cursor < tokens.size(); cursor++)
    {
        auto token = tokens.at(cursor);
        switch (state)
        {
        case initialMode:
            if (token->getType() == HTMLToken::TokenType::DOCTYPE)
            {
                document.set_doctype(token->getName());
                state = beforeHTMLMode;
                break;
            }
        // TODO: check for comments and add comment node.
            state = beforeHTMLMode;
            break;
        case beforeHTMLMode:
        {
            if (token->getType() == HTMLToken::TokenType::StartTag)
            {
                crt_node = insert_data_node(token, crt_node);
                state = beforeHeadMode;
                break;
            }
            if (token->getType() == HTMLToken::TokenType::EndTag &&
                !(token->getName() == "head" ||
                  token->getName() == "body" ||
                  token->getName() == "html" ||
                  token->getName() == "br"))
                break;

            // Add html element
            Node *html_node = new DataNode("html");
            open_elements.push_back(html_node);
            if (crt_node != nullptr)
                crt_node->add(html_node);
            else
                document.set_root(html_node);
            crt_node = html_node;
            state = beforeHeadMode;
        }
            break;
        case beforeHeadMode:
        {
            if (token->getType() == HTMLToken::TokenType::StartTag && token->getName() == "head")
            {
                crt_node = insert_data_node(token, crt_node);
                state = inHeadMode;
                break;
            }
            if (token->getType() == HTMLToken::TokenType::EndTag &&
                !(token->getName() == "head" ||
                  token->getName() == "body" ||
                  token->getName() == "html" ||
                  token->getName() == "br"))
                break;

            // Add head element
            Node *head_node = new DataNode("head");
            open_elements.push_back(head_node);
            if (crt_node != nullptr)
                crt_node->add(head_node);
            else
                document.set_root(head_node);
            crt_node = head_node;
            state = inHeadMode;
        }
            break;
        case inHeadMode:
            if (token->getType() == HTMLToken::TokenType::StartTag &&
                (token->getName() == "base" || token->getName() == "basefont" ||
                 token->getName() == "bgsound" || token->getName() == "link"))
            {
                crt_node = insert_data_node(token, crt_node);
                open_elements.pop_back();
                crt_node = crt_node->get_parent();
            }
            if (token->getType() == HTMLToken::TokenType::EndTag && token->getName() == "head")
            {
                open_elements.pop_back();
                crt_node = crt_node->get_parent();
                state = afterHeadMode;
            }
            break;
        case afterHeadMode:
            if (token->getType() == HTMLToken::TokenType::StartTag)
            {
                if (token->getName() == "body")
                {
                    crt_node = insert_data_node(token, crt_node);
                    state = inBodyMode;
                    break;
                }
                if (token->getName() == "frameset")
                {
                    crt_node = insert_data_node(token, crt_node);
                    state = inFramesetMode;
                    break;
                }
            }
            break;
        case inBodyMode:
            if (token->getType() == HTMLToken::TokenType::Character)
            {
                if (crt_node->get_children().empty() || crt_node->get_children().back()->get_type() != TEXT)
                {
                    Node *text = new TextNode(token->get_char());
                    crt_node->add(text);
                }
                else
                    crt_node->get_children().back()->append_character(token->get_char());
                break;
            }
            if (token->getType() == HTMLToken::TokenType::StartTag)
            {
                if ((token->getName() == "base" || token->getName() == "basefont" ||
                    token->getName() == "bgsound" || token->getName() == "link"))
                {
                    crt_node = insert_data_node(token, crt_node);
                    open_elements.pop_back();
                    crt_node = crt_node->get_parent();
                }
                else if (valid_open_tags.count(token->getName()) != 0)
                {
                    // TODO: check if is in button scope
                    crt_node = insert_data_node(token, crt_node);
                }
                else if (header_tags.count(token->getName()) != 0)
                {
                    if (header_tags.count(crt_node->get_name()) != 0)
                    {
                        open_elements.pop_back();
                        crt_node = crt_node->get_parent();
                    }
                    crt_node = insert_data_node(token, crt_node);
                }

            }
            else if (token->getType() == HTMLToken::TokenType::EndTag)
            {
                if (token->getName() == "body")
                    state = afterBodyMode;
                else if (token->getName() == "html")
                {
                    state = afterBodyMode;
                    cursor--;
                }
                else if (valid_close_tags.count(token->getName()) != 0)
                {
                    while (open_elements.back()->get_name() != token->getName())
                    {
                        open_elements.pop_back();
                        crt_node = crt_node->get_parent();
                    }
                    open_elements.pop_back();
                    crt_node = crt_node->get_parent();
                }
                else if (token->getName() == "p" || token->getName() == "li")
                {
                    // TODO: If the stack of open elements does not have a p element in button scope,
                    // then this is a parse error; insert an HTML element for a "p" start tag token with no attributes.
                    // TODO: the same scope checking for li tag
                    while (open_elements.back()->get_name() != token->getName())
                    {
                        open_elements.pop_back();
                        crt_node = crt_node->get_parent();
                    }
                    open_elements.pop_back();
                    crt_node = crt_node->get_parent();
                }
                else if (header_tags.count(token->getName()) != 0)
                {
                    while (header_tags.count(open_elements.back()->get_name()) != 0)
                    {
                        open_elements.pop_back();
                        crt_node = crt_node->get_parent();
                    }
                    open_elements.pop_back();
                    crt_node = crt_node->get_parent();
                }
            }
            break;
        case afterBodyMode:
            if (token->getType() == HTMLToken::TokenType::EndTag && token->getName() == "html")
            {
                state = afterAfterBodyMode;
                break;
            }
            // state = inBodyMode;
            // cursor--;
            break;
        case afterAfterBodyMode:
            // state = inBodyMode;
            // cursor--;
            break;
        default:
            break;
        }
    }
    return document;
}
