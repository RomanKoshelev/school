// Robotango (c) 2015 Krokodev
// Robotango.Tests
// Ilia.cs

using System;
using NUnit.Framework;
using Robotango.Tests.Utils.Bases;

namespace Robotango.Tests.Cases
{
    [TestFixture]
    public class Ilia : BaseTests
    {
        #region Console

        private static void Print( object obj )
        {
            Console.WriteLine( obj );
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
            n = n*n;
            for( var i = 0; i < n; i++ ) {
                Print( i );
                Print( "Hello World" );
            }
        }
    }
}