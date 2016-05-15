// School (c) 2016 School
// School.Tests
// Cards_Tests.cs

using NUnit.Framework;
using School.Nunit.Tests.Probability.Base;
using School.Nunit.Tests.Probability.Cards.Entities;

namespace School.Nunit.Tests.Probability.Cards.Tests
{
    [TestFixture]
    public class Cards_Tests : ProbabilityBaseTest
    {
        [Test]
        public void We_have_cards_with_ranks_and_suits()
        {
            var card = new Card( Rank.Jack, Suit.Spades );

            Assert.That( card.Suit, Is.EqualTo( Suit.Spades ) );
            Assert.That( card.Rank, Is.EqualTo( Rank.Jack ) );
        }

        [Test]
        public void We_can_print_card()
        {
            // https://en.wikipedia.org/wiki/Playing_cards_in_Unicode
            var js = new Card( Rank.Jack, Suit.Spades );
            var qh = new Card( Rank.Qween, Suit.Hearts );
            var ad = new Card( Rank.Ace, Suit.Diamonds );
            var kc = new Card( Rank.King, Suit.Clubs );

            Print( js );
            Print( qh );
            Print( ad );
            Print( kc );

            Assert.That( kc.ToString(), Is.EqualTo( "K♣" ) );
            Assert.That( ad.ToString(), Is.EqualTo( "A♦" ) );
            Assert.That( qh.ToString(), Is.EqualTo( "Q♥" ) );
            Assert.That( js.ToString(), Is.EqualTo( "J♠" ) );
        }

        [Test]
        public void We_have_deck_of_crads()
        {
            var deck = new Deck();

            Assert.That( deck.Size, Is.EqualTo( 52 ) );
            Assert.That( deck.NumOf( Rank.Qween ), Is.EqualTo( 4 ) );
            Assert.That( deck.NumOf( Suit.Hearts ), Is.EqualTo( 13 ) );
            Assert.That( deck.NumOf( Rank.N6, Suit.Clubs ), Is.EqualTo( 1 ) );
        }

        [Test]
        public void Suits_are_ordered()
        {
            for( var suit = Suit.Hearts; suit <= Suit.Spades; suit++ )
            {
                Print( "{0} {1}", Card.SuitToString( suit ), suit.ToString() );
            }

            Assert.That( Suit.Hearts < Suit.Diamonds );
            Assert.That( Suit.Diamonds < Suit.Clubs );
            Assert.That( Suit.Clubs < Suit.Spades );
        }

        [Test]
        public void We_can_print_deck()
        {
            var deck = new Deck();

            Print( deck );

            Assert.That( deck.ToString(), Is.StringContaining( "2♥" ) );
            Assert.That( deck.ToString(), Is.StringContaining( "A♠" ) );
        }

        [Test]
        public void We_can_draw_card_from_deck()
        {
            var deck = new Deck();
            Print( deck );
            Assert.That( deck.Size, Is.EqualTo( 52 ) );

            var card1 = deck.Draw();
            Print( card1 );
            Print( deck );
            Assert.That( deck.Size, Is.EqualTo( 51 ) );
            Assert.That( card1.Rank, Is.EqualTo( Rank.N2 ) );
            Assert.That( card1.Suit, Is.EqualTo( Suit.Hearts ) );

            var card2 = deck.Draw();
            Print( card2 );
            Print( deck );
            Assert.That( deck.Size, Is.EqualTo( 50 ) );
            Assert.That( card2.Rank, Is.EqualTo( Rank.N3 ) );
            Assert.That( card2.Suit, Is.EqualTo( Suit.Hearts ) );

            Print( "Num of {0}={1}", Suit.Hearts, deck.NumOf( Suit.Hearts ) );
            Assert.That( deck.NumOf( Suit.Hearts ), Is.EqualTo( 11 ) );
            Assert.That( deck.NumOf( Suit.Diamonds ), Is.EqualTo( 13 ) );

            Print( "Num of {0}={1}", Rank.N2, deck.NumOf( Rank.N2 ) );
            Assert.That( deck.NumOf( Rank.N2 ), Is.EqualTo( 3 ) );
        }

