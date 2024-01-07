#ifndef INC_11_12TH_HW_EDGE_H
#define INC_11_12TH_HW_EDGE_H

#include <ostream>
#include "Graph.h"
#include "Node.h"
#include "Identifier.h"

template<typename EData>
class Edge {
private:
    Identifier source_;
    Identifier target_;
    EData data_;
    Identifier id_;

public:
    Edge(Identifier from, Identifier to, EData data, Identifier id);

    Identifier getId() const;

    Identifier getSource() const;

    Identifier getTarget() const;

    EData &getData();

    const EData &getData() const;

};

template<typename EData>
Edge<EData>::Edge(Identifier from, Identifier to, EData data, Identifier id) : source_(from), target_(to), data_(data),
                                                                               id_(id) {
}

template<typename EData>
Identifier Edge<EData>::getId() const {
    return id_;
}

template<typename EData>
Identifier Edge<EData>::getSource() const {
    return source_;
}

template<typename EData>
Identifier Edge<EData>::getTarget() const {
    return target_;
}

template<typename EData>
EData &Edge<EData>::getData() {
    return data_;
}

template<typename EData>
const EData &Edge<EData>::getData() const {
    return data_;
}

template<typename EData>
std::ostream &operator<<(std::ostream &stream, const Edge<EData> &edge) {
    stream << "edge " << "(" << edge.getSource() << ")-" << "[" << edge.getId() << " {" << edge.getData() << "}"
           << "]->("
           << edge.getTarget() << ")";
    return stream;
}

#endif //INC_11_12TH_HW_EDGE_H
