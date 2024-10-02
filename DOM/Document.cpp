#include "Document.hpp"

Document::Document()
{
}

Document::~Document()
{
}

bool Document::is_quirks_mode() const
{
	return quirks_mode;
}

void Document::set_quirks_mode(bool quirks_mode)
{
	this->quirks_mode = quirks_mode;
}

std::string Document::get_doctype() const
{
	return doctype;
}

void Document::set_doctype(const std::string &doctype)
{
	this->doctype = doctype;
}

Node * Document::get_root() const
{
	return root;
}

void Document::set_root(Node *root)
{
	this->root = root;
}




