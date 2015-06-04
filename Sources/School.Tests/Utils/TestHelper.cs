// School (c) 2015 Krokodev
// School.Tests
// Sorter_Tests.cs

 // ReSharper disable All

using NUnit.Framework;

namespace School.Tests.Utils
{
    public static class TestHelper
    {
        public static int[] CreateRandomArray( int n=100 )
        {
            var rand = new Randomizer();
            return rand.GetInts( 0, n + 1, n );
        }

        public static int[] CreateArrayFrom9to0()
        {
            return new int[] { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        }
    }
}