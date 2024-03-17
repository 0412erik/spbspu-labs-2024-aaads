#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include <stdexcept>
#include <initializer_list>
#include <cstddef>

namespace nikiforov
{
  template <typename T>
  class List
  {
  public:
    List();
    List(size_t count, const T& value);
    List(Iterator<T> begin, Iterator<T> end, int value);
    List(const List& other);
    ~List();

    T& front();
    T& back();

    void assign(size_t count, const T& value);
    void assign(Iterator<T> first, Iterator<T> last);
    void assign(std::initializer_list<T> ilist);

    bool is_empty();
    size_t size();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    Iterator<T> insert(Iterator<T> pos, const T& value);
    Iterator<T> insert(Iterator<T> pos, size_t count, const T& value);
    Iterator<T> erase(Iterator<T> pos);
    Iterator<T> erase(Iterator<T> first, Iterator<T> last);
    void splice(Iterator<T> pos, List<T>& other);
    void reverse();
    void swap(List<T>& other);
    void clear();

    void remove(T value);
    template<class UnaryPredicate>
    void remove_if(UnaryPredicate p);

    Iterator<T> begin();
    Iterator<T> end();
    void advance(Iterator<T>& pos, size_t count);
    void advance(Iterator<T>& first, Iterator<T> last);

  private:

    Node<T>* head;
    size_t size_l;
  };
}

template<typename T>
nikiforov::List<T>::List()
{
  head = nullptr;
  size_l = 0;
}

template<typename T>
nikiforov::List<T>::List(size_t count, const T& value)
{
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template<typename T>
nikiforov::List<T>::List(Iterator<T> begin, Iterator<T> end, int value)
{
  for (begin; begin != end; ++begin)
  {
    push_back(value);
  }
}

template<typename T>
nikiforov::List<T>::List(const nikiforov::List<T>& other)
{
  if (other.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node<T>(*other.head);
  }
  size_l = other.size_l;
}

template<typename T>
nikiforov::List<T>::~List()
{
  clear();
}

template<typename T>
T& nikiforov::List<T>::front()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  return head->data;
}

template<typename T>
T& nikiforov::List<T>::back()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node<T>* actual = head;
  for (size_t i = 0; i < (size_l - 1); i++)
  {
    actual = actual->pNext;
  }
  return actual->data;
}

template<typename T>
void nikiforov::List<T>::assign(size_t count, const T& value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template<typename T>
void nikiforov::List<T>::assign(Iterator<T> first, Iterator<T> last)
{
  clear();
  while (first != last)
  {
    push_back(*first);
    first++;
  }
}

template<typename T>
void nikiforov::List<T>::assign(std::initializer_list<T> ilist)
{
  clear();
  for (const T* iter = ilist.begin(); iter != ilist.end(); ++iter)
  {
    push_back(*iter);
  }
}

template<typename T>
bool nikiforov::List<T>::is_empty()
{
  if (head == nullptr)
  {
    return true;
  }
  return false;
}

template<typename T>
size_t nikiforov::List<T>::size()
{
  return size_l;
}

template<typename T>
void nikiforov::List<T>::push_front(T data)
{
  Node<T>* nData = new Node<T>(data);
  if (head == nullptr)
  {
    head = nData;
  }
  else
  {
    Node<T>* actual = head;
    nData->pNext = actual;
    head = nData;
  }
  size_l++;
}

template<typename T>
void nikiforov::List<T>::push_back(T data)
{
  Node<T>* nData = new Node<T>(data);
  if (head == nullptr)
  {
    head = nData;
  }
  else
  {
    Node<T>* actual = head;
    while (actual->pNext != nullptr)
    {
      actual = actual->pNext;
    }
    actual->pNext = nData;
  }
  size_l++;
}

template<typename T>
void nikiforov::List<T>::pop_front()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node<T>* actual = head;
  head = head->pNext;
  delete actual;
  size_l--;
}