        // мы умем перемешивать колоду
        [Test]
        public void We_can_shuffle_deck()
        {
            const int n = 100000;
            for( var i = 0; i < n; i++ )
            {
                var deck = new Deck();
                deck.Shuffle();

                if( i%( n/10 ) == 0 )
                {
                    Print();
                    Print( deck );
                }

                Assert.That(
                    !( deck[ 0 ].Is( Rank.N2, Suit.Hearts ) && deck[ 1 ].Is( Rank.N3, Suit.Hearts )
                       && deck[ 2 ].Is( Rank.N4, Suit.Hearts ) && deck[ 3 ].Is( Rank.N5, Suit.Hearts )
                       && deck[ 51 ].Is( Rank.Ace, Suit.Spades ) ) );
            }
        }

        // мы умем считать статистику пар
        [Test]
        public void We_can_calculate_pair_statistics()
        {
            const int total = 10000;
            var pairNum = 0;
            var log = "";

            for( var i = 0; i < total; i++ )
            {
                var deck = new Deck();
                deck.Shuffle();

                var hand = new Hand();
                var cards = deck.Draw( 5 );

                hand.Take( cards );
                var hasPair = hand.HasPair();

                log += i > 100 ? "" : string.Format( "{0} {1}\n", hasPair ? "+ " : "  ", hand );
                pairNum += hasPair ? 1 : 0;
            }

            Print( "Total: {0}", total );
            Print( "Pairs: {0} ({1:F}%)", pairNum, ( double ) pairNum/total*100 );
            Print();
            Print( log );
        }

        // мы умем считать статистику двух пар
        [Test]
        public void We_can_calculate_two_pairs_statistics()
        {
            const int total = 10000;
            var success = 0;
            var log = "";

            for( var i = 0; i < total; i++ )
            {
                var deck = new Deck();
                deck.Shuffle();

                var hand = new Hand();
                var cards = deck.Draw( 5 );

                hand.Take( cards );
                var hasPair = hand.HasTwoPairs();

                log += i > 100 ? "" : string.Format( "{0} {1}\n", hasPair ? "+ " : "  ", hand );
                success += hasPair ? 1 : 0;
            }

            Print( "Total:     {0}", total );
            Print( "Two pairs: {0} ({1:F}%)", success, ( double ) success/total*100 );
            Print();
            Print( log );
        }

        // Мы умеем узнавать пару
        [Test]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.N4, Rank.N5 }, false )]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.N2, Rank.N5 }, true )]
        public void We_can_recognise_pair( Rank[] ranks, bool answer )
        {
            var hand = new Hand();

            foreach( var rank in ranks )
            {
                hand.Take( new Card( rank, Suit.Clubs ) );
            }

            Print( hand );
            Print( hand.HasPair() ? "Has pair" : "No" );

            Assert.That( hand.HasPair(), Is.EqualTo( answer ) );
        }


        // Мы умеем узнавать две пары
        [Test]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.N4, Rank.N5 }, false )]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.N2, Rank.N5 }, false )]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.N2, Rank.Jack }, true )]
        [TestCase( new[] { Rank.Ace, Rank.N2, Rank.Jack, Rank.Jack, Rank.Jack }, false )]
        [TestCase( new[] { Rank.Jack, Rank.N2, Rank.Jack, Rank.Jack, Rank.Jack }, true )]
        [TestCase( new[] { Rank.Jack, Rank.Jack, Rank.Jack, Rank.Jack, Rank.Jack }, true )]
        [TestCase( new[] { Rank.Jack, Rank.Jack, Rank.Jack, Rank.Ace, Rank.Ace }, true )]
        [TestCase( new[] { Rank.Jack, Rank.Jack, Rank.Jack, Rank.Ace, Rank.Qween }, false )]
        [TestCase( new[] { Rank.Ace, Rank.Jack, Rank.Ace, Rank.Qween, Rank.Qween }, true )]
        [TestCase( new[] { Rank.N2, Rank.N2, Rank.N2, Rank.N2, Rank.N2 }, true )]
        public void We_can_recognise_two_pairs( Rank[] ranks, bool answer )
        {
            var hand = new Hand();

            foreach( var rank in ranks )
            {
                hand.Take( new Card( rank, Suit.Clubs ) );
            }

            Print( hand );
            Print( hand.HasTwoPairs() ? "Has two pair" : "No" );

            Assert.That( hand.HasTwoPairs(), Is.EqualTo( answer ) );
        }
    }
}