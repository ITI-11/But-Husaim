#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File{
	char name[20];
	bool type; // 0 - file 1 - folder
	char info[255];
	int pos;
	int per;
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

bool CheckForEr(char *string)
{	char h[255] = "HOME";
	for(int i = 0; i < strlen(string); i++)
	{
		if(string[i] == '\\' or string[i] == '/' or string[i] == '.' or string[i] == ',' or !strcmp(string,h)) return false;
	}
	return true;
} 

void ReadValueName(char *string)
{
	bool right = true;
	while(right)
	{
		fflush(stdin);
	    gets(string);
		if(strlen(string)>0 && strlen(string)<20 && CheckForEr(string)) 
			right = false;
		else{
			printf("Enter correct name! \n");	
			string[19] = '\0';
			string[0] = '\0';		
		}
	}
}

bool CheckName(File *d,File der,int *col,char *n){
	for(int i = 0; i < *col; i++){
		if(!strcmp((d+i)->name,n) && (d+i)->per == der.pos) return false;
	}
	return true;
}

void CreateFolder(File *d,File der,int *col){
	char name[20];
	printf("Enter folder name : ");
	ReadValueName(name);
	while(!CheckName(d,der,col,name)){
		printf("Name already in use. Please choose another one: ");
		ReadValueName(name);
	}
	strcpy((d+*col)->name,name);
	(d+*col)->pos = *col;
	(d+*col)->per = der.pos;
	(d+*col)->type = 1;
	(d+*col)->info[0] = '\0';
	(*col)++;
	printf("Folder create!\n");
}

void CreateFile(File *d,File der,int *col){
	char name[20],str[20]="1",n[20]="n",y[20]="y";
	printf("Enter file name : ");
	ReadValueName(name);
	while(!CheckName(d,der,col,name)){
		printf("Name already in use. Please choose another one: ");
		ReadValueName(name);
	}
	strcpy((d+*col)->name,name);
	(d+*col)->pos = *col;
	(d+*col)->per = der.pos;
	(d+*col)->type = 0;
	printf("Want to fill file(y/n) : ");
	while(strcmp(str,n) && strcmp(str,y)){
		scanf("%s",&str);
		if(!(!strcmp(str,n) || !strcmp(str,y))) printf("Enter correct answer!\n");
	}
	if(!strcmp(str,y)){
		printf("Enter: \n");
		scanf("%s",(d+*col)->info);
	}else{
		(d+*col)->info[0]='\0';
	}
	(*col)++;
	printf("File create!\n");
}

void ChengeDer(File *d,File *der,int *col){
	char name[20];
	printf("Enter folder name : ");
	ReadValueName(name);
	for(int i = 0; i < *col; i++){
		if(!strcmp((d+i)->name,name) && der->pos == (d+i)->per && (d+i)->type == 1){
			printf("Open folder\n");
			*der = *(d+i);
			return;
		}
	}	
	printf("Folder not found\n");
}

void OpenFile(File *d,File der,int *col,float *m){
	char name[20],str[20]="1",n[20]="n",y[20]="y";
	bool such = false;
	printf("Enter file name : ");
	ReadValueName(name);
	for(int i = 0; i < *col; i++){
		if(!strcmp((d+i)->name,name) && der.pos == (d+i)->per){
			such = true;
			printf("Open file :\n");
			printf("%s\n",(d+i)->info);
			printf("Want to change file(y/n) : ");
			while(strcmp(str,n) && strcmp(str,y)){
				scanf("%s",&str);
				if(!(!strcmp(str,n) || !strcmp(str,y))) printf("Enter correct answer!\n");
			}
			if(!strcmp(str,y)){
				(*m) += strlen((d+*col)->info);
				printf("Enter: \n");
				scanf("%s",(d+*col)->info);
				(*m) -= strlen((d+*col)->info);
			}
		}
	}	
	if(!such) printf("File not found\n");
}

