// School (c) 2015 Krokodev
// School.Lybrary
// BubbleSorter.cs

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class BubbleSorter : BaseSorter
    {
        public static void Sort( int[] array )
        {
            bool swapped;

            do {
                swapped = false;
                for( var index = 0; index < array.Length - 1; index++ ) {
                    if( array[ index ] > array[ index + 1 ] ) {
                        Swap( array, index, index + 1 );
                        swapped = true;
                    }
                }
            } while( swapped );
        }
    }
}