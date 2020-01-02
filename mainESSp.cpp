#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

class Turn {

	public:
		string name;
		int time;
		vector <string> restriccion;

		void set_values (string,int, vector <string>);
		string get_name() {return name;}
		int get_time() {return time;}
		vector <string> get_restriccions() {return restriccion;}

};

void Turn::set_values(string n, int t , vector <string> l ){
	name = n;
	time = t;
	restriccion = l;
}

class List_Turns {
	vector <Turn> list_of_turns;
	vector <string> turns_names;
	public:
		void append_turn(string name, int time, vector<string> restriccions) {
			Turn new_turn;
			new_turn.set_values(name, time, restriccions); 	
			list_of_turns.push_back(new_turn);
			turns_names.push_back(name);
		}

		vector <string> get_restriccions (string name){
			vector <string> rest;

			for (auto i = list_of_turns.begin(); i != list_of_turns.end(); ++i){
				if((*i).get_name() == name){
					return  (*i).get_restriccions();
				}
			}

			return rest;
		}

		int get_duration (string name) {
			for (auto j = list_of_turns.begin(); j != list_of_turns.end(); ++j){
				if((*j).get_name() == name){
					return (*j).get_time();
				}
			}	

		}

		vector <string> get_turns_names() {
			return turns_names;
		} 

};

vector <string> split(string line){
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));	
	return tokens;	
};
 
int main () {

	string str;
	/* nombre de archivo por defecto */
	string file_name = "caso1.txt"; 
	/* casos de prueba deben estar en la carpeta "Casos" */
	std::ifstream file("Casos//"+file_name);

	if(file.fail()){
		cout << "caso de prueba no encontrado\n";
	
	} else {

		/* lista con el archivo */
		list<string> list_aux;

		while (std::getline(file,str))
		{
			if(!std::regex_match (str, std::regex("(^#[\\s\\S]*)")) && str != "") {
				list_aux.push_back(str);
			}

		}

		file.close();

		/* Parseo de datos sobre la lista auxiliar*/

		string HORIZON = "SECTION_HORIZON";
		string SHIFTS = "SECTION_SHIFTS";
		string STAFF = "SECTION_STAFF";
		string DAY_OFF = "SECTION_DAY_OFF";
		string SHIFT_ON_REQUESTS = "SECTION_SHIFT_ON_REQUESTS";
		string SHIFT_OFF_REQUESTS = "SECTION_SHIFT_OFF_REQUESTS";
		string COVER = "SECTION_COVER";

		int Horizon;
		List_Turns turn_shifts;
		list<string> Staff_list;
		list<string> Days_off_list;
		list<string> Shift_on_request_list;
		list<string> Shift_off_request_list;
		list<string> Cover_list;

		std::set<std::string> set_labels = {HORIZON, SHIFTS, STAFF, DAY_OFF, SHIFT_ON_REQUESTS, SHIFT_OFF_REQUESTS, COVER};
		list<string>::iterator line;
		string label;
		std::set<std::string>::iterator in_set_labels;

		for(line = list_aux.begin(); line != list_aux.end(); line++)
		{

			in_set_labels = set_labels.find(*line);

			if(in_set_labels != set_labels.end()){
				label = *line;
			}
			
			else{

				if(label == HORIZON){
					Horizon = stoi(*line);
				}

				else if(label == SHIFTS){
					std::regex comas ("\\s*,\\s*");
					//std::cout << std::regex_replace (*line,e," ") << "\n";
					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> split_line = split(parse_line);

					if (split_line.size() == 3){
						std::regex separadores ("\\|");
						string parce_rest = std::regex_replace (split_line[2],separadores," ");
						turn_shifts.append_turn(split_line[0], stoi(split_line[1]), split(parce_rest));
					}
					else if (split_line.size() == 2){
						vector <string> rest;
						turn_shifts.append_turn(split_line[0], stoi(split_line[1]), rest);
					}
					else {
						cout << "error of format: " << SHIFTS << "\n";
					}

				}

				else if(label == STAFF){
					
				}

				else if(label == DAY_OFF){
					
				}

				else if(label == SHIFT_ON_REQUESTS){
					
				}

				else if(label == SHIFT_OFF_REQUESTS){
					
				}

				else if(label == SHIFT_OFF_REQUESTS){
					
				}

				else if(label == COVER){
					
				}

				else{
					cout << "Fail in the format case\n";
					cout << *line << "\n";
				} 

			}

		}	

		cout << "horizon: " << Horizon << "\n";
		vector <string> w = turn_shifts.get_restriccions("E");
		for (auto i = w.begin() ; i != w.end(); ++i){
			cout << *i << "\n";
		}

		
		

	}

    return 0;
}