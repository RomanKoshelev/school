// School (c) 2015 Krokodev
// School.Lybrary
// ArrayProxy.cs

namespace School.Lybrary.Utils
{
    // ReSharper disable All
    public class ArrayProxy: IArrayProxy
    {
        #region Ctor

        public ArrayProxy( int[] array, IStatistics statistics )
        {
            _array = array;
            _statistics = statistics;
        }

        #endregion


        #region IArrayProxy

        IArrayItemProxy IArrayProxy.Item( int i )
        {
            return new ArrayItemProxy( this, i );
        }

        int IArrayProxy.Value( int index )
        {
            return _array[ index ];
        }

        void IArrayProxy.Swap( int i, int j )
        {
            _statistics.Swap();
            var array_i = _array[ i ];
            _array[ i ] = _array[ j ];
            _array[ j ] = array_i;
        }

        int IArrayProxy.Compare( int a, int b )
        {
            _statistics.Compare();
            return a - b;
        }

        #endregion


        #region Fields

        private readonly int[] _array;
        private IStatistics _statistics;

        #endregion
    }
}