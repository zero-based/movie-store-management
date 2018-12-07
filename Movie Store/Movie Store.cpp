//MOVIE STORE PROJECT

/*/////////////////////////////////////////////////////////////////////////////
Please note the following:
	1] Set cmd layout width to 100 (right click on the title bar of the cmd
	   then choose properties > layout > screen buffer size > width > 100).
	2] Go to line 82 and 83 then change "USERNAME" to your computer's name. 
/////////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#define CAPACITY 10000
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

/*     Structs     */
struct Date {
	int day;
	int month;
	int year;
};

struct Customer {
	string name;
	string phoneNumber;
}AllCustomers[CAPACITY];

struct Movie {
	string name;
	int productionYear;
	float fees;
	float overdueFees;
	int numberOfRents = 0;
	int numberOfRates = 0;
	float rating = 0;
	bool isRented = false;
}AllMovies[CAPACITY];

struct Rent {
	Customer rentingCustomerData;
	Movie rentedMovieData;
	int numberOfRentingDays;
	Date rentDate;
	Date dueDate;
}RentedMovie, AllRentedMovies[CAPACITY];

struct Receive {
	Customer rentingCustomerData;
	Movie receivedMovieData;
	Date rentDate;
	Date dueDate;
	Date receiveDate;
	bool status = false;
	float totalFees = 0.0;
}ReceivedMovie, AllReceivedMovies[CAPACITY];



/*     File declaration     */
fstream customersFile;
fstream moviesFile;
fstream rentFile;
fstream receiveFile;
fstream passwordFile;
fstream logsFile;
fstream rentPrint;
fstream recevieprint;

/*     File paths     */
char customersFilePath[]    = "Customers.csv";
char moviesFilePath[]       = "Movies.csv";
char rentFilePath[]         = "Renting.csv";
char receiveFilePath[]      = "Receive.csv";
char passwordFilePath[]     = "Password.txt";
char logsFilePath[]         = "Logs.csv";
char rentPrintFilePath[]    = "C:\\Users\\USERNAME\\Desktop\\Rent Print.doc";         //IMPORTANAT: put your computer's user name instead of "USERNAME"
char receviePrintFilePath[] = "C:\\Users\\USERNAME\\Desktop\\Recevie Print.doc";	  //IMPORTANAT: put your computer's user name instead of "USERNAME"


/*     Customers functions' prototype     */
void addNewCustomer();
void sortCutomersFile();
void listAllCustomers();
void listOverdueCustomers();
void stringValidation(string &name);


/*     Movies functions' prototype     */
void saveNewMovieToFile(Movie movie);
void addMovie();
void sortMovieFile();
void listAllMovies();
void listAllRentedMovies();
void sortTopRated();
void sortMostRented();
void rateAMovie();
void searchMovie();
void deleteMovieFromFile();
void replaceAllMoviesFile(Movie movies[], int size);


/*     Rent functions' prototype     */
void rent();
int  searchingForMovie(string searchMovieName);
int  searchingForCustomer(string customrphonenumber);
bool isMovieRented(string moviename);
void collectRentedMovieData(string customerphoneNumber, string movieName, int numberOfDueDays);
void displayRentingData(Rent RentedMovie);
void exportRentigData(Rent RentedMovie);
void switchisRentedAndIncrementNumberOfRents(Rent RentedMovie);
void uploadToRentPrintFile(Rent RentedMovie);


/*     Receive functions' prototype     */
void  receive();
bool  isOverdue(Receive data);
float calculateTotalFees(Receive data);
void  displayReceivedMovieData(Receive data);
void  exportRecievedMovieData(Receive data);
void  removeMovieFromRentFile(int size, int skipedIndex);
void  switchisRentedAfterReceivingMovie(string returnedMovie);
void  uploadToReceivePrintFile(Receive data);


/*     Admin functions' prototype     */
void resetAllData();
void monthlyIncome();
void enterPasswordWithoutEcho(char enteredPassword[]);
string encryptEnteredPassword(char enteredPassword[]);
string loadPasswordFile();
void savePasswordToFile(string password);
void createPasswordFile();
bool loginProcess();
void exportTologsFile();


/*     Menues functions' prototype     */
void splashScreen();
void mainMenu();
void customerMenu();
void movieMenu();
void adminMenu();




/////////// Main Function ///////////
void main() {
	splashScreen();
	mainMenu();
}
////////////////////////////////////




/////// Menues functions' Definition ///////

void splashScreen() {

	cout << endl
		 << endl
		 << endl
		 << "                                     __  __            _      	  "   << endl;
		 Sleep(100);				           
		 Beep(2000, 300);			           
	cout << "                                    |  \\/  |          (_)         " << endl;
		 Sleep(100);				           
		 Beep(1800, 300);			           
	cout << "                                    | \\  / | _____   ___  ___  "    << endl;
		 Sleep(100);				           
		 Beep(1600, 300);			           
	cout << "                                    | |\\/| |/ _ \\ \\ / / |/ _ \\ " << endl;
		 Sleep(100);				           
		 Beep(1400, 300);			           
	cout << "                                    | |  | | (_) \\ V /| |  __/	" << endl;
		 Sleep(100);				           
		 Beep(1200, 300);			           
	cout << "                                    |_|__|_|\\___/ \\_/ |_|\\___|  " << endl;
		 Sleep(100);				           
		 Beep(1000, 300);			           
	cout << "                                     / ____| |                	  "   << endl;
		 Sleep(100);				           
		 Beep(800, 300);			           
	cout << "                                    | (___ | |_ ___  _ __ ___ 	  "   << endl;
		 Sleep(100);				           
		 Beep(600, 300);			           
	cout << "                                     \\___ \\| __/ _ \\| '__/ _ \\ " << endl;
		 Sleep(100);				           
		 Beep(400, 300);			           
	cout << "                                     ____) | || (_) | | |  __/	  "   << endl;
		 Sleep(100);				           
		 Beep(200, 300);			           
	cout << "                                    |_____/ \\__\\___/|_|  \\___|  " << endl;
		 Sleep(100);				           
		 Beep(20000, 300);			           
	cout << "                                                                   " << endl;
	cout << "                                    B Y   M 3 L E S H Y - 2018     " << endl;
	cout << endl
		 << endl
		 << endl;

		 Sleep(2000);
		 system("cls");

}

void mainMenu() {

	cout << endl
		 << "  1  Customers' issues"      << endl
		 << "  2  Movies' issues"         << endl
		 << "  3  Rent a movie"           << endl
		 << "  4  Receive a movie"        << endl
		 << "  5  Admin panel"            << endl
		 << "  0  Exit"                   << endl<<endl
		 << "  X  Shut down the computer" << endl
		 << endl << endl;

	string choice;
	cout << "  Enter your choice: ";
	getline(cin, choice);
	
	if (choice.length() > 1)
		choice = "wrong answer";


	switch (choice[0]) {

	case '1': {
				  system("cls");
				  customerMenu();
				  break;
	}

	case '2': {
				  system("cls");
				  movieMenu();
				  break;
	}

	case '3': {
				  system("cls");
				  rent();
				  break;
	}

	case '4': {
				  system("cls");
				  receive();
				  break;
	}

	case '5': {
				  system("cls");
				  if (loginProcess()) {
					  Sleep(800);
					  system("cls");
					  adminMenu();
					  break;
				  }
				  else {
					  exportTologsFile();
					  system("exit");
					  break;
				  }
	}

	case '0': {
				  system("cls");
				  splashScreen();
				  system("exit");
				  break;
			
	}

	case 'x':
	case 'X': {
				  char key;
				  while (true) {
					  cout << "\n  Are you sure? <y/n>: ";
					  cin >> key;

					  if (key == 'y' || key == 'Y') {
						  system("cls");
						  splashScreen();
						  cout << "\n\n  GOOD BYE :) " << endl;
						  system("c:\\windows\\system32\\shutdown /s");
						  Sleep(10000);
						  system("exit");

					  }
					  else if (key == 'n' || key == 'N') {
						  system("cls");
						  mainMenu();
					  }
					  else{
						  cout << "Please enter <y/n>\n";
						  Sleep(1000);
					  }
				  }
	}


	default: {
				 cout << "  Please concentrate, Enter A valid charachter!\n";
				 Sleep(1000);
				 system("cls");
				 mainMenu();
				 break;
	}

	}

}

