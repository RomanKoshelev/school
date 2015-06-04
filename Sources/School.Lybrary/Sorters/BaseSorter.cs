// School (c) 2015 Krokodev
// School.Lybrary
// BaseSorter.cs

using System.Collections.Generic;
using School.Lybrary.Utils;

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public abstract class BaseSorter : ISorter
    {
        public BaseSorter()
        {
            statistics = new Statistics();
        }
        Statistics ISorter.GetStatistics()
        {
            return statistics;
        }
        
        private Statistics statistics;

        protected internal ArrayProxy In( int[] array )
        {
            return new ArrayProxy( array, statistics );
        }

        protected BaseSorter Then
        {
            get { return this; }
        }

        protected static IEnumerable< int > Range( int start, int end )
        {
            var range = new int[end - start + 1];
            for( var i = 0; i < range.Length; i++ ) {
                range[ i ] = start + i;
            }
            return range;
        }

        public abstract void Sort( int[] array );
    }
}