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

// 마지막에 삽입
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

	// 리스트에 해당 데이터가 없을 경우 실패
	return false;
}

bool MoveNode(RANode* srcHead, void* data, RANode* dstHead)
{
	RANode* prevNode = srcHead;
	RANode* currNode = srcHead->next;

	// 옮길 노드를 찾는 코드
	while (currNode != NULL)
	{
		// 옮길 노드를 찾았다면
		if (currNode->data == data)
		{
			// 옮길 노드를 src에서 떼네는 코드
			prevNode->next = currNode->next;
			// 만약 떼넨 노드가 가장 마지막 노드였으면 tail 변경
			if (prevNode->next == NULL)
			{
				srcHead->data = prevNode;
			}

			// dest의 맨 앞으로 해당 노드를 옮기는 코드
			RANode* tempNode = dstHead->next;
			dstHead->next = currNode;
			currNode->next = tempNode;
			// 만약 붙인 노드가 가장 마지막 노드였으면 tail 변경
			if (currNode->next == NULL)
			{
				dstHead->data = (void*)currNode;
			}
			return true;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}

	// 리스트에 해당 데이터가 없을 경우 실패
	return false;
}
