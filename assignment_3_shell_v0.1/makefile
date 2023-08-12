lib_dir=./mymathlibs

dy: main.o command_handler.o
	gcc *.o -o myexe -lmymath -L $(lib_dir)
	@echo "-----> myexe is in -Dynamic- linking <-----"
	@make -s clean

st: main.o command_handler.o
	gcc *.o -o myexe --static -lmymath -L $(lib_dir)
	@echo "-----> myexe is in -Static- linking <-----"
	@make -s clean

%.o: %.c
	gcc -c $< -o $@ -I $(lib_dir)

create_dynamic_lib:
	$(MAKE) -s -C $(lib_dir)

create_static_lib:
	$(MAKE) -s -C $(lib_dir) creat_static_lib
	
clean:
	rm *.o
	
remove:
	rm myexe
