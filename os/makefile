OBJS := $(patsubst %.c,../file/files/1%,$(wildcard *.c))

allhash.tmp: $(OBJS)
	cat $^ > $@

$(OBJS): ../file/files/1%: %.c
	cp $^ ../crosscompiler/main.c
	cd ../crosscompiler && make
	cp ../crosscompiler/out.min $@

.PHONY: clean
clean:
	rm ../file/files/1*
