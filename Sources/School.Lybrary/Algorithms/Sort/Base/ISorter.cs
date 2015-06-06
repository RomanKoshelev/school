// School (c) 2015 Krokodev
// School.Lybrary
// ISorter.cs

using School.Lybrary.Algorithms.Base;

namespace School.Lybrary.Algorithms.Sort.Base
{
    public interface ISorter
    {
        void Sort( int[] array );
        IAlgorithm Algorithm { get; }
    }
}