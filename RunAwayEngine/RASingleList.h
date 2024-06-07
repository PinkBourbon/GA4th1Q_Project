#pragma once
#include <stdlib.h>
#include "RAType.h"

typedef struct _RANode
{
	struct _RANode* next;
	void* data;
}RANode;

/// <summary>
/// 새로운 리스트생성
/// </summary>
/// <returns>생성된 리스트의 head</returns>
RANode* MakeNewList();

/// <summary>
/// head를 머리로 가지는 리스트 전체 삭제.
/// data는 따로 삭제하지 않는다.
/// </summary>
/// <param name="head"></param>
void DeleteList(RANode* head);

/// <summary>
/// head를 머리로 가지는 리스트에 data가 존재하는지 검색
/// 있다면 가장 처음 발견한 노드를 리턴.
/// 없다면 NULL을 리턴
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
/// <returns>검색된 Node</returns>
RANode* SearchNode(RANode* head, void* data);

/// <summary>
/// head를 머리로 가지는 리스트의 마지막에 Node생성 및 추가
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
bool AddNode(RANode* head, void* data);

/// <summary>
/// head를 머리로 가지는 리스트에 data가 존재하면 해당 노드만 삭제.
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
bool DeleteNode(RANode* head, void* data);

/// <summary>
/// srcList에서 해당 노드를 검색 후 있다면 dstList의 맨 앞으로 이동.
/// </summary>
/// <param name="srcHead">Data가 들어있는 리스트의 Head.</param>
/// <param name="data">찾을 Data</param>
/// <param name="dstHead">목적지 Node</param>
bool MoveNode(RANode* srcHead, void* data, RANode* dstHead);
