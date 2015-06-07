// School (c) 2015 Krokodev
// School.Lybrary
// Edge.cs

namespace School.Lybrary.Structures.Graphs
{
    public class Edge : IEdge
    {
        #region Ctor

        public Edge( IVertex vertex1, IVertex vertex2 )
        {
            IEdge.Vertex1 = vertex1;
            IEdge.Vertex2 = vertex2;
            vertex1.AddEdge( this );
            vertex2.AddEdge( this );
        }

        public IEdge IEdge
        {
            get { return this; }
        }

        #endregion


        #region IEdge

        IVertex IEdge.Vertex1 { get; set; }
        IVertex IEdge.Vertex2 { get; set; }

        IVertex IEdge.Neighbor( Vertex vertex )
        {
            return vertex == IEdge.Vertex1
                ? IEdge.Vertex2
                : vertex == IEdge.Vertex2
                    ? IEdge.Vertex1
                    : null;
        }

        bool IEdge.DoesConnect( IVertex a, IVertex b )
        {
            return IEdge.Vertex1 == a && IEdge.Vertex2 == b || IEdge.Vertex1 == b && IEdge.Vertex2 == a;
        }

        #endregion
    }
}