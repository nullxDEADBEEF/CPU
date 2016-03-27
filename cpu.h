#pragma once
#include <stdint.h>
#include <stdio.h>

//typedef uint8_t u8;
//typedef uint16_t u16;

using u8 = unsigned char;

// REMEMBER 8-BITS 

// CPU THINGS
// CONTROL UNIT - regulates the flow of information within the processor
// fetch, decode, execute

// ALU(ARITHMETIC LOGIC UNIT) - circuit that does arithmetic operations
// does logical operations <, <=, >, >=

enum {
  ADX, ADY, SBX, SBY
, STA, STX, STY, LDA
, LDX, LDY, SPO, SPB
, BR, BRT, EQX, EQY
, NT, GRX, GRY, LSX
, LSY, SPP, LPP
};

struct Control_Unit {
  // Registers
  u8 accumilator;
  u8 x = 100, y = 1;
  u8 pb, po;
  u8 pp;
  u8 offset;
  u8 memory[1 << 8];
};

/*
u8   fetch();
void decode_and_execute();
void adx(u8 x); // implemented
void ady(u8 y); // implemented
void sbx(u8 x); // implemented
void sby(u8 y); // implemented
void sta(); // implemented
void stx(); // implemented
void sty(); // implemented
void lda(); // implemented
void ldx(); // implemented
void ldy(); // implemented
void spo(u8 po); // implemented
void spb(u8 pb); // implemented
void br(u8 offset); // implemented
void brt(u8 offset); // implemented
void eqx(u8 x); // implemented
void eqy(u8 y); // implemented
void nt(); // implemented
void grx(u8 x); // implemented
void gry(u8 y); // implemented
void lsx(u8 x); // implemented
void lsy(u8 y); // implemented
void spp(u8 pp); // implemented
void lpp(); // implemented
*/

Control_Unit control_unit;

// Add x to accumilator
void adx(u8 x) {
  control_unit.accumilator += x;
}

// Add y to accumilator
void ady(u8 y) {
  control_unit.accumilator += y;
}

// Subtract x from accumilator
void sbx(u8 x) {
  control_unit.accumilator -= x;
}

// Subtract y from accumilator
void sby(u8 y) {
  control_unit.accumilator -= y;
}

// Set page offset
void spo(u8 po) {
  control_unit.po = po;
}

// Set page base
void spb(u8 pb) {
  control_unit.pb = pb;
}

// Set program pointer
void spp(u8 pp) {
  control_unit.pp = pp;
}

// Store accumilator
void sta() {
  control_unit.accumilator += control_unit.po;
}

// Store x
void stx() {
  control_unit.x += control_unit.po;
}

// Store y
void sty() {
  control_unit.y += control_unit.po;
}

// Load accumilator
void lda() {
  control_unit.accumilator = (control_unit.pb << 8) + control_unit.po;
}

// Load x
void ldx() {
  control_unit.x = (control_unit.pb << 8) + control_unit.po;
}

// Load y
void ldy() {
  control_unit.y = (control_unit.pb << 8) + control_unit.po;
}

// Load program pointer
void lpp() {
  control_unit.pp = (control_unit.pb << 8) + control_unit.po;
}

// Branch
void br(u8 offset) {
  control_unit.pp += offset;
}

// Branch if true
void brt(u8 offset) {
  if (control_unit.accumilator != 0) {
    control_unit.pp += offset;
  }
  else {
    // nothing happens
  }
}

// Equal x
// does actions based on if the accumilator is equal to x or not
void eqx(u8 x) {
  if (control_unit.accumilator != x) {
    control_unit.accumilator = 0;
  }
  else {
    control_unit.accumilator = 1;
  }
}

// Equal y
// does actions based on if the accumilator is equal to y or not
void eqy(u8 y) {
  if (control_unit.accumilator != y) {
    control_unit.accumilator = 0;
  }
  else {
    control_unit.accumilator = 1;
  }
}

// not
// the name "nt" is because C++ has a not keyword.
// NEEDS TO DO SOME INVESTIGATION, THE MSVC COMPILER DOES
// NOT HAVE A "NOT" KEYWORD, BUT G++ DOES??
void not() {
  if (control_unit.accumilator == 0) {
    control_unit.accumilator = 1;
  }
  else {
    control_unit.accumilator = 0;
  }
}

// Greater than x
void grx(u8 x) {
  control_unit.accumilator = (u8)control_unit.accumilator > x;
}

// Greater than y
void gry(u8 y) {
  control_unit.accumilator = (u8)control_unit.accumilator > y;
}

// Less than x
void lsx(u8 x) {
  control_unit.accumilator = (u8)control_unit.accumilator < x;
}

// Less than y
void lsy(u8 y) {
  control_unit.accumilator = (u8)control_unit.accumilator < y;
}

// Retrieves instruction from memory
u8 fetch() {
  // the memory address in program memory
  // is determined by a program counter( PC ) 
  // that stores a number to identify the address of the next instruction

  // when an instruction is fetched the PC is incremented by the length
  // of the instruction, so that it will contain the address of the 
  // next instruction in the sequence.

  // We start by loading the program pointer
  // so we can point to the necessary places in memory

  // start retrieving instructions from memory
  control_unit.memory[control_unit.pp] = control_unit.memory[control_unit.pp];
  return control_unit.memory[control_unit.pp++];
}

// Decodes the retrieved instruction from memory
void decode_and_execute() {
  // The instruction that is fetched from memory 
  // will determine what the cpu will do.
  // The way the instruction is interpreted is defined 
  // by the CPU's instruction set architecture(ISA)

  // Often one group of bits within the instruction, called the opcode,
  // indicates which operation is to be performed, while the remaining
  // fields usually provide supplemental information required
  // for the operation, such as operands

  // those operands may be specified as a constant value, or as the
  //location of a value that may be a processor register or a 
  // memory address.
  
  u8 op = fetch();
  switch (op) {
  case ADX:
    adx(control_unit.x);
    break;
  case ADY:
    ady(control_unit.y);
    break;
  case SBX:
    sbx(control_unit.x);
    break;
  case SBY:
    sby(control_unit.y);
    break;
  case STA:
    sta();
    break;
  case STX:
    stx();
    break;
  case STY:
    sty();
    break;
  case LDA:
    lda();
    break;
  case LDX:
    ldx();
    break;
  case LDY:
    ldy();
  case SPO:
    spo(control_unit.po);
    break;
  case SPB:
    spb(control_unit.pb);
    break;
  case BR:
    br( control_unit.offset);
    break;
  case BRT:
    brt(control_unit.offset);
    break;
  case EQX:
    eqx(control_unit.x);
    break;
  case EQY:
    eqy(control_unit.y);
    break;
  case NT:
    not();
    break;
  case GRX:
    grx(control_unit.x);
    break;
  case GRY:
    gry(control_unit.y);
    break;
  case LSX:
    lsx(control_unit.x);
    break;
  case LSY:
    lsy(control_unit.y);
    break;
  case SPP:
    spp(control_unit.pp);
    break;
  case LPP:
    lpp();
    break;
  default:
    printf("not an instruction... so we don't really care\n");
    break;
  }
}

void decode_and_execute_test() {
	// we assign instructions in memory manually, just for testing purposes
	control_unit.memory[0] = ADX;
	control_unit.memory[1] = ADY;
	control_unit.memory[2] = ADX;
  decode_and_execute();
}
