#include "Suppressor.h"

PIMAGE_SECTION_HEADER GetSection(HMODULE hModule, PCSTR sectionName)
{
    PBYTE               ImageBase = (PBYTE)hModule;
    PIMAGE_DOS_HEADER   DosHdr = (PIMAGE_DOS_HEADER)ImageBase;
    PIMAGE_NT_HEADERS   NtHdr = (PIMAGE_NT_HEADERS)(ImageBase + DosHdr->e_lfanew);

    for (WORD i = 0; i < NtHdr->FileHeader.NumberOfSections; i++)
    {
        PIMAGE_SECTION_HEADER SectionHdr = (PIMAGE_SECTION_HEADER)((DWORD_PTR)IMAGE_FIRST_SECTION(NtHdr) + ((DWORD_PTR)IMAGE_SIZEOF_SECTION_HEADER * i));

        if (!strcmp((PCSTR)SectionHdr->Name, sectionName))
        {
            return (SectionHdr);
        }
    }
    return (NULL);
}


PVOID FindGadget(PVOID mem, SIZE_T mem_size, BYTE* gadget, DWORD gadget_size)
{
    BYTE* Gadget = NULL;
    for (DWORD i = 0; i < mem_size; i++)
    {
        Gadget = (PBYTE)mem + i;
        if (!memcmp(Gadget, gadget, gadget_size))
        {
            return (LPVOID)(Gadget);
        }
    };
    return NULL;
}
