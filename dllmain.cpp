// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.
#include "pch.h"

const std::string LogFileName = "config_gamelog.txt";
const std::string DataFileName = "config_data.txt";
const std::string SaveFileName = "config_save.txt";
const uint32_t VALUE_SAVE = 1;
const uint32_t VALUE_LOAD = 2;

extern "C" {
    void MonitorGameMemory() {
        // sleep 2 seconds
        Sleep(2000);
        auto m_StartTime = std::chrono::system_clock::now();
        bool running = true;
        // read game name from file
        std::wifstream ifile(DataFileName);
        std::wstring gameName;
        std::getline(ifile, gameName);
        // look for specific value of a System Variable
        DWORD SysVarA_Address = 0x004456B0; //position of System Variable A
        size_t bufferSize = 30; //32 bytes worth of System Variables to save (maybe 30? let's use SysVar P to trigger the save action)
        DWORD saveLoadTriggerVarAddress = SysVarA_Address + 30;
        DWORD access =  PROCESS_VM_READ |
                        PROCESS_QUERY_INFORMATION |
                        PROCESS_VM_WRITE |
                        PROCESS_VM_OPERATION;
        auto pid2 = GetCurrentProcessId();
        std::ofstream file(LogFileName, std::ios_base::app);
        file << "Attaching DLL to game process..." << std::endl;
        file << "Own process handle is " << pid2 << std::endl;
        file.close();
        HANDLE phandle = OpenProcess(access, 0, pid2); //Get permission to read
        if (!phandle) //Once again, if it fails, tell us
        {
            std::ofstream file(LogFileName, std::ios_base::app);
            file << "Could not get process handle." << std::endl;
            running = false;
            return;
        }
        else {
            std::ofstream file(LogFileName, std::ios_base::app);
            file << "Found process handle " << pid2 << std::endl;
            file.close();
        }
        while (running) {
            auto m_Time = std::chrono::system_clock::now();
            long long duration = (std::chrono::duration_cast<std::chrono::milliseconds>(m_Time - m_StartTime)).count();
            if (duration > 100) {
                uint8_t valueLow = 0;
                uint8_t valueHigh = 0;
                SIZE_T writtenLow;
                SIZE_T writtenHigh;
                DWORD address = saveLoadTriggerVarAddress;
                ReadProcessMemory(phandle, (void*)address, &valueLow, sizeof(valueLow), &writtenLow);
                ReadProcessMemory(phandle, (void*)(address + 1), &valueHigh, sizeof(valueHigh), &writtenHigh);
                uint32_t result = (uint32_t(valueHigh) << 8) | (uint32_t)valueLow;
                m_StartTime = m_Time;
                if (result > 0) {
                    if (result == VALUE_SAVE) {
                        std::ofstream file(LogFileName, std::ios_base::app);
                        file << "Save command received" << std::endl;
                        char buffer[30];
                        SIZE_T writtenBytes = 0;
                        ReadProcessMemory(phandle, (void*)SysVarA_Address, buffer, sizeof(buffer), &writtenBytes);
                        file << "Read: " << writtenBytes << " bytes" << std::endl;
                        file.close();
                        std::ofstream savefile(SaveFileName, std::ios::binary);
                        for (int i = 0; i < writtenBytes; ++i) {
                            savefile << buffer[i];
                        }
                        savefile.close();
                    }
                    else if (result == VALUE_LOAD) {
                        std::ofstream file(LogFileName, std::ios_base::app);
                        file << "Load command received" << std::endl;
                        std::ifstream savefile(SaveFileName, std::ios::binary);
                        char buffer[30];
                        savefile.read(buffer, 30);
                        savefile.close();
                        SIZE_T writtenBytes = 0;
                        WriteProcessMemory(phandle, (void*)SysVarA_Address, buffer, sizeof(buffer), &writtenBytes);
                        file << "Written: " << writtenBytes << " bytes" << std::endl;
                        std::ofstream savefilebck("bck_" + SaveFileName, std::ios::binary);
                        for (int i = 0; i < writtenBytes; ++i) {
                            savefilebck << buffer[i];
                            char valueToWrite = buffer[i];
                            WriteProcessMemory(phandle, (void*)(SysVarA_Address + i), &valueToWrite, sizeof(valueToWrite), 0);
                        }
                        savefilebck.close();
                        file.close();

                    }
                    // write the save variable to 0 after dumping
                    uint16_t valueZero = 0;
                    WriteProcessMemory(phandle, (void*)address, &valueZero, sizeof(valueZero), 0);
                }
            }
            Sleep(50);
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            std::ofstream file(LogFileName);
            file << "The DLL was attached successfully" << std::endl;
            file.close();
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonitorGameMemory, NULL, 0, NULL);
        }
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        {
            std::ofstream file(LogFileName, std::ios_base::app);
            file << "The DLL was detached..." << std::endl;
            file.close();
        }
        break;
    }
    return TRUE;
}

