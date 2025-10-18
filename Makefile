CC = gcc
CFLAGS = -Wall -g
SRCS = test.c utility.c mat.c
OUT = mat

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

clean:
	rm -f $(OUT)
