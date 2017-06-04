// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include <cstdio>
#include <cstdlib>
#include "libs/handle.h"

#define DEFAULT_STEPS 100
#define DEFAULT_LATTICE_SIZE 1000
#define DEFAULT_OUTFILE (char*)"out.txt"

int main(int argc, char** argv)
{

	// char* filename           = setDefaultArgument((char*)"Output filename");
	char* outputFilename     = addArgument((char*)"Output filename", TAKES_ONE_ARGUMENT, (char*)"-o", (char*)"--out");
	char* historySizeOption  = addArgument((char*)"Number of steps", TAKES_ONE_ARGUMENT, (char*)"-n", (char*)"--steps");
	char* latticeSizeOption  = addArgument((char*)"Size of lattice", TAKES_ONE_ARGUMENT, (char*)"-s", (char*)"--size");
	char* helpOption         = addArgument((char*)"Print usage", TAKES_NO_ARGUMENTS, (char*)"-h", (char*)"--help");

	int argError;
	argError = handle(argc, argv);
	if(argError) {
		fprintf(stderr, "Run `evolve --help` for more information\n");
		return argError;
	}

	if(argSet(helpOption)) {
		printUsage();
		return 0;
	}

	if(argSet(outputFilename)) {
		// Output specified
		printf("Writing output to %s\n", outputFilename);
	} else {
		free(outputFilename);
		outputFilename = DEFAULT_OUTFILE;
	}

	int steps = 0;
	// steps defines the number of times the program will evolve our lattice
	if(argSet(historySizeOption)) {
		steps = atoi(historySizeOption);
	}
	if(steps == 0) steps = DEFAULT_STEPS;
	unsigned int latticeSize = 0;
	if(argSet(latticeSizeOption)) {
		latticeSize = atoi(latticeSizeOption);
	}
	if(latticeSize == 0) latticeSize = DEFAULT_LATTICE_SIZE;

	// printf("Generating a history of %d lattice states (%f MB)\n",
	//  steps, ((float)((sizeof(Lattice)+latticeSize*(sizeof(State)+sizeof(Complex))) * steps))/(1e6));

	Lattice* history = new Lattice[steps + 1];

	puts("Finished allocating memory");

	// Initialize

	_float timestep = .1; // Something
	// Set initial lattice (*history);

	puts("Setting initial state...");
	history->initialize(0, latticeSize);
	history->setInitialState(0.1);

	// Evolve

	puts("Evolving...");

	Lattice* curr = &(history[0]);
	Lattice* next = NULL;
	printf("\n");


	FILE* f = fopen(outputFilename, "w");
	if(f == NULL)
	{
		fprintf(stderr, "Cannot write to %s\n", outputFilename);
		return 1;
	}

	register int i;
	for(i=0;i<steps;++i)
	{
		next = &(history[1+i]);
		next->initialize(0, latticeSize);

		curr->evolve(timestep, next);

		if(i % 5 == 0) {
			history[i].writeLattice(f);
			fprintf(f, "\n");
		}

		delete [] curr->lattice;

		curr = next;

		//printf("\rSteps: %05d", i);
		fflush(stdout);
	}
	printf("\n");

	// Analyze

	return 0;

}
