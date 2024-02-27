#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  void trickleUp(int idx);
  void heapify(int idx);
  bool isLeaf(int idx);
  int getValuedChild(int idx);
  std::vector<T> items_;
  int dim_;
  PComparator compare_;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  dim_ = m;
  compare_ = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
  int parent = (loc - 1) / dim_;
  while (parent >= 0 && compare_(items_[loc], items_[parent]))
  {
    std::swap(items_[parent], items_[loc]);
    loc = parent;
    parent = (loc - 1) / dim_;
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx)
{
  if (isLeaf(idx)) return;
  int valuedChild = getValuedChild(idx);
  if (compare_(items_[valuedChild], items_[idx]))
  {
    std::swap(items_[idx], items_[valuedChild]);
    heapify(valuedChild);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::isLeaf(int idx)
{
  return (idx * dim_ + 1 > size() - 1);
}

template <typename T, typename PComparator>
int Heap<T,PComparator>::getValuedChild(int idx)
{
  int valuedChild = dim_ * idx + 1;
  for (int i=2; i < dim_ + 1; ++i)
  {
    if ((dim_ * idx) + i > size() - 1) {break;} 
    if (compare_(items_[(dim_ * idx) + i], items_[valuedChild])) 
    {
      valuedChild = (dim_ * idx) + i;
    }
  }
  return valuedChild;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return items_.size();
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return size() == 0;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  items_.push_back(item);
  trickleUp(size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("UNDER");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("UNDER");
  }
  items_[0] = items_.back();
  items_.pop_back();
  if (size() != 0) {heapify(0);}
}

/*template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
  int parent = loc / dim_;
  while (parent >= 1 && compare_(items_[loc], items_[parent]))
  {
    std::swap(items_[parent], items_[loc]);
    loc = parent;
    parent = loc / dim_;
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx)
{
  if (isLeaf(idx)) return;
  int valuedChild = getValuedChild(idx);
  if (compare_(items_[valuedChild], items_[idx]))
  {
    std::swap(items_[idx], items_[valuedChild]);
    heapify(valuedChild);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::isLeaf(int idx)
{
  return (idx * dim_ > size());
}

template <typename T, typename PComparator>
int Heap<T,PComparator>::getValuedChild(int idx)
{
  int valuedChild = dim_ * idx;
  for (int i=1; i < dim_; ++i)
  {
    if ((dim_ * idx) + i > size()) {break;} 
    if (compare_(items_[(dim_ * idx) + i], items_[valuedChild])) 
    {
      valuedChild = (dim_ * idx) + i;
    }
  }
  return valuedChild;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  if (items_.size() == 0) {return 0;}
  return items_.size() - 1;
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return (items_.size() <= 1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  if (empty()) {items_.push_back(item);}
  items_.push_back(item);
  trickleUp(size());
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("UNDER");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[1];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("UNDER");
  }
  items_[1] = items_.back();
  items_.pop_back();
  heapify(1);
}*/

#endif