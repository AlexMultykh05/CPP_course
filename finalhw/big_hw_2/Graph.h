#ifndef INC_11_12TH_HW_GRAPH_H
#define INC_11_12TH_HW_GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Node.h"
#include "Nodes.h"
#include "Edge.h"
#include "Edges.h"
#include "Exception.h"
#include "Identifier.h"
#include "GraphType.h"
#include "Constants.h"


template<typename NData, typename EData>
class Graph {
protected:
    lib::Array<lib::Array<Edge<EData> *>> adjMatrix_;
    Nodes<NData, EData> nodes_;
    Edges<NData, EData> edges_;

    void parse(std::string &line);

public:
    Graph(bool directed);

    Graph(const Graph<NData, EData> &graph);

    Graph(Graph<NData, EData> &&graph) noexcept;

    Graph<NData, EData> &operator=(const Graph<NData, EData> &graph);

    Graph<NData, EData> &operator=(Graph<NData, EData> &&graph) noexcept;

    Nodes<NData, EData> &nodes();

    Edges<NData, EData> &edges();

    const Nodes<NData, EData> &nodes() const;

    const Edges<NData, EData> &edges() const;

    void print(std::ostream &stream = std::cout) const;

    void print(const std::string &filename) const;

    void import(std::istream &stream = std::cin);

    void import(const std::string &filename);

};

// ------------------ Graph implementation ------------------


// ------------------ Graph constructors/operator= ------------------

template<typename NData, typename EData>
Graph<NData, EData>::Graph(bool directed) : nodes_(adjMatrix_), edges_(adjMatrix_, directed) {}

template<typename NData, typename EData>
Graph<NData, EData>::Graph(const Graph<NData, EData> &graph) : nodes_(adjMatrix_),
                                                               edges_(adjMatrix_, graph.edges_.isDirected()) {
    for (auto &node: graph.nodes_) {
        try {
            nodes_.add(node.getData());
        } catch (...) {
            nodes_.clear();
            throw;
        }
    }

    for (auto &edge: graph.edges_) {
        try {
            edges_.add(edge.getSource(), edge.getTarget(), edge.getData());
        } catch (...) {
            edges_.clear();
            throw;
        }
    }
}

template<typename NData, typename EData>
Graph<NData, EData>::Graph(Graph<NData, EData> &&graph) noexcept : nodes_(adjMatrix_),
                                                                   edges_(adjMatrix_, graph.edges_.isDirected()) {
    nodes_.swap(graph.nodes_);
    edges_.swap(graph.edges_);
    lib::swap(adjMatrix_, graph.adjMatrix_);
}

template<typename NData, typename EData>
Graph<NData, EData> &Graph<NData, EData>::operator=(const Graph<NData, EData> &graph) {
    edges_.clear();
    nodes_.clear();

    for (auto &node: graph.nodes_) {
        try {
            nodes_.add(node.getData());
        } catch (...) {
            nodes_.clear();
            throw;
        }
    }

    for (auto &edge: graph.edges_) {
        try {
            edges_.add(edge.getSource(), edge.getTarget(), edge.getData());
        } catch (...) {
            edges_.clear();
            throw;
        }
    }

    return *this;
}

template<typename NData, typename EData>
Graph<NData, EData> &Graph<NData, EData>::operator=(Graph<NData, EData> &&graph) noexcept {
    if (this == &graph) {
        return *this;
    }
    nodes_.clear();
    edges_.clear();
    nodes_.swap(graph.nodes_);
    edges_.swap(graph.edges_);
    lib::swap(adjMatrix_, graph.adjMatrix_);

    return *this;
}

// ------------------ Graph nodes/edges methods ------------------

template<typename NData, typename EData>
Nodes<NData, EData> &Graph<NData, EData>::nodes() {
    return nodes_;
};

template<typename NData, typename EData>
Edges<NData, EData> &Graph<NData, EData>::edges() {
    return edges_;
}

template<typename NData, typename EData>
const Nodes<NData, EData> &Graph<NData, EData>::nodes() const {
    return nodes_;
};

template<typename NData, typename EData>
const Edges<NData, EData> &Graph<NData, EData>::edges() const {
    return edges_;
}

// ------------------ Graph print/import methods ------------------

template<typename NData, typename EData>
void Graph<NData, EData>::parse(std::string &line) {
    std::istringstream iss(line);
    std::string token;
    std::getline(iss, token, SPACE);
    if (token == NODE) {
        std::string id;
        std::string data;
        iss.ignore();
        std::getline(iss, id, SPACE);
        iss.ignore();
        std::getline(iss, data, CLOSE_CURLY_BRACKET);

        std::istringstream iss2(data);
        NData finalData;
        iss2 >> finalData;

        nodes_.add(std::stoi(id), finalData);

    } else if (token == EDGE) {
        std::string id;
        std::string sourceID;
        std::string targetID;
        std::string data;
        iss.ignore();
        std::getline(iss, sourceID, CLOSE_ROUND_BRACKET);
        iss.ignore();
        iss.ignore();
        std::getline(iss, id, SPACE);
        iss.ignore();
        std::getline(iss, data, CLOSE_CURLY_BRACKET);
        iss.ignore();
        iss.ignore();
        iss.ignore();
        iss.ignore();
        std::getline(iss, targetID, CLOSE_ROUND_BRACKET);

        std::istringstream iss2(data);
        EData finalData;
        iss2 >> finalData;

        edges_.add(std::stoi(id), std::stoi(sourceID), std::stoi(targetID), finalData);
    }
}

template<typename NData, typename EData>
void Graph<NData, EData>::print(std::ostream &stream) const {
    stream << nodes_;
    stream << edges_;
}

template<typename NData, typename EData>
void Graph<NData, EData>::print(const std::string &filename) const {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw FileException("Unable to open output file " + filename);
    }
    print(file);
    file.close();
}

template<typename NData, typename EData>
void Graph<NData, EData>::import(std::istream &stream) {
    std::string line;
    while (std::getline(stream, line)) {
        parse(line);
    }
}

template<typename NData, typename EData>
void Graph<NData, EData>::import(const std::string &filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw FileException("Unable to open input file " + filename);
    }
    import(file);
    file.close();
}

// ------------------ Graph operators ------------------

template<typename NData, typename EData>
std::istream &operator>>(std::istream &is, NData &data) {
    is >> data;
    return is;
}

template<typename NData, typename EData>
std::istream &operator>>(std::istream &is, EData &data) {
    is >> data;
    return is;
}

template<typename NData, typename EData>
std::ostream &operator<<(std::ostream &os, const Graph<NData, EData> &graph) {
    graph.print(os);
    return os;
}

// ------------------ Directed Graph ------------------

template<typename NData, typename EData>
class DirectedGraph : public Graph<NData, EData> {
public:
    DirectedGraph();

};

template<typename NData, typename EData>
DirectedGraph<NData, EData>::DirectedGraph() : Graph<NData, EData>(true) {}

// ------------------ Undirected Graph ------------------

template<typename NData, typename EData>
class UndirectedGraph : public Graph<NData, EData> {
public:
    UndirectedGraph();

};

template<typename NData, typename EData>
UndirectedGraph<NData, EData>::UndirectedGraph() : Graph<NData, EData>(false) {}


#endif //INC_11_12TH_HW_GRAPH_H
