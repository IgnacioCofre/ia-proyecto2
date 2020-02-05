all:
	g++ -Wall mainESSp.cpp -o main
	./main
clean:
	rm -rf *o main
	rm -rf output.txt
	
