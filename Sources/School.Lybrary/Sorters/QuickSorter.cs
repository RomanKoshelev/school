﻿// School (c) 2015 Krokodev
// School.Lybrary
// QuickSorter.cs

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class QuickSorter : BaseSorter
    {
        public static void Sort( int[] array )
        {
            Sort( array, 0, array.Length - 1 );
        }

        private static void Sort( int[] array, int lo, int hi )
        {
            if( lo < hi ) {
                var p = Partition( array, lo, hi );
                Sort( array, lo, p - 1 );
                Sort( array, p + 1, hi );
            }
        }
        private static int Partition( int[] array, int lo, int hi )
        {
            var pivotIndex = ChoosePivotIndex( array, lo, hi );
            var pivotValue = array[ pivotIndex ];
            Swap( array, pivotIndex, hi );

            var partition = lo;
            for( var index = lo; index <= ( hi - 1 ); index++ ) {
                if( array[ index ] <= pivotValue ) {
                    Swap( array, partition, index );
                    partition++;
                }
            }
            Swap( array, partition, pivotIndex );
            return partition;
        }

        private static int ChoosePivotIndex( int[] array, int lo, int hi )
        {
            return hi;
        }
    }
}