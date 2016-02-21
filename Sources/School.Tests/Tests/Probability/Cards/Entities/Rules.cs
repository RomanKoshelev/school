// School (c) 2016 School
// School.Tests
// Rules.cs

using System.Collections.Generic;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Rules
    {
        public const int MaxNumberOnHand = 5;

        public static bool IsRoyalFlush( IList< Card > cards )
        {
            return IsStraight( cards ) && IsFlush( cards ) && HightCard( cards ).Rank == Rank.Ace;
        }

        public static bool IsStraighFlush( IList< Card > cards )
        {
            return IsStraight( cards ) && IsFlush( cards );
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

            if( LastAceButNotKing( sorterd ) )
            {
                MoveLastToBegin( sorterd );
            }

            for( var i = 1; i < MaxNumberOnHand; i++ )
            {
                if( !RanksAreNeighbours( sorterd[ i ].Rank, sorterd[ i - 1 ].Rank ) )
                {
                    return false;
                }
            }
            return true;
        }

        private static void MoveLastToBegin( IList< Card > cards )
        {
            var card = cards[ 4 ];
            for( var i = MaxNumberOnHand-1; i >0; i--)
            {
                cards[ i ] = cards[ i - 1 ];
            }
            cards[ 0 ] = card;
        }

        private static bool LastAceButNotKing( IList< Card > cards )
        {
            return cards[ MaxNumberOnHand-1 ].Rank == Rank.Ace && cards[ MaxNumberOnHand-2 ].Rank != Rank.King;
        }

        private static bool RanksAreNeighbours( Rank r1, Rank r2 )
        {
            return r1 == r2 + 1 || r1 == r2 - 1 || r1 == Rank.Ace && r2 == Rank.N2
                   || r1 == Rank.N2 && r2 == Rank.Ace;
        }
    }
}