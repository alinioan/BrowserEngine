#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

enum NodeType
{
	DATA,
	TEXT
};

class Node
{
private:
	std::vector<Node *> children;
	Node *parent;
	NodeType type;

	void rec_pretty_print(Node *node, const std::string &indent);

public:
	virtual ~Node();

	virtual std::string to_string() = 0;

	void add(Node *child);

	void pretty_print();

	std::vector<Node *> get_children();

	NodeType get_type() const;

	void set_children(const std::vector<Node *> &children);

	void set_type(NodeType type);

	Node *get_parent() const;

	void set_parent(Node *parent);

	// DataNode
	virtual std::string get_name() { return ""; }

	// TextNode
	virtual void append_character(char character)
	{
	}
};

#endif
