TARGET=hack_fix_reuseaddr

TEST_PORT=1234

$(TARGET): $(TARGET).c
	$(CC) -shared -ldl -D_GNU_SOURCE -o $(TARGET).so -fPIC $(TARGET).c

test: $(TARGET)
	LD_PRELOAD=$$PWD/$(TARGET).so socat tcp4-listen:$(TEST_PORT) exec:/bin/true&
	socat tcp:127.0.0.1:$(TEST_PORT) -

clean:
	rm -f $(TARGET).so *.o