void Find(File *d,int *col){
	char name[20];
	File tmp;
	bool such = false;
	printf("Enter file or folder name : ");	
	ReadValueName(name);
	for(int i = 0; i < *col; i++){
		if(!strcmp((d+i)->name,name)){
			such = true;
			tmp = *(d+i);
			while(tmp.pos != 0){
				printf("%s\\",tmp.name);
				tmp = *(d + tmp.per);
			}
			printf("HOME\n");
		}
	}	
	if(!such) printf("File or Folder not found\n");	
}

void FindD(File *d,File dd,int *col){
	File tmp;
	for(int i = 0; i < *col; i++){
		if(!strcmp((d+i)->name,dd.name) && dd.pos == (d+i)->per){
			tmp = *(d+i);
			while(tmp.pos != 0){
				printf("%s\\",tmp.name);
				tmp = *(d + tmp.per);
			}
			printf("HOME\n");
		}
	}	
}





void delF(File *d,File dd,int *col,float *m){
	for(int i = 0; i < *col; i++){
		if(dd.pos == (d+i)->per){
			if((d+i)->type == 0){
				printf("Delete file : ");
				FindD(d,*(d+i),col);
				(*m) += strlen((d+i)->info);
				for(int j=i;j<(*col)-1;j++){
					*(d+j) = *(d+j+1);
					(d+j)->pos--;
					if(i<(d+j)->per)
					{
						(d+j)->per--;
					}
				}
				(*col)--;
				i--;
			}else{
				printf("Delete folder : ");
				FindD(d,*(d+i),col);
				delF(d,*(d+i),col,m);
				for(int j=i;j<(*col)-1;j++){
					*(d+j) = *(d+j+1);
					(d+j)->pos--;
					if(i<(d+j)->per)
					{
						(d+j)->per--;
					}
				}
				(*col)--;
				i--;
			}
		}
	}
}

bool OpenCheck(File *d,File der,int *col,char *n){
	for(int i = 0; i < *col;i++){
		if(!strcmp((d+i)->name,n) && der.pos >= (d+i)->pos) return false;
	}
	return true;
}

int ProvInfoL(char *n){
	int test = 0;
	for(int i = 0; i < strlen(n); i++){
		if( *(n+i) != ' ' ){
			test++;	
		}
	}
	return test;
}

int Load(File *d,float *m){
	FILE *f = fopen("hdd.txt","rt+");
	int i = 0,tmp;
	while(!feof(f)){
		fseek(f,(i*284)+1,0);
		fgets((d+i)->name,20,f);
		(d+i)->name[20]='\0';
		fseek(f,(i*284)+20,0);
		fscanf(f,"%d",&tmp);
		(d+i)->type = tmp;
		fseek(f,(i*284)+25,0);
		fgets((d+i)->info,254,f);
		(d+i)->info[255]='\0';
		if(ProvInfoL((d+i)->info)){
			(*m) -= ProvInfoL((d+i)->info);
		}
		fseek(f,(i*284)+278,0);
		fscanf(f,"%d",&(d+i)->pos);
		fseek(f,(i*284)+281,0);
		fscanf(f,"%d",&(d+i)->per);
		printf("Load : ");
		printf("%20s name ",(d+i)->name);
		printf("%d type ",(d+i)->type);
		printf("%255s info ",(d+i)->info);
		printf("%d %d pos per \n",(d+i)->pos,(d+i)->per);
		i++;
	}
	fclose(f);
	printf("All inform load\n");
	return(i-1);
}

void Save(File *d,int *col){
	FILE *f = fopen("hdd.txt","wt+");
	for(int i= 0; i<*col;i++){
		fprintf(f,"%20s %d %255s %d %d\n",(d+i)->name,(d+i)->type,(d+i)->info,(d+i)->pos,(d+i)->per);
	}
	fclose(f);
	printf("All inform save for hdd\n");
}


