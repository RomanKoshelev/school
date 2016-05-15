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
        public void Straight_flush_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N9, Suit.Clubs ),
            };
            var success3 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.N3, Suit.Clubs ),
                new Card( Rank.N4, Suit.Clubs ),
                new Card( Rank.N5, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var failed1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N9, Suit.Clubs ),
            };
            var failed2 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N9, Suit.Clubs ),
            };

            Assert.That( Rules.IsStraighFlush( success1 ), Is.True, "Success 1" );
            Assert.That( Rules.IsStraighFlush( success2 ), Is.True, "Success 2" );
            Assert.That( Rules.IsStraighFlush( success3 ), Is.True, "Success 3" );
            Assert.That( Rules.IsStraighFlush( failed1 ), Is.False, "Failed 1" );
            Assert.That( Rules.IsStraighFlush( failed2 ), Is.False, "Failed 2" );
        }

        [Test]
        public void Straight_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Diamonds),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Hearts),
                new Card( Rank.N9, Suit.Clubs ),
            };
            var success3 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.N3, Suit.Spades),
                new Card( Rank.N4, Suit.Clubs ),
                new Card( Rank.N5, Suit.Diamonds),
                new Card( Rank.Ace, Suit.Hearts ),
            };
            var failed1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N8, Suit.Clubs ),
            };
            var failed2 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N9, Suit.Clubs ),
            };

            Assert.That( Rules.IsStraight( success1 ), Is.True, "Success 1" );
            Assert.That( Rules.IsStraight( success2 ), Is.True, "Success 2" );
            Assert.That( Rules.IsStraight( success3 ), Is.True, "Success 3" );
            Assert.That( Rules.IsStraight( failed1 ), Is.False, "Failed 1" );
            Assert.That( Rules.IsStraight( failed2 ), Is.False, "Failed 2" );
        }

        [Test]
        public void Roya_flush_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Qween, Suit.Diamonds ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Diamonds ),
            };
            var failed1 = new[] {
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            var failed2 = new[] {
                new Card( Rank.N9, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };

            Assert.That( Rules.IsRoyalFlush( success1 ), Is.True );
            Assert.That( Rules.IsRoyalFlush( success2 ), Is.True );
            Assert.That( Rules.IsRoyalFlush( failed1 ), Is.False );
            Assert.That( Rules.IsRoyalFlush( failed2 ), Is.False );
        }

        [Test]
        public void Four_of_kind_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };

            var success2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Hearts ),
                new Card( Rank.King, Suit.Hearts ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.N10, Suit.Spades ),
            };
            var success3 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
            };
            var failed1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
            };

            var failed2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            Assert.That( Rules.IsFourOfKind( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsFourOfKind( success2 ), Is.True, "success2" );
            Assert.That( Rules.IsFourOfKind( success3 ), Is.True, "success3" );
            Assert.That( Rules.IsFourOfKind( failed1 ), Is.False, "failed1" );
            Assert.That( Rules.IsFourOfKind( failed2 ), Is.False, "failed2" );
        }

        [Test]
        public void Three_of_kind_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };

            var success2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Hearts ),
                new Card( Rank.N10, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.N10, Suit.Spades ),
            };
            var success3 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
            };
            var failed1 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
            };

            var failed2 = new[] {
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Ace, Suit.Clubs ),
            };
            Assert.That( Rules.IsThreeOfKind( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsThreeOfKind( success2 ), Is.True, "success2" );
            Assert.That( Rules.IsThreeOfKind( success3 ), Is.True, "success3" );
            Assert.That( Rules.IsThreeOfKind( failed1 ), Is.False, "failed1" );
            Assert.That( Rules.IsThreeOfKind( failed2 ), Is.False, "failed2" );
        }

        [Test]
        public void Flush_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.N8, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.N9, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.Qween, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Diamonds ),
                new Card( Rank.N3, Suit.Diamonds ),
                new Card( Rank.King, Suit.Diamonds ),
            };
            var success3 = new[] {
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.N4, Suit.Spades ),
                new Card( Rank.N7, Suit.Spades ),
                new Card( Rank.N8, Suit.Spades ),
                new Card( Rank.King, Suit.Spades ),
            };
            var failed1 = new[] {
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.N3, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };

            var failed2 = new[] {
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.N10, Suit.Clubs ),
                new Card( Rank.N3, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };
            Assert.That( Rules.IsFlush( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsFlush( success2 ), Is.True, "success2" );
            Assert.That( Rules.IsFlush( success3 ), Is.True, "success3" );
            Assert.That( Rules.IsFlush( failed1 ), Is.False, "failed1" );
            Assert.That( Rules.IsFlush( failed2 ), Is.False, "failed2" );

        }

        [Test]
        public void FullHouse_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.Qween, Suit.Hearts),
                new Card( Rank.Qween, Suit.Spades),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Spades),
                new Card( Rank.Jack, Suit.Diamonds),
            };
            var failed1 = new[] {
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.N3, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };
            Assert.That( Rules.IsFullHouse( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsFullHouse( failed1 ), Is.False, "failed1" );

        }
        [Test]
        public void TwoPairs_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.Jack, Suit.Clubs ),
            };

            var failed1 = new[] {
                new Card( Rank.N4, Suit.Clubs ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N5, Suit.Clubs ),
            };

            Assert.That( Rules.IsTwoPairs( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsTwoPairs( success2 ), Is.True, "success2" );
            Assert.That( Rules.IsTwoPairs( failed1 ), Is.False, "failed1" );
        }

        [Test]
        public void HighCard_is_detected()
        {
            var cards1 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.Ace, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };
            var cards2 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.N10, Suit.Clubs ),
            };

            var cards3 = new[] {
                new Card( Rank.N4, Suit.Clubs ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Qween, Suit.Clubs ),
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.N5, Suit.Clubs ),
            };

            Assert.That( Rules.HightCard( cards1 ).Rank, Is.EqualTo( Rank.Ace), "cards1" );
            Assert.That( Rules.HightCard( cards2 ).Rank, Is.EqualTo( Rank.King), "cards2" );
            Assert.That( Rules.HightCard( cards3 ).Rank, Is.EqualTo( Rank.Qween), "cards3" );
        }

        [Test]
        public void Pair_is_detected()
        {
            var success1 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.King, Suit.Clubs ),
            };
            var success2 = new[] {
                new Card( Rank.N2, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Hearts ),
                new Card( Rank.King, Suit.Diamonds ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.N10, Suit.Clubs ),
            };

            var failed1 = new[] {
                new Card( Rank.N4, Suit.Clubs ),
                new Card( Rank.N10, Suit.Diamonds ),
                new Card( Rank.Ace, Suit.Clubs ),
                new Card( Rank.King, Suit.Clubs ),
                new Card( Rank.N5, Suit.Clubs ),
            };

            Assert.That( Rules.IsPair( success1 ), Is.True, "success1" );
            Assert.That( Rules.IsPair( success2 ), Is.True, "success2" );
            Assert.That( Rules.IsPair( failed1 ), Is.False, "failed1" );
        }
    }
}