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
            foreach( var index in Range( 0, array.Length - 1 ) ) {
                if( From( array ).Item( index ).Is_Equal_to_value( key ) ) {
                    return index;
                }
            }
            return KeyNotFound;
        }
    }
}