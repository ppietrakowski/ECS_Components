#include "ComponentRegistry.h"

int ComponentRegistry::RegisterNewEntity()
{
    int back = 0;
    if (!Entities.empty())
    {
        back = Entities.back();
    }

    Entities.emplace_back(back + 1);
    return Entities.back();
}

void ComponentRegistry::ReleaseId(int id)
{
    for (auto& [typeId, holder] : Components)
    {
        holder.RemoveComponent(id);
    }
 
    auto it = std::remove(Entities.begin(), Entities.end(), id);
    if (it != Entities.end())
    {
        Entities.erase(it);
    }
}
