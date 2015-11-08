#include "eventqueue.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
	EventQueue& queue1 = EventQueue::get_instance();
	EventQueue& queue2 = EventQueue::get_instance();
	EventQueue& queue3 = EventQueue::get_instance();
	
	cout<<queue1.test_count()<<endl;
	cout<<queue2.test_count()<<endl;
	cout<<queue3.test_count()<<endl;
	
}