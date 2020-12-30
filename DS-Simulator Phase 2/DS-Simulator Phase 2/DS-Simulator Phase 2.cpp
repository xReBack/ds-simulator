// ConsoleApplication18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include <list> 
#include <iterator> 
#include <string>
using namespace std;

//*********************************************************************************
//********************************** FCFS *****************************************
//*********************************************************************************
void FCFS(int requests[], int head_position, int req_count, int distance, int seek_count)
{
	cout << "FCFS: " << endl;
	distance = abs(head_position - requests[0]);
	for (int i = 0; i < req_count - 1; i++) {
		distance += abs(requests[i] - requests[i + 1]);
	}
	cout << "Order: " << head_position << " -> ";
	for (int i = 0; i < req_count; i++) {
		string _ = " -> ";
		if (i == req_count - 1) {
			_ = "";
		}
		cout << requests[i] << _;
	}
	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}


//*********************************************************************************
//********************************** SCAN *****************************************
//*********************************************************************************
void SCAN(int requests[], int head_position, int distance, int req_count, int seek_count, int disk_size, bool direction_right) {
	cout << "Scan: " << endl;
	sort(requests, requests + req_count);
	//Get closest request
	int closest_diiference = requests[0];
	int closest_index = 0;
	for (int i = 1; i < req_count; i++) {
		if (direction_right) {
			if (abs(head_position - requests[i]) < abs(head_position - closest_diiference) && requests[i] > head_position) {
				closest_diiference = requests[i];
				closest_index = i;
			}
		}
		else {
			if (abs(head_position - requests[i]) < abs(head_position - closest_diiference) && requests[i] < head_position) {
				closest_diiference = requests[i];
				closest_index = i;
			}
		}
	}
	//Get boundaries
	int boundaries = (req_count - 1) * (direction_right);
	int rqst_cntx = req_count;
	//Push
	list<int> SCAN_rqst;
	SCAN_rqst.push_front(head_position);
	for (int i = 0; i < rqst_cntx; i++) {
		int index = closest_index - i * (!direction_right) + i * (direction_right);
		SCAN_rqst.push_back(requests[index]);
		if (index == boundaries) {
			SCAN_rqst.push_back((disk_size - 1) * direction_right);
			i = 0;
			direction_right = !direction_right;
			rqst_cntx = req_count - closest_index;
		}
	}


	cout << "Order: ";
	for (list<int> ::iterator i = SCAN_rqst.begin(); i != prev(SCAN_rqst.end()); i++) {
		cout << *i << " -> ";
		distance += abs(*i - *next(i));

	}
	cout << *prev(SCAN_rqst.end());
	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}

void CLOOK(int requests[], int head_position, int req_count, int distance, int seek_count)
{
	cout << "CLOOK: " << endl;

	int old_head = head_position;
	for (int i = 0; i < req_count; i++)
	{
		if (head_position < requests[i])
		{
			distance += abs(head_position - requests[i]);
			head_position = requests[i];
		}

	}
	distance += abs(head_position - requests[0]);
	for (int i = 0; i < req_count; i++)
	{
		if (requests[i] < old_head && requests[i + 1] < old_head)

			distance += abs(requests[i] - requests[i + 1]);
	}
	cout << "Order: " << old_head << " -> ";
	for (int i = 0; i < req_count; i++) {
		string _ = " -> ";
		if (i == req_count - 1) {
			_ = "";
		}
		cout << requests[i] << _;
	}
	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}


void CSCAN(int requests[], int head_position, int req_count, int distance, int seek_count)
{
	cout << "CSCAN: " << endl;

	for (int i = 0; i < req_count; i++)
	{
		if (head_position < requests[i])
		{
			distance += abs(head_position - requests[i]);
			head_position = requests[i];
		}

	}

	for (int i = 0; i < req_count; i++)
	{
		if (requests[i] < head_position && requests[i + 1] < head_position)

			distance += abs(requests[i] - requests[i + 1]);
	}
	cout << "Order: " << head_position << " -> ";
	for (int i = 0; i < req_count; i++) {
		string _ = " -> ";
		if (i == req_count - 1) {
			_ = "";
		}
		cout << requests[i] << _;
	}
	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}

void SSTF(int requests[], int head_position, int req_count, int distance, int seek_count, int disk_size)
{


	cout << "SSTF: " << endl;
	int closest_index = disk_size - head_position;
	int closest_i = disk_size - head_position;
	//cout << "closest index = " << closest_index << endl;
	for (int i = 0; i < req_count - 1; i++)
	{

		//cout << "distance = " << head_position << " - " << requests[i] << " = ";
		distance = (head_position - requests[i]);
		//cout << distance << endl;

		if (closest_i > abs(distance)) {
			closest_i = abs(distance);

			closest_index = distance;

		}
		//cout <<"closest index = " << closest_index << endl;
		//cout << "closest i = " << closest_i << endl;

	}
	cout << "Order: " << head_position << " -> ";
	string _ = " -> ";
	int requests_x[8];

	if (closest_index > 0) //Move left first
	{
		sort(requests, requests + req_count, greater<int>());
		for (int i = 0; i < req_count; i++) {

			if (requests[i] < head_position)
			{

				requests_x[i] = requests[i];
				cout << requests_x[i] << _;
				distance += abs(requests[i] - requests[i + 1]);

			}

		}


		for (int i = 0; i < req_count; i++)
		{
			sort(requests, requests + req_count);

			if (requests[i] > head_position)
			{
				requests_x[i] = requests[i];
				if (i == req_count - 1)
				{
					_ = "";
				}
				cout << requests_x[i] << _;
				distance += abs(requests[i] - requests[i + 1]);


			}
		}
	}

	else if (closest_index < 0) //Move left first
	{

		for (int i = 0; i < req_count; i++) {
			sort(requests, requests + req_count, greater<int>());

			if (requests[i] < head_position)
			{

				requests_x[i] = requests[i];
				cout << requests_x[i] << _;
				distance += abs(requests[i] - requests[i + 1]);

			}
		}

		sort(requests, requests + req_count);

		for (int i = 0; i < req_count; i++) {
			if (requests[i] > head_position)
			{
				requests_x[i] = requests[i];
				if (i == req_count - 1) {
					_ = "";
				}
				cout << requests_x[i] << _;
				distance += abs(requests[i] - requests[i + 1]);


			}
		}
	}


	distance = abs(head_position - requests[0]);
	for (int i = 0; i < req_count - 1; i++) {
		distance += abs(requests[i] - requests[i + 1]);
	}


	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}


//*********************************************************************************
//********************************* Driver Code ***********************************
//*********************************************************************************
int main()
{
	//INPUTS
	int head_position = 50;
	int disk_size = 200;
	/*int* requests = NULL;
	int n;
	cout << "How many requests? : ";
	cin >> n;
	cout << "Enter the list of requests"<<endl;
	requests = new int[8];
	for (int i = 0; i < 8; i++) {
		cout << i+1 << " - ";
		cin >> requests[i];
	}*/
	int seek_count = 6;
	int requests[8] = { 176, 79, 34, 60, 92, 11, 41, 114 };
	int req_count = sizeof(requests) / sizeof(requests[0]);
	bool direction_right = false;
	cout << "req count = " << req_count << endl;
	int distance = 0;

	FCFS(requests, head_position, req_count, distance, seek_count);
	SSTF(requests, head_position, req_count, distance, seek_count, disk_size);

	SCAN(requests, head_position, distance, req_count, seek_count, disk_size, direction_right);
	CLOOK(requests, head_position, req_count, distance, seek_count);
	CSCAN(requests, head_position, req_count, distance, seek_count);


}



