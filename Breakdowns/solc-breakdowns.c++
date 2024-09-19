
// Contract creation code....
// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3 

// runtime code
// fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056


// metadata
// fea2646970667358221220c276cfaa26a978c7cbd6472fe8f6998f4608429a6fb1e97f12f1b1fd0b52111d64736f6c63430008140033


// ? CONTRACT CREATION CODE.....................
//////////////////////////////
PUSH1 0x80 // [0x80]
PUSH1 0x40   // [0x40, 0x80]                 // ---> Free memory pointer
MSTORE     // Memory[0x40: 0x80]
//////////////////////////

///////////////////////////////
// If someone sent value to this call REVERT and If someone didn't send any value to this call, Jump to the 0x0E PC/JumpDest...

CALLVALUE    // [msg.value]
DUP1         // [msg.value, msg.value]
ISZERO       // [msg.value == 0, msg.value]
PUSH1 0x0e   // [0x0E, msg.value == 0, msg.value]
JUMPI        // [msg.value]
PUSH0       // [0x00, msg.value
DUP1        // [0x00, 0x00, msg.value]
REVERT      // [msg.value]
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////

// Jump dest if msg.value == 0
// ! STICKS THE RUNTIME CODE ON-CHAIN..
JUMPDEST   // [msg.value]
POP        // []
PUSH1 0xa5 // [0xa5]
DUP1       // [0xa5, 0xa5]
PUSH2 0x001b // [0x001b, 0xa5, 0xa5]
PUSH0        // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY     // [0xa5]     Memory: [runtime code]
PUSH0        // [0x00, 0xa5]
RETURN       // []
INVALID  // --> Signifies the end of the contract creation sequence..
////////////////////////////////////////
// ? ///////////////////////////////////////////////////////////////////////////////////////////////////////

// 2. RUNTIME CODE..................
// Entry point for all calls....
////////////////////////////////////////////////////////
PUSH1 0x80 // [0x80]
PUSH1 0x40 // [0x40, 0x80]       ---->  Free memory pointer
MSTORE    // []
///////////////////////////////////////////////////////////

// check for msg.value, and if given, REVERT!

CALLVALUE // [msg.value]
DUP1      // [msg.value, msg.value]
ISZERO    // [msg.value == 0, msg.value]
PUSH1 0x0e  // [0x0e, msg.value == 0, msg.value]
JUMPI      // [msg.value]
PUSH0     // [0x00, msg.value]
DUP1      // [0x00, 0x00, msg.value]
REVERT    // [msg.value]

// if msg.value == 0, start here!!
JUMPDEST  // [msg.value]
POP       // []
PUSH1 0x04 // [0x04]
CALLDATASIZE  // [CALLDATASIZE, 0x04]
LT            // [CALLDATASIZE < 0x04]
PUSH1 0x30    // [0x30, CALLDATASIZE < 0x04]
JUMPI         // []
// if calldata_size < 0x04 -> calldata_Jump

///////////////////////////
// Function dispatcher ////

PUSH0     // [0x00]
CALLDATALOAD  // [32 bytes of calldata]
PUSH1 0xe0   // [0xe0, 32 bytes of Calldata]
SHR         // [calldata[0:4]] <<< function_selector
DUP1        // [func_selector, func_selector]
PUSH4 0xcdfead2e // [0xcdfead2e, func_selector, func_selector]
EQ              // [0xcdfead2e == func_selector, func_selector]
PUSH1 0x34      // [0x34, 0xcdfead2e == func_selector, func_selector]
JUMPI          // [func_selector]
// if func_selector == 0xcdfead2e -> UpdateNumberofhorses
/////////////////////////////////////////////////////////////////
// func dispatching for readNumberOfHorses
DUP1 // [func_selector, func_selector]
PUSH4 0xe026c017  // [0xe026c017, func_selector, func_selector]
EQ                // [func_selector == 0xe026c017, func_selector]
PUSH1 0x45        // [0x45, func_selector == 0xe026c017, func_selector]
JUMPI             // [func_selector]
// if func_selector == 0xe026c017 -> readNumberOfHorses
////////////////////////////////////////////////////////////////////////////
/////////////
// Revert JUMDEST
JUMPDEST // []
PUSH0 // [0x00]
DUP1  // [0x00, 0x00]
REVERT // []
/////////////////////////////////
///////////////////////////////////////////////
// updateHorseNumber jump dest 1
// SetUp jumping program counters in the stack..
JUMPDEST // [func_selector]
PUSH1 0x43 // [0x43, func_selector]
PUSH1 0x3f // [0x3f, 0x43, func_selector]
CALLDATASIZE // [calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x04   // [0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x59   // [0x59 ,0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMP         // [0x04, calldatasize, 0x3f, 0x43, func_selector]

