// School (c) 2015 Krokodev
// School.Tests
// BaseSorterTests.cs

using System;
using NUnit.Framework;
using School.Lybrary.Utils;

// ReSharper disable All

namespace School.Tests.Sorters
{
    public class BaseSorterTests
    {
        protected static void Assert_is_ascending( int[] arr )
        {
            for( var i = 0; i < arr.Length - 1; i++ ) {
                if( arr[ i ] > arr[ i + 1 ] ) {
                    Assert.Fail( "\narr[{0}] > arr[{1}] ({2} > {3})", i, i + 1, arr[ i ], arr[ i + 1 ] );
                }
            }
        }

        protected static int[] CreateRandomArray( int n )
        {
            var rand = new Randomizer();
            return rand.GetInts( 0, n + 1, n );
        }

        protected static void Print( int[] array )
        {
            for( var i = 0; i < array.Length; i++ ) {
                Console.Write( "{0} ", array[ i ] );
            }
        }

        protected void Print( Statistics statistics )
        {
            Console.Write( statistics );
        }
    }
}