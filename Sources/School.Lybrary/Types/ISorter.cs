using School.Lybrary.Utils;

namespace School.Lybrary.Types
{
    public interface ISorter {
        Statistics GetStatistics();
        void Sort( int[] array );
    }
}