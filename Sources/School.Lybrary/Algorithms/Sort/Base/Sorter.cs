﻿// School (c) 2015 Krokodev
// School.Lybrary
// Sorter.cs

using School.Lybrary.Algorithms.Base;

namespace School.Lybrary.Algorithms.Sort.Base
{
    // ReSharper disable All
    public abstract class Sorter : Algorithm, ISorter
    {
        #region ISorter

        void ISorter.Sort( int[] array )
        {
            base.Init( array );
            DoSort( array );
        }

        IAlgorithm ISorter.Algorithm
        {
            get { return this; }
        }

        #endregion


        #region Abstracts

        protected abstract void DoSort( int[] array );

        #endregion
    }
}