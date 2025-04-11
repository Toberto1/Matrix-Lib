CC = gcc
CFLAGS = -Wall -g
SRCS = test.c utility.c myAO.c
OUT = myAO

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

clean:
	rm -f $(OUT)
