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
        }

        public IEdge IEdge
        {
            get { return this; }
        }

        #endregion


        #region IEdge

        IVertex IEdge.Vertex1 { get; set; }
        IVertex IEdge.Vertex2 { get; set; }

        bool IEdge.Contains( IVertex v )
        {
            return IEdge.Vertex1 == v || IEdge.Vertex2 == v;
        }

        #endregion
    }
}