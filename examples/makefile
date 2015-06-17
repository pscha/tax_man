all:
	gcc cherry_count.c -o cherry_count -lpthread
	gcc cherry_count.c -O2 -o cherry_count-O2 -lpthread
	gcc cherry_count.c -O2 -S -o cherry_count.s
	gcc cherry_count_mutex.c -o cherry_count_mutex -lpthread
	gcc cherry_count_mutex.c -S -o cherry_count_mutex.s
	gcc cherry_count_semaphore.c -o cherry_count_semaphore -lpthread
	gcc threadadd.c -o threadadd -lpthread

clean:
	rm -f cherry_count cherry_count_mutex cherry_count-O2 cherry_count_semaphore threadadd cherry_count.s cherry_count_mutex.s
