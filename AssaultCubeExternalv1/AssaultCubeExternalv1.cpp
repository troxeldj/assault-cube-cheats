#include "proc.h"
#include <iostream>

int main()
{
    const wchar_t* procName = L"ac_client.exe";
    const unsigned int healthOffset = 0x00F8;
    const unsigned int ammoOffset = 0x0150;
    int ammoValue = 0;
    int healthValue = 0;

    // Get ProcessID of the Process in Memory
    DWORD procID = getProcID(procName);
    if (procID == 0)
    {
        std::cout << "Unable to Get Process ID.\n";
        return 0;
    }

    // Get Base Address of the Module loaded in the process'
    uintptr_t modBaseAddr = GetModuleBaseAddress(procID, procName);

    if (modBaseAddr == 0)
    {
        std::cout << "Unable to Module Base Address.\n";
        return 0;
    }
    
    // Get a handle to the process
    HANDLE procHandle = 0;
    procHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

    if (procHandle == 0)
    {
        std::cout << "Could not retrieve process handle.\n";
    }
    
    // Resolve Base Address of Pointer Chain
    uintptr_t entityBaseAddr = modBaseAddr + 0x10F4F4;
    
    // Read Ammo and Health Value
    uintptr_t ammoAddr = FindDMAAddy(procHandle, entityBaseAddr, { ammoOffset });
    uintptr_t healthAddr = FindDMAAddy(procHandle, entityBaseAddr, { healthOffset });
    ReadProcessMemory(procHandle, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    ReadProcessMemory(procHandle, (BYTE*)healthAddr, &healthValue, sizeof(healthValue), nullptr);
    std::cout << "Initial Ammo: " << ammoValue << "\n";
    std::cout << "Inital Health: " << healthValue << "\n";
    
    // Set Ammo Value
    ammoValue = 9999;
    healthValue = 9999;
    WriteProcessMemory(procHandle, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    WriteProcessMemory(procHandle, (BYTE*)healthAddr, &healthValue, sizeof(healthValue), nullptr);
    std::cout << "New Ammo: " << ammoValue << "\n";
    std::cout << "New Health: " << healthValue << "\n";
}

