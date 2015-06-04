// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcher.cs

// ReSharper disable All

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Searchers
{
    public class BinarySearcherRecursive : Searcher
    {
        protected override int DoSearch( int[] array, int value )
        {
            return BinarySearchRecursive( array, value );
        }

        private int BinarySearchRecursive( int[] array, int value )
        {
            // Todo:> BinarySearch http://en.wikipedia.org/wiki/Binary_search_algorithm
            return 0;
        }
    }
}