#include <iostream>
#include "mpi.h"
#include "omp.h"

//Round
int main(int argc, char* argv[]){
	int arrSize = 10;

	for (int i = 0; i < argc; i++){
		if (strncmp(argv[i], "--size-array", 12) == 0){
			arrSize = atoi(argv[i + 1]);
			break;
		}
	}
	
	MPI_Init(NULL, NULL);
	int rank, total;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &total);
	MPI_Status Stat[2];

	int* arrSend = new int[arrSize];
	int* arrRecv = new int[arrSize];
	for (int i = 0; i < arrSize; i++) 
		arrSend[i] =i;

	//int MPI_Send(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
	MPI_Send(arrSend, arrSize, MPI_INT, (rank + 1) % total, 1, MPI_COMM_WORLD);


	//int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,
	//				MPI_Comm comm, MPI_Status* status)
	MPI_Recv(arrRecv, arrSize, MPI_INT, (total + rank - 1) % total, 1, MPI_COMM_WORLD, &Stat[0]);

	std::cout << "Rank: " << rank <<" received:"<< std::endl;
	for (int i = 0; i < arrSize; i++) 
		std::cout << arrRecv[i] << " ";

	std::cout << std::endl;
	MPI_Finalize();
}