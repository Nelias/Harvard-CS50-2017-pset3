/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // implementation of a binary search
    
    if (n < 0)
    {
        return false;
    }
    
    if (n == 1)
    {
        if (value == values[0])
        {
          return true;
        }
        else
        {
          return false;
        }
     }

    int right_bound = n;
    int left_bound = 0;
  
    while (left_bound <= right_bound) 
    {
        int middle = (right_bound + left_bound) / 2;
        
        if (value == values[middle]) 
        {
            return true;
        }
        else if (value > values[middle])
        {
            left_bound = middle + 1;
        }
        else
        {
            right_bound = middle - 1;
        }
    }

    return false;
}

/**
 * Sorts an array of n values.
 */
void sort(int values[], int n)
{
    // implementation of selection sort
    int temp;
	for (int i = 0; i < n - 1; i++)
    {
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (values[j] > values[j + 1])
			{
				temp = values[j + 1];
				values[j + 1] = values[j];
				values[j] = temp;
			}
		}
    }
}
