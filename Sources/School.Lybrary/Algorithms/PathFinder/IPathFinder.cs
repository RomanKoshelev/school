// School (c) 2015 Krokodev
// School.Tests
// IPathFinder.cs

using System.Collections.Generic;
using School.Lybrary.Structures.Graphs;

namespace School.Lybrary.Algorithms.PathFinder
{
    public interface IPathFinder
    {
        IList< IVertex > FindPath( IWeightedGraph graph, IVertex start, IVertex finish );
    }
}