#include <iostream>
#include "Windows.h"

DWORD GetProcId(const char* procName) // Expects  a return of a DWORD
{
	HWND acWindow = FindWindow(nullptr, "AssaultCube"); // HWIND = Handel to window, Its just a number that points to a place in memory, FindWindow(class, Name of the window)

	DWORD processId; // declaring it
	GetWindowThreadProcessId(acWindow, &processId); // feeding it the handel to the window -> returns the process ID -> returns it to the address of processID

	return processId; // return process ID, 
}

int main()
{
	const char* dllPath = "C://dev//learning/acDLL/Debug//acDll.dll"; // Assigning a constant char pointer to our dllPath, constant because the location of this file will never change (if it does we come back and change)
	const char* procName = "ac_client.exe"; // procname explains itself

	DWORD processId = GetProcId(procName); // Windows stores processs ID'S as DWORDS so we match that, processId gets its value from GetProcId function on line 4

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId); // Complicated so check OneNote

	void* spaceForDllPath = VirtualAllocEx(hProc, nullptr, strlen(dllPath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); // Again on one Note

	WriteProcessMemory(hProc, spaceForDllPath, dllPath, strlen(dllPath), nullptr); //One Note

	HANDLE hThread = CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, spaceForDllPath, NULL, nullptr);// One note

	CloseHandle(hThread); // closes the threads
	CloseHandle(hProc);




}