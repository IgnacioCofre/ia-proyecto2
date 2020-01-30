#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

class List_Turns {
	vector <string> turns_names;
	map <string, vector <string>> turns_restriccions;
	map <string, int> duration_turn;

	public:

		void append_turn_restriccions(string turn_name, vector <string> restriccion){
			turns_names.push_back(turn_name);
			turns_restriccions.insert(pair <string, vector <string>> (turn_name, restriccion));
		}

		void append_duration_turn(string name_turn, int duration){
			duration_turn.insert(pair <string, int> (name_turn, duration));
		}

		int get_duration_turn(string name_turn){
			// caso de los dias no trabajados
			if(name_turn == "-"){
				return 0;
			} 

			return duration_turn[name_turn];
		}

		/* 
			funcion veryfi_restriccion(string, string)
			verfica que si se cumple la restriccion de los turnos respecto al turno del dia siguiente 
			return int:
				0 : restriccion se cumple
				1 : no se cumple
		
		*/

		int verify_restriction(string turn_name, string next_turn){
			vector <string>  restriccion = turns_restriccions[turn_name];
			// no verifica si alguno de los dias es libre
			if (turn_name != "-" && next_turn != "-"){
				for (auto iter = restriccion.begin(); iter != restriccion.end(); ++ iter ){
					if (next_turn == *iter){
						return 1; 
					}
				}
			}
			
			return 0;		

			
		}

		vector <string> get_turns_names() {
			return turns_names;
		} 

};

class List_Staff {
	vector <string> staff_names ;
	map <string, int> staff_index;
	//MaxT[int [trabajador][string turno] = int cantidad
	vector <map<string , int>> MaxT;
	//[maxm, minm, maxct, minct, mincdl, maxfd]
	vector <vector <int>> staff_data;
	// days_off [int trbajadador] = vector int [days_off]
	vector <vector <int>> days_off;
	 
	// shift on request
	vector <int> shift_on_request_empleado;
	vector <int> shift_on_request_dia;
	vector <string> shift_on_request_turno;
	vector <int> shift_on_request_peso;

	// shift off request
	vector <int> shift_off_request_empleado;
	vector <int> shift_off_request_dia;
	vector <string> shift_off_request_turno;
	vector <int> shift_off_request_peso;

	public:

		void set_shift_on_request(string name_staff, int day, string turn, int peso){
			shift_on_request_empleado.push_back(staff_index[name_staff]);
			shift_on_request_dia.push_back(day);
			shift_on_request_turno.push_back(turn);
			shift_on_request_peso.push_back(peso);
		}

		void set_shift_off_request(string name_staff, int day, string turn, int peso){
			shift_off_request_empleado.push_back(staff_index[name_staff]);
			shift_off_request_dia.push_back(day);
			shift_off_request_turno.push_back(turn);
			shift_off_request_peso.push_back(peso);
		}

		void set_days_off(int horizon,  vector <int> list_days_off){
			days_off.push_back(list_days_off);
		}

		void set_MaxT(map <string, int> dict){
			MaxT.push_back(dict);
		}

		void set_staff_data(string name, int maxm, int minm, int maxct, int minct, int mincdl, int maxfd){
			staff_names.push_back(name);
			staff_index.insert(pair <string, int> (name, staff_index.size()));

			vector <int> data_aux;
			
			data_aux.push_back(maxm);
			data_aux.push_back(minm);
			data_aux.push_back(maxct);
			data_aux.push_back(minct);
			data_aux.push_back(mincdl);
			data_aux.push_back(maxfd);

			staff_data.push_back(data_aux);
		}

		int get_MaxT(int staff, string turn){
			return MaxT[staff][turn];
		}

		int get_MaxM(int trabajador){
			return staff_data[trabajador][0];
		}
		int get_MinM(int trabajador){
			return staff_data[trabajador][1];
		}
		int get_MaxCT(int trabajador){
			return staff_data[trabajador][2];
		}
		int get_MinCT(int trabajador){
			return staff_data[trabajador][3];
		}
		int get_MinCDL(int trabajador){
			return staff_data[trabajador][4];
		}
		int get_MaxFD(int trabajador){
			return staff_data[trabajador][5];
		}

		vector <vector <int>> get_days_off(){
			return days_off;
		}


		vector <int> get_shift_on_request_empleado(){	
			return shift_on_request_empleado;
		}	
		vector <int> get_shift_on_request_dia(){	
			return shift_on_request_dia;
		}	
		vector <string> get_shift_on_request_turno(){	
			return shift_on_request_turno;
		}	
		vector <int> get_shift_on_request_peso(){	
			return shift_on_request_peso;
		}	


