#include "DataNode.hpp"
#include "../HTMLParser/Tokens/HTMLToken.hpp"

DataNode::DataNode(const std::string &tag_name)
{
    this->tag_name = tag_name;
    this->set_type(DATA);
    this->self_closing = false;
}

DataNode::DataNode(const std::string &tag_name, const AttrMap &attrs, bool self_closing)
{
    this->tag_name = tag_name;
    this->set_type(DATA);
    this->attrs = attrs;
    this->self_closing = self_closing;
}

DataNode::DataNode(HTMLToken *token)
{
    tag_name = token->getName();
    attrs = token->getAttributes();
    self_closing = token->isSelfClosing();
}

DataNode::~DataNode() {}

std::string DataNode::to_string()
{
    std::string node = "DataNode{tagName=" + tag_name + ", attrs={";
    for (auto set : attrs)
    {
        node.append(set.first + ":" + set.second + ", ");
    }
    if (!attrs.empty())
    {
        node = node.substr(0, node.size() - 2);
    }
    node.append("}}");
    return node;
}
