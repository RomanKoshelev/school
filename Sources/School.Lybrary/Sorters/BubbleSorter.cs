﻿// School (c) 2015 Krokodev
// School.Lybrary
// BubbleSorter.cs

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class BubbleSorter
    {
        public static void Sort( int[] arr )
        {
            var n = arr.Length;
            var swapped = false;

            do {
                for( var i = 0; i < n - 1; i++ ) {
                    if( arr[ i ] > arr[ i + 1 ] ) {
                        Swap( arr, i, i + 1 );
                        swapped = true;
                    }
                }
            } while( swapped );
        }

        private static void Swap( int[] arr, int i, int j )
        {
            var arr_i = arr[ i ];
            arr[ i ] = arr[ j ];
            arr[ j ] = arr_i;
        }
    }
}