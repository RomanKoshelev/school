// School (c) 2015 Krokodev
// School.Lybrary
// Searcher.cs

using School.Lybrary.Searchers;

namespace School.Lybrary.Types
{
    // ReSharper disable All
    public abstract class Searcher : Algorithm, ISearcher
    {
        #region Constatns

        public const int NotFound = int.MinValue;

        #endregion


        #region ISearcher

        int ISearcher.Search( int[] array, int value )
        {
            base.Init( array );
            return DoSearch( array, value );
        }

        IAlgorithm ISearcher.Algorithm
        {
            get { return this; }
        }

        #endregion


        #region Abstracts

        protected abstract int DoSearch( int[] array, int value );

        #endregion
    }
}