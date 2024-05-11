hards= ipc.h
opts= -g -c
s_src = smoker.c ipc.c
s_obj = smoker.o ipc.o
p_src = supplier.c ipc.c
p_obj = supplier.o ipc.o

all: smoker supplier

smoker: $(s_obj)
	gcc $(s_obj) -o smoker
smoker.o: $(s_src) $(hdrs)
	gcc $(opts) $(s_src)

supplier: $(p_obj)
	gcc $(p_obj) -o supplier
supplier.o: $(p_src) $(hdrs)
	gcc $(opts) $(p_src)

clean:
	rm smoker supplier *.o
