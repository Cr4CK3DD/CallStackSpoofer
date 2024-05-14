#pragma once

#include <stdio.h>
#include <Windows.h>


#define SUPP_DEBUG 1

#if SUPP_DEBUG == 0
#define DEBUG_PRINT( STR, ... )
#else
#define DEBUG_PRINT( STR, ... ) printf(STR, __VA_ARGS__ ); 
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x)>=0)
#define STATUS_SUCCESS ((NTSTATUS)0)
#endif

typedef struct {
    LPVOID      api;
    LPVOID      gadget;
    LPVOID      retaddr;
    LPVOID      rcx;
    LPVOID      rdx;
    LPVOID      r8;
    DWORD64     args_size;
} PARAMS, * PPARAMS;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
	ULONG           Length;
	HANDLE          RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG           Attributes;
	PVOID           SecurityDescriptor;
	PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef (NTAPI *NtAllocateVirtualMemory_t)(
	IN HANDLE               ProcessHandle,
	IN OUT PVOID* BaseAddress,
	IN ULONG                ZeroBits,
	IN OUT PULONG           RegionSize,
	IN ULONG                AllocationType,
	IN ULONG                Protect);

typedef NTSTATUS(NTAPI* NtCreateProcessEx_t)
(
    OUT PHANDLE     ProcessHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes  OPTIONAL,
    IN HANDLE   ParentProcess,
    IN ULONG    Flags,
    IN HANDLE SectionHandle     OPTIONAL,
    IN HANDLE DebugPort     OPTIONAL,
    IN HANDLE ExceptionPort     OPTIONAL,
    IN BOOLEAN  InJob
    );

//
// NtCreateProcessEx flags
//
#define PS_REQUEST_BREAKAWAY                     1
#define PS_NO_DEBUG_INHERIT                     2
#define PS_INHERIT_HANDLES                      4
#define PS_UNKNOWN_VALUE                        8
#define PS_ALL_FLAGS PS_REQUEST_BREAKAWAY |PS_NO_DEBUG_INHERIT |PS_INHERIT_HANDLES | PS_UNKNOWN_VALUE

extern LPVOID           Suppressor(LPVOID a1, LPVOID a2, LPVOID a3, LPVOID a4, PPARAMS params, ...);
PIMAGE_SECTION_HEADER   GetSection(HMODULE hModule, PCSTR sectionName);
PVOID                   FindGadget(PVOID mem, SIZE_T mem_size, BYTE* gadget, DWORD gadget_size);
