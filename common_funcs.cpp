#include "common_funcs.h"


bool checksumValid(uint8_t* packet){
	uint8_t sum = 0;
	for(uint8_t i = 2; i<(packet[LENGTH_POS]+3);i++){
		sum+=packet[i];
	}
	sum = ~sum;
	if(sum == packet[packet[LENGTH_POS]+3]) {
		return true;
	} else {
		return false;
	}
}


bool checksumValid(uint8_t id, uint8_t length, uint8_t* packet) {
	uint8_t sum = id + length;
	uint8_t i;
	for(i = 0; i < length - 1;i++) {
		sum += packet[i];
	}
	sum = ~(sum);
	if(sum == packet[length-1]) {
		return true;
	} else {
		return false;
	}
}

void UARTInterruptHandler(void)
{
	//
	//wil prevent the interrupt from being called again, clears the asserted interrupts
	//
	cRs485Bus.clearInterrupt();
	uint8_t ch = UARTCharGetNonBlocking(UART1_BASE);
	cRingBuffer.put(ch);


	//	uint8_t packet[20];
	//
	////	uint8_t header[2];
	////	uint8_t id, length;
	////	uint8_t command[10];  //contains the instruction and the parameters
	//
	//	uint8_t prev_byte;
	//	uint8_t curr_byte;
	//	uint8_t count;
	//
	//	while(cRs485Bus.charsAvailable()) //loop while there are chars
	//	{
	//		bool first_flag = true; //if this is true this is first time we are iterating through a given data
	//		while(cRs485Bus.getData(&curr_byte, 1)){
	//			if(first_flag == true){
	//				first_flag = false;
	//				prev_byte = curr_byte;
	//				continue;
	//			}
	//			else{
	//				if(curr_byte == 0xff && prev_byte == 0xff){
	//					for(uint8_t i = 0;i<20;i++)
	//						packet[i] = 0;
	//					count = 0;
	//					packet[count++] = 0xff;
	//					packet[count++] = 0xff;
	//				}
	//				else{
	//					packet[count++] = curr_byte;
	//				}
	//			}
	//			prev_byte = curr_byte;
	//			if(packet[LENGTH_POS]!=0 && count == packet[LENGTH_POS]+4)
	//				break;
	//		}
	//
	//		if(packet[ID_POS] == cParams.getId() || packet[ID_POS] == cRs485Bus.BROADCAST_ID){
	//			//check for validity of checksum
	//			if(checksumValid(packet)){
	//				//check for the various commands and send the control to those functions
	//				if(packet[INSTRUCTION_POS] == INSTR_PING){
	//					printf("in ping\n");
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_READ_REG){
	//					printf("in read\n");
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_WRITE_REG){
	//					printf("in write\n");
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_WRITE_QUEUE){
	//
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_QUEUE_ACTION){
	//
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_FACTORY_RESET){
	//
	//				}
	//
	//				else if(packet[INSTRUCTION_POS] == INSTR_SYNC_WRITE){
	//
	//				}
	//
	//			}
	//			else{
	//				//TODO: return a error code
	//				printf("Invalid checksum\n");
	//			}
	//		}




	//		// Read headers
	//		cRs485Bus.getData(header, 2); //cRs485Bus.getByte();
	//		header[0] = UARTCharGetNonBlocking(UART1_BASE);
	//		header[1] = UARTCharGetNonBlocking(UART1_BASE);
	//
	//		if (header[0] == 0xff && header[1] == 0xff) {
	//			// Every transmit should include a TXEN pin HIGH transition
	//			//			cRs485Bus.sendD
	//
	//			uint8_t ch = 'Y';
	//			cRs485Bus.sendData(&ch,1);
	//
	//			id = cRs485Bus.getByte();
	//
	//			if (id == cParams.getId() || id == cRs485Bus.BROADCAST_ID) {
	//				length = cRs485Bus.getByte();
	//
	//				if(length > 10) { // temporary length cap
	//					//    				return err
	//				}
	//
	//				cRs485Bus.getData(command, length);
	//				//				for(i = 0; i < length; i++) {
	//				//					// Length = number of bytes after the length byte including checksum
	//				//					// (Check dynamixel docs)
	//				//					command[i] = UARTCharGetNonBlocking(UART1_BASE);
	//				//				}
	//
	//				if (checksumValid(id, length, command)) {
	//					if (command[0] == INSTR_READ_REG) {
	//						uint8_t add = command[1];
	//						uint8_t nBytes = command[2];
	//						if(nBytes > 2) {
	//							//err
	//						}
	//						uint8_t returnData = cParams.getParam(add+i);
	//						cRs485Bus.sendData(&(returnData), nBytes);
	//						//						for (i = 0; i < nBytes; i++) {
	//						//							// TODO: CREATE A RESPONSE packet here
	//						//
	//						//							UARTCharPutNonBlocking(UART1_BASE, cParams.getParam(add+i));
	//						//						}
	//					} else if (command[0] == INSTR_WRITE_REG) {
	//						uint8_t add = command[1];
	//						// if 1 byte packet = ff,ff,id,len,instr, where,byte,checksum = 8 bytes so len=5
	//						// for 2 bytes(hi,lo) packet = ff,ff,id,len,instr,where,hi,lo,checksum = 9 bytes, len=5
	//
	//						if (length == 5) { // more than 1 byte to write
	//							uint16_t data = command[3]<<8 + command[2];
	//							cParams.setParam2Byte(add, data);
	//						} else {
	//							cParams.setParam(add, command[2]);
	//						}
	//					}
	//				} else {
	//					uint8_t ch = 'E';
	//					cRs485Bus.sendData(&ch,1);
	//				}
	//			}
	//
	//		} else {
	//			UARTCharPutNonBlocking(UART1_BASE, 'X');
	//		}
}

