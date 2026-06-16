all:
	g++ ./opendisk.cpp -o opendisk
install:
	sudo cp ./opendisk /usr/local/bin/
remove:
	sudo rm -f /usr/local/bin/opendisk
clean:
	rm -f ./opendisk
