// School (c) 2016 School
// School.Tests
// Hand.cs

using System.Collections.Generic;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Hand
    {
        private readonly List< Card > _cards = new List< Card >();

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

        public bool HasPair()
        {
            for( var i = 0; i < _cards.Count - 1; i++ )
            {
                var c1 = _cards[ i ];

                for( var j = i + 1; j < _cards.Count; j++ )
                {
                    var c2 = _cards[ j ];
                    if( c2.Rank == c1.Rank )
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        public bool Has10()
        {
            /*            for( var i = 0; i < _cards.Count; i++) 
            {
                if( _cards[ i ].Rank == Rank.N10 )
                {
                    return true;
                }
            }
 */
            // если есть 10 (в переменной _cards) то вернуть true 
            foreach( var card in _cards )
            {
                if( card.Rank == Rank.N10 )
                {
                    return true;
                }
            }

            // иначе вернуть false 
            return false;
        }

        public bool HasPair_Ilia()
        {
            for( var i = 0; i < _cards.Count - 1; i++ )
            {
                var c1 = _cards[ i ];
                for( var j = i + 1; j < _cards.Count; j++ )
                {
                    var c2 = _cards[ j ];
                    if( c1.Rank == c2.Rank )
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        public bool HasTwoPairs()
        {
            var pairsNum = 0;

            var cards = new List< Card >( _cards );

            for( var i = 0; i < cards.Count - 1; i++ )
            {
                var c1 = cards[ i ];

                for( var j = i + 1; j < cards.Count; j++ )
                {
                    var c2 = cards[ j ];
                    if( c2.Rank == c1.Rank )
                    {
                        pairsNum++;
                        cards.RemoveAt( j );
                        break;
                    }
                }
            }
            return pairsNum == 2;
        }
    }
}