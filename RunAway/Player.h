#pragma once

typedef struct _RACamera RACamera;
typedef struct _Map Map;
typedef struct _GameObject GameObject;

GameObject* SetPlayer(RACamera* camera, Map* map, GameObject* outOutOfBody);

void DisablePlayer();