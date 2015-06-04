// School (c) 2015 Krokodev
// School.Lybrary
// BubbleSorter.cs

using School.Lybrary.Types;

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class BubbleSorter : BaseSorter
    {
        protected override void DoSort( int[] array )
        {
            BubleSort( array );
        }

        public void BubleSort( int[] array )
        {
            bool swapped;

            do {
                swapped = false;
                for( var index = 0; index < array.Length - 1; index++ ) {
                    if( In( array ).Item( index ).Is_Greater_than_item( index + 1 ) ) {
                        In( array ).Swap( index, index + 1 );
                        swapped = true;
                    }
                }
            } while( swapped );
        }
    }
}