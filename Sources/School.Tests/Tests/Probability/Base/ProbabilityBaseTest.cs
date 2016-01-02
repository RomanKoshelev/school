using System;

namespace School.Nunit.Tests.Probability.Base
{
    public class ProbabilityBaseTest
    {
        protected void Print( string template, params object[] args )
        {
            Console.WriteLine( template, args );
        }

        protected void Print( object obj)
        {
            Console.WriteLine( obj.ToString() );
        }
    }
}