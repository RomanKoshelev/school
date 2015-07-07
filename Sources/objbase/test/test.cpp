#include <time.h>
#include <stdio.h>

int main ()
{
   time_t time_0 = time (NULL);
   tm LcTime;  memcpy (&LcTime, localtime (&time_0), sizeof (tm));
   tm GmTime;  memcpy (&GmTime, gmtime    (&time_0), sizeof (tm));
   int res = mktime(&LcTime) - mktime(&GmTime);
   printf ("\n%d\n", res);
}