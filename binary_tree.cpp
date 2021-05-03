//Poroject Description: Program the creates a binary tree (max heap)
//Date: 05-01-2021
//Author: Aammya Sapra

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//Node struct
struct Node {
	int data;
	Node* right;
	Node* left;
};

//function prototypes
Node* add_node(Node* root, int num);
Node* remove_node(Node* root, int num);
Node* smallest_node(Node* root);
void display_tree(Node* root, int num_spaces);



//--------------------------------------------------MAIN FUNCTION-------------------------------------------------
int main() {

	//print out input options
	string input_option;
	cout << "BINARY TREE PROGRAM" << endl;
	cout << "To input numbers in a text file, type \'F\'." << endl;
	cout << "To input numbers in the console, type \'C\'." << endl;
	cin >> input_option;
	cin.get();

	int num_numbers = 0; //number of input numbers

	int num_arr[100]; //array to hold input numbers
	memset(num_arr, -1, 100); //fill with -1
	

	//numbers inputted in the console (manually)
	if (input_option == "C" || input_option == "c") {
		cout << "How many numbers would you like to input?" << endl;
		cin >> num_numbers;
		cout << "Enter " << num_numbers << " numbers (one per line) between 1-1000." << endl;
		for (int i = 0; i < num_numbers; i++) {
			cin >> num_arr[i];
		}
	}

	//file input
	else if (input_option == "F" || input_option == "f") {

		cout << "Enter file name. Current input files stored: \'numbers.txt\'" << endl;
		char file_name[50];
		cin.getline(file_name, 50, '\n');

		FILE* pfile = NULL; //file pointer
		pfile = fopen(file_name, "r");
		if (pfile == NULL) {
			cout << "Error x_x. File may not exist or permissions may not be granted. Please check that file name was inputted correctly." << endl;
			return 0;
		}

		//store input numbers into num_arr[]
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
					num_arr[arr_index++] = stoi(line_buffer);
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



	//create binary tree
	Node* root = NULL;
	for (int i = 0; i < num_numbers; i++) {
		root = add_node(root, num_arr[i]);
	}

	


	//print out instructions
	cout << '\n' << "To display tree, branching out towards the right, type \'DISPLAY\'." << endl;
	cout << "To add a number, type \'ADD\'." << endl;
	cout << "To remove a number, type \'REMOVE\'." << endl;
	cout << "To quit type \'QUIT\'." << endl << endl;

	bool inputting = true;
	char command[10];  //stores the command (ADD, DISPLAY, DELETE, QUIT) inputted by the user


	while (inputting) {
		cin >> command;

		//ADD NEW STUDENT(S)------------------------------------
		if (strcmp(command, "ADD") == 0) {
			int n;
			cout << "Enter number to add: ";
			cin >> n;
			cin.get();
			root = add_node(root, n); 
			cout << "Finished adding." << endl;
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\' to continue or \'QUIT\' to exit." << endl << endl;
		} 

		//DISPLAY TREE-------------------------------------
		else if (strcmp(command, "DISPLAY") == 0) {
			display_tree(root, 0);
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\' to continue or \'QUIT\' to exit." << endl << endl;
		}

		//REMOVE--------------------------------------
		else if (strcmp(command, "REMOVE") == 0) {
			int n;
			cout << "Enter number to delete: ";
			cin >> n;
			cin.get();
			root = remove_node(root, n); 
			cout << "Finished removing." << endl;
			cout << "\nEnter \'DISPLAY\', \'ADD\', \'REMOVE\' to continue or \'QUIT\' to exit." << endl << endl;
		}

		//QUIT------------------------------------------------
		else if (strcmp(command, "QUIT") == 0) {
			inputting = false;
			break;
		}

		//INVALID INPUT---------------------------------------
		else { //prompt user to re-enter command if something invalid was entered
			cout << "\nPlease enter either \'DISPLAY\', \'ADD\', \'REMOVE\', or \'QUIT\'." << endl;
		}
	} //end of while loop 


	
	return 0;

}







//--------------------------------------------------------FUNCTIONS------------------------------------------------------------


//function to add node
Node* add_node(Node* root, int num) {
	if (root == NULL) { //if no node in tree
		Node* n = new Node();
		n->data = num;
		return n;
	}
	else {
		if (num < root->data) {
			root->left = add_node(root->left, num);
		}
		else {
			root->right = add_node(root->right, num);
		}
	}

	return root;
}



//function to remove node
Node* remove_node(Node* root, int num) {
	//if tree empty (base case for recursion)
	if (root == NULL) { 
		return root;
	}

	//if tree not empty
	if (num < root->data) {
		root->left = remove_node(root->left, num);
	}
	else if (num > root->data) {
		root->right = remove_node(root->right, num);
	}
	else { //node to be deleted found
		if (root->left == NULL) { //no left child
			Node* temp = root->right; //save right child
			delete root;
			return temp;
		}
		else if (root->right == NULL) { //no right child
			Node* temp = root->left; //save left child
			delete root;
			return temp;
		}
		else { //has two children
			Node* temp = smallest_node(root->right); //find smallest number in subtree
			root->data = temp->data; //copy
			root->right = remove_node(root->right, temp->data);
		}
	}

	return root;
}



//function that returns the node with the smallest number data in the subtree
Node* smallest_node(Node* root) {
	Node* least = root;
	while (least != NULL && least->left != NULL) {
		least = least->left;
	}
	return least;
}



//function to visually display tree (root on left, branches out towards the right)
void display_tree(Node* root, int num_spaces) {
	if (root != NULL) {
		num_spaces = num_spaces + 10;
		display_tree(root->right, num_spaces);
		cout << endl;

		for (int i = 0; i < num_spaces; i++) {
			cout << " ";
		}
		cout << root->data << endl;
		display_tree(root->left, num_spaces);
	}

	return;
}
