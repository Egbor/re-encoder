# Build
* 1. Type 'cd ./docker' to chnage the project directory to the build directory
* 2. Then type 'make' to build 'ffutil' docker image

# Run
* 1. Type 'make run [INPUTDIR=][INPUTFILENAME=][OUTPUTFILENAME=][TIMESTAMP=]'

## Arguments:
* 'INPUTDIR=' directory with input and output files
* 'INPUTFILENAME=' name of input file
* 'OUTPUTFILENAME=' name of output file
* 'TIMESTAMP=' from time in seconds to time in seconds

## Default argument value:
* INPUTDIR=~/
* INPUTFILENAME=mando_test.mkv
* OUTPUTFILENAME=mandu_test_cut.mkv
* TIMESTAMP="0 60"

## Examples:
* make run
* make run INPUTDIR=../../resources/
* make run INPUTDIR=../../resources/ TIMESTAMP="30 60"
* make run INPUTFILENAME=input.mkv OUTPUTFILENAME=output.mkv

# Run with shell
* 1. Type 'make sh' to run a docker container with the utility in interactive mode
