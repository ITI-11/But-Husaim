#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Page{
	int memory;
	int free_memory;
	char proc_name[20];
	int appeal;
	bool active;
};

void FirstFilling(Page *pg,int col,int size){	
	for(int i = 0; i < col; i++){
		(pg+i)->memory = size;
		(pg+i)->free_memory = size; 
		(pg+i)->proc_name[0] = '-';
		(pg+i)->proc_name[1] = ' ';
		(pg+i)->proc_name[2] = '\0';
		(pg+i)->appeal = 0;		
		(pg+i)->active = false;		
	}	
}





bool CheckForNamb(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		if(string[i] < 48 || string[i] > 57) return false;
	}
	return true;
} 

int ReadValueInt()
{
	bool right = true;
	char string[255];
	while(right)
	{
		scanf("%s",string);
		if(strlen(string)<10 && CheckForNamb(string)) 
			right = false;
		else
			printf("Enter number < 147483647 !\n");
	}
	return atoi(string);
}

int SuchFree(Page *p,int col){
	int i = -1;
	bool such = true;
	while(i < col && such){
		i++;
		if(!((p+i)->active)) such = false;	
	}
	return(i);
}

bool In(int * m,int col,int z){
	bool r = true;
	for(int i = 0 ; i < col; i++){
		//printf("%d\n",m[i]);
		if(m[i] == z) r = false;
	}
	//printf("\n");
	return(r);
}

int Reb(Page *p,int col,int size){
	int c=0;
	for(int i = 0; i < col; i++){
		if((p+i)->free_memory == size){
	 		(p+i)->active = false;	
	 		c++;
	 	}	
	}		
	return(c);
}

int main(){
	Page pag[100];
	int  max_appeal,r,p,menu = 1,memory = 0,free_memory,max_page,amt_page = 0,free_page,appeal = 0,successful_appeal = 0,pr_size,page[100],amt_mas_page,shud_page,max_appel,pr_appeal;
	char pr_name[20];
	bool add_page,tmp;
	for(int b = 0 ; b < 100; b++ ){
		page[b] = 0;
	}
	printf("Enter amount for memory : ");
	while (memory == 0){
		printf("col > 0\n");
		memory = ReadValueInt();			
	}
	free_memory = memory;
	printf("Enter amount for page : ");
	while (amt_page == 0){
		printf("col > 1\n");
		amt_page = ReadValueInt();			
	}
	free_page = amt_page;
	FirstFilling(pag,amt_page,memory/amt_page);
	printf("Enter max amount of pages for process : ");
	max_page = ReadValueInt();
	printf("Enter max appeal of pages for process : ");
	max_appeal = ReadValueInt();
	while(menu != 5){
		printf("<========================================>\n");
		printf("<==================MENU==================>\n");
		printf("<========================================>\n");
		printf("<-1-Add process-------------------------->\n");
		printf("<-2-Delete process----------------------->\n");
		printf("<-3-Info--------------------------------->\n");
		printf("<-4-Periodic appeal---------------------->\n");
		printf("<-5-Exit--------------------------------->\n");
		printf("Enter point menu : ");
		menu = ReadValueInt();
		switch(menu){
			case 1:{
				printf("Enter name of process : \n");
				scanf("%s",&pr_name);
				printf("Enter size of process : \n");
				pr_size = ReadValueInt();
				if(pr_size > 0){
					amt_mas_page = max_page;
					free_page = Reb(pag,amt_page,memory/amt_page);
					for(int i = 0; i < amt_mas_page; i++){
						if(SuchFree(pag,amt_page) < amt_page){
							page[i] = SuchFree(pag,amt_page);
							pag[SuchFree(pag,amt_page)].active = true ;
						}else{
							p = rand() % amt_page;
							if(In(page,amt_mas_page,p)){page[i] = p;}else{i--;}
						} 	
						//printf("Form local pages : page[%d] = %d\n",i,page[i]);
					}	
					r = 0;
					pr_appeal = 0;
					while(pr_size != 0){
						//printf("1\n");
						appeal++;
						//printf("Wark with page : page[%d] = %d\n",r,page[r]);
						if(pr_size > (memory / amt_page)){
							pag[page[r]].memory = (memory / amt_page);
							pag[page[r]].free_memory = 0;
							pr_size -= (memory / amt_page);
						}else{
							pag[page[r]].memory = pr_size;
							pag[page[r]].free_memory = (memory / amt_page) - pr_size;
							pr_size = 0;	
						}
						strcpy(pag[page[r]].proc_name,pr_name);
						pag[page[r]].appeal++;
						pr_appeal++;
						if(pr_appeal >= max_appeal){
							//printf("Add page\n");
							add_page = true;
							pr_appeal = 0;
							amt_mas_page++;
							while(add_page && amt_mas_page <= amt_page){
								//printf("2");
								if(SuchFree(pag,amt_page) < amt_page){p = SuchFree(pag,amt_page);pag[SuchFree(pag,amt_page)].active = true;}else{p = rand() % amt_page;};
								//printf("Form new page = %d, amt page = %d",p,amt_mas_page);
								if(In(page,amt_mas_page,p) || amt_mas_page == amt_page){page[amt_mas_page-1] = p; add_page = false;}
								//printf("\n");
							}
						}
						r++;
						if(r >= amt_mas_page) r = 0;
						
					}
					printf("Process added\n");
				}else{
					printf("Size > 0\n");
				}
				break;
			}	
			case 2:{
				printf("Enter delete name of process : \n");
				scanf("%s",&pr_name);
				tmp = false;	
				for(int i = 0 ; i < amt_page ; i++)
				{
					if(!strcmp(pag[i].proc_name,pr_name)){
						pag[i].memory = memory / amt_page;
						pag[i].free_memory = memory / amt_page; 
						pag[i].proc_name[0] = '-';
						pag[i].proc_name[1] = ' ';
						pag[i].proc_name[2] = '\0';
						pag[i].appeal = 0;		
						pag[i].active = false;	
						tmp = true	;
					}
				}		
				if(tmp){
					printf("Process %s delete!\n",pr_name);
				}else{
					printf("This process not found!\n");
				}
				break;
			}
			case 3:{
				printf("Memory : %d\n",memory);
				printf("Amount page : %d\n",amt_page);
				printf("Appeal : %d\n",appeal);
				printf("|-----|--------------------|----------|----------|\n");
				printf("|  N  |  Name of process   | Memory/%% |  Appeal  |\n");
				printf("|_____|____________________|__________|__________|\n");
				printf("|-----|--------------------|----------|----------|\n");
				for(int i = 0; i < amt_page; i++){	
					printf("| %3d |%20s|%4d/%3.0f%% |  %6d  |\n",i+1,pag[i].proc_name,pag[i].memory,(pag[i].free_memory/(float)(memory / amt_page))*100,pag[i].appeal);
				}
				printf("|_____|____________________|__________|__________|\n");
				break;
			}	
			case 4:{
				printf("Enter amount appeal : ");
				p = ReadValueInt();
				for(int i = 0; i < p;i++){
					r = rand() % amt_page;
					pag[r].appeal++;
					appeal++;
					printf("Appeal to page N = %d\n",r);
				}
				break;
			}
			case 5:{
				printf("Exit...\n");
				break;
			}
			default:{
				printf("Error : Not right argument of menu!\n");
				break;
			}
		}
	}
		
	return 0;
}





























