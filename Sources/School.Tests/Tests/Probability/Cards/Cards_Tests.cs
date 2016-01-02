﻿// School (c) 2016 School
// School.Tests
// Cards_Tests.cs

using NUnit.Framework;
using School.Nunit.Tests.Probability.Base;

namespace School.Nunit.Tests.Probability.Cards
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

            // Напечать число двоек
            // Убедиться что двоек осталось 3
            Print( "Num of {0}={1}", Rank.N2, deck.NumOf( Rank.N2 ) );
            Assert.That( deck.NumOf( Rank.N2 ), Is.EqualTo( 3 ) );
        }

        [Test, Ignore]
        public void We_can_shuffle_deck() {}
    }
}