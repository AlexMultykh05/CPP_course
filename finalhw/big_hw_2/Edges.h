#ifndef INC_11_12TH_HW_EDGES_H
#define INC_11_12TH_HW_EDGES_H

#include <ostream>
#include "Node.h"
#include "Edge.h"
#include "Identifier.h"
#include "Exception.h"
#include "GraphType.h"
#include "Constants.h"

template<typename NData, typename EData>
class Edges {
private:
    lib::Array<Edge<EData>> edges_;
    lib::Array<lib::Array<Edge<EData> *>> &adjMatrix_;
    bool directed_;

    class Request;

    void updateMatrix(Identifier source, Identifier target);

    void checkIdValidity(Identifier id) const;

    void checkExistingId(Identifier id) const;

    void tryAddingEdge(Edge<EData> &edge);

    void checkID(Identifier id) const;

    void checkSource(Identifier source) const;

    void checkTarget(Identifier target) const;

    void checkEdgeBetween(Identifier source, Identifier target) const;

    void checkEdgeBetweenExistence(Identifier source, Identifier target) const;

public:
    Edges(lib::Array<lib::Array<Edge<EData> *>> &adjMatrix, bool directed);

    void print(std::ostream &stream = std::cout) const;

    void printMatrix(std::ostream &stream = std::cout) const;

    void swap(Edges<NData, EData> &edges);

    void clear();

    Edge<EData> &add(Identifier id, Identifier source, Identifier target, const EData &data);

    Edge<EData> &add(Identifier id, Identifier source, Identifier target, EData &&data);

    Edge<EData> &add(Identifier source, Identifier target, const EData &data);

    Edge<EData> &add(Identifier source, Identifier target, EData &&data);

    size_t size() const;

    bool exists(Identifier id) const;

    bool exists(Identifier source, Identifier target) const;

    Edge<EData> &get(Identifier id);

    const Edge<EData> &get(Identifier id) const;

    Edge<EData> &get(Identifier source, Identifier target);

    const Edge<EData> &get(Identifier source, Identifier target) const;

    bool isDirected() const;

    Request operator[](Identifier source);

    const Request operator[](Identifier source) const;

    typename lib::Array<Edge<EData>>::iterator begin();

    typename lib::Array<Edge<EData>>::iterator end();

    typename lib::Array<Edge<EData>>::const_iterator begin() const;

    typename lib::Array<Edge<EData>>::const_iterator end() const;

};

// -------------- Implementation --------------

template<typename NData, typename EData>
Edges<NData, EData>::Edges(lib::Array<lib::Array<Edge<EData> *>> &adjMatrix, bool directed) : adjMatrix_(adjMatrix),
                                                                                              directed_(directed) {}

template<typename NData, typename EData>
void Edges<NData, EData>::print(std::ostream &stream) const {
    for (size_t i = 0; i < edges_.size(); ++i) {
        stream << edges_[i] << std::endl;
    }
}

template<typename NData, typename EData>
std::ostream &operator<<(std::ostream &stream, const Edges<NData, EData> &edges) {
    edges.print(stream);
    return stream;
}

template<typename NData, typename EData>
void Edges<NData, EData>::printMatrix(std::ostream &stream) const {
    for (size_t i = 0; i != adjMatrix_.size(); ++i) {
        for (size_t j = 0; j != adjMatrix_[0].size(); ++j) {
            bool last_col = false;
            if (j == adjMatrix_.size() - 1) {
                last_col = true;
            }
            if (adjMatrix_[i][j] == nullptr) {
                stream << "-" << (last_col ? "" : "|");
                continue;
            }
            stream << adjMatrix_[i][j]->getId() << (last_col ? "" : "|");
        }
        if (i != adjMatrix_.size() - 1) {
            stream << std::endl;
        }
    }
    stream << std::endl;
}

template<typename NData, typename EData>
void Edges<NData, EData>::swap(Edges<NData, EData> &edges) {
    lib::swap(edges_, edges.edges_);
}

template<typename NData, typename EData>
void Edges<NData, EData>::clear() {
    edges_.clear();
}


template<typename NData, typename EData>
void Edges<NData, EData>::updateMatrix(Identifier source, Identifier target) {
    if (directed_) {
        adjMatrix_[source][target] = &edges_[edges_.size() - 1];
        if (source != target) {
            adjMatrix_[target][source] = nullptr;
        }
    } else {
        adjMatrix_[source][target] = &edges_[edges_.size() - 1];
        adjMatrix_[target][source] = &edges_[edges_.size() - 1];
    }
}

// ------------------ Check ------------------

