#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

struct process
{
	char 	name[5];
	int 	size;
	bool 	activ;
	int 	amtPage;
	int 	tabl[100];
};

struct page
{
	int 	virt;
	int 	phus;
	bool    free;
	int 	memory_occ;
	char 	proc_name[5];
};  

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

int main()
{
	page page[100];
	process proc[100];
	int n,i,j,memory,PowTwo,amtPage,menu = 0,amtP = 0,memory_free,req = 0,req_true=0,g;
	char name[5];
	printf("Enter memory size : ");
	memory = ReadValueInt();
	printf("Enter power of two : ");
	PowTwo = ReadValueInt();
	PowTwo = pow(2,PowTwo);
	amtPage	= memory / PowTwo;
	printf("Namber of pages : %d\n",amtPage);
    memory = PowTwo*amtPage;
    memory_free = PowTwo*amtPage;
	for( i = 0 ; i < amtPage ; i++ )
	{
		page[i].proc_name[0] = '-';
		page[i].proc_name[1] = '\0';
		page[i].virt = 0;
		page[i].phus = i;
		page[i].memory_occ = 0;
		page[i].free = true;
	}
	fflush(stdin);
	getchar();
	while( menu != -1 )
	{
		//system("cls");
		printf("----------Menu----------\n");
		printf("- 1. Add process -------\n");
		printf("- 2. Delete proess -----\n");
		printf("- 3. Stop process -------\n");
		printf("- 4. Run process --------\n");
		printf("- 5. Show pages --------\n");
		printf("- 6. Show memory info --\n");
		printf("- 7. Exit --------------\n");
		printf("Enter point menu : ");
		menu = ReadValueInt();
		switch(menu)
		{
			case 1:
			{
				req++;
				printf("Enter process name : ");
				scanf("%s",&proc[amtP].name);
				printf("Enter process memory size : ");
				proc[amtP].size = ReadValueInt();
				if(memory_free < proc[amtP].size || proc[amtP].size < 1)
				{
				    proc[amtP].size < 1 ?  printf("Process size > 0") : printf("Out of memory");
				}
				else
				{
					req_true++;
					if(proc[amtP].size % PowTwo == 0)
					{
						proc[amtP].amtPage = proc[amtP].size / PowTwo;
						i = 0;
						j = 0;
						while( i < proc[amtP].amtPage )
						{
							if (page[j].free)
							{
								strcpy(page[j].proc_name,proc[amtP].name);
								page[j].memory_occ = PowTwo;
								page[j].virt = i;
								page[j].phus = j;
								page[j].free = false;
								memory_free -= PowTwo;
								proc[amtP].tabl[i] = j;
								j++;
								i++;
							}
							else
							{
								j++;
							}
						}
					}
					else
					{
						proc[amtP].amtPage = ( proc[amtP].size / PowTwo ) + 1;
						i = 0;
						j = 0;
						while( i < proc[amtP].amtPage )
						{
							if (page[j].free)
							{
								strcpy(page[j].proc_name,proc[amtP].name);
								page[j].memory_occ = PowTwo;
								page[j].virt = i;
								page[j].phus = j;
								page[j].free = false;
								memory_free -= PowTwo;
								proc[amtP].tabl[i] = j;
								if( i == proc[amtP].amtPage - 1 )
								{
									page[j].memory_occ = proc[amtP].size % PowTwo;
								}
								j++;
								i++;
							}
							else
							{
								j++;
							}
						}
					}
					proc[amtP].activ = true; 
					amtP++;
				printf("\nProcess add\n");
				}
				break;
			}
			case 2:
			{
				printf("Enter process name : ");
				scanf("%s",&name);
				bool check = true;
				for( i = 0 ; i < amtP ; i++)
				{
					if( strcmp( proc[i].name , name ) == 0 )
					{
						check = false;
						if(proc[i].activ)
						{
							for( j = 0 ; j < proc[i].amtPage ; j++ )
							{
								page[proc[i].tabl[j]].proc_name[0] = '-';
								page[proc[i].tabl[j]].proc_name[1] = '\0';
								page[proc[i].tabl[j]].virt = 0;
								page[proc[i].tabl[j]].phus = proc[i].tabl[j];
								page[proc[i].tabl[j]].memory_occ = 0;
								page[proc[i].tabl[j]].free = true;
							}
							memory_free += PowTwo * proc[i].amtPage;
						}
						printf("Process %s delete\n",proc[i].name);
						for( j = i ; j < amtP ; j++ )
						{
							proc[j] = proc[j+1];
						}
						amtP--;
						i--;
					}
				}
				if(check){
					printf("\nProcess Not Found\n");	
				}
				break;
			}
			case 3:
			{
				printf("Enter process name : ");
				scanf("%s",&name);
				bool check = true;
				for( i = 0 ; i < amtP ; i++)
				{
					if( strcmp( proc[i].name , name ) == 0 )
					{
						check = false;
						for( j = 0 ; j < proc[i].amtPage ; j++ )
						{
							page[proc[i].tabl[j]].proc_name[0] = '-';
							page[proc[i].tabl[j]].proc_name[1] = '\0';
							page[proc[i].tabl[j]].virt = 0;
							page[proc[i].tabl[j]].phus = proc[i].tabl[j];
							page[proc[i].tabl[j]].memory_occ = 0;
							page[proc[i].tabl[j]].free = true;
						}
						memory_free += PowTwo * proc[i].amtPage;
						proc[i].activ = false;
						printf("Process %s stopped\n",proc[i].name);
					}
				}
				if(check){
					printf("\nProcess Not Found\n");	
				}
				break;
			}
			case 4:
			{
				bool ch = true;
				printf("Process stopped :\n");
				for( g = 0 ; g < amtP ; g++)
				{
					if(!proc[g].activ){
						printf("%s\n",proc[g].name);
						ch=false;
					}	
				}
				if(ch) printf("Not stopped process");
				printf("Enter process name : ");
				scanf("%s",&name);
				bool check = true;
				for( g = 0 ; g < amtP ; g++)
				{
					if( strcmp( proc[g].name , name ) == 0 && !proc[g].activ )
					{
						if(memory_free < proc[g].size)
						{
							printf("Out of memory");
						}
						else
						{
							check = false;
							printf("Run process %s\n",proc[g].name);
							if(proc[g].size % PowTwo == 0)
							{
								i = 0;
								j = 0;
								while( i < proc[g].amtPage )
								{
									if (page[j].free)
									{
										strcpy(page[j].proc_name,proc[g].name);
										page[j].memory_occ = PowTwo;
										page[j].virt = i;
										page[j].phus = j;
										page[j].free = false;
										memory_free -= PowTwo;
										proc[g].tabl[i] = j;
										j++;
										i++;
									}
									else
									{
										j++;
									}
								}
							}
							else
							{
								i = 0;
								j = 0;
								while( i < proc[g].amtPage )
								{
									if (page[j].free)
									{
										strcpy(page[j].proc_name,proc[g].name);
										page[j].memory_occ = PowTwo;
										page[j].virt = i;
										page[j].phus = j;
										page[j].free = false;
										memory_free -= PowTwo;
										proc[g].tabl[i] = j;
										if( i == proc[g].amtPage - 1 )
										{
											page[j].memory_occ = proc[g].size % PowTwo;
										}
										j++;
										i++;
									}
									else
									{
										j++;
									}
								}
							}
							proc[g].activ = true; 
						}
					}
				}
				if(check){
					printf("\nProcess Not Found\n");	
				}
				break;
			}	
			case 5:
			{
				printf("| process name | page virt | page phys | occuped/memory |\n\n");
				for( i = 0 ; i < amtPage ; i++ )
				{
					printf("| %12s |  %7d  |  %7d  |    %4d/%-4d   |\n",page[i].proc_name,page[i].virt,page[i].phus,page[i].memory_occ,PowTwo);
				}
				break;
			}
			case 6:
			{
				printf("Full memory : %d\n",memory);
				float m_p = memory == 0 ? 0 : (memory_free/(float)memory)*100;
				printf("Free memory / percent : %d / %.2f \n",memory_free,m_p);
				printf("Amount proess : %d\n",amtP);
				g = 0;
				for( i = 0 ; i < amtP ; i++ )
				{
					if( proc[i].activ )
					{
						g++;
					}
				}
				if( amtP ){printf("Amount activ process / percent : %d / %.2f \n",g,(g/(float)amtP)*100);}else{printf("Amount activ process / percent : 0 / 0.00 \n");}
				if( req ){printf("Amount request , approved request / percent : %d , %d / %.2f \n",req,req_true,(req_true/(float)req)*100);}else{printf("Amount request , approved request / percent : 0 , 0 / 0.00 \n");}
				break;
			}
			case 7:
			{
				printf("Finsh work\n");
				menu = -1;
				break;
			}	
			default:
			{
				printf("Not correct point\n");
				break;
			}
		}
		fflush(stdin);
		//printf("\nPress Enter\n");
		//getchar();
	}		
		
} 
