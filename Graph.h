/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Implementation of Graph using a vector of vectors                 *
*    Progess: Basic implementation and methods complete                      *
*****************************************************************************/

// This is an unweighted directional graph: Meaning each edge has to be explicitly stated, node to node

#ifndef GRAPH_H
#define GRAPH_H

#include "Node.cpp"

template <class T>
class Graph {
    private:
        std::vector<Node<T>*> adjacency_list_;

        void copy_(const std::vector<Node<T>*>& adjacency_list);
        int search_(const T& data) const;
        void erase_neighbors_(Node<T>*& node);
    public:
        Graph();
        Graph(const std::vector<Node<T>*> adjacency_list);
        Graph(const Graph<T>& other);
        ~Graph();
        T& operator=(const Graph<T>& other);
        std::vector<Node<T>*> getAdjacencyList() const;
        void addVertex(const T& data);
        void removeVertex(const T& data);
        void addEdge(const T& data1, const T& data2);
        void removeEdge(const T& data1, const T& data2);
        bool contains(const T& data) const;
        bool empty() const;
        int size() const;
        void printAdjacencyList() const;
};

#endif
