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
	
	MPI_Reduce(&a, &b, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(my_rank == 0){
		cout<< b <<endl;
	}
	
	MPI_Finalize();
}