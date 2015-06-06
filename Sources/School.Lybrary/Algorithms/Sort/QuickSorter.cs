// School (c) 2015 Krokodev
// School.Lybrary
// QuickSorter.cs

using School.Lybrary.Algorithms.Sort.Base;

namespace School.Lybrary.Algorithms.Sort
{
    // ReSharper disable All
    public class QuickSorter : Sorter
    {
        protected override void DoSort( int[] array )
        {
            QuickSort( array, 0, array.Length - 1 );
        }

        private void QuickSort( int[] array, int first, int last )
        {
            if( first < last ) {
                var partition = MakePartition( array, first, last );
                QuickSort( array, first, partition - 1 );
                QuickSort( array, partition + 1, last );
            }
        }

        private int MakePartition( int[] array, int first, int last )
        {
            var pivotIndex = ChoosePivotIndex( array, first, last );
            var pivotValue = array[ pivotIndex ];
            In( array ).Swap( pivotIndex, last );

            var partition = first;

            foreach( var index in Order( first, last - 1 ) ) {
                if( From( array ).Item( index ).LessOrEqual_than( pivotValue ) ) {
                    Then.In( array ).Swap( partition, index );
                    partition++;
                }
            }

            In( array ).Swap( pivotIndex, partition );

            return partition;
        }

        private static int ChoosePivotIndex( int[] array, int first, int last )
        {
            return last;
        }
    }
}