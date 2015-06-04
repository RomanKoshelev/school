// School (c) 2015 Krokodev
// School.Tests
// Searcher_Tests.cs

using NUnit.Framework;
using School.Lybrary.Searchers;
using School.Tests.Bases;

// ReSharper disable All

namespace School.Tests.Units
{
    [TestFixture]
    public class Searcher_Tests : SearherTestsBase
    {
        [Test]
        public void Binary_search_RandomArray()
        {
            Test_search_random_value_from_random_array( new BinarySearcher() );
        }

        [Test]
        public void Linear_search_RandomArray()
        {
            Test_search_random_value_from_random_array( new LinearSearcher() );
        }
    }
}