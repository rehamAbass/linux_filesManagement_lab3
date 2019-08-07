// lab3  - tar1

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
int input1, input2, output;
int read1=1,read2=1, wt;
char buffer=1,enter='\n',temp1,temp2;
int flag=0;

if (argc != 4){
	printf("\nInvalid parameters.");
	exit(1);
}
/*open file descriptors*/
input1 = open(argv[1], O_RDONLY);
input2 = open(argv[2], O_RDONLY);
output = open(argv[3], O_WRONLY | O_CREAT,0644);		// -rw-r--r--
if (input1 == -1 || input2 == -1 || output == -1){
	printf("\nError opening.");
	exit(1);
}

while(read1>0 || read2>0){		// while there is text to read..

	/*read from first file*/
	if (flag==0 && read1>0){		// if file1 turn and still has text.
		temp1=buffer;
		read1=read(input1,&buffer,1);
		if (temp1=='\n' && read1>0 && buffer!='\n'){	//print enter after line
			wt = write(output,&enter,1);
			temp1=1;
		}
		if (buffer != '\n')					// check if end of line
			wt = write(output,&buffer,1);
		else flag=1;
	}else flag=1;

	/*read from second file*/
	if(flag==1 && read2>0){			// if file2 turn and still has text
		temp2=buffer;
		read2=read(input2,&buffer,1);
		if (temp2=='\n' && read2>0 && buffer!='\n'){	//print enter after line
			wt = write(output,&enter,1);
			temp2=2;
		}
		if (buffer != '\n')					// check if end of line
			wt = write(output,&buffer,1);
		else flag=0;
	}else flag=0;
}

/*close file descriptors*/
close(input1);
close(input2);
close(output);
}

