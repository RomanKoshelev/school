// School (c) 2016 School
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
    }
}