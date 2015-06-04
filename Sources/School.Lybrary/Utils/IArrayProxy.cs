// School (c) 2015 Krokodev
// School.Lybrary
// IArrayProxy.cs

namespace School.Lybrary.Utils
{
    public interface IArrayProxy {
        int Value( int index );
        void Swap( int i, int j );
        int Compare( int a, int b );
        IArrayItemProxy Item( int i );
    }
}