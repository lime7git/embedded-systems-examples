#include "commands_interface.h"

static volatile uint8_t commands_counter = 0;

void Command_Parser_Handler(tCircular_buffer *hBuffer)	// parse single command from circular buffer
{
	if(commands_counter > 0)
	{
		uint8_t single_command[COMMAND_FRAME_SIZE] = {NULL};
		eCircular_buffer_status result;
		uint8_t tmp_buf;
		unsigned int tmp_cnt = 0;
		
		do	// pop out circular buffer till find command start charater
		{
			result = tCircular_buffer_pop(hBuffer, &tmp_buf);
			
			if(result == BUFFER_EMPTY) // if there is no command start character in buffer
			{
				Serial_Log("\r\nUnknown command!\r\n");
				tCircular_buffer_clear(hBuffer);
				commands_counter = 0;
				break;
			}
		}	while(tmp_buf != COMMAND_START_CHAR);
		
		tmp_cnt = 0;
		
		do	// pop out circular buffer starting after start charater, till stop charater to extract single command
		{
			result = tCircular_buffer_pop(hBuffer, &tmp_buf);
			
			if(result == BUFFER_EMPTY) // if there is no command stop character in buffer
			{
				Serial_Log("\r\nUnknown command!\r\n");
				tCircular_buffer_clear(hBuffer);
				commands_counter = 0;
				break;
			}
			
			if(tmp_buf != COMMAND_STOP_CHAR) single_command[tmp_cnt] = tmp_buf;	// store command in single command array
			tmp_cnt++;

		}	while(tmp_buf != COMMAND_STOP_CHAR);

		if(result != BUFFER_EMPTY) commands_counter--; 
		
		if(result != BUFFER_EMPTY) Command_Execute((char *)single_command);	// execute extracted single command
	}
}
void Command_Execute(char *command)
{
	switch(Command_Get_Type(command))	// get type of executed command
	{
		case UNKNOWN:	// proper frame with start and stop charaters, but command is unknown
		{
			char buf[128];
			sprintf(buf, "Unknown command!\t $%s# \r\n", command);
		
			Serial_Log(buf);
		
			break;
		}
		case LED:
		{
			char param_buffer[PARAM_BUFFER_ROWS][PARAM_BUFFER_COLS];
			Command_Get_Params(command, param_buffer);

			uint8_t led_num = atoi(param_buffer[0]);
			uint8_t led_state = atoi(param_buffer[1]);

			// Led_Switch(led_num, led_state);
			
			break;
		}
		case STATE:
		{
			char param_buffer[PARAM_BUFFER_ROWS][PARAM_BUFFER_COLS];
			Command_Get_Params(command, param_buffer);

			uint8_t state = 0;
			
			if(param_buffer[0][0] == 'G' && param_buffer[0][1] == 'E' && param_buffer[0][2] == 'T')	// if first parameter == "GET"
			{
				char buf[32];
				sprintf(buf, "Actual state = %i \r\n", state);
				Serial_Log(buf);
			}
			else if(param_buffer[0][0] == 'S' && param_buffer[0][1] == 'E' && param_buffer[0][2] == 'T') // if first parameter == "SET"
			{	
				if((atoi(param_buffer[1]) >= 0) && (atoi(param_buffer[1]) <= 10)) // if second parameter in valid range
				state = atoi(param_buffer[0]);
			}
			else
			{
			Serial_Log("\r\nUnknown state!\r\n");	
			}				
			
			break;
		}
		case READY:
		{	
			char param_buffer[PARAM_BUFFER_ROWS][PARAM_BUFFER_COLS];
			Command_Get_Params(command, param_buffer);
			
			if(param_buffer[0][0] == '?')
			{
			Serial_Log("\r\nREADY\r\n");
			}
			
			break;
		}
	}
}
eCOMMANDS Command_Get_Type(char *command)
{
	char command_type[COMMAND_TYPE_MAX_LENGTH];
	eCOMMANDS type = UNKNOWN;
	unsigned int counter = 0;
	
	while( (command[counter] != COMMAND_SPLITTER_CHAR) && (counter < strlen(command)) )	// extract only command type from frame
	{
		command_type[counter] = command[counter];
		
		counter++;
	}
	
	// check command type
	if	   (strncmp(command_type, "LED", 	counter) == 0) type = LED;
	else if(strncmp(command_type, "STATE",	counter) == 0) type = STATE;
	else if(strncmp(command_type, "READY", 	counter) == 0) type = READY;
	else type = UNKNOWN;
	
	return type;
}
unsigned int Command_Get_Params(char *command, char param_buffer[PARAM_BUFFER_ROWS][PARAM_BUFFER_COLS])
{
  unsigned int counter = 0, single_param_counter = 0, params_counter = 0;

	while(command[counter++] != COMMAND_SPLITTER_CHAR) {}	// skip command type, start after command splitter char (first parameter)

	command = &command[counter];	// point on first parameter

    counter = 0;
    while(counter < strlen(command))
    {
        if(command[counter] == COMMAND_PARAMETERS_SPLITTER_CHAR) // if new parameter
        {
           params_counter++;
           single_param_counter = 0;
        }
        else
        {
            param_buffer[params_counter][single_param_counter] = command[counter];	// split parameters into parameters buffer
            single_param_counter++;
        }

    counter++;
    }

    return (params_counter + 1);
}
void Command_IRQ_Handler(tCircular_buffer *hBuffer, uint8_t data)	// place inside serial reciever interrupt handler 
{
	tCircular_buffer_push(hBuffer, data);	// push recieve byte into buffer
	
	if(data == COMMAND_STOP_CHAR) commands_counter++; // if there is a stop char inside buffer, suppose that there is a command inside
}
void Serial_Log(const char *message)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 100);
}