////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////

// Jump dest 4
// We can finally run a sstore to save our value to storage.
// We can only do this if::
// 1. Function dispatch
// 2. checked for msg.value
// 3. checked the calldata is long enough
// 4. Received the number to use from the calldata.

JUMPDEST   // [calldata (of numberToUpdate), 0x43, func_selector]
PUSH0      // [0x00, calldata (of numberToUpdate),0x43, func_selector]
SSTORE     // [0x43, func_selector]
JUMP       // [func_selector]
// Jump dest 5
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Jump dest 5
JUMPDEST  // [func_selector]
STOP     // [func_selector]
///////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReadNumberOfHorses Jump dest 1
// the only Jump dest for ReadNumberOfHorses
JUMPDEST    // [func_selector]
PUSH0         // [0x00, func_selector]
SLOAD       //  [num_Horses, func_selector]
PUSH1 0x40  //  [0x40 ,num_Horses, func_selector]
MLOAD      // [0x80, num_Horses, func_selector]  Memory[0x40: 0x80](Free memory pointer)
SWAP1      // [ num_Horses, 0x80, func_selector]
DUP2       // [0x80, num_Horses, 0x80, func_selector]
MSTORE     // [0x80, func_selector]         Memory[0x80: num_Horses]
PUSH1 0x20  // [0x20, 0x80, func_selector]
ADD         // [0x20 + 0x80 = 0xa0 , func_selector]
PUSH1 0x40 // [0x40, 0xa0, func_selector]
MLOAD     // [0x80, 0xa0, func_selector]
DUP1     // [0x80, 0x80, 0xa0, func_selector]
SWAP2    // [0xa0, 0x80, 0x80, func_selector]
SUB      // [0x20, 0x80, func_selector ]
SWAP1   // [0x80, 0x20, func_selector]
// return a value of 32 bytes that is located at position 0x80 in memory...
RETURN // [func_selector]
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////
// updateHorseNumber jump dest 2 
// Check if there is a value to update the horse Number to...
// 4 bytes for the function selector, 32 bytes for the horseNumber
JUMPDEST  // [0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH0     //  [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x20  //  [ 0x20 ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
DUP3        // [ 0x04, 0x20 ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
DUP5        //  [calldatsize ,0x04, 0x20 ,0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
SUB         // [calldatsize - 0x04, 0x20 ,0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
// below we are asking ourselves whether there is more calldata than just the function selector??

SLT         // [calldatsize - 0x04 < 0x20 ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
ISZERO     //  [calldatsize - 0x04 < 0x20 == true(more_calldata_than_selector) ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x68 // [0x68, calldatsize - 0x04 < 0x20 == true(more_calldata_than_selector) ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
JUMPI     // [0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
// We are going to jump to jump dest 3 if there is more calldata than:
// function_selector + 0x20
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// Revert if there isn't enough collateral...
PUSH0 // [0x00 ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
DUP1  // [0x00, 0x00 ,0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
REVERT // [0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
// UpdateHorseNumber jump dest 3
// Grab the calldata for updating the horse number.
// delete some stuff in the stack.
JUMPDEST // [0x00, 0x04 calldatasize, 0x3f, 0x43, func_selector]
POP     // [0x04 calldatasize, 0x3f, 0x43, func_selector]

// Ignore the function selector, and just grab the data 

CALLDATALOAD // [calldata (of numberToUpdate),calldatasize, 0x3f, 0x43, func_selector]
SWAP2        // [0x3f, calldatasize, calldata (of numberToUpdate),  0x43, func_selector]
SWAP1       // [calldatasize, 0x3f, calldata (of numberToUpdate),  0x43, func_selector]
POP         // [0x3f,calldata (of numberToUpdate), 0x43, func_selector]
JUMP        // [calldata (of numberToUpdate), 0x43, func_selector]
// jump to jump dest 4...
////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3. Metadata
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
PUSH23 0xcfaa26a978c7cbd6472fe8f6998f4608429a6fb1e97f12
CALL
INVALID
REVERT
SIGNEXTEND
MSTORE
GT
SAR
PUSH5 0x736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////