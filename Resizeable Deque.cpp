#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
class Resizable_deque{
private:
	Type *array;
	int front;
	int back;
	int deque_size;
	int current_capacity;
	int initial_capacity;
	int ID;

public:

	Resizable_deque(int n); //n is the initial capacity of the array
	~Resizable_deque();

	int get_front() const;
	int get_back() const; //enter throw error
	int get_deque_size() const;
	bool empty() const;
	int get_currcapacity() const;
	int getID() const;
	void setID(int id);

	void swap(Resizable_deque<Type> & other);
	//Resizable_deque(const Resizable_deque& u);//copy constructor

	//Resizable_deque operator=(Resizable_deque const & other);
	Resizable_deque& operator=(const Resizable_deque& a) 
	{ //overloaded assignment operator
		current_capacity = a.get_currcapacity();
		deque_size = a.deque_size;
		back = a.back;
		front = a.front;
		if (this != &a)	{
			delete[] this->array;
			this->array = new Type[current_capacity];
		
			for (int i = 0; i < current_capacity; i++)
			{
				this->array[i] = a.array[i];
			}
		}
		return *this; 
	} 

	void push_front(const Type e);
	void push_back(const Type e);
	void pop_front();
	void pop_back();
	void pop_front_back();
	void clear();
	void display();

};

/////////////////////////////////////////////////////////////////////
//******************CONSTRUCTORS AND DESTRUCTOR*******************//
///////////////////////////////////////////////////////////////////

//constructor
template<typename Type>
Resizable_deque<Type>::Resizable_deque(int n): initial_capacity(n) 
{
	if (n < 10)
		initial_capacity = 10;

	//create a new array and initialize its variables
	array = new Type[initial_capacity];
	current_capacity = initial_capacity;
	front = 0;
	back = 0;
	deque_size = 0;

	//initialize the array
	for(int i=0; i<current_capacity; i++)
	{
		array[i]=0;
	}

};

//destructor
template<typename Type>
Resizable_deque<Type>::~Resizable_deque()
{
	//delete[] array;
};

/////////////////////////////////////////////////////////////////////
//****************************ACCESSORS***************************//
///////////////////////////////////////////////////////////////////

//return front object//error if array empty
template<typename Type>
int Resizable_deque<Type>::get_front() const 
{
	if (empty()){
		throw out_of_range("Deque is Empty...");
	}
	else{
		return array[front];
	}
};

//return back object//error if array empty
template<typename Type>
int Resizable_deque<Type>::get_back() const 
{
	if (empty()){
		throw out_of_range("Deque is Empty...");
	}
	else{
		return array[back];
	}
};

//return size
template<typename Type>
int Resizable_deque<Type>::get_deque_size() const
{
	return deque_size;
};

//return true if empty
template<typename Type>
bool Resizable_deque<Type>::empty() const
{	
	if(deque_size==0)
		return true;
	else
		return false;
};

//return current capacity
template<typename Type>
int Resizable_deque<Type>::get_currcapacity() const
{
	return current_capacity;
};

//return ID
template<typename Type>
int Resizable_deque<Type>::getID() const 
{
	return ID;
}

//set ID
template<typename Type>
void Resizable_deque<Type>::setID(int id)  
{
	ID = id;
}

/////////////////////////////////////////////////////////////////////
//****************************MUTATORS***************************//
///////////////////////////////////////////////////////////////////

//swap function
template<typename Type>
void Resizable_deque<Type>::swap(Resizable_deque<Type>& other){
	std::swap(this->front, other.front);
	std::swap(this->back, other.back);
	std::swap(this->deque_size, other.deque_size);
	std::swap(this->current_capacity, other.current_capacity);
	std::swap(this->array, other.array);
}

