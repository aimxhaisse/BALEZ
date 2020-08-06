VST 	:= BALEZverb

include dpf/Makefile.base.mk

all: 	$(VST)

install:
	-$(CURDIR)/dpf/utils/generate-vst-bundles.sh
	sudo cp -r bin/BALEZverb.vst /Library/Audio/Plug-Ins/VST/

deps:
	$(MAKE) -C dpf/dgl

$(VST):	deps
	$(MAKE) -C plugins/$@
