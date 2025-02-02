#include <fstream>		//lectura y escritura de archivos
#include <iostream>
#include <string>		
#include <algorithm>	//funcion find()
#include <regex>		//parseo archivo
#include <random>
#include <cstdio>		//timer
#include <ctime> 		//timer 
#include <sstream>		//input 

using namespace std;

// Clase List_turns: clase que guarda la informacion sobre los turnos
class List_Turns {
	vector <string> turns_names;
	map <string, vector <string>> turns_restriccions;
	map <string, int> duration_turn;
	map <string, int> turn_index;

	public:

		void append_turn_restriccions(string turn_name, vector <string> restriccion){
			turns_names.push_back(turn_name);
			turns_restriccions.insert(pair <string, vector <string>> (turn_name, restriccion));
			turn_index.insert(pair <string, int> (turn_name, turn_index.size()));
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

		string get_turn_name(int turn){
			return turns_names[turn];
		}
		
		map <string, int> get_turns_index(){
			return turn_index;
		}

		int get_turn_quantity(){
			return turns_names.size();
		}
		 

};

// Class List_Staff: clase que guarda la informacion sobre los empleados
class List_Staff {
	vector <string> staff_names ;
	map <string, int> staff_index;
	// MaxT[int [trabajador][string turno] = int cantidad
	vector <map<string , int>> MaxT;
	// [maxm, minm, maxct, minct, mincdl, maxfd]
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
	
	// info in putput file 
	vector <string> output_info;

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

		void set_output_info(string line){
			output_info.push_back(line);
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

		vector <string> get_output_info(){
			return output_info;
		}

};

// Class Cover: clase que guarda la informacion referida a los turnos totales que debe tener el horario por dia
class Cover{

	vector <vector <vector <int>>> matrix_of_covers;

	public:
		void add_values(int dia, string turno, vector <int> datos){
			int actual_size_matrix =  matrix_of_covers.size();
			if(dia == actual_size_matrix){
				vector <vector <int>> aux_matrix;
				aux_matrix.push_back(datos);
				matrix_of_covers.push_back(aux_matrix);

			}
			else{
				matrix_of_covers[dia].push_back(datos);
			}
			
			
		}

		void print_section_cover(){
			int dias = matrix_of_covers.size();
			int turnos = matrix_of_covers[0].size(); 

			for(int dia = 0 ; dia < dias; ++dia){
				for(int turno = 0 ; turno < turnos ; ++turno){
					cout << matrix_of_covers[dia][turno][0] << " , ";
					cout << matrix_of_covers[dia][turno][1] << " , ";
					cout << matrix_of_covers[dia][turno][2] << "\n"; 
				}
			}
		}

		vector <vector <vector <int>>> get_section_cover(){
			return matrix_of_covers;
		}

};

// Funcion split: realiza una separacion de strings por espacios en blanco
vector <string> split(string line){
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));	
	return tokens;	
};