void customerMenu() {

	cout << endl
		 << "  1  Add a new customer"     << endl
		 << "  2  List all customers"     << endl
		 << "  3  List overdue customers" << endl << endl
		 << "  0  Main Menu"              << endl << endl
		 << endl;

	string choice;
	cout << "  Enter your choice: ";
	getline(cin, choice);

	if (choice.length() > 1)
		choice = "wrong answer";

	switch (choice[0]) {

	case '1': {

				  system("cls");
				  addNewCustomer();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  customerMenu();
				  break;
	}

	case '2': {
				  system("cls");
				  if (loginProcess()) {
					  Sleep(800);
					  system("cls");
					  listAllCustomers();
					  cout << "\nPress any key to continue";
					  if (char x = _getch()) system("cls");
					  customerMenu();
					  break;
				  }
				  else {
					  exportTologsFile();
					  system("cls");
					  customerMenu();
					  break;
				  }
	}

	case '3': {
				  system("cls");
				  listOverdueCustomers();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  customerMenu();
				  break;
	}

	case '0': {
				  system("cls");
				  mainMenu();
				  break;
	}

	default: {
				 cout << "  Please concentrate, Enter A valid charachter!\n";
				 Sleep(1000);
				 system("cls");
				 customerMenu();
				 break;
	}

	}

}

