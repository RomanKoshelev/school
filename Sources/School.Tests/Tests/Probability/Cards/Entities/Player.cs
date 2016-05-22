// School (c) 2016 School
// School.Tests
// Player.cs

using System;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    public class Player
    {
        private readonly Hand _hand = new Hand();

        public override string ToString()
        {
            return Name + ": " + _hand;
        }

        public Player( string name )
        {
            Name = name;
        }

        public string Name { get; set; }

        public int CardsNum
        {
            get
            {
                return _hand.CardsNum;
            }
        }

        public void Take( Card card )
        {
            _hand.Take( card );
        }

        public bool Has( Card card )
        {
            return _hand.Contains( card );
        }

        public bool Has( Combination combination )
        {
            switch( combination )
            {
                case Combination.RoyalFlush :
                    return _hand.HasRoyalFlush();

                case Combination.StraightFlush :
                    return _hand.HasStraightFlush();

                case Combination.FourOfKind :
                    return _hand.HasFourOfKind();

                case Combination.FullHouse :
                    return _hand.HasFullHouse();

                case Combination.Flush :
                    return _hand.HasFlush();

                case Combination.Straight :
                    return _hand.HasStraight();

                case Combination.ThreeOfKind :
                    return _hand.HasThreeOfKind();

                case Combination.TwoPair :
                    return _hand.HasTwoPair();

                case Combination.Pair :
                    return _hand.HasPair();
            }
            throw new ArgumentException( combination.ToString() );
        }

        public void Take( Card[] cards )
        {
            foreach( var card in cards )
            {
                Take( card );
            }
        }

        public Combination ask_the_best_combination()
        {
            // todo:
            // начать проверку с самой крутой комбинации и если это не ноа идем вниз по комбинациям
            return  Combination.RoyalFlush;
        }
    }
}