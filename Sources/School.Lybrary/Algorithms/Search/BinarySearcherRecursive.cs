// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcherRecursive.cs

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Search
{
    // ReSharper disable All
    public class BinarySearcherRecursive : Searcher
    {
        protected override int DoSearch( int[] array, int key )
        {
            return BinarySearchRecursive( array, key, 0, array.Length - 1 );
        }

        private int BinarySearchRecursive( int[] array, int key, int first, int last )
        {
            if( first > last ) {
                return KeyNotFound;
            } else {
                var middle = GetMiddleIndex( first, last );
                if( From( array ).Item( middle ).Is_Greater_than_value( key ) ) {
                    return BinarySearchRecursive( array, key, first, middle - 1 );
                } else if( From( array ).Item( middle ).Is_Less_than_value( key ) ) {
                    return BinarySearchRecursive( array, key, middle + 1, last );
                } else {
                    return middle;
                }
            }
        }

        private int GetMiddleIndex( int first, int last )
        {
            return first + ( last - first )/2;
        }
    }
}