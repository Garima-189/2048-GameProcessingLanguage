assignment : parser.ypp game.cpp scanner.l
		bison -d parser.ypp
		flex -o scanner.lex.cpp scanner.l
		g++ -Wall -o scanner scanner.lex.cpp parser.tab.cpp game.cpp -lfl -lm

clean : 
	rm -rf assignment