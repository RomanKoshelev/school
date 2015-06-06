// School (c) 2015 Krokodev
// School.Lybrary
// IGraph.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public interface IGraph
    {
        IEnumerable< IVertex > Vertices { get; }
        IEnumerable< IEdge > Edges { get; }
        void AddEdge( IVertex a, IVertex b );
        IEdge GetEdge( IVertex a, IVertex b );
        void AddVertex( IVertex vertex );
        bool Linked( IVertex a, IVertex b );
    }
}