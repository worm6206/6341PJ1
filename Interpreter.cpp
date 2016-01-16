// Kevin Yen Jan13, 2016
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


// Reads file from cin, and store them in a string named inputLines. 
// "\n" wont matter.
// possible bug: if the input exceeds the capacity of a string
void readFile(string& inputLines){
	string buff;
	while (getline(cin, buff)){
		inputLines+=buff;
	}
}

// "index" is the starting position to get token
// "inputLines" is the string this function is reading
// "error" is for error message. Stays empty unless error occurs.
//  "atoms" is a string vector storing all literal atoms.
//  "sum" is for summing up all numeric atoms.
string getNextToken(int& index, string inputLines, string& error, vector<string>& atoms, int& sum){ 
	// current position "index" is same as the ending of input string. Either string is empty or reached the end of  string.
	if((inputLines.length())==(unsigned)index){
		return "EOF";
	}
	// 32 is space. Simply move index forward by index++
	if (inputLines[index]==32){
		return getNextToken(++index, inputLines, error, atoms, sum);
	}
	// 40 is "("
	else if(inputLines[index]==40){
		index++;
		return "OpenParenthesis";
	}
	// 41 is ")"
	else if(inputLines[index]==41){
		index++;
		return "ClosingParenthesis";
	}
	// occurs if the first character is capital ASCII
	else if((inputLines[index]>=65) && (inputLines[index]<=90)){
		string word = string(1,inputLines[index]);
		int temp = index;
		// if the next character is number or capital letter, assemble them into a string "word"
		// if not, store what we've obtained so far and push "word" into "atoms" the vector
		while( ((inputLines[++temp])>=65 && (inputLines[temp])<=90) || ((inputLines[temp])>=48 && (inputLines[temp])<=57) )
			word+=inputLines[temp];
		index=temp;
		atoms.push_back(word);
		return "LiteralAtom";
	}
	// occurs if the starting character is a number letter
	else if((inputLines[index]>=48) && (inputLines[index]<=57)){
		string number = string(1,inputLines[index]);
		bool valid = true;
		int temp = index;
		// doesn't care if the next character is letter or number, just assemble them as a string
		while(((inputLines[++temp])>=65 && (inputLines[temp])<=90) || ((inputLines[temp])>=48 && (inputLines[temp])<=57) )
			number+=inputLines[temp];
		index = temp;
		// if the string contains letter in it, it's invalid and therefore become an error
		for(unsigned int i =0;i<number.length();i++){
			if (number[i] >=65 && number[i] <=90)
				valid = false;
			if(!valid) break;
		}
		if(!valid){
			error = "Invalid token " + number;
			return "ERROR";
		}
		// otherwise, sum it up
		sum+=stoi(number);
		return "NumericAtom";
	}
	// (OPTIONAL, not in requirement) 
	// if there are anything other character rather than capital letters, number letters, space, and parenthesis, it's an error
	else{
		stringstream convert;
		convert << index+1;
		error="unrecognized character \"" + string(1,inputLines[index]) + "\" at " + convert.str() +" inputlength=" + to_string(inputLines.length()) + " index=" + to_string(index) ;
		return "ERROR";
	}
}

int main( int argc, char *argv[] ){

/*VARIABLES*/
	string error, token, inputLines, outputLines;
	vector<string> atoms;
	int  literalAtom=0, numericAtom=0, openPar=0, closingPar=0, sum=0, index=0;

/*READCIN*/
	//read file via cin and store into string called inputLines
	readFile(inputLines);

/*TOKEN*/
	// if the returning string is not "EOF" or "ERROR", it's considered valid token.
	while( token = getNextToken(index, inputLines, error, atoms, sum), token!= "EOF" && token!= "ERROR" ){
		if(token == "OpenParenthesis")
			openPar++;
		else if(token == "ClosingParenthesis")
			closingPar++;
		else if(token == "LiteralAtom")
			literalAtom++;
		else if (token == "NumericAtom")
			numericAtom++;
		else{
			// for debugging. would never happen but i wanted to keep it
			error = "uncaught token " + token;
			break;
		}
	}

/*WRITECOUT*/
	// if the string "error" is not empty, then some error must have happened.
	// only print the error not the result
	if (!error.empty()){
		cout << "ERROR: " << error << endl;
	}
	// if error is empty, then print the results
	else{
		cout << "LITERAL ATOMS: ";
		if(literalAtom==0)
			cout << "0" << endl;
		else {
			cout << literalAtom << ", ";
			for (unsigned int i =0; i<=atoms.size()-1; ++i)
			{
				cout << atoms[i];
				if((i+1)!=atoms.size()) 
					cout << ", ";
				else
					cout << endl;
			}
		}
		cout << "NUMERIC ATOMS: ";
		if(numericAtom==0)
			cout << "0" << endl;
		else
			cout << numericAtom << ", " << sum << endl;
		cout << "OPEN PARENTHESES: " << openPar << endl;
		cout  << "CLOSING PARENTHESES: " << closingPar << endl;
		// not sure about printing the last endl, since generates one empty line in file output file
		// but in terminal we need it else the format would be weird.
	}
}