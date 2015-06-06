// School (c) 2015 Krokodev
// School.Lybrary
// Algorithm.cs

using System.Collections.Generic;
using System.Linq;
using School.Lybrary.Utils;

namespace School.Lybrary.Algorithms.Base
{
    public abstract class Algorithm : IAlgorithm
    {
        #region IAlgorithm

        IStatistics IAlgorithm.Statistics
        {
            get { return _statistics; }
        }

        #endregion


        #region Protected

        protected void Init( int[] array )
        {
            _statistics = new Statistics( array.Length );
        }

        protected static IEnumerable< int > Order( int first, int last )
        {
            return
                first <= last
                    ? Enumerable.Range( first, last - first + 1 )
                    : Order( last, first ).Reverse();
        }

        protected Algorithm Then
        {
            get { return this; }
        }

        protected IArrayProxy From( int[] array )
        {
            return new ArrayProxy( array, _statistics );
        }

        protected internal IArrayProxy In( int[] array )
        {
            return new ArrayProxy( array, _statistics );
        }

        protected IArrayItemProxy Value( int[] array, int index )
        {
            return From( array ).Item( index );
        }

        protected void StopStatistics()
        {
            _statistics.Stop();
        }

        #endregion


        #region Fields

        private IStatistics _statistics;

        #endregion
    }
}