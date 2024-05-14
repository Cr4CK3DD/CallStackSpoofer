#include "Suppressor.h"

int main()
{
    PIMAGE_SECTION_HEADER       TextSection;
    LPVOID                      TextSectionAddr;
    DWORD                       TextSectionSize;
    HMODULE                     Kernel32;
    HMODULE                     Ntdll;
    LPVOID                      Gadget;
    NtAllocateVirtualMemory_t   NtAVM;
    PVOID                       BaseAddress;
    DWORD64                     Size;
    NTSTATUS                    Status;
    

    // Find ret gadget
    Kernel32        = GetModuleHandleA("Kernel32");
    TextSection     = GetSection(Kernel32, ".text");
    TextSectionAddr = Kernel32 + TextSection->VirtualAddress;
    TextSectionSize = TextSection->SizeOfRawData;

    Gadget          = FindGadget(TextSectionAddr, TextSectionSize, "\xC3", 1);
    if (Gadget == NULL)
    {
        DEBUG_PRINT("[-] No Gadget For You!");
        return (1);
    }
    
    Ntdll = GetModuleHandleA("ntdll");
    if (Ntdll == NULL)
    {
        DEBUG_PRINT("[-] No Handle(Ntdll) For You!");
        return (1);
    }

    NtAVM           = GetProcAddress(Ntdll, "NtAllocateVirtualMemory");
    if (NtAVM == NULL)
    {
        DEBUG_PRINT("[-] No Allocate Memory For You! (NtAllocateVirtualMemory)");
        return (1);
    }

    // 
    // {    API,   Gadget,     Return,     RCX,    RDX,    R8,     Size of Arguments * 8   }
    //
    PARAMS  params  = {NtAVM, Gadget, (BYTE *)Suppressor + 0x4C, NULL, NULL, NULL, 2 * 8};
    BaseAddress     = NULL;
    Size            = 0xBAAD;
  
    Status = Suppressor(GetCurrentProcess(), &BaseAddress, 0, &Size, &params, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if (!NT_SUCCESS(Status))
    {
        DEBUG_PRINT("[-] No Allocate Memory For You! (Suppressor)");
        return (1);
    }
    
    DEBUG_PRINT("[+] Allocated Memory : %p\n", BaseAddress);
	return (0);
}