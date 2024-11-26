# Makefile

# Question 1
question1: main.cpp
	g++ -c main.cpp
	g++ -g -o debug1 main.o
	g++ -O3 -o optimize1 main.o

# Question 2
question2: publication.cpp
	g++ -c publication.cpp
	g++ -g -o debug1 publication.o
	g++ -O3 -o optimize1 publication.o

# Question 3
question3: parser.cpp
	g++ -c parser.cpp
	g++ -g -o debug1 parser.o
	g++ -O3 -o optimize1 parser.o

# Question 4
question4: author.cpp
	g++ -c author.cpp
	g++ -g -o debug1 author.o
	g++ -O3 -o optimize1 author.o

