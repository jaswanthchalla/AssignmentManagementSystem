#include <bits/stdc++.h>
#include <fstream>
using namespace std;

const int MAX_LEN = 50;


//For student records
class Node1 {
public:
	int student_id;
    string name;
    string group_partner;
    int group_id;
    string assignment_name_id;
    string deadline;
    string status;
    float offline_marks;
    float viva_marks;
    int ht;

    Node1* left;
    Node1* right;

    // Constructor
    Node1(int id, string& n, string& gp, int gid, string& ani, 
                    string& d, string& s, float om, float vm) {
        student_id = id; name = n; group_partner = gp; group_id = gid; assignment_name_id = ani; 
            deadline = d; status = s; offline_marks = om; viva_marks = vm; left = nullptr; right = nullptr; ht = 1; 
    }
};

//For student-assignment record
class Node3{
public:
	int student_group_id;
    string status;
    float marks_given;
    int ht;

    Node3* left;
    Node3* right;

    // Constructor
    Node3(int sgid, string& s, float mg){
        student_group_id = sgid; status = s; marks_given = mg; left = nullptr; right = nullptr; ht = 1;
    }
};

//For assignment record
class Node2{
public:
	int assignment_id;
    string topic_name;
    string status;
    Node3* student_group;
    int ht;

    Node2* left;
    Node2* right;

    // Constructor
    Node2(int id, string& tn) {
        assignment_id = id; topic_name = tn; status = "Declared"; student_group = nullptr;
                     left = nullptr; right = nullptr; ht = 1;
    }
};


Node1* student = NULL ;
Node2* assignment = NULL ;


Node1* create_student(int student_id, string &name, string &group_partner,int group_id,
        string &assignment_name_id,string &deadline,string &status,float offline_marks,float viva_marks)
{
	Node1* nptr = new Node1(student_id, name, group_partner, group_id, assignment_name_id, deadline, status, offline_marks, viva_marks);
    return nptr;
}

Node2* create_assignment(int assignment_id, string& topic_name) {
    Node2* nptr = new Node2(assignment_id, topic_name);
    return nptr;
}


Node3* create_student_group(int student_group_id, string& status, float offline_marks1, 
            float viva_marks1, float offline_marks2, float viva_marks2) {

    Node3* nptr = new Node3(student_group_id, status, 
                                 	max(offline_marks1 + viva_marks1, offline_marks2 + viva_marks2));
    return nptr;
}


// Traversing Functions

void visit_1(Node1* ptr)
{
	cout<<ptr->student_id;
	cout<<ptr->name;
	cout<<ptr->group_partner;
	cout<<ptr->group_id;
	cout<<ptr->assignment_name_id;
	cout<<ptr->deadline;
	cout<<ptr->status;
	cout<<ptr->offline_marks;
	cout<<ptr->viva_marks;
	cout<<"-----------"<<endl;
}

void inOrder_1(Node1* root) {
    if (root != nullptr) {
        inOrder_1(root->left);
        visit_1(root); 
        inOrder_1(root->right);
    }
}

void visit_3(Node3* ptr)
{
	cout<<ptr->student_group_id;
	cout<<ptr->status;
	cout<<ptr->marks_given;
	cout<<"----------\n";
}

void inOrder_3(Node3* ptr)
{
	Node3* root = ptr;
	if(root!=NULL)
	{
		inOrder_3(root->left);
		visit_3(root);
		inOrder_3(root->right);
	}
}

void visit_2(Node2* ptr)
{
	cout<<ptr->assignment_id;
	cout<<ptr->topic_name;
	cout<<ptr->status;
	inOrder_3(ptr->student_group);
	cout<<"-----------\n";
}

void inOrder_2(Node2* assignment)
{
	Node2* root = assignment;
	if(root!=NULL)
	{
		inOrder_2(root->left);
		visit_2(root);
		inOrder_2(root->right);
	}
}


// Function for Node1

Node1* search_1(Node1* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->student_id == key)
    {
        return root;
    }
 
    if(key > root->student_id)
    {
        search_1(root->right, key);
    }
    else
    {
        search_1(root->left, key);
    } 
}

