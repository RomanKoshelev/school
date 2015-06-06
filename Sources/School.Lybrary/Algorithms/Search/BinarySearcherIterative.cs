// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcherIterative.cs

using School.Lybrary.Algorithms.Search.Base;

namespace School.Lybrary.Algorithms.Search
{
    // ReSharper disable All
    public class BinarySearcherIterative : Searcher
    {
        protected override int DoSearch( int[] array, int key )
        {
            return BinarySearchIterative( array, key );
        }

        private int BinarySearchIterative( int[] array, int key )
        {
            var first = 0;
            var last = array.Length - 1;
            while( first <= last ) {
                var middle = ( first + last )/2;
                if( Value( array, middle ).Equal( key ) ) {
                    return middle;
                }
                if( Value( array, middle ).Less_than( key ) ) {
                    first = middle + 1;
                } else {
                    last = middle - 1;
                }
            }
            return KeyNotFound;
        }
    }
}