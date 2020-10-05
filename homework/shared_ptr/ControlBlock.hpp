#pragma once
#include <atomic>
#include <iostream>

class ControlBlock{
public:
    ControlBlock() : sharedRefs_(0) {};

    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;

    ControlBlock& operator++();
    ControlBlock& operator--();
    int getSharedRefs() const;

private:
    std::atomic<int> sharedRefs_;
};

/*------------------------------------------------------------------*/
ControlBlock &ControlBlock::operator--() {
    sharedRefs_--;
    return *this;
}

/*------------------------------------------------------------------*/
ControlBlock &ControlBlock::operator++() {
    sharedRefs_++;
    return *this;
}

/*------------------------------------------------------------------*/
int ControlBlock::getSharedRefs() const { return sharedRefs_; }
