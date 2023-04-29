#include "Node.h"

/*****************************************************************************
    Constructors/ Destructor
*****************************************************************************/
// Time Complexity: O(1)
template <class T>
Node<T>::Node() : data_(T()) {}

// Time Complexity: O(1)
template <class T>
Node<T>::Node(const T& data) : data_(data) {}
 
// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
Node<T>::Node(const T& data, const std::vector<Node<T>*>& edge_list) : data_(data) {
    copy_(edge_list);
}

// Time Complexity: O(N), where N is the number of edges in the edge list in other
template <class T>
Node<T>::Node(const Node<T>& other): data_(other.data_) {
    copy_(other.edge_list_);
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
Node<T>::~Node() {
    edge_list_.clear();
}

/*****************************************************************************
    Operator Overload
*****************************************************************************/
// Time Complexity: O(N), where N is the number of edges in the edge list in other
template <class T>
T& Node<T>::operator=(const Node<T>& other) {
    data_ = other.data_;
    copy_(other.edge_list_);
}

/*****************************************************************************
    Data Manipulation
*****************************************************************************/
// Time Complexity: O(1)
template <class T>
void Node<T>::setData(const T& data) {
    data_ = data;
}

// Time Complexity: O(1)
template <class T>
void Node<T>::setEdgeList(std::vector<Node<T>*> edge_list) {
    edge_list_ = edge_list;
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
void Node<T>::addEdge(Node<T>*& node) {
    if (contains(node)) {
        return;
    }

    edge_list_.push_back(node);
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
void Node<T>::removeEdge(Node<T>*& node) {
    if (!contains(node)) {
        return;
    }

    //Get an iterator to the node location, set it to null pointer
    std::vector<Node<int>*>::iterator it = edge_list_.begin();
    for (; it != edge_list_.end(); ++it) {
        if ((*it)->getData() == node->getData()) {
            int i_index = search_(node);
            edge_list_[i_index] = nullptr;
            break;
        }
    }

    //Erase via iterator, std::vector handles shifting
    edge_list_.erase(it);
}

/*****************************************************************************
    Data Observation
*****************************************************************************/
// Time Complexity: O(1)
template <class T>
T Node<T>::getData() const {
    return data_;
}

// Time Complexity: O(1)
template <class T>
std::vector<Node<T>*> Node<T>::getEdgeList() const {
    return edge_list_;
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
bool Node<T>::contains(Node<T>*& node) const {
    if (empty()) {
        return false;
    }

    for (int i = 0; i < edge_list_.size(); ++i) {
        if (edge_list_[i]->getData() == node->getData()) {
            return true;
        }
    }

    return false;
}

// Time Complexity: O(1)
template <class T>
bool Node<T>::empty() const {
    return edge_list_.empty();
}

// Time Complexity: O(1)
template <class T>
int Node<T>::size() const {
    return edge_list_.size();
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
void Node<T>::printNeighbors() const {
    for (int i = 0; i < edge_list_.size(); ++i) {
        std::cout << edge_list_[i]->getData() << ", ";
    }
    std::cout << '\n';
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
int Node<T>::search_(Node<T>*& node) const {
    for (int i = 0; i < edge_list_.size(); ++i) {
        if (edge_list_[i]->getData() == node->getData()) {
            return i;
        }
    }

    return -1;
}

// Time Complexity: O(N), where N is the number of edges in the edge list
template <class T>
void Node<T>::copy_(const std::vector<Node<T>*>& edge_list) {
    for (int i = 0; i < edge_list.size(); ++i) {
        Node<T>* node_ptr = edge_list[i];
        edge_list_.push_back(node_ptr);
    }
}
