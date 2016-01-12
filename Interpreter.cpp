#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main( int argc, char *argv[] ){
	vector<string> lines;
	string buff, error;

	// read file via cin
	while (getline(cin, buff)){
		lines.push_back(buff);
	}

	// write file via cout
	if (!error.empty()){
		cout << error << endl;
	}else{
		for(int i=0; i<lines.size(); ++i)
			cout << lines[i] << endl;
	}
}