LDFLAGS += -lhighgui

targets = e2.1 e2.2 e2.3 e2.4

.PHONY: clean

all: $(targets)

e2.1: example_2.1
	mv $< $@

e2.2: example_2.2
	mv $< $@

e2.3: example_2.3
	mv $< $@

e2.4: example_2.4
	mv $< $@

clean:
	@$(RM) *.o
	@$(RM) $(targets)
