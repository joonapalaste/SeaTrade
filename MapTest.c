#include <exec/types.h>
#include <exec/memory.h>
#include <libraries/dos.h>
#include <stdio.h>

void display(UBYTE seen[])
{
    UWORD i;
    for (i=0; i<256; i++)
    {
        if (seen[i])
            printf("%2X ", i);
        else
            printf("   ");
        if ((i&15)==15)
            printf("\n");
    }
}

int main()
{
    UBYTE seen[256];
    ULONG i;
    UBYTE *mem;
    BPTR file;
    file=Open("IslandMap.dat", MODE_OLDFILE);
    if (!file)
    {
        printf("Can't open IslandMap.dat!\n");
        return 1;
    }
    mem=AllocVec(720000, MEMF_CLEAR);
    if (!mem)
    {
        printf("Out of memory!\n");
        Close(file);
        return 1;
    }
    Read(file, mem, 720000);
    Close(file);
    for (i=0; i<256; i++)
        seen[i]=0;
    for (i=0; i<640000; i++)
        seen[*(mem+i)]=1;
    display(seen);
    for (i=0; i<256; i++)
        seen[i]=0;
    for (i=640000; i<720000; i++)
        seen[*(mem+i)]=1;
    display(seen);
    FreeVec(mem);
    return 0;
}