void movieMenu() {

	cout << endl
		 << "  1  Add a new movie"        << endl
		 << "  2  List all movies"        << endl
		 << "  3  List all rented movies" << endl
		 << "  4  List top rated"         << endl
		 << "  5  List most rented"       << endl
		 << "  6  Rate a movie"           << endl
		 << "  7  Search for a movie"     << endl
		 << "  8  Delete a movie"         << endl << endl
		 << "  0  Main Menu"              << endl << endl
		 << endl;				     

	string choice;
	cout << "  Enter your choice: ";
	getline(cin, choice);

	if (choice.length() > 1)
		choice = "wrong answer";

	switch (choice[0]) {

	case '1': {
				  system("cls");
				  addMovie();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '2': {
				  system("cls");
				  listAllMovies();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '3': {
				  system("cls");
				  listAllRentedMovies();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '4': {
				  system("cls");
				  sortTopRated();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '5': {
				  system("cls");
				  sortMostRented();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '6': {
				  system("cls");
				  rateAMovie();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '7': {
				  system("cls");
				  searchMovie();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '8': {
				  system("cls");
				  deleteMovieFromFile();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  movieMenu();
				  break;
	}

	case '0': {
				  system("cls");
				  mainMenu();
				  break;
	}

	default: {
				 cout << "  Please concentrate, Enter A valid charachter!\n";
				 Sleep(1000);
				 system("cls");
				 movieMenu();
				 break;
	}

	}

}

void adminMenu() {

	cout << endl
		 << "  1  Monthly Income" << endl
		 << "  2  Reset All Data" << endl
		 << "  3  Reset Password" << endl << endl
		 << "  0  Main Menu"      << endl << endl
		 << endl;

	string choice;
	cout << "  Enter your choice: ";
	getline(cin, choice);

	if (choice.length() > 1)
		choice = "wrong answer";

	switch (choice[0]) {

	case '1': {
				  system("cls");
				  monthlyIncome();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  adminMenu();
				  break;
	}

	case '2': {
				  system("cls");

				  resetAllData();
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  adminMenu();
				  break;
	}

	case '3': {
				  system("cls");
				  char newPassword[50];
				  cout << "Please enter your new Password: ";
				  enterPasswordWithoutEcho(newPassword);
				  remove(passwordFilePath);
				  savePasswordToFile(encryptEnteredPassword(newPassword));
				  cout << "\nNew password Saved!\n";
				  cout << "\nPress any key to continue";
				  if (char x = _getch()) system("cls");
				  adminMenu();
				  break;
	}


	case '0': {
				  system("cls");
				  mainMenu();
				  break;
	}

	default: {

				 cout << "  Please concentrate, Enter A valid charachter!\n";
				 Sleep(1000);
				 system("cls");
				 adminMenu();
				 break;
	}

	}

}

/////////////////////////////////////////////////////////////////////




////////////////// Customers functions' Definition //////////////////

//add customer
void addNewCustomer() {

	Customer newCustomer;

	//Customer's name entering: doesn't allow "\n"
	bool isNameValid;

	do{
		isNameValid = true;
		cout << "Enter customer's name: ";
		getline(cin, newCustomer.name);
		stringValidation(newCustomer.name);

		if (newCustomer.name == ""){
			isNameValid = false;
			Beep(1500, 500);
			cout << "Enter a valid name!\n";
			Sleep(1500);

			//clearing screen
			system("cls");
		}

	} while (isNameValid == false);


	//Customer's phone number entering: doesn't allow already existing phone numbers and doesn't allow "\n"
	bool isPhoneNumberValid;
	do{
		isPhoneNumberValid = true;
		cout << "Enter customer's phone number: ";
		getline(cin, newCustomer.phoneNumber);
		stringValidation(newCustomer.phoneNumber);

		for (int i = 0; i < 11; i++){
			if (newCustomer.phoneNumber[i] > '9' || newCustomer.phoneNumber[i] < '0' || newCustomer.phoneNumber.length() != 11){
				isPhoneNumberValid = false;
				Beep(1500, 500);
				cout << "Phone number must be 11 Numbers only!";
				Sleep(1500);

				//clearing screen
				COORD coord; // coordinates
				for (int y = 1; y <= 2; y++){
					coord.X = 0;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
					for (int x = 0; x <= 70; x++){
						cout << " ";
					}
				}

				coord.X = 0;
				coord.Y = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				break;
			}

			int customerIndex = searchingForCustomer(newCustomer.phoneNumber);

			if (customerIndex != -1 && isPhoneNumberValid){
				isPhoneNumberValid = false;
				Beep(1500, 500);
				cout << "Customer already exists!";
				Sleep(1500);
				system("cls");
				customerMenu();
			}

		}

	} while (isPhoneNumberValid == false);

	customersFile.open(customersFilePath, ios::out | ios::app);

	customersFile << newCustomer.name        << ","
				  << newCustomer.phoneNumber << '\n';

	customersFile.close();

	sortCutomersFile();

	cout << endl << "Customer is added Successfully..." << endl << endl;

	char key;
	while (true) {
		cout << "\nDo you want to add another customer? <y/n>: ";
		cin >> key;
		cin.ignore();
		if (key == 'y' || key == 'Y') {
			system("cls");
			addNewCustomer();
		}
		else if (key == 'n' || key == 'N') {
			system("cls");
			customerMenu();
			break;
		}
		else
			cout << "Please enter <y/n>\n";
	}

}

//sort customers inside the file alphabetically
void sortCutomersFile() {

	int i = 0;

	customersFile.open(customersFilePath);
	while (!customersFile.eof()) {
		string name;
		getline(customersFile, name, ',');
		if (name == "") break;
		AllCustomers[i].name = (name);

		string phonenumber;
		getline(customersFile, phonenumber, '\n');
		AllCustomers[i].phoneNumber = (phonenumber);

		i++;
	}
	customersFile.close();

	Customer temp;

	for (int x = 0; x <= i; x++) {
		for (int j = 0; j < i - 1; j++) {
			if (AllCustomers[j].name > AllCustomers[j + 1].name) {
				temp = AllCustomers[j];
				AllCustomers[j] = AllCustomers[j + 1];
				AllCustomers[j + 1] = temp;
			}
		}
	}

	customersFile.open(customersFilePath, ios::out);

	for (int j = 0; j < i; j++){
		customersFile << AllCustomers[j].name        << ','
			          << AllCustomers[j].phoneNumber << '\n';

	}

	customersFile.close();
}

//display data of all customers
void listAllCustomers(){
	
	cout << "\n------------------------------------------\n"
		 << setw(25) << left << "Customer Name"
		 << setw(20) << left << "Phone Number"
		 << "\n------------------------------------------\n";

	customersFile.open(customersFilePath);
	while (!customersFile.eof()) {
		string name;
		getline(customersFile, name, ',');
		if (name == "") break;

		string phoneNumber;
		getline(customersFile, phoneNumber, '\n');

		cout << setw(25) << left << name
		     << setw(20) << left << phoneNumber
		     << endl;
	}

	customersFile.close();
	cout << endl;

}

//list all Overdue customer
void listOverdueCustomers(){

	cout << "\n-------------------------------------------------------------------------------------------------\n"
  		 << setw(25) << left << "Name"	
		 << setw(20) << left << "Phone Number"							   							   
		 << setw(30) << left << "Movie Name"							   
		 << setw(15) << left << "Due Date"								   
		 << "\n-------------------------------------------------------------------------------------------------\n";
						
	time_t systemDateInSeconds = time(NULL);
	struct tm todayDate = *localtime(&systemDateInSeconds);

	rentFile.open(rentFilePath);
	while (!rentFile.eof())
	{
		string phoneNumber;
		getline(rentFile, phoneNumber, ',');
		if (phoneNumber == "") break;

		string name;
		getline(rentFile, name, ',');

		string movieName;
		getline(rentFile, movieName, ',');

		string fees;
		getline(rentFile, fees, ',');

		string overDueFees;
		getline(rentFile, overDueFees, ',');

		string rentingDay;
		getline(rentFile, rentingDay, '/');
		string rentingMonth;
		getline(rentFile, rentingMonth, '/');
		string rentingYear;
		getline(rentFile, rentingYear, ',');

		string dueDay;
		getline(rentFile, dueDay, '/');
		string dueMonth;
		getline(rentFile, dueMonth, '/');
		string dueYear;
		getline(rentFile, dueYear, '\n');

		bool isOverDue = false;

		if (stoi(dueYear) < todayDate.tm_year + 1900) {
			isOverDue = true;
		}
		else {
			if (stoi(dueMonth) < todayDate.tm_mon + 1 && stoi(dueYear) == todayDate.tm_year + 1900) {
				isOverDue = true;
			}
			else {
				if (stoi(dueDay) < todayDate.tm_mday && stoi(dueMonth) == todayDate.tm_mon + 1 && stoi(dueYear) == todayDate.tm_year + 1900)
					isOverDue = true;
			}
		}

		string dueDate;
		dueDate = dueDay + '/' + dueMonth + '/' + dueYear;

		if (isOverDue)
		{
			cout << setw(25) << left << name
				 << setw(20) << left << phoneNumber
				 << setw(30) << left << movieName
				 << setw(15) << left << dueDate
				 << endl;
		}
	}

	rentFile.close();
	cout << endl;

}

//Capitalizing first letter of every word in a Movie name
void stringValidation(string &name){

	//capitalizing
	transform(name.begin(), name.end(), name.begin(), tolower);
	name[0] = toupper(name[0]);

	for (int i = 1; i < (int)name.length(); i++)
	{
		if (name[i - 1] == ' ')
			name[i] = toupper(name[i]);
	}

	//removing all spaces
	name.erase(remove_if(name.begin(), name.end(), isspace), name.end());

	//adding spaces between words, number & symbols
	for (int i = 0; i < (int)name.length(); i++)
	{
		if ((name[i] >= 'a' && name[i] <= 'z') && (name[i + 1] >= 'A' && name[i + 1] <= 'Z')){
			name.insert(i + 1, " ");
		}
		else if ((name[i] >= 33 && name[i] <= 64) && (name[i + 1] >= 'A' && name[i + 1] <= 'Z')){
			name.insert(i + 1, " ");
		}
		else if ((name[i] >= 'a' && name[i] <= 'z') && (name[i + 1] >= 33 && name[i + 1] <= 64)){
			name.insert(i + 1, " ");
		}
		else if ((name[i] >= 'A' && name[i] <= 'Z') && (name[i + 1] >= 'A' && name[i + 1] <= 'Z')){
			name.insert(i + 1, " ");
		}

	}

}

/////////////////////////////////////////////////////////////////////




/////////////////// Movies functions' Definition ///////////////////

//save new movie
void saveNewMovieToFile(Movie movie) {

	moviesFile.open(moviesFilePath, ios::out | ios::app);

	moviesFile << movie.name           << ","
			   << movie.productionYear << ","
			   << movie.fees           << ","
			   << movie.overdueFees    << ","
			   << movie.numberOfRents  << ","
			   << movie.numberOfRates  << ","
			   << movie.rating         << ","
			   << movie.isRented       << "\n";

	moviesFile.close();

}

//let the user add a new movie to his file
void addMovie() {

	Movie newMovie;

	system("cls");

	//Movie's name entering: doesn't allow already existing movies and doesn't allow "\n" or "  "
	bool isNameValid;

	do{
		isNameValid = true;
		cout << "Enter movie's name: ";
		getline(cin, newMovie.name);
		stringValidation(newMovie.name);

		if (newMovie.name == ""){
			isNameValid = false;
			Beep(1500, 500);
			cout << "Enter a valid name!\n";
			Sleep(1500);

			//clearing screen
			system("cls");
		}
		
		int movieIndex = searchingForMovie(newMovie.name);

		if (movieIndex != -1 && isNameValid){
			isNameValid = false;
			Beep(1500, 500);
			cout << "Movie already exists!";
			Sleep(1500);
			system("cls");
			movieMenu();
		}

	} while (isNameValid == false);


	//Production year entering: allow entering 4 numbers only
	bool isYearValid;
	string productionYear;

	do{
		isYearValid = true;
		cout << "Enter production year: ";
		getline(cin, productionYear);
		stringValidation(productionYear);

		for (int i = 0; i < 4; i++){
			if (productionYear[i] > '9' || productionYear[i] < '0' || productionYear.length() != 4){
				isYearValid = false;
				Beep(1500, 500);
				cout << "Production Year must be four Numbers only!\n";
				Sleep(1500);

				//clearing screen
				COORD coord; // coordinates
				for (int y = 1; y <= 2; y++){
					coord.X = 0;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
					for (int x = 0; x <= 70; x++){
						cout << " ";
					}
				}

				coord.X = 0;
				coord.Y = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				break;
			}
		}

		time_t systemDateInSeconds = time(NULL);
		struct tm currentDate = *localtime(&systemDateInSeconds);

		if (productionYear > to_string(currentDate.tm_year + 1900) && isYearValid){
			isYearValid = false;
			Beep(1500, 500);
			cout << "Production Year is bigger than current year!\n";
			Sleep(1500);

			//clearing screen
			COORD coord; // coordinates
			for (int y = 1; y <= 2; y++){
				coord.X = 0;
				coord.Y = y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
				for (int x = 0; x <= 70; x++){
					cout << " ";
				}
			}

			coord.X = 0;
			coord.Y = 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}

	} while (isYearValid == false);
	newMovie.productionYear = stoi(productionYear);


	//Fees entering: allow entering numbers and floating point only and doesn't allow "\n" or "  "
	bool isFeesValid;
	string fees;

	do{
		isFeesValid = true;
		cout << "Enter movie's fees: ";
		getline(cin, fees);
		stringValidation(fees);

		if (fees == ""){
			isFeesValid = false;
			Beep(1500, 500);
			cout << "Enter valid fees!\n";
			Sleep(1500);

			//clearing screen
			COORD coord; // coordinates
			for (int y = 2; y <= 3; y++){
				coord.X = 0;
				coord.Y = y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
				for (int x = 0; x <= 70; x++){
					cout << " ";
				}
			}

			coord.X = 0;
			coord.Y = 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			continue;
		}

		for (int i = 0; i < (int)fees.length(); i++){

			if (fees[i] > '9' || fees[i] < '0' && fees[i] != '.'){ //if the entered data is not numbers and is not a floating point then the fees is not valid
				isFeesValid = false;
				Beep(1500, 500);
				cout << "Fees must be Numbers only!\n";
				Sleep(1500);

				//clearing screen
				COORD coord; // coordinates
				for (int y = 2; y <= 3; y++){
					coord.X = 0;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
					for (int x = 0; x <= 70; x++){
						cout << " ";
					}
				}

				coord.X = 0;
				coord.Y = 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				break;
			}
		}

	} while (isFeesValid == false);
	newMovie.fees = stof(fees);


	//Overdue fees entering: allow entering numbers and floating point only and doesn't allow "\n" or "  "
	bool isOverdueFeesValid;
	string overduefees;

	do{
		isOverdueFeesValid = true;
		cout << "Enter overdue fees: ";
		getline(cin, overduefees);
		stringValidation(overduefees);

		if (overduefees == ""){
			isOverdueFeesValid = false;
			Beep(1500, 500);
			cout << "Enter valid overdue fees!\n";
			Sleep(1500);

			//clearing screen
			COORD coord; // coordinates
			for (int y = 3; y <= 4; y++){
				coord.X = 0;
				coord.Y = y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
				for (int x = 0; x <= 70; x++){
					cout << " ";
				}
			}

			coord.X = 0;
			coord.Y = 3;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			continue;
		}

		for (int i = 0; i < (int)overduefees.length(); i++){
			if (overduefees[i] > '9' || overduefees[i] < '0' && overduefees[i] != '.'){ //if the entered data is not numbers and is not a floating point then the overdue fees is not valid	
				isOverdueFeesValid = false;
				Beep(1500, 500);
				cout << "Overdue fees must be Numbers only!\n";
				Sleep(1500);

				//clearing screen
				COORD coord; // coordinates
				for (int y = 3; y <= 4; y++){
					coord.X = 0;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
					for (int x = 0; x <= 70; x++){
						cout << " ";
					}
				}

				coord.X = 0;
				coord.Y = 3;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				break;
			}
		}

	} while (isOverdueFeesValid == false);
	newMovie.overdueFees = stof(overduefees);

	saveNewMovieToFile(newMovie);
	sortMovieFile();
	cout << endl << "Movie is added Successfully..." << endl << endl;

	char key;
	while (true) {
		cout << "\nDo you want to add another movie? <y/n>: ";
		cin >> key;
		cin.ignore();
		if (key == 'y' || key == 'Y') {
			system("cls");
			addMovie();
		}
		else if (key == 'n' || key == 'N') {
			system("cls");
			movieMenu();
			break;
		}
		else
			cout << "Please enter <y/n>\n";
	}


}

//sort movies inside the file alphabetically
void sortMovieFile() {

	int i = 0;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);
		i++;
	}

	moviesFile.close();

	Movie temp;

	for (int x = 0; x <= i; x++) {
		for (int j = 0; j < i - 1; j++) {
			if (AllMovies[j].name > AllMovies[j + 1].name) {
				temp = AllMovies[j];
				AllMovies[j] = AllMovies[j + 1];
				AllMovies[j + 1] = temp;
			}
		}
	}

	replaceAllMoviesFile(AllMovies, i);
}

//Show all movies on cmd
void listAllMovies() {

	cout << "\n----------------------------------------------------------------------------------------------\n"
		 << setw(30) << left << "Movie"
		 << setw(10) << left << "Prod."
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Overdue"
		 << setw(10) << left << "Rent"
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Renting"
		 << endl
		 << setw(30) << left << "Name"
		 << setw(10) << left << "Year"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Times"
		 << setw(10) << left << "Rating"
		 << setw(10) << left << "Status"
		 << "\n----------------------------------------------------------------------------------------------\n";


	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;

		string productionYear;
		getline(moviesFile, productionYear, ',');

		string fees;
		getline(moviesFile, fees, ',');

		string overdueFees;
		getline(moviesFile, overdueFees, ',');

		string noOfRents;
		getline(moviesFile, noOfRents, ',');

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		int numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		float rateSummition = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');

		cout << setw(30) << left << name
			 << setw(10) << left << productionYear
			 << setw(10) << left << fees
			 << setw(10) << left << overdueFees
			 << setw(10) << left << noOfRents;

		if (numberOfRates != 0)
			cout << setw(10) << left << (rateSummition / (float)numberOfRates);
		else
			cout << setw(10) << left << "0";

		if (isRented == "1")
			cout << setw(10) << left << "Rented"     << endl;
		else
			cout << setw(10) << left << "Not Rented" << endl;
	}

	moviesFile.close();
	cout << endl;

}

//list all rentd movies
void listAllRentedMovies() {

	cout << "\n------------------------------------------------------------------------------\n"
		 << setw(30) << left << "Movie"
		 << setw(10) << left << "Prod."
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Overdue"
		 << setw(10) << left << "Rent"
		 << setw(10) << left << "Movie"
		 << endl
		 << setw(30) << left << "Name"
		 << setw(10) << left << "Year"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Times"
		 << setw(10) << left << "Rating"
		 << "\n------------------------------------------------------------------------------\n";

	int i = 0;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {

		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		if (AllMovies[i].isRented) {
			cout << setw(30) << left << AllMovies[i].name
				 << setw(10) << left << AllMovies[i].productionYear
				 << setw(10) << left << AllMovies[i].fees
				 << setw(10) << left << AllMovies[i].overdueFees
				 << setw(10) << left << AllMovies[i].numberOfRents;

			if (AllMovies[i].numberOfRates != 0)
				cout << setw(10) << left << (AllMovies[i].rating / (float)AllMovies[i].numberOfRates) << endl;
			else
				cout << setw(10) << left << "0" << endl;
		}

		i++;
	}
	moviesFile.close();

	cout << endl;
}

//Sort top 10 rated movies
void sortTopRated() {

	int i = 0;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		i++;
	}

	moviesFile.close();

	//sorting
	Movie temp;
	for (int x = 0; x <= i; x++) {
		for (int j = 0; j < i - 1; j++) {

			float rating1 = 0;
			float rating2 = 0;

			if (AllMovies[j].numberOfRates != 0)
				rating1 = AllMovies[j].rating     / (float)AllMovies[j].numberOfRates;

			if (AllMovies[j + 1].numberOfRates != 0)
				rating2 = AllMovies[j + 1].rating / (float)AllMovies[j + 1].numberOfRates;

			if (rating1 < rating2) {
				temp = AllMovies[j];
				AllMovies[j] = AllMovies[j + 1];
				AllMovies[j + 1] = temp;
			}
		}
	}

	cout << "\n-------------------------------------------------------------------------------------------------\n"
		 << setw(4)  << left << ""
		 << setw(30) << left << "Movie"
		 << setw(10) << left << "Prod."
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Overdue"
		 << setw(10) << left << "Rent"
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Renting"
		 << endl
		 << setw(4)  << left << "No."
		 << setw(30) << left << "Name"
		 << setw(10) << left << "Year"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Times"
		 << setw(10) << left << "Rating"
		 << setw(10) << left << "Status"
		 << "\n-------------------------------------------------------------------------------------------------\n";


	for (int j = 0; j < 10 && AllMovies[j].rating != 0; j++) {
		cout << "#" << setw(3)  << left << j + 1
				    << setw(30) << left << AllMovies[j].name
				    << setw(10) << left << AllMovies[j].productionYear
				    << setw(10) << left << AllMovies[j].fees
				    << setw(10) << left << AllMovies[j].overdueFees
				    << setw(10) << left << AllMovies[j].numberOfRents
			        << setw(10) << left << (AllMovies[j].rating / (float)AllMovies[j].numberOfRates);
		
		if (AllMovies[j].isRented)
			cout << setw(10) << left << "Rented" << endl;
		else
			cout << setw(10) << left << "Not Rented" << endl;

	}
	cout << endl;

}

//sort top 10 most RENTED movies
void sortMostRented() {

	int i = 0;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);
		i++;
	}

	moviesFile.close();

	Movie temp;
	for (int x = 0; x <= i; x++) {
		for (int j = 0; j < i - 1; j++) {
			if (AllMovies[j].numberOfRents < AllMovies[j + 1].numberOfRents) {
				temp = AllMovies[j];
				AllMovies[j] = AllMovies[j + 1];
				AllMovies[j + 1] = temp;
			}
		}
	}

	cout << "\n-------------------------------------------------------------------------------------------------\n"
		 << setw(4)  << left << ""
		 << setw(30) << left << "Movie"
		 << setw(10) << left << "Prod."
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Overdue"
		 << setw(10) << left << "Rent"
		 << setw(10) << left << "Movie"
		 << setw(10) << left << "Renting"
		 << endl
		 << setw(4)  << left << "No."
		 << setw(30) << left << "Name"
		 << setw(10) << left << "Year"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Fees"
		 << setw(10) << left << "Times"
		 << setw(10) << left << "Rating"
		 << setw(10) << left << "Status"
		 << "\n-------------------------------------------------------------------------------------------------\n";


	for (int j = 0; j < 10 && AllMovies[j].numberOfRents != 0; j++) {
		cout << "#" << setw(3)  << left << j + 1
				    << setw(30) << left << AllMovies[j].name
				    << setw(10) << left << AllMovies[j].productionYear
				    << setw(10) << left << AllMovies[j].fees
				    << setw(10) << left << AllMovies[j].overdueFees
				    << setw(10) << left << AllMovies[j].numberOfRents;

		if (AllMovies[j].numberOfRates != 0)
			cout << setw(10) << left << (AllMovies[j].rating / (float)AllMovies[j].numberOfRates);
		else
			cout << setw(10) << left << "0";

		if (AllMovies[j].isRented)
			cout << setw(10) << left << "Rented" << endl;
		else
			cout << setw(10) << left << "Not Rented" << endl;

	}
	cout << endl;

}

//let the user add rating to a particular movie
void rateAMovie() {

	string rateName;
	cout << "Enter movie's name: ";
	getline(cin, rateName);
	stringValidation(rateName);

	int i = 0;
	int index;
	bool isFound = false;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		//modify the movie you searched for
		if (AllMovies[i].name == rateName) {
			isFound = true;
			index = i;
		}
		i++;

	}
	moviesFile.close();

	if (isFound) {
		float newRate;
		do{
			cout << "Enter Movie's Rating (0 to 10): ";
			cin >> newRate;
		} while (newRate < 0 || newRate > 10);
		cin.ignore();

		AllMovies[index].numberOfRates++;
		AllMovies[index].rating += newRate;
		replaceAllMoviesFile(AllMovies, i);
	}
	else {
		Beep(1500, 500);
		cout << "Concentrate! You might have entered a wrong movie name\n";
	}
}

