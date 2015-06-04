// School (c) 2015 Krokodev
// School.Lybrary
// Statistics.cs

namespace School.Lybrary.Utils
{
    public class Statistics {

        public Statistics( int size )
        {
            _size = size;
        }

        public void Swap()
        {
            _swaps++;
        }

        public void Compare()
        {
            _comparisons++;
        }

        public override string ToString()
        {
            var str = "";
            str += string.Format( "Size: {0}", _size );
            str += "\n";
            str += string.Format( "Comparisons: {0}", _comparisons );
            str += "\n";
            str += string.Format( "Swaps: {0}", _swaps );
            return str;
        }

        private int _comparisons;
        private int _swaps;
        private int _size;
    }
}