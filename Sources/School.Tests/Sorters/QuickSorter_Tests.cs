// School (c) 2015 Krokodev
// School.Tests
// QuickSorter_Tests.cs

using NUnit.Framework;
using School.Lybrary.Sorters;
using School.Lybrary.Utils;

// ReSharper disable All

namespace School.Tests.Sorters
{
    [TestFixture]
    public class QuickSorter_Tests : BaseSorterTests
    {
        [Test]
        public void Array_9876543210_is_sorted_in_ascending_order()
        {
            ISorter sorter = new QuickSorter();
            var array = new int[] { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
            sorter.Sort( array );
            Print( array );
            Print( sorter.GetStatistics() );
            Assert_is_ascending( array );
        }

        [Test]
        public void Random_array_is_sorted_ascendently()
        {
            var sorter = new QuickSorter();
            var array = CreateRandomArray( 70 );
            sorter.Sort( array );
            Print( array );
            Assert_is_ascending( array );
        }
    }
}