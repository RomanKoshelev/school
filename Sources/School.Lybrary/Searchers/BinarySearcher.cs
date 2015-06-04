// School (c) 2015 Krokodev
// School.Lybrary
// BinarySearcher.cs

// ReSharper disable All

using School.Lybrary.Types;

namespace School.Lybrary.Searchers
{
    public class BinarySearcher : Searcher
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
        private int BinarySearchIterative( int[] array, int value )
        {
            // Todo:> BinarySearch http://en.wikipedia.org/wiki/Binary_search_algorithm
            return 0;
        }
    }
}