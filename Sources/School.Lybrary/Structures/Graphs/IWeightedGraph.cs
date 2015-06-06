// School (c) 2015 Krokodev
// School.Lybrary
// IWeightedGraph.cs

namespace School.Lybrary.Structures.Graphs
{
    public interface IWeightedGraph : IGraph
    {
        int Weight( IVertex a, IVertex b );
    }
}