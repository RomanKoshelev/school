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
            return BinarySearch( array, value );
        }

        private int BinarySearch( int[] array, int value )
        {
            return 0;
        }
    }
}