// Funcion Model2: entrega el valor de la funcion de satisfaccion de acuerdo al horario
int Model2(List_Turns list_turns, List_Staff list_staff, Cover cover, int horizon, vector <int> castigos,vector <vector <string>> horario){
	//cout << "\nLista de restricciones no cumplidas encontradas:\n";

	vector <string> turn_names = list_turns.get_turns_names();
	int cantidad_empleados = list_staff.get_staff_quantity();
	int cantidad_turnos = turn_names.size();
	int satisfaction_sum = 0;

	//diccionario usado en la novena restriccion
	map <string, int> turn_index = list_turns.get_turns_index();
	vector <vector <vector <int>>> cover_matrix = cover.get_section_cover();

	//variables usadas en la decima restriccion
	vector <int> aux_vector(list_staff.get_staff_quantity(), 0);
	vector <vector <int>> actual_cover(horizon,aux_vector);

	// iteracion sobre horario[empleado]
	for(int count_trabajador = 0 ; count_trabajador < cantidad_empleados; ++count_trabajador ){
		vector <string> horario_trabajador = horario[count_trabajador];
		
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
					// string name = list_staff.get_staff_name(count_trabajador);
					// cout << "Restriccion de turnos seguidos no se cumple: " << "\n";
					// cout << "trabajador:  " << name << "\n";
					// cout << "turno dia_1: " << actual_day << "\n";
					// cout << "turno dia_2: " << next_day << "\n"; 

					satisfaction_sum += castigos[1];

				}
			}

			
			if(actual_day == "-"){
				++cont_dias_libres;

				if(cont_dias_trabajados != 0){
					// quinta restriccion [cantidad maxima de dias trabajados consecutivos]
					if(cont_dias_trabajados > MaxCT){
						// cout << "restriccion maxima de dias trabajados no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						satisfaction_sum += castigos[5]*abs(cont_dias_trabajados - MaxCT);
					}
					// sexta restriccion [cantidad minima de dias trabajados consecutivos]
					if(cont_dias_trabajados < MinCT){
						// cout << "restriccion minima de dias trabajados no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						satisfaction_sum += castigos[6]*abs(MinCT-cont_dias_trabajados);
					}

					cont_dias_trabajados = 0;
				}
			}

			if(actual_day != "-"){
				++cont_dias_trabajados;

				//decima restriccion [section cover]
				//contador de turnos trabajados por dia
				++actual_cover[dia][turn_index[actual_day]];
				
				// septima restriccion [cantidad de minima de dias libres consecutivos]
				if(cont_dias_libres != 0){

					if(cont_dias_libres < MinCDL){
						// cout << "restriccion minima de dias libres no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						satisfaction_sum += castigos[7]*abs(MinCDL - cont_dias_libres);
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
				// cout << "restriccion maxima de dias trabajados no se cumple\n";
				// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
				satisfaction_sum += castigos[5]*abs(cont_dias_trabajados - MaxCT);
			}
			else if(cont_dias_trabajados < MinCT){
				// cout << "restriccion minima de dias trabajados no se cumple\n";
				// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
				satisfaction_sum += castigos[6]*abs(MinCT - cont_dias_trabajados);
			}
		}

		// verificacion de septima restriccion
		if(cont_dias_libres != 0 && cont_dias_libres < MinCDL){
			// cout << "restriccion minima de dias libres no se cumple\n";
			// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
			satisfaction_sum += castigos[7]*abs(MinCDL - cont_dias_libres);
		} 

		// verificacion segunda restriccion

		for(auto turn_name = turn_names.begin(); turn_name != turn_names.end() ; ++turn_name){
			if(dict_cantidad_turnos[*turn_name] >  list_staff.get_MaxT(count_trabajador, *turn_name)){
				// cout << "Restricciones MaxT no cumplidas\n";
				// cout << "Trabajador:\t" << list_staff.get_staff_name(count_trabajador) << "\n";
				// cout << "Turn:\t" << *turn_name << "\n";
				// cout << "MaxT:\t" << list_staff.get_MaxT(count_trabajador, *turn_name) << "\n";
				// cout << "Total:\t" << dict_cantidad_turnos[*turn_name] << "\n";

				satisfaction_sum += castigos[2]*abs(dict_cantidad_turnos[*turn_name] - list_staff.get_MaxT(count_trabajador, *turn_name));
			}
		}

		// verificacion de tercera restriccion
		if(tiempo_trabajado > list_staff.get_MaxM(count_trabajador)){
			// cout << "MaxM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			// cout << "MaxM:   " << list_staff.get_MaxM(count_trabajador)<< "\n";
			// cout << "tiempo: " <<  tiempo_trabajado << "\n";
			satisfaction_sum += castigos[3]-600;
		}

		if(tiempo_trabajado < list_staff.get_MinM(count_trabajador)){
			// cout << "MinM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			// cout << "MinM:   " << list_staff.get_MinM(count_trabajador)<< "\n";
			// cout << "tiempo: " <<  tiempo_trabajado << "\n";
			satisfaction_sum += castigos[3];
		}

		// cout << "tiempo: " << list_staff.get_staff_name(count_trabajador) << ": " << tiempo_trabajado << "\n";
		
		
	}

	// cuarta restriccion [dias libres]
	vector <vector <int>> days_off = list_staff.get_days_off();
	
	for(int emp = 0; emp < cantidad_empleados; ++emp){
		for(auto dia = days_off[emp].begin() ; dia != days_off[emp].end(); ++dia){
			if(horario[emp][*dia] != "-"){
				//cout << "Restricciones [Days off] trabajador: " << emp << ", dia " << *dia << "\n"; 
				satisfaction_sum += castigos[4];
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
			//cout << "[shift on request] empleado: " << list_staff.get_staff_name(on_empleado[request]) << ", dia: "<< on_dia[request] <<", peso: "<< on_peso[request]<<"\n";
			satisfaction_sum+= on_peso[request];
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
			//cout << "[shift off request] empleado: " << list_staff.get_staff_name(off_empleado[request]) << ", dia: "<< off_dia[request] <<", peso: "<< off_peso[request]<<"\n";
			satisfaction_sum+= off_peso[request];
		}
	}

	// decima restriccion [cover section]
	for(int i = 0; i < horizon ; ++i){
		for(int j = 0; j < cantidad_turnos; ++j){
			if(cover_matrix[i][j][0] < actual_cover[i][j]){
				//cout << "resticcion [cover section][over] dia: " << i << ", turno: " << j << "\n";
				satisfaction_sum+= cover_matrix[i][j][2]*abs(actual_cover[i][j] - cover_matrix[i][j][0]);
			}
			if(cover_matrix[i][j][0] > actual_cover[i][j]){
				//cout << "resticcion [cover section][sub] dia: " << i << ", turno: " << j << "\n"; 
				satisfaction_sum += cover_matrix[i][j][1]*abs(cover_matrix[i][j][0] - actual_cover[i][j]);
			}
		}
	}

	// onceaba restriccion [maximo de fines de semana trabajados]
	for(int empleado = 0; empleado < list_staff.get_staff_quantity(); ++empleado){
		int contador_findes_trabajados = 0;
		int sabado = 5;
		while(sabado < horizon){
			int domingo = sabado + 1;
			if(domingo < horizon){
				if(horario[empleado][sabado] != "-" || horario[empleado][domingo] != "-"){
					++contador_findes_trabajados;
				}
			}
			else{
				if(horario[empleado][sabado] != "-"){
					++contador_findes_trabajados;
				}
			}

			sabado = sabado + 7;
		}

		if(contador_findes_trabajados > list_staff.get_MaxFD(empleado)){
			//cout << "restriccion [max findes] trabajador: " << empleado <<"\n";
			satisfaction_sum += castigos[8]*abs(contador_findes_trabajados - list_staff.get_MaxFD(empleado));
		}
	}

	return satisfaction_sum;
}

