// School (c) 2015 Krokodev
// School.Tests
// Searcher_Tests.cs

using NUnit.Framework;
using School.Lybrary.Algorithms.Searchers;
using School.Nunit.Bases;

// ReSharper disable All

namespace School.Nunit.Tests
{
    [TestFixture]
    public class Searcher_Tests : SearherTestsBase
    {
        [Test]
        public void Binary_Recursive_search_RandomArray()
        {
            Test_search_random_value_from_random_array( new BinarySearcherRecursive() );
        }

        [Test]
        public void Binary_Iterative_search_RandomArray()
        {
            Test_search_random_value_from_random_array( new BinarySearcherIterative() );
        }

        [Test]
        public void Linear_search_RandomArray()
        {
            Test_search_random_value_from_random_array( new LinearSearcher() );
        }
    }
}