#include "ComponentHolder.h"

inline ComponentHolder::ComponentHolder() :
    PushFunc([](int id) {}),
    RemoveFunc([](int id) {}),
    TypeId(INVALID_TYPE_ID)
{
}

template <typename T>
inline void ComponentHolder::PushNewComponent(int Id)
{
    if (Components.size() == 0)
    {
        PushFunc = [this](int id)
        {
            std::map<int, T>& d = reinterpret_cast<std::map<int, T>&>(Components);
            d.insert({ id, T{} });
        };

        RemoveFunc = [this](int id)
        {
            std::map<int, T>& d = reinterpret_cast<std::map<int, T>&>(Components);
            d.erase(id);
        };

        TypeId = GetTypeId<T>();
    }

    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<T>() && "Invalid type of container");

    PushFunc(Id);
}

template <typename T>
inline T& ComponentHolder::GetComponent(int Id)
{
    assert(HasComponent<T>(Id));
    const std::map<int, T>* d = reinterpret_cast<const std::map<int, T>*>(&Components);

    return (T&)d->at(Id);
}

template <typename T>
inline bool ComponentHolder::HasComponent(int Id) const
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<T>() && "Invalid type of container");
    
    const std::map<int, T>* d = reinterpret_cast<const std::map<int, T>*>(&Components);
    return d->find(Id) != d->end();
}

inline void ComponentHolder::RemoveComponent(int Id)
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    RemoveFunc(Id);
}

inline size_t ComponentHolder::GetSize() const
{
    return Components.size();
}

template <typename T>
inline auto ComponentHolder::begin()
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<T>() && "Invalid type of container");

    std::map<int, T>* d = reinterpret_cast<std::map<int, T>*>(&Components);
    return d->begin();
}

template <typename T>
inline auto ComponentHolder::end()
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    assert(TypeId == GetTypeId<T>() && "Invalid type of container");

    std::map<int, T>* d = reinterpret_cast<std::map<int, T>*>(&Components);
    return d->end();
}