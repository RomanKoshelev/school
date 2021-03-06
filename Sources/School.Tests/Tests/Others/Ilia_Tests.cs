﻿// School (c) 2015 Aspose
// School.Tests
// Ilia_Tests.cs

using System;
using System.Linq;
using NUnit.Framework;

namespace School.Nunit.Tests
{
    [TestFixture]
    public class Ilia
    {
        #region Console
        private static void Print( object arg )
        {
            Console.WriteLine( arg.ToString() );
        }

        private static void Print( string template, params object[] args )
        {
            Console.WriteLine( template, args );
        }

        private int Input()
        {
            return 6;
        }
        #endregion



        [Test]
        public void Print_42()
        {
            var a = 42;
            Print( a );
        }

        [Test]
        public void Print_Hello_World()
        {
            Print( "Hello World" );
        }

        [Test]
        public void Print_Square()
        {
            var n = Input();
            Print( n*n );
        }

        [Test]
        public void Print_Hello_World_n_times()
        {
            var n = Input();

            for( var i = 0; i < n; i = i + 1 )
            {
                Print( i );
                Print( "Hello World" );
            }
        }

        [Test]
        public void Print_Hello_World_nn_times()
        {
            var n = Input();
            int i;
            n = 2500;

            for( i = 25; i < n; i = i + 10000 )
            {
                Print( i );
            }

            Print( "-----" );

            Print( i );
        }

        [Test]
        public void Print_5_25()
        {
            for( var i = 25; i <= 100; i = i + 10 )
            {
                Print( i );
            }
        }

        [Test]
        public void Summ_1_n()
        {
            var n = 100388.0;
            var s = 0.0;

            for( var i = 1; i <= n; i = i + 1 )
            {
                s = s + i;
            }

            Print( s );

            Assert.That( s, Is.EqualTo( ( n + 1 )*n/2 ) );
        }

        [Test]
        [TestCase( 1 )]
        [TestCase( 2 )]
        [TestCase( 10 )]
        [TestCase( 100 )]
        [TestCase( 1001 )]
        [TestCase( 300 )]
        [TestCase( 5 )]
        public void Operator_if_less_10( int n )
        {
            if( n < 10 )
            {
                Print( "{0}<10", n );
                Print( "(Yes)" );
            }
            else
            {
                Print( "{0}>=10", n );
                Print( "(No)" );
                if( n > 301 )
                {
                    Print( "Wow! " );
                }
            }
            if( n < 1000 )
            {
                Print( "why?" );
            }
        }

        [Test]
        [TestCase( "man", 5, "small" )]
        [TestCase( "man", 116, "big" )]
        [TestCase( "cat", 11, "big" )]
        [TestCase( "cat", 3, "small" )]
        [TestCase( "whale", 3000, "small" )]
        [TestCase( "whale", 1000, "small" )]
        [TestCase( "whale", 3001, "big" )]
        [TestCase( "whale", 5000, "big" )]
        [TestCase( "ant", 100, "unknown" )]
        public void Big_or_small( string kind, int weight, string answer )
        {
            var result = "unknown";

            if( kind == "man" )
            {
                result = weight > 70 ? "big" : "small";
            }

            if( kind == "cat" )
            {
                result = weight > 10 ? "big" : "small";
            }

            if( kind == "whale" )
            {
                result = weight > 3000 ? "big" : "small";
            }

            Print( "{0} {1} kg = {2}", kind, weight, result );
            Assert.That( result, Is.EqualTo( answer ) );
        }

        [TestCase( "man", 1, "small" )]
        [Test]
        [TestCase( "man", 5, "small" )]
        [TestCase( "man", 50, "small" )]
        [TestCase( "man", 59, "small" )]
        [TestCase( "man", 60, "normal" )]
        [TestCase( "man", 110, "normal" )]
        [TestCase( "man", 111, "big" )]
        [TestCase( "man", 200, "big" )]
        [TestCase( "man", 299, "big" )]
        [TestCase( "man", 300, "fat" )]
        [TestCase( "man", 500, "fat" )]
        [TestCase( "man", 10000, "fat" )]
        [TestCase( "mouse", 1, "big" )]
        public void Big_or_normal_or_small( string kind, int weight, string answer )
        {
            var result = "unknown";

            if( kind == "man" )
            {
                Print( "- Man" );

                if( weight > 299 && weight < 10000000 )
                {
                    result = "fat";
                    Print( "-- Fat" );
                }

                if( weight > 110 && weight < 300 )
                {
                    result = "big";
                    Print( "-- Big" );
                }

                if( weight > 59 && weight < 111 )
                {
                    result = "normal";
                    Print( "-- Normal" );
                }

                if( weight > 0 && weight < 60 )
                {
                    result = "small";
                    Print( "-- Small" );
                }
            }

            if( kind == "mouse" )
            {
                Print( "- Mouse" );
                if( weight > 0 && weight < 2 )
                {
                    result = "big";
                    Print( "-- Big" );
                }
            }

            Print( "{0} {1} kg = {2}", kind, weight, result );
            Assert.That( result, Is.EqualTo( answer ) );
        }

