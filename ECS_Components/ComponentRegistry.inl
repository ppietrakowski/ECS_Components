#include "ComponentRegistry.h"

template <typename T>
inline View<T> ComponentRegistry::GetView()
{
    View<T> view(&Entities, &GetComponentHolder<T>());
    return view;
}

template <typename T>
inline T& ComponentRegistry::AddNewComponent(int Id)
{
    ComponentHolder& holder = GetComponentHolder<T>();
    holder.PushNewComponent<T>(Id);

    return holder.GetComponent<T>(Id);
}

template <typename T>
inline T& ComponentRegistry::GetComponent(int Id)
{
    int typeId = GetTypeId<T>();

    if (Components.find(typeId) == Components.end())
    {
        Components.insert({ typeId, ComponentHolder{} });
    }

    ComponentHolder& holder = Components[typeId];
    return holder.GetComponent<T>(Id);
}

template <typename T>
inline bool ComponentRegistry::HasComponent(int Id) const
{
    int typeId = GetTypeId<T>();
    assert(Components.find(typeId) != Components.end() && "Registry doesn't contain container of T data");

    const ComponentHolder& holder = Components.at(typeId);
    return holder.HasComponent<T>(Id);
}

template<typename T>
inline void ComponentRegistry::RemoveComponent(int Id)
{
    int typeId = GetTypeId<T>();
    assert(Components.find(typeId) != Components.end() && "Registry doesn't contain container of T data");

    ComponentHolder& holder = Components[typeId];
    holder.RemoveComponent(Id);
}

template <typename T>
inline ComponentHolder& ComponentRegistry::GetComponentHolder()
{
    int typeId = GetTypeId<T>();

    if (Components.find(typeId) == Components.end())
    {
        Components.insert({ typeId, ComponentHolder{} });
    }

    return Components[typeId];
}