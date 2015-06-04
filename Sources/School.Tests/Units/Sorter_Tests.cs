// School (c) 2015 Krokodev
// School.Tests
// Sorter_Tests.cs

using NUnit.Framework;
using School.Lybrary.Algorithms.Sorters;
using School.Tests.Bases;
using School.Tests.Utils;

// ReSharper disable All

namespace School.Tests.Units
{
    [TestFixture]
    public class Sorter_Tests : SorterTestsBase
    {
        [Test]
        public void Bubble_9876543210()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), TestHelper.CreateArrayFrom9to0() );
        }

        [Test]
        public void Bubble_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new BubbleSorter(), TestHelper.CreateRandomArray() );
        }

        [Test]
        public void Quick_9876543210()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), TestHelper.CreateArrayFrom9to0() );
        }

        [Test]
        public void Quick_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new QuickSorter(), TestHelper.CreateRandomArray() );
        }

        [Test]
        public void Insertion_9876543210()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), TestHelper.CreateArrayFrom9to0() );
        }

        [Test]
        public void Insertion_RandomArray()
        {
            Array_is_sorted_in_ascending_order( new InsertionSorter(), TestHelper.CreateRandomArray() );
        }
    }
}