void Del(File *d,File der,int *col,float *m){
	char name[20],h[20] = "HOME";
	int i,j;
	bool such = false;
	printf("Enter file or folder name : ");	
	ReadValueName(name);
	if(strcmp(name,h) && OpenCheck(d,der,col,name)){
		for(i = 0; i < *col; i++){
			if(!strcmp((d+i)->name,name) && der.pos == (d+i)->per){
				such = true;
				if((d+i)->type == 0){
					(*m) += strlen((d+i)->info);
					printf("Delete file : ");
					FindD(d,*(d+i),col);
					for(j=i;j<(*col)-1;j++){
						*(d+j) = *(d+j+1);
						(d+j)->pos--;
						if(i<(d+j)->per)
						{
							(d+j)->per--;
						}
					}
					(*col)--;
					i--;
				}else{
					printf("Delete folder : ");
					FindD(d,*(d+i),col);
					delF(d,*(d+i),col,m);
					for(j=i;j<(*col)-1;j++){
						*(d+j) = *(d+j+1);
						(d+j)->pos--;
						if(i<(d+j)->per)
						{
							(d+j)->per--;
						}
					}
					(*col)--;
					i--;
				}
			}
		}
	}else{
		such = true;
		printf("This folder is open!\n");	
	}
	if(!such) printf("File or Folder not found\n");			
}

void ProvName(char *n,int amt){
	bool test = false;
	for(int i = 0; i < strlen(n); i++){
		if( (*(n+i) > 47 && *(n+i)<58) || (*(n+i) > 64 && *(n+i)<91) || (*(n+i) > 96 && *(n+i)<123) ) test = true;
	}
	if(!test){
		printf("File or folder N %d name is broken !\n",amt);
		printf("Create new name...\n");
		*(n+0) = 'N';
		*(n+1) = 'e';
		*(n+2) = 'w';
		*(n+3) = 'N';
		*(n+4) = 'a';
		*(n+5) = 'm';
		*(n+6) = 'e';
		*(n+7) = '\0';
		char tmp[4];
		int code;
		itoa(amt,tmp,10);
		tmp[3] =  '\0';
		strcat(n,tmp);
		printf("New name  :  %s\n",n);
	}
}

bool ProvInfo(char *n){
	bool test = false;
	for(int i = 0; i < strlen(n); i++){
		if( *(n+i) != ' ' ){
			test = true;	
		}
	}
	return test;
}

void NameCorect(File *d,int *col){
	for(int i = 0; i < *col; i++){
		if((d+i)->name[0]==' '){
			while((d+i)->name[0]==' '){
				for(int k = 0; k < 19;k++){
					(d+i)->name[k]=(d+i)->name[k+1];
				}
			} 
		}
		if((d+i)->info[0]==' '){
			while((d+i)->info[0]==' '){
				for(int k = 0; k < 254;k++){
					(d+i)->info[k]=(d+i)->info[k+1];
				}
			} 
		}
	}
}



int ScanDisk(File *d,float *m){
	FILE *f = fopen("hdd.txt","rt+");
	int i = 0,tmp,l;
	while(!feof(f)){
		fseek(f,(i*284)+1,0);
		fgets((d+i)->name,20,f);
		ProvName((d+i)->name,i);
		(d+i)->name[20]='\0';
		fseek(f,(i*284)+20,0);
		fscanf(f,"%d",&tmp);
		(d+i)->type = tmp;
		fseek(f,(i*284)+25,0);
		fgets((d+i)->info,254,f);
		(d+i)->info[255]='\0';
		if(ProvInfoL((d+i)->info)){
			(*m) -= ProvInfoL((d+i)->info);
		}		
		fseek(f,(i*284)+278,0);
		fscanf(f,"%d",&(d+i)->pos);
		if((d+i)->pos != i){
			printf("File or folder location is lost!\n");
			printf("Find location...\n");
			(d+i)->pos = i;
			printf("Location installed\n");
		}
		fseek(f,(i*284)+281,0);
		fscanf(f,"%d",&(d+i)->per);
		if(((d+i)->per > i)){
			printf("The path is lost\n");
			printf("Create path...\n");
			(d+i)->per = 0;
			printf("New path installed   : HOME\n");
		}else{
			if((d+(d+i)->per)->type == 0) {
				printf("This file or folder path in file %s!\n",(d+(d+i)->per)->name);
				printf("Chenge type file %s file have info ( 1 - yes \\ 0 - no ) : %d \\ create new path (1 \\ 2) : ",(d+(d+i)->per)->name,ProvInfo((d+(d+i)->per)->info));
				scanf("%d",&l);
				if(l == 2){
					printf("The path is lost\n");
					printf("Create path...\n");
					(d+i)->per = 0;
					printf("New path installed   : HOME\n");					
				}else{
					printf("Chenge type...\n");
					(d+(d+i)->per)->type = 1;
					(d+(d+i)->per)->info[0] = '\0';
					printf("Type chenge\n");
				}
			}
		}
		printf("Load : ");
		printf("%20s name ",(d+i)->name);
		printf("%d type ",(d+i)->type);
		printf("%255s info ",(d+i)->info);
		printf("%d %d pos per \n",(d+i)->pos,(d+i)->per);
		i++;
	}
	fclose(f);
	printf("All inform load\n");
	return(i-1);	
}



