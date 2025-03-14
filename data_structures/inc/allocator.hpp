#pragma once

#include "iallocator.hpp"

class MyAllocator : public IMyAllocator {
public:
    using allocCb_t = void* (*)(size_t);
    using freeCb_t =  void (*)(void*);

    MyAllocator() = delete;
    MyAllocator(allocCb_t, freeCb_t);

    virtual ~MyAllocator(){}

    virtual void* alloc(size_t) const noexcept override;

    virtual void free(void*) const noexcept override;

private:
    allocCb_t allocCb{nullptr};
    freeCb_t freeCb{nullptr};
};