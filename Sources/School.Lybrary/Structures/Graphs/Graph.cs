// School (c) 2015 Krokodev
// School.Lybrary
// Graph.cs

using System;
using System.Collections.Generic;
using System.Linq;

namespace School.Lybrary.Structures.Graphs
{
    public class Graph : IGraph
    {
        #region IGraph

        protected IGraph IGraph
        {
            get { return this; }
        }

        IEnumerable< IVertex > IGraph.Vertices
        {
            get { return _vertices; }
        }

        IEnumerable< IEdge > IGraph.Edges
        {
            get { return _edges; }
        }

        void IGraph.AddEdge( IVertex a, IVertex b )
        {
            if( IGraph.Linked( a, b ) ) {
                throw new Exception( "Edge already exists" );
            }
            _edges.Add( new Edge( a, b ) );
        }

        void IGraph.AddVertex( IVertex vertex )
        {
            if( _vertices.Contains( vertex ) ) {
                throw new Exception( "Vertex already exists" );
            }
            _vertices.Add( vertex );
        }

        bool IGraph.Linked( IVertex a, IVertex b )
        {
            return _edges.Any( v => v.Contains( a ) && v.Contains( b ) );
        }

        IEdge IGraph.GetEdge( IVertex a, IVertex b )
        {
            return _edges.First( v => v.Contains( a ) && v.Contains( b ) );
        }

        #endregion


        #region Fields

        private readonly IList< IEdge > _edges = new List< IEdge >();
        private readonly IList< IVertex > _vertices = new List< IVertex >();

        #endregion


        #region Utils

        #endregion
    }
}