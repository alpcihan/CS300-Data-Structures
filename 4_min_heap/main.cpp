// CS300 HW4 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MinHeap.h"
using namespace std;

void fillTheHeaps(fstream & inputFile, MinHeap<Worker> & workerHeap, MinHeap<Job> & jobHeap, const int & workerCount, const int & jobCount)
{
	/* Fill the worker heap */
	for(int i = 1; i <= workerCount; i++)
	{
		Worker temp(i,0);
		workerHeap.insert(temp);
	}

	/* Fill the job heap */
	string line;
	for(int i = 0; i < jobCount; i++) // for each line
	{
		getline(inputFile, line);
		int id, deadline;
		istringstream iss(line);
		iss >> id >> deadline; // get id and deadline from the line

		cout << id << " " << deadline << endl; // print the inputs

		Job temp(id, deadline); // temp job with id and deadline
		jobHeap.insert(temp); // insert temp job to the job heap
	}
}
void getInput(fstream & inputFile, int & workerCount, int & jobCount, string & fileName)
{
	/* Open the input file */
	string emptyString;
	do{
		cout << "Please enter file name: ";
		cin >> fileName;
		inputFile.open(fileName.c_str());
	}while(inputFile.fail());

	/* Get job and worker amounts */
	inputFile >> workerCount;
	inputFile >> jobCount;

	getline(inputFile, emptyString); // in order to skip the empty string

	/* Input file output */
	cout << endl << "Input file:" << endl << workerCount << endl << jobCount << endl;
}

void callWorkersBack(MinHeap<Worker> & workerHeap, MinHeap<Worker> & matchHeap)
{
	bool isEveryBodyCalled = false;
	Worker tempWorker;
	while(matchHeap.getHeapSize() > 0 && isEveryBodyCalled == false)
	{
		matchHeap.deleteMin(tempWorker);
		if(tempWorker.days == 0)
			workerHeap.insert(tempWorker);
		else
		{
			matchHeap.insert(tempWorker);
			isEveryBodyCalled = true;
		}		
	}
}
void finishJob(MinHeap<Worker> & workerHeap, MinHeap<Job> & jobHeap, MinHeap<Worker> & matchHeap, int & countDays)
{
	Worker tempWorker;
	if(matchHeap.getHeapSize() > 0)
	{	
		matchHeap.deleteMin(tempWorker);

		matchHeap.decreaseElements(tempWorker.days);

		countDays += tempWorker.days;
		tempWorker.days = 0;


		workerHeap.insert(tempWorker);
	}
}
void assignWorkers(MinHeap<Worker> & workerHeap, MinHeap<Job> & jobHeap, MinHeap<Worker> & matchHeap, const int & workerCount, const int & countDays, ofstream & outputFile)
{
	Worker tempWorker;
	Job tempJob;
	/* Assign each worker to new job respect to id numbers */
	while(workerHeap.getHeapSize() > 0 && jobHeap.getHeapSize() > 0)
	{
		/* Get job and worker */
		workerHeap.deleteMin(tempWorker);
		jobHeap.deleteMin(tempJob);

		/* Give output */
		outputFile << "Job-" << tempJob.id << "->Worker-" << tempWorker.id << " (Day: " << countDays << ")" << endl;
		cout << "Job-" << tempJob.id << "->Worker-" << tempWorker.id << " (Day: " << countDays << ")" << endl; 

		/* Assign days to worker */
		tempWorker.days = tempJob.deadline;
		matchHeap.insert(tempWorker);
	}
}
void openOutputFile(ofstream & outputFile, const string & fileName)
{
	string outputFileName = fileName + ".out";
	outputFile.open(outputFileName.c_str());
}
void jobFlow(MinHeap<Worker> & workerHeap, MinHeap<Job> & jobHeap, const string & fileName, const int & workerCount, const int & jobCount)
{
	/* Open output file */
	ofstream outputFile;
	openOutputFile(outputFile, fileName);
	cout << "Output File:" << endl;	

	/* Work flow */
	int countDays = 0;
	MinHeap<Worker> matchHeap(workerCount);
	do
	{
		assignWorkers(workerHeap, jobHeap, matchHeap, workerCount, countDays, outputFile); // assign each worker to a job if they are not assigned already
		finishJob(workerHeap, jobHeap, matchHeap, countDays); // worker with less working days finish it's job
		callWorkersBack(workerHeap, matchHeap); // if worker finished the job 
	}while(jobHeap.getHeapSize() > 0 || matchHeap.getHeapSize() > 0);

	outputFile << "All jobs are completed in " << countDays << " days." << endl;
	cout << "All jobs are completed in " << countDays << " days." << endl;
}

int main()
{
	fstream inputFile; // input file
	string fileName;
	int workerCount, jobCount; // amount of workers and job

	getInput(inputFile, workerCount, jobCount, fileName); // open the file and get worker and job count

	MinHeap<Worker> workerHeap(workerCount); // heap to keep workers
	MinHeap<Job> jobHeap(jobCount); // heap to keep jobs

	fillTheHeaps(inputFile, workerHeap, jobHeap, workerCount, jobCount); // fill the job and worker heaps

	jobFlow(workerHeap, jobHeap, fileName, workerCount, jobCount); // start the work flow

	inputFile.close();	

	return 0;

}
