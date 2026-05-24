
all: dummy

dummy: dummy.cpp
	clang++ -Ofast -o dummy dummy.cpp

clean:
	rm -f dummy
