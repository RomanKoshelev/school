// School (c) 2016 School
// School.Tests
// Card.cs

using System;
using System.Collections.Generic;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Card
    {
        public Card( Rank rank, Suit suit )
        {
            Suit = suit;
            Rank = rank;
        }

        public override string ToString()
        {
            var suit = SuitToString( Suit );
            var rank = RankToString( Rank );

            return string.Format( "{0}{1}", rank, suit );
        }

        public static string SuitToString( Suit suit )
        {
            switch( suit )
            {
                case Suit.Clubs :
                    return "♣";
                case Suit.Diamonds :
                    return "♦";
                case Suit.Hearts :
                    return "♥";
                case Suit.Spades :
                    return "♠";
                default :
                    throw new ArgumentOutOfRangeException( "suit", suit, null );
            }
        }

        private static string RankToString( Rank rank )
        {
            var ranks = new List< string > { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
            return ranks[ ( int ) rank - ( int ) Rank.N2 ];
        }

        public Suit Suit { get; private set; }
        public Rank Rank { get; private set; }

        public bool Is( Rank rank, Suit suit )
        {
            return Suit == suit && Rank == rank;
        }
    }
}