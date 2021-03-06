﻿// School (c) 2016 School
// School.Tests
// Game_Tests.cs

using NUnit.Framework;
using School.Nunit.Tests.Probability.Base;
using School.Nunit.Tests.Probability.Cards.Entities;

namespace School.Nunit.Tests.Probability.Cards.Tests
{
    [TestFixture]
    public class Game_Tests : ProbabilityBaseTest
    {
        [Test]
        public void Player_exists()
        {
            var player = new Player( "mr. First" );

            Assert.That( player.Name, Is.EqualTo( "mr. First" ) );
        }

        [Test]
        public void Player_takes_cards()
        {
            var player = new Player( "mr. First" );
            var deck = new Deck();

            var card1 = deck.Draw();
            var card2 = deck.Draw();
            player.Take( card1 );
            player.Take( card2 );

            Print( card1 );
            Print( card2 );
            Print( player );
            Print( deck );

            Assert.That( player.Has( card1 ) );
            Assert.That( player.Has( card2 ) );
            Assert.That( player.CardsNum, Is.EqualTo( 2 ) );
            Assert.That( deck.Size, Is.EqualTo( 50 ) );
        }

        [Test]
        public void Player_says_his_combination()
        {
            var player = new Player( "Dad" );
            player.Take( new Card( Rank.N2, Suit.Clubs ) );
            player.Take( new Card( Rank.Ace, Suit.Spades ) );
            player.Take( new Card( Rank.N9, Suit.Clubs ) );
            player.Take( new Card( Rank.N2, Suit.Diamonds ) );
            player.Take( new Card( Rank.N2, Suit.Hearts ) );

            Assert.That( player.Has( Combination.Pair ) );
            Assert.That( player.Has( Combination.ThreeOfKind ) );
            Assert.IsFalse( player.Has( Combination.Flush ) );
            Assert.IsFalse( player.Has( Combination.FullHouse ) );
        }

        [Test]
        public void Player_ask_the_best_combination()
        {
            var player = new Player( "Ilia" );

            // создать пять карт
            var fullHaouse = new[] {
                new Card( Rank.Qween, Suit.Hearts ),
                new Card( Rank.Qween, Suit.Spades ),
                new Card( Rank.Jack, Suit.Clubs ),
                new Card( Rank.Jack, Suit.Spades ),
                new Card( Rank.Jack, Suit.Diamonds ),
            };
            var pair = new[] {
                new Card( Rank.Qween, Suit.Hearts ),
                new Card( Rank.Qween, Suit.Spades ),
                new Card( Rank.N7, Suit.Clubs ),
                new Card( Rank.N10, Suit.Spades ),
                new Card( Rank.Jack, Suit.Diamonds ),
            };


            
            // дать карты игроку
            player.Take( fullHaouse );

            // спросить игрока про лучшую комбюинацуию 
           var combination=player.ask_the_best_combination();

            // убедиться ,что ответ верный 

            Assert.That( player.Name == "Ilia" );
            Assert.That( player.CardsNum == 5 );
        }
    }
}