// School (c) 2015 Krokodev
// School.Lybrary
// IWeightedGraph.cs

namespace School.Lybrary.Structures.Graphs
{
    public interface IWeightedGraph : IGraph
    {
        int GetWeight( IVertex a, IVertex b );
        void SetWeight( IVertex a, IVertex b, int w );
    }
}