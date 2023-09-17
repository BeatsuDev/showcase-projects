#ifndef SWAP_H
#define SWAP_H

void swap(long *i, long *j)
{
    long temp = *i;
    *i = *j;
    *j = temp;
}
#endif