IMAGENAME=ffutil

CONTAINERROOT=/
CONTAINERHOME=$(CONTAINERROOT)$(IMAGENAME)/
CONTAINERMOUNT=$(CONTAINERHOME)resources/

DEFAULT_INPUTDIR=~/
DEFAULT_INPUTFILENAME=mando_test.mkv
DEFAULT_OUTPUTFILENAME=mando_test_cut.mkv
DEFAULT_TIMESTAMP=0 60

#===Can be changed like command line arguments==#
INPUTDIR=$(DEFAULT_INPUTDIR)
INPUTFILENAME=$(DEFAULT_INPUTFILENAME)
OUTPUTFILENAME=$(DEFAULT_OUTPUTFILENAME)
TIMESTAMP=$(DEFAULT_TIMESTAMP)
#===============================================#

MOUNTDIR=$(shell realpath $(INPUTDIR))
ENTRYPOINT=./ffutil $(CONTAINERMOUNT)$(INPUTFILENAME) $(TIMESTAMP) $(CONTAINERMOUNT)$(OUTPUTFILENAME)

image:
	docker build -t $(IMAGENAME) -f ./Dockerfile ../
run:
	docker run -v $(MOUNTDIR):$(CONTAINERMOUNT) $(IMAGENAME) $(ENTRYPOINT)
sh:
	docker run -it $(IMAGENAME)
