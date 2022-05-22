#ifndef _COMMANDS_INTERFACE_H
#define _COMMANDS_INTERFACE_H

#include "main.h"
#include "stdio.h"
#include "string.h"

#include "circular_buffer.h"

#define COMMAND_START_CHAR					'$'
#define COMMAND_STOP_CHAR 					'#'
#define COMMAND_SPLITTER_CHAR 				'='
#define COMMAND_PARAMETERS_SPLITTER_CHAR 	','

#define PARAM_BUFFER_ROWS 4			// maximum number of additional parameters
#define PARAM_BUFFER_COLS 32		// maximum length of single additional parameter

#define COMMAND_TYPE_MAX_LENGTH 16
#define COMMAND_FRAME_SIZE 		32

typedef enum{
	UNKNOWN,
	LED,
	STATE,
	READY
} eCOMMANDS;

void Command_Parser_Handler(tCircular_buffer *hBuffer);
void Command_Execute(char *command);
eCOMMANDS Command_Get_Type(char *command);
unsigned int Command_Get_Params(char *command, char param_buffer[PARAM_BUFFER_ROWS][PARAM_BUFFER_COLS]);
void Command_IRQ_Handler(tCircular_buffer *hBuffer, uint8_t data);
void Serial_Log(const char *message);

#endif
