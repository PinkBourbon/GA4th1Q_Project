#pragma once
#include "Monster.h"
#include "Monster2.h"

typedef struct _GameObject GameObject;
typedef struct _Map Map;

GameObject* SetMonsterMgr(GameObject* player, Map* map);

void EnableMonsterMgr();

void EnableMonsterPool();

void EnableMonsterPool2();

void DisableMonsterMgr();