//Search for a movie and display it on cmd
void searchMovie() {

	string searchName;
	cout << "Enter movie's name: ";
	getline(cin, searchName);
	stringValidation(searchName);

	int i = 0;
	int index;
	bool isFound = false;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {

		string name;
		getline(moviesFile, name, ',');
		if (name == "") {
			break;
		}
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		if (searchName == name) {
			isFound = true;
			index = i;

		}
		i++;
	}

	moviesFile.close();
	system("cls");

	if (isFound) {
		//printing header
		cout << "\n-------------------------------------------------------------------------------------------\n"
			 << setw(30) << left << "Movie"
			 << setw(10) << left << "Prod."
			 << setw(10) << left << "Movie"
			 << setw(10) << left << "Overdue"
			 << setw(10) << left << "Rent"
			 << setw(10) << left << "Movie"
			 << setw(10) << left << "Renting"
			 << endl
			 << setw(30) << left << "Name"
			 << setw(10) << left << "Year"
			 << setw(10) << left << "Fees"
			 << setw(10) << left << "Fees"
			 << setw(10) << left << "Times"
			 << setw(10) << left << "Rating"
			 << setw(10) << left << "Status"
			 << "\n-------------------------------------------------------------------------------------------\n";

		//printing searched movie on cmd
		cout << setw(30) << left << AllMovies[index].name
			 << setw(10) << left << AllMovies[index].productionYear
			 << setw(10) << left << AllMovies[index].fees
			 << setw(10) << left << AllMovies[index].overdueFees
			 << setw(10) << left << AllMovies[index].numberOfRents;

		if (AllMovies[index].numberOfRates != 0)
			cout << setw(10) << left << (AllMovies[index].rating / (float)AllMovies[index].numberOfRates);
		else
			cout << setw(10) << left << "0";

		if (AllMovies[index].isRented)
			cout << setw(10) << left << "Rented"     << endl;
		else
			cout << setw(10) << left << "Not Rented" << endl;
	}

	else {
		Beep(1500, 500);
		cout << "SORRY :'( Movie is NOT FOUND";
	}

	cout << endl;

}

