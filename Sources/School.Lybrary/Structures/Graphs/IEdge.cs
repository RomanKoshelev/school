// School (c) 2015 Krokodev
// School.Lybrary
// IEdge.cs

namespace School.Lybrary.Structures.Graphs
{
    public interface IEdge
    {
        IVertex Vertex1 { get; set; }
        IVertex Vertex2 { get; set; }
        IVertex Neighbor( Vertex vertex );
        bool DoesConnect( IVertex a, IVertex b );
    }
}