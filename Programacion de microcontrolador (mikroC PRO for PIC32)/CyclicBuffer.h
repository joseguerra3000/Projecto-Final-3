/*
 * File         : CyclicBuffer.c
 * Project      : Cyclic Buffer Library
 * Revision History:
 *                 2017/06/15:
 *                         - initial release
 *
 * Author       : José Guerra Carmenate 
 * 
 * Description  : This library provides you a FIFO-Buffer struct and a comfortable set of routines 
 *        to work with this Buffers
 * Routines: 
 *                        - Buffer_Init
 *                        - Buffer_Data_Ready
 *                        - Buffer_GetData
 *                        - Buffer_GetAllData
 *                        - Buffer_PushData
 *                        - __Buffer_Next_index
 */
#ifndef __LibCyclicBuffer
#define __LibCyclicBuffer
 /*********************
  *   Buffer Struct   *
  *********************/
typedef struct CyclicBuffer{
        unsigned int max_size, // Maximun Capacity
                front,           // index of data on the top of the buffer
                back,           // index of the last data in the buffer
                data_count;// quantity of data in the buffer
        unsigned char *buff;
} Buffer;

 /*************************************************************
  * Prototype: 
  *                void Buffer_Init( Buffer *buffer, unsigned char *array, int max_size )
  * Description:
  *                                   Initilaize the Buffer 'buffer'
  * Parameters:
  *     - buffer: Buffer to be initialized
  *                - array : Global Array used for the buffer
  * Returns:
  *         nothing
  * Example:
  *                // Initialize the 'Buff1' Buffer
  *                Buffer_Init( &Buff1, *buff_arr, 256 );
  *************************************************************/
void Buffer_Init( Buffer *buffer, unsigned char *array, unsigned int max_size );

 /*************************************************************
  * Prototype: 
  *                int Buffer_Data_Ready( Buffer *buff )
  * Description:
  *                                   get the quantity of data on 'buff'.
  * Parameters:
  *     - buff: buffer
  * Returns:
  *         the quantity of data on 'buff'.
  * Example:
  *                // Get the quantity of data ready to be read from Buff1
  *                int sz = Buffer_Data_Ready( &Buff1 );
  *************************************************************/
int Buffer_Data_Ready( Buffer *buffer );

 /*************************************************************
  * Prototype: 
  *                unsigned char Buffer_GetData( Buffer *buff )
  * Description:
  *                                   get the data on the top of 'buff' and erase it.
  * Parameters:
  *     - buff: buffer
  * Returns:
  *         the data on the top of 'buff' 
  * Example:
  *                // get the data on the top of Buff1
  *                unsigned char sz = Buffer_GetData( &Buff1 );
  *************************************************************/
unsigned char Buffer_GetData( Buffer *buffer );

 /*************************************************************
  * Prototype: 
  *                int Buffer_GetAllData( Buffer *buff, unsigned char *data )
  * Description:
  *                                   put all the data on the 'buff' in the 'data' array and erase it.
  * Parameters:
  *     - buff: buffer
  *         - data: 
  * Returns:
  *         the quantity of bytes stored on 'data'.
  * Example:
  *                // get all the data on Buff1 and put it in 'data' array
  *                int sz = Buffer_GetAllData( &Buff1, data );
  *************************************************************/
int Buffer_GetAllData( Buffer *buffer, unsigned char *dat );

 /*************************************************************
  * Prototype: 
  *                char Buffer_PushData( Buffer *buff, unsigned char dat )
  * Description:
  *                                   put dat on the 'buff'.
  * Parameters:
  *     - buff: buffer
  *         - dat : byte to be pushed into the buffer
  * Returns:
  *         1 - byte pushed successfully
  *                        0 - Overflow error
  * Example:
  *                //put the data 0x85 on the buffer Buff1
  *                int ok = Buffer_PushData( &Buff1, 0x85 );
  *************************************************************/
int Buffer_PushData( Buffer *buffer, unsigned char dat );

 /*************************************************************
  * Prototype: 
  *                void __Buffer_PopFront( Buffer *buff )
  * Description:
  *                                   "Erace" the next element on the Buffer
  * Parameters:
  *     - buff: buffer
  * Returns:
  *         - Nothing
  * NOTA:
  *                - This routine is only for internal use
  * Example:
  *                             __Buffer_PopFront( &Buff1 );
  *************************************************************/
void __Buffer_PopFront( Buffer *buffer );


#endif