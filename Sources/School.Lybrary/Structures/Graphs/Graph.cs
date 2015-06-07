// School (c) 2015 Krokodev
// School.Lybrary
// Graph.cs

using System.Collections.Generic;
using System.Linq;
using School.Lybrary.Utils;

namespace School.Lybrary.Structures.Graphs
{
    public class Graph : IGraph
    {
        #region IGraph

        public IGraph IGraph
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

        void IGraph.NewVertex( object name )
        {
            var v = new Vertex( name );
            _vertices.Add( v );
        }

        bool IGraph.Linked( IVertex a, IVertex b )
        {
            return _edges.Any( e => e.DoesConnect( a, b ) );
        }

        IEdge IGraph.GetEdge( IVertex a, IVertex b )
        {
            return _edges.First( e => e.DoesConnect( a, b ) );
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