        [TestCase( new[] { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1 }, 10 )]
        [TestCase( new[] { 6, 19, 1, 4 }, 30 )]
        [TestCase( new[] { 10, 7, 6 }, 23 )]
        [TestCase( new[] { 1, 2, 1 }, 4 )]
        [TestCase( new[] { 0, 1, 2 }, 3 )]
        [TestCase( new[] { 100, -100 }, 0 )]
        [TestCase( new[] { 42 }, 42 )]
        [TestCase( new int[] { }, 0 )]
        public void Money_sum( int[] money, int sum )
        {
            var result = 0;
            var i = 0;

            while( i < money.Length )
            {
                result = result + money[ i ];
                Print( money[ i ] );
                i = i + 1;
            }

            Print( "=================" );
            Print( result );

            Assert.That( result, Is.EqualTo( sum ) );
        }

        [TestCase( new[] { 1, 2, 6 }, false )]
        [TestCase( new[] { 4, 62, 7, 42 }, true )]
        [TestCase( new[] { 4, 62, 7, 42, 157 }, true )]
        public void Is_sense_of_life( int[] digits, bool answer )
        {
            var result = false;
            var i = 0;

            while( i < digits.Length )
            {
                if( digits[ i ] == 42 )
                {
                    result = true;
                }

                Print( digits[ i ] );
                i = i + 1;
            }
            Print( result );

            Assert.That( result, Is.EqualTo( answer ) );
        }

        [Test]
        [TestCase( new[] { 1, 3, 2 }, 1 )]
        [TestCase( new[] { 5, 8, 25, 300, 287, 0 }, 3 )]
        [TestCase( new[] { 1, 2, 29, 5, 188, 1488, 42 }, 5 )]
        public void Best_strategy( int[] arr, int pos )
        {
            var r = -1;
            var i = 0;

            while( i < arr.Length )
            {
                Print( arr[ i ] );
                if( r == -1 )
                {
                    r = 0;
                }
                if( arr[ i ] >= arr[ r ] )
                {
                    Print( "Gotcha!" );
                    r = i;
                }

                i = i + 1;
            }

            Print( "----" );
            Print( "{0}->{1}", r, arr[ r ] );
            Assert.That( r, Is.EqualTo( pos ) );
        }

        [Test]
        [TestCase( 1, new[] { 1, 3, 2 }, 0 )]
        [TestCase( 2, new[] { 5, 8, 25, 300, 287, 0 }, 5 )]
        [TestCase( 3, new[] { 1, 2, 29, -188, -1488, 42 }, 4 )]
        public void Worst_strategy( int n, int[] arr, int pos )
        {
            Assert.That( arr.Length, Is.GreaterThan( 0 ) );
            var r = 0; // позиция с самым маленьким из проверенных чисел

            // перебрать все и найти самое маленькое и запомнить его место
            for( var i = 0; i < arr.Length; i++ ) // i - проверяемая позиция
            {
                // сравним значения в позициях i и r
                if( arr[ i ] < arr[ r ] )
                {
                    // если i-ая меньше r-ая то записать i в r
                    r = i;
                }
            }

            Assert.That( r, Is.EqualTo( pos ) );
        }

        [Test]
        [TestCase( new[] { 1, 3, 2 }, 2 )]
        [TestCase( new[] { 1, 0, 10, 1 }, 3 )]
        [TestCase( new[] { 2, 100, -2, 200, 50 }, 70 )]
        public void Calc_average( int[] arr, int ave )
        {
            Assert.That( arr.Length, Is.GreaterThan( 0 ) );

            var r = 0;

            // naiti summu i zapisatj ee v s
            var s = 0;

            // idem po vsem chislam
            for( var i = 0; i < arr.Length; i++ )
            {
                // uvelichivaem summu na tekuchsee chislo
                s += arr[ i ]; // s = s + arr[i]
            }

            // razdelitj summu s na kolichestvo chisel arr.Length
            r = s/arr.Length;

            // zapomnitj resultat deleniya v r

            Assert.That( r, Is.EqualTo( ave ) );
        }

        [Test]
        public void Print_1_10_copy_paste()
        {
            Print( 1 );
            Print( 2 );
            Print( 3 );
            Print( 4 );
            Print( 5 );
            Print( 6 );
            Print( 8 );
            Print( 9 );
            Print( 10 );
        }

        [Test]
        public void Print_1_10_smart_copy_paste()
        {
            var i = 0;
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
            i++;
            Print( i );
        }

        [Test]
        public void Print_1_100_goto()
        {
            var i = 0;

            start:
            i++;
            Print( i );
            if( i >= 100 )
            {
                goto end;
            }
            goto start;
            end:
            ;
        }

        [Test]
        public void Print_1_100_while_true()
        {
            var i = 0;

            while( true ) // m01
            {
                // if(!true) goto m02
                i++; //i=i+1;

                Print( i );

                if( i >= 100 )
                {
                    break; // goto m02
                }
            } // goto m01

            //m02
        }

