#include <mpi.h>

constexpr int steps = 100000000;

int main(int argc, char *argv[])
{

	MPI_Init(&argc,&argv);
	int rank;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int width = steps / size;
	int start = rank * width;
	int stop  = start + width;
	double step = 1.0/steps;

	double local_sum=0.0;
	for (int i = start; i < stop; ++i) {
		double x = (i - 0.5) * step;
		local_sum += (4.0/(1.0 + x * x));
	}


	double global_sum=0.0;
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank == 0)
	{
		global_sum *= step;
		std::cout << global_sum << std::endl;
	}

	MPI_Finalize();
	return 0;
}
