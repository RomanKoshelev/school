// School (c) 2015 Krokodev
// School.Tests
// GraphTestsBase.cs

using System;
using System.Collections.Generic;
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
            AddVertecies( graph, num );
            return graph;
        }

        private static void AddVertecies( IGraph graph, int num )
        {
            for( var i = 0; i < num; i++ ) {
                graph.NewVertex( i );
            }
        }

        protected IWeightedGraph CreateWeightedGraph( int num )
        {
            var graph = new WeightedGraph();
            AddVertecies( graph, num );
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

        protected IWeightedGraph CreateRandomWeightedGraph( int num, double linkageThreshold, int minWeight, int maxWeight )
        {
            var graph = CreateWeightedGraph( num );
            MakeGraphRandomLinked( graph, linkageThreshold );
            MakeRandomWeighted( graph, minWeight, maxWeight );
            return graph;
        }

        protected IWeightedGraph CreateCompleteWeightedGraph( int num, int minWeight, int maxWeight )
        {
            var graph = CreateWeightedGraph( num );
            MakeGraphComplete( graph );
            MakeRandomWeighted( graph, minWeight, maxWeight );
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

        protected void MakeRandomWeighted( IWeightedGraph graph, int minWeight, int maxWeight )
        {
            var rand = new Randomizer();
            foreach( var e in graph.Edges ) {
                graph.SetWeight( e, rand.Next( minWeight, maxWeight + 1 ) );
            }
        }

        #endregion


        #region Print

        protected static void PrintEdges( IGraph graph )
        {
            Console.WriteLine();
            foreach( var e in graph.Edges ) {
                Console.WriteLine( "{0}-{1} ", e.Vertex1, e.Vertex2 );
            }
        }

        protected static void PrintVertecies( IGraph graph )
        {
            Console.WriteLine();
            foreach( var v in graph.Vertices ) {
                Console.WriteLine();
                foreach( var n in v.Neighbors ) {
                    Console.Write( "{0}-{1} ", v, n );
                }
            }
        }

        protected void PrintWeights( IWeightedGraph graph )
        {
            Console.WriteLine();
            foreach( var v in graph.Vertices ) {
                Console.WriteLine();
                foreach( var n in v.Neighbors ) {
                    Console.Write( "{0}-{1}:{2} ", v, n, graph.GetWeight( v, n ) );
                }
            }
        }

        protected static void PrintPath( IWeightedGraph graph, IList< IVertex > path, IVertex start, IVertex finish )
        {
            Console.WriteLine( "\n" );
            Console.Write( "path: [{0}", start );
            var prev = start;
            var dist = 0;
            if( path.Count > 0 ) {
                foreach( var step in path ) {
                    Console.Write( "-{0}", step );
                    dist += graph.GetWeight( prev, step );
                    prev = step;
                }
            } else {
                Console.Write( " not found {0}", finish );
            }
            Console.Write( "]" );
            if( dist > 0 ) {
                Console.Write( ":{0}", dist );
            }
            Console.WriteLine();
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

            foreach( var edge in graph.Edges ) {
                Assert.AreNotEqual( edge.Vertex1, edge.Vertex2, "edge.Vertex1, edge.Vertex2" );
            }
        }

        protected static void Verify_Complete_Graph( IGraph graph )
        {
            Verify_Graph( graph );
            var num = graph.Vertices.Count;
            Assert.AreEqual( num*( num - 1 )/2, graph.Edges.Count, "graph.Edges.Count" );
            foreach( var vertex in graph.Vertices ) {
                Assert.AreEqual( num - 1, vertex.Neighbors.Count, "vertex.Neighbors.Count" );
            }
        }

        protected void Verify_Weighted_Graph( IWeightedGraph graph )
        {
            Verify_Graph( graph );
            foreach( var vertex in graph.Vertices ) {
                Assert.AreEqual( 0, graph.GetWeight( vertex, vertex ), vertex.ToString() );
            }

            foreach( var v in graph.Vertices ) {
                foreach( var n in v.Neighbors ) {
                    Assert.Greater( graph.GetWeight( v, n ), 0, "vertex.Neighbors weight" );
                }
            }
        }

        #endregion
    }
}