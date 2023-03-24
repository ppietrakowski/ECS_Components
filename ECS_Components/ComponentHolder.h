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
    ~ComponentHolder();

    ComponentHolder(ComponentHolder&&) noexcept = default;
    ComponentHolder(const ComponentHolder&) = delete;

    ComponentHolder& operator=(ComponentHolder&&) noexcept = default;
    ComponentHolder& operator=(const ComponentHolder&) = delete;

    void PushNewComponent(int id);

    template <typename TComponent>
    TComponent& GetComponent(int id);

    template <typename TComponent>
    bool HasComponent(int id) const;

    void RemoveComponent(int id);

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

    template <typename TComponent>
    void AssignType();
};

#include "ComponentHolder.inl"