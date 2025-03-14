
#include "allocator.hpp"

MyAllocator::MyAllocator(allocCb_t a, freeCb_t f) :
allocCb(a), freeCb(f) {

}

void* MyAllocator::alloc(size_t size) const noexcept {
    return this->allocCb(size);
}

void MyAllocator::free(void* p) const noexcept {
    this->freeCb(p);
}