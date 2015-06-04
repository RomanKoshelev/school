// School (c) 2015 Krokodev
// School.Lybrary
// Statistics.cs

namespace School.Lybrary.Utils
{
    public class Statistics {

        private int _comparisons;
        private int _swaps;

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
            str += string.Format( "comparisons: {0}", _comparisons );
            str += "\n";
            str += string.Format( "swaps: {0}", _swaps );
            return str;
        }
    }
}