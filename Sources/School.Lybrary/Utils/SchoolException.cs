// School (c) 2015 Krokodev
// School.Lybrary
// SchoolException.cs

using System;

namespace School.Lybrary.Utils
{
    public class SchoolException : Exception
    {
        public SchoolException( string template, params object[] args )
            : base( string.Format( template, args ) ) {}
    }
}