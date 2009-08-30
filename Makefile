LDFLAGS += -lhighgui

targets = e2.1

.PHONY: clean

all: $(targets)

e2.1: example_2.1
	mv $< $@

clean:
	@$(RM) *.o
	@$(RM) $(targets)
