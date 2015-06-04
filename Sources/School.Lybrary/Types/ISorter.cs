// School (c) 2015 Krokodev
// School.Lybrary
// ISorter.cs

using School.Lybrary.Utils;

namespace School.Lybrary.Types
{
    public interface ISorter
    {
        Statistics GetStatistics();
        void Sort( int[] array );
    }
}