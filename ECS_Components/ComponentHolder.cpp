#include "ComponentHolder.h"

ComponentHolder::ComponentHolder() :
    PushFunc([](int id) {}),
    RemoveFunc([](int id) {}),
    TypeId(INVALID_TYPE_ID)
{
}

ComponentHolder::~ComponentHolder()
{
    for (auto& [id, dummy] : Components)
    {
        RemoveFunc(id);
    }

    Components.clear();
}

void ComponentHolder::PushNewComponent(int Id)
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");

    PushFunc(Id);
}

void ComponentHolder::RemoveComponent(int Id)
{
    assert(TypeId != INVALID_TYPE_ID && "Not component data assigned");
    RemoveFunc(Id);
}
