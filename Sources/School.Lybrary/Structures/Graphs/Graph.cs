// School (c) 2015 Krokodev
// School.Lybrary
// Graph.cs

using System;
using System.Collections.Generic;
using System.Linq;
using School.Lybrary.Utils;

namespace School.Lybrary.Structures.Graphs
{
    public class Graph : IGraph
    {
        #region IGraph

        protected IGraph IGraph
        {
            get { return this; }
        }

        IList< IVertex > IGraph.Vertices
        {
            get { return _vertices; }
        }

        IList< IEdge > IGraph.Edges
        {
            get { return _edges; }
        }

        void IGraph.AddEdge( IVertex a, IVertex b )
        {
            if( IGraph.Linked( a, b ) ) {
                throw new SchoolException( "Edge {0}-{1} already exists", a, b );
            }
            _edges.Add( new Edge( a, b ) );
        }

        IVertex IGraph.AddVertex( IVertex vertex )
        {
            if( _vertices.Contains( vertex ) ) {
                throw new SchoolException( "Vertex {0} already exists", vertex );
            }
            _vertices.Add( vertex );
            return vertex;
        }

        public IVertex NewVertex( object name )
        {
            var v = new Vertex( name );
            _vertices.Add( v );
            return v;
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