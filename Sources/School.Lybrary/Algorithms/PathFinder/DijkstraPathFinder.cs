// School (c) 2015 Krokodev
// School.Lybrary
// DijkstraPathFinder.cs

using System.Linq;
using School.Lybrary.Structures.Graphs;
using School.Lybrary.Utils;

namespace School.Lybrary.Algorithms.PathFinder
{
    public class DijkstraPathFinder : DijkstraPathFinderBase
    {
        public void FindPathes( IWeightedGraph graph, IVertex source )
        {
            Dist[ source ] = 0;
            Path[ source ] = EmptyPath();

            foreach( var vertex in graph.Vertices.Except( source ) ) {
                Dist[ vertex ] = Infinity;
                Path[ vertex ] = EmptyPath();
                Qeue.Add( vertex );
            }

            while( Qeue.NotEmpty() ) {
                var vertex = Qeue.SelectHasMin( Dist );
                Qeue.Remove( vertex );
                foreach( var neighbor in vertex.Neighbors.Intersect( Qeue ) ) {
                    var newDist = Dist[ vertex ] + graph.GetWeight( vertex, neighbor );
                    if( newDist >= Dist[ neighbor ] ) {
                        continue;
                    }
                    Dist[ neighbor ] = newDist;
                    Path[ neighbor ] = Path[ vertex ].With( neighbor );
                }
            }
        }
    }
}