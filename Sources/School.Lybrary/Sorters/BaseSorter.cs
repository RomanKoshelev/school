// School (c) 2015 Krokodev
// School.Lybrary
// BaseSorter.cs

using School.Lybrary.Utils;

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public abstract class BaseSorter
    {
        private static Statistics statistics;

        protected static ArrayProxy In( int[] array )
        {
            return new ArrayProxy( array, statistics );
        }
    }
}