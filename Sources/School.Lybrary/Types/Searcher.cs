// School (c) 2015 Krokodev
// School.Lybrary
// Searcher.cs

namespace School.Lybrary.Types
{
    // ReSharper disable All
    public abstract class Searcher : Algorithm, ISearcher
    {
        #region Constatns

        public const int KeyNotFound = -1;

        #endregion


        #region ISearcher

        int ISearcher.Search( int[] array, int key )
        {
            base.Init( array );
            return DoSearch( array, key );
        }

        IAlgorithm ISearcher.Algorithm
        {
            get { return this; }
        }

        #endregion


        #region Abstracts

        protected abstract int DoSearch( int[] array, int key );

        #endregion
    }
}