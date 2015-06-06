// School (c) 2015 Krokodev
// School.Lybrary
// IGraph.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public interface IGraph
    {
        IEnumerable< IVertex > Vertices { get; set; }
    }
}