// School (c) 2015 Krokodev
// School.Lybrary
// LinearSearcher.cs

using School.Lybrary.Types;

namespace School.Lybrary.Searchers
{
    public class LinearSearcher : Searcher
    {
        protected override int DoSearch( int[] array, int value )
        {
            return BinarySearch( array, value );
        }

        private int BinarySearch( int[] array, int value )
        {
            foreach( var index in Indices( array ) ) {
                if(In(array).Item( index ).Is_Equal_to_value( value ))
                { }
            }
            return NotFound;
        }
    }
}