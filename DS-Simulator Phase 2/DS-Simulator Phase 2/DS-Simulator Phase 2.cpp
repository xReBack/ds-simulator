#include <cmath>
#include <iostream>
#include <algorithm>
#include <list> 
#include <iterator> 
#include <string>
using namespace std;

//********************************** FCFS *****************************************
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

//********************************** SCAN *****************************************
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

//********************************** CLOOK ****************************************
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

//********************************** CSCAN ****************************************
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

//********************************** LOOK ****************************************
void LOOK(int requests[], int head_position, int req_count, int seek_count, int disk_size, bool direction_right) {
	int* requests_x = new int[req_count];
	for (int i = 0; i < req_count; i++) {
		requests_x[i] = requests[i];
	}
	cout << "LOOK: " << endl;
	sort(requests_x, requests_x + req_count);

	list<int>left;
	list<int>right;
	for (int i = 0; i < req_count; i++)
	{
		if (requests_x[i] > head_position)
			right.push_back(requests_x[i]);
		else
			left.push_back(requests_x[i]);
	}
	list<int> LOOK_requests;
	LOOK_requests.push_back(head_position);
	for (int i = 0; i < 2; i++)
	{
		if (direction_right)
		{
			for (list <int> ::iterator i = right.begin(); i != (right.end()); i++)
			{
				LOOK_requests.push_back(*i);
			}

		}
		else
		{
			for (auto i = left.rbegin(); i != (left.rend()); i++)
			{
				LOOK_requests.push_back(*i);
			}
		}
		if (i == 0)
			direction_right = !direction_right;
	}


	int total_distance = 0;
	cout << "Order: ";

	for (list <int> ::iterator i = LOOK_requests.begin(); i != prev(LOOK_requests.end()); i++) {
		cout << *i << " -> ";
		total_distance += abs(*i - *next(i));

	}
	cout << *prev(LOOK_requests.end());
	cout << "\n" << "Seek: " << total_distance << " cylinders, " << total_distance * seek_count << "ms";
	cout << endl << endl;
}

//********************************** SSTF ****************************************
void SSTF(int requests[], int head_position, int req_count, int seek_count, int disk_size) {
	cout << "SSTF: " << endl;

	int* requests_x = new int[req_count];
	for (int i = 0; i < req_count; i++) {
		requests_x[i] = requests[i];
	}

	int* sstf_requests = new int[req_count];
	for (int i = 0; i < req_count; i++) {
		sstf_requests[i] = requests_x[i];
	}
	int current_request = head_position;
	int current_request_index = -1;
	int least_distance = 99999;
	int least_distance_index = 0;
	for (int i = 0; i < req_count; i++) {
		for (int j = 0; j < req_count; j++) {
			if (j == current_request_index) {
				continue;
			}
			if (least_distance > abs(current_request - requests_x[j])) {
				least_distance = abs(current_request - requests_x[j]);
				least_distance_index = j;
			}
		}
		least_distance = 99999;
		sstf_requests[i] = requests_x[least_distance_index];
		current_request = requests_x[least_distance_index];
		requests_x[least_distance_index] = 99999;
	}

	cout << "Order: " << head_position << " -> ";
	string _ = " -> ";

	for (int i = 0; i < req_count; i++) {
		string arrow = " -> ";
		if (i == req_count - 1) {
			arrow = "";
		}
		cout << sstf_requests[i] << arrow;
	}

	int total_distance = abs(head_position - sstf_requests[0]);
	for (int i = 0; i < req_count - 1; i++) {
		total_distance += abs(sstf_requests[i] - sstf_requests[i + 1]);
	}
	cout << "\n" << "Seek: " << total_distance << " cylinders, " << total_distance * seek_count << "ms";
	cout << endl << endl;
}

//********************************** Driver Code **********************************
int main()
{
	//INPUTS
	int n;
	/*cout << "How many requests? : ";
	cin >> n;
	cout << "enter the list of requests"<<endl;
	int*requests = new int[n];
	for (int i = 0; i < n; i++) {
		cout << i+1 << " - ";
		cin >> requests[i];
	}
	int req_count = n;*/
	/**/ int requests[8] = { 98, 183, 40, 122, 10, 124, 65, 175 };
	int req_count = sizeof(requests) / sizeof(requests[0]); /**/
	int head_position = 50;
	int disk_size = 200;
	int seek_count = 6;
	bool direction_right = false;
	int distance = 0;

	LOOK(requests, head_position, req_count, seek_count, disk_size, direction_right);
	SSTF(requests, head_position, req_count, seek_count, disk_size);
	CSCAN(requests, head_position, req_count, distance, seek_count);
	CLOOK(requests, head_position, req_count, seek_count, disk_size);
	FCFS(requests, head_position, req_count, distance, seek_count);
	SCAN(requests, head_position, distance, req_count, seek_count, disk_size, direction_right);
}