// //assignment operator function
//template<typename Type>
//Resizable_deque<Type>::Resizable_deque(const Resizable_deque &u)
//{
//	initial_capacity = u.get_currcapacity();
//	deque_size = u.get_deque_size();
//
//	if (this != &u)
//	{
//		delete[] this->array;
//		this->array = new Type[initial_capacity];
//
//		for (int i = 0; i < initial_capacity; i++)
//		{
//			array[i] = u[i];
//		}
//	}
//}
 //template<typename Type>
 /*Resizable_deque<int>::operator=(Resizable_deque const &other)
 {
 	initial_capacity = other.get_currcapacity();
 	deque_size = other.get_deque_size();

 	if(this!=&other)
 	{
 		delete[] this->array;
 		this->array = new Type[initial_capacity];

 		for(int i=0; i<initial_capacity; i++)
 		{
			array[i] = other.array[i];
 		}
 	}

 	return *this;
 }*/

//add element to the front 
template<typename Type>
void Resizable_deque<Type>::push_front(const Type e)
{
	if( current_capacity <= deque_size)
	{	

		// deque_size = deque_size + 1;
		// front = ((front - 1) % current_capacity) + current_capacity;
		// array[front] = e;

		int prev_curr_capacity = current_capacity;

		//create an array of double the current capacity
		current_capacity = current_capacity*2;
		Type *darray = new Type[current_capacity];

		//initialize array
		for (int i=0; i<current_capacity; i++)
		{
			darray[i] = 0;
		}

		for(int i=0; i<prev_curr_capacity; i++)
		{
			darray[i] = array[front];
			front = (front + 1) % prev_curr_capacity;

		}

		front = 0;
		back = deque_size - 1;

		//create a temporary array to swap the pointers of the two arrays
		Type *temp = new Type[current_capacity];
		temp = array;
		array = darray;
		darray = temp;

		//delete the other arrays
		// delete [] darray;
		// delete [] temp; 

	}

	//increment deque size and sift the position of front index
	if (front==0)
	{
		deque_size = deque_size + 1;
		front = ((front - 1) % current_capacity) + current_capacity;
		array[front] = e;
	}
	else
	{
		deque_size = deque_size + 1;
		front = (front - 1) % current_capacity;
		array[front] = e;
	}
}


//add element to the back 
template<typename Type>
void Resizable_deque<Type>::push_back(const Type e)
{	
	if( current_capacity <= deque_size)
	{
		int prev_curr_capacity = current_capacity;

		//create an array of double the current capacity
		current_capacity = current_capacity*2;
		Type *darray = new Type[current_capacity];

		//initialize array
		for (int i=0; i<current_capacity; i++)
		{
			darray[i] = 0;
		}

		//transfer elements from array to darray
		for(int i=0; i<prev_curr_capacity; i++)
		{
			darray[i] = array[front];
			front = (front + 1) % prev_curr_capacity;

		}

		front = 0;
		back = deque_size;

		//create a temporary array to swap the pointers of the two arrays
		Type *temp = new Type[current_capacity];
		temp = array;
		array = darray;
		darray = temp;

		//delete the other arrays
		// delete [] darray;
		// delete [] temp; 

	}
	//increment deque size and sift the position of back index
	//cout << back << endl ;
	array[back] = e;
	deque_size = deque_size + 1;
	back = (back + 1) % current_capacity;	
}

//remove element from the front 
template<typename Type>
void Resizable_deque<Type>::pop_front()
{	
	//throw an error if deque is empty
	if (empty()==true)
	{
		cout <<"Error! Removal from an empty array..."<<endl;
		throw out_of_range("Resizable deque is empty...");
	}

	else
	{	
		//set the value of the element to be removed to 0
		array[front] = 0;

		//increment the index of front
		front = (front+1)%current_capacity;

		//decrement the deque size
		deque_size = deque_size-1;

		//half the current capacity if it the size of deque is quarter of the current capacity
		int quar_curr_cap = current_capacity/4; //quarter of current capacity
		int dinicap = 2*initial_capacity; //double of initial capacity

		if (deque_size <= quar_curr_cap && current_capacity >= dinicap)
		{	
			int prev_curr_capacity = current_capacity;

			//create an array of half the current capacity
			current_capacity = current_capacity/2;
			Type *harray = new Type[current_capacity];

			//initialize array
			for (int i=0; i<current_capacity; i++)
			{
				harray[i] = 0;
			}

			//transfer elements from array to harray
			for(int i=0; i<prev_curr_capacity; i++)
			{
				harray[i] = array[front];
				front = (front + 1) % prev_curr_capacity;

			}

			front = 0;
			back = deque_size - 1;

			//create a temporary array to swap the pointers of the two arrays
			Type *temp = new Type[prev_curr_capacity];
			temp = array;
			array = harray;
			harray = temp;

			//delete the other arrays
			// delete [] harray;
			// delete [] temp; 
		}

	}
}

