// School (c) 2015 Krokodev
// School.Lybrary
// LinearSearcher.cs

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Search
{
    // ReSharper disable All
    public class LinearSearcher : Searcher
    {
        protected override int DoSearch( int[] array, int key )
        {
            return LinearSearch( array, key );
        }

        private int LinearSearch( int[] array, int key )
        {
            foreach( var index in Order( 0, array.Length - 1 ) ) {
                if( From( array ).Item( index ).Equal( key ) ) {
                    return index;
                }
            }
            return KeyNotFound;
        }
    }
}