// Funcion horario_creation: crea un horario de manera aleatoria 
vector <vector <string>> horario_creation( List_Turns turns_list,List_Staff staff_list, Cover cover , int horizon){
	int cantidad_empleados = staff_list.get_staff_quantity();
	vector <string> aux_list(horizon, "-");
	vector <vector <string>> new_horario(cantidad_empleados,aux_list);
	
	vector <string> turn_names = turns_list.get_turns_names();

	vector <vector <int>> days_off = staff_list.get_days_off();

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> free_day(0,9);
	uniform_int_distribution<std::mt19937::result_type> random_generator(0,turns_list.get_turn_quantity()-1); 

	for(int emp = 0 ; emp < cantidad_empleados ; ++emp){
		for(int dia = 0; dia < horizon; ++dia){
			if(free_day(rng) > 5){
				new_horario[emp][dia] = "-";
			}
			else{
				new_horario[emp][dia] = turn_names[random_generator(rng)];
			}
		}
	}

	//descomentar para incluir los libres obligatorios

	// for(int emp = 0; emp < cantidad_empleados; ++emp){
	// 	for(auto dia = days_off[emp].begin() ; dia != days_off[emp].end(); ++dia){
	// 		new_horario[emp][*dia] = "-";
	// 	}
	// }

	return new_horario;
} 