//Delete a movie by name
void deleteMovieFromFile() {

	string deleteName;
	cout << "Enter movie's name:";
	getline(cin, deleteName);
	stringValidation(deleteName);

	int i = 0;
	int skipIndex = -1;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {

		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		if (AllMovies[i].name == deleteName) {
			skipIndex = i;
		}
		i++;
	}

	moviesFile.close();


	if (skipIndex != -1){

		moviesFile.open(moviesFilePath, ios::out);

		for (int j = 0; j < i; j++){
			if (j != skipIndex){
				moviesFile << AllMovies[j].name           << ','
						   << AllMovies[j].productionYear << ','
						   << AllMovies[j].fees           << ','
						   << AllMovies[j].overdueFees	  << ','
						   << AllMovies[j].numberOfRents  << ','
						   << AllMovies[j].numberOfRates  << ','
						   << AllMovies[j].rating		  << ',';

				if (AllMovies[j].isRented)
					moviesFile << "1" << '\n';
				else
					moviesFile << "0" << '\n';
			}
		}
			
		moviesFile.close();

		Beep(1500, 500);
		cout << "Movie is Deleted...\n";
	}

	else {
		Beep(1500, 500);
		cout << "Movie is NOT FOUND\n";
	}

}

//replace the movies file after modification
void replaceAllMoviesFile(Movie movies[], int size) {

	moviesFile.open(moviesFilePath, ios::out);

	for (int j = 0; j < size; j++){
		moviesFile << movies[j].name           << ','
				   << movies[j].productionYear << ','
				   << movies[j].fees           << ','
				   << movies[j].overdueFees    << ','
				   << movies[j].numberOfRents  << ','
				   << movies[j].numberOfRates  << ','
				   << movies[j].rating         << ',';

		if (movies[j].isRented)
			moviesFile << "1" << '\n';
		else
			moviesFile << "0" << '\n';

	}

	moviesFile.close();

}

/////////////////////////////////////////////////////////////////////




//////////////////// Rent functions' Definition ////////////////////

//rent main function
void rent() {

	string movieName, customerPhoneNumber;
	int numberOfDueDays, movieIndex, customerIndex;
	bool isRented;

	//entering movie name and check if not found and if rented  
	cout << "Movie Name: ";
	getline(cin, movieName);
	stringValidation(movieName);

	movieIndex = searchingForMovie(movieName);
	if (movieIndex == -1){
		Beep(1500, 500);
		cout << endl << "The Movie is NOT FOUND" << endl << endl;
		Sleep(1000);
		system("cls");
		mainMenu();
	}

	isRented = isMovieRented(movieName);
	if (isRented){
		Beep(1500, 500);
		cout << endl << "The Movie is Rented" << endl << endl;
		Sleep(1000);
		system("cls");
		mainMenu();
	}

	//entering phone number and check if it is valid
	bool isPhoneNumberValid;
	do{
		isPhoneNumberValid = true;
		cout << "Phone Number: ";
		getline(cin, customerPhoneNumber);
		stringValidation(customerPhoneNumber);

		for (int i = 0; i < 11; i++){
			if (customerPhoneNumber[i] > '9' || customerPhoneNumber[i] < '0' || customerPhoneNumber.length() != 11){
				isPhoneNumberValid = false;
				Beep(1500, 500);
				cout << "Phone number must be 11 Numbers only!";
				Sleep(1500);

				//clearing screen
				COORD coord; // coordinates
				for (int y = 1; y <= 3; y++){
					coord.X = 0;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
					for (int x = 0; x <= 70; x++){
						cout << " ";
					}
				}

				coord.X = 0;
				coord.Y = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				break;
			}
		}

	} while (isPhoneNumberValid == false);

	customerIndex = searchingForCustomer(customerPhoneNumber);

	//check if phone number is not found
	if (customerIndex == -1){
		Beep(1500, 500);
		cout << endl << "The customer is NOT FOUND" << endl;

		Customer newCustomer;
		newCustomer.phoneNumber = customerPhoneNumber;
		cout << "Please enter customer's name: ";
		getline(cin, newCustomer.name);
		stringValidation(newCustomer.name);

		customersFile.open(customersFilePath, ios::out | ios::app);
		customersFile << newCustomer.name		 << ","
					  << newCustomer.phoneNumber << '\n';
		customersFile.close();

		sortCutomersFile();

		cout << "Customer is added successfully..." << endl << endl;
		Sleep(1500);

		//clearing screen
		COORD coord; // coordinates
		for (int y = 3; y <= 5; y++){
			coord.X = 0;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
			for (int x = 0; x <= 70; x++){		
				cout << " ";
			}
		}

		coord.X = 0;
		coord.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	//entering number of due days
	cout << "Number of Due Days: ";
	cin  >> numberOfDueDays;

	system("cls");

	collectRentedMovieData(customerPhoneNumber, movieName, numberOfDueDays);
	displayRentingData(RentedMovie);

	exportRentigData(RentedMovie);
	switchisRentedAndIncrementNumberOfRents(RentedMovie);
	uploadToRentPrintFile(RentedMovie);


	char key;
	while (true) {
		cout << "\nDo you want to rent another movie? <y/n>: ";
		cin >> key;
		cin.ignore();

		if (key == 'y' || key == 'Y') {
			system("cls");
			rent();
		}
		else if (key == 'n' || key == 'N') {
			system("cls");
			mainMenu();
			break;
		}
		else
			cout << "Please enter <y/n>\n";
	}
	
}

//search in movie file
int searchingForMovie(string searchMovieName) {

	int i = 0;
	int index = -1;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRentings;
		getline(moviesFile, noOfRentings, ',');
		AllMovies[i].numberOfRents = stoi(noOfRentings);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string status;
		getline(moviesFile, status, '\n');
		AllMovies[i].isRented = stoi(status);

		if (AllMovies[i].name == searchMovieName)
			index = i;
		i++;

	}
	moviesFile.close();

	return index;

}

