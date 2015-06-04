// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcherIterative.cs

using School.Lybrary.Types;

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
            // Todo:> BinarySearch http://en.wikipedia.org/wiki/Binary_search_algorithm
            return 0;
        }
    }
}