libexample.so:
	@gcc -shared -o libexample.so -fPIC -Wl,--version-script example.map example.c
main:	libexample.so
	@gcc main.c -lexample -L. -I. -o main -Wl,-rpath='$$ORIGIN/'
clean:
	@rm -f libexample.so main
run:	main
	@./main
