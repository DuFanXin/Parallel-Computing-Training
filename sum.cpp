#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;
int comm_sz=0;
int my_rank=0;
int arra[]={1,2,3,4,5},arrb[]={10,9,8,7,6},arrc[]={0,0,0,0,0};

bool get_input(double &a,double &b,int n)
{
    if(my_rank==0){
		cout<<" enter a,b,n"<<endl;
		cin>>a>>b>>n;
    }
	else{
		MPI_Recv(&a,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&b,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
    return true;
}

int count_sum(int beg,int en)
{
	int sum=0;
	for(int i=beg;i<en;i++){
		sum += arra[i]+arrb[i];
	}
	return sum;
}

int main()
{
    int local_sum=0,total_sum=0;	

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	
    //get_input(a,b,n);
    int n = sizeof(arra);
    int jiange=n/(comm_sz-1);
    if(my_rank==0){
		cout<<"n: "<<n<<endl;
		for(int source=1;source<comm_sz;source++){
			MPI_Recv(&local_sum,1,MPI_INT,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			total_sum += local_sum;
		}
		cout<<"total_sum: "<<total_sum<<endl;
	}
	else if(my_rank==(comm_sz-1)){
		int rest=n-jiange*(comm_sz-2);
                //int rest=n%(comm_sz-1);
		//rest += jiange;
                //cout<<"rest: "<<rest<<endl;
		int sum=count_sum(n-rest,n);
		MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	else{
		
		int sum=count_sum(jiange*(my_rank-1),jiange*my_rank);
		MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
		//cout<<"process "<<my_rank<<" a "<<a<<" b "<<b<<" n "<<n<<endl;
	
    MPI_Finalize();
    return 0;
}