//customer search
int searchingForCustomer(string customrphonenumber) {

	int i = 0;
	int index = -1;
	
	customersFile.open(customersFilePath);
	while (!customersFile.eof()) {
		string name;
		getline(customersFile, name, ',');
		if (name == "") break;
		AllCustomers[i].name = (name);

		string phonenumber;
		getline(customersFile, phonenumber, '\n');
		AllCustomers[i].phoneNumber = (phonenumber);

		if (AllCustomers[i].phoneNumber == customrphonenumber){
			index = i;
		}

		i++;
	}
	customersFile.close();

	return index;

}

//search if the movie is rented or no
bool isMovieRented(string moviename) {

	int movieindex = searchingForMovie(moviename);

	if (AllMovies[movieindex].isRented == 0)
		return false;
	else
		return true;

}

// Fill the rent struct with the data then returns a struct filled with this data
void collectRentedMovieData(string customerPhoneNumber, string movieName, int numberOfDueDays){

	//Customer Part
	int customerIndex = searchingForCustomer(customerPhoneNumber);
	RentedMovie.rentingCustomerData.phoneNumber = AllCustomers[customerIndex].phoneNumber;
	RentedMovie.rentingCustomerData.name        = AllCustomers[customerIndex].name;

	//Movie Part
	int movieIndex = searchingForMovie(movieName);
	RentedMovie.rentedMovieData.name            = AllMovies[movieIndex].name;
	RentedMovie.rentedMovieData.fees            = AllMovies[movieIndex].fees;
	RentedMovie.rentedMovieData.overdueFees     = AllMovies[movieIndex].overdueFees;
	RentedMovie.rentedMovieData.numberOfRents   = AllMovies[movieIndex].numberOfRents + 1;
	RentedMovie.rentedMovieData.isRented        = true;

	//Renting Days Part
	RentedMovie.numberOfRentingDays = numberOfDueDays;

	//Renting date Part
	time_t systemDateInSeconds = time(NULL);
	struct tm date1            = *localtime(&systemDateInSeconds);
	RentedMovie.rentDate.day   = date1.tm_mday;
	RentedMovie.rentDate.month = date1.tm_mon  + 1;
	RentedMovie.rentDate.year  = date1.tm_year + 1900;

	//Due Date Part
	time_t dueDateInSeconds    = systemDateInSeconds + (numberOfDueDays * 24 * 60 * 60);
	struct tm date2            = *localtime(&dueDateInSeconds);
	RentedMovie.dueDate.day    = date2.tm_mday;
	RentedMovie.dueDate.month  = date2.tm_mon  + 1;
	RentedMovie.dueDate.year   = date2.tm_year + 1900;

}

//display all renting data
void displayRentingData(Rent RentedMovie) {
	
	string RENTDATE, DUEDATE, RENTINGDAYS;
	RENTDATE    = to_string(RentedMovie.rentDate.day) + '/' + to_string(RentedMovie.rentDate.month) + '/' + to_string(RentedMovie.rentDate.year);
	DUEDATE     = to_string(RentedMovie.dueDate.day)  + '/' + to_string(RentedMovie.dueDate.month)  + '/' + to_string(RentedMovie.dueDate.year);
	RENTINGDAYS = to_string(RentedMovie.numberOfRentingDays) + " Days";


	cout << "Order Detials:\n\n"
	     << "Customer Name: "  << setw(20) << left << RentedMovie.rentingCustomerData.name 
		 << "Movie Name:   "   << RentedMovie.rentedMovieData.name                  << endl
	     << "Phone Number:  "  << setw(20) << left << RentedMovie.rentingCustomerData.phoneNumber
		 << "Renting Days: "   << RENTINGDAYS                                       << endl
	     << "Renting Date:  "  << setw(20) << left << RENTDATE
		 << "Movie Fees:   "   << RentedMovie.rentedMovieData.fees        << " EGP" << endl
	     << "Due Date:      "  << setw(20) << left << DUEDATE      
	     << "Overdue Fees: "   << RentedMovie.rentedMovieData.overdueFees << " EGP" << endl;

}

//export renting movie data into rentings file
void exportRentigData(Rent RentedMovie) {

	rentFile.open(rentFilePath, ios::out | ios::app);

	rentFile << RentedMovie.rentingCustomerData.phoneNumber << ","
			 << RentedMovie.rentingCustomerData.name        << ","
			 << RentedMovie.rentedMovieData.name            << ","
			 << RentedMovie.rentedMovieData.fees            << ","
			 << RentedMovie.rentedMovieData.overdueFees     << ","
			 << RentedMovie.rentDate.day                    << "/"
			 << RentedMovie.rentDate.month                  << "/"
			 << RentedMovie.rentDate.year                   << ","
			 << RentedMovie.dueDate.day                     << "/"
			 << RentedMovie.dueDate.month                   << "/"
			 << RentedMovie.dueDate.year                    << "\n";

	rentFile.close();
}

//replace the movies file after modification
void switchisRentedAndIncrementNumberOfRents(Rent RentedMovie) {

	int i = 0, index;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRentings;
		getline(moviesFile, noOfRentings, ',');
		AllMovies[i].numberOfRents = stoi(noOfRentings);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string status;
		getline(moviesFile, status, '\n');
		AllMovies[i].isRented = stoi(status);

		if (AllMovies[i].name == RentedMovie.rentedMovieData.name)
			index = i;
		i++;

	}
	moviesFile.close();

	AllMovies[index].isRented      = 1;
	AllMovies[index].numberOfRents = RentedMovie.rentedMovieData.numberOfRents;

	replaceAllMoviesFile(AllMovies, i);

}

//upload data to rent print file
void uploadToRentPrintFile(Rent RentedMovie) {

	string RENTDATE, DUEDATE, RENTINGDAYS;
	RENTDATE    = to_string(RentedMovie.rentDate.day) + '/' + to_string(RentedMovie.rentDate.month) + '/' + to_string(RentedMovie.rentDate.year);
	DUEDATE     = to_string(RentedMovie.dueDate.day)  + '/' + to_string(RentedMovie.dueDate.month)  + '/' + to_string(RentedMovie.dueDate.year);
	RENTINGDAYS = to_string(RentedMovie.numberOfRentingDays) + " Days";

	rentPrint.open(rentPrintFilePath, ios::out | ios::app);

	rentPrint << "Order Detials:\n\n"
			  << "Customer Name: " << setw(20) << left << RentedMovie.rentingCustomerData.name
			  << "Movie Name:   "  << RentedMovie.rentedMovieData.name                                 << endl
			  << "Phone Number:  " << setw(20) << left << RentedMovie.rentingCustomerData.phoneNumber
			  << "Renting Days: "  << RENTINGDAYS                                                      << endl
			  << "Renting Date:  " << setw(20) << left << RENTDATE
			  << "Movie Fees:   "  << RentedMovie.rentedMovieData.fees                       << " EGP" << endl
			  << "Due Date:      " << setw(20) << left << DUEDATE
			  << "Overdue Fees: "  << RentedMovie.rentedMovieData.overdueFees                << " EGP" << endl
			  << "-------------------------------------------------------------------------"           << endl;

	rentPrint.close();

	cout << endl << "To print The Receipt go to \"Rent Print.doc\" file on your Desktop. "   << endl;
	Sleep(500);

}

/////////////////////////////////////////////////////////////////////




/////////////////// Recive functions' Definition ///////////////////

