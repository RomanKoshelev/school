// School (c) 2015 Krokodev
// School.Lybrary
// LinqExtension.cs

using System.Collections.Generic;
using System.Linq;

namespace School.Lybrary.Utils
{
    public static class LinqExtension
    {
        public static IEnumerable< T > Except<T>( this IEnumerable< T > set, T item )
        {
            return set.Except( new[] { item } );
        }

        public static IList< T > With<T>( this IEnumerable< T > set, T item )
        {
            return set.ToList().Concat( new[] { item } ).ToList();
        }

        public static bool NotEmpty<T>( this IEnumerable< T > set )
        {
            return set.Any();
        }

        public static T SelectHasMin<T>( this IEnumerable< T > set, IDictionary< T, int > value )
        {
            return value.Where( p => set.Contains( p.Key ) ).Min().Key;
            ;
        }
    }
}