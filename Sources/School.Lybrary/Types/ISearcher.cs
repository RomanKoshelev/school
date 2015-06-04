// School (c) 2015 Krokodev
// School.Lybrary
// ISearcher.cs

namespace School.Lybrary.Types
{
    public interface ISearcher
    {
        int Search( int[] array, int key );
        IAlgorithm Algorithm { get; }
    }
}