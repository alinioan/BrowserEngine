#ifndef DATANODE_H
#define DATANODE_H

#include <string>
#include <map>

#include "Node.hpp"
#include "../HTMLParser/Tokens/HTMLToken.hpp"

typedef std::map<std::string, std::string> AttrMap;

class DataNode : public Node
{
public:
	std::string to_string() override;
	DataNode(const std::string &tag_name, const AttrMap &attrs, bool self_closing);
	DataNode(const std::string &tag_name);
	DataNode(HTMLToken *token);
	~DataNode();

	std::string get_name() override;

private:
	std::string tag_name;
	AttrMap attrs;
	bool self_closing = false;
};

#endif
