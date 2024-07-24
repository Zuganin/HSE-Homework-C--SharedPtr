

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <algorithm>

template <class T>
class SharedPtr {
 private:
  T* ptr_;
  size_t* strong_count_;

  void Release() const {
    if (strong_count_) {
      --(*strong_count_);
      if (*strong_count_ == 0) {
        delete ptr_;
        delete strong_count_;
      }
    }
  }

 public:
  SharedPtr() : ptr_(nullptr), strong_count_(nullptr) {}

  explicit SharedPtr(T* pointer)  {
    if (pointer) {
      ptr_ = pointer;
      strong_count_ = new size_t(1);
    } else {
      ptr_ = nullptr;
      strong_count_ = nullptr;
    }
  }
  SharedPtr(const SharedPtr& other)
      : ptr_(other.ptr_), strong_count_(other.strong_count_) {
    if (strong_count_) {
      ++(*strong_count_);
    }
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Release();
      ptr_ = other.ptr_;
      strong_count_ = other.strong_count_;

      if (strong_count_) {
        ++(*strong_count_);
      }
    }
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept
      : ptr_(other.ptr_), strong_count_(other.strong_count_) {
    other.ptr_ = nullptr;
    other.strong_count_ = nullptr;
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      Release();
      ptr_ = other.ptr_;
      strong_count_ = other.strong_count_;

      other.ptr_ = nullptr;
      other.strong_count_ = nullptr;
    }
    return *this;
  }
  ~SharedPtr() { Release(); }

  T* Get() const { return ptr_; }
  void Reset(T* ptr = nullptr) {
    Release();
    if (ptr) {
      ptr_ = ptr;
      strong_count_ = new size_t(1);

    } else {
      ptr_ = nullptr;
      strong_count_ = nullptr;
    }
  }
  void Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(strong_count_, other.strong_count_);
  }
  [[nodiscard]] size_t UseCount() const {
    return strong_count_ ? *strong_count_ : 0;
  }

  T& operator*() const { return *ptr_; }

  T* operator->() const { return ptr_; }

  explicit operator bool() const { return ptr_ != nullptr; }
};


#endif  // SHAREDPTR_H
