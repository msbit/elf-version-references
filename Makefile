libexample.so:
	@gcc -shared -o libexample.so -fPIC -Wl,--version-script example.map example.c
main:	libexample.so
	@gcc main.c -lexample -L. -I. -o main
clean:
	@rm -f libexample.so main
run:	main
	@LD_LIBRARY_PATH=. ./main