//remove element from the back 
template<typename Type>
void Resizable_deque<Type>::pop_back()
{	
	//throw an error if deque is empty
	if (empty()==true)
	{	
		cout <<"Error! Removal from an empty array..."<<endl;
		throw out_of_range("Resizable deque is empty...");
	}
	else
	{	
		//decrement the index of back
		if (back==0)
		{	
			//set the value of the element to be removed to 0
			back = ((back - 1) % current_capacity) + current_capacity;
			array[back] = 0;
		}
		else
		{	
			//set the value of the element to be removed to 0
			back = (back-1) % current_capacity;
			array[back] = 0;
		}

		//decrement the deque size
		deque_size = deque_size-1;

		//half the current capacity if it the size of deque is quarter of the current capacity
		int quar_curr_cap = current_capacity/4; //quarter of current capacity
		int dinicap = 2*initial_capacity; //double of initial capacity

		if (deque_size <= quar_curr_cap && current_capacity >= dinicap)
		{
			int prev_curr_capacity = current_capacity;

			//create an array of half the current capacity
			current_capacity = current_capacity/2;
			Type *harray = new Type[current_capacity];

			//initialize array
			for (int i=0; i<current_capacity; i++)
			{
				harray[i] = 0;
			}

			//transfer elements from array to harray
			for(int i=0; i<prev_curr_capacity; i++)
			{
				harray[i] = array[front];
				front = (front + 1) % prev_curr_capacity;

			}

			front = 0;
			//back = deque_size - 1;

			//create a temporary array to swap the pointers of the two arrays
			Type *temp = new Type[current_capacity];
			temp = array;
			array = harray;
			harray = temp;

			//delete the other arrays
			// delete [] harray;
			// delete [] temp; 
		}
	}
}

//removes the elements from the front and back of the deque
template<typename Type>
void Resizable_deque<Type>::pop_front_back()
{
	pop_front();
	pop_back();
}

//empties the deque
template<typename Type>
void Resizable_deque<Type>::clear()
{
	//delete the original array
	delete [] array;
	initial_capacity = 10;

	//create a new array and initialize its variables
	array = new Type[initial_capacity];
	current_capacity = initial_capacity;
	front = 0;
	back = 0;
	deque_size = 0;

	//initialize the array
	for(int i=0; i<current_capacity; i++)
	{
		array[i]=0;
	}

}

template<typename Type>
void Resizable_deque<Type>::display()
{
	cout << "| ";
	for(int i=0; i < current_capacity; i++){
		cout << array[i] << " | ";
	}
	cout << endl;
}

//global variables and function declarations

vector<Resizable_deque<int>> v;
void printmenu();
void newdeque();
Resizable_deque<int>& finddeque(int);
void addelem();
void removeelem();
void getnofelem();
void getcurcap();
void ifempty();
void displaydeque();
void cleardeque();
void swapdeques();
void copyelems();

//main function
int main()
{	
	printmenu();
	
	return 0;
}

