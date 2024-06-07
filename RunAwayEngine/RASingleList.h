#pragma once
#include <stdlib.h>
#include "RAType.h"

typedef struct _RANode
{
	struct _RANode* next;
	void* data;
}RANode;

/// <summary>
/// ���ο� ����Ʈ����
/// </summary>
/// <returns>������ ����Ʈ�� head</returns>
RANode* MakeNewList();

/// <summary>
/// head�� �Ӹ��� ������ ����Ʈ ��ü ����.
/// data�� ���� �������� �ʴ´�.
/// </summary>
/// <param name="head"></param>
void DeleteList(RANode* head);

/// <summary>
/// head�� �Ӹ��� ������ ����Ʈ�� data�� �����ϴ��� �˻�
/// �ִٸ� ���� ó�� �߰��� ��带 ����.
/// ���ٸ� NULL�� ����
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
/// <returns>�˻��� Node</returns>
RANode* SearchNode(RANode* head, void* data);

/// <summary>
/// head�� �Ӹ��� ������ ����Ʈ�� �������� Node���� �� �߰�
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
bool AddNode(RANode* head, void* data);

/// <summary>
/// head�� �Ӹ��� ������ ����Ʈ�� data�� �����ϸ� �ش� ��常 ����.
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
bool DeleteNode(RANode* head, void* data);

/// <summary>
/// srcList���� �ش� ��带 �˻� �� �ִٸ� dstList�� �� ������ �̵�.
/// </summary>
/// <param name="srcHead">Data�� ����ִ� ����Ʈ�� Head.</param>
/// <param name="data">ã�� Data</param>
/// <param name="dstHead">������ Node</param>
bool MoveNode(RANode* srcHead, void* data, RANode* dstHead);
