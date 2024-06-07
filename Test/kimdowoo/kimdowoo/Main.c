#include <stdio.h>
#include "RAEngine.h"
#include "RAVector3.h"
#include "RAMatrix3.h"
#include "RAVector2.h"
#include "RAMatrix2.h"
#include "RATimer.h"
#include "RABmpParser.h"
#include "RASingleList.h"
#pragma comment(lib, "RunAwayEngine.lib")
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	printf("%d %d %d\n", rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
	return 0;
}

