#pragma once

#include "ControlBlock.hpp"
#include "NullPtrException.h"

#include <iostream>
#include <memory>

template <typename T>
class shared_ptr{
public:
    shared_ptr(T* ptr = nullptr);
    shared_ptr(shared_ptr& otherPtr);
    shared_ptr(shared_ptr&& otherPtr);
    ~shared_ptr();

    T& operator*() const;
    T* operator->() const;
    T* get();
    size_t useCount() const;

    shared_ptr<T>& operator=(shared_ptr<T>&& otherPtr);
    shared_ptr<T>& operator=(const shared_ptr<T>& otherPtr);

    void checkRefs();
    void reset(T* ptr = nullptr);

private:
    T* ptr_;
    ControlBlock* sharedRefs_{nullptr};
};

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr &otherPtr) :
    ptr_(otherPtr.ptr_),
    sharedRefs_(otherPtr.sharedRefs_) {

    ++(*sharedRefs_);
}

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr &&otherPtr) :
    ptr_(otherPtr.ptr_),
    sharedRefs_(otherPtr.sharedRefs_) {

    otherPtr.ptr_ = nullptr;
    otherPtr.sharedRefs_ = nullptr;
}

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T>::shared_ptr(T *ptr) : ptr_(ptr) {
    if(ptr_) {
        sharedRefs_ = new ControlBlock();
        ++(*sharedRefs_);
    }
}

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T>::~shared_ptr() {
    if(sharedRefs_ != nullptr){
        --(*sharedRefs_);
        checkRefs();
    }
}

/*------------------------------------------------------------------*/
template<typename T>
T &shared_ptr<T>::operator*() const {
    if(!ptr_){
        throw NullPtrException("You're trying to delete nullptr.\n");
    }
    return *ptr_;
}

/*------------------------------------------------------------------*/
template<typename T>
T *shared_ptr<T>::operator->() const {
    return ptr_;
}

/*------------------------------------------------------------------*/
template<typename T>
T *shared_ptr<T>::get() {
    return ptr_;
}

/*------------------------------------------------------------------*/
template<typename T>
size_t shared_ptr<T>::useCount() const {
    if(sharedRefs_ == nullptr)
        return 0;
    return sharedRefs_->getSharedRefs();
}

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&otherPtr) {
    if(this != &otherPtr) {
        if (useCount()) {
            --(*sharedRefs_);
            checkRefs();
        }

        sharedRefs_ = otherPtr.sharedRefs_;
        ptr_ = otherPtr.ptr_;
        otherPtr.ptr_ = nullptr;
        otherPtr.sharedRefs_ = nullptr;
    }

    return *this;
}

/*------------------------------------------------------------------*/
template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &otherPtr) {
    if(useCount()){
        --(*sharedRefs_);
        checkRefs();
    }

    sharedRefs_ = otherPtr.sharedRefs_;
    ptr_ = otherPtr.ptr_;
    ++(*sharedRefs_);

    return *this;
}

/*------------------------------------------------------------------*/
template<typename T>
void shared_ptr<T>::checkRefs() {
    if(useCount() == 0){
        delete ptr_;
        delete sharedRefs_;
    }
}

/*------------------------------------------------------------------*/
template<typename T>
void shared_ptr<T>::reset(T *ptr) {
    if(useCount() == 1){
        delete ptr_;
    }
    else{
        sharedRefs_ = new ControlBlock();
        ++(*sharedRefs_);
    }
    ptr_ = ptr;
}
