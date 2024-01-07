#ifndef INC_11_12TH_HW_NODE_H
#define INC_11_12TH_HW_NODE_H

#include <ostream>
#include "Graph.h"
#include "Identifier.h"


template<typename NData>
class Node {
private:
    NData data_;
    Identifier id_;

public:
    Node(NData data_, Identifier id_);

    Identifier getId() const;

    NData &getData();

    const NData &getData() const;
};

template<typename NData>
Node<NData>::Node(NData data, Identifier id) : data_(data), id_(id) {
}

template<typename NData>
Identifier Node<NData>::getId() const {
    return id_;
}

template<typename NData>
NData &Node<NData>::getData() {
    return data_;
}

template<typename NData>
const NData &Node<NData>::getData() const {
    return data_;
}

template<typename NData>
std::ostream &operator<<(std::ostream &stream, const Node<NData> &node) {
    stream << "node " << "(" << node.getId() << " {" << node.getData() << "}" << ")";
    return stream;
}

#endif //INC_11_12TH_HW_NODE_H
