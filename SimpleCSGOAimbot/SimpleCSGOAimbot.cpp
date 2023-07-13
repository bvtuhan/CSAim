#include "Memory/Memory.h"
#include "Offsets/Offsets.h"
#include "Utils/Vector3.h"
#include "Utils/Aimbot.h"

int main()
{
    DWORD pid = getProcID(L"csgo.exe");
    DWORD client = getModuleBaseAddress(L"client.dll", pid);
    DWORD engine = getModuleBaseAddress(L"engine.dll", pid);
    DWORD client_state;

    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

    ReadProcessMemory(proc, (LPCVOID)(engine + hazedumper::signatures::dwClientState),
        &client_state, sizeof(client_state), NULL);

    while (1)
    {
        if (GetAsyncKeyState(VK_XBUTTON1))
        {
            break;
        }
        while (GetAsyncKeyState(VK_LBUTTON))
        {
            DWORD localPlayerBaseAddr;
            ReadProcessMemory(proc, (LPCVOID)(client + hazedumper::signatures::dwLocalPlayer), &localPlayerBaseAddr,
                sizeof(localPlayerBaseAddr), NULL);
            Vector3 localPlayer{ 0,0,0 };
            ReadProcessMemory(proc, (LPCVOID)(localPlayerBaseAddr + hazedumper::netvars::m_vecOrigin),
                &localPlayer, sizeof(Vector3), NULL);

            Vector3 closestEnemy = getClosestEnemy(localPlayer, client, proc);


            aimAt(localPlayer, closestEnemy, client_state, proc);
        }
    }

    return 0;
}

