TAGET:=bin/server_remoteLoginSystem
OBJ:=obj/control.o obj/link.o obj/common.o obj/user.o obj/thread_function.o obj/vector_fd.o
OBJ+=src/server_remoteLoginSystem.c
OBJ+=obj/main_func.o
F:=-Wall -g -pthread
CC:=gcc

$(TAGET):$(OBJ)
	$(CC) -o $@ -I./include $^ $(F)
obj/%.o:src/%.c
	$(CC) -o $@ -I./include -c $^ $(F)

.PHONEY:clean
clean:
	rm -rf $(TAGET)
	rm -rf obj/*.o
	rm -rf *~ *.*~
	rm -rf include/*.*~
	rm -rf src/*.*~
