encoder.out : BinaryHeap.o decoder.o encoder.o encoderRunner.o  
	g++ -ansi -Wall -o encoder.out BinaryHeap.o decoder.o encoder.o encoderRunner.o  

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h 
	g++ -ansi -Wall -c BinaryHeap.cpp

decoder.o : decoder.cpp decoder.h 
	g++ -ansi -Wall -c decoder.cpp

encoder.o : encoder.cpp encoder.h 
	g++ -ansi -Wall -c encoder.cpp

encoderRunner.o : encoderRunner.cpp CPUTimer.h encoder.h decoder.h 
	g++ -ansi -Wall -c encoderRunner.cpp

clean : 
	rm -f encoder.out BinaryHeap.o  decoder.o  encoder.o  encoderRunner.o   
