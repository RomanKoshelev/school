// School (c) 2015 Krokodev
// School.Lybrary
// ISearcher.cs

using School.Lybrary.Algorithms.Base;

namespace School.Lybrary.Algorithms.Search.Base
{
    public interface ISearcher
    {
        int Search( int[] array, int key );
        IAlgorithm Algorithm { get; }
    }
}