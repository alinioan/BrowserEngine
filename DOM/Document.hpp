#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>

#include "Node.hpp"

class Document {
private:
	bool quirks_mode;
	std::string doctype;
	Node *root;

public:
	Document();
	~Document();

	bool is_quirks_mode() const;
	void set_quirks_mode(bool quirks_mode);
	std::string get_doctype() const;
	void set_doctype(const std::string &doctype);
	Node * get_root() const;
	void set_root(Node *root);
};



#endif //DOCUMENT_H