int main(){
	File disk[100],derect;
	strcpy(disk[0].name,"HOME              \0");
	disk[0].type = 1;
	disk[0].pos = 0;
	disk[0].per = 0;
	disk[0].info[0] = '\0';
	derect = disk[0]; 
	int menu=0,i,sizeKlast,col=1;
	float memory;
	printf("Enter size of cluster : ");
	sizeKlast = ReadValueInt();
	memory = sizeKlast * 4.096;	
	while(menu != 11){
		NameCorect(disk,&col);
		strcpy(disk[0].name,"HOME              \0");
		printf("<========================================>\n");
		printf("<= Memory                       %-8.2f=>\n",memory);
		printf("<========================================>\n");
		printf("<========================================>\n");
		printf("<=                %-20s  =>\n",derect.name);
		printf("<========================================>\n");
		for(i = 0; i<col;i++){
			if(derect.pos == disk[i].per && i!=0) 
				if(disk[i].type == 0) printf("<-%-32s(file)->\n",disk[i].name);
					else printf("<-%-30s(folder)->\n",disk[i].name);
		}
		printf("<========================================>\n");
		printf("<==================MENU==================>\n");
		printf("<========================================>\n");
		printf("<-1-Create folder------------------------>\n");
		printf("<-2-Open folder-------------------------->\n");
		printf("<-3-Create file-------------------------->\n");
		printf("<-4-Open file---------------------------->\n");
		printf("<-5-Find file or folder------------------>\n");
		printf("<-6-Delete file or folder---------------->\n");
		printf("<-7-Back--------------------------------->\n");
		printf("<-8-Load hdd----------------------------->\n");
		printf("<-9-Save hdd----------------------------->\n");
		printf("<-10-CHKDSK------------------------------>\n");
		printf("<-11-Exit-------------------------------->\n");
		printf("Enter menu point : ");
		menu = ReadValueInt();
		switch(menu){
			case 1:{
				CreateFolder(disk,derect,&col);
				printf("%d",col);
				break;
			}
			case 2:{
				ChengeDer(disk,&derect,&col);
				break;
			}
			case 3:{
				CreateFile(disk,derect,&col);
				if(memory - strlen(disk[col-1].info) < 0){
					col--;
					printf("Out of memory!\n");
				}else{
					memory -= strlen(disk[col-1].info);					
				}
				break;
			}
			case 4:{
				OpenFile(disk,derect,&col,&memory);
				break;
			}
			case 5:{
				Find(disk,&col);
				break;
			}
			case 6:{
				Del(disk,derect,&col,&memory);
				break;
			}
			case 7:{
				derect = disk[derect.per];
				break;
			}
			case 8:{
				col = Load(disk,&memory);
				break;
			}
			case 9:{
				Save(disk,&col);
				break;
			}
			case 10:{
				col = ScanDisk(disk,&memory);
				break;
			}			
			case 11:{
				printf("Exit..............\n");
				break;
			}
			default:{
				printf("Incorrect point!\n");
				break;
			}
		}
	}
}












