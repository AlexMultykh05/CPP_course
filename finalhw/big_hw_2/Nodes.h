#ifndef INC_11_12TH_HW_NODES_H
#define INC_11_12TH_HW_NODES_H

#include <ostream>
#include "Node.h"
#include "Edge.h"
#include "Identifier.h"
#include "Exception.h"
#include "Constants.h"

template<typename NData, typename EData>
class Nodes {
private:
    lib::Array<Node<NData>> nodes_;
    lib::Array<lib::Array<Edge<EData> *>> &adjMatrix_;

    void tryAddingNode(Node<NData> &node);

    void resizeMatrix();

    void checkIdValidity(Identifier id) const;

    void checkExistingId(Identifier id) const;

    void checkID(Identifier id) const;

public:
    Nodes(lib::Array<lib::Array<Edge<EData> *>> &adjMatrix);

    void print(std::ostream &stream = std::cout) const;

    void swap(Nodes<NData, EData> &nodes);

    void clear();

    Node<NData> &add(Identifier id, const NData &data);

    Node<NData> &add(Identifier id, NData &&data);

    Node<NData> &add(const NData &data);

    Node<NData> &add(NData &&data);

    size_t size() const;

    bool exists(Identifier id) const;

    Node<NData> &get(Identifier id);

    const Node<NData> &get(Identifier id) const;

    Node<NData> &operator[](size_t id);

    const Node<NData> &operator[](size_t id) const;

    typename lib::Array<Node<NData>>::iterator begin();

    typename lib::Array<Node<NData>>::iterator end();

    typename lib::Array<Node<NData>>::const_iterator begin() const;

    typename lib::Array<Node<NData>>::const_iterator end() const;

};

// -------------- Implementation --------------

template<typename NData, typename EData>
Nodes<NData, EData>::Nodes(lib::Array<lib::Array<Edge<EData> *>> &adjMatrix) : adjMatrix_(adjMatrix) {}

template<typename NData, typename EData>
void Nodes<NData, EData>::print(std::ostream &stream) const {
    for (size_t i = 0; i < nodes_.size(); ++i) {
        stream << nodes_[i] << std::endl;
    }
}

template<typename NData, typename EData>
std::ostream &operator<<(std::ostream &stream, const Nodes<NData, EData> &nodes) {
    nodes.print(stream);
    return stream;
}

template<typename NData, typename EData>
void Nodes<NData, EData>::swap(Nodes<NData, EData> &nodes) {
    lib::swap(nodes_, nodes.nodes_);
}

template<typename NData, typename EData>
void Nodes<NData, EData>::clear() {
    nodes_.clear();
}

// ------------------ Check ------------------

template<typename NData, typename EData>
void Nodes<NData, EData>::tryAddingNode(Node<NData> &node) {
    try {
        nodes_.push_back(node);
    } catch (...) {
        throw MemoryException(NO_MEMORY_NODE);
    }
}

template<typename NData, typename EData>
void Nodes<NData, EData>::resizeMatrix() {
    try {
        for (auto &&row: adjMatrix_) {
            row.push_back(nullptr);
        }
        adjMatrix_.push_back(lib::Array<Edge<EData> *>(adjMatrix_.size() + 1, nullptr));
    } catch (...) {
        throw MemoryException(NO_MEMORY_MATRIX);
    }
}

template<typename NData, typename EData>
void Nodes<NData, EData>::checkIdValidity(Identifier id) const {
    if (id != nodes_.size()) {
        throw IdentifierException("Invalid node identifier " + std::to_string(id) + " requested");
    }
}

template<typename NData, typename EData>
void Nodes<NData, EData>::checkExistingId(Identifier id) const {
    if (id < nodes_.size()) {
        throw ConflictException("Node with identifier " + std::to_string(id) + " already exists");
    }
}

template<typename NData, typename EData>
void Nodes<NData, EData>::checkID(Identifier id) const {
    if (id >= nodes_.size()) {
        throw ElementException("Node with identifier " + std::to_string(id) + " does not exist");
    }
}

// ------------------ Add ------------------

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::add(Identifier id, const NData &data) {
    checkExistingId(id);

    checkIdValidity(id);

    Node<NData> node(data, id);

    tryAddingNode(node);

    resizeMatrix();

    return nodes_[nodes_.size() - 1];
}

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::add(Identifier id, NData &&data) {
    checkExistingId(id);

    checkIdValidity(id);

    Node<NData> node(data, id);

    tryAddingNode(node);

    resizeMatrix();

    return nodes_[nodes_.size() - 1];
}

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::add(const NData &data) {
    Node<NData> node(data, nodes_.size());

    tryAddingNode(node);

    resizeMatrix();

    return nodes_[nodes_.size() - 1];
}

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::add(NData &&data) {
    Node<NData> node(data, nodes_.size());

    tryAddingNode(node);

    resizeMatrix();

    return nodes_[nodes_.size() - 1];
}

// ------------------ Size/Exists/Get/Operator[] ------------------

template<typename NData, typename EData>
size_t Nodes<NData, EData>::size() const {
    return nodes_.size();
}

template<typename NData, typename EData>
bool Nodes<NData, EData>::exists(Identifier id) const {
    return id < nodes_.size();
}

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::get(Identifier id) {
    checkID(id);

    return nodes_[id];
}

template<typename NData, typename EData>
const Node<NData> &Nodes<NData, EData>::get(Identifier id) const {
    checkID(id);

    return nodes_[id];
}

template<typename NData, typename EData>
Node<NData> &Nodes<NData, EData>::operator[](size_t id) {
    checkID(id);

    return nodes_[id];
}

template<typename NData, typename EData>
const Node<NData> &Nodes<NData, EData>::operator[](size_t id) const {
    checkID(id);

    return nodes_[id];
}

// ------------------ Iterators ------------------

template<typename NData, typename EData>
typename lib::Array<Node<NData>>::iterator Nodes<NData, EData>::begin() {
    return nodes_.begin();
}

template<typename NData, typename EData>
typename lib::Array<Node<NData>>::iterator Nodes<NData, EData>::end() {
    return nodes_.end();
}

template<typename NData, typename EData>
typename lib::Array<Node<NData>>::const_iterator Nodes<NData, EData>::begin() const {
    return nodes_.begin();
}

template<typename NData, typename EData>
typename lib::Array<Node<NData>>::const_iterator Nodes<NData, EData>::end() const {
    return nodes_.end();
}

#endif //INC_11_12TH_HW_NODES_H
