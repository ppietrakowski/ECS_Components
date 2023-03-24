#include "ComponentHolder.h"

template <typename TComponent>
inline TComponent& ComponentHolder::GetComponent(int id)
{
    assert(HasComponent<TComponent>(id));
    const std::map<int, TComponent>* d = reinterpret_cast<const std::map<int, TComponent>*>(&Components);

    return (TComponent&)d->at(id);
}

template <typename TComponent>
inline bool ComponentHolder::HasComponent(int id) const
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<TComponent>() && "Invalid type of container");
    
    const std::map<int, TComponent>* d = reinterpret_cast<const std::map<int, TComponent>*>(&Components);
    return d->find(id) != d->end();
}

inline size_t ComponentHolder::GetSize() const
{
    return Components.size();
}

template <typename TComponent>
inline auto ComponentHolder::begin()
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<TComponent>() && "Invalid type of container");

    std::map<int, TComponent>* d = reinterpret_cast<std::map<int, TComponent>*>(&Components);
    return d->begin();
}

template <typename TComponent>
inline auto ComponentHolder::end()
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<TComponent>() && "Invalid type of container");

    std::map<int, TComponent>* d = reinterpret_cast<std::map<int, TComponent>*>(&Components);
    return d->end();
}

template<typename TComponent>
inline void ComponentHolder::AssignType()
{
    PushFunc = [this](int id)
    {
        std::map<int, TComponent>& d = reinterpret_cast<std::map<int, TComponent>&>(Components);
        d.insert({ id, TComponent{} });
    };

    RemoveFunc = [this](int id)
    {
        std::map<int, TComponent>& d = reinterpret_cast<std::map<int, TComponent>&>(Components);
        d.erase(id);
    };

    TypeId = GetTypeId<TComponent>();
}
