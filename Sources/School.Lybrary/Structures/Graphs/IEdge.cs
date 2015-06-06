// School (c) 2015 Krokodev
// School.Lybrary
// IEdge.cs

namespace School.Lybrary.Structures.Graphs
{
    public interface IEdge
    {
        IVertex Vertex1 { get; set; }
        IVertex Vertex2 { get; set; }
        bool Contains( IVertex v );
    }
}