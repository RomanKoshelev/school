// School (c) 2015 Krokodev
// School.Lybrary
// IGraph.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public interface IGraph
    {
        IList< IVertex > Vertices { get; }
        IList< IEdge > Edges { get; }
        void AddEdge( IVertex a, IVertex b );
        IEdge GetEdge( IVertex a, IVertex b );
        IVertex AddVertex( IVertex vertex );
        IVertex NewVertex( object name );
        bool Linked( IVertex a, IVertex b );
    }
}