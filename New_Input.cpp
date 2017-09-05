#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;
int comm_sz=0;
int my_rank=0;
int arra[]={1,2,3,4,5},arrb[]={10,9,8,7,6},arrc[]={0,0,0,0,0};

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

//获取输入，0进程从键盘读取，非0进程从0进程获取
bool get_input(double &a,double &b,int n)
{
	MPI_Datatype input_mpi_t;
	Build_mpi_type(&a,&b,&n,&input_mpi_t);
	
    if(my_rank==0){	//用户输入
		cout<<" enter a,b,n"<<endl;
		cin>>a>>b>>n;
    }
	MPI_Bcast(&a,1,input_mpi_t,0,MPI_COMM_WORLD);
	
	MPI_Type_free(&input_mpi_t);
    return true;
}

//加和数组a和数组b的对应项
int count_sum(int beg,int en)
{
	int sum=0;
	for(int i=beg;i<en;i++){
		sum += arra[i]+arrb[i];
	}
	return sum;
}

int main(void)
{
    int local_sum=0,total_sum=0;	//local_sum为本进程使用，total_sum为计算风格进程的合使用

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	
	int a = 0, b = 0, c = 0;
	
    get_input(&a, &b, &n);
    cout<<"a "<<a<<" b "<<b<<" c "<<c<<endl;
	
    MPI_Finalize();
    return 0;
}