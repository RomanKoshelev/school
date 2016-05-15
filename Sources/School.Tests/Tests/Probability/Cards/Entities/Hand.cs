// School (c) 2016 School
// School.Tests
// Hand.cs

using System.Collections.Generic;
using System.Linq;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Hand
    {
        private readonly List< Card > _cards = new List< Card >();

        public int CardsNum
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

        public void Take( Card card )
        {
            _cards.Add( card );
        }

        public void Take( List< Card > cards )
        {
            foreach( var card in cards )
            {
                Take( card );
            }
        }

        public bool Contains( Card card )
        {
            return _cards.Any( c => c.Rank == card.Rank && c.Suit == card.Suit );
        }

        public bool HasPair()
        {
            return Rules.IsPair(_cards);
        }

        public bool HasTwoPairs()
        {
            return Rules.IsTwoPairs( _cards );
        }

        public bool HasRoyalFlush()
        {
            return Rules.IsRoyalFlush( _cards );
        }

        public bool HasStraightFlush()
        {
            return Rules.IsStraighFlush( _cards );
        }

        public bool HasFourOfKind()
        {
            return Rules.IsFourOfKind( _cards );
        }

        public bool HasFullHouse()
        {
            return Rules.IsFullHouse( _cards );
        }

        public bool HasFlush()
        {
            return Rules.IsFlush( _cards );
        }

        public bool HasStraight()
        {
            return Rules.IsStraight( _cards );
        }

        public bool HasThreeOfKind()
        {
            return Rules.IsThreeOfKind( _cards );
        }

        public bool HasTwoPair()
        {
            return Rules.IsTwoPairs( _cards );
        }
    }
}