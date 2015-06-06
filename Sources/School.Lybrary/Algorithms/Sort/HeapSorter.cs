// School (c) 2015 Krokodev
// School.Lybrary
// HeapSorter.cs

using System;
using School.Lybrary.Algorithms.Sort.Base;

namespace School.Lybrary.Algorithms.Sort
{
    // ReSharper disable All
    public class HeapSorter : Sorter
    {
        protected override void DoSort( int[] array )
        {
            HeapSort( array );
        }

        private void HeapSort( int[] array )
        {
            foreach( var index in Order( array.Length/2 - 1, 0 ) ) {
                SiftDown( array, index, array.Length - 1 );
            }

            foreach( var index in Order( array.Length - 1, 0 ) ) {
                In( array ).Swap( 0, index );
                SiftDown( array, 0, index - 1 );
            }
        }

        private void SiftDown( int[] array, int node, int last )
        {
            var lastParent = ( last - 1 )/2;
            while( node < last && node <= lastParent ) {
                var child = LargestChild( array, node, last );
                if( From( array ).Item( node ).Less_than_item( child ) ) {
                    Then.In( array ).Swap( node, child );
                    node = child;
                } else {
                    return;
                }
            }
        }

        private int LargestChild( int[] array, int node, int last )
        {
            var left = Math.Min( last, node*2 + 1 );
            var right = Math.Min( last, node*2 + 2 );
            return
                From( array ).Item( left ).Greater_than_item( right )
                    ? left
                    : right
                ;
        }
    }
}