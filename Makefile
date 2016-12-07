tsp: main.o cities.o tour.o population.o genetic_algorithm.o
	g++ main.o cities.o tour.o population.o genetic_algorithm.o -std=c++11 -g -fopenmp

main.o: main.cpp
	g++ -c main.cpp -std=c++11 -g -fopenmp

cities.o: cities.cpp
	g++ -c cities.cpp -std=c++11 -g

tour.o: tour.cpp
	g++ -c tour.cpp -std=c++11 -g -fopenmp

population.o: population.cpp
	g++ -c population.cpp -std=c++11 -g

genetic_algorithm.o: genetic_algorithm.cpp
	g++ -c genetic_algorithm.cpp -std=c++11 -g -fopenmp

clean:
	rm -f *.o a.out
