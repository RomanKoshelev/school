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
        void NewVertex( object name );
        bool Linked( IVertex a, IVertex b );
    }
}