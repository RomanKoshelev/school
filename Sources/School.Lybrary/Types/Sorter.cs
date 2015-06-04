// School (c) 2015 Krokodev
// School.Lybrary
// Sorter.cs

namespace School.Lybrary.Types
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

        public IAlgorithm Algorithm
        {
            get { return this; }
            set { }
        }

        #endregion


        #region Abstracts

        protected abstract void DoSort( int[] array );

        #endregion
    }
}