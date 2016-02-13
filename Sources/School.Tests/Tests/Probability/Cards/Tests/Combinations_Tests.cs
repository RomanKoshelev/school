// School (c) 2016 School
// School.Tests
// Combinations_Tests.cs

using NUnit.Framework;
using School.Nunit.Tests.Probability.Base;
using School.Nunit.Tests.Probability.Cards.Entities;

namespace School.Nunit.Tests.Probability.Cards.Tests
{
    [TestFixture]
    public class Combinations_Tests : ProbabilityBaseTest
    {
        [Test]
        public void Cards_combinations_are_sorted()
        {
            Assert.That( Combination.RoyalFlush, Is.GreaterThan( Combination.StraightFlush ) );
            Assert.That( Combination.StraightFlush, Is.GreaterThan( Combination.FourOfKind ) );
            Assert.That( Combination.FourOfKind, Is.GreaterThan( Combination.FullHouse ) );
            Assert.That( Combination.FullHouse, Is.GreaterThan( Combination.Flush ) );
            Assert.That( Combination.Flush, Is.GreaterThan( Combination.Straight ) );
            Assert.That( Combination.Straight, Is.GreaterThan( Combination.ThreeOfKind ) );
            Assert.That( Combination.ThreeOfKind, Is.GreaterThan( Combination.TwoPair ) );
            Assert.That( Combination.TwoPair, Is.GreaterThan( Combination.Pair ) );
            Assert.That( Combination.Pair, Is.GreaterThan( Combination.HighCard ) );
        }

        [Test]
        public void Flush_royal_is_detected()
        {
          
            var success1 = new [] {
                new Card( Rank.N10, Suit.Clubs ), 
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween , Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var success2 = new [] {
                new Card( Rank.N10, Suit.Diamonds ), 
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Qween , Suit.Diamonds ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Diamonds ),
            };
            var failed1 = new [] {
                new Card( Rank.N10, Suit.Diamonds ), 
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween , Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var failed2 = new [] {
                new Card( Rank.N9, Suit.Clubs ), 
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween , Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };

            Assert.That( Rules.IsFlushRoyal(success1), Is.True );
            Assert.That( Rules.IsFlushRoyal(success2), Is.True );
            Assert.That( Rules.IsFlushRoyal(failed1), Is.False );
            Assert.That( Rules.IsFlushRoyal(failed2), Is.False );
            
        }

    }
}