        [Test]
        public void Print_1_100_while_condition()
        {
            var i = 0;
            while( i < 100 )
            {
                Print( i++ );
            }
        }

        [Test]
        public void Print_1_100_for()
        {
            for( var i = 1; i <= 100; i++ )
            {
                Print( i );
            }
        }

        [Test]
        public void Print_1_100_in()
        {
            var arr = Enumerable.Range( 1, 100 );

            foreach( var i in arr )
            {
                Print( i );
            }
        }

        [Test]
        [TestCase( new[] { 1, 2, 3, 5 }, 1, 5, true )]
        [TestCase( new[] { 0, 1, 2, 3, 5, 7 }, 1, 5, false )]
        [TestCase( new[] { 1, 2, 3, 5, 0 }, 2, 6, false )]
        public void Sequence_in_range( int[] arr, int min, int max, bool answer )
        {
            var res = true;

            for( var i = 0; i < arr.Length; i++ )
            {
                Print( arr[ i ] );

                if( min > arr[ i ] || arr[ i ] > max )
                {
                    res = false;
                    Print( "out" );
                }
            }

            Assert.That( res, Is.EqualTo( answer ) );
        }

        [Test]
        [TestCase( new[] { 7 }, true )]
        [TestCase( new[] { 1, 2, 3, 5 }, true )]
        [TestCase( new[] { 0, 1, 2, 3, 5, 5 }, true )]
        [TestCase( new[] { -1, 0, 2, 3 }, true )]
        [TestCase( new[] { 1, 2, 3, 2 }, false )]
        [TestCase( new[] { 3, 2, 1 }, false )]
        public void Sequence_is_ordered( int[] arr, bool answer )
        {
            var res = true;

            for( var i = 0; i < arr.Length - 1; i++ )
            {
                Print( arr[ i ] );
                if( arr[ i ] > arr[ i + 1 ] )
                {
                    res = false;
                    Print( "out" );
                }
            }
            Print( arr[ arr.Length - 1 ] );

            Assert.That( res, Is.EqualTo( answer ) );
        }

        [Test]
        public void Test_print()
        {
            var a = 1;
            var b = a + 2;

            Print( b );
        }

        [TestCase( new[] { 1, 2, 3 }, new[] { 1, 2, 3 } )]
        [TestCase( new[] { 1, 3, 2, 4 }, new[] { 1, 2, 3, 4 } )]
        public void Bubble_sort( int[] arr, int[] result )
        {
            // печатаем входной массив
            for( var i = 0; i < arr.Length; i++ )
            {
                Print( arr[ i ] );
            }

            // i -- граница, справа от нее порядок, слева включая i -- хаос
            for( var i = arr.Length - 1; i > 0; i-- )
            {
                // тащим направо самый большой элемент до границы
                for( var a = 0; a <= i - 1; a++ )
                {
                    // Поменять местами если не по порядку
                    if( arr[ a ] > arr[ a + 1 ] )
                    {
                        var tmp = arr[ a ];

                        arr[ a ] = arr[ a + 1 ];
                        arr[ a + 1 ] = tmp;
                    }
                }
            }

            Assert.That( arr, Is.EqualTo( result ) );
        }

        [TestCase( new[] { 1, 2, 3 }, new[] { 3, 2, 1 } )]
        [TestCase( new[] { 3, 2, 1 }, new[] { 3, 2, 1 } )]
        [TestCase( new[] { 1, 3, 2, 4 }, new[] { 4, 3, 2, 1 } )]
        [TestCase( new[] { 1, 1, 1, 1 }, new[] { 1, 1, 1, 1 } )]
        [TestCase( new[] { 1, -1, 1, -1 }, new[] { 1, 1, -1, -1 } )]
        [TestCase( new[] { 1/2, 1/4, 1/3, 1/5 }, new[] { 1/2, 1/3, 1/4, 1/5 } )]
        [TestCase( new[] { 2^2, 4^-1, 42, -1488,300 }, new[] { 300, 42, 2^2, 4^-1, -1488  } )] 
        public void Bubble_sort_desc( int[] arr, int[] result )
        {
            // печатаем входной массив
            for( var i = 0; i < arr.Length; i++ )
            {
                Print( arr[ i ] );
            }

            // i -- граница, справа от нее порядок, слева включая i -- хаос
            for( var i = arr.Length - 1; i > 0; i-- )    
            {
                // тащим направо самый маленький элемент до границы
                for( var a = 0; a <= i - 1; a++ )       
                {
                    // Поменять местами если не по порядку
                    if( arr[ a ] < arr[ a + 1 ] )
                    {
                        var tmp = arr[ a ];

                        arr[ a ] = arr[ a + 1 ];
                        arr[ a + 1 ] = tmp;
                    }
                }
            }

            Assert.That( arr, Is.EqualTo( result ) );
        }
    }
}