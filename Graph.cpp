#include "Graph.h"

/*****************************************************************************
    Constructors/Destructor
*****************************************************************************/
template <class T>
Graph<T>::Graph() {}

template <class T>
Graph<T>::Graph(std::vector<Node<T>*> adjacency_list) {
    copy_(adjacency_list);
}

template <class T>
Graph<T>::Graph(const Graph<T>& other) {
    std::vector<Node<T>*> adjacency_list = other.getAdjacencyList();
    copy_(adjacency_list);
}

template <class T>
Graph<T>::~Graph() {
    for (int i = 0; i < adjacency_list_.size(); ++ i) {
        delete adjacency_list_[i];
        adjacency_list_[i] = nullptr;
    }

    adjacency_list_.clear();
}

/*****************************************************************************
    Operator Overload
*****************************************************************************/
template <class T>
T& Graph<T>::operator=(const Graph<T>& other) {
    std::vector<Node<T>*> adjacency_list = other.getAdjacencyList();
    copy_(adjacency_list);
}

/*****************************************************************************
    Data Modification
*****************************************************************************/
template <class T>
void Graph<T>::addVertex(const T& data) {
    if (contains(data)) {
        return;
    }

    Node<T>* node = new Node<T>(data);

    adjacency_list_.push_back(node);
}

template <class T>
void Graph<T>::removeVertex(const T& data) {
    if (!contains(data)) {
        return;
    }

    //Get an iterator to the data location
    typename std::vector<Node<T>*>::iterator it = adjacency_list_.begin();
    Node<T>* node_ptr = nullptr;
    for (; it != adjacency_list_.end(); ++it) {
        if ((*it)->getData() == data) {
            //Free the memory first then erase node from neighbor pointers
            int i_index = search_(data);
            node_ptr = adjacency_list_[i_index];
            erase_neighbors_(node_ptr);

            delete adjacency_list_[i_index];
            adjacency_list_[i_index] = nullptr;
            break;
        }
    }

    //Erase via iterator, std::vector handles shifting
    adjacency_list_.erase(it);
}

template <class T>
void Graph<T>::addEdge(const T& data1, const T& data2) {
    if (!contains(data1) || !contains(data2)) {
        return;
    }

    int data1_index = search_(data1);
    int data2_index = search_(data2);

    Node<T>* data2_node_ptr = adjacency_list_[data2_index];
    adjacency_list_[data1_index]->addEdge(data2_node_ptr);
}

template <class T>
void Graph<T>::removeEdge(const T& data1, const T& data2) {
    if (!contains(data1) || !contains(data2)) {
        return;
    }

    int data1_index = search_(data1);
    int data2_index = search_(data2);

    Node<T>* data2_node_ptr = adjacency_list_[data2_index];
    adjacency_list_[data1_index]->removeEdge(data2_node_ptr);
}

/*****************************************************************************
    Data Observation
*****************************************************************************/
template <class T>
std::vector<Node<T>*> Graph<T>::getAdjacencyList() const {
    return adjacency_list_;
}

template <class T>
bool Graph<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }

    for (int i = 0; i < adjacency_list_.size(); ++i) {
        if (adjacency_list_[i]->getData() == data) {
            return true;
        }
    }

    return false;
}

template <class T>
bool Graph<T>::empty() const {
    return adjacency_list_.empty();
}

template <class T>
int Graph<T>::size() const {
    return adjacency_list_.size();
}

template <class T>
void Graph<T>::printAdjacencyList() const {
    std::cout << "Adjacency List:" << '\n';
    for (int i = 0; i < adjacency_list_.size(); ++i) {
        std::cout << adjacency_list_[i]->getData() << ": ";
        adjacency_list_[i]->printNeighbors();
    }
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
template <class T>
void Graph<T>::copy_(std::vector<Node<T>*>& adjacency_list) {
    for (int i = 0; i < adjacency_list.size(); ++i) {
        Node<T>* new_node = new Node<T>(adjacency_list[i]->getData(), adjacency_list[i]->getEdgeList());
        adjacency_list_.push_back(new_node);
    }
}

template <class T>
int Graph<T>::search_(const T& data) const {
    for (int i = 0; i < adjacency_list_.size(); ++i) {
        if (adjacency_list_[i]->getData() == data) {
            return i;
        }
    }

    return -1;
}

template <class T>
void Graph<T>::erase_neighbors_(Node<T>*& node) {
    for (int i = 0; i < adjacency_list_.size(); ++i) {
        if (adjacency_list_[i]->contains(node)) {
            adjacency_list_[i]->removeEdge(node);
        }
    }
}