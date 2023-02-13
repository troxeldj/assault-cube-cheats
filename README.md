# Very Simple Assault Cube Cheats

<font size=4 color=red>**Note: These were made only for Assault Cube v1.2.0.2 ONLY**</font>\
Link: https://github.com/assaultcube/AC/releases/tag/v1.2.0.2

## Assault Cube External
Basic External Cheat for Assault Cube\
**Features:**
- Health (WriteProcessMemory)
- Ammo (WriteProcessMemory)

This external cheat will run from a seperate exe. It is external in the sense that it modifies the game's memory from an external process. Because we are not inside of the game's memory, we need to gain somehow gain access to the game's memory using windows API functions.

**The basic steps for this program:**
- Get the process ID of the game process running. This is dynamic so we need to get it everytime.
- Get the base address of the module (ac_client.exe).
- Obtain a handle to the process and declare our process access rights (In this case: PROCESS_ALL_ACCESS)
- Modify game memory addresses relative to the base address of the module.
  - For example, in this version of the game, the local player object is located statically at: moduleBaseAddress + 0x10F4F4;
    - 0x10F4F4 is called an "offset".

**Windows API Functions Used**
- CreateToolhelp32Snapshot: Create a snapshot of all processes in memory.
- ReadProcessMemory: Read memory for an external process at a given memory address.
- WriteProcessMemory: Write memory for an external process at a given memory address.
- OpenProcess: Opens a handle with provided access rights to a process given it's process ID.

**Steps to Use**
1. Run Assault Cube.
2. Open Visual Studio Project and run as an x86 process in either debug or release.
    - The exe is also located in: Release\AssaultCubeExternalv1.exe
3. In game, you will now have unlimited ammo and unlimited health.

## Assault Cube Internal
**Features:**
- Health
- Ammo
- Recoil

This internal cheat runs from a dll. Basically this is a shared library file. Using a **DLL Injector**, we can inject our code (inside of the DLL) into the target process. The cool thing about this is that, our code is actually inside of the target process's virtual memory. This means that we can directly access and read/write over the memory in the process. SUPER COOL!\
Example: 
- External Ammo: 
```
WriteProcessMemory(procHandle, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
```
- Internal Ammo: 
```
*(int*)(ammoAddress) = 99999;
```
This syntax, in my opinion is MUCH, MUCH cleaner!

**The basic steps for this program:**
- Inject our DLL into our target process. You can do with with a **DLL Injector** like I mentioned before. There are tons of them.
- This DLL will then run our start routine or function automatically
  - We will use this function to "hook" a game function that runs at every frame. If we successfully do this, our hack function will run once for every frame internally!
  - For this example we used an OpenGL function "SwapBuffers"
- Watch for user key input and toggle off and on the cheats according to the key that user has presssed.

**Windows API Funcions Used**
- GetModuleHandleA: Gets a handle to a process module. In this case: ac_client.exe 
- That's it... We no longer need them as we are IN the process's memory!


**Steps to Use**
1. Use dll Injector to inject our dll library into the game.
    - The DLL is located in: Release\AssaultCubeInternalv1.dll
2. Press assigned keys to activate our cheats:
    * VK_NUMPAD1: Unlimited Health
    * VK_NUMPAD2: Unlimited Ammo
    * VK_NUMPAD3: No Recoil

Note: you can change these to whatever you want using the win32 api [virtual key codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)


## Credits
- [GuidedHacking](https://guidedhacking.com/)
    - Tremendous resource with lots of tutorials, both text and video, regarding game hacking. Awesome people
    - [Their YouTube](https://www.youtube.com/@GuidedHacking) / [Website](https://guidedhacking.com/)
- [Win32 API](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)
    - Microsoft's docs are almost always super useful when writing projects. If you have a question about an API function, **BOOM** here you go!
- [C++ Language Docs](https://learn.microsoft.com/en-us/cpp/cpp/?view=msvc-170)