#pragma once

#include <stdint.h>
#include <stdio.h>

class IMyAllocator {
public:
    virtual ~IMyAllocator() = default;
    virtual void* alloc(size_t size) const noexcept = 0;
    virtual void free(void*) const noexcept = 0;
};