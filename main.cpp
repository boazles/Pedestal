#include <stdint.h>     // C99 fixed data types
#include <stdio.h>      // Standard input/output definitions
#include <stdlib.h>     // C standard library
#include <string.h>     // String function definitions
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
/* void send(std::string);
int fd;
int  main(void)
{
    
    fd = open ("/dev/ttyUSB0", O_RDWR  | O_NOCTTY);
    if (fd ==1)
    {
        printf("\n ERROR in Opening ttyUSB0\n");
    }
     else
        printf("\n ttyUSB0 Opened Successfully\n");

	int rc ; //return value
    struct termios SerialPortSettings;
	// Get the current options for the port
    if((rc = tcgetattr(fd, &SerialPortSettings)) < 0){
        fprintf(stderr, "failed to get attr: %d, Error is: %s\n", fd, strerror(errno));
       // exit(EXIT_FAILURE);
    }

        
        //tcgetattr(fd, &SerialPortSettings);
        cfsetispeed(&SerialPortSettings, B2400);
        cfsetospeed(&SerialPortSettings, B2400);
        
        /* 8N1 Mode */
		
		//SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
		//SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
		//SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
		//SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */

        //SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
        //SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
		//SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		//SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

		//SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
		
		/* Setting Time outs */
		//SerialPortSettings.c_cc[VMIN] = 10; /* Read at least 10 characters */
		//SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

/*
		if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
   /*     {
		    printf("\n  ERROR ! in Setting attributes\n");
            fprintf(stderr, "failed to set attr: %d, %s\n", fd, strerror(errno));
            exit(EXIT_FAILURE);
        }
		else
                    printf("\n  BaudRate = 2400 \n  StopBits = 1 \n  Parity   = none");
			
	        /*------------------------------- Read data from serial port -----------------------------*/

		//tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */
		//send("Z=00");
		//unsigned char read_buffer[19];   /* Buffer to store the data received              */
		//int  bytes_read = 0;    /* Number of bytes read by the read() system call */
 		/*int i = 0;
		
			send("J=80,80");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			send("R=F");
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				send("R=O");
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				send("J=80,80");
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				send("W=001000F80");
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				send("J=80,80");
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				int l=0;
		while(l<2)
		{
			bool end = false;
			while (!end)
			{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			bytes_read = read(fd,&read_buffer,19); /* Read the data                   */
			
			//printf("\n\n  Bytes Rxed %d", bytes_read); /* Print the number of bytes read */
			//printf("\n\n  ");

			//for(i=0;i<bytes_read;i++)	{ /*printing only the received characters*/
		    /*	printf("0x%02x",read_buffer[i]);
				if ( read_buffer[i] == 0x0A)
				end=true;
				printf("\n +----------------------------------+\n\n\n");
			}
			}
			if (bytes_read != 0 )
			{
				tcflush(fd, TCIFLUSH); 
				bytes_read ==0;
				send("J=00,80");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				send("J=80,80");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				send("J=80,80");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				l++;
			}
			else{
				l++;
			}
		}
			// unsigned char write_buffer[] = {0x24 ,0x50, 0x3d, 0x43, 0x30, 0x36 ,0x42, 0x2c, 0x41, 0x36, 0x41, 0x38, 0x2c, 0x30, 0x30, 0x30, 0x30, 0x80, 0x0D, 0x0A};
			// //unsigned char write_buffer[] = "$P=C06B,A6A8,000080\r\n";	/* Buffer containing characters to write into port	     */	
			// int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */ 

			// bytes_written = write(fd,write_buffer,sizeof(write_buffer));
			// 							 /* use write() to send data to port                                            */
			// 						     /* "fd"                   - file descriptor pointing to the opened serial port */
			// 						     /*	"write_buffer"         - address of the buffer containing data	            */
			// 						     /* "sizeof(write_buffer)" - No of bytes to write                               */	
			// tcdrain(fd);
			// printf("\n  %s written to ttyUSB0",write_buffer);
			// printf("\n  %d Bytes written to ttyUSB0", bytes_written);
			// printf("\n +----------------------------------+\n\n");
			//  const char* str = "A4D3,C2A8,0000";
			 
			 
    		//  for (const char* p = str; *p; ++p)
    		//  {
        	//  	printf("0x%02x\n", *p);
				
    		//  }
    		//  printf("\n");


			//  std::string msg  = "56D2,A2A8,0000";
			 
			//  //unsigned char msg_buf[sizeof(msg)];

			// // for (int index = 0 ; index <sizeof(msg_buf); index++ )
			// // {
			// // 	msg_buf[index] = msg.at(index);
			// // }
			// // printf("%s",msg_buf );
			// unsigned char checksum = 0; // could be an int if preferred
			// std::string stra = "P=" + msg; 
			// std::cout << "string is:" << stra << std::endl;
			// int SizeOfArray = stra.size();
			// std::cout << "length is:" << SizeOfArray << std::endl;
			// for(int x = 0; x < SizeOfArray; x++)
			// {
      		// 	checksum += stra[x]%256;
	  		// 	printf("current %d CRC for MyArray is: %d\n",x, checksum);
			// }

			// printf("size of myArray is %d Checksum for MyArray is: %d\n",SizeOfArray, checksum);
			
			// //sprintf(crc,"%x", checksum);
			// std::stringstream ss;
			// ss << checksum;
			// std::string crc = ss.str();
			
			// std::string message = "$" + stra +crc + "\r\n";
			// std::cout << "string is:" << message << std::endl;
			// unsigned char write_buf[message.size()];
			// for (int i = 0 ; i <sizeof(write_buf); i++ )
			// {
			// 		write_buf[i] = message.at(i);
			// }
			// bytes_written=0;
			// bytes_written = write(fd,write_buf,sizeof(write_buf));   // use write() to send data to port 
			// tcdrain(fd);
			// printf("\n  %s written to ttyUSB0",write_buf);
			// printf("\n  %d Bytes written to ttyUSB0", bytes_written);
			// printf("\n +----------------------------------+\n\n");
		//}

		//close(fd); /* Close the serial port */
		//return 0;
