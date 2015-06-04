// School (c) 2015 Krokodev
// School.Lybrary
// ArrayItemProxy.cs

namespace School.Lybrary.Utils
{
    public class ArrayItemProxy
    {
        private readonly ArrayProxy _array;
        private readonly int _index;

        public ArrayItemProxy( ArrayProxy array, int index )
        {
            _array = array;
            _index = index;
        }

        public int Value()
        {
            return _array.Value( _index );
        }

        public bool Is_Greater_than_item( int otherIndex )
        {
            return _array.Compare( Value(), _array.Value( otherIndex ) ) > 0;
        }

        public void Swap_with( int otherIndex )
        {
            _array.Swap( _index, otherIndex );
        }

        public bool Is_LessOrEqual_than_value( int value )
        {
            return _array.Compare( Value(), value ) <= 0;
        }
    }
}