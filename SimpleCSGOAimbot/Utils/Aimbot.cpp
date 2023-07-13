#include "Aimbot.h"
#include "../Offsets/Offsets.h"
#include <Windows.h>

void aimAt(Vector3 local, Vector3 target, DWORD client_state,HANDLE game)
{
    //--debug
    float curYaw;
    float curPitch;
    ReadProcessMemory(game, (LPCVOID)(client_state + hazedumper::signatures::dwClientState_ViewAngles),
        &curYaw, sizeof(float), NULL);
    ReadProcessMemory(game, (LPCVOID)(client_state + hazedumper::signatures::dwClientState_ViewAngles + 0x4),
        &curPitch, sizeof(float), NULL);
    //--debug
    float yaw = local.yawAngle(target);
    float pitch = local.pitchAngle(target);

    if (pitch > 89) pitch = 89;
    if (pitch < -89) pitch = -89;
    if (yaw > 180) yaw = 180;
    if (yaw < -180) yaw = -180;

    WriteProcessMemory(game, (LPVOID)(client_state + hazedumper::signatures::dwClientState_ViewAngles),
        &pitch, sizeof(float), NULL);
    WriteProcessMemory(game, (LPVOID)(client_state + hazedumper::signatures::dwClientState_ViewAngles + 0x4),
        &yaw, sizeof(float), NULL);
}

Vector3 getClosestEnemy(Vector3 local, DWORD client, HANDLE game)
{
    DWORD entityList = client + hazedumper::signatures::dwEntityList;
    //ReadProcessMemory(game, (LPCVOID)(client + hazedumper::signatures::dwEntityList),
    //    &entityList, sizeof(entityList), NULL);

    Vector3 tempEnemy{ 0,0,0 };
    for (int i = 1; i < 12; i++) {

        DWORD firstEnemy;
        ReadProcessMemory(game, (LPCVOID)(entityList + (i * 0x10)), &firstEnemy, sizeof(DWORD), NULL);

        if (firstEnemy == 0) continue;

        int health;
        ReadProcessMemory(game, (LPCVOID)(firstEnemy + hazedumper::netvars::m_iHealth),
            &health, sizeof(int), NULL);

        if (health < 1 || health > 100) continue;

        Vector3 enemyCoords{ 0,0,0 };
        ReadProcessMemory(game, (LPCVOID)(firstEnemy + hazedumper::netvars::m_vecOrigin),
            &enemyCoords, sizeof(Vector3), NULL);


        if (local.magnitude(enemyCoords) < local.magnitude(tempEnemy)
            || (tempEnemy.x == 0 && tempEnemy.y == 0 && tempEnemy.z == 0)) {
            tempEnemy = enemyCoords;
        }

    }

    return tempEnemy;
}
