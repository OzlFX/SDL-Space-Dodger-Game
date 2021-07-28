#include "cProgram.h"

//Main Init function


int main(int argc, char* argv[])
{
	cProgram* program = new cProgram();
	program->Update();
	delete program;
	return 0;
}