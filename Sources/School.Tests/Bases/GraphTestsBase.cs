// School (c) 2015 Krokodev
// School.Tests
// GraphTestsBase.cs

using System;
using NUnit.Framework;
using School.Lybrary.Structures.Graphs;
using School.Lybrary.Utils;

namespace School.Nunit.Bases
{
    // ReSharper disable All
    public class GraphTestsBase
    {
        #region Create

        protected static IGraph CreateGraph( int num )
        {
            IGraph graph = new Graph();

            for( var i = 0; i < num; i++ ) {
                graph.NewVertex( i );
            }

            return graph;
        }

        protected static IGraph CreateCompleteGraph( int num )
        {
            var graph = CreateGraph( num );
            MakeGraphComplete( graph );
            return graph;
        }

        protected static IGraph CreateRandomGraph( int num, double threshold )
        {
            var graph = CreateGraph( num );
            MakeGraphRandomLinked( graph, threshold );
            return graph;
        }

        #endregion


        #region Change

        protected static void MakeGraphComplete( IGraph graph )
        {
            foreach( var v1 in graph.Vertices ) {
                foreach( var v2 in graph.Vertices.Except( v1 ) ) {
                    if( !graph.Linked( v1, v2 ) ) {
                        graph.AddEdge( v1, v2 );
                    }
                }
            }
        }

        protected static void MakeGraphRandomLinked( IGraph graph, double threshold )
        {
            var rand = new Randomizer();
            foreach( var v1 in graph.Vertices ) {
                foreach( var v2 in graph.Vertices.Except( v1 ) ) {
                    if( !graph.Linked( v1, v2 ) ) {
                        if( rand.NextDouble() <= threshold ) {
                            graph.AddEdge( v1, v2 );
                        }
                    }
                }
            }
        }

        #endregion


        #region Print

        protected static void PrintEdges( IGraph graph )
        {
            foreach( var v in graph.Vertices ) {
                Console.WriteLine();
                foreach( var n in v.Neighbors ) {
                    Console.Write( "{0}-{1} ", v, n );
                }
            }
        }

        #endregion


        #region Verify

        protected static void Verify_Graph( IGraph graph )
        {
            var neighborNum = 0;
            foreach( var vertex in graph.Vertices ) {
                neighborNum += vertex.Neighbors.Count;
            }
            Assert.AreEqual( graph.Edges.Count, neighborNum/2, "neighborNum/2" );
        }

        protected static void Verify_Complete_Graph( IGraph graph )
        {
            var num = graph.Vertices.Count;
            Assert.AreEqual( num*( num - 1 )/2, graph.Edges.Count, "graph.Edges.Count" );
            foreach( var vertex in graph.Vertices ) {
                Assert.AreEqual( num - 1, vertex.Neighbors.Count, "vertex.Neighbors.Count" );
            }
        }

        #endregion
    }
}