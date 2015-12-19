// School (c) 2015 Aspose
// School.Tests
// Cormorant_Tests.cs

using System;
using System.Collections.Generic;
using NUnit.Framework;

namespace School.Nunit.Tests
{
    [TestFixture]
    public class Cormorant_Tests
    {
        #region Console
        private static void Print( object arg )
        {
            Console.WriteLine( arg.ToString() );
        }

        private static void Print( string template, params object[] args )
        {
            Console.WriteLine( template, args );
        }
        #endregion



        [Test]
        [TestCase( 1, 3, 3, 3 )]
        [TestCase( 1, 100, 100, 100 )]
        [TestCase( 2, 4, 5, 3)]
        [TestCase( 1, 300, 200, 10400)]

        public void Nash_Equilibrium( int left, int right, int maxSumm, int neNumAnswer )
        {
            var nashEqList = GetAllNashEqs( left, right, maxSumm );
            var neNum = nashEqList.Count;

            PrintResults( nashEqList );

            Assert.That( neNum, Is.EqualTo( neNumAnswer ), "Number of Nash Equilibrium" );
        }

        private static void PrintResults( List< Tuple< int, int > > nashEqList )
        {
            Print( "Number of Nash Equilibriums = {0}", nashEqList.Count );
            foreach( var ne in nashEqList )
            {
                Print( "({0},{1})", ne.Item1, ne.Item2 );
            }
        }

        private List< Tuple< int, int > > GetAllNashEqs( int left, int right, int maxSumm )
        {
            var res = new List< Tuple< int, int > >();

            var outcomes = GetAllOutcomes( left, right );
            foreach( var outcome in outcomes )
            {
                if( IsNashEquilibrium( outcome, left, right, maxSumm ) )
                {
                    res.Add( outcome );
                }
            }
            return res;
        }

        private bool IsNashEquilibrium( Tuple< int, int > outcome, int left, int right, int maxSumm )
        {
            var gain1 = GetGain( outcome, maxSumm, outcome.Item1 );
            if( CanImproveGain( gain1, outcome, left, right, maxSumm, outcome.Item2 ) )
            {
                return false;
            }

            var gain2 = GetGain( outcome, maxSumm, outcome.Item2 );
            if( CanImproveGain( gain2, outcome, left, right, maxSumm, outcome.Item1 ) )
            {
                return false;
            }

            return true;
        }

        private bool CanImproveGain(
            int gain,
            Tuple< int, int > outcome,
            int left,
            int right,
            int maxSumm,
            int otherStrategy )
        {
            for( var i = left; i <= right; i++ )
            {
                var o = new Tuple< int, int >( i, otherStrategy );
                var gi = GetGain( o, maxSumm, i );
                if( gi > gain )
                {
                    return true;
                }
            }
            return false;
        }

        private int GetGain( Tuple< int, int > outcome, int maxSumm, int strategy )
        {
            return outcome.Item1 + outcome.Item2 > maxSumm ? 0 : strategy;
        }

        private List< Tuple< int, int > > GetAllOutcomes( int left, int right )
        {
            var outcomes = new List< Tuple< int, int > >();

            for( var s1 = left; s1 <= right; s1++ )
            {
                for( var s2 = left; s2 <= right; s2++ )
                {
                    outcomes.Add( new Tuple< int, int >( s1, s2 ) );
                }
            }
            return outcomes;
        }
    }
}