int height_1(Node1* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

// rotates to the left
Node1* rotate_left_1(Node1* root)
{
    Node1* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_1(root);
    right_child->ht = height_1(right_child);
 
    // return the new node after rotation
    return right_child;
}

// rotates to the right
Node1* rotate_right_1(Node1* root)
{
    Node1* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_1(root);
    left_child->ht = height_1(left_child);
 
    // return the new node after rotation
    return left_child;
}

// calculates the balance factor of a node
int balance_factor_1(Node1* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

Node1* insert_1(Node1* root, Node1* new_node)
{
	int student_id = new_node->student_id;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (student_id > root->student_id)
    {
        // insert the new node to the right
        root->right = insert_1(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_1(root) == -2)
        {
            if (student_id > root->right->student_id)
            {
                root = rotate_left_1(root);
            }
            else
            {
                root->right = rotate_right_1(root->right);
                root = rotate_left_1(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_1(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_1(root) == 2)
        {
            if (student_id < root->left->student_id)
            {
                root = rotate_right_1(root);
            }
            else
            {
                root->left = rotate_left_1(root->left);
                root = rotate_right_1(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_1(root);
    return root;
}






/////Functions for Node2

Node2* search_2(Node2* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->assignment_id == key)
    {
        return root;
    }
 
    if(key > root->assignment_id)
    {
        search_2(root->right, key);
    }
    else
    {
        search_2(root->left, key);
    } 
}

int height_2(Node2* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

// rotates to the left
Node2* rotate_left_2(Node2* root)
{
    Node2* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_2(root);
    right_child->ht = height_2(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
Node2* rotate_right_2(Node2* root)
{
    Node2* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_2(root);
    left_child->ht = height_2(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor_2(Node2* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}


Node2* insert_2(Node2* root, Node2* new_node)
{
	int assignment_id = new_node->assignment_id;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (assignment_id > root->assignment_id)
    {
        // insert the new node to the right
        root->right = insert_2(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_2(root) == -2)
        {
            if (assignment_id > root->right->assignment_id)
            {
                root = rotate_left_2(root);
            }
            else
            {
                root->right = rotate_right_2(root->right);
                root = rotate_left_2(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_2(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_2(root) == 2)
        {
            if (assignment_id < root->left->assignment_id)
            {
                root = rotate_right_2(root);
            }
            else
            {
                root->left = rotate_left_2(root->left);
                root = rotate_right_2(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_2(root);
    return root;
}




/////Functions for Node3

Node3* search_3(Node3* root, float key)
{
    if (root == NULL)
    {
        return NULL;
    }
 
    if(root->marks_given == key)
    {
        return root;
    }
 
    if(key > root->marks_given)
    {
        search_3(root->right, key);
    }
    else
    {
        search_3(root->left, key);
    } 
}

int height_3(Node3* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
        return (lh);
    return (rh);
}

// rotates to the left
Node3* rotate_left_3(Node3* root)
{
    Node3* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height_3(root);
    right_child->ht = height_3(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
Node3* rotate_right_3(Node3* root)
{
    Node3* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height_3(root);
    left_child->ht = height_3(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor_3(Node3* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

Node3* insert_3(Node3* root, Node3* new_node)
{
	float marks_given = new_node->marks_given;
	
    if (root == NULL)
    {
        //Node1* new_node = create(student_id);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (marks_given > root->marks_given)
    {
        // insert the new node to the right
        root->right = insert_3(root->right, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_3(root) == -2)
        {
            if (marks_given > root->right->marks_given)
            {
                root = rotate_left_3(root);
            }
            else
            {
                root->right = rotate_right_3(root->right);
                root = rotate_left_3(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert_3(root->left, new_node);
 
        // tree is unbalanced, then rotate it
        if (balance_factor_3(root) == 2)
        {
            if (marks_given < root->left->marks_given)
            {
                root = rotate_right_3(root);
            }
            else
            {
                root->left = rotate_left_3(root->left);
                root = rotate_right_3(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height_3(root);
    return root;
}



// ---------->>>>

Node1* insert_student(Node1* student, int student_id1, int student_id2, string& name,
                             string& group_partner, int group_id, string& assignment_name_id, 
                             string& deadline, string& status, float offline_marks1, 
                             float viva_marks1, float offline_marks2, float viva_marks2, int assignment_id){

	Node1* nptr1 = create_student(student_id1,name,group_partner,group_id,assignment_name_id,
                                    deadline,status,offline_marks1,viva_marks1);
	Node1* nptr2 = create_student(student_id2,group_partner,name,group_id,assignment_name_id,
                                    deadline,status,offline_marks2,viva_marks2);

	if (search_1(student, student_id1) || search_1(student, student_id2)) {
        cout << "Student with same id already exists\n\n";
    } else {
        student = insert_1(student, nptr1);
        student = insert_1(student, nptr2);

        // Checking in Assignment Record
        Node2* ptr = assignment;
        Node2* found = search_2(ptr, assignment_id);

        if (found == nullptr) {
            Node2* nptr = create_assignment(assignment_id, assignment_name_id);
            assignment = insert_2(assignment, nptr);
        }

        Node3* nptr3 = create_student_group(group_id, status, offline_marks1,
        										 viva_marks1, offline_marks2, viva_marks2);
        ptr = search_2(assignment, assignment_id);

        ptr->student_group = insert_3(ptr->student_group, nptr3);
    }

    return student;
}


// ------------>>>>>>>

Node2* insert_assignment(Node1* student, Node2* assignment, string& topic_name,
             int assignment_id, vector<int> student_ids, vector<string> names, 
             vector<int> group_ids, string deadline, 
             vector<string> status, vector<float>& offline_marks, 
             vector<float>& viva_marks, int num_stud) {
    Node2* nptr = create_assignment(assignment_id, topic_name);

    Node2* ptr = assignment;
    Node2* found = search_2(ptr, assignment_id);

    if (found != nullptr) {
        cout << "An assignment with same id already exists\n\n";
    } else {
        if (found == 0) { // This condition seems redundant
            assignment = insert_2(assignment, nptr);
        }

        for (int i = 0; i < num_stud; i += 2) {
            Node3* nptr3 = create_student_group(group_ids[i], status[i], offline_marks[i], viva_marks[i], offline_marks[i + 1], viva_marks[i + 1]);
            nptr->student_group = insert_3(nptr->student_group, nptr3);
        }

        for (int i = 0; i < num_stud; i += 2) {
            Node1* nptr1 = create_student(student_ids[i], names[i], names[i + 1], group_ids[i], topic_name, deadline, status[i], offline_marks[i], viva_marks[i]);
            Node1* nptr2 = create_student(student_ids[i + 1], names[i + 1], names[i], group_ids[i + 1], topic_name, deadline, status[i], offline_marks[i + 1], viva_marks[i + 1]);

            if (search_1(student, nptr1->student_id) || search_1(student, nptr2->student_id)) {
                cout << "Student with same id already exists\n\n";
            } else {
                student = insert_1(student, nptr1);
                student = insert_1(student, nptr2);
            }
        }
    }
    return assignment;
}

// --------->>>>>

int flag = 1;

int check_status(Node3* root)
{
	if(root!=NULL)
	{
		check_status(root->left );
		if(root->status != "Evaluated")
		{
			flag = 0;
		}
		check_status(root->right );
	}
	
	return flag;	
}

void check_asg_grp(Node2* root)
{
	int a;
	if(root!=NULL)
	{
		check_asg_grp(root->left);
		flag = 1;
		a = check_status(root->student_group);
		if(a == 1)
		{
			root->status = "Evaluated";
		}
		check_asg_grp(root->right);
	}
}

void change_status(Node1* student, Node2* assignment, int student_id1, int student_id2, 
                    string& status, float offline_marks1, float viva_marks1, float offline_marks2, 
                    float viva_marks2, int asg_id) {
    float marks;    
    Node1* ptr1 = search_1(student, student_id1);
    Node1* ptr2 = search_1(student, student_id2);

    if (ptr1 != nullptr && ptr2 != nullptr) {
        marks = max(ptr1->offline_marks + ptr1->viva_marks, ptr2->offline_marks + ptr2->viva_marks);

        ptr1->status = status;
        ptr1->offline_marks = offline_marks1;
        ptr1->viva_marks = viva_marks1;

        ptr2->status = status;
        ptr2->offline_marks = offline_marks2;
        ptr2->viva_marks = viva_marks2;
    }

    // Changing in student group records
    Node2* ptr = assignment;
    Node2* nptr = search_2(assignment, asg_id);
    if (nptr != nullptr) {
        Node3* ptr3 = search_3(nptr->student_group, marks);
        ptr3->status = status;
        ptr3->marks_given = max(offline_marks1 + viva_marks1, offline_marks2 + viva_marks2);
    }

    // Changing status of Assignment
    check_asg_grp(assignment); // Assuming check_asg_grp is defined appropriately
}


// -------------->>>>>>

void print_declared_not_eval(Node2* root) {
    if (root != nullptr) {
        print_declared_not_eval(root->left);

        if (root->status != "Evaluated" && root->status != "DueDateOver") {
            cout << "\nAssignment id: " << root->assignment_id << endl;
            cout << "Topic Name: " << root->topic_name << endl;
            cout << "Status: " << root->status << endl;
            cout << "-----------\n";
        }

        print_declared_not_eval(root->right);
    }
}


//------------->>>>>>

bool found = false; 
void check_q5(Node3* root) {
    if (root != nullptr) {
        check_q5(root->left);

        if (root->status == "NotSubmitted") {
            cout << "    Group id: " << root->student_group_id << endl;
            cout << "    Status: " << root->status << endl;
            found = true;
        }

        check_q5(root->right);
    }
}

void print_stud_not_submitted(Node2* assignment, Node1* student) {
    if (assignment != nullptr) {
        print_stud_not_submitted(assignment->left, student);

        if (assignment->status == "DueDateOver") {
            cout << "\nAssignment id: " << assignment->assignment_id << endl;
            cout << "Topic Name: " << assignment->topic_name << endl;
            cout << "Status: " << assignment->status << endl << endl;

            Node3* ptr2 = assignment->student_group;
            if (ptr2 != nullptr) {
                // found = false; // Reset found flag for each assignment
                check_q5(ptr2);
                if (found == false) {
                    cout << "    No One\n";
                }
                cout << "------------------------------\n\n";
            }
        }

        print_stud_not_submitted(assignment->right, student);
    }
}


////--------->>>>>>>

void print_stud_notEval_sub(Node1* root) {
    if (root != nullptr) {
        print_stud_notEval_sub(root->left);

        if (root->status == "Submitted") {
            cout << "\nGroup id: " << root->group_id << endl;
            cout << "Assignment Topic: " << root->assignment_name_id << endl;
            cout << "Member 1: " << root->name << endl;
            cout << "Member 2: " << root->group_partner << endl;
            cout << "Submitted but not Evaluated\n\n\n";
        } else if (root->status == "Evaluated" && root->viva_marks == 0) {
            cout << "\nGroup id: " << root->group_id << endl;
            cout << "Assignment Topic: " << root->assignment_name_id << endl;
            cout << "Member 1: " << root->name << endl;
            cout << "Member 2: " << root->group_partner << endl;
            cout << "Evaluated but Viva is Not Yet Completed\n\n\n";
        }

        print_stud_notEval_sub(root->right);
    }
}


//------------->>>>>>>

void print_dec_order(Node2* assignment, int assignment_id) {
    Node2* ptr = search_2(assignment, assignment_id);
    if (ptr == nullptr) {
        cout << "No such assignment\n\n";
    } else {
        Node3* ptr1 = ptr->student_group;
        cout << "\nAssignment id: " << ptr->assignment_id << endl;
        cout << "Topic Name: " << ptr->topic_name << endl;

        inOrder_3(ptr1);
    }
}


//------------->>>>>>>>

Node3* get_rightmost_node(Node3* root)
{
	if(root!=NULL)
	{
		if(root->right == NULL)
		{
			return root;
		}
		if(root->right!=NULL)
		{
			return get_rightmost_node(root->right);
		}
	}
}

void print_top_stud(Node2* root) {
    if (root != nullptr) {
        print_top_stud(root->left);

        cout << "\nAssignment id: " << root->assignment_id << endl;
        cout << "Topic Name: " << root->topic_name << endl;

        Node3* ptr1 = root->student_group;
        Node3* right_node = get_rightmost_node(ptr1);
        cout << "    Group id: " << right_node->student_group_id << endl;
        cout << "    Top Marks Given: " << right_node->marks_given << endl << endl;

        print_top_stud(root->right);
    }
}

//--------------->>>>>>>>>>>

void range_search(Node2* root , int a1 , int a2)
{
	if(root!=NULL)
	{
		range_search(root->left , a1, a2);
		if(a1 < root->assignment_id && a2 > root->assignment_id)
		{
			cout<<root->assignment_id << endl;
			cout<<root->topic_name<<endl;
			cout<<root->status<<endl;
			inOrder_3(root->student_group);
			cout<<"-----------\n";
		}
		range_search(root->right , a1, a2);
	}
}






void Display_Marks(int student_id) {
    Node1* ptr = search_1(student, student_id);
    if (ptr != nullptr) {
        cout << ptr->student_id << endl;
        cout << ptr->name << endl;
        cout << ptr->status << endl;
        cout << ptr->offline_marks << endl;
        cout << ptr->viva_marks << endl;
    }
}

void Display_grp_details(int student_id) {
    Node1* ptr = search_1(student, student_id);
    if (ptr != nullptr) {
        cout << ptr->student_id << endl;
        cout << ptr->name << endl;
        cout << ptr->group_partner << endl;
        cout << ptr->group_id << endl;
        cout << ptr->assignment_name_id << endl;
        cout << ptr->deadline << endl;
        cout << ptr->status << endl;
        cout << ptr->offline_marks << endl;
        cout << ptr->viva_marks << endl;
    }
}




int main(){

	while(1){
		cout << "Choose the correct choice :\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "3. Exit Program\n";

        int op;
        cin>>op;
        string name, name2, password1;
		int password ,found;
		Node1* ptr;
		int key;


        if(op == 1){
        	cout<<"You choose 1 \n\n";
			cout<<"------------------Students Portal-------------------\n";
			found = 0;
			cin >> name;
			cin >> password;
			cout<< name << " " << password << endl;
			ptr = search_1(student, password);

			if(ptr){
				cout<<"validated"<<endl<<endl;

				while(1){
					cout<<"Choose the correct choice :\n";
					cout<<"1. Display your Marks\n";
					cout<<"2. Display your Group Details\n";
					cout<<"3. Exit this block\n\n";
					cout<<"Enter your choice : "<<endl<<endl;
					int op2 ;
					cin>>op2;

					if(op2 == 1){
						cout<<"You choose 1 \n\n";
						Display_Marks(password);
					}
					else if(op2 == 2){
						cout<<"You choose 2 \n\n";
						Display_grp_details(password);
					}
					else if(op2 == 3){
						cout<<"Exiting this block\n\n";
						break;
					}
					else {
						cout<<"Invalid Choice\n";
					}
				}
			}
        }

        else if(op == 2){
        	cout<<"You choose 2 \n\n";
			cout<<"------------------Teachers Portal-------------------\n";
			cin >> name2;
			cin >> password1;

			if(name2 == "Jaswanth" && password1 == "jashu"){
				cout<<"Validated"<<endl<<endl;

				while(1){
					cout<<"Choose the correct choice :\n";
					cout<<"1. Insert Student Record\n";
					cout<<"2. Insert Assignment\n";
					cout<<"3. Change Status\n";
					cout<<"4. Print List of Assignments declared but not Evaluated\n";
					cout<<"5. Print the list student groups who have not submitted the assignments even if the due-date is over. \n";
					cout<<"6. Print the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n";
					cout<<"7. Print the details of student-groups, in the decreasing order of marks for a particular assignment\n";
					cout<<"8. Print student groups receiving top marks in each of the assignment given.\n";
					cout<<"9. Range Search between 2 assignments\n";
					cout<<"10. Exit this Block\n\n";
					cout<<"Enter your choice : ";

					int op2;
					cin >> op2;

					int c,d,h,o;
                    string e, f, g, i, j;
                    float k,l,m,n;

                    

                    int s1,s2,assig_id;
                    string stat;
                    float m1,m2,m3,m4;

					if(op2 == 10){
						cout<<"Exiting this block\n\n";
						break;
					}
					else if(op2 == 1){
						cout<<"Inserting student record-------->\n";
						cout<<"Enter the both student ids and names : ";
						cin >> c >> d >> e >> f;
						cout<<"\nEnter group id : ";
						cin >> o;
						cout<<"\nEnter asg name and id";
						cin >> g >> h;
						cout<<"\nEnter deadline and status : ";
						cin >> i >> j;
						cout<<"\nEnter offline and viva marks of both students : ";
						cin >> k >> l >> m >> n;
						
						student = insert_student(student,c,d,e,f,o,g,i,j,k,l,m,n,h);
						inOrder_1(student);
					}

					else if(op2 == 2){
						int num, p, asg_id;
	                    string deadline;
	                    string topic_name;
	               
	                    char name_pointers[100];
	                    char status_pointers[100];

	                    cout<<"Inserting Assignment record---------->\n";
						cout<<"Enter Assignment id , Topic name and deadline respectively : ";
						cin >> asg_id >> topic_name >> deadline;
						
						cout<<endl<<"Enter number of students : ";
						cin >> num;

						vector<int> stud_id(num,0);
						vector<int> grp_id(num,0);
						vector<string> names(num, "");
						vector<string> status(num, "");
						vector<float> off_marks(num, 0);
						vector<float> viva_marks(num, 0);

						for(p=0;p<num;p++)
						{
							cout<< "Enter student id , Name , Group Id , Status , Offline and viva marks respectively : " << endl;
							cin >> stud_id[p] >> names[p] >> grp_id[p] >> status[p] >> off_marks[p] >> viva_marks[p];
                            // name_pointers[p] =names[p];
                            // status_pointers[p]=status[p];
						}

						assignment = insert_assignment(student ,assignment ,topic_name, asg_id,stud_id,names,
                                                                grp_id,deadline,status,off_marks,viva_marks,num);
						cout<<"-----\n";
						inOrder_1(student);
						cout<<"-----\n";
						inOrder_2(assignment);
					}
					else if(op2 == 3){
						int s1,s2,assig_id;
						string stat;
						float m1,m2,m3,m4;
						cout<<"Changing status of a group ----------->\n";
						cout<<"Enter the group id , Assignment id and status : ";
						cin >> s1 >> s2 >> assig_id >> stat;

						if(stat != "Evaluated")
						{
							change_status(student,assignment,s1,s2,stat,0,0,0,0,assig_id);
						}

						else if(stat == "Evaluated"){
							cout<<"Enter offline and viva marks of both students respectively : ";
							cin >> m1 >> m2 >> m3 >> m4;
									
							change_status(student,assignment,s1,s2,stat,m1,m2,m3,m4,assig_id);
						}

						cout<<"-----\n";
						inOrder_1(student);
						cout<<"-----\n";
						inOrder_2(assignment);
					}
					else if(op2 == 4){
						cout<<"Printing List of Assignments declared but not evaluated--------->\n";
						print_declared_not_eval(assignment);
					}
					else if(op2 == 5){
						cout<<"Printing the list student groups who have not submitted the assignments even if the due-date is over.\n";
						print_stud_not_submitted(assignment , student);
					}
					else if(op2 == 6){
						cout<<" Printing the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n";
						print_stud_notEval_sub(student);
					}
					else if(op2 == 7){
						cout<<"Printing the details of student-groups, in the Increasing order of marks for a particular assignment\n";
						cout<<"Enter Assignment id : ";
						int assignment_id;
						cin >> assignment_id;
						print_dec_order(assignment , assignment_id);
					}
					else if(op2 == 8){
						cout<<"Printing student groups receiving top marks in each of the assignment given.\n";
						print_top_stud(assignment);
					}
					else if(op2 == 9){
						cout<<"Range Search\n";
						int a1,a2;
						cin >> a1 >> a2;
						range_search(assignment,a1,a2);
					}
					else{
						cout<<"Enter valid Number \n";
					}
				}
			}
        }
        else if(op == 3) break;
        else{
        	cout<<"Enter Valid Number\n\n";
        }
	}


	return 0;
}

