// School (c) 2015 Krokodev
// School.Lybrary
// QuickSorter.cs

using School.Lybrary.Types;

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class QuickSorter : BaseSorter
    {
        protected override void DoSort( int[] array )
        {
            QuickSort( array, 0, array.Length - 1 );
        }


        private void QuickSort( int[] array, int lo, int hi )
        {
            if( lo < hi ) {
                var p = Partition( array, lo, hi );
                QuickSort( array, lo, p - 1 );
                QuickSort( array, p + 1, hi );
            }
        }

        private int Partition( int[] array, int lo, int hi )
        {
            var pivotIndex = ChoosePivotIndex( array, lo, hi );
            var pivotValue = array[ pivotIndex ];
            In( array ).Swap( pivotIndex, hi );

            var partition = lo;

            foreach( var index in Range( lo, hi - 1 ) ) {
                if( In( array ).Item( index ).Is_LessOrEqual_than_value( pivotValue ) ) {
                    Then.In( array ).Swap( partition, index );
                    partition++;
                }
            }

            In( array ).Swap( partition, pivotIndex );
            return partition;
        }

        private static int ChoosePivotIndex( int[] array, int lo, int hi )
        {
            return hi;
        }
    }
}