// School (c) 2016 School
// School.Tests
// Rules.cs

using System.Collections.Generic;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Rules
    {
        public const int MaxNumberOnHand = 5;

        public static bool IsFlushRoyal( IList< Card > cards )
        {
            return IsStraight( cards ) && IsFlush( cards ) && HightCard( cards ).Rank == Rank.Ace;
        }

        private static Card HightCard( IList< Card > cards )
        {
            var hc = cards[ 0 ];
            foreach( var card in cards )
            {
                if( card.Rank > hc.Rank )
                {
                    hc = card;
                }
            }
            return hc;
        }

        private static bool IsFlush( IList< Card > cards )
        {
            var suit = cards[ 0 ].Suit;
            foreach( var card in cards )
            {
                if( card.Suit != suit )
                {
                    return false;
                }
            }
            return true;
        }

        private static bool IsStraight( IList< Card > cards )
        {
            var sorterd = Helper.GetSorted( cards );

            for( var i = 1; i < MaxNumberOnHand; i++ )
            {
                if( sorterd[ i ].Rank != sorterd[ i - 1 ].Rank + 1 )
                {
                    return false;
                }
            }
            return true;
        }
    }
}