default: sum par_sum

sum: sum.c
	gcc -g -O2 --std=c99 -Wall -o sum sum.c

par_sum: par_sum.c
	gcc -g -O2 --std=c99 -Wall -o par_sum par_sum.c -lpthread ./utils/queue.c

exec-sum: sum
	./sum ./examples/medium.txt

exec-par-sum: par_sum
	./par_sum -t 1 -f ./examples/simple.txt

clean:
	rm -f sum par_sum