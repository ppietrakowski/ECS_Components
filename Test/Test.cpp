// TestComponents.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <ComponentRegistry.h>
#include <Windows.h>


struct JustData
{
    int Data;
    float Health{ 100.0f };

    void OnConstruct(int i, char* str)
    {
        Data = 100;
    }
};

int main()
{
    ComponentRegistry registry;

    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x01))
    {

        int NewId = registry.RegisterNewEntity();

        registry.AddNewComponent<JustData>(NewId);
        registry.AddNewComponent<tm>(NewId);

        if (registry.HasComponent<tm>(NewId))
        {
            tm& t = registry.GetComponent<tm>(NewId);
            std::cout << t.tm_year << " ";
            std::cout << registry.GetComponent<JustData>(NewId).Data << "\n";
        }

        View<JustData> data = registry.GetView<JustData>();

        for (std::pair<const int, JustData>& d : data)
        {
            std::cout << d.first << "=> health=" << d.second.Health << " " << d.second.Data << std::endl;
        }

        registry.ReleaseId(NewId);
    }
}