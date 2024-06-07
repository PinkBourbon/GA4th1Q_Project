#include "RASingleList.h"

RANode* MakeNewList()
{
	RANode* head;
	head = (RANode*)malloc(sizeof(RANode));
	if (head == NULL)
	{
		return NULL;
	}
	head->data = (void*)head;
	head->next = NULL;
	return head;
}

void DeleteList(RANode* head)
{
	while (head != NULL)
	{
		RANode* forFreeNode = head;
#pragma warning(push)
#pragma warning(disable:6001)
		head = head->next;
#pragma warning(pop)
		free(forFreeNode);
	}
}

RANode* SearchNode(RANode* head, void* data)
{
	while (head != NULL)
	{
		if (head->data == data)
		{
			return head;
		}
		head = head->next;
	}
	return head;
}

// �������� ����
bool AddNode(RANode* head, void* data)
{
	RANode* tail = head->data;
	RANode* newNode = (RANode*)malloc(sizeof(RANode));
	if (newNode == NULL)
	{
		return false;
	}
	newNode->data = data;
	newNode->next = NULL;
	head->data = (void*)newNode;

	tail->next = newNode;

	return true;
}

bool DeleteNode(RANode* head, void* data)
{
	RANode* prevNode = head;
	RANode* currNode = head->next;

	while (currNode != NULL)
	{
		if (currNode->data == data)
		{
			prevNode->next = currNode->next;
			if (prevNode->next == NULL)
			{
				head->data = prevNode;
			}
			free(currNode);
			return true;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}

	// ����Ʈ�� �ش� �����Ͱ� ���� ��� ����
	return false;
}

bool MoveNode(RANode* srcHead, void* data, RANode* dstHead)
{
	RANode* prevNode = srcHead;
	RANode* currNode = srcHead->next;

	// �ű� ��带 ã�� �ڵ�
	while (currNode != NULL)
	{
		// �ű� ��带 ã�Ҵٸ�
		if (currNode->data == data)
		{
			// �ű� ��带 src���� ���״� �ڵ�
			prevNode->next = currNode->next;
			// ���� ���� ��尡 ���� ������ ��忴���� tail ����
			if (prevNode->next == NULL)
			{
				srcHead->data = prevNode;
			}

			// dest�� �� ������ �ش� ��带 �ű�� �ڵ�
			RANode* tempNode = dstHead->next;
			dstHead->next = currNode;
			currNode->next = tempNode;
			// ���� ���� ��尡 ���� ������ ��忴���� tail ����
			if (currNode->next == NULL)
			{
				dstHead->data = (void*)currNode;
			}
			return true;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}

	// ����Ʈ�� �ش� �����Ͱ� ���� ��� ����
	return false;
}
