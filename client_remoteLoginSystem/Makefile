TAGET:=bin/client_remoteLoginSystem
OBJ:=obj/view.o obj/control.o obj/common.o obj/mainFile_func.o 
OBJ+=src/client_remoteLoginSystem.c
OBJ+=obj/thrd_func.o
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
