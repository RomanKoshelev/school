// School (c) 2015 Krokodev
// School.Lybrary
// DijkstraPathFinder.cs

using System.Collections.Generic;
using System.Linq;
using School.Lybrary.Structures.Graphs;
using School.Lybrary.Utils;

namespace School.Lybrary.Algorithms.PathFinder
{
    // ReSharper disable All
    public class DijkstraPathFinder : DijkstraPathFinderBase, IPathFinder
    {
        public IList< IVertex > FindPath( IWeightedGraph graph, IVertex start, IVertex finish )
        {
            Init();
            FindPathes( graph, start );
            return Path[ finish ];
        }

        private void FindPathes( IWeightedGraph graph, IVertex source )
        {
            foreach( var vertex in graph.Vertices ) {
                Dist[ vertex ] = vertex == source ? 0 : Infinity;
                Path[ vertex ] = EmptyPath();
                Qeue.Add( vertex );
            }

            while( Qeue.NotEmpty() ) {
                var current = Qeue.SelectHasMin( Dist );
                Qeue.Remove( current );
                foreach( var neighbor in current.Neighbors.Intersect( Qeue ) ) {
                    var distNeighbor = Dist[ current ] + graph.GetWeight( current, neighbor );
                    if( distNeighbor < Dist[ neighbor ] ) {
                        Dist[ neighbor ] = distNeighbor;
                        Path[ neighbor ] = Path[ current ].With( neighbor );
                    }
                }
            }
        }
    }
}