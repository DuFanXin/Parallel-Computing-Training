#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;

int main()
{
	int my_rank=0, comm_sz=0;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	int a = 10, b = 0;
	
	MPI_Allreduce(&a, &b, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	
	cout<<"process "<<my_rank<<" "<< b <<endl;
	
	MPI_Finalize();
}