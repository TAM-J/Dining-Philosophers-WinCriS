#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;
CRITICAL_SECTION STICKS[5];
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int phil = *((int*)lpParameter), eat = 0;
	while (eat<1000000)
	{
		EnterCriticalSection(&STICKS[(phil+phil%2)%5]);
		if (TryEnterCriticalSection((&STICKS[(phil +1-phil % 2) % 5])))
		{
		//	cout << phil << ": is eating" << endl;
			eat++;
			LeaveCriticalSection((&STICKS[(phil + 1 - phil % 2) % 5]));
		}
		LeaveCriticalSection(&STICKS[(phil + phil % 2) % 5]);
	}
	return 1;
}
int main()
{
	clock_t tStart = clock();
	for (int i = 0; i < 5; i++)
	{
		InitializeCriticalSection(&STICKS[i]);
	}
	int arr[] = { 0,1, 2 ,3 ,4 };
	HANDLE hndl[5];
	for (int i = 0; i < 5; i++)
	{
		hndl[i]=CreateThread(NULL, NULL, ThreadProc, &arr[i], NULL, NULL);
	}
	WaitForMultipleObjects(5, hndl, 1, INFINITE);
	for (int i = 0; i < 5; i++)
	{
		DeleteCriticalSection(&STICKS[i]);
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}
