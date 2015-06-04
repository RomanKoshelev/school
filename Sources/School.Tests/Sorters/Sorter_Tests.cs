// School (c) 2015 Krokodev
// School.Tests
// Sorter_Tests.cs

using NUnit.Framework;
using School.Lybrary.Sorters;
using School.Tests.Bases;

// ReSharper disable All

namespace School.Tests.Sorters
{
    [TestFixture]
    public class Sorter_Tests : SorterTestsBase
    {
        [Test]
        public void Bubble_9876543210()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), Create9876543210Array() );
        }

        [Test]
        public void Bubble_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), CreateRandomArray( 100 ) );
        }

        [Test]
        public void Quick_9876543210()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), Create9876543210Array() );
        }

        [Test]
        public void Quick_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), CreateRandomArray( 100 ) );
        }

        [Ignore]
        [Test]
        public void Insertion_9876543210()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), Create9876543210Array() );
        }

        [Ignore]
        [Test]
        public void Insertion_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), CreateRandomArray( 100 ) );
        }
    }
}