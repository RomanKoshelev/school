// School (c) 2015 Krokodev
// School.Lybrary
// Vertex.cs

using System.Collections.Generic;
using System.Linq;

namespace School.Lybrary.Structures.Graphs
{
    public class Vertex : IVertex
    {
        #region Ctor

        public Vertex( object name = null )
        {
            name = name ?? _totalNum;
            IVertex.Name = name.ToString();
            _totalNum ++;
        }

        #endregion


        #region IVertex

        private IVertex IVertex
        {
            get { return this; }
        }

        IList< IVertex > IVertex.Neighbors
        {
            get { return _edges.Select( e => e.Neighbor( this ) ).ToList(); }
            set { }
        }

        string IVertex.Name { get; set; }

        void IVertex.AddEdge( IEdge edge )
        {
            _edges.Add( edge );
        }

        #endregion


        #region Static

        private static int _totalNum;

        #endregion


        #region Overrides

        public override string ToString()
        {
            return IVertex.Name;
        }

        #endregion


        #region Fields

        private readonly IList< IEdge> _edges = new List< IEdge >();

        #endregion

    }
}