#include "Node.h"
#include <iostream>
std::string ArrayNode::toJSON() const {
    std::string result = "[";
    for (auto &value: values) {
        if (result.size() > 1) result += ", ";
        result += value->toJSON();
    }
    result += "]";
    return result;
}

std::string ValueNode::toJSON() const {
    // If the value can be converted to a simple int. Paradox's floats, ie. 123.000
    // will be returned as a string(for now anyways).
    if (std::all_of(value.begin(), value.end(), ::isdigit))
        return value;
    else {
        if(value.find('"')!=-1){
            return value;
        }

        return '"' + value + '"';
    }
}

std::string ObjectNode::toJSON() const {
    std::string result = "{";
    for (const auto &pair: children) {
        //We initialize result with length 1. If it's
        // larger than that, it means that the first element has already been added.
        if (result.size() > 1) result += ", ";
        //first -> key, second -> value(<Node>)
        result += '"' + pair.first + "\": " + pair.second->toJSON();
    }
    result += "}";
    return result;
}