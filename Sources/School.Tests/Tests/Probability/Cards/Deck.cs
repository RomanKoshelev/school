// School (c) 2016 School
// School.Tests
// Deck.cs

using System.Collections.Generic;
using System.Linq;

namespace School.Nunit.Tests.Probability.Cards
{
    public class Deck
    {
        private readonly List< Card > _cards = new List< Card >();

        public Deck()
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

        public Card Draw()
        {
            var card = _cards[ 0 ];
            _cards.RemoveAt( 0 );
            return card;
        }
    }
}