// School (c) 2015 Krokodev
// School.Tests
// SearherTestsBase.cs

using System;
using NUnit.Framework;
using School.Lybrary.Algorithms.Sort;
using School.Lybrary.Types;
using School.Nunit.Utils;

namespace School.Nunit.Bases
{
    // ReSharper disable All
    public class SearherTestsBase
    {
        protected int[] CreateSortedRandomArray()
        {
            var array = TestHelper.CreateRandomArray( 1000 );
            ISorter sorter = new QuickSorter();
            sorter.Sort( array );
            return array;
        }

        protected void Test_search_random_value_from_random_array( ISearcher searcher )
        {
            var array = CreateSortedRandomArray();
            var index = new Random().Next( array.Length );
            var value = array[ index ];
            var found = searcher.Search( array, value );

            Assert.AreNotEqual( Searcher.KeyNotFound, found );

            Console.WriteLine( "array[{0}]={1}", index, value );
            Console.WriteLine( "found[{0}]={1}", found, array[ found ] );
            Console.WriteLine();

            TestHelper.Print( searcher.Algorithm.Statistics );

            Assert.AreEqual( value, array[ found ] );
            Assert_wrong_values_not_found( searcher, array );
            Assert_bounds_found( searcher, array );
        }

        private static void Assert_wrong_values_not_found( ISearcher searcher, int[] array )
        {
            Assert.AreEqual( Searcher.KeyNotFound, searcher.Search( array, Int32.MaxValue ) );
            Assert.AreEqual( Searcher.KeyNotFound, searcher.Search( array, Int32.MinValue ) );
        }

        private static void Assert_bounds_found( ISearcher searcher, int[] array )
        {
            Assert_index_found( searcher, array, 0 );
            Assert_index_found( searcher, array, 1 );
            Assert_index_found( searcher, array, array.Length/2 );
            Assert_index_found( searcher, array, array.Length - 1 );
            Assert_index_found( searcher, array, array.Length - 2 );
        }

        private static void Assert_index_found( ISearcher searcher, int[] array, int index )
        {
            Assert.AreEqual( array[ index ], array[ searcher.Search( array, array[ index ] ) ] );
        }
    }
}