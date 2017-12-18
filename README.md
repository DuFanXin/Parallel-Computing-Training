# Parallel-Computing-Training
这是我学习并行计算的代码文件夹
1.AllReduce.cpp 计算各个节点的值（MPI集合通信）
2.Derive .cpp 新建一个数据类型（MPI）
3.New_Input.cpp 接收数据，然后用新建的数据类型来广播（MPI）
4.Reduce.cpp 加和各个进程的值，然后由0号进程输出（MPI集合通信）
5.sum.cpp 加和各个进程的值，然后由0号进程输出（MPI点对点通信）
6.vector_sum.cpp 将两个数组分段给各个进程加和，将结果存入第三个数组，然后0进程打印数组（MPI集合通信）
