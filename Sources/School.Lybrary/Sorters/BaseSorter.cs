// School (c) 2015 Krokodev
// School.Lybrary
// BaseSorter.cs

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public abstract class BaseSorter
    {
        protected static void Swap( int[] array, int i, int j )
        {
            var array_i = array[ i ];
            array[ i ] = array[ j ];
            array[ j ] = array_i;
        }
    }
}