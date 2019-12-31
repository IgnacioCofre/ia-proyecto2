#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <regex>

using namespace std;
 
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
		
		/*	Iteracion sobre lineas de texto en lista */

		// list<string>::iterator line;
		// for(line = list_aux.begin(); line !=list_aux.end(); line++)
		// {
		// 	cout<< *line <<"\n";
		// }

		/* Parseo de datos sobre la lista auxiliar*/

		string HORIZON = "SECTION_HORIZON";
		string SHIFTS = "SECTION_SHIFTS";
		string STAFF = "SECTION_STAFF";
		string DAY_OFF = "SECTION_DAY_OFF";
		string SHIFT_ON_REQUESTS = "SECTION_SHIFT_ON_REQUESTS";
		string SHIFT_OFF_REQUESTS = "SECTION_SHIFT_OFF_REQUESTS";
		string COVER = "SECTION_COVER";

		int Horizon;
		list<string> Shifts_list;
		list<string> Staff_list;
		list<string> Days_off_list;
		list<string> Shift_on_request_list;
		list<string> Shift_off_request_list;
		list<string> Cover_list;
		list<string>::iterator line;

		for(line = list_aux.begin(); *line != SHIFTS; line++)
		{
			Horizon = std::stoi(*line);
		}
		
	}

    return 0;
}