		vector <int> get_shift_off_request_empleado(){	
			return shift_off_request_empleado;
		}	
		vector <int> get_shift_off_request_dia(){	
			return shift_off_request_dia;
		}	
		vector <string> get_shift_off_request_turno(){	
			return shift_off_request_turno;
		}	
		vector <int> get_shift_off_request_peso(){	
			return shift_off_request_peso;
		}	
	

		vector <string> get_staff_names(){
			return staff_names;
		}

		string get_staff_name(int index){
			return staff_names[index];
		}

		int get_staff_quantity(){
			return staff_names.size();
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


int Model2(List_Turns list_turns, List_Staff list_staff,  vector <vector <string>> horario, int horizon){
	cout << "\nLista de restricciones no cumplidas encontradas:\n";
	
	int count_trabajador = 0;
	vector <string> turn_names = list_turns.get_turns_names();

	// iteracion sobre horario[empleado]
	for(auto trabajador = horario.begin(); trabajador != horario.end() ; ++trabajador){
		vector <string> horario_trabajador = *trabajador;
		
		int tiempo_trabajado = 0;
		map <string, int> dict_cantidad_turnos;
		for(auto turn_name = turn_names.begin(); turn_name != turn_names.end(); ++turn_name){
			dict_cantidad_turnos.insert(pair <string,int> (*turn_name, 0));
		}

		//variables utilizada en la quinta restricicon [cantidad de turnos maxima]
		//int next_day_off = -1; 
		int cont_dias_libres = 0;
		int cont_dias_trabajados = 0;
		int MaxCT = list_staff.get_MaxCT(count_trabajador);
		int MinCT = list_staff.get_MinCT(count_trabajador);
		int MinCDL = list_staff.get_MinCDL(count_trabajador);

		// iteracion sobre horario[empleado][dia]
		for(int dia = 0 ; dia < horizon; ++dia){

			// primera restriccion [restriccion de turnos seguidos]
			string actual_day = horario_trabajador[dia];

			if(dia < (horizon-1)){
				string next_day =horario_trabajador[dia+1];
				
				// cout << "turno dia_1 :" << actual_day << "\n";
				// cout << "turno dia_2 :" << next_day << "\n"; 

				// verificacion primera restriccion
				if(list_turns.verify_restriction(actual_day, next_day) == 1 ){
					string name = list_staff.get_staff_name(count_trabajador);
					cout << "Restriccion de turnos seguidos no se cumple: " << "\n";
					cout << "trabajador:  " << name << "\n";
					cout << "turno dia_1: " << actual_day << "\n";
					cout << "turno dia_2: " << next_day << "\n"; 

				}
			}

			
			if(actual_day == "-"){
				++cont_dias_libres;

				if(cont_dias_trabajados != 0){
					// quinta restriccion [cantidad maxima de dias trabajados consecutivos]
					if(cont_dias_trabajados > MaxCT){
						cout << "restriccion maxima de dias trabajados no se cumple\n";
						cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
					}
					// sexta restriccion [cantidad minima de dias trabajados consecutivos]
					if(cont_dias_trabajados < MinCT){
						cout << "restriccion minima de dias trabajados no se cumple\n";
						cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
					}

					cont_dias_trabajados = 0;
				}
			}

			if(actual_day != "-"){
				++cont_dias_trabajados;
				
				// septima restriccion [cantidad de minima de dias libres consecutivos]
				if(cont_dias_libres != 0){

					if(cont_dias_libres < MinCDL){
						cout << "restriccion minima de dias libres no se cumple\n";
						cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
					}

					cont_dias_libres = 0;
				} 
			}

			// segunda restriccion [cantidad de turnos maxima]
			dict_cantidad_turnos[actual_day] += 1;

			// tercera restriccion [tiempo maximo y minimo de tiempo por trabajador]
			tiempo_trabajado += list_turns.get_duration_turn(actual_day);
		
		}

		// verificacion de quinta y sexta restriccion
		if(cont_dias_trabajados != 0){

			if(cont_dias_trabajados > MaxCT){
				cout << "restriccion maxima de dias trabajados no se cumple\n";
				cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
			}
			else if(cont_dias_trabajados < MinCT){
				cout << "restriccion minima de dias trabajados no se cumple\n";
				cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
			}
		}

		// verificacion de septima restriccion
		if(cont_dias_libres != 0 && cont_dias_libres < MinCDL){
			cout << "restriccion minima de dias libres no se cumple\n";
			cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
		} 

		// verificacion segunda restriccion

		for(auto turn_name = turn_names.begin(); turn_name != turn_names.end() ; ++turn_name){
			if(dict_cantidad_turnos[*turn_name] >  list_staff.get_MaxT(count_trabajador, *turn_name)){
				cout << "Restricciones MaxT no cumplidas\n";
				cout << "Trabajador:\t" << list_staff.get_staff_name(count_trabajador) << "\n";
				cout << "Turn:\t" << *turn_name << "\n";
				cout << "MaxT:\t" << list_staff.get_MaxT(count_trabajador, *turn_name) << "\n";
				cout << "Total:\t" << dict_cantidad_turnos[*turn_name] << "\n";
			}
		}

		// verificacion de tercera restriccion
		if(tiempo_trabajado > list_staff.get_MaxM(count_trabajador)){
			cout << "MaxM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			cout << "MaxM:   " << list_staff.get_MaxM(count_trabajador)<< "\n";
			cout << "tiempo: " <<  tiempo_trabajado << "\n";
		}

		if(tiempo_trabajado < list_staff.get_MinM(count_trabajador)){
			cout << "MinM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			cout << "MinM:   " << list_staff.get_MinM(count_trabajador)<< "\n";
			cout << "tiempo: " <<  tiempo_trabajado << "\n";
		}

		// cout << "tiempo: " << list_staff.get_staff_name(count_trabajador) << ": " << tiempo_trabajado << "\n";
		
		tiempo_trabajado = 0; 

		count_trabajador += 1;
		
	}

	// cuarta restriccion [dias libres]

	int cantidad_empleados = list_staff.get_staff_quantity();
	vector <vector <int>> days_off = list_staff.get_days_off();
	
	for(int emp = 0; emp < cantidad_empleados; ++emp){
		for(auto dia = days_off[emp].begin() ; dia != days_off[emp].end(); ++dia){
			if(horario[emp][*dia] != "-"){
				cout << "Restricciones Days off : trabajador " << emp << ", dia " << *dia << "\n"; 
			}
			
		}
	}

	// octava restriciccion [shift on requests]
	vector <int> on_empleado = list_staff.get_shift_on_request_empleado();
	vector <int> on_dia = list_staff.get_shift_on_request_dia();
	vector <string> on_turno = list_staff.get_shift_on_request_turno();
	vector <int> on_peso = list_staff.get_shift_on_request_peso();

	int size_on = on_empleado.size();

	for(int request = 0; request < size_on ; ++request){
		if(horario[on_empleado[request]][on_dia[request]] != on_turno[request]){
			cout << "[shift on request] empleado: " << list_staff.get_staff_name(on_empleado[request]) << ", dia: "<< on_dia[request] <<", peso: "<< on_peso[request]<<"\n";
		}
	}

	// novena restriccion [shift off requests]
	vector <int> off_empleado = list_staff.get_shift_off_request_empleado();
	vector <int> off_dia = list_staff.get_shift_off_request_dia();
	vector <string> off_turno = list_staff.get_shift_off_request_turno();
	vector <int> off_peso = list_staff.get_shift_off_request_peso();

	int size_off = off_empleado.size();

	for(int request = 0; request < size_off ; ++request){
		if(horario[off_empleado[request]][off_dia[request]] == off_turno[request]){
			cout << "[shift off request] empleado: " << list_staff.get_staff_name(off_empleado[request]) << ", dia: "<< off_dia[request] <<", peso: "<< off_peso[request]<<"\n";
		}
	}

	return 0;
}
 
int main () {

	string str;
	/* nombre de archivo por defecto */ 
	string file_name = "Instance0.txt"; 
	/* casos de prueba deben estar en la carpeta "Casos" */
	std::ifstream file("Instances//"+file_name);

	if(file.fail()){
		cout << "caso de prueba no encontrado\n";
	
	} else {

		/* lista con las lineas del archivo */
		list<string> list_aux;

		while (std::getline(file,str))
		{
			if(!std::regex_match (str, std::regex("(^#[\\s\\S]*)")) && str != "" ) {
				
				list_aux.push_back(str);

			}

		}

		file.close();

		/* Parseo de datos sobre la lista auxiliar*/

		string HORIZON = "SECTION_HORIZON";
		string SHIFTS = "SECTION_SHIFTS";
		string STAFF = "SECTION_STAFF";
		string DAY_OFF = "SECTION_DAYS_OFF";
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
				cout << label << "\n";
			}
			
			else{

				if(label == HORIZON){
					Horizon = stoi(*line);
					cover_list.set_values(Horizon);

				}

				else if(label == SHIFTS){
					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> split_line = split(parse_line);
					// split_line[0] = name_turn
					// split_line[1] = duration
					// split_line[2] = restricction
					// turn_shifts.append_turn(split_line[0], stoi(split_line[1]), split(parce_rest));

					string name_turn = split_line[0];
					int duration = stoi(split_line[1]);

					if (split_line.size() == 3){
						string parce_rest = std::regex_replace (split_line[2],separadores," ");
						turn_shifts.append_turn_restriccions(name_turn,  split(parce_rest));
						turn_shifts.append_duration_turn(name_turn, duration);
					}
					else if (split_line.size() == 2){
						vector <string> rest;
						turn_shifts.append_turn_restriccions(name_turn, rest);
						turn_shifts.append_duration_turn(name_turn, duration);
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

					// crea el diccionario MaxT
					for (auto i = split_aux.begin();i!=split_aux.end();++i){
						string aux_equal = std::regex_replace (*i,equal," ");

						vector <string> aux_MatT = split(aux_equal);
						MaxT.insert(pair <string, int> (aux_MatT[0], stoi(aux_MatT[1]))); 
						
					}

					/*funciones nuevas*/

					staff_list.set_MaxT(MaxT);
					staff_list.set_staff_data(split_line[0],stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]), stoi(split_line[5]), stoi(split_line[6]), stoi(split_line[7]));

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

					staff_list.set_days_off(Horizon, list_days_off);

				}

				else if(label == SHIFT_ON_REQUESTS){

					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> aux_line = split(parse_line);
					
					string staff_name = aux_line[0];
					int dia = stoi(aux_line[1]);
					string turno = aux_line[2];
					int peso = stoi(aux_line[3]);

					staff_list.set_shift_on_request(staff_name, dia, turno, peso);
				}

				else if(label == SHIFT_OFF_REQUESTS){

					string parse_line = std::regex_replace (*line,comas," ");
					vector <string> aux_line = split(parse_line);

					string staff_name = aux_line[0];
					int dia = stoi(aux_line[1]);
					string turno = aux_line[2];
					int peso = stoi(aux_line[3]);
					
					staff_list.set_shift_off_request(staff_name, dia, turno, peso);

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
					cout << "Fail in the format case: "<< *line << "\n" ;
				} 

			}

		}	

