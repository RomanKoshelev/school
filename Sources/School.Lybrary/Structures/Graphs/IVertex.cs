// School (c) 2015 Krokodev
// School.Lybrary
// IVertex.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public interface IVertex
    {
        IList< IVertex > Neighbors { get; set; }
        string Name { get; set; }
        void AddEdge( IEdge edge );
    }
}