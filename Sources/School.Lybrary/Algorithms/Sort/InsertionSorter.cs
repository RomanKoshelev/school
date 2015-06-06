// School (c) 2015 Krokodev
// School.Lybrary
// InsertionSorter.cs

using School.Lybrary.Algorithms.Sort.Base;

namespace School.Lybrary.Algorithms.Sort
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
            foreach( var inputIndex in Order( 1, array.Length - 1 ) ) {
                var inputValue = array[ inputIndex ];
                var searchIndex = inputIndex - 1;
                while( searchIndex >= 0 ) {
                    if( From( array ).Item( searchIndex ).Greater_than_item( searchIndex + 1 ) ) {
                        Then.In( array ).Swap( searchIndex, searchIndex + 1 );
                    }
                    searchIndex--;
                }
            }
        }
    }
}