		cout << "Termino del parseo del archivo\n";

		/* Termino de parseo del archivo*/


		/* Comienzo de pruebas de soluciones */

		map <string, vector <string>> solution;
		vector <vector <string>> solution_method_2;

		std::ifstream file("Instances//solution.txt");

		if(file.fail()){
			cout << "caso de prueba [solucion] no encontrado\n";
	
		} else {

			/* lista con las lineas del archivo */
			list<string> line_solution;

			while (std::getline(file,str))
			{
				if(!std::regex_match (str, std::regex("(^#[\\s\\S]*)")) && str != "" ) {
					
					line_solution.push_back(str);

				}

			}

			file.close();


			for (auto line = line_solution.begin(); line != line_solution.end(); ++line){
				// string parse_line = std::regex_replace (*line,separadores," ");
				// vector <string> trabajador_horario = split(parse_line);
				// string trabajador = trabajador_horario[0];
				// string horario_aux = std::regex_replace (trabajador_horario[1],comas," ");
				// vector <string> horario = split(horario_aux);
				// solution.insert(pair <string , vector <string>> (trabajador, horario));
				
				/* solucion solo con vectores */

				string parse_line = std::regex_replace (*line,separadores," ");
				vector <string> trabajador_horario = split(parse_line);
				string horario_aux = std::regex_replace (trabajador_horario[1],comas," ");
				vector <string> horario = split(horario_aux);
				solution_method_2.push_back(horario);
				
			}

			/* Ejecucion del modelo sobre las soluciones de prueba */
			//Model(List_Turns list_turns, List_Staff list_staff,  map <string, vector <string>> horario, int horizon)
			cout << "Inicio de pruebas del modelo\n";
			//Model(turn_shifts, staff_list, solution, Horizon);
			Model2(turn_shifts, staff_list, solution_method_2, Horizon);
			

		}

	}
    return 0;
}