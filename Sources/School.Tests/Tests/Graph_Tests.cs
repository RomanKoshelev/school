// School (c) 2015 Krokodev
// School.Tests
// Graph_Tests.cs

using NUnit.Framework;
using School.Lybrary.Structures.Graphs;
using School.Nunit.Bases;

namespace School.Nunit.Tests
{
    // ReSharper disable All
    [TestFixture]
    public class Graph_Tests : GraphTestsBase
    {

        [Test]
        public void Random_graph_is_correct()
        {
            var graph = CreateRandomGraph( 10, 0.7 );
            PrintVertecies( graph );
            Verify_Graph( graph );
        }

        [Test]
        public void Complete_graph_is_correct()
        {
            var graph = CreateCompleteGraph( 10 );
            PrintVertecies( graph );
            Verify_Complete_Graph( graph );
        }

        [Test]
        public void Weighted_graph_is_correct()
        {
            var graph = CreateWeightedGraph( 3 );
            MakeGraphRandomLinked( graph, 10.7 );
            MakeRandomWeighted( graph, 1, 10 );
            PrintEdges( graph );
            PrintWeights( graph );
            Verify_Weighted_Graph( graph );
        }

        public void Dijkstra_PathFinder()
        {
            var graph = CreateWeightedGraph( 10 );
        }
    }
}