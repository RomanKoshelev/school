// School (c) 2015 Krokodev
// School.Tests
// Graph_Tests.cs

using System;
using System.Collections.Generic;
using NUnit.Framework;
using School.Lybrary.Algorithms.PathFinder;
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
            var graph = CreateRandomWeightedGraph( num : 10, linkageThreshold : 0.7, minWeight : 1, maxWeight : 10 );
            PrintWeights( graph );
            Verify_Weighted_Graph( graph );
        }

        [Test]
        public void Dijkstra_PathFinder()
        {
            var graph = CreateRandomWeightedGraph( num : 10, linkageThreshold : 0.12, minWeight : 1, maxWeight : 10 );
            IPathFinder pathFinder = new DijkstraPathFinder();

            var start = graph.GetVertex( "0" );
            var finish = graph.GetVertex( "1" );

            if( graph.Linked( start, finish ) ) {
                graph.SetWeight( start, finish, 99 );
            }

            var path = pathFinder.FindPath( graph, start, finish );

            PrintWeights( graph );
            PrintPath( graph, path, start, finish );
        }
    }
}