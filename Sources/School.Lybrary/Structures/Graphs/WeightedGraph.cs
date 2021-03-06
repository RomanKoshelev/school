﻿// School (c) 2015 Krokodev
// School.Lybrary
// WeightedGraph.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public class WeightedGraph : Graph, IWeightedGraph
    {
        #region IWeightedGraph

        private IWeightedGraph IWeightedGraph
        {
            get { return this; }
        }

        int IWeightedGraph.GetWeight( IVertex a, IVertex b )
        {
            if( IGraph.Linked( a, b ) ) {
                var edge = IGraph.GetEdge( a, b );
                return IWeightedGraph.GetWeight( edge );
            }
            return 0;
        }

        int IWeightedGraph.GetWeight( IEdge edge )
        {
            return
                IsWeightAssigned( edge )
                    ? _weights[ edge ]
                    : 0;
        }

        void IWeightedGraph.SetWeight( IVertex a, IVertex b, int weight )
        {
            var edge = IGraph.GetEdge( a, b );
            IWeightedGraph.SetWeight( edge, weight );
        }

        void IWeightedGraph.SetWeight( IEdge edge, int weight )
        {
            if( IsWeightAssigned( edge ) ) {
                _weights[ edge ] = weight;
            } else {
                _weights.Add( edge, weight );
            }
        }

        #endregion


        #region Fields

        private readonly Dictionary< IEdge, int > _weights = new Dictionary< IEdge, int >();

        #endregion


        #region Utils

        private bool IsWeightAssigned( IEdge edge )
        {
            return _weights.ContainsKey( edge );
        }

        #endregion
    }
}