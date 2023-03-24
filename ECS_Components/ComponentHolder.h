#pragma once

#include <map>
#include <functional>
#include <cassert>
#include "TypeId.h"

class ComponentHolder
{
    friend class ComponentRegistry;

public:
    ComponentHolder();

    ComponentHolder(ComponentHolder&&) noexcept = default;
    ComponentHolder(const ComponentHolder&) = delete;

    ComponentHolder& operator=(ComponentHolder&&) noexcept = default;
    ComponentHolder& operator=(const ComponentHolder&) = delete;

    template <typename T>
    void PushNewComponent(int Id);

    template <typename T>
    T& GetComponent(int Id);

    template <typename T>
    bool HasComponent(int Id) const;

    void RemoveComponent(int Id);

    size_t GetSize() const;

    template <typename T>
    auto begin();

    template <typename T>
    auto end();

private:
    // Dummy int value
    // inside is store T value
    typedef std::map<int, int> Holder;

    Holder Components;
    std::function<void(int id)> PushFunc;
    std::function<void(int id)> RemoveFunc;
    int TypeId;
};

#include "ComponentHolder.inl"