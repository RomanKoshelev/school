// School (c) 2015 Krokodev
// School.Lybrary
// ArrayItemProxy.cs

namespace School.Lybrary.Utils
{
    public class ArrayItemProxy : IArrayItemProxy
    {
        #region Ctor

        public ArrayItemProxy( IArrayProxy array, int index )
        {
            _array = array;
            _index = index;
        }

        #endregion


        #region IArrayItemProxy

        bool IArrayItemProxy.Greater_than_item( int otherIndex )
        {
            return _array.Compare( Value(), _array.Value( otherIndex ) ) > 0;
        }

        bool IArrayItemProxy.LessOrEqual_than( int value )
        {
            return _array.Compare( Value(), value ) <= 0;
        }

        bool IArrayItemProxy.Equal( int value )
        {
            return _array.Compare( Value(), value ) == 0;
        }

        public bool Greater_than( int value )
        {
            return _array.Compare( Value(), value ) > 0;
        }

        public bool Less_than( int value )
        {
            return _array.Compare( Value(), value ) < 0;
        }

        #endregion


        #region Fields

        private readonly IArrayProxy _array;
        private readonly int _index;

        #endregion


        #region Utils

        private int Value()
        {
            return _array.Value( _index );
        }

        #endregion
    }
}