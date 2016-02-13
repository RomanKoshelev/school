// School (c) 2016 School
// School.Tests
// Helper.cs

using System.Collections.Generic;
using System.Linq;

namespace School.Nunit.Tests.Probability.Cards.Entities
{
    internal class Helper
    {
        public static List< Card > GetSorted( IList< Card > cards )
        {
            return cards.OrderBy( c => c.Rank ).ToList();
        }
    }
}