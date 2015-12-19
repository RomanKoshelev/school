// School (c) 2015 Aspose
// School.Tests
// Coin_Tests.cs

using System;
using NUnit.Framework;

namespace School.Nunit.Tests.Probability
{
    [TestFixture]
    public class Coin_Tests
    {
        #region Console
        private static void Print( Coin coin )
        {
            Console.WriteLine( coin.Value );
        }

        private static void Print( string template, params object[] args )
        {
            Console.WriteLine( template, args );
        }
        #endregion



        [Test]
        public void The_generator_of_the_coins_works_properly()
        {
            var was0 = false;
            var was1 = false;

            var generator = new CoinGenerator();
            for( var i = 0; i < 10; i++ )
            {
                var coin = generator.MakeRandomCoin();
                was0 = was0 || coin.Value == 0;
                was1 = was1 || coin.Value == 1;
                Print( coin );
            }

            Assert.That( was0 && was1 );
        }

        [Test]
        public void The_count_of_0_and_1_mast_be_great_tahn_zero()
        {
            var num0 = 0;
            var num1 = 0;

            var generator = new CoinGenerator();

            for( var i = 0; i < 100; i++ )
            {
                var coin = generator.MakeRandomCoin();
                num0 += coin.Value == 0 ? 1 : 0;
                num1 += coin.Value == 1 ? 1 : 0;
            }
            Print( "Number of 0: {0}", num0 );
            Print( "Number of 1: {0}", num1 );

            Assert.That( num0, Is.GreaterThan( 0 ) );
            Assert.That( num1, Is.GreaterThan( 0 ) );
        }

        [TestCase( new [] { 2, 3, 5, 7, 10, 20, 30, 100, 300, 1000, 10*1000, 100*1000, 1*1000*1000 } )]
        public void The_sequence_of_coins_exists_and_it_counts_its_number_of_0_and_1( int[] numbers )
        {
            var generator = new CoinGenerator();

            foreach( var n in numbers )
            {
                var seq = generator.MakeRandomCoinSequance( n );

                var num0 = seq.NumOf( 0 );
                var num1 = seq.NumOf( 1 );
                var div = Math.Abs(num1-num0);

                Print( "n={0} {1}:{2}, div={3}, rate={4}", n, num0, num1, div, div/(double)n*100 );

                Assert.That( num0 + num1, Is.EqualTo( n ), "N(0)+N(1)" );
            }
        }
    }
}