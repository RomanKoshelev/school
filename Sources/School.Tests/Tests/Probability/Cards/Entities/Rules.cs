﻿// School (c) 2016 School
// School.Tests
// Rules.cs

using System.Collections.Generic;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Rules
    {
        public const int MaxNumberOnHand = 5;

        public static bool IsRoyalFlush( IList< Card > hand )
        {
            return IsStraight( hand ) && IsFlush( hand ) && HightCard( hand ).Rank == Rank.Ace;
        }

        public static bool IsStraighFlush( IList< Card > hand )
        {
            return IsStraight( hand ) && IsFlush( hand );
        }

        private static Card HightCard( IList< Card > hand )
        {
            var hc = hand[ 0 ];
            foreach( var card in hand )
            {
                if( card.Rank > hc.Rank )
                {
                    hc = card;
                }
            }
            return hc;
        }

        private static bool IsFlush( IList< Card > hand )
        {
            var suit = hand[ 0 ].Suit;
            foreach( var card in hand )
            {
                if( card.Suit != suit )
                {
                    return false;
                }
            }
            return true;
        }

        private static bool IsStraight( IList< Card > hand )
        {
            var sorterd = Helper.GetSorted( hand );

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

        public static bool IsFourOfKind( IList< Card > hand )
        {
            // пройитсь по всем картам чтобы найти сколько таких же -- foreach 
            //    в теле цикла -- для текущей карты card, узнаем сколько в руке с таким же значением (card.Rank)
            //    для этого выызваем функцию (которой пока нет) NumOfRank(card.Rank, hand)
            //    если возващаемое значение == 4 то вернуть true
            //    иначе -- продолжить цикл
            // в конце вернуть false, т ак как не нашли

            foreach( var card in hand )
            {
                var rankNum = NumOfRank( card.Rank, hand );
                if( rankNum >= 4 )
                {
                    return true;
                }
            }
            return false;
        }

        private static int NumOfRank( Rank rank, IList< Card > cards )
        {
            var num = 0;
            foreach( var card in cards )
            {
                if( card.Rank == rank )
                {
                    num++;
                }
            }
            return num;
        }

        private static void MoveLastToBegin( IList< Card > cards )
        {
            var card = cards[ 4 ];
            for( var i = MaxNumberOnHand - 1; i > 0; i-- )
            {
                cards[ i ] = cards[ i - 1 ];
            }
            cards[ 0 ] = card;
        }

        private static bool LastAceButNotKing( IList< Card > cards )
        {
            return cards[ MaxNumberOnHand - 1 ].Rank == Rank.Ace && cards[ MaxNumberOnHand - 2 ].Rank != Rank.King;
        }

        private static bool RanksAreNeighbours( Rank r1, Rank r2 )
        {
            return r1 == r2 + 1 || r1 == r2 - 1 || r1 == Rank.Ace && r2 == Rank.N2
                   || r1 == Rank.N2 && r2 == Rank.Ace;
        }
    }
} //return IsStraight( cards ) && IsFlush( cards ) && HightCard( cards ).Rank == Rank.Ace;