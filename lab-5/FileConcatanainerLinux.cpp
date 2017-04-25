#include "FileConcatanainerLinux.h"

void concateFiles(vector<string> inputFiles, string outputFile)
{
	int fd, ret; 
  	struct aiocb *my_aiocb;
  	BUFFER = (char*)malloc(BUFSIZE);
	
	// open output file
	OUTPUT_FILE_DESCRIPTOR = open(outputFile.c_str(), O_WRONLY | O_APPEND);
    	if(fd < 0) {
		printf("Error! Cannot open output file...\n");
    	}

	// read input files
	for(int i = 0; i < inputFiles.size(); i++){
  		fd = open( inputFiles[i].c_str(), O_RDONLY );
  		if (fd < 0) {
		      printf("Error! Cannot open input file [%d]...\n", i);
		}
		my_aiocb = (struct aiocb*)malloc(sizeof(struct aiocb));
			
  		/* Zero out the aiocb structure (recommended) */
  		bzero( (char *)my_aiocb, sizeof(struct aiocb) );

  		/* Allocate a data buffer for the aiocb request */
  		my_aiocb->aio_buf = malloc(BUFSIZE+1);
  		if (!my_aiocb->aio_buf) {
		      printf("Error! Cannot allocate memory for aio_buf...\n");
		}

  		/* Initialize the necessary fields in the aiocb */
  		my_aiocb->aio_fildes = fd;
  		my_aiocb->aio_nbytes = BUFSIZE;
  		my_aiocb->aio_offset = 0;
		
		// link the AIO request with a thread callback
		my_aiocb->aio_sigevent.sigev_notify = SIGEV_THREAD;
		my_aiocb->aio_sigevent.sigev_notify_function = completeReadingFile;
		my_aiocb->aio_sigevent.sigev_notify_attributes = NULL;
		my_aiocb->aio_sigevent.sigev_value.sival_ptr = my_aiocb;

		// read from input file
  		ret = aio_read( my_aiocb );
  		if (ret < 0) {
		      printf("Error! Complete aio_read() ...\n");
		}

  		while ( aio_error( my_aiocb ) == EINPROGRESS ) ;
		
  		if ((ret = aio_return( my_aiocb )) > 0) {
  		  /* got ret bytes on the read */
  		    printf("Read success!\n");
  		    strcpy(BUFFER, (char*)my_aiocb->aio_buf);
  		} else {
  		  /* read failed, consult errno */
		    printf("Read failed!\n");
  		}
  	
	}

}

void completeReadingFile(sigval_t sigval)
{
	printf("Writer thread is activated\n");
	sleep(1);
	struct aiocb *request;
	request = (struct aiocb*)sigval.sival_ptr;
	
	// checks if the request complete successfully
	if(aio_error(request) == 0){
		struct aiocb my_aiocb;
		
		/* Zero out the aiocb structure (recommended) */
  		bzero( (char *)&my_aiocb, sizeof(struct aiocb) );
		
		my_aiocb.aio_fildes = OUTPUT_FILE_DESCRIPTOR;
		my_aiocb.aio_buf = request->aio_buf;
		my_aiocb.aio_nbytes = strlen((char*)request->aio_buf);

		if (aio_write( &my_aiocb) < 0) {
		    printf("Error! Cannot write to output file...\n");
		}

		while ( aio_error( &my_aiocb ) == EINPROGRESS ) ;
  
		if (aio_return( &my_aiocb ) > 0) {
		    printf("Write success!\n");
		    //printf("%s", (char*)my_aiocb.aio_buf);
		} else {
		    printf("Write failed!");
		}
	}
}

