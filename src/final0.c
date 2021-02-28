#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <signal.h>


//procDescs

struct procDesc
	{
		int id;
		int duration;
		int priority;
	} ; 

struct procDesc *B; 


	
//NonInteractiveProcessAdministrator - NIPA

struct procDesc * NIPA()
{
	
	int i, P=0, N=0, sleep_t=0, flag;
	static struct procDesc buffer[50];
	
	printf("NIPA start\n");
	printf("\nbuffer: {\n");
	
	while (1) {
		sleep_t=rand() %10 +1; 
		sleep(sleep_t);
		N = rand() %10 +1;
		if (flag==1) break;   //break loop when 50 procDescs completed
		for (i=0; i<N; i++) {
			if (P+i>49) {
				flag=1;
				 break; }
		buffer[P +i].id=P +i; 
		buffer[P +i].duration = rand() %26 + 5;
		buffer[P +i].priority = rand() %5 +1;
		
		printf ("[ proc %d, dur %d, pr %d ]\n", buffer[P+i].id, buffer[P+i].duration, buffer[P+i].priority); 
		
				
							}
		P = P + N;
				}
	printf("}\n");
	printf("\nNIPA end\n\n");	
	return buffer; //return procDesc pointer

}


// inputProcessList

typedef struct inputProcessList
	{
	struct procDesc *C;
	struct inputProcessList *next;
	} ipr_t;
	
	ipr_t  *head[5] ={NULL};	
	
	
//TerminatedProcessList

typedef struct terminatedProcessList
	{
	struct procDesc *D;
	struct terminatedProcessList *next
	} tpl_t;

	tpl_t *headT={NULL};


//PrioritySchedulerFIFO
tpl_t *PSFIFO (struct procDesc *B)
{
	B+=49;
	 for (int i=0; i<50; i++) {  //Εισαγωγή των procDesc σε λίστα ανάλογα με το priority
		 switch (B->priority) {
			 
		case 1 :
			insertFirst (B, 0);
			break;
			
		case 2: 
			insertFirst (B, 1);
			break;
			
		case 3: 
			insertFirst (B, 2);
			break;
			
		case 4: 
			insertFirst (B, 3);
			break;
			
		case 5: ;
			insertFirst (B, 4);
			break;
			
		
	}
		--B;
	}
	
	printf("\ninputProcessLists\n\n");  //Εμφάνιση των λιστών όπως διαμορφώθηκαν
	for(int i=0; i<5; i++)
		printList(i);
	
	printf("\ntestProcess EXEC\n\n"); // Για κάθε λίστα δημιουργία και εκτέλεση των διεργασιών testProc
	for (int i=0; i<5; i++)
		create_testProc ( i);
	
	return headT;
	
}


// main

int main(int argc, char **argv)
{ 
	B=NIPA();

	tpl_t *T;	
	T=PSFIFO(B);
	
	printList_term();	//εμφάνιση της λίστας τερματισμού
	
	
	return 0;
}



//ProcessLists Functions


//insert link at the first location

void insertFirst (struct procDesc *C, int n) { 
	ipr_t *link = (ipr_t *) malloc (sizeof ( ipr_t));
	
			
	link -> C = C;
	link -> next = head[n]; 
	head[n] = link; 
	}
	

void insertFirst_term (struct procDesc *D) { 
	tpl_t *link = (tpl_t *) malloc (sizeof ( tpl_t));	
				
	link -> D = D;
	link -> next = headT; 
	headT= link; 
	}


//display the lists

void printList(int n) {
   ipr_t *ptr = head[n];
   printf("\nList Pr %d: \n[ ", n+1);
	
   while(ptr != NULL) {
      printf("(Proc: id %d, dur %d, pr %d) \n ", ptr-> C->id, ptr-> C->duration, ptr-> C-> priority);
      ptr = ptr->next;
      
   }
	
   printf(" ]\n");
}

void printList_term() {
   tpl_t *ptr = headT;
   printf("\nList Term: \n[ ");
	
   while(ptr != NULL) {
      printf("(Proc: id %d, dur %d, pr %d) \n", ptr-> D-> id, ptr->D->duration, ptr-> D-> priority);
      ptr = ptr->next;
      
   }
	
   printf(" ]");
   printf("\n");
}

//Create and execute testProc for inputProcessList

void create_testProc(int n) {
	
	ipr_t *ptr = head[n];
	
   while(ptr != NULL) {
	   char str[2][3]; 
		int aint[3]={ ptr-> C->id, ptr-> C->duration, ptr-> C-> priority};
		
		for (int i=0; i<3; i++) 
		sprintf(str[i], "%d", aint[i]);  //int to char, κατάλληλο για παράμετρος της execve

		char *pv[] = {str[0], str[1], str[2], NULL};
		
		int spv1=0, spv2=0;
		int which;
		pid_t child_pid=fork();  //create child process
		
		if (child_pid ==0){
		spv1=setpriority (which, child_pid, ptr->C->priority); //set real system priority
		execve("./testProc", pv, NULL); //αντικατάσταση του προγράμματος εκτέλεσης της child process
		perror("execve"); /* execve() only returns on error */
		exit(EXIT_FAILURE);
		
		}
		else if (child_pid >0) { 
			int returnStatus;    
			wait(&returnStatus);	//parent waits for child to terminate					
		}
	
		insertFirst_term (ptr->C);
		ptr = ptr->next;	
		
	}
}
