creat_dynamic_lib: factorial.o fibonacci.o random.o
	gcc *.o --shared -o libmymath.so 
	@make -s clean

%.o : %.c
	gcc -c $< -o $@ -fPIC

creat_static_lib: factorial.o fibonacci.o random.o
	ar -rs libmymath.a *.o
	@make -s clean

%.o : %.c
	gcc -c $< -o $@


clean : 
	@rm *.o
	@echo "All .o is cleaned"
