CC=gcc

CURRENTDIR=./
DOCKERDIR=docker/

IMAGENAME=ffutil
DOCKERFILENAME=Dockerfile

CONTAINERROOT=/
CONTAINERHOME=$(CONTAINERROOT)$(IMAGENAME)/

#SHELLCONTAINERID=$(shell sudo docker ps -a | grep $(IMAGENAME) -m 1 | awk '{ print $$1 }')

image:
	sudo docker build -t $(IMAGENAME) -f $(CURRENTDIR)$(DOCKERDIR)$(DOCKERFILENAME) $(CURRENTDIR)
run:
	sudo docker create $(IMAGENAME) ./ffutil $(notdir $(IN)) $(TIMESTAMP) $(OUT)
	export CONTAINER_ID=$$(sudo docker ps -a | grep $(IMAGENAME) -m 1 | awk '{ print $$1 }') && \
	sudo docker cp $(IN) $$CONTAINER_ID:$(CONTAINERHOME) && \
	sudo docker start -ai $$CONTAINER_ID && \
	sudo docker cp $$CONTAINER_ID:$(CONTAINERHOME)$(OUT) $(CURRENTDIR)
sh:
	sudo docker run -it $(IMAGENAME)
