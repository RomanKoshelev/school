// School (c) 2015 Krokodev
// School.Lybrary
// DijkstraPathFinderBase.cs

using System;
using System.Collections.Generic;
using School.Lybrary.Structures.Graphs;

namespace School.Lybrary.Algorithms.Traverse
{
    // ReSharper disable All
    public class DijkstraPathFinderBase
    {
        #region Consts

        protected const int Infinity = Int32.MaxValue;

        #endregion


        #region Fields

        protected IDictionary< IVertex, int > Dist = new Dictionary< IVertex, int >();
        protected IDictionary< IVertex, IList< IVertex > > Path = new Dictionary< IVertex, IList< IVertex > >();
        protected IList< IVertex > Qeue = new List< IVertex >();

        #endregion


        #region Utils

        protected IList< IVertex > EmptyPath()
        {
            return new List< IVertex >();
        }

        #endregion
    }
}