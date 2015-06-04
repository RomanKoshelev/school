// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcher.cs

// ReSharper disable All

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Searchers
{
    public class BinarySearcherIterative : Searcher
    {
        protected override int DoSearch( int[] array, int value )
        {
            return BinarySearchIterative( array, value );
        }

        private int BinarySearchIterative( int[] array, int value )
        {
            // Todo:> BinarySearch http://en.wikipedia.org/wiki/Binary_search_algorithm
            return 0;
        }
    }
}