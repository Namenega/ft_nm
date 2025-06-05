#!/bin/bash

GR='\033[1;32m'
CY='\033[0;36m'
NC='\033[0m' # No Color

echo "\n${CY}+-----------------------------------------+"
echo "|                                         |"
echo "|               START TESTS               |"
echo "|                                         |"
echo "+-----------------------------------------+\n\n"

echo "\n>> FIRST TESTS: ARGUMENTS ${NC}\n"

echo "${GR}Test 0: Too many arguments --> ./ft_nm a b c d${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm a b c d
echo "\n"

echo "${GR}Test 1: No argument --> ./ft_nm${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm
echo "\n"

echo "${GR}Test 2: Unexistent file --> ./ft_nm abc${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm abc
echo "\n"

echo "${GR}Test 3: Directory --> ./ft_nm src${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm src
echo "\n"

echo "${GR}Test 4: non ELF file --> ./ft_nm Makefile${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm Makefile
echo "\n"

echo "${GR}Test 5: non ELF file --> ./ft_nm tester.txt${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm ./resources/tester.txt
echo "\n"

#-------------------------------------------------------------

echo "\n\n${CY}>> SECOND TESTS: ELF FILES ${NC}\n"

echo "${GR}Test 6: ELF file --> ./ft_nm ft_nm${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm ft_nm
echo "\n"

echo "${GR}Test 7: ELF file --> ./ft_nm src/main.o${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm src/main.o
echo "\n"

echo "${GR}Test 8: ELF file --> ./ft_nm /bin/ls${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm /bin/ls
echo "\n"

#-------------------------------------------------------------

echo "\n\n${CY}>> THIRD TEST: EVERYTHING ${NC}\n"

echo "${GR}Test 9: Everything --> ./ft_nm a b ft_nm Makefile /bin/ls /bin/grep ./resources/tester.txt src ./src/main.o${NC}"
echo ""
#valgrind --leak-check=full
./ft_nm a b ft_nm Makefile /bin/ls /bin/grep ./resources/tester.txt src ./src/main.o
echo "\n"
