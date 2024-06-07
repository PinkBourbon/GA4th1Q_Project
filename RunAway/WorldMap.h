#pragma once

typedef struct _Map Map;

typedef enum _eMapState
{
	WALL = 0x00000000,
	TILE = 0x00ffffff,
	PASSWALL = 0x0000ff00,
	TREE01 = 0x00fffc00,
	TREE02 = 0x0000ffd9,
	TREE03 = 0x005100ff,
	TREE04 = 0x008000ff,
	TREE05 = 0x00ff6a00,

}eMapState;

Map* SetWorldMap();
void EnableWorldMap();
void DisableWorldMap();