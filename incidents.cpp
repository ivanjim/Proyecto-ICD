//============================================================================
// Name        : incidents.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <map>
#include <cstdlib>

using namespace std;

#define FILE_PATH "C:/Users/2ivan/Desktop/Haciendo/MongoDB/datos.csv"
#define INTERVAL 50000

vector<string> split(const string &l, const string &d) {

	auto *line = new char[l.length() + 1];
	strcpy(line, l.c_str());

	auto *del = new char[d.length() + 1];
	strcpy(del, d.c_str());

	vector<string> words;

	char *word = strtok(line, del);

	while (word != nullptr) {

		words.emplace_back(word);
		word = strtok(nullptr, del);
	}

	return words;
}

vector<string> split_csv(const string &l) {
	return split(l, ";");
}

int getMonth(const string &date) {
	vector<string> fecha = split(date, " /");
	auto *c = new char[fecha[0].length() + 1];
	strcpy(c, fecha[0].c_str());

	// index be in 0-11 not to 1-12
	return atoi(c) - 1;
}

/**
 * Get the day of week with more incidents and the number of incidents.
 * @return
 */
pair<string, unsigned> getDayWithMoreIncidents() {

	ifstream file;
	string line;

	string day;
	unsigned cont = 0;

	vector<string> columns;
	map<string, unsigned> daysWithMoreIncidents;

	pair<string, unsigned> dayWithMoreIncidents = pair<string, unsigned>(
			"Unkown", 0);

	// Read file from path.
	file.open(FILE_PATH, ios::in);

	// Check if the file is opened
	if (!file.is_open()) {
		return dayWithMoreIncidents;
	}

	// Delete headers.
	getline(file, line);

	cout << "Solving" << flush;

	// While the file has lines
	while (!file.eof()) {
		cont++;

		// Get next line
		getline(file, line);

		// Check if the line is not empty
		if (!line.empty()) {

			// Get all columns from line
			columns = split_csv(line);

			// Save the day of incident
			day = columns[3];

			// If we can add the new register, added else increment the count of value in one more
			if (!daysWithMoreIncidents.insert(pair<string, unsigned>(day, 1)).second) {
				daysWithMoreIncidents[day] += 1;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	// Get the day with more incidents
	if (!daysWithMoreIncidents.empty()) {

		for (auto &current : daysWithMoreIncidents) {

			if (current.second > dayWithMoreIncidents.second) {
				dayWithMoreIncidents.first = current.first;
				dayWithMoreIncidents.second = current.second;
			}
		}

	}

	return dayWithMoreIncidents;
}
;

/**
 * Get the category of incidents most frequent and the number of incidents.
 * @return
 */
pair<string, unsigned> getMostCommittedIncident() {

	ifstream file;
	string line;
	unsigned cont = 0;

	string category;

	vector<string> columns;
	map<string, unsigned> mostCommittedIncidents;

	pair<string, unsigned> mostCommittedIncident = pair<string, unsigned>(
			"Unkown", 0);

	// Read file from path.
	file.open(FILE_PATH, ios::in);

	// Check if the file is opened
	if (!file.is_open()) {
		return mostCommittedIncident;
	}

	// Delete headers.
	getline(file, line);

	cout << "Solving" << flush;
	// While the file has lines
	while (!file.eof()) {
		cont++;

		// Get next line
		getline(file, line);

		// Check if the line is not empty
		if (!line.empty()) {

			// Get all columns from line
			columns = split_csv(line);

			// Save the category of incident
			category = columns[1];

			// If we can add the new register, added else increment the count of value in one more
			if (!mostCommittedIncidents.insert(
					pair<string, unsigned>(category, 1)).second) {
				mostCommittedIncidents[category] += 1;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	// Get the category with more incidents
	if (!mostCommittedIncidents.empty()) {

		for (auto &current : mostCommittedIncidents) {

			if (current.second > mostCommittedIncident.second) {
				mostCommittedIncident.first = current.first;
				mostCommittedIncident.second = current.second;
			}
		}

	}

	return mostCommittedIncident;
}

/*
 *Obtener el numero de incidentes en una zona determinada de la ciudad.
 */
int getCountIncidentsByZone(string district) {
	cout << "Obtener el número de incidentes en un distrito concreto." << endl;

	string line = "";
	ifstream file;
	string delimiter = ";";
	vector<string> columns;
	string pdDistrict;
	int count = 0;
	unsigned cont = 0;

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return count;
	}

	cout << "Solving";
	cout.flush();

	getline(file, line); // para eliminar las cabeceras

	while (!file.eof()) {
		cont++;
		getline(file, line);
		columns = split_csv(line);

		if (!line.empty()) {

			pdDistrict = columns[6];

			if (pdDistrict.compare(district) == 0) {
				count++;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	file.close();

	return count;
}

/*
 *Obtener los incidentes a partir de una determinada fecha y una zona
 */

bool validarFecha(string date) {
	bool ok = true;
	string month = date.substr(0, 2);
	string day = date.substr(3, 2);
	string year = date.substr(6, 4);

	if (month.size() > 2 || month.size() < 2 || month > "12" || month < "01") {
		ok = false;
	}

	if (day.size() > 2 || day.size() < 2 || day > "31" || day < "01") {
		ok = false;
	}

	if (year.size() > 4 || year.size() < 4) {
		ok = false;
	}

	return ok;
}

void getIncidentsByDateAndZone(string date, string district) {
	cout << "Obtener los incidentes a partir de una fecha y una zona." << endl;

	string line = "";
	ifstream file;
	string delimiter = ";";
	vector<string> columns;
	string pdDistrict;
	string date_csv;
	unsigned cont = 0;

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return;
	}

	cout << "Solving" << endl;
	cout.flush();

	getline(file, line); // para eliminar las cabeceras

	if (validarFecha(date)) {
		while (!file.eof()) {
			cont++;
			getline(file, line);
			columns = split_csv(line);

			if (!line.empty()) {

				pdDistrict = columns[6];
				date_csv = columns[4];

				string finalDate = date_csv.substr(0, 10);

				if (pdDistrict.compare(district) == 0
						&& finalDate.compare(date) > 0) {
					cout << columns[0] << " " << columns[1] << " " << columns[2]
							<< " " << columns[4] << " " << columns[6] << endl;
				}

				if ((cont % INTERVAL) == 0) {
					cout << ".";
					cout.flush();
				}
			}
		}
	} else {
		cout << "Error en el formato de la fecha (mm/dd/yyyy)." << endl;
	}

	cout << endl;

	file.close();

}

/**
 * Get the period with more incidents
 * @return
 */
pair<string, unsigned> getPeriodWithMoreIncidents() {
	string line;
	ifstream file;
	unsigned cont = 0;
	vector<string> columns;
	map<unsigned, unsigned> months;
	pair<string, unsigned> finalMonth = pair<string, unsigned>("Unkown", 0);
	string date;
	int current_month;

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return finalMonth;
	}

	getline(file, line); // para eliminar las cabeceras

	for (unsigned i = 0; i < 11; i++) {    // los 12 meses del aÃ±o
		months.insert(make_pair(i, 0));
	}

	cout << "Solving" << flush;

	while (!file.eof()) {
		cont++;

		getline(file, line);
		columns = split_csv(line);

		if (!line.empty()) {
			date = columns[4];

			current_month = getMonth(date); // current month va de 0 a 11

			months[current_month] += 1;

		}

		if ((cont % INTERVAL) == 0) {
			cout << ".";
			cout.flush();
		}
	}

	cout << endl;

	file.close();

	map<unsigned, unsigned>::iterator it;
	unsigned max_m = 0;

	for (it = months.begin(); it != months.end(); it++) {
		if (it->second > finalMonth.second) {
			finalMonth.second = it->second;
			max_m = it->first;
		}
	}

	vector<string> month_select = { "enero", "febrero", "marzo", "abril",
			"mayo", "junio", "julio", "agosto", "septiempre", "octubre",
			"noviembre", "diciembre" };

	finalMonth.first = month_select[max_m];

	return finalMonth;
}

/**
 * Get the district with more incidents
 * @return
 */
pair<string, unsigned> getDistrictWithMoreIncidents() {
	string line;
	ifstream file;
	vector<string> columns;
	map<string, unsigned> districts;
	unsigned cont = 0;
	string current;
	pair<string, unsigned> finalDistrict = pair<string, unsigned>("Unkown", 0);

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return finalDistrict;
	}

	// to remove headers
	getline(file, line);

	cout << "Solving" << flush;

	while (!file.eof()) {
		cont++;
		getline(file, line);

		columns = split_csv(line);

		if (!line.empty()) {

			current = columns[6];

			// if we can add the new register, added else increment the count of value in one more
			if (!districts.insert(make_pair(current, 1)).second) {
				districts[current] += 1;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	file.close();

	// get the district with more incidents

	if (!districts.empty()) {
		for (auto &d : districts) {
			if (d.second > finalDistrict.second) {
				finalDistrict.first = d.first;
				finalDistrict.second = d.second;
			}
		}

	}
	return finalDistrict;
}

// obtener el numero de delitos que han sido resueltos
void getIncidentsWithArrest() {

	string line;
	ifstream file;
	vector<string> columns;
	int arrests = 0; // numero de delitos con arresto
	string current;
	unsigned cont = 0;

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return;
	}

	cout << "Solving";
	cout.flush();
	getline(file, line); // para eliminar las cabeceras

	while (!file.eof()) {
		cont++;
		getline(file, line);

		columns = split_csv(line);

		if (!line.empty()) {

			current = columns[7];

			if (current.find("ARREST") == 0) {
				//cout << "resolution: " << current << endl;
				arrests++;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	file.close();

	cout << "\nNumber of resolved incidents: " << arrests << endl;

}

// obtener la resolución mas común
void getMostCommonResolutuion() {

	string line;
	ifstream file;
	vector<string> columns;
	map<string, unsigned> resolutions;//asocia cada resolución con su número de resoluciones del mismo tipo
	string current;
	unsigned cont = 0;

	file.open(FILE_PATH, ios::in);

	if (!file.is_open()) {
		return;
	}

	cout << "Solving";
	cout.flush();
	getline(file, line); // para eliminar las cabeceras

	while (!file.eof()) {
		cont++;
		getline(file, line);

		columns = split_csv(line);

		if (!line.empty()) {

			current = columns[7];

			// intenta insertar la clave, si no puede lo incrementa en 1
			if (!resolutions.insert(make_pair(current, 1)).second) {
				resolutions[current] += 1;
			}

			if ((cont % INTERVAL) == 0) {
				cout << ".";
				cout.flush();
			}
		}
	}

	cout << endl;

	file.close();

	string maxResolution;
	unsigned maxCount = 0;
	map<string, unsigned>::iterator iterator;

	for (iterator = resolutions.begin(); iterator != resolutions.end();
			iterator++) {

		//cout << it -> first << ": " << it->second << endl;
		if (iterator->second > maxCount) {
			maxCount = iterator->second;
			maxResolution = iterator->first;
		}
	}

	cout << "\nThe most common resolution is " << maxResolution << " ("
			<< maxCount << " times)." << endl;

}

int main() {

	// References times
	clock_t tt;
	clock_t t0;

	// Total execution time
	tt = clock();

	cout << "Executing getDayWithMoreIncidents..." << endl;

	// Execution time for that query
	t0 = clock();

	pair<string, unsigned> dayWithMoreIncidents = getDayWithMoreIncidents();

	cout << "\tThe day with more incidents is: " << dayWithMoreIncidents.first
			<< "." << endl;
	cout << "\tThe total of incidents are: " << dayWithMoreIncidents.second
			<< "." << endl;

	cout << "Execution time for getDayWithMoreIncidents: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getMostCommittedIncident..." << endl;

	t0 = clock();

	pair<string, unsigned> mostCommittedIncident = getMostCommittedIncident();

	cout << "\tThe most committed incident is: " << mostCommittedIncident.first
			<< "." << endl;
	cout << "\tThe total of incidents are: " << mostCommittedIncident.second
			<< "." << endl;

	cout << "Execution time for getMostCommittedIncident: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getCountIncidentsByZone..." << endl;

	// Execution time for that query
	t0 = clock();

	int total_incidents = getCountIncidentsByZone("CENTRAL");

	cout << "\tThe total of incidents are: " << total_incidents << "." << endl;

	cout << "Execution time for getCountIncidentsByZone: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getIncidentsByDateAndZone..." << endl;

	// Execution time for that query
	t0 = clock();

	getIncidentsByDateAndZone("10/19/2017", "CENTRAL");

	cout << "Execution time for getIncidentsByDateAndZone: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getPeriodWithMoreIncidents..." << endl;

	// Execution time for that query
	t0 = clock();

	pair<string, unsigned> month = getPeriodWithMoreIncidents();

	cout << "\tThe month with more incidents is: " << month.first << "."
			<< endl;
	cout << "\tThe total of incidents are: " << month.second << "." << endl;

	cout << "Execution time for getPeriodWithMoreIncidents: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getDistrictWithMoreIncidents..." << endl;

	// Execution time for that query
	t0 = clock();

	pair<string, unsigned> district = getDistrictWithMoreIncidents();

	cout << "\tThe district with more incidents is: " << district.first << "."
			<< endl;
	cout << "\tThe total of incidents are: " << district.second << "." << endl;

	cout << "Execution time for getDistrictWithMoreIncidents: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getIncidentsWithArrest..." << endl;

	// Execution time for that query
	t0 = clock();

	getIncidentsWithArrest();

	cout << "Execution time for getIncidentsWithArrest: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Executing getMostCommonResolutuion..." << endl;

	// Execution time for that query
	t0 = clock();

	/**
	 * Con esta comprobación queremos representar como la mayoría de los delitos quedan sin resolver, que son bastantes.
	 */
	getMostCommonResolutuion();

	cout << "Execution time for getMostCommonResolutuion: "
			<< (double(clock() - t0) / CLOCKS_PER_SEC) << endl << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Total execution time: " << (double(clock() - tt) / CLOCKS_PER_SEC)
			<< endl;

	return 0;
}
