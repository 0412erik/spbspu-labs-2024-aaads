#ifndef NODE_HPP
#define NODE_HPP

namespace kaseev{
  template <class T>
  class Node
  {
  public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
  };
}
#endif
