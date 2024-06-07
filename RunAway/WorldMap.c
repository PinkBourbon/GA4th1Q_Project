#include "WorldMap.h"

#include <malloc.h>

#include "RAGameEngine.h"
#include "ReadMapData.h"
#include "RARGB.h"
#include "RAMacro.h"

#include "define.h"



static Map _map;
static GameObject** _mapObjects;

Map* SetWorldMap()
{
	_map = ReadMapData(MAP_DATA);
	uint16 width = _map.width;
	uint16 height = _map.height;
	_mapObjects = (GameObject**)malloc(sizeof(GameObject*) * width * height);
	if (_mapObjects == NULL)
	{
		return NULL;
	}

	for (uint16 i = 0; i < height; ++i)
	{
		for (uint16 j = 0; j < width; ++j)
		{
			uint16 index = i * width + j;
			_mapObjects[index] = AllocGameObject();
			_mapObjects[index]->isLeftDir = true;
			_mapObjects[index]->posX = (float)(j * 150 + 75);
			_mapObjects[index]->posY = (float)(i * 150 + 75);
			_mapObjects[index]->Start = nullptr;
			_mapObjects[index]->Update = nullptr;
			
			_mapObjects[index]->animArray = (RAAnimation*)malloc(sizeof(RAAnimation));
			_mapObjects[index]->animSize = 0;
			_mapObjects[index]->currAnimIndex = 0;

			SetAnimation(_mapObjects[index]->animArray, 0, 1000, 1);

			switch (_map.mapArray[index].argb)
			{
				case WALL:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, WALL_0);
				}
				break;
				case TILE:
				{
					_mapObjects[index]->layer = LAYER_TILE;
					SetImage(_mapObjects[index]->animArray, 0, 0, TILE_0);
				}
				break;
				case PASSWALL:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, WALL_1);
				}
				break;
				case TREE01:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, TREE_0);
				}
				break;
				case TREE02:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, TREE_1);
				}
				break;
				case TREE03:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, TREE_2);
				}
				break;
				case TREE04:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, TREE_3);
				}
				break;
				case TREE05:
				{
					_mapObjects[index]->layer = LAYER_COMMON_OBJECT;
					SetImage(_mapObjects[index]->animArray, 0, 0, TREE_4);
				}
				break;
				default:
					Crash();
					break;
			}
		}
	}

	return &_map;
}

void EnableWorldMap()
{
	uint16 height = _map.height;
	uint16 width = _map.width;
	for (uint16 i = 0; i < height; ++i)
	{
		for (uint16 j = 0; j < width; ++j)
		{
			EnableGameObject(_mapObjects[i * width + j]);
		}
	}
}

void DisableWorldMap()
{
	uint16 height = _map.height;
	uint16 width = _map.width;
	for (uint16 i = 0; i < height; ++i)
	{
		for (uint16 j = 0; j < width; ++j)
		{
			DisableGameObject(_mapObjects[i * width + j]);
		}
	}
}

