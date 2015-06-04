﻿// School (c) 2015 Krokodev
// School.Tests
// BubbleSorter_Tests.cs

using NUnit.Framework;
using School.Lybrary.Sorters;

// ReSharper disable All

namespace School.Tests.Sorters
{
    [TestFixture]
    public class BubbleSorter_Tests : BaseSorterTests
    {
        [Test]
        public void Array_9876543210_is_sorted_in_ascending_order()
        {
            var sorter = new BubbleSorter();
            var array = new int[] { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
            sorter.Sort( array );
            Print( array );
            Assert_is_ascending( array );
        }

        [Test]
        public void Random_array_is_sorted_ascendently()
        {
            var sorter = new BubbleSorter();
            var array = CreateRandomArray( 100 );
            sorter.Sort( array );
            Print( array );
            Assert_is_ascending( array );
        }
    }
}