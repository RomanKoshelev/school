// School (c) 2015 Krokodev
// School.Lybrary
// ArrayProxy.cs

namespace School.Lybrary.Utils
{
    // ReSharper disable All
    public class ArrayProxy
    {
        public ArrayProxy( int[] array, Statistics statistics )
        {
            _array = array;
            _statistics = statistics;
        }

        public ArrayItemProxy Item( int i )
        {
            return new ArrayItemProxy( this, i );
        }

        private readonly int[] _array;
        private Statistics _statistics;

        public int Value( int index )
        {
            return _array[ index ];
        }

        public void Swap( int i, int j )
        {
            _statistics.Swap();
            var array_i = _array[ i ];
            _array[ i ] = _array[ j ];
            _array[ j ] = array_i;
        }

        public int Compare( int a, int b )
        {
            _statistics.Compare();
            return a - b;
        }
    }
}