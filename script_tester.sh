#!/bin/bash

GR='\033[1;32m'
RD='\033[0;31m'
CY='\033[0;36m'
NC='\033[0m' # No Color

echo "\n${CY}--------------- START TESTS ---------------${NC}\n\n"

#echo "${GR}Test 0: Unexistent file --> ./ft_nm abc${NC}"
#echo "${RD}"
#./ft_nm abc
#echo "${NC}\n"


#echo "${GR}Test 1: Directory --> ./ft_nm src${NC}"
#echo "${RD}"
#./ft_nm src
#echo "${NC}\n"

#echo "${GR}Test 2: non ELF file --> ./ft_nm Makefile${NC}"
#echo "${RD}"
#./ft_nm Makefile
#echo "${NC}\n"

#echo "${GR}Test 3: non ELF file --> ./ft_nm tester.txt${NC}"
#echo "${RD}"
#./ft_nm tester.txt
#echo "${NC}\n"

echo "${GR}Test 4: ELF file --> ./ft_nm ft_nm${NC}"
echo "${RD}"
./ft_nm ft_nm
echo "${NC}\n"

echo "${GR}Test 5: ELF file --> ./ft_nm src/main.o${NC}"
echo "${RD}"
./ft_nm src/main.o
echo "${NC}\n"

echo "${GR}Test 6: ELF file --> ./ft_nm /bin/ls${NC}"
echo "${RD}"
./ft_nm /bin/ls
echo "${NC}\n"