//menu function
void printmenu()
{
	int choice=0;
	do
	{	//print options
		cout<<"Please select a command: "<<endl
			<<"1) Create a new deque."<<endl
			<<"2) Copy the elements of an existing deque to a new deque."<<endl
			<<"3) Add elements to a deque."<<endl
			<<"4) Remove elements from a deque."<<endl
			<<"5) Get number of elements in a deque."<<endl
			<<"6) Get the current capacity of a deque."<<endl
			<<"7) Check if a deque is empty. "<<endl
			<<"8) Display a deque."<<endl
			<<"9) Clear a deque."<<endl
			<<"10) Swap the elements of two deques."<<endl			
			<<"11) Exit"<<endl;

			cin >> choice;

		switch (choice)
		{
			case 1: 
				newdeque();
				break;

			case 2:
				copyelems();
				break;

			case 3:
				addelem();
				break;

			case 4:
				removeelem();
				break;

			case 5:
				getnofelem();
				break;

			case 6:
				getcurcap();
				break;

			case 7:
				ifempty();
				break;

			case 8:
				displaydeque();
				break;

			case 9:
				cleardeque();
				break;
			
			 case 10:
			 	swapdeques();
			 	break;

		}

	} while (choice != 11 );

}

//create a new deque
void newdeque()
{
	int ini_cap;
	cout << "Please enter the initial capacity of your resizable deque." << endl;
	cin >> ini_cap;

	//add a new deque into a vector of deques
	v.push_back(Resizable_deque<int>(ini_cap));

	cout << endl << "DEQUE SUCCESSFULLY CREATED!" << endl;
	cout << "Your deque has been assigned an ID " << v.size() <<'.' << endl;

	//set the ID of the deque
	v[v.size()-1].setID(v.size());
	cout << "Please use this ID to carry out further methods on this deque." << endl << endl;
}

Resizable_deque<int>& finddeque(int id)
{	
	if(v.size()==1)
		return v[0];
	else
	{	
		for(int i=0; i < v.size(); i++)
		{
			if (v[i].getID()==id)
			{
				return v[i];
			}
		}
	}
	//return v[0];
}

void addelem()
{	
	int ForB = 0;
	int nofelem = 0;
	int elem = 0;
	int deqID = 0;
	bool exist = false;
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	/*Resizable_deque<int> u = ;*/
	if(v.size()>=1)
	{	
		cout << "Would you like to add elements to the front or back of the deque?" << endl;
		cout << "For front, enter 1." << endl << "For back, enter 2." << endl;
		cin >> ForB;

		cout << "How many elements would you like to add?" << endl;
		cin >> nofelem;

		switch (ForB)
		{//add front
			case 1:
				
				cout << "Enter the " << nofelem << " elements to be added." << endl;
				for (int i=0; i<nofelem; i++)
				{
					cout << "Element: ";
					cin >> elem;
					finddeque(deqID).push_front(elem);
				}
				break;
			case 2:
				//Resizable_deque<int> u = finddeque();
				//finddeque().display();
				//finddeque().push_back(1);
				cout << "Enter the " << nofelem << " elements to be added." << endl;
				for (int i=0; i<nofelem; i++)
				{
					cout << "Element: ";
					cin >> elem;
					finddeque(deqID).push_back(elem);
				}
				break;
	
			}
		}

	cout << endl;
	finddeque(deqID).display();
	cout << nofelem << " ELEMENTS SUCCESSFULLY ADDED. " << endl << endl;
}

void removeelem()
{	
	int ForB = 0; //front or back 
	int nofelem = 0;
	int elem = 0;
	int deqID = 0;
	bool exist = false;
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl;
		newdeque();
	}
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	//Resizable_deque<int> u = ;
	if(v.size()>=1)
	{
		cout << "Would you like to remove elements front the front or back of the deque?" << endl;
		cout << "For front, enter 1." << endl << "For back, enter 2." << endl << "For front and back, enter 3." << endl;
		cin >> ForB;

		cout << "How many elements would you like to remove?" << endl;
		cin >> nofelem;

		switch (ForB)
		{
			case 1://remove front
				for (int i=0; i<nofelem; i++)
					finddeque(deqID).pop_front();
				break;
			case 2://remove back
				for (int i=0; i<nofelem; i++)
					finddeque(deqID).pop_back();
				break;
			case 3://remove front and back
				for (int i=0; i<nofelem; i++)
					finddeque(deqID).pop_front_back();
				break;

		}
	}

	cout << endl;
	finddeque(deqID).display();
	cout << nofelem << " ELEMENTS SUCCESSFULLY REMOVED. " << endl << endl;
}
//get deque size
void getnofelem()
{
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	int deqID = 0;
	bool exist = false;
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	if(v.size()>=1)
	{
		cout << "THERE ARE " << finddeque(deqID).get_deque_size() << " ELEMENTS IN YOUR DEQUE." << endl << endl;
	}
}
//get current capacity
void getcurcap()
{
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	int deqID = 0;
	bool exist = false;
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	if(v.size()>=1)
	{
		cout << "THE CAPACITY OF THE DEQUE IS " << finddeque(deqID).get_currcapacity() << endl << endl;
	}
}
//check if empty
void ifempty()
{
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	int deqID = 0;
	bool exist = false;
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	if(v.size()>=1)
	{
		if (finddeque(deqID).empty()==true)
		{
			cout << "THE DEQUE IS EMPTY." << endl << endl;
		}
		else
			cout << "THE DEQUE IS NOT EMPTY." << endl << endl;
	}
}

