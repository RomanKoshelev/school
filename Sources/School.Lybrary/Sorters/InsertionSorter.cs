// School (c) 2015 Krokodev
// School.Lybrary
// InsertionSorter.cs

using School.Lybrary.Types;

namespace School.Lybrary.Sorters
{
    // ReSharper disable All
    public class InsertionSorter : AbstractSorter
    {
        protected override void DoSort( int[] array )
        {
            InsertionSort( array );
        }

        private void InsertionSort( int[] array ) {}
    }
}