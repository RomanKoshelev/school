// School (c) 2016 School
// School.Tests
// Deck.cs

using System;
using System.Collections.Generic;
using System.Linq;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Deck
    {
        private readonly List< Card > _cards = new List< Card >();
        private static readonly Random Random = new Random();

        public Deck()
        {
            CreateCards();
        }

        private void CreateCards()
        {
            for( var s = Suit.Hearts; s <= Suit.Spades; s++ )
            {
                for( var r = Rank.N2; r <= Rank.Ace; r++ )
                {
                    var card = new Card( r, s );
                    _cards.Add( card );
                }
            }
        }

        public int Size
        {
            get
            {
                return _cards.Count;
            }
        }

        public override string ToString()
        {
            var text = "";
            foreach( var card in _cards )
            {
                text += card + " ";
            }
            return text;
        }

        public int NumOf( Rank rank )
        {
            return _cards.Count( c => c.Rank == rank );
        }

        public int NumOf( Suit suit )
        {
            return _cards.Count( c => c.Suit == suit );
        }

        public int NumOf( Rank rank, Suit suit )
        {
            return _cards.Count( c => c.Rank == rank && c.Suit == suit );
        }

        private Card DrawAt( int pos )
        {
            var card = _cards[ pos ];
            _cards.RemoveAt( pos );
            return card;
        }

        public Card Draw()
        {
            return DrawAt( 0 );
        }

        public Card this[ int i ]
        {
            get
            {
                return _cards[ i ];
            }
        }

        public void Shuffle()
        {
            const int n = 300;
            var size = _cards.Count;

            for( var i = 0; i < n; i++ )
            {
                var j = Random.Next( 0, size );
                var card = DrawAt( j );
                _cards.Add( card );
            }
        }

        public List< Card > Draw( int num )
        {
            var cards = new List< Card >();
            for( var i = 0; i < num; i++ )
            {
                var card = Draw();
                cards.Add( card );
            }
            return cards;
        }
    }
}