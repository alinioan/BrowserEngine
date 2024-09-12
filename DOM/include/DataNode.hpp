#ifndef __DATANODE__
#define __DATANODE__

#include <string>
#include <map>
#include "Node.hpp"

typedef std::map<std::string, std::string> AttrMap;

class DataNode : public Node {
private:
    std::string tagName;
    AttrMap attrs;

public:
    std::string toString() override;
    DataNode(std::string tagName);
    ~DataNode();
};

#endif
