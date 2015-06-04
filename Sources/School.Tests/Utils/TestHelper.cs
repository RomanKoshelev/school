// School (c) 2015 Krokodev
// School.Tests
// TestHelper.cs

using System;
using NUnit.Framework;
using School.Lybrary.Utils;

namespace School.Nunit.Utils
{
    // ReSharper disable All
    public static class TestHelper
    {
        public static int[] CreateRandomArray( int n = 100 )
        {
            var rand = new Randomizer();
            return rand.GetInts( 0, n + 1, n );
        }

        public static int[] CreateArrayFrom9To0()
        {
            return new int[] { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        }

        public static void Print( int[] array )
        {
            for( var i = 0; i < array.Length; i++ ) {
                Console.Write( "{0} ", array[ i ] );
            }
            Console.WriteLine( "\n" );
        }

        public static void Print( IStatistics statistics )
        {
            Console.WriteLine( statistics );
        }
    }
}