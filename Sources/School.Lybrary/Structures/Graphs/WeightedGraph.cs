// School (c) 2015 Krokodev
// School.Lybrary
// WeightedGraph.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public class WeightedGraph : Graph, IWeightedGraph
    {
        #region IWeightedGraph

        int IWeightedGraph.GetWeight( IVertex a, IVertex b )
        {
            return _weights[ IGraph.GetEdge( a, b ) ];
        }

        void IWeightedGraph.SetWeight( IVertex a, IVertex b, int weight )
        {
            var edge = IGraph.GetEdge( a, b );
            if( !_weights.ContainsKey( edge ) ) {
                _weights.Add( edge, weight );
            } else {
                _weights[ edge ] = weight;
            }
        }

        #endregion


        #region Fields

        private readonly Dictionary< IEdge, int > _weights = new Dictionary< IEdge, int >();

        #endregion
    }
}