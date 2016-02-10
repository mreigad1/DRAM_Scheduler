Matthew Reigada
11/30/2015

DRAM Operation Scheduler Simulator

This program receives input operations from a formatted text file and simulates
an externally specified DRAM chip’s scheduling and operation. 

Notes:	No known bugs at current.  All programs receive input from cin and provide output to cout.
	Therefore input & output files are required with <> at program invocation.

Getting Started:

	DRAM Scheduler:
		(1)	Execute "make" to compile "main.cpp" into "driver"

		(2)	Invoke "./driver < [INPUT_FILE_NAME] > [OUTPUT_FILE_NAME]"
				Note: input.txt contains full example file with 10,000 lines

		(3)	Program will generate output file for comparison.