//receive main function
void receive() {

	string receivedMovieName;
	cout << "Enter movie's name: ";
	getline(cin, receivedMovieName);
	stringValidation(receivedMovieName);

	int i = 0;
	int movieIndex = -1;

	rentFile.open(rentFilePath);
	while (!rentFile.eof()) {
		string phoneNumber;
		getline(rentFile, phoneNumber, ',');
		if (phoneNumber == "") break;
		AllRentedMovies[i].rentingCustomerData.phoneNumber = phoneNumber;

		string customerName;
		getline(rentFile, customerName, ',');
		AllRentedMovies[i].rentingCustomerData.name = customerName;

		string movieName;
		getline(rentFile, movieName, ',');
		AllRentedMovies[i].rentedMovieData.name = movieName;

		string fees;
		getline(rentFile, fees, ',');
		AllRentedMovies[i].rentedMovieData.fees = stof(fees);

		string overduefees;
		getline(rentFile, overduefees, ',');
		AllRentedMovies[i].rentedMovieData.overdueFees = stof(overduefees);

		string rentday, rentmonth, rentyear;
		getline(rentFile, rentday, '/');
		AllRentedMovies[i].rentDate.day   = stoi(rentday);
		getline(rentFile, rentmonth, '/');
		AllRentedMovies[i].rentDate.month = stoi(rentmonth);
		getline(rentFile, rentyear, ',');
		AllRentedMovies[i].rentDate.year  = stoi(rentyear);

		string dueday, duemonth, dueyear;
		getline(rentFile, dueday, '/');
		AllRentedMovies[i].dueDate.day   = stoi(dueday);
		getline(rentFile, duemonth, '/');
		AllRentedMovies[i].dueDate.month = stoi(duemonth);
		getline(rentFile, dueyear, '\n');
		AllRentedMovies[i].dueDate.year  = stoi(dueyear);

		if (AllRentedMovies[i].rentedMovieData.name == receivedMovieName) {
			movieIndex = i;
		}

		i++;
	}
	rentFile.close();


	if (movieIndex == -1){
		Beep(1500, 500);
		cout << "Movie is NOT FOUND\n";
		Sleep(1000);
		system("cls");
		mainMenu();
	}

	else {
		cout << "Enter Receiving Date (DD/MM/YYYY): ";
		cin  >> ReceivedMovie.receiveDate.day;
		cin.get();
		cin  >> ReceivedMovie.receiveDate.month;
		cin.get();
		cin  >> ReceivedMovie.receiveDate.year;

		ReceivedMovie.rentingCustomerData = AllRentedMovies[movieIndex].rentingCustomerData;
		ReceivedMovie.receivedMovieData   = AllRentedMovies[movieIndex].rentedMovieData;
		ReceivedMovie.dueDate             = AllRentedMovies[movieIndex].dueDate;
		ReceivedMovie.rentDate            = AllRentedMovies[movieIndex].rentDate;
		ReceivedMovie.status              = isOverdue(ReceivedMovie);
		ReceivedMovie.totalFees           = calculateTotalFees(ReceivedMovie);

		displayReceivedMovieData(ReceivedMovie);
		exportRecievedMovieData(ReceivedMovie);
		uploadToReceivePrintFile(ReceivedMovie);

		removeMovieFromRentFile(i, movieIndex);
		switchisRentedAfterReceivingMovie(ReceivedMovie.receivedMovieData.name);

		char key;
		while (true) {
			cout << "\nDo you want to receive another movie? <y/n>: ";
			cin >> key;
			cin.ignore();
			if (key == 'y' || key == 'Y') {
				system("cls");
				receive();
			}
			else if (key == 'n' || key == 'N') {
				system("cls");
				mainMenu();
				break;
			}
			else
				cout << "Please enter <y/n>\n";
		}
	}

}

//check if customer is overdue or not
bool isOverdue(Receive data){

	data.status = false;

	if (data.receiveDate.year > data.dueDate.year) {
		data.status = true;
	}
	else {
		if (data.receiveDate.month > data.dueDate.month && data.receiveDate.year == data.dueDate.year) {
			data.status = true;
		}
		else {
			if (data.receiveDate.day > data.dueDate.day && data.receiveDate.month == data.dueDate.month && data.receiveDate.year == data.dueDate.year)
				data.status = true;
		}
	}

	return data.status;

}

//calculate the total fees
float calculateTotalFees(Receive data){
	if (data.status)
		data.totalFees = data.receivedMovieData.fees + data.receivedMovieData.overdueFees;
	else
		data.totalFees = data.receivedMovieData.fees;

	return data.totalFees;
}

//display recevie customer data
void displayReceivedMovieData(Receive data) {

	system("cls");

	cout << "Order Details:\n\n"
		 << "Customer's name: "          << data.rentingCustomerData.name        << endl
		 << "Customer's phone number: "  << data.rentingCustomerData.phoneNumber << endl
		 << "Movie's name: "             << data.receivedMovieData.name          << endl << endl
		 << "Rent date:    "             << data.rentDate.day                    << "/"
									     << data.rentDate.month                  << "/" 
									     << data.rentDate.year                   << endl
		 << "Due date:     "             << data.dueDate.day                     << "/" 
									     << data.dueDate.month                   << "/" 
									     << data.dueDate.year                    << endl
		 << "Receive date: "             << data.receiveDate.day                 << "/" 
									     << data.receiveDate.month               << "/" 
								         << data.receiveDate.year                << endl << endl;

	if (data.status)
		cout << "Status: OVERDUE!"       << endl;
	else
		cout << "Status: NOT OVERDUE!"   << endl;

	cout << "Movie fees:   "             << data.receivedMovieData.fees            << " EGP" << endl
		 << "Overdue fees: "             << data.receivedMovieData.overdueFees     << " EGP" << endl
		 << "Total fees:   "             << data.totalFees                         << " EGP" << endl;

}

//upload data to recive file
void exportRecievedMovieData(Receive data) {


	receiveFile.open(receiveFilePath, ios::out | ios::app);

	receiveFile << data.rentingCustomerData.phoneNumber << ","
	            << data.rentingCustomerData.name        << ","
	            << data.receivedMovieData.name          << ","
	            << data.rentDate.day                    << "/"
				<< data.rentDate.month                  << "/"
				<< data.rentDate.year                   << ","
				<< data.receiveDate.day                 << "/"
				<< data.receiveDate.month               << "/"
				<< data.receiveDate.year                << ",";

	if (data.status == true) {
		receiveFile << "Overdue"     << ",";
	}
	else {
		receiveFile << "Not Overdue" << ",";
	}

	receiveFile << data.totalFees << "\n";

	receiveFile.close();
}

//remove recive customer data from rent file and upload new data to rent file
void removeMovieFromRentFile(int size, int skipedIndex) {

	rentFile.open(rentFilePath, ios::out);

	for (int j = 0; j < size; j++) {
		if (j != skipedIndex) {
			rentFile << AllRentedMovies[j].rentingCustomerData.phoneNumber << ","
				     << AllRentedMovies[j].rentingCustomerData.name        << ","
				     << AllRentedMovies[j].rentedMovieData.name            << ","
					 << AllRentedMovies[j].rentedMovieData.fees            << ","
					 << AllRentedMovies[j].rentedMovieData.overdueFees     << ","
				     << AllRentedMovies[j].rentDate.day                    << "/" 
				     << AllRentedMovies[j].rentDate.month                  << "/" 
				     << AllRentedMovies[j].rentDate.year                   << "," 
				     << AllRentedMovies[j].dueDate.day                     << "/" 
				     << AllRentedMovies[j].dueDate.month                   << "/" 
					 << AllRentedMovies[j].dueDate.year                    << "\n";
		}
	}

	rentFile.close();

}

//return the bool of movie
void switchisRentedAfterReceivingMovie(string returnedMovie) {

	int i = 0;

	moviesFile.open(moviesFilePath);
	while (!moviesFile.eof()) {
		string name;
		getline(moviesFile, name, ',');
		if (name == "") break;
		AllMovies[i].name = name;

		string productionYear;
		getline(moviesFile, productionYear, ',');
		AllMovies[i].productionYear = stoi(productionYear);

		string fees;
		getline(moviesFile, fees, ',');
		AllMovies[i].fees = stof(fees);

		string overdueFees;
		getline(moviesFile, overdueFees, ',');
		AllMovies[i].overdueFees = stof(overdueFees);

		string noOfRents;
		getline(moviesFile, noOfRents, ',');
		AllMovies[i].numberOfRents = stoi(noOfRents);

		string noOfRates;
		getline(moviesFile, noOfRates, ',');
		AllMovies[i].numberOfRates = stoi(noOfRates);

		string rating;
		getline(moviesFile, rating, ',');
		AllMovies[i].rating = stof(rating);

		string isRented;
		getline(moviesFile, isRented, '\n');
		AllMovies[i].isRented = stoi(isRented);

		//modify the movie you searched for
		if (AllMovies[i].name == returnedMovie) {
			AllMovies[i].isRented = false;
		}

		i++;
	}
	moviesFile.close();

	//replace the old file with the modifies array of movies
	replaceAllMoviesFile(AllMovies, i);

}

