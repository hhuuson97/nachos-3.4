/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

int A[100];

int
main()
{
    int i, j, tmp;
    int n;

    PrintString("Nhap n (trong khoang 1 den 100): ");
    n = ReadInt();

    for (i = 0; i < n; i++) {
        PrintString("Nhap A[");
        PrintInt(i);
        PrintString("]= ");
        A[i] = ReadInt();
    }

    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
	   if (A[j] > A[j + 1]) {
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
    
    PrintString("Mang duoc sap xep tang dan:\n");
    for (i = 0; i < n; i++) {
        PrintInt(A[i]);
        if (i%10==9) PrintString("\n");
        else PrintString(" ");
    }

    Halt();  
}
