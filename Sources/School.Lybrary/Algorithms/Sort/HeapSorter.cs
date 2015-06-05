// School (c) 2015 Krokodev
// School.Lybrary
// HeapSorter.cs

using System;
using School.Lybrary.Types;

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
            BuildHeap( array );
            BuildArray( array );
        }

        private void BuildHeap( int[] array )
        {
            foreach( var index in Order( 0, array.Length - 1 ) ) {
                ShiftUp( array, index );
            }
        }

        private void ShiftUp( int[] array, int node )
        {
            while( node != 0 ) {
                var parent = ( node - 1 )/2;
                if( From( array ).Item( node ).Greater_than_item( parent ) ) {
                    Then.In( array ).Swap( node, parent );
                    node = parent;
                } else {
                    return;
                }
            }
        }

        private void BuildArray( int[] array )
        {
            foreach( var index in Order( array.Length - 1, 0 ) ) {
                In( array ).Swap( 0, index );
                ShiftDown( array, 0, index - 1 );
            }
        }

        private void ShiftDown( int[] array, int node, int last )
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
            var left = node*2 + 1;
            var right = Math.Min( node*2 + 2, last );
            return
                From( array ).Item( left ).Greater_than_item( right )
                    ? left
                    : right;
        }
    }
}