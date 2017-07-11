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
#include "CyclicBuffer.h"
void Buffer_Init( Buffer *buffer, unsigned char *array, unsigned int max_size ){
        (*buffer).buff = array;
        (*buffer).max_size = max_size;
        (*buffer).front = (*buffer).back = (*buffer).data_count = 0;
}

int Buffer_Data_Ready( Buffer *buffer ){
        return (*buffer).data_count;
}

unsigned char Buffer_GetData( Buffer *buffer ){
        unsigned char res;
        if( (*buffer).data_count == 0 ) return 0;
        res = (*buffer).buff[ (*Buffer).front ];
        __Buffer_PopFront( buffer );
        return res;
}

int Buffer_GetAllData( Buffer *buffer, unsigned char *out ){
        int cnt = 0;
        while( Buffer_Data_Ready( buffer ) ){
                out[cnt++] = (*buffer).buff[ (*buffer).front ];
                __Buffer_PopFront( buffer );
        }
        out[cnt] = '\0';
        (*buffer).data_count = 0;
        return cnt;
}

int Buffer_PushData( Buffer *buffer, unsigned char dat ){
        if( (*buffer).data_count == (*buffer).max_size+1 )
                return 0;
        (*buffer).buff[ (*buffer).back ] = dat;
        (*buffer).back++;
        (*buffer).data_count++;
        if( (*buffer).back == (*buffer).max_size )
                (*buffer).back = 0;
        return ( (*buffer).front != (*buffer).back);
}

void __Buffer_PopFront( Buffer *buffer ){
        (*buffer).front++;
        (*buffer).data_count--;
        if( (*buffer).front == (*buffer).max_size )
                (*buffer).front = 0;
}