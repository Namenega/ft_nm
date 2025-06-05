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

echo "${GR}Test 0: Too many arguments --> nm a b c d${NC}"
echo ""
nm a b c d
echo "\n"

echo "${GR}Test 1: No argument --> nm${NC}"
echo ""
nm
echo "\n"

echo "${GR}Test 2: Unexistent file --> nm abc${NC}"
echo ""
nm abc
echo "\n"

echo "${GR}Test 3: Directory --> nm src${NC}"
echo ""
nm src
echo "\n"

echo "${GR}Test 4: non ELF file --> nm Makefile${NC}"
echo ""
nm Makefile
echo "\n"

echo "${GR}Test 5: non ELF file --> nm tester.txt${NC}"
echo ""
nm ./resources/tester.txt
echo "\n"

#-------------------------------------------------------------

echo "\n\n${CY}>> SECOND TESTS: ELF FILES ${NC}\n"

echo "${GR}Test 6: ELF file --> nm ft_nm${NC}"
echo ""
nm ft_nm
echo "\n"

echo "${GR}Test 7: ELF file --> nm src/main.o${NC}"
echo ""
nm src/main.o
echo "\n"

echo "${GR}Test 8: ELF file --> nm /bin/ls${NC}"
echo ""
nm /bin/ls
echo "\n"

#-------------------------------------------------------------

echo "\n\n${CY}>> THIRD TEST: EVERYTHING ${NC}\n"

echo "${GR}Test 9: Everything --> nm a b ft_nm Makefile /bin/ls /bin/grep ./resources/tester.txt src ./src/main.o${NC}"
echo ""
nm a b ft_nm Makefile /bin/ls /bin/grep ./resources/tester.txt src ./src/main.o
echo "\n"

