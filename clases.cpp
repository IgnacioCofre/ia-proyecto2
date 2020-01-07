class Turn {

	public:
		string name;
		int time;
		// restricciones para el dia siguiente
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
int Model(List_Turns list_turns, List_Staff list_staff,  map <string, vector <string>> horario, int horizon){

	int count_first_restriction = 0 ;
	
	vector <string> staff_names = list_staff.get_staff_names();
	cout << "Lista de restricciones no cumplidas encontradas:\n";


	for(auto trabajador = staff_names.begin(); trabajador != staff_names.end(); ++trabajador){
		// restricciones que involucran solo a un empleado a la vez

		vector <string> trabajdor_horario = horario[*trabajador];
		// cout << "trabajador: " << *trabajador << "\n";

		for(int dia = 0 ; dia < (horizon-1); ++dia){

			// primera restriccion

			string actual_day = trabajdor_horario[dia % horizon];
			string next_day =trabajdor_horario[dia+1];
			
			// cout << "turno dia_1 :" << actual_day << "\n";
			// cout << "turno dia_2 :" << next_day << "\n"; 
			// revisa si no se cumple la restriccion de los turnos seguidos
			
			if(list_turns.verify_restriction(actual_day, next_day) == 1){
				cout << "Restriccion se turnos seguidos no se cumple: " << "\n";
				cout << "trabajador: " << *trabajador << "\n";
				cout << "turno dia_1 :" << actual_day << "\n";
				cout << "turno dia_2 :" << next_day << "\n"; 
				count_first_restriction += 1;
			}

			// segunda restriccion

		}
		
	}

	cout << "fin de ejecucion del modelo\n";

	return 0;
}