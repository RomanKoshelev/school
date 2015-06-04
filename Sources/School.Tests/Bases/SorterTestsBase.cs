// School (c) 2015 Krokodev
// School.Tests
// SorterTestsBase.cs

using NUnit.Framework;
using School.Lybrary.Types;
using School.Nunit.Utils;

// ReSharper disable All

namespace School.Nunit.Bases
{
    public class SorterTestsBase
    {
        #region Protected

        protected static void Assert_is_ascending( int[] arr )
        {
            for( var i = 0; i < arr.Length - 1; i++ ) {
                if( arr[ i ] > arr[ i + 1 ] ) {
                    Assert.Fail( "\narr[{0}] > arr[{1}] ({2} > {3})", i, i + 1, arr[ i ], arr[ i + 1 ] );
                }
            }
        }

        protected void Array_is_sorted_in_ascending_order( ISorter sorter, int[] array )
        {
            sorter.Sort( array );
            TestHelper.Print( array );
            TestHelper.Print( sorter.Algorithm.Statistics );
            Assert_is_ascending( array );
        }

        #endregion
    }
}