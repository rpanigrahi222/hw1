#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val) {
  if(empty()) {
    head_ = new Item();
    tail_ = head_;
    head_->first = 0;
    head_->last = 0;
  }

  if(tail_->last == ARRSIZE) {
    Item* it = new Item();
    it->prev = tail_;
    tail_->next = it;
    tail_ = it;

  }

  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;

}

void ULListStr::push_front(const std::string& val) {
  if(empty()) {
    head_ = new Item();
    tail_ = head_;
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }

  if(head_->first == 0) {
    Item* it = new Item();
    it->first = ARRSIZE;
    it->last = ARRSIZE;
    it->next = head_;
    head_->prev = it;
    head_ = it;
  }

  head_->first--;
  head_->val[head_->first] = val;
  size_++;



}

void ULListStr::pop_back() {
  if(empty()) {
    return;
  }

  tail_->last--;
  size_--;

  if(tail_->first == tail_->last) {
    Item* to_remove = tail_;
    tail_ = tail_->prev;

    if(tail_ != NULL) {
      tail_->next = NULL;
    } else {
      head_ = NULL;
    }

    delete to_remove;
  }
}

void ULListStr::pop_front() {
  if(empty()) {
    return;
  }
  
  head_->first++;
  size_--;

  if(head_->first == head_->last) {
    Item* to_remove = head_;
    head_ = head_->next;

    if(head_ != NULL) {
      head_->prev = NULL;
    } else {
      tail_ = NULL;
    }

    delete to_remove;
  }
}

std::string const& ULListStr::back() const {
  static const std::string empty_str;
  if(empty()) {
    return empty_str;
  }
  return tail_->val[tail_->last - 1];
}

std::string const& ULListStr::front() const {
  static const std::string empty_str;
  if(empty()) {
    return empty_str;
  }
  return head_->val[head_->first];
}

 std::string* ULListStr::getValAtLoc(size_t loc) const {
  if(loc >= size_) {
    return NULL;
  }

  Item* curr = head_;
  size_t rest = loc;

  while(curr != NULL) {
    size_t cnt = curr->last - curr->first;
    if(rest < cnt) {
      return const_cast<std::string*>(&curr->val[curr->first + rest]);
    }
    rest -= cnt;
    curr = curr->next;
  }
  return NULL;
 }

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
