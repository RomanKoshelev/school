// School (c) 2015 Krokodev
// School.Lybrary
// ISorter.cs

namespace School.Lybrary.Types
{
    public interface ISorter
    {
        void Sort( int[] array );
        IAlgorithm Algorithm { get; }
    }
}