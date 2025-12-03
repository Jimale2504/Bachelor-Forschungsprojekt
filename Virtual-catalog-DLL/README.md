# Virtual-catalog-DLL
Vurtual catalog of the 5472730538 min lexical sudoku solution grids 

This repository contains the necessary files to use a DLL offering the following services related to the 
NED= 5472730538 possible min lexical solution grids of a sudoku.

the three main services are 

give the rank 1-NED get the solution grid

Give a solution grid, get the rank 1-NED

Get a virtual file for a sequential process on part of the catalog.

The virtual file is always a sequence of the 652408 valid fills for the first four rows of a solution grid;
In the frist delivery, the sequence fits with a given chunks of the first band

The repository contains 

all DLL and .LIB files used here

The sources of the DLL

User files for all the DLL 

and a sample file used to test the DLL

The sources for the DLLs called by the virtual catalog can be seen in another repository
https://github.com/GPenet/Virtual-calatog

4 more  DLL are needed

skbminlex    giving Id and mapping for a band

skbvcminlex  same, but a special variant with a quicker respond in the virtual catalog context

skgminlex    giving the gangster Id and the fills avalble for the band

skbgridmin  giving the min lexical morph of a given grid (with auto morphs in option)

            a special entry for the virtual catalog gives a quicker response if the entry is not minimal
            

Note : One reason to include here all user files and .lib files of called DLLs 
is that the user can call any of the entries of these DLLs, 
but anyway, the four DLLs must be available to use this DLL



