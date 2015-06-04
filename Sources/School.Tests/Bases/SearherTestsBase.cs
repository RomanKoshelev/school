// School (c) 2015 Krokodev
// School.Tests
// SearherTestsBase.cs

using System;
using NUnit.Framework;
using School.Lybrary.Algorithms.Sorters;
using School.Lybrary.Types;
using School.Tests.Utils;

namespace School.Tests.Bases
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

            Console.WriteLine( "array[{0}]={1}", index, value );
            Console.WriteLine( "found[{0}]={1}", found, array[ found ] );
            Console.WriteLine();
            Console.WriteLine( searcher.Algorithm.Statistics.ToString() );

            Assert.AreEqual( value, array[ found ] );
            Assert.AreEqual( Searcher.NotFound, searcher.Search( array, Int32.MaxValue ) );
            Assert.AreEqual( Searcher.NotFound, searcher.Search( array, Int32.MinValue ) );
        }
    }
}