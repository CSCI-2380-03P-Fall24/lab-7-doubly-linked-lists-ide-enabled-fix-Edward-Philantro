	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() { head = nullptr; tail = nullptr; numStudents = 0;}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) { 
		if (numStudents == 0){
		Node *newhead = new Node(s);

		head = newhead;
		tail = newhead;
		numStudents++;
		}else {
		Node *newhead = new Node(s);
		
		newhead->next = head; 
		head->prev = newhead;

		head = newhead;
		numStudents++;
		}
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
			if (numStudents == 0){
		Node *newtail = new Node(s);

		head = newtail;
		tail = newtail;
		numStudents++;
		}else {
		Node *newtail = new Node(s);
		
		newtail->prev = tail; 
		tail->next = newtail;

		tail = newtail;
		numStudents++;
		}
	}

	//Print out the names of each student in the list.
	void StudentList::printList() { 
		Node *current = head;
		
		while(current != nullptr) {
		cout << current->data.name << " ";
		current = current->next;
		}

	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (tail == nullptr){
			cout << "list is empty";
			return;
		}else if (numStudents == 1){
			Node *ridtail = tail;
			tail = tail->prev;
			
			delete ridtail;
			head = nullptr;
			tail = nullptr;
			numStudents--;

		}else {
			Node *ridtail = tail;
			tail = tail->prev;
			tail->next = nullptr;
			
			delete ridtail;
			numStudents--;
		}
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {if (head == nullptr){
			cout << "list is empty";
			return;
		}else if (numStudents == 1){
			Node *ridhead = head;
			
			delete ridhead;
			head = nullptr;
			tail = nullptr;
			numStudents--;

		}else {
			Node *ridhead = head;
			head = head->next;
			head->prev = nullptr;
			delete ridhead;
			numStudents--;
		}
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if(index > numStudents){
			cout << "position extends outside of list" << endl;
			addBack(s);
		}else{
			int i = 1;
			Node *current = head;
			if(index == 0){
				addFront(s);
				}else if (index == numStudents){
					addBack(s);
				}	
				else{
				while(i < index ){
				current = current->next;
				i++;	
				}
				Node *newNode = new Node(s);
				
				newNode->next = current->next;
				newNode->prev = current;
				current->next->prev = newNode;
				current->next = newNode;
				
				numStudents++;
			}
		}

	}


	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Student fixthis;
		bool check = false;
    	Node* current = head;
    	while (current != nullptr) {
        if (current->data.id == idNum) {
            check = true; 
			return current->data;
        }
		
        current = current->next;
    }
		if(check != true){
			cout << "no student match..." << endl;
			return fixthis;
		}
		
	}


	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
	bool check = true;
	Node* current = head;
	if(head == nullptr) {
    cout << "list is empty" << endl;
    return;
}
	if(head->data.id == idNum){
		popFront();
	}else if(tail->data.id == idNum){
		popBack();
	}else{
    	while (current != nullptr) {
			Node *next = current->next;
			if (current->data.id == idNum) {
            
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
				check = true;
				numStudents--;
        }
        current = next;
		check = false;
    	}
	}
	if (check != true){
		cout << "did not find student..." << endl;
	}
}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		bool check = false;
    	Node* current = head;
		
    	while (current != nullptr) {
        if (current->data.id == idNum) {
            check = true; 
			current->data.GPA = newGPA;
        }
		
        current = current->next;
    }
		if(check != true){
			cout << "no student match..." << endl;
		}
		
	}
	

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		Node *current = otherList.head;
		for(int i = 0; i < otherList.numStudents; i++){
			addBack(current->data);
    		current = current->next;
		}
		while(otherList.head != nullptr) {
   			Node *temp = otherList.head;
    		otherList.head = otherList.head->next;
    		delete temp;
	}
	otherList.tail = nullptr;
	otherList.numStudents = 0;
}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList fixthis;

		Node* current = head;
		
    	while (current != nullptr) {
        if (current->data.GPA >= minGPA) {
			fixthis.addFront(current->data);
        }
		
        current = current->next;
    }
		return fixthis;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold){

	Node* current = head;
	if (head == nullptr){
		cout << "list is empty." << endl;
		return;
	}else{
    	while (current != nullptr) {
			Node *next = current->next;
		if (current == tail && current->data.GPA < threshold) {
		popBack();
		}else if(current == head && current->data.GPA < threshold){
		popFront();
		}else if (current->data.GPA < threshold) {
            
				current->prev->next = current->next;
				current->next->prev = current->prev;
				Node *temp = current->next;
				delete current;
				numStudents--;
        }
        current = next;
    	}
	}
}