// Funcion iteration: realiza un cambio aleatorio sobre un horario 
vector <vector <string>> iteration(List_Turns turn_list,List_Staff staff_list,Cover cover, int horizon, vector <vector <string>> horario ){
	int cantidad_empleados = staff_list.get_staff_quantity();
	vector <string> turn_names = turn_list.get_turns_names();

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> free_day(0,9);
	uniform_int_distribution<std::mt19937::result_type> random_turn(0,turn_list.get_turn_quantity()-1);
	uniform_int_distribution<std::mt19937::result_type> random_day(0,horizon-1);
	uniform_int_distribution<std::mt19937::result_type> random_staff(0,cantidad_empleados - 1);

	int turn = random_turn(rng);
	int day = random_day(rng);
	int staff = random_staff(rng);

	//cout << "actu:	"<< horario[staff][day] << endl;

	if(free_day(rng) > 5){
		if(horario[staff][day] == "-"){
			horario[staff][day] = turn_names[turn];
		}
		else{	
			horario[staff][day] = "-";
		}

	}
	else{
		if(horario[staff][day] == turn_names[turn]){
			horario[staff][day] = "-";
		}
		else{
			horario[staff][day] = turn_names[turn];
		}
	}

	return horario;
	
}

// Funcion archive_out: escribe el archivo de salida [output.txt]
void archive_out(List_Turns list_turns, List_Staff list_staff, Cover cover, int horizon, vector <int> castigos,vector <vector <string>> horario){
	
	//int count_trabajador = 0;
	vector <string> turn_names = list_turns.get_turns_names();
	int cantidad_turnos = turn_names.size();
	int cantidad_empleados = list_staff.get_staff_quantity();
	int satisfaction_sum = 0;

	// contador de penalizaciones por empleado
	vector <int> penalizaciones_empleado(cantidad_empleados,0);

	// costos por dia [cover section]
	vector <int> costos_por_dia(horizon,0);

	//diccionario usado en la novena restriccion
	map <string, int> turn_index = list_turns.get_turns_index();
	vector <vector <vector <int>>> cover_matrix = cover.get_section_cover();

	//variables usadas en la decima restriccion
	vector <int> aux_vector(list_staff.get_staff_quantity(), 0);
	vector <vector <int>> actual_cover(horizon,aux_vector);

	// iteracion sobre horario[empleado]
	for(int count_trabajador = 0 ; count_trabajador < cantidad_empleados; ++count_trabajador ){
		vector <string> horario_trabajador = horario[count_trabajador];
		
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
					// string name = list_staff.get_staff_name(count_trabajador);
					// cout << "Restriccion de turnos seguidos no se cumple: " << "\n";
					// cout << "trabajador:  " << name << "\n";
					// cout << "turno dia_1: " << actual_day << "\n";
					// cout << "turno dia_2: " << next_day << "\n"; 
					++penalizaciones_empleado[count_trabajador];

					satisfaction_sum += castigos[1];

				}
			}

			
			if(actual_day == "-"){
				++cont_dias_libres;

				if(cont_dias_trabajados != 0){
					// quinta restriccion [cantidad maxima de dias trabajados consecutivos]
					if(cont_dias_trabajados > MaxCT){
						// cout << "restriccion maxima de dias trabajados no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						++penalizaciones_empleado[count_trabajador];
						satisfaction_sum += castigos[5]*(cont_dias_trabajados - MaxCT);
					}
					// sexta restriccion [cantidad minima de dias trabajados consecutivos]
					if(cont_dias_trabajados < MinCT){
						// cout << "restriccion minima de dias trabajados no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						++penalizaciones_empleado[count_trabajador];
						satisfaction_sum += castigos[6]*(MinCT - cont_dias_trabajados);
					}

					cont_dias_trabajados = 0;
				}
			}

			if(actual_day != "-"){
				++cont_dias_trabajados;

				//decima restriccion [section cover]
				//contador de turnos trabajados por dia
				++actual_cover[dia][turn_index[actual_day]];
				
				// septima restriccion [cantidad de minima de dias libres consecutivos]
				if(cont_dias_libres != 0){

					if(cont_dias_libres < MinCDL){
						// cout << "restriccion minima de dias libres no se cumple\n";
						// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << dia << "\n" ;
						satisfaction_sum += castigos[7]*(MinCDL - cont_dias_libres);
						++penalizaciones_empleado[count_trabajador];
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
				// cout << "restriccion maxima de dias trabajados no se cumple\n";
				// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
				++penalizaciones_empleado[count_trabajador];
				satisfaction_sum += castigos[5]*(cont_dias_trabajados - MaxCT);
			}
			else if(cont_dias_trabajados < MinCT){
				// cout << "restriccion minima de dias trabajados no se cumple\n";
				// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
				++penalizaciones_empleado[count_trabajador];
				satisfaction_sum += castigos[6]*(MinCT-cont_dias_trabajados);
			}
		}

		// verificacion de septima restriccion
		if(cont_dias_libres != 0 && cont_dias_libres < MinCDL){
			// cout << "restriccion minima de dias libres no se cumple\n";
			// cout << "empleado: " << list_staff.get_staff_name(count_trabajador) << ", dia; " << horizon - 1 << "\n" ;
			++penalizaciones_empleado[count_trabajador];
			satisfaction_sum += castigos[7]*(MinCDL - cont_dias_libres);
		} 

		// verificacion segunda restriccion

		for(auto turn_name = turn_names.begin(); turn_name != turn_names.end() ; ++turn_name){
			if(dict_cantidad_turnos[*turn_name] >  list_staff.get_MaxT(count_trabajador, *turn_name)){
				// cout << "Restricciones MaxT no cumplidas\n";
				// cout << "Trabajador:\t" << list_staff.get_staff_name(count_trabajador) << "\n";
				// cout << "Turn:\t" << *turn_name << "\n";
				// cout << "MaxT:\t" << list_staff.get_MaxT(count_trabajador, *turn_name) << "\n";
				// cout << "Total:\t" << dict_cantidad_turnos[*turn_name] << "\n";
				++penalizaciones_empleado[count_trabajador];
				satisfaction_sum += castigos[2]*abs(dict_cantidad_turnos[*turn_name] - list_staff.get_MaxT(count_trabajador, *turn_name));
			}
		}

		// verificacion de tercera restriccion
		if(tiempo_trabajado > list_staff.get_MaxM(count_trabajador)){
			// cout << "MaxM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			// cout << "MaxM:   " << list_staff.get_MaxM(count_trabajador)<< "\n";
			// cout << "tiempo: " <<  tiempo_trabajado << "\n";
			++penalizaciones_empleado[count_trabajador];
			satisfaction_sum += castigos[3];
		}

		if(tiempo_trabajado < list_staff.get_MinM(count_trabajador)){
			// cout << "MinM restriccion [Trabajador]: " << list_staff.get_staff_name(count_trabajador) <<"\n";  
			// cout << "MinM:   " << list_staff.get_MinM(count_trabajador)<< "\n";
			// cout << "tiempo: " <<  tiempo_trabajado << "\n";
			++penalizaciones_empleado[count_trabajador];
			satisfaction_sum += castigos[3];
		}

		// cout << "tiempo: " << list_staff.get_staff_name(count_trabajador) << ": " << tiempo_trabajado << "\n";
		
		//tiempo_trabajado = 0; 

		//count_trabajador += 1;
		
	}

	// cuarta restriccion [dias libres]
	vector <vector <int>> days_off = list_staff.get_days_off();
	
	for(int emp = 0; emp < cantidad_empleados; ++emp){
		for(auto dia = days_off[emp].begin() ; dia != days_off[emp].end(); ++dia){
			if(horario[emp][*dia] != "-"){
				//cout << "Restricciones [Days off] trabajador: " << emp << ", dia " << *dia << "\n"; 
				++penalizaciones_empleado[emp];
				satisfaction_sum += castigos[4];
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
			//cout << "[shift on request] empleado: " << list_staff.get_staff_name(on_empleado[request]) << ", dia: "<< on_dia[request] <<", peso: "<< on_peso[request]<<"\n";
			satisfaction_sum+= on_peso[request];
			++penalizaciones_empleado[on_empleado[request]];
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
			//cout << "[shift off request] empleado: " << list_staff.get_staff_name(off_empleado[request]) << ", dia: "<< off_dia[request] <<", peso: "<< off_peso[request]<<"\n";
			++penalizaciones_empleado[off_empleado[request]];
			satisfaction_sum+= off_peso[request];
		}
	}

	// decima restriccion [cover section]
	for(int i = 0; i < horizon ; ++i){
		for(int j = 0; j < cantidad_turnos; ++j){
			if(cover_matrix[i][j][0] < actual_cover[i][j]){
				//cout << "resticcion [cover section][over] dia: " << i << ", turno: " << j << "\n";
				satisfaction_sum+= cover_matrix[i][j][2]*abs(actual_cover[i][j] - cover_matrix[i][j][0]);
				costos_por_dia[i]+= cover_matrix[i][j][2]*abs(actual_cover[i][j] - cover_matrix[i][j][0]);
			}
			if(cover_matrix[i][j][0] > actual_cover[i][j]){
				//cout << "resticcion [cover section][sub] dia: " << i << ", turno: " << j << "\n"; 
				satisfaction_sum += cover_matrix[i][j][1]*abs(cover_matrix[i][j][0] - actual_cover[i][j]);
				costos_por_dia[i]+= cover_matrix[i][j][1]*abs(cover_matrix[i][j][0] - actual_cover[i][j]);
			}
		}
	}

	// onceaba restriccion [maximo de fines de semana trabajados]
	for(int empleado = 0; empleado < cantidad_empleados; ++empleado){
		int contador_findes_trabajados = 0;
		int sabado = 5;
		while(sabado < horizon){
			int domingo = sabado + 1;
			if(domingo < horizon){
				if(horario[empleado][sabado] != "-" || horario[empleado][domingo] != "-"){
					++contador_findes_trabajados;
				}
			}
			else{
				if(horario[empleado][sabado] != "-"){
					++contador_findes_trabajados;
				}
			}

			sabado += 7;
		}

		if(contador_findes_trabajados > list_staff.get_MaxFD(empleado)){
			//cout << "restriccion [max findes] trabajador: " << empleado <<"\n";
			++penalizaciones_empleado[empleado];
			satisfaction_sum += castigos[8]*abs(contador_findes_trabajados - list_staff.get_MaxFD(empleado));
		}
	}

	ofstream output;
	output.open ("output.txt");
  	output << "#Valor Función Objetivo:\n\n";
	output << satisfaction_sum << "\n\n";

	output << "#Calendario horizonte de " << horizon << " días:\n\n";  
	output << "Empleados/Días\t";
	for(int iter = 0 ; iter < horizon ; ++iter){
		output << "|" << iter << "\t";
	}
	output << "\n";
	for(int emp = 0 ; emp < cantidad_empleados ; ++emp){
		output << list_staff.get_staff_name(emp) << "\t\t" ;
		for(int dia = 0; dia < horizon; ++dia){
			output << "|" << horario[emp][dia] << "\t" ;
		}
		output << "\n"; 
	}

	int penalizaciones_totales = 0;

	output << "\n#Penalizaciones por empleado:\n\n";
	for(int emp = 0 ; emp < cantidad_empleados ; ++emp){
		output << list_staff.get_staff_name(emp) << "\t,\t" ;
		output << penalizaciones_empleado[emp] << "\n";
		penalizaciones_totales+= penalizaciones_empleado[emp];
	}

	output << "\nTabla de cobertura de turnos y penalización por dı́a:\n\n";
	output << "Turnos/Días\t";
	for(int iter = 0 ; iter < horizon ; ++iter){
		output << "|" << iter << "\t";
	}
	output << "\n";

	for(int turno = 0 ; turno < cantidad_turnos ; ++turno){
		output << list_turns.get_turn_name(turno) << "\t\t" ;
		for(int dia = 0; dia < horizon ; ++dia){
			output << "|" << actual_cover[dia][turno] <<"/"<< cover_matrix[dia][turno][0] << "\t";
		}
		output << "\n";
	}

	int costo_asignacion = 0;

	output << "Costo\t\t";
	for(int dia = 0; dia < horizon ; ++dia){
		output << "|" << costos_por_dia[dia] << "\t";
		costo_asignacion+= costos_por_dia[dia];
	}

	

	output << "\n\n#Resumen información por empleado:\n";
	output << "EmpleadoID, MaxT, MaxM, MinM, MaxCT, MinCT, MinCDL, MaxFD\n\n";

	vector <string> output_info = list_staff.get_output_info();

	for(int empleado = 0; empleado < cantidad_empleados; ++empleado){
		output << output_info[empleado] << "\n";
	}

  	output.close();

	//cout << "Costo de asignacion: "<< costo_asignacion << endl;  
	//cout << "Cantidad de penalizaciones: "<< penalizaciones_totales << endl;
}

