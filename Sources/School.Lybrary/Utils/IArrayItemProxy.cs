﻿// School (c) 2015 Krokodev
// School.Lybrary
// IArrayItemProxy.cs

namespace School.Lybrary.Utils
{
    public interface IArrayItemProxy
    {
        bool Is_Greater_than_item( int otherIndex );
        bool Is_LessOrEqual_than_value( int value );
        bool Is_Equal_to_value( int value );
        bool Is_Greater_than_value( int value );
        bool Is_Less_than_value( int value );
    }
}