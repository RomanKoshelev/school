// School (c) 2016 School
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

        public static Card HightCard( IList< Card > hand )
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

        public static bool IsStraight( IList< Card > hand )
        {
            var sorted = Helper.GetSorted( hand );

            if( LastAceButNotKing( sorted ) )
            {
                MoveLastToBegin( sorted );
            }

            for( var i = 1; i < MaxNumberOnHand; i++ )
            {
                if( !RanksAreNeighbours( sorted[ i ].Rank, sorted[ i - 1 ].Rank ) )
                {
                    return false;
                }
            }
            return true;
        }

        public static bool IsFourOfKind( IList< Card > hand )
        {
            // пройтись по всем картам чтобы найти сколько таких же -- foreach 
            //    в теле цикла -- для текущей карты card, узнаем сколько в руке с таким же значением (card.Rank)
            //    для этого выызваем функцию (которой пока нет) NumOfRank(card.Rank, hand)
            //    если возващаемое значение == 4 то вернуть true
            //    иначе -- продолжить цикл
            // в конце вернуть false, так как не нашли

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

        public static bool IsThreeOfKind( IList< Card > hand )
        {
            foreach( var card in hand )
            {
                var rankNum = NumOfRank( card.Rank, hand );
                if( rankNum >= 3 )
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

        public static bool IsFlush( IList< Card > hand )
        {
            // берём первую карту из 5 карт и запоминаем её масть 
            // проходим по всем картам и смотрим, если текущая карта другой масти то возвращаем false
            // в конце, если не нашли другой масти, то значит все масти одинаковые и возвращаем true   

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

        public static bool IsPair( IList< Card > cards )
        {
            for( var i = 0; i < cards.Count; i++ )
            {
                for( var j = i + 1; j < cards.Count; j++ )
                {
                    if( cards[ i ].Rank == cards[ j ].Rank )
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        public static bool IsTwoPairs( IList< Card > cards )
        {
            var pairsNum = 0;

            var tmp = new List< Card >( cards );

            for( var i = 0; i < tmp.Count - 1; i++ )
            {
                var c1 = tmp[ i ];

                for( var j = i + 1; j < tmp.Count; j++ )
                {
                    var c2 = tmp[ j ];
                    if( c2.Rank == c1.Rank )
                    {
                        pairsNum++;
                        tmp.RemoveAt( j );
                        break;
                    }
                }
            }
            return pairsNum >= 2;
        }

        public static bool IsFullHouse( IList< Card > cards )
        {
            var sc = Helper.GetSorted( cards );

            // 3+2
            if( sc[ 0 ].Rank == sc[ 1 ].Rank && sc[ 1 ].Rank == sc[ 2 ].Rank && sc[ 3 ].Rank == sc[ 4 ].Rank )
            {
                return true;
            }
            // 2+3
            if( sc[ 0 ].Rank == sc[ 1 ].Rank && sc[ 2 ].Rank == sc[ 3 ].Rank && sc[ 3 ].Rank == sc[ 4 ].Rank )
            {
                return true;
            }

            return false;
        }
    }
}