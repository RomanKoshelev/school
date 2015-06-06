// School (c) 2015 Krokodev
// School.Lybrary
// IVertex.cs

using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public interface IVertex
    {
        IEnumerable< IVertex > Neighbors { get; set; }
    }
}