dirtest: main.c
	gcc main.c -o dirtest

run: dirtest
	./dirtest

clean:
	rm dirtest