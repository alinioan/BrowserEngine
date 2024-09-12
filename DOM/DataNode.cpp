#include "include/DataNode.hpp"

DataNode::DataNode(std::string tagName) {
    this->tagName = tagName;
    this->setType(DATA);
}

DataNode::~DataNode() {}

std::string DataNode::toString() {
    std::string node = "DataNode{tagName=" + tagName + ", attrs={";
    for (auto set : attrs) {
        node.append(set.first + ":" + set.second + ", ");
    }
    if (!attrs.empty()) {
        node = node.substr(0, node.size() - 2);
    }
    node.append("}}");
    return node;
}
