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

        bool IArrayItemProxy.Is_Greater_than_item( int otherIndex )
        {
            return _array.Compare( Value(), _array.Value( otherIndex ) ) > 0;
        }

        bool IArrayItemProxy.Is_LessOrEqual_than_value( int value )
        {
            return _array.Compare( Value(), value ) <= 0;
        }

        bool IArrayItemProxy.Is_Equal_to_value( int value )
        {
            return _array.Compare( Value(), value ) == 0;
        }

        public bool Is_Greater_than_value( int value )
        {
            return _array.Compare( Value(), value ) > 0;
        }

        public bool Is_Less_than_value( int value )
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