#pragma once

#include <atomic>

extern std::atomic_int TypeIdCounter;

template <typename TValue>
int GetTypeId()
{
    static int Id = TypeIdCounter++;
    return Id;
}

constexpr int INVALID_TYPE_ID = -1;
