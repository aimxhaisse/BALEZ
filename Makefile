VST 	:= BALEZverb

include dpf/Makefile.base.mk

all: 	$(VST)

deps:
	$(MAKE) -C dpf/dgl

$(VST):	deps
	$(MAKE) -C plugins/$@
