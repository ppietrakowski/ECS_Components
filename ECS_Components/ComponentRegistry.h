#pragma once

#include "ComponentHolder.h"
#include "View.h"

class ComponentRegistry
{
public:
    template <typename TComponent>
    View<TComponent> GetView();

    int RegisterNewEntity();

    template <typename TComponent>
    TComponent& AddNewComponent(int id);

    template <typename TComponent>
    TComponent& GetComponent(int id);

    template <typename TComponent>
    bool HasComponent(int id) const;

    template <typename TComponent>
    void RemoveComponent(int id);

    void ReleaseId(int id);
private:
    std::map<int, ComponentHolder> Components;
    std::vector<int> Entities;

    template <typename TComponent>
    ComponentHolder& GetComponentHolder();
};

#include "ComponentRegistry.inl"