// Funcion logs: escribe un archivo adicional [logs.txt] con infomacion de la ejecucion del algoritmo
void logs(string file_name, int restarts, int numero_vecinos,int vecindarios, int best_solution, double total_duration){

	// escritura de sobre archivo logs:
	ifstream file("logs.txt");

	//logs.open("logs.txt", ios::app);
	ofstream logs;
	logs.open("logs.txt", ios::app);

	if(file.fail()){

		logs << "Caso\t\tRest\tVecinos\t\tVecindarios\tResultado\tDuracion Total[seg]" << "\n";
	}
	
	file.close();
	// ofstream logs;
	// logs.open("logs.txt", ios::app);
	logs << file_name << "\t";
	logs << restarts << "\t";
	logs << numero_vecinos << "\t\t";
	logs << vecindarios << "\t\t";
	logs << best_solution << "\t\t";
	logs << total_duration << "\t";
	logs << "\n" ;
	logs.close();
	
}

int main () {

	string str;
	string input;

	int number_instance;
	int restarts;	
	int numero_vecindarios;
	int numero_vecinos;			

	bool check_1 = true;
	bool check_2 = true;
	bool check_3 = true;
	bool check_4 = true;

	string file_name;
	string default_configurtion;

	cout << "Ejecutar la configuración por defecto? [y/n]: ";
	getline(cin,input);
	stringstream(input) >> default_configurtion;

	if(default_configurtion == "n" || default_configurtion == "N"){
		cout << "Escriba el número de la instacia a ejecutar" << endl <<  "[debe ser un número del 1 al 24]: " ;
		getline(cin,input);
		stringstream(input) >> number_instance;

		if(0 < number_instance && number_instance < 25){
			file_name = "Instance"+to_string(number_instance)+".txt";
			check_1 = false;
		}

		while(check_1){
			cout << "Escriba un número entre el 1 al 24: ";
			getline(cin,input);
			stringstream(input) >> number_instance;
			if(0 < number_instance && number_instance < 25){
				file_name = "Instance"+to_string(number_instance)+".txt";
				check_1 = false;
			}
		}

		cout << "Número de reinicios: ";
		getline(cin,input);
		stringstream(input) >> restarts;

		if(0 <= restarts ){
			check_2 = false;
		}

		while(check_2){
			cout << "La cantidad de reinicios debe ser igual o mayor que 0: ";
			getline(cin,input);
			stringstream(input) >> restarts;
			if(0 <= restarts ){
				check_2 = false;
			}
		}

		cout << "Número vecindarios a visitar: ";
		getline(cin,input);
		stringstream(input) >> numero_vecindarios;

		if(0 < numero_vecindarios ){
			check_3 = false;
		}

		while(check_3){
			cout << "El número de vecindarios debe ser mayor que 0: ";
			getline(cin,input);
			stringstream(input) >> numero_vecindarios;
			if(0 < numero_vecindarios ){
				check_3 = false;
			}
		}

		cout << "Número de vecinos por vecindario: ";
		getline(cin,input);
		stringstream(input) >> numero_vecinos;

		if(0 < numero_vecinos ){
			check_4 = false;
		}

		while(check_4){
			cout << "El vecinos debe ser mayor que 0: ";
			getline(cin,input);
			stringstream(input) >> numero_vecinos;
			if(0 < numero_vecinos ){
				check_4 = false;
			}
		}
	}

	else{
		// parametros [Default] del HC
		file_name = "Instance5.txt"; 
		restarts = 100;					// cantidad de restarts
		numero_vecinos = 50;			// cantidad de vecinos
		numero_vecindarios = 50;		// cantidad de vecindarios revisados

	}
	
	std::ifstream file("Instances//"+file_name);

	if(file.fail()){
		cout << "Instancia de prueba no encontrada\n";
	
	} else {

		/* lista con las lineas del archivo */
		vector <string> list_aux;
		

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

		//std::set<std::string> set_labels = {HORIZON, SHIFTS, STAFF, DAY_OFF, SHIFT_ON_REQUESTS, SHIFT_OFF_REQUESTS, COVER};
		string label;
		//std::set<std::string>::iterator in_set_labels;

		vector <string> set_labels = {HORIZON, SHIFTS, STAFF, DAY_OFF, SHIFT_ON_REQUESTS, SHIFT_OFF_REQUESTS, COVER};


		std::regex comas ("\\s*,\\s*");
		std::regex spaces ("\\s");
		std::regex separadores ("\\|");
		std::regex equal ("=");

		for(auto line = list_aux.begin(); line != list_aux.end(); line++)
		{

			//in_set_labels = set_labels.find(*line);

			auto in_set_labels = find(set_labels.begin(), set_labels.end(), *line);

			if(in_set_labels != set_labels.end()){
				label = *line;
				//cout << label << "\n";
			}
			
			else{

				if(label == HORIZON){
					Horizon = stoi(*line);
					//cover_list.set_values(Horizon);

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

					staff_list.set_output_info(*line);

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

		/* Comienzo de pruebas de soluciones */

		// castigos para las soluciones infactibles [Jerarquia de prioridades]
		vector <int> castigos;
		castigos.push_back(0);
		// estos valores no cambian a lo largo de la ejecucion del programa
		castigos.push_back(800); // 1° restriccion		[restriccion de turnos seguidos]
		castigos.push_back(500); // 2° restriccion		[cantidad de turnos maxima]
		castigos.push_back(1300); // 3° restriccion		[tiempo maximo y minimo de tiempo por trabajador]
		castigos.push_back(1500); // 4° restriccion		[dias libres]
		castigos.push_back(500); // 5° restriccion		[cantidad maxima de dias trabajados consecutivos]
		castigos.push_back(500); // 6° restriccion		[cantidad minima de dias trabajados consecutivos]
		castigos.push_back(500); // 7° restriccion		[cantidad de minima de dias libres consecutivos]
		castigos.push_back(500); // 11° restriccion		[maximo de fines de semana trabajados]
	
		if(default_configurtion != "n" && default_configurtion != "N"){
			cout << "\nConfiguracion por defecto:" << endl;
		}
		else{
			cout << "\n";
		}
		
		cout << "Caso de prueba:\t\t"<<file_name << endl; 
		cout << "Cantidad de Restarts:\t" << restarts << endl;	
		cout << "Numero de vecindarios:\t" << numero_vecindarios << endl;
		cout << "Numero de vecinos:\t"<<numero_vecinos << endl;
		
		cout << "\nInicio del HC-BI\n" << endl ;

		int best_solution = -1;
		vector <vector<string>> best_horario;
		clock_t start;
		double sum_soluciones = 0;

		start = clock();
		// double Total_time = minutos * 60;

		for(auto rest = 0; rest <= restarts ; ++rest){
				
			vector <vector <string>> horario = horario_creation(turn_shifts,staff_list, cover_list, Horizon);;
			int solution = Model2(turn_shifts, staff_list, cover_list, Horizon, castigos,horario);

			for(int vecindarios = 0; vecindarios < numero_vecindarios ; ++vecindarios ){
				int best_solution_vecino = -1;
				vector <vector<string>> best_vecino;

				for(int vecino = 0; vecino < numero_vecinos; ++vecino){

					vector <vector <string>> new_horario = iteration(turn_shifts,staff_list, cover_list, Horizon, horario);
					int solution_vecino = Model2(turn_shifts, staff_list, cover_list, Horizon, castigos,new_horario);

					if(solution_vecino < best_solution_vecino || best_solution_vecino == -1){
						best_vecino = new_horario;
						best_solution_vecino = solution_vecino;
					}

				}

				if(best_solution_vecino < solution){
					solution = best_solution_vecino;
					horario = best_vecino;
				}

			}

			// promedio de mejores soluciones encontradas por vecindario 
			sum_soluciones+=solution;

			if(solution < best_solution || best_solution == -1){
				best_solution = solution;
				best_horario = horario;
				cout << "Current best solution: " << best_solution << "\n";
			}

		}

		double total_duration = (clock() - start ) / (double) CLOCKS_PER_SEC;	

		cout<<"\nTiempo de ejecucion: "<< total_duration << "[seg]" <<'\n';

		cout << "Mejor solucion encontrada: " << best_solution << "\n";

		archive_out(turn_shifts, staff_list, cover_list, Horizon, castigos,best_horario);
		logs(file_name,restarts,numero_vecinos,numero_vecindarios,best_solution,total_duration);

	}

    return 0;
}