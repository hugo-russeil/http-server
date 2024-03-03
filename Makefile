CC = gcc
CFLAGS = -Iinclude
DEPS = include/httpRequest.h include/httpResponse.h include/fileHandler.h include/requestHandler.h
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, httpRequest.o httpResponse.o fileHandler.o requestHandler.o main.o)

$(OBJDIR)/%.o: src/%.c $(DEPS)
	mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm $(OBJ)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*
	rmdir $(OBJDIR)