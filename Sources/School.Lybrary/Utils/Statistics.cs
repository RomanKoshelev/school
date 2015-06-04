// School (c) 2015 Krokodev
// School.Lybrary
// Statistics.cs

namespace School.Lybrary.Utils
{
    public class Statistics : IStatistics
    {
        #region Ctor

        public Statistics( int size )
        {
            _size = size;
        }

        #endregion


        #region IStatistics

        void IStatistics.Swap()
        {
            _swaps++;
        }

        void IStatistics.Compare()
        {
            _comparisons++;
        }

        #endregion


        #region Overrides

        public override string ToString()
        {
            var str = "";
            str += string.Format( "Size: {0}", _size );
            str += "\n";
            str += string.Format( "Comparisons: {0}", _comparisons );
            str += "\n";
            str += string.Format( "Swaps: {0}", _swaps );
            return str;
        }

        #endregion


        #region Fields

        private int _comparisons;
        private int _swaps;
        private readonly int _size;

        #endregion
    }
}