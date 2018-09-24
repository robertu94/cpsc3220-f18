.PHONY: all clean
all: build
	make -C build -j8
build:
	mkdir build
	cd build && cmake ..
clean:
	$(RM) -r build
