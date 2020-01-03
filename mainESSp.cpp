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

class Staff {
	string name;
	std::map<string , int> MaxT;
	int MaxM;
	int MinM;
	int MaxCT;
	int MinCT;
	int MinCDL;
	int MaxFD;

	vector <int> days_off;

	std::map<string , int> shift_on_request;
	std::map<string , int> shift_off_request;

	public:
		void set_values (string, std::map<string , int>, int,int,  int,int,int, int);
		string get_name(){return name;}
		
		int get_MaxT(string name){
			if(MaxT.find(name) != MaxT.end()){
				return MaxT[name];
			}
			else{
				return 0;
			}
		}
		int get_MaxM(){
			return MaxM;
		}
		int get_MinM(){
			return MinM;
		}
		int get_MaxCT(){
			return MaxCT;
		}
		int get_MinCT(){
			return MinCT;
		}
		int get_MinCDL(){
			return MinCDL;
		}
		int get_MaxFD(){
			return MaxFD;
		}

		void set_days_off(vector <int> list_days_off){
			days_off = list_days_off;
		}

		void set_shift_on_request(string day_turn, int peso){
			shift_on_request.insert(pair <string,int> (day_turn,peso));
		}

		void set_shift_off_request(string day_turn, int peso){
			shift_off_request.insert(pair <string,int> (day_turn,peso));
		}

};

void Staff::set_values(string n, std::map<string, int> dict,int maxm, int minm, int maxct, int minct, int mincdl, int maxfd){
	name = n;
	MaxT = dict;
	MaxM = maxm;
	MinM = minm;
	MaxCT = maxct;
	MinCT = minct;
	MinCDL = mincdl;
	MaxFD = maxfd;
}

class List_Staff {
	vector <string> staff_names ;
	vector <Staff> list_of_staff;
	public:
	void append_staff(string name, std::map<string, int> dict, int maxm, int minm, int maxct, int minct, int mincdl, int maxfd) {
			Staff new_staff;
			new_staff.set_values(name, dict,maxm,  minm,  maxct,  minct,  mincdl,  maxfd); 	
			list_of_staff.push_back(new_staff);
			staff_names.push_back(name);
		}
	vector <string> get_staff_names(){
		return staff_names;
	}	
	/*funciones get sobre staff*/

	int set_days_off(string name_staff, vector <int> list_days_off){
		for(auto iter = list_of_staff.begin(); iter!= list_of_staff.end(); ++iter){
			if((*iter).get_name() == name_staff){
				(*iter).set_days_off(list_days_off);
				return 1;
			}
		}

		return 0;
	}

	int set_shift_on_request(string name_staff, string day_turn, int peso){
		for(auto iter = list_of_staff.begin(); iter!= list_of_staff.end(); ++iter){
			if((*iter).get_name() == name_staff){
				(*iter).set_shift_on_request(day_turn, peso);
				return 1;
			}
		}

		return 0;
	}

	int set_shift_off_request(string name_staff, string day_turn, int peso){
		for(auto iter = list_of_staff.begin(); iter!= list_of_staff.end(); ++iter){
			if((*iter).get_name() == name_staff){
				(*iter).set_shift_off_request(day_turn, peso);
				return 1;
			}
		}

		return 0;
	}

};

class Cover{
	vector <std::map<string , vector <int>>> list_of_covers;
	public:
		void set_values(int horizon){
			for(auto i = 0; i!= horizon; ++i){
				map <string , vector <int>> dict;
				list_of_covers.push_back(dict);
			}
		}
		void add_values(int dia, string turno, vector <int> datos){
			
			list_of_covers[dia].insert(pair <string , vector <int>> (turno, datos));
			
		}

		vector <int> get_section_cover(int dia, string turn){
			return list_of_covers[dia][turn];
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
		List_Staff staff_list;
		Cover cover_list;

		std::set<std::string> set_labels = {HORIZON, SHIFTS, STAFF, DAY_OFF, SHIFT_ON_REQUESTS, SHIFT_OFF_REQUESTS, COVER};
		list<string>::iterator line;
		string label;
		std::set<std::string>::iterator in_set_labels;

		std::regex comas ("\\s*,\\s*");
		std::regex spaces ("\\s");
		std::regex separadores ("\\|");
		std::regex equal ("=");

		for(line = list_aux.begin(); line != list_aux.end(); line++)
		{

			in_set_labels = set_labels.find(*line);

			if(in_set_labels != set_labels.end()){
				label = *line;
			}
			
			else{

				if(label == HORIZON){
					Horizon = stoi(*line);
					cover_list.set_values(Horizon);

				}

				else if(label == SHIFTS){
					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> split_line = split(parse_line);

					if (split_line.size() == 3){
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

					string parse_line = std::regex_replace (*line,spaces,"");
					parse_line = std::regex_replace (parse_line,comas," ");
					vector <string> split_line = split(parse_line);

					// parseo de restricciones de MaxT
					map <string, int > MaxT;
					string aux_line = std::regex_replace (split_line[1],separadores," "); 	
					vector <string> split_aux = split(aux_line);


					for (auto i = split_aux.begin();i!=split_aux.end();++i){
						string aux_equal = std::regex_replace (*i,equal," ");
						vector <string> aux_MatT = split(aux_equal);
						MaxT.insert(pair <string, int> (aux_MatT[0], stoi(aux_MatT[1]))); 
					}

					staff_list.append_staff(split_line[0], MaxT, stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]), stoi(split_line[5]), stoi(split_line[6]), stoi(split_line[7]));

				}

				else if(label == DAY_OFF){
					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> split_line = split(parse_line);

					// split_line [0] = name_staff
					// split_line [1] = list_days_off

					vector <int> list_days_off;

					if(split_line.size() == 2){
						string aux_line = std::regex_replace (split_line[1],separadores," ");		
						vector <string> aux_vector = split(aux_line);

						for(auto iter = aux_vector.begin(); iter != aux_vector.end(); ++iter){
						list_days_off.push_back(stoi(*iter));	
						}
					} 

					staff_list.set_days_off(split_line[0], list_days_off);

				}

				else if(label == SHIFT_ON_REQUESTS){
					
					// split_line [0] = name_staff
					// aux_line[1]+","+aux_line[2] = dict index
					// stoi(aux_line[3]) = peso;

					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> aux_line = split(parse_line);
					staff_list.set_shift_on_request(aux_line[0], aux_line[1]+","+aux_line[2], stoi(aux_line[3]));
				}

				else if(label == SHIFT_OFF_REQUESTS){

					// split_line [0] = name_staff
					// aux_line[1]+","+aux_line[2] = dict index
					// stoi(aux_line[3]) = peso;

					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> aux_line = split(parse_line);
					staff_list.set_shift_off_request(aux_line[0], aux_line[1]+","+aux_line[2], stoi(aux_line[3]));
				}

				else if(label == COVER){
					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> aux_line = split(parse_line);
					vector <int> datos;
					datos.push_back(stoi(aux_line[2])); //Empleado
					datos.push_back(stoi(aux_line[3])); //Peso
					datos.push_back(stoi(aux_line[4])); //Unknow

					cover_list.add_values(stoi(aux_line[0]), aux_line[1], datos);
				}

				else{
					cout << "Fail in the format case\n";
					cout << *line << "\n";
				} 

			}

		}	

		vector <int> cover_inf = cover_list.get_section_cover(2,"L");
		for(auto i = cover_inf.begin(); i!= cover_inf.end(); ++i){
			cout << *i << "\n";
		}

		// cout << "horizon: " << Horizon << "\n";
		

	}

    return 0;
}