// School (c) 2015 Krokodev
// School.Tests
// Sorter_Tests.cs

using NUnit.Framework;
using School.Lybrary.Sorters;

// ReSharper disable All

namespace School.Tests.Sorters
{
    [TestFixture]
    public class BubbleSorter_Tests : SorterTestsBase
    {
        [Test]
        public void Bubble_9876543210_is_sorted_in_ascending_order()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), Create9876543210Array() );
        }

        [Test]
        public void Bubble_RandomArray_is_sorted_ascendently()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), CreateRandomArray( 100 ) );
        }

        [Test]
        public void Quick_9876543210_is_sorted_in_ascending_order()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), Create9876543210Array() );
        }

        [Test]
        public void Quick_RandomArray_is_sorted_ascendently()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), CreateRandomArray( 100 ) );
        }

        [Ignore]
        [Test]
        public void Insertion_9876543210_is_sorted_in_ascending_order()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), Create9876543210Array() );
        }

        [Ignore]
        [Test]
        public void Insertion_RandomArray_is_sorted_ascendently()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), CreateRandomArray( 100 ) );
        }
    }
}