template<typename NData, typename EData>
void Edges<NData, EData>::checkIdValidity(Identifier id) const {
    if (id != edges_.size()) {
        throw IdentifierException("Invalid edge identifier " + std::to_string(id) + " requested");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkExistingId(Identifier id) const {
    if (id < edges_.size()) {
        throw ConflictException("Edge with identifier " + std::to_string(id) + " already exists");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::tryAddingEdge(Edge<EData> &edge) {
    try {
        edges_.push_back(edge);
    } catch (...) {
        throw MemoryException(NO_MEMORY_EDGE);
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkID(Identifier id) const {
    if (id >= edges_.size()) {
        throw ElementException("Edge with identifier " + std::to_string(id) + " does not exist");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkSource(Identifier source) const {
    if (source >= adjMatrix_.size()) {
        throw ElementException("Source node with identifier " + std::to_string(source) + " does not exist");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkTarget(Identifier target) const {
    if (target >= adjMatrix_[0].size()) {
        throw ElementException("Target node with identifier " + std::to_string(target) + " does not exist");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkEdgeBetween(Identifier source, Identifier target) const {
    if (adjMatrix_[source][target] != nullptr) {
        throw ConflictException("Edge between nodes " + std::to_string(source) + " and " + std::to_string(target) + " already exists");
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::checkEdgeBetweenExistence(Identifier source, Identifier target) const {
    if (adjMatrix_[source][target] == nullptr) {
        throw ElementException("Edge between nodes " + std::to_string(source) + " and " + std::to_string(target) + " does not exist");
    }
}

// ------------------ Add ------------------

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::add(Identifier id, Identifier source, Identifier target, const EData &data) {
    checkExistingId(id);
    checkIdValidity(id);
    checkSource(source);
    checkTarget(target);
    checkEdgeBetween(source, target);

    Edge<EData> edge(source, target, data, id);

    tryAddingEdge(edge);

    updateMatrix(source, target);

    return edges_[edges_.size() - 1];
}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::add(Identifier id, Identifier source, Identifier target, EData &&data) {
    checkExistingId(id);
    checkIdValidity(id);
    checkSource(source);
    checkTarget(target);
    checkEdgeBetween(source, target);

    Edge<EData> edge(source, target, data, id);

    tryAddingEdge(edge);

    updateMatrix(source, target);

    return edges_[edges_.size() - 1];
}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::add(Identifier source, Identifier target, const EData &data) {
    checkSource(source);
    checkTarget(target);
    checkEdgeBetween(source, target);

    Edge<EData> edge(source, target, data, edges_.size());

    tryAddingEdge(edge);

    updateMatrix(source, target);

    return edges_[edges_.size() - 1];
}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::add(Identifier source, Identifier target, EData &&data) {
    checkSource(source);
    checkTarget(target);
    checkEdgeBetween(source, target);

    Edge<EData> edge(source, target, data, edges_.size());

    tryAddingEdge(edge);

    updateMatrix(source, target);

    return edges_[edges_.size() - 1];
}

// ------------------ Size/Exists/Get ------------------

template<typename NData, typename EData>
size_t Edges<NData, EData>::size() const {
    return edges_.size();
}

template<typename NData, typename EData>
bool Edges<NData, EData>::exists(Identifier id) const {
    return id < edges_.size();
}

template<typename NData, typename EData>
bool Edges<NData, EData>::exists(Identifier source, Identifier target) const {
    checkSource(source);
    checkTarget(target);
    return adjMatrix_[source][target] != nullptr;
}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::get(Identifier id) {
    checkID(id);

    return edges_[id];
}

template<typename NData, typename EData>
const Edge<EData> &Edges<NData, EData>::get(Identifier id) const {
    checkID(id);

    return edges_[id];
}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::get(Identifier source, Identifier target) {
    checkSource(source);
    checkTarget(target);
    checkEdgeBetweenExistence(source, target);

    return *adjMatrix_[source][target];
}

template<typename NData, typename EData>
const Edge<EData> &Edges<NData, EData>::get(Identifier source, Identifier target) const {
    checkSource(source);
    checkTarget(target);
    checkEdgeBetweenExistence(source, target);

    return *adjMatrix_[source][target];
}

template<typename NData, typename EData>
bool Edges<NData, EData>::isDirected() const {
    return directed_;
}

// ------------------ Request/operator[] ------------------

template<typename NData, typename EData>
class Edges<NData, EData>::Request {
    friend class Edges<NData, EData>;

private:
    const Edges<NData, EData> &edges_;
    Identifier source_{};

    Request(const Edges<NData, EData> &edges, Identifier source);

public:
    Edge<EData> &operator[](Identifier target);

    const Edge<EData> &operator[](Identifier target) const;
};

template<typename NData, typename EData>
Edges<NData, EData>::Request::Request(const Edges<NData, EData> &edges, Identifier source) : edges_(edges),
                                                                                             source_(source) {}

template<typename NData, typename EData>
Edge<EData> &Edges<NData, EData>::Request::operator[](Identifier target) {
    auto &new_edges = const_cast<Edges<NData, EData> &>(edges_);

    return new_edges.get(source_, target);
}

template<typename NData, typename EData>
const Edge<EData> &Edges<NData, EData>::Request::operator[](Identifier target) const {
    return edges_.get(source_, target);
}

template<typename NData, typename EData>
typename Edges<NData, EData>::Request Edges<NData, EData>::operator[](Identifier source) {
    return Request(*this, source);
}

template<typename NData, typename EData>
const typename Edges<NData, EData>::Request Edges<NData, EData>::operator[](Identifier source) const {
    return Request(*this, source);
}

// ------------------ Iterators ------------------

template<typename NData, typename EData>
typename lib::Array<Edge<EData>>::iterator Edges<NData, EData>::begin() {
    return edges_.begin();
}

template<typename NData, typename EData>
typename lib::Array<Edge<EData>>::iterator Edges<NData, EData>::end() {
    return edges_.end();
}

template<typename NData, typename EData>
typename lib::Array<Edge<EData>>::const_iterator Edges<NData, EData>::begin() const {
    return edges_.begin();
}

template<typename NData, typename EData>
typename lib::Array<Edge<EData>>::const_iterator Edges<NData, EData>::end() const {
    return edges_.end();
}

#endif //INC_11_12TH_HW_EDGES_H
