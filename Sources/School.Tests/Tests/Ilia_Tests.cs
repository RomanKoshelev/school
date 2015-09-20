// School (c) 2015 Krokodev
// School.Tests
// Ilia_Tests.cs

using System;
using NUnit.Framework;

namespace School.Nunit.Tests
{
    [TestFixture]
    public class Ilia
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

        private int Input()
        {
            return 6;
        }

        #endregion


        [Test]
        public void Print_42()
        {
            var a = 42;
            Print( a );
        }

        [Test]
        public void Print_Hello_World()
        {
            Print( "Hello World" );
        }

        [Test]
        public void Print_Square()
        {
            var n = Input();
            Print( n*n );
        }

        [Test]
        public void Print_Hello_World_n_times()
        {
            var n = Input();

            for( var i = 0; i < n; i = i + 1 ) {
                Print( i );
                Print( "Hello World" );
            }
        }

        [Test]
        public void Print_Hello_World_nn_times()
        {
            var n = Input();
            int i;
            n = 2500;

            for( i = 25; i < n; i = i + 1000 ) {
                Print( i );
            }

            Print( "-----" );

            Print( i );
        }

        [Test]
        public void Print_5_25()
        {
            for( var i = 25; i <= 100; i = i + 10 ) {
                Print( i );
            }
        }

        [Test]
        public void Summ_1_n()
        {
            var n = 100388.0;
            var s = 0.0;

            for( var i = 1; i <= n; i = i + 1 ) {
                s = s + i;
            }

            Print( s );

            Assert.That( s, Is.EqualTo( ( n + 1 )*n/2 ) );
        }

        [Test]
        [TestCase( 1 )]
        [TestCase( 2 )]
        [TestCase( 10 )]
        [TestCase( 100 )]
        [TestCase( 1001 )]
        [TestCase( 300 )]
        [TestCase( 5 )]
        public void Operator_if_less_10( int n )
        {
            if( n < 10 ) {
                Print( "{0}<10", n );
                Print( "(Yes)" );
            } else {
                Print( "{0}>=10", n );
                Print( "(No)" );
                if( n > 301 ) {
                    Print( "Wow! " );
                }
            }
            if( n < 1000 ) {
                Print( "why?" );
            }
        }

        [TestCase( "man", 5, "small" )]
        [TestCase( "man", 116, "big" )]
        [TestCase( "cat", 11, "big" )]
        [TestCase( "cat", 3, "small" )]
        [TestCase( "ant", 100, "unknown" )]
        public void Big_or_small( string kind, int weight, string answer )
        {
            var result = "unknown";

            if( kind == "man" ) {
                if( weight > 70 ) {
                    result = "big";
                } else {
                    result = "small";
                }
            }

            if( kind == "cat" ) {
                if( weight > 10 ) {
                    result = "big";
                } else {
                    result = "small";
                }
            }

            Print( "{0} {1} kg = {2}", kind, weight, result );
            Assert.That( result, Is.EqualTo( answer ) );
        }
    }
}