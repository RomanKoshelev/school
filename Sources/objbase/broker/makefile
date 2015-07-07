OBJS = tmp/stop.o

#cc = eg++
cc = g++295

bin/stop:	$(OBJS)
			$(cc) $(OBJS) -o bin/stop
#	$(CC) $(CFLAGS) -o $(.TARGET) $(.ALLSRC)
#	$(CC) -O2 -o $(.TARGET) $(.ALLSRC)
$(OBJS):	stop.cpp ../bcc/CGI_sock.h
			$(cc) -c stop.cpp -o tmp/stop.o
#cfbased.o   : cfbased.cpp
#	$(CC) -O2 -c $(.PREFIX).cpp
#	gcc -O2 -c cfbased.cpp