﻿// School (c) 2015 Krokodev
// School.Lybrary
// Algorithm.cs

using System.Collections.Generic;
using System.Linq;
using School.Lybrary.Utils;

namespace School.Lybrary.Types
{
    public abstract class Algorithm : IAlgorithm
    {
        #region IAlgorithm

        Statistics IAlgorithm.GetStatistics()
        {
            return _statistics;
        }

        #endregion


        #region Protected

        protected void Init( int[] array )
        {
            _statistics = new Statistics( array.Length );
        }

        protected static IEnumerable< int > Range( int first, int last )
        {
            return Enumerable.Range( first, last - first + 1 );
        }

        protected static IEnumerable< int > Indices( int[] array )
        {
            return Range( 0, array.Length - 1 );
        }

        protected Algorithm Then
        {
            get { return this; }
        }

        protected internal IArrayProxy In( int[] array )
        {
            return new ArrayProxy( array, _statistics );
        }

        #endregion


        #region Fields

        private Statistics _statistics;

        #endregion
    }
}