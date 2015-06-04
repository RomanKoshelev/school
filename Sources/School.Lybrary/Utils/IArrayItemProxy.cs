// School (c) 2015 Krokodev
// School.Lybrary
// IArrayItemProxy.cs

namespace School.Lybrary.Utils
{
    public interface IArrayItemProxy
    {
        bool Greater_than_item( int otherIndex );
        bool LessOrEqual_than( int value );
        bool Equal( int value );
        bool Greater_than( int value );
        bool Less_than( int value );
    }
}