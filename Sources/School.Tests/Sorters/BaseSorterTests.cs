using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace School.Tests.Sorters
{
    public class BaseSorterTests {
        protected static void Assert_is_ascending( int[] arr )
        {
            for( var i = 0; i < arr.Length - 1; i++ ) {
                if( arr[ i ] > arr[ i + 1 ] ) {
                    Assert.Fail( "\narr[{0}] > arr[{1}] ({2} > {3})", i, i + 1, arr[ i ], arr[ i + 1 ] );
                }
            }
        }
    }
}