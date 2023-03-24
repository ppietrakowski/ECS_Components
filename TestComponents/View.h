#pragma once

#include "ComponentHolder.h"

#include <vector>

template <typename T>
class View
{
    friend class ComponentRegistry;

public:
    void ForEach(std::function<void(int id, T& component)> fn);

    auto begin();
    auto end();

private:
    const std::vector<int>* Entities;
    ComponentHolder* Holder;

    View(const std::vector<int>* entities, ComponentHolder* holder);
};

#include "View.inl"