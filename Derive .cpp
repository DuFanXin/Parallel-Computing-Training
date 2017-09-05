#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;

const int maxn = 10;
const int maxm = 5;

bool Build_mpi_type(
				double*			a_p,			/* IN */
				double*			b_p,			/* IN */
				int*			n_p,			/* IN */
				MPI_Datatype*	input_mpi_t_p	/* OUT */
				)
{
	int array_of_blocklength[3] = {1, 1, 1};
	MPI_Datatype array_of_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_IN};
	MPI_Aint a_addr, b_addr, n_addr;
	MPI_Aint array_of_displacement[3] = {0};
	
	MPI_Get_address(a_p,&a_addr);
	MPI_Get_address(b_p,&b_addr);
	MPI_Get_address(n_p,&n_addr);
	
	array_of_displacement[0] = 0;
	array_of_displacement[1] = b_addr-a_addr;
	array_of_displacement[2] = n_addr-b_addr;
	
	MPI_Type_create_struct(3,array_of_blocklength,array_of_displacement,array_of_types,input_mpi_t_p);
	MPI_Type_commit(input_mpi_t_p);
}

int main(void)
{
	int my_rank=0;
	int comm_sz=0;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	//streambuf * inbuf = cin.rdbuf((new ifstream("input"))->rdbuf());//重定向，OJ时将它注释掉
	double a=0, b=0, n=0;
	MPI_Datatype input_mpi_t_p;
	
	cin>>a>>b>>n;
	
	Build_mpi_type(&a, &b, &n, &input_mpi_t_p);
	
	MPI_Bcast(&a,1,input_mpi_t_p,0,MPI_COMM_WORLD);
	
	MPI_Type_free(&input_mpi_t_p);

	MPI_Finalize();
	return 0;
}