//display deque
void displaydeque()
{
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	int deqID = 0;
	bool exist = false;
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	if(v.size()>=1)
	{
		finddeque(deqID).display();
	}
}
//clear deque
void cleardeque()
{
	if(v.size()==0)
	{
		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
		newdeque();
	}
	int deqID = 0;
	bool exist = false;
	do {
		cout << "Which deque would you like to use? Please enter its ID." << endl;
		cin >> deqID;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getID() == deqID) {
				exist = true;
			}
		}
	} while (!exist);
	exist = false;
	if(v.size()>=1)
	{
		finddeque(deqID).clear();
		finddeque(deqID).display();
		cout << "YOUR DEQUE HAS BEEN CLEARED." << endl << endl;
	}
}
//swap deques
 void swapdeques()
 {
 	if(v.size()==0)
 	{
 		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
 		newdeque();
 		v[0].display();
 	}
 	if(v.size()>=1)
 	{
 		if (v.size()==1)
 		{//one deque only
 			cout << "Please create a new deque to swap your existing deque with." <<endl;
 			newdeque();
			v[0].display();
 			v[1].display();
			v[0].swap(v[1]);
			cout << "The deques have been swapped." << endl;
			v[0].display();
			v[1].display();
 		}

 		else
 		{//if more than one deques
 			int deqID1 = 0;
			int deqID2 = 0;
			cout << "Enter ID of the first deque." << endl;
			cin >> deqID1;
 			cout << "Which deque would you like to swap with? Please enter its ID." << endl;
			cin >> deqID2;
			v[deqID1 - 1].display();
			v[deqID2 - 1].display();
			v[deqID1 - 1].swap(v[deqID2 - 1]);
			cout << "The deques have been swapped." << endl;
			v[deqID1 - 1].display();
			v[deqID2 - 1].display();
 		}

 	}
}
// cope one deque onto the other
void copyelems()
{	
	 if(v.size()==0)
 	{
 		cout << "You do not have any existing deques." << endl << "Please create a new deque." << endl << endl;
 		newdeque();
 		v[0].display();
 	}
 	if(v.size()>=1)
 	{
 		if (v.size()==1)
 		{	
 			//Resizable_deque<int> u(5);
			v.push_back(Resizable_deque<int>(1));
 			v[v.size()-1] = v[0];
 			cout << "New deque successfully created from deque ID 1." <<endl;
 			cout << "Deque to be copied: " <<endl;
			v[0].display();
			cout << "New deque: " <<endl;
 			v[v.size()-1].display();
			v[v.size() - 1].setID(v.size());
 		}

 		else
 		{	
 			//Resizable_deque<int> u(5);
 			int deqID = 0;
			cout << "Enter ID of the deque that you would like to copy." << endl;
			cin >> deqID;
			cout << "Deque to be copied: " <<endl;
			v[deqID - 1].display();
			cout << "New deque: " <<endl;
			v.push_back(Resizable_deque<int>(1));
			v[v.size()-1] = v[deqID - 1];
			v[v.size()-1].display();
			v[v.size() - 1].setID(v.size());
 		}

 	}
}

