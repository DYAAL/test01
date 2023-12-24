CC := g++
CFLAGS 	:= -g
PTHREAD  := -lpthread
FILENAME_1 	:= cpp
FILENAME_2 	:= c
FILENAME_3 	:= hpp


TARGET 	:= mainProject.out
SOURCE1 	:= $(wildcard *.$(FILENAME_1) ../s1/*.$(FILENAME_1) ../s2/*.$(FILENAME_1))
SOURCE2 	:= $(wildcard *.$(FILENAME_2) ../s1/*.$(FILENAME_2) ../s2/*.$(FILENAME_2))
SOURCE3 	:= $(wildcard *.$(FILENAME_3) ../s1/*.$(FILENAME_3) ../s2/*.$(FILENAME_3))
OBJS1 	:= $(patsubst %.$(FILENAME_1),%.o,$(SOURCE1))
OBJS2 	:= $(patsubst %.$(FILENAME_2),%.o,$(SOURCE2))


$(TARGET) : $(OBJS1) $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS1) $(OBJS2) -o $(TARGET) $(PTHREAD) 

%.o : %.$(FILENAME_1)
	$(CC) $(CFLAGS) -c $< -o $@ 
%.o : %.$(FILENAME_2)
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : clean
clean : 
	rm -rf $(TARGET) *.o ../s1/*.o ../s2/*.o

.PHONY : clean_middle
clean_middle : 
	rm -rf *.o ../s1/*.o ../s2/*.o
	
.PHONY : format
format : 
	clang-format -style=google -i $(SOURCE1) $(SOURCE2) $(SOURCE2)
	