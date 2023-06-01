#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

class Node {
public:
    virtual ~Node() = default;
    virtual std::string toJSON() const = 0;
};

class ValueNode : public Node {
public:
    std::string value;
    ValueNode(const std::string &val) : value(val) {}

    std::string toJSON() const override;
};

class ArrayNode : public Node {
public:
    std::vector<std::unique_ptr<Node>> values;

    std::string toJSON() const override;
};

//ObjectNode is anything and the entirety of the data contained within curly braces {}.
class ObjectNode : public Node {
public:
    std::vector<std::pair<std::string, std::unique_ptr<Node>>> children;

    std::string toJSON() const override;
};

#endif