/***
 * -> check if the length of the packet is greater than equal to 4
 * -> following cases may arise:
 *		1. first two bytes are 0xff 0xff and there is correct packet following it
 *		2. first two bytes are 0xff 0xff and the packet is courrupted, checksum does not match.
 *		3. first two bytes are 0xff 0xff and the packet is incomplete, 0xff 0xff comes later again
 *		4. first two bytes are not 0xff 0xff and packet starts elsewhere
 * ** case 1 **
 * 	->check the length byte and ensure that the count is greater than that
 ***/
bool isPacketAvailable(){
	uint8_t dummy_tail = cRingBuffer.tail;
	uint8_t dummy_head = cRingBuffer.head;
	uint8_t curr_byte, prev_byte;
	uint8_t c = 0, i; //local function counter
	uint8_t packet[20];
	bool ret_val = false;
	bool packet_found = false;

	while(c < cRingBuffer.count){
		curr_byte = cRingBuffer.buff[dummy_tail + c];
		if(c == 0){
			prev_byte = curr_byte;
			c++;
			continue;
		}
		if(packet_found == true && i == packet[LENGTH_POS]+4)
			break;
		if(packet_found == true){
			packet[i++] = curr_byte;
		}
		if(curr_byte == 0xff && prev_byte == 0xff){
			for(i=0; i<20;i++)
				packet[i] = 0;
			i=0;
			packet[i++] = 0xff;
			packet[i++] = 0xff;
			packet_found =  true;
		}

		prev_byte = curr_byte;
		c++;
	}

	if(packet[ID_POS] == cParams.getId() || packet[ID_POS] == cRs485Bus.BROADCAST_ID){
		//check for validity of checksum
		if(checksumValid(packet)){
			//check for the various commands and send the control to those functions
			if(packet[INSTRUCTION_POS] == INSTR_PING){
				printf("in ping\n");
			}

			else if(packet[INSTRUCTION_POS] == INSTR_READ_REG){
				printf("in read\n");
			}

			else if(packet[INSTRUCTION_POS] == INSTR_WRITE_REG){
				printf("in write\n");
			}

			else if(packet[INSTRUCTION_POS] == INSTR_WRITE_QUEUE){

			}

			else if(packet[INSTRUCTION_POS] == INSTR_QUEUE_ACTION){

			}

			else if(packet[INSTRUCTION_POS] == INSTR_FACTORY_RESET){

			}

			else if(packet[INSTRUCTION_POS] == INSTR_SYNC_WRITE){

			}

		}
		else{
			//TODO: return a error code
			printf("Invalid checksum\n");
		}
	}

	return true;
}
