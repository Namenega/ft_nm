#!/bin/bash

CY='\033[0;36m'
GR='\033[1;32m'
NC='\033[0m' # No Color

echo "\n${CY}+-----------------------------------------+"
echo "|                                         |"
echo "|               START TESTS               |"
echo "|                                         |"
echo "+-----------------------------------------+\n\n"

echo ">> TESTING 19-provided files <<"
echo ""

echo""
echo "TEST 0: headers files"
echo "---------------------${NC}"
echo""
echo "${GR}./ft_nm nm-testers/error_header${NC}"
./ft_nm nm-testers/error_header
echo ""
echo "${GR}./ft_nm nm-testers/header${NC}"
./ft_nm nm-testers/header
echo ""
echo "${GR}./ft_nm nm-testers/header_and_prog_copy${NC}"
./ft_nm nm-testers/header_and_prog_copy
echo ""
echo "${GR}./ft_nm nm-testers/header_copy${NC}"
./ft_nm nm-testers/header_copy
echo ""
echo "${GR}./ft_nm nm-testers/header_offset_error${NC}"
./ft_nm nm-testers/header_offset_error

echo ""
echo ""
echo "${CY}TEST 1: string file"
echo "-------------------${NC}"
echo ""
echo "${GR}./ft_nm nm-testers/error_header${NC}"
./ft_nm nm-testers/unterminated_string

echo ""
echo ""
echo "${CY}TEST 2: wrong arch file"
echo "-----------------------${NC}"
echo ""
echo "${GR}./ft_nm nm-testers/error_header${NC}"
./ft_nm nm-testers/wrong_arch

echo "--------------------------------------------"
echo ""
echo ""
echo "${CY}TEST 3: (not_so)_easy_test file"
echo "-----------------------${NC}"
echo ""
echo "${GR}./ft_nm nm-testers/easy_test${NC}"
./ft_nm nm-testers/easy_test

echo ""
echo "${GR}./ft_nm nm-testers/not_so_easy_test${NC}"
./ft_nm nm-testers/not_so_easy_test

echo ""
echo "${GR}./ft_nm nm-testers/not_so_easy_test_32-bit${NC}"
./ft_nm nm-testers/not_so_easy_test_32-bit

echo ""
echo ""
echo "${CY}TEST 4: random tests"
echo "--------------------${NC}"
echo ""
echo "${GR}./ft_nm ./ft_nm${NC}"
./ft_nm ft_nm

echo ""
echo "${GR}./ft_nm a b ./ft_nm Makefile src src/main.o${NC}"
./ft_nm a b ./ft_nm Makefile src src/main.o

echo ""
echo ""
echo "${CY}TEST 4: Dynamic Library"
echo "--------------------${NC}"
echo ""
echo "${GR}./ft_nm /usr/lib/systemd/system/dbus.socket${NC}"
./ft_nm /usr/lib/systemd/system/dbus.socket
./ft_nm /usr/lib/brltty/libbrlttybcn.so

