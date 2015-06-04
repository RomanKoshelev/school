// School (c) 2015 Krokodev
// School.Lybrary
// InsertionSorter.cs

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Sorters
{
    // ReSharper disable All
    public class InsertionSorter : Sorter
    {
        protected override void DoSort( int[] array )
        {
            InsertionSort( array );
        }

        private void InsertionSort( int[] array )
        {
            foreach( var inputIndex in Range( 1, array.Length - 1 ) ) {
                var inputValue = array[ inputIndex ];
                var searchIndex = inputIndex - 1;
                while( searchIndex >= 0 ) {
                    if( In( array ).Item( searchIndex ).Is_Greater_than_item( searchIndex + 1 ) ) {
                        Then.In( array ).Swap( searchIndex, searchIndex + 1 );
                    }
                    searchIndex--;
                }
            }
        }
    }
}