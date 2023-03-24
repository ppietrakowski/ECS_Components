#include "ComponentRegistry.h"

template <typename TComponent>
inline View<TComponent> ComponentRegistry::GetView()
{
    View<TComponent> view(&Entities, &GetComponentHolder<TComponent>());
    return view;
}

template <typename TComponent>
inline TComponent& ComponentRegistry::AddNewComponent(int id)
{
    ComponentHolder& holder = GetComponentHolder<TComponent>();
    holder.PushNewComponent(id);

    return holder.GetComponent<TComponent>(id);
}

template <typename TComponent>
inline TComponent& ComponentRegistry::GetComponent(int id)
{
    int typeId = GetTypeId<TComponent>();
    assert(Components.find(typeId) != Components.end());

    ComponentHolder& holder = Components[typeId];
    return holder.GetComponent<TComponent>(id);
}

template <typename TComponent>
inline bool ComponentRegistry::HasComponent(int id) const
{
    int typeId = GetTypeId<TComponent>();
    assert(Components.find(typeId) != Components.end() && "Registry doesn't contain container of T data");

    const ComponentHolder& holder = Components.at(typeId);
    return holder.HasComponent<TComponent>(id);
}

template<typename TComponent>
inline void ComponentRegistry::RemoveComponent(int id)
{
    int typeId = GetTypeId<TComponent>();
    assert(Components.find(typeId) != Components.end() && "Registry doesn't contain container of T data");

    ComponentHolder& holder = Components[typeId];
    holder.RemoveComponent(id);
}

template <typename TComponent>
inline ComponentHolder& ComponentRegistry::GetComponentHolder()
{
    int typeId = GetTypeId<TComponent>();

    if (Components.find(typeId) == Components.end())
    {
        Components.insert({ typeId, ComponentHolder{} });
        Components[typeId].AssignType<TComponent>();
    }

    return Components[typeId];
}