using School.Lybrary.Utils;

namespace School.Lybrary.Sorters
{
    public interface ISorter {
        Statistics GetStatistics();
        void Sort( int[] array );
    }
}