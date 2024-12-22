OBJS := $(patsubst %.c,../file/files/1%,$(wildcard *.c))

$(OBJS): ../file/files/1%: %.c
	cp $^ ../crosscompiler/main.c
	cd ../crosscompiler && make
	cp ../crosscompiler/out.min $@
