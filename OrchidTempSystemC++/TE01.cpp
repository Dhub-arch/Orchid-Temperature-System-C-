#include<iostream> //use for input and output
#include<fstream> // use to read and write a file
#include <string> // use to handle strings
#include <vector> // use to  store and mange collection of elements
#include <sstream> //use for input and output in a string
using namespace std;

void inputTemperature();
void displayTemperature();
void dailyTemperatureFluctuation();
void monthlyAverageTemperatureFluctuation();
void monthlyAverageDayNightTemperatures();
void convertCentigradeToFahrenheit();
void maxMinTemperature();
void temperatureSuitability();
float no1, no2;

int main() {
    int option;
    do {
    	cout <<endl;
        cout << " MAIN MENU"<<endl;
        cout << "    1. Input Temperature for 30DAYS"<<endl;
        cout << "    2. Display Saved Temperature"<<endl;
        cout << "    3. Daily Temperature Fluctuation"<<endl;
        cout << "    4. Monthly Average Temperature Fluctuation"<<endl;
        cout << "    5. Monthly Average DAY and NIGHT Temperatures"<<endl;;
        cout << "    6. Convert Centigrade to Fahrenheit"<<endl;
        cout << "    7. Maximum and Minimum Temperature"<<endl;
        cout << "    8. Temperature Suitability"<<endl;
        cout << "    9. Exit"<<endl<<endl;
        cout << "Choose an option: ";
        cin >> option;

        switch(option) { //funtions of the system
            case 1: inputTemperature(); break;
            case 2: displayTemperature(); break;
            case 3: dailyTemperatureFluctuation(); break;
            case 4: monthlyAverageTemperatureFluctuation(); break;
            case 5: monthlyAverageDayNightTemperatures(); break;
            case 6: convertCentigradeToFahrenheit(); break;
            case 7: maxMinTemperature(); break;
            case 8: temperatureSuitability(); break;
            case 9: cout << "Exiting program"<<endl; break;
            default: cout << "Invaild Option, please enter number between 1 and 9";
        }
    } while(option != 9);

    return 0;
}
void inputTemperature() {

    ofstream out;
	out.open("SAVE.txt"); //open file
	if(!out){
		cout<<"ERROR! Unable to open file"<<endl;
		}
	
	for (int day = 1; day <= 30; ++day){
		float DT, NT;
		cout <<"     Enter day "<<day<< " temprature: ";
    	cin >> DT;
    	cout <<"     Enter Night "<<day<< " temperature: ";
    	cin >> NT;
    	cout<<endl;
    	
    	out<<"DAY "<< day <<" DAY TEMPERATURE: "<<DT<<endl;//DT represent Day time
		out<<"DAY "<< day <<" NIGHT TEMPERATURE: "<<NT<<endl;//NT represent Night Time
	}
	out.close(); 
}
void displayTemperature() {
    ifstream in("SAVE.txt");
    if (!in) {
        cerr << "ERROR: Unable to open file!" << endl;
        return;
    }

    string data; //loop to read all the lines in the  file
    while (getline(in, data)) {
        cout << data << endl;
    }

    in.close(); 
}
void dailyTemperatureFluctuation() {
    float HT, LT, fluctuation;//HT and LT represent highhest time and lowest time
    cout << "Enter the highest temperature of the day: ";
    cin >> HT;
    cout << "Enter the lowest temperature of the day: ";
    cin >> LT;
    fluctuation = HT - LT;
    cout << "The daily temperature fluctuation is: " << fluctuation << " degrees." << endl;
    return ;
}
void monthlyAverageTemperatureFluctuation() {
    ifstream in("SAVE.txt"); 
    if (!in) { //logical NOT(!)
        cerr << "ERROR: Unable to open file!" << endl;
        return;
    }
    string data;
    vector<float> DT, NT;//DT= day time and NT night time
    while (getline(in, data)) {
        if (data.find("DAY TEMPERATURE") != string::npos) {
            string tempStr = data.substr(data.find(":") + 1);
            stringstream ss(tempStr);
            float temp;
            ss >> temp;
            DT.push_back(temp);
        } else if (data.find("NIGHT TEMPERATURE") != string::npos) {
            string tempStr = data.substr(data.find(":") + 1);
            stringstream ss(tempStr);
            float temp;
            ss >> temp;
            NT.push_back(temp);
        }
    }
    in.close(); 
    float totalFluctuation = 0;
    for (size_t i = 0; i < DT.size(); ++i) {
        float fluctuation = DT[i] - NT[i];
        totalFluctuation += fluctuation;
    }
    float averageFluctuation = totalFluctuation / DT.size();
    cout << "Monthly Average Temperature Fluctuation: " << averageFluctuation << "°C" << endl;
}
void monthlyAverageDayNightTemperatures() {
    ifstream in("SAVE.txt");  
    if (!in) {
        cerr << "ERROR: Unable to open file!" << endl;
        return;
    }
    string line;
    vector<float> DT, NT;//DT= day time and NT night time
    while (getline(in, line)) {
        if (line.find("DAY TEMPERATURE") != string::npos) {
            string tempStr = line.substr(line.find(":") + 1);
            stringstream ss(tempStr);
            float temp;
            ss >> temp;
            DT.push_back(temp);
        } else if (line.find("NIGHT TEMPERATURE") != string::npos) {
            string tempStr = line.substr(line.find(":") + 1);
            stringstream ss(tempStr);
            float temp;
            ss >> temp;
            NT.push_back(temp);
        }
    }
    in.close();  
    float TDT = 0, TNT = 0;
    for (size_t i = 0; i < DT.size(); ++i) {
        TDT += DT[i];
        TNT += NT[i];
    }
    float avgDT = TDT / DT.size();
    float avgNT = TNT / NT.size();

    cout << "Monthly Average Day Temperature: " << avgDT << "°C" << endl;
    cout << "Monthly Average Night Temperature: " << avgNT << "°C" << endl;
}
void convertCentigradeToFahrenheit() {
    float C, F;//c=celcius and F=Fahrenheit
    cout << "Enter temperature in Celsius: ";
    cin >> C;
    F = (C * 9.0 / 5.0) + 32;
    cout << "Temperature in Fahrenheit: " << F << "°F" << endl;
}
void maxMinTemperature() {
    {
    ifstream in("SAVE.txt");  
    if (!in) {
        cerr << "ERROR: Unable to open file!" << endl;
        return;
    }
    string line;
    vector<float> temperatures;
    while (getline(in, line)) {
        if (line.find("DAY TEMPERATURE") != string::npos || line.find("NIGHT TEMPERATURE") != string::npos) {
            string tempStr = line.substr(line.find(":") + 1);
            stringstream ss(tempStr);
            float temp;
            ss >> temp;
            temperatures.push_back(temp);
        }
    }
    in.close(); 
    float maxT = temperatures[0];
    float minT = temperatures[0];

    for (size_t i = 1; i < temperatures.size(); ++i) {
        if (temperatures[i] > maxT) {
            maxT = temperatures[i];
        }
        if (temperatures[i] < minT) {
            minT = temperatures[i];
        }
    }
    cout << "Maximum Temperature: " << maxT << "°C" << endl;
    cout << "Minimum Temperature: " << minT << "°C" << endl;
	}
}

void temperatureSuitability() {
    float DT, NT;
    cout << "Enter daytime temperature in Fahrenheit: ";
    cin >> DT;
    cout << "Enter nighttime temperature in Fahrenheit: ";
    cin >> NT;
    cout << endl;
    
    float fluctuation = DT - NT;//DT= day time and NT night time
    if (NT >= 60 && NT <= 62 && //&&mean logical AND both inputs must be true
        DT >= 70 && DT <= 80 && 
        fluctuation >= 10 && fluctuation <= 15) {
        cout << "suitable for orchid plants to flower." <<endl;
    } else if (NT >= 55 && NT < 60 && 
               DT >= 70 && DT <= 80) {
        cout << "suitable for orchid plants to grow healthy leaves but will not flower." << endl;
    } else {
        cout << " not suitable for orchid plants." <<endl;
    }
return ;

}


 
