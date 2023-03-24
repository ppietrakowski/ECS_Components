#pragma once

#include "ComponentHolder.h"
#include "View.h"

class ComponentRegistry
{
public:
    template <typename T>
    View<T> GetView();

    int RegisterNewEntity();

    template <typename T>
    T& AddNewComponent(int Id);

    template <typename T>
    T& GetComponent(int Id);

    template <typename T>
    bool HasComponent(int Id) const;

    template <typename T>
    void RemoveComponent(int Id);

    void ReleaseId(int id);
private:
    std::map<int, ComponentHolder> Components;
    std::vector<int> Entities;

    template <typename T>
    ComponentHolder& GetComponentHolder();
};

#include "ComponentRegistry.inl"