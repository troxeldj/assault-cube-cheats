
#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcID(const wchar_t* procName);
uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);