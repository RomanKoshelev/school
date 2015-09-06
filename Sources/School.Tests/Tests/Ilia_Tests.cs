// Robotango (c) 2015 Krokodev
// Robotango.Tests
// Ilia.cs

using System;
using NUnit.Framework;

namespace School.Nunit.Tests
{
    [TestFixture]
    public class Ilia
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
            int a = 42;
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
            n = 2500 ;

            for( i = 25; i < n; i = i + 1000 ) {
                Print( i );
            }
            
            Print("-----");

            Print( i );
        }

        [Test]
        public void Print_5_25()
        {
            for( var i = 25; i <= 100 ; i = i + 10 ) {
                Print( i );
            }



        }

        [Test]
        public void Summ_1_n()
        {
            var n =100343454.0;
            var s = 0.0;

            for( var i = 1; i <= n; i = i + 1 ) {
                s = s + i;

            }      
            
            Print(s);

            Assert.That( s, Is.EqualTo( (n+1)*n/2 ) );
        }

        [Test]
        public void Factorial()
        {
            var n =10;
            //var f = ;

            
            //Print(f);

            //Assert.That( s, Is.EqualTo( (n+1)*n/2 ) );
        }
    }
}