SHIFT_PORT=60000

TARGET=hack_shift_sys_ports

TEST_SYS_PORT=999

$(TARGET): $(TARGET).c
	$(CC) -shared -ldl -D_GNU_SOURCE -o $(TARGET).so -fPIC $(TARGET).c -DSHIFT_PORT=$(SHIFT_PORT) -DDEBUG

test: $(TARGET)
	LD_PRELOAD=$$PWD/$(TARGET).so socat tcp4-listen:$(TEST_SYS_PORT) exec:/bin/true&
	socat tcp:127.0.0.1:$$(($(SHIFT_PORT) + $(TEST_SYS_PORT))) -

clean:
	rm -f $(TARGET).so *.o

