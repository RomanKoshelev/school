// School (c) 2015 Aspose
// School.Tests
// CoinGenerator.cs

using System;
using System.Collections.Generic;

namespace School.Nunit.Tests.Probability
{
    public class CoinGenerator
    {
        private readonly Random _random = new Random();

        public Coin MakeRandomCoin()
        {
            var val = _random.Next( 0, 2 );
            var coin = new Coin( val );
            return coin;
        }

        public CoinSequence MakeRandomCoinSequance( int len )
        {
            var seq = new CoinSequence();

            for( int i = 0; i < len; i++ )
            {
                var coin = MakeRandomCoin();
                seq.Add( coin );
            }

            return seq;
        }
    }
    public class CoinSequence
    {
        private readonly List< Coin > _coins = new List< Coin >();

        public int NumOf( int val )
        {
            var num = 0;
            for( var i = 0; i < _coins.Count; i++ )
            {
                num += _coins[ i ].Value == val ? 1 : 0;
            }
            return num;
        }

        public void Add( Coin coin )
        {
            _coins.Add( coin );
        }
    }
    public class Coin
    {
        public readonly int Value;

        public Coin( int value )
        {
            Value = value;
        }
    }
}