template<typename T>
void nikiforov::List<T>::pop_back()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node<T>* actual = head;
  Node<T>* todel = head;
  for (size_t i = 0; i < (size_l - 1); i++)
  {
    actual = todel;
    todel = actual->pNext;
  }
  actual->pNext = nullptr;
  delete todel;
  size_l--;
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::insert(Iterator<T> pos, const T& value)
{
  Iterator<T> newPos = begin();
  if (pos == begin())
  {
    push_front(value);
    newPos = begin();
  }
  else
  {
    Node<T>* nData = new Node<T>(value);
    Node<T>* actual = head;
    Node<T>* before_actial = head;
    size_t count = 0;
    for (Iterator<T> iter = begin(); iter != pos; ++iter)
    {
      before_actial = actual;
      actual = actual->pNext;
      count++;
    }
    before_actial->pNext = nData;
    nData->pNext = actual;
    size_l++;
    advance(newPos, count);
  }
  return Iterator<T>(newPos);
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::insert(Iterator<T> pos, size_t count, const T& value)
{
  Iterator<T> newPos = begin();
  for (size_t i = 0; i < count; i++)
  {
    newPos = insert(pos, value);
  }
  return Iterator<T>(newPos);
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::erase(Iterator<T> pos)
{
  Iterator<T> newPos = begin();
  if (pos == end())
  {
    newPos = end();
  }
  else if (pos == begin())
  {
    pop_front();
    newPos = begin();
  }
  else
  {
    Node<T>* todel = head;
    Node<T>* before_todel = head;
    size_t count = 0;
    for (Iterator<T> iter = begin(); iter != pos; ++iter)
    {
      before_todel = todel;
      todel = todel->pNext;
      count++;
    }
    before_todel->pNext = todel->pNext;
    delete todel;
    size_l--;
    newPos = begin();
    advance(newPos, count);
  }
  return Iterator<T>(newPos);
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::erase(Iterator<T> first, Iterator<T> last)
{
  Iterator<T> newPos = begin();
  if (first == last)
  {
    newPos = last;
  }
  else
  {
    for (first; first != last; ++first)
    {
      first = erase(first);
    }
    newPos = first;
  }
  return Iterator<T>(newPos);
}

template<typename T>
void nikiforov::List<T>::splice(Iterator<T> pos, List<T>& other)
{
  if (other.is_empty())
  {
    throw std::logic_error("Empty list!");
  }

  Node<T>* actual = head;
  for (Iterator<T> iter = begin(); iter != pos; ++iter)
  {
    actual = actual->pNext;
  }

  Node<T>* other_end = other.head;
  for (size_t i = 0; i < (other.size() - 1); i++)
  {
    other_end = other_end->pNext;
  }

  Node<T>* subhead = actual->pNext;
  actual->pNext = other.head;
  other_end->pNext = subhead;
}

template<typename T>
void nikiforov::List<T>::reverse()
{
  Iterator<T> iter = begin();
  size_t count = size();
  size_t count_iter = size();
  for (size_t i = 0; i < count; i++)
  {
    advance(iter, count_iter);
    push_back(*iter);
    iter = begin();
    count_iter--;
  }
  for (size_t i = 0; i < count; i++)
  {
    pop_front();
  }
}

template<typename T>
void nikiforov::List<T>::swap(List<T>& other)
{
  Node<T>* short_termH = this->head;
  head = other.head;
  other.head = short_termH;

  size_t short_termS = this->size_l;
  size_l = other.size_l;
  other.size_l = short_termS;
}

template<typename T>
void nikiforov::List<T>::clear()
{
  const size_t size = size_l;
  for (size_t i = 0; i < size; i++)
  {
    pop_front();
  }
}

template<typename T>
void nikiforov::List<T>::remove(T value)
{
  size_t size = size_l;
  size_t count = 0;
  Node<T>* actual = head;
  Node<T>* todel = head;
  Iterator<T> iter = begin();
  for (size_t i = 0; i < size; i++)
  {
    actual = head;
    todel = head;
    if (*iter == value)
    {
      if (iter == begin())
      {
        head = head->pNext;
        iter = begin();
        delete actual;
        size_l--;
        continue;
      }
      else
      {
        for (size_t i = 0; i < (count - 1); i++)
        {
          actual = actual->pNext;
        }
        todel = actual->pNext;
        actual->pNext = todel->pNext;
        iter++;
        delete todel;
        size_l--;
        continue;
      }
    }
    iter++;
    count++;
  }
}

template< typename T >
template< class UnaryPredicate>
void nikiforov::List< T >::remove_if(UnaryPredicate p)
{
  Node<T>* actial = head;
  Node<T>* before_actial = head;
  while (actial)
  {
    if ((p(actial->data)) && (actial == head))
    {
      pop_front();
      actial = head;
      before_actial = head;
      continue;
    }
    else if ((p(actial->data)) && (actial->pNext == nullptr))
    {
      pop_back();
      break;
    }
    else if ((p(actial->data)) && (actial != head))
    {
      before_actial->pNext = actial->pNext;
      delete actial;
      actial = before_actial;
      size_l--;
    }
    before_actial = actial;
    actial = before_actial->pNext;
  }
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::begin()
{
  return Iterator<T>(head);
}

template<typename T>
nikiforov::Iterator<T> nikiforov::List<T>::end()
{
  return Iterator<T>(nullptr);
}

template<typename T>
void nikiforov::List<T>::advance(Iterator<T>& pos, size_t count)
{
  if (count < 0)
  {
    throw std::logic_error("Wrong input count!");
  }
  for (size_t i = 0; i < count; i++)
  {
    if (pos == end())
    {
      pos = end();
      break;
    }
    pos++;
  }
}

template<typename T>
void nikiforov::List<T>::advance(Iterator<T>& first, Iterator<T> last)
{
  for (Iterator<T> iter = first; iter != last; ++iter)
  {
    if (iter == end())
    {
      first = end();
      break;
    }
    first++;
  }
}

#endif
