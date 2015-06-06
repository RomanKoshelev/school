// School (c) 2015 Krokodev
// School.Lybrary
// WeightedGraph.cs

using System;
using System.Collections.Generic;

namespace School.Lybrary.Structures.Graphs
{
    public abstract class WeightedGraph : Graph, IWeightedGraph
    {
        public int Weight( IVertex a, IVertex b )
        {
            throw new NotImplementedException();
        }
    }

    public class Graph
    {
        public IEnumerable< IVertex > Vertices { get; set; }
    }
}