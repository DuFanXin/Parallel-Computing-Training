#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;

const int maxn=10;

bool Parallel_vector_sum(double local_x[],double local_y[],double local_z[],int local_n)
{
  for(int local_i=0;local_i<local_n;local_i++){
  	local_z[local_i] = local_x[local_i]+local_y[local_i];
  }
  return true;
}

bool Read_vector(double local_a[],int local_n,int n,string vec_name,int my_rank,MPI_Comm comm)
{
  double* a = NULL;

  if(my_rank==0){
    a = new double[n];
    cout<<"Enter the vector "<<vec_name<<endl;
    for(int i=0;i<n;i++){
      cin>>a[i];
    }
    MPI_Scatter(a,local_n,MPI_DOUBLE,local_a,local_n,MPI_DOUBLE,0,comm);
    delete [] a;
  } 
  else{
    MPI_Scatter(a,local_n,MPI_DOUBLE,local_a,local_n,MPI_DOUBLE,0,comm);
  }
  return true;
}

bool Print_vector(double local_b[],int local_n,int n,string title,int my_rank,MPI_Comm comm)
{
  double* b=NULL;
  
  if(my_rank==0){
    b = new double[n]; 
    MPI_Gather(local_b,local_n,MPI_DOUBLE,b,local_n,MPI_DOUBLE,0,comm);
    cout<<title<<endl;
    for(int i=0;i<n;i++){
      cout<<b[i]<<" ";
    }
    cout<<endl;
    delete [] b;
  }
  else{
    MPI_Gather(local_b,local_n,MPI_DOUBLE,b,local_n,MPI_DOUBLE,0,comm);
  }
  return true;
}

int main()
{
  int my_rank=0;
  int comm_sz=0;

  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

  streambuf * inbuf = cin.rdbuf((new ifstream("input"))->rdbuf());//重定向，OJ时将它注释掉

  int local_n=maxn/comm_sz;
  double local_a[maxn],local_b[maxn],local_c[maxn];
  
  Read_vector(local_a,local_n,maxn,"arryA",my_rank,MPI_COMM_WORLD);
  Read_vector(local_b,local_n,maxn,"arryB",my_rank,MPI_COMM_WORLD);
  Parallel_vector_sum(local_a,local_b,local_c,local_n);
  Print_vector(local_c,local_n,maxn,"arry",my_rank,MPI_COMM_WORLD);


  MPI_Finalize();
  return 0;
}