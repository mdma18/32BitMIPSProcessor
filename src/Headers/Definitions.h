#ifndef DEFINITIONS_H
#define DEFINITION_H

#pragma once
///All headers, constants and prepocessor directives
#include <cstdio>
#include <cmath>
#include <vector>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
///Instruction Properties
constexpr auto MIPS_32 = 32;
constexpr auto OP	  = 6;
constexpr auto DATA	  = 5;
constexpr auto CONST  = 16;
constexpr auto TARGET = 26;
constexpr auto RTYPE  = 0x00;
constexpr auto JTYPE2 = 0x02;
constexpr auto JTYPE3 = 0x03;
constexpr auto SW	  = 0x2B;
constexpr auto NOP    = 0x00;
///ALU Operations
constexpr auto ADDIU  = 0x09;
constexpr auto SLT	  = 0x2A;
constexpr auto BEQ	  = 0x04;
constexpr auto ADDI	  = 0x08;
constexpr auto BNE    = 0x05;
constexpr auto ADD	  = 0x20;
constexpr auto SUB	  = 0x22;

constexpr auto MemSize = 65536;
#endif // !DEFINITIONS_H