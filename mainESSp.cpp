#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;
 
int main () {

	//char data[1000];
	std:string str;
	string file_name = "caso1.txt"; 
	std::ifstream file("Casos//"+file_name);

	if(file.fail()){
		cout << "caso no encontrado\n";
	
	} else {
		list<string> list1;

		while (std::getline(file,str))
		{
			list1.push_back(str);
			//cout << str;
			//cout << "\n";
		}

		list<string>::iterator line;
		for(line = list1.begin(); line !=list1.end(); line++)
		{
			cout<< *line <<" ";
		}

		file.close();
	}



    return 0;
}