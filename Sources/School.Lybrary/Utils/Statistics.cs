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
            _active = true;
        }

        #endregion


        #region IStatistics

        void IStatistics.Swap()
        {
            if( _active ) {
                _swaps++;
            }
        }

        void IStatistics.Compare()
        {
            if( _active ) {
                _comparisons++;
            }
        }

        void IStatistics.Stop()
        {
            _active = false;
        }

        #endregion


        #region Overrides

        public override string ToString()
        {
            var str = "";
            str += ToString( "Size", _size );
            str += ToString( "Comparisons", _comparisons );
            str += ToString( "Swaps", _swaps );
            return str;
        }

        #endregion


        #region Fields

        private int _comparisons;
        private int _swaps;
        private readonly int _size;
        private bool _active;

        #endregion


        #region Utils

        private static string ToString( string name, int value )
        {
            return value == 0 ? "" : string.Format( "{0}: {1}\n", name, value );
        }

        #endregion
    }
}