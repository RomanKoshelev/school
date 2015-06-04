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
            return _array.getValue( _index );
        }
        public bool Greater_than_item( int otherIndex )
        {
            return Value() > _array.getValue( otherIndex );
        }

        public void Swap_with( int otherIndex )
        {
            _array.Swap( _index, otherIndex );
        }

        public bool Less_or_equal_than( int value )
        {
            return Value() <= value;
        }
    }
}