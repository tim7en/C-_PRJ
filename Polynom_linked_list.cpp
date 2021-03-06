// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//HW1  Polynomial Operations using linked lists

//Due 11:59 pm, February 2 (Friday)
//
//A polynomial is implemented using a linked list.  Only non-zero coefficients are included in linked list.
//Implment member functions operator+ , operator* , and add term
//
//You have to use the main function and print_linked_list provided to you.


//Polynomial addition and multiplication using Linked List.
//Project realized under course C++ Obj Oriented Programming, created by Roger Chen, moderated by Timur Sabitov with support of teaching assistant 1 st yar PHD, Eyoel Getahun Armede. 2018
//All right reserved

#include <iostream>

using namespace std;

class term {
public:
	int power;
	int coef;
	term * next;
	term() { next = nullptr; }
	term(int c, int p) { power = p; coef = c; next = nullptr; }
};

class polynomial {
public:
	int num_terms;
	term * head;
	polynomial() { num_terms = 0; head = nullptr; }

	void add_term(int c, int p);

	polynomial operator+(polynomial P);
	polynomial operator*(polynomial P);
	void print_polynomial();
};


void polynomial::print_polynomial() {
	cout << endl;
	term * p = head;
	while (p != nullptr) {
		cout << p->coef << " " << p->power << "   ";
		p = p->next;
	}
}


void polynomial::add_term(int c, int p) {

	if (head == nullptr) 
	{
		term*cur = new term(c, p);
		head = cur;
		num_terms++;
		return;
	}

	term*cur = head;
	term*tail = cur->next;

	if (head->power < p) {
		term*temp_new = new term(c, p); //create a new node; (b)
		temp_new->next= head;			//head will be after a new value if a < b then b and a
		head = temp_new;				//head will be pointing to the same thing as a new value
		num_terms++;
		return;
	}

	if (head->power == p) {

		if (head->coef+c == 0) {

			term*temp_new = head;
			head = head->next;
			delete temp_new;			//to avoid memory leak
			num_terms--;
			return;
		}
		else 
		{
			head->coef = head->coef + c;
			return;
		}
	}

	while (cur!= nullptr)
	{
		term*temp_new = new term(c, p);

		if (tail!=nullptr && tail->power < p) //cur->next
		{
			term*temp_new = new term(c, p);			//create temporay c, and the order should now be a, b
			temp_new->next = tail;						//b->next=a; b->next will be pointing to the a
			cur->next = temp_new;							//a will be pointing to the same thing as a b
			num_terms++;
			return;
		}
		else if (tail!=nullptr && tail->power == p) {

			if (tail->coef + c == 0) {
				cur->next = tail->next;
				delete tail;
				num_terms--;
				return;
			}
			else { 
				tail->coef = tail->coef + c; return; 
			}
		}

		if (tail == nullptr) {
			cur->next = temp_new;
			return;
		}

		cur = cur->next;
		tail = cur->next;
	}
}


//problem of the third pointer


polynomial polynomial::operator+(polynomial P) {
	polynomial add;
	term*t1 = head;
	term*t2 = P.head;

	while (t1 != nullptr && t2 != nullptr) {

		if (t1->power == t2->power) {
			if (t1->coef + t2->coef == 0) {
				t1 = t1->next;
				t2 = t2->next;
			}
			else{
			add.add_term(t1->coef + t2->coef, t1->power);
			t1 = t1->next;
			t2 = t2->next;
			}
			//return add;
		}
		else if (t1->power > t2->power) {
			add.add_term(t1->coef, t1->power);
			t1 = t1->next;
			//return add;
		}
		else if (t1->power < t2->power){
			add.add_term(t2->coef, t2->power);  
			t2 = t2->next;
			//return add;
		}
		while (t1 == nullptr || t2 == nullptr) {
			if (t1 != nullptr) {
				add.add_term(t1->coef, t1->power);
				t1 = t1->next;
			}
			else if (t2 != nullptr) {
				add.add_term(t2->coef, t2->power);
				t2 = t2->next;
			}
			else if (t1 == nullptr && t2 == nullptr) {
				return add;
			}
		}
	}
	return add;
}


polynomial polynomial::operator*(polynomial P) {
	polynomial add;
	term*t1 = head;
	term*t2 = P.head;

	while (t1 != nullptr && t2 != nullptr) {
		if (t1->power == t2->power) {
			if (t1->coef + t2->coef == 0) {
				t1 = t1->next;
				t2 = t2->next;
			}
			else {
				add.add_term(t1->coef * t2->coef, t1->power);
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		else if (t1->power > t2->power) {
			add.add_term(t1->coef, t1->power);
			t1 = t1->next;
			//return add;
		}
		else if (t1->power < t2->power) {
			add.add_term(t2->coef, t2->power);
			t2 = t2->next;
			//return add;
		}
		while (t1 == nullptr || t2 == nullptr) {
			if (t1 != nullptr) {
				add.add_term(t1->coef, t1->power);
				t1 = t1->next;
			}
			else if (t2 != nullptr) {
				add.add_term(t2->coef, t2->power);
				t2 = t2->next;
			}
			else if (t1 == nullptr && t2 == nullptr) {
				return add;
			}
		}
	}
	return add;
}



int main() {
	polynomial p1, p2, p3, p4, p5, p6;
	int num_t;
	cout << "Enter numer of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { //You don't need to check for input error
		int c, p;
		cin >> c >> p;
		p1.add_term(c, p);
	}
	p1.print_polynomial();
	cout << endl;
	cout << "Enter numer of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { //You don't need to check for input error
		int c, p;
		cin >> c >> p;
		p2.add_term(c, p);
	}
	p2.print_polynomial();
	p3 = p1 + p2;
	p3.print_polynomial();
	p4 = p1 * p2;
	p4.print_polynomial();
	getchar();
	getchar();
	return 0;
}
