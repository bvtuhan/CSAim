#pragma once

#include "../Offsets/Offsets.h"
#include "Vector3.h"
#include "../Offsets/Offsets.h"
#include <Windows.h>

void aimAt(Vector3 local, Vector3 target, DWORD client_state, HANDLE game);

Vector3 getClosestEnemy(Vector3 local, DWORD client, HANDLE game);