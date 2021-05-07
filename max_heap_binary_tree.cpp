//Poroject Description: Program the creates a binary tree (max heap)
//Date: 05-01-2021
//Author: Aammya Sapra

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;


//function prototypes
void max_heap (int* array, int i, int num_numbers);
void build_heap (int* array, int num_numbers);
void display_heap (int* array, int num_numbers, int i, int j);



//--------------------------------------------------MAIN FUNCTION-------------------------------------------------
int main() {

	//print out input options
	string input_option;
	cout << "BINARY TREE PROGRAM" << endl;
	cout << "To input numbers in a text file, type \'F\'." << endl;
	cout << "To input numbers in the console, type \'C\'." << endl;
	cin >> input_option;
	cin.get(); //kill the return

	int num_numbers = 0; //number of input numbers
	int* array = new int[100]; //array to hold input numbers
	
	//numbers inputted in the console (manually)
	if (input_option == "C" || input_option == "c") {
		cout << "Enter numbers (seperate each with a space)" << endl;
		char* input = new char[500];
		cin.getline(input, 500);
		char* num = strtok(input, " "); //break input into a series of tokens using the delimiter " "
		int index = 1;
		while (num != NULL) { //walk through the tokens
			array[index] = atoi(num);
			num = strtok(NULL, " ");
			num_numbers++;
			index++;
		}
	}

	//file input
	else if (input_option == "F" || input_option == "f") {

		cout << "Enter file name. Current input files stored: \'input_numbers.txt\'" << endl;
		char file_name[50];
		cin.getline(file_name, 50, '\n');

		FILE* pfile = NULL; //file pointer
		pfile = fopen(file_name, "r");
		if (pfile == NULL) {
			cout << "Error x_x. File may not exist or permissions may not be granted. Please check that file name was inputted correctly." << endl;
			return 0;
		}

		//store input numbers into array[]
		int arr_index = 0;
		char file_line[5000];
		while (fgets(file_line, 500, pfile)) {
			char* buffer = new char[20];
			memset(buffer, '\0', 20);
			int pos = 0;
			while (buffer != NULL) {
				buffer = strchr(file_line + pos, ' ');
				if (buffer != NULL) {
					char line_buffer[20];
					memset(line_buffer, '\0', 20);
					strncpy(line_buffer, file_line + pos, sizeof(file_line - buffer));
					array[arr_index++] = stoi(line_buffer);
					num_numbers++;
					pos = (buffer - file_line) + 1;
				}
			}
		}
		fclose(pfile);
	}

	//invalid input option entered
	else {
		cout << "Invalid input option entered. Input options are \'F\' and \'C\'." << endl;
		return 0;
	}


	//build the tree
	build_heap(array, num_numbers);

	//print binary tree
	cout << "Tree: " << endl;
	display_heap(array, num_numbers, 0, 1);

	//print heap output (sorted numbers from greatest to least)
	//remove each element in order from heao, adding it to the output
	cout << "\nHeap Output: ";
	for (int i = num_numbers; i > 0; i--) {
		cout << array[1] << ' ';
		array[1] = array[i];
		array[i] = 0;;
		build_heap(array, i);
		array[i] = array[i - 1];
	}

	
	return 0;

} //end of main




//--------------------------------------------------------FUNCTIONS------------------------------------------------------------


//function to sort the binary tree so that all children are smaller than parents
void max_heap (int* array, int i, int num_numbers) {
	int temp = array[i];
	int index = i * 2;
	while (index <= num_numbers) {
		if (index < num_numbers  &&  array[index+1] > array[index]) {
			index = index + 1;
		}
		if (temp > array[index]) {
			break;
		}
		else if (temp <= array[index]) {
			array[index/2] = array[index];
			index *= 2;
		}
	}

	array[index/2] = temp;
	return;
}




//function to build the binary tree
void build_heap (int* array, int num_numbers) {
	int i;
	for (i = num_numbers/2; i >= 1; i--)  {
		max_heap(array, i, num_numbers);
	}
	return;
}



//function to visually display tree (root on left, branches out towards the right)
void display_heap (int* array, int num_numbers, int i, int pos) {
	int leftpos = pos * 2;
	int rightpos = (pos * 2) + 1;
	if (rightpos <= num_numbers) {
		display_heap(array, num_numbers, i + 1, rightpos);
	}
	int current = i;
	while (i > 0) {
		cout << '\t';
		i--;
	}
	cout << array[pos] << endl;
	if (leftpos <= num_numbers) {
		display_heap(array, num_numbers, current + 1, leftpos);
	}
	return;
}





