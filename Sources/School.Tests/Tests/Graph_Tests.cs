// School (c) 2015 Krokodev
// School.Tests
// Graph_Tests.cs

using System;
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
        public void Complete_graph_is_correct()
        {
            var graph = CreateCompleteGraph( 10 );

            PrintEdges( graph );

            Verify_Graph( graph );
            Verify_Complete_Graph( graph );
        }

        [Test]
        public void Random_graph_is_correct()
        {
            var graph = CreateRandomGraph( 10, 0.1 );
            
            PrintEdges( graph );

            Verify_Graph( graph );
        }

        private IGraph CreateWeightedGraph( int num )
        {
            throw new System.NotImplementedException();
        }

        [Test]
        public void Dijkstra_PathFinder() {}
    }
}