//upload data to recive print file
void uploadToReceivePrintFile(Receive data) {

	recevieprint.open(receviePrintFilePath, ios::out | ios::app);

	recevieprint << "Order Details:\n\n"
				 << "Customer's name: "         << data.rentingCustomerData.name                << endl
				 << "Customer's phone number: " << data.rentingCustomerData.phoneNumber         << endl
				 << "Movie name:   "            << data.receivedMovieData.name         << endl  << endl
				 << "Rent date:    "            << data.rentDate.day                            << "/"
												<< data.rentDate.month                          << "/"
												<< data.rentDate.year                           << endl
				 << "Due date:     "            << data.dueDate.day                             << "/"
												<< data.dueDate.month                           << "/"
												<< data.dueDate.year                            << endl
				 << "Receive date: "            << data.receiveDate.day                         << "/"
												<< data.receiveDate.month                       << "/"
												<< data.receiveDate.year              << endl   << endl;

	if (data.status)
		recevieprint << "Status: OVERDUE!"      << endl;
	else
		recevieprint << "Status: NOT OVERDUE!"  << endl;

	recevieprint << "Movie fees:   "            << data.receivedMovieData.fees        << " EGP" << endl
		         << "Overdue fees: "            << data.receivedMovieData.overdueFees << " EGP" << endl
		         << "Total fees:   "            << data.totalFees                     << " EGP" << endl
				 << "-------------------------------------------------------------------------" << endl;

	recevieprint.close();

	cout << endl << "To print The Receipt go to \"Receive Print.doc\" file on your Desktop. "   << endl;

	Sleep(500);
}

/////////////////////////////////////////////////////////////////////




//////////////////// Admin functions' Definition ////////////////////

//monthly Income
void monthlyIncome() {

	int searchMonth, searchYear;
	cout << "Enter Month & Year (MM/YYYY): ";
	cin  >> searchMonth;
	cin.get();
	cin  >> searchYear;

	int i = 0;
	double income = 0.0;

	receiveFile.open(receiveFilePath);
	while (!receiveFile.eof()) {
		string phoneNumber;
		getline(receiveFile, phoneNumber, ',');
		if (phoneNumber == "") break;
		AllReceivedMovies[i].rentingCustomerData.phoneNumber = phoneNumber;

		string customerName;
		getline(receiveFile, customerName, ',');
		AllReceivedMovies[i].rentingCustomerData.name = customerName;

		string movieName;
		getline(receiveFile, movieName, ',');
		AllReceivedMovies[i].receivedMovieData.name = movieName;

		string rentday, rentmonth, rentyear;
		getline(receiveFile, rentday, '/');
		AllReceivedMovies[i].rentDate.day   = stoi(rentday);
		getline(receiveFile, rentmonth, '/');
		AllReceivedMovies[i].rentDate.month = stoi(rentmonth);
		getline(receiveFile, rentyear, ',');
		AllReceivedMovies[i].rentDate.year  = stoi(rentyear);

		string receiveday, receivemonth, receiveyear;
		getline(receiveFile, receiveday, '/');
		AllReceivedMovies[i].receiveDate.day   = stoi(receiveday);
		getline(receiveFile, receivemonth, '/');
		AllReceivedMovies[i].receiveDate.month = stoi(receivemonth);
		getline(receiveFile, receiveyear, ',');
		AllReceivedMovies[i].receiveDate.year  = stoi(receiveyear);

		string status;
		getline(receiveFile, status, ',');

		string sum;
		getline(receiveFile, sum, '\n');
		AllReceivedMovies[i].totalFees = stof(sum);

		if (AllReceivedMovies[i].receiveDate.month == searchMonth && AllReceivedMovies[i].receiveDate.year == searchYear) {
			income += AllReceivedMovies[i].totalFees;
		}

		i++;
	}
	receiveFile.close();

	cout << "The Income of " << searchMonth << "/" << searchYear << " is: " << income << " EGP" << endl;

	char key;
	while (true) {
		cout << "\nDo you want to know the income of another month? <y/n>: ";
		cin >> key;

		if (key == 'y' || key == 'Y') {
			system("cls");
			monthlyIncome();
		}
		else if (key == 'n' || key == 'N') {
			system("cls");
			mainMenu();
			break;
		}
		else
			cout << "Please enter <y/n>\n";

	}

}

//deletes all data saved in all files
void resetAllData() {

	char key;
	Beep(1500, 500);
	cout << "\nAre you sure to delete all your data? <y/n>" << endl
		 << "WARNING!: THIS DATA CAN'T BE RESTORED"         << endl;
	cin  >> key;
	cin.ignore();

	if (key == 'y' || key == 'Y') {

		customersFile.open(customersFilePath, ios::out);
		customersFile << "";
		customersFile.close();

		moviesFile.open(moviesFilePath, ios::out);
		moviesFile << "";
		moviesFile.close();

		rentFile.open(rentFilePath, ios::out);
		rentFile << "";
		rentFile.close();

		receiveFile.open(receiveFilePath, ios::out);
		receiveFile << "";
		receiveFile.close();

		Beep(1500, 500);
		cout << "All data has been deleted..." << endl;
		Sleep(1500);
	}
	else if (key == 'n' || key == 'N') {
		system("cls");
		adminMenu();
	}
	else{
		cout << "please enter <y/n>\n";
		resetAllData();
	}

}

//displays asterisks on the screen while entering Password
void enterPasswordWithoutEcho(char enteredPassword[]) {

	int i = 0;
	while (true) {
		enteredPassword[i] = _getch();

		//handling backspace
		if (enteredPassword[i] == '\b') {
			i--;
			cout << '\b' << ' ' << '\b';
			continue;
		}

		//pressing enter means end of input
		if (enteredPassword[i] == '\r') {
			enteredPassword[i] = '\0';
			break;
		}

		cout << "*";
		i++;
	}

}

//encrypts the entered password
string encryptEnteredPassword(char enteredPassword[]) {

	string encryptedPassword;
	int num = 99999;

	for (int i = 0; enteredPassword[i] != '\0'; i++) {
		int temp = enteredPassword[i] + num;
		char hexCharachter[7];
		_itoa(temp, hexCharachter, 16);

		for (int i = 0; hexCharachter[i] != '\0'; i++) {
			encryptedPassword += hexCharachter[i];
		}
	}

	return encryptedPassword;

}

//saves the entered password to the password file
void savePasswordToFile(string password) {

	passwordFile.open(passwordFilePath, ios::out);
	passwordFile << password;
	passwordFile.close();

	//Hide the file
	int attributes = GetFileAttributes(L"Password.txt");
	SetFileAttributes(L"Password.txt", attributes | FILE_ATTRIBUTE_HIDDEN);

}

//creates the file if it doesn't exist or does nothing if the file already exists
void createPasswordFile() {

	passwordFile.open(passwordFilePath, ios::out | ios::app);
	passwordFile << "";
	passwordFile.close();

}

//gets the content of the password file
string loadPasswordFile() {

	passwordFile.open(passwordFilePath);
	string password;
	while (!passwordFile.eof()){
		getline(passwordFile, password);
	}
	passwordFile.close();

	return password;

}

//returns true if login successful & false if not
bool loginProcess() {

	char enteredPassword[50];
	bool isLoginSuccessful = false;

	createPasswordFile();

	if (loadPasswordFile() == "") {
		cout << "Please set your Password: ";
		enterPasswordWithoutEcho(enteredPassword);
		savePasswordToFile(encryptEnteredPassword(enteredPassword));
		cout << "\nPassword Saved!\n";
		isLoginSuccessful = true;
	}

	else {
		int trials = 0;
		do {
			cout << "Please Enter your Password: ";
			enterPasswordWithoutEcho(enteredPassword);

			if (encryptEnteredPassword(enteredPassword) == loadPasswordFile()) {
				cout << "\nLogin Successful\n";
				isLoginSuccessful = true;
				break;
			}
			else {
				Beep(1500, 500);
				cout << "\nAccess Denied!\n\n";
				trials++;
			}
		} while (trials < 3);

	}

	return isLoginSuccessful;

}

//saves Date and Time when loging in fails 3 times
void exportTologsFile() {

	time_t systemDateInSeconds = time(NULL);
	struct tm currentDate      = *localtime(&systemDateInSeconds);

	logsFile.open(logsFilePath, ios::out | ios::app);

	logsFile << currentDate.tm_hour        << ":"
			 << currentDate.tm_min         << ","
			 << currentDate.tm_mday        << "/"
			 << currentDate.tm_mon + 1     << "/"
			 << currentDate.tm_year + 1900 << ","
			 << "Failed to login 3 times"  << "\n";

	logsFile.close();

}

/////////////////////////////////////////////////////////////////////