//}
/*
void send (std::string input)
{
			unsigned char checksum = 0; // could be an int if preferred
			//std::string stra = "P=" + msg; 
			std::cout << "string is:" << input << std::endl;

			int SizeOfArray = input.size();
			std::cout << "length is:" << SizeOfArray << std::endl;
			for(int x = 0; x < SizeOfArray; x++)
			{
      			checksum += input[x]%256;
	  			printf("current %d CRC for MyArray is: %d\n",x, checksum);
			}

			printf("size of myArray is %d Checksum for MyArray is: %d\n",SizeOfArray, checksum);
			
			//sprintf(crc,"%x", checksum);
			std::stringstream ss;
			ss << checksum;
			std::string crc = ss.str();
			
			std::string message = "$" + input +crc + "\r\n";
			std::cout << "string is:" << message << std::endl;
			unsigned char write_buf[message.size()];
			for (int i = 0 ; i <sizeof(write_buf); i++ )
			{
					write_buf[i] = message.at(i);
			}
			int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */
			//bytes_written = write(fd,write_buf,sizeof(write_buf));   // use write() to send data to port 
			//tcdrain(fd);
			//printf("\n  %s written to ttyUSB0",write_buf);
			//printf("\n  %d Bytes written to ttyUSB0", bytes_written);
			//printf("\n +----------------------------------+\n\n");
		
//} 
#include <iostream>
#include "serial.cpp"

using namespace std;
using namespace boost;
int main(int argc, char* argv[])
{
    try {

        Serial serial("/dev/ttyUSB0",2400);

        serial.writeString("Hello world\n");

        cout<<"Received : "<<serial.readLine()<<" : end"<<endl;

    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
}