// School (c) 2015 Krokodev
// School.Lybrary
// AbstractSorter.cs

using System.Collections.Generic;
using School.Lybrary.Utils;

namespace School.Lybrary.Types
{
    // ReSharper disable All
    public abstract class AbstractSorter : ISorter
    {
        #region ISorter

        Statistics ISorter.GetStatistics()
        {
            return statistics;
        }

        void ISorter.Sort( int[] array )
        {
            statistics = new Statistics( array.Length );
            DoSort( array );
        }

        #endregion


        #region Fields

        private Statistics statistics;

        #endregion


        #region Utils

        protected internal ArrayProxy In( int[] array )
        {
            return new ArrayProxy( array, statistics );
        }

        protected AbstractSorter Then
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

        #endregion


        #region Abstracts

        protected abstract void DoSort( int[] array );

        #endregion
    }
}