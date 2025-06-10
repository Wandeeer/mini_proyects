#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

void read_process() {
    // Tomar una snapshot de los procesos
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
      std::cerr << "Error al cargar los procesos del sistema.\n";
      return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
          std::wcout << L"PROCESS NAME: " << pe32.szExeFile << L" (PID: " << pe32.th32ProcessID << L")\n";
        } while (Process32Next(hSnapshot, &pe32));
    } else {
      std::cerr << "Error al obtener el primer proceso.\n";
    }

    CloseHandle(hSnapshot);
}

int main() {
    std::wcout << L"Procesos activos:\n\n";
    read_process();
    return 0;
}

