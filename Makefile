executables = main main_base main_11 main_12 main_20

libexample.so:
	@ gcc -shared -o libexample.so -fPIC -Wl,--version-script example.map example.c

clean:
	@ rm -f libexample.so $(executables)

run:	$(executables)
	@ ./main
	@ ./main_base
	@ ./main_11
	@ ./main_12
	@ ./main_20

$(executables):	libexample.so
	@ gcc $@.c -lexample -L. -I. -o $@ -Wl,-rpath='$$ORIGIN/'
