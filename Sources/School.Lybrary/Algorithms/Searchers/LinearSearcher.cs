// School (c) 2015 Krokodev
// School.Lybrary
// LinearSearcher.cs

using School.Lybrary.Types;

namespace School.Lybrary.Algorithms.Searchers
{
    // ReSharper disable All
    public class LinearSearcher : Searcher
    {
        protected override int DoSearch( int[] array, int value )
        {
            return LinearSearch( array, value );
        }

        private int LinearSearch( int[] array, int value )
        {
            foreach( var index in Indices( array ) ) {
                if( In( array ).Item( index ).Is_Equal_to_value( value ) ) {
                    return index;
                }
            }
            return NotFound;
        }
    }
}