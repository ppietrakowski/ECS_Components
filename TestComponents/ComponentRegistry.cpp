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