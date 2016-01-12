rm -f outputfile
g++ Interpreter.cpp -o Interpreter
./Interpreter < inputfile > outputfile
cat outputfile
