#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 30
#define ID 10
#define LINESIZE 100
#define FAIL 0
#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif
typedef struct{
	char id[ID];
	char ad[SIZE];
	char soyad[SIZE];
	int toplamDers;
	int toplamKredi;
}OGRENCI;

typedef struct{
	char id[ID];
	char ad[SIZE];
	char soyad[SIZE];
	char unvan[ID];
}OGRETMEN;

typedef struct{
	char dersKodu[ID];
	char ad[SIZE];
	int kredi;
	int kapasite;
	int kontenjan;
	char dersVeren[SIZE];
}DERS;

/*The functions used in the program*/
void menu ();
void setparameters();
/*Course Affairs*/
void dersEkle();
int dersGuncel();
int dersGuncelId(char* kod);
int dersSil(char* kod);
void derslerliste();
/*Student Affairs*/
int ogrcEkle();
int ogrcGuncel();
int ogrcGuncelId(char* id);
int ogrcSil(char* id);
/*Lecturer Affairs*/
void ogrtEkle();
int ogrtGuncel();
int ogrtGuncelId(char* id);
int ogrtSil(char* id);
/*Enrollment Affairs*/
int kayitEkle();
int kayitSil();
int kayitSilId(int id);
int kayitGuncel();
int kayitGuncelId(int id);
/*Displaying functions*/
int listOgrtDers();
int ListDersOgrc();
int ListOgrcDers();
int ClassList();


/*Other functions*/
long search(char* name, char* id);
long searchIdKod(int* kayitId, char* id,char* kod);
int satirSil(char* name,char* id);
int satirGuncelOgrenci(OGRENCI* ogrc);
int satirGuncelDers(DERS* ders);
int removeFromStudent(char* id,int kredi, int dec);
int removeFromCourse(char* kod);
int maxFind(int* maxkredi, int* maxcourse);
int incrementId();
int getId();
int findAllCoursesForLect(char* id);
int findAllStudents(char* kod);
int findAllCoursesForStd(char* id);
void remove_spaces(char* s);
void uppercase(char* s);
void putSpaces(char* s);
int display(char* name);
int krediBul(char* kod);


int main(int argc, char *argv[]){
	setparameters();
	menu();
	return 0;
}
/*This function initialize/changes the parameters of the system (maxkredi/maxcourse) */
void setparameters(){
	int maxkredi,maxcourse;
	printf("******** Welcome to the data base system of the university!********\n");
	FILE *fp=fopen("parameters.txt","r");
	if(fp!=NULL){
		printf("\n** Do you want to change the default settings? \nie Change maximum number of credits/ maximum number of courses? Y/N: ");
		char* cevap = (char*) malloc(sizeof(char)*10);
		scanf(" %[^\n]%*c",cevap);uppercase(cevap);
		if(strcmp(cevap,"Y")==0){
			printf("\n** Please enter the maximum credit that a student can take: "); scanf(" %d",&maxkredi);
			printf("\n** Please enter the maximum number of courses that a student can take: "); scanf(" %d",&maxcourse);
			int tmpMaxkredi, tmpMaxcourse,counter;
			char* line= (char*)malloc(sizeof(char)*LINESIZE);
			fgets(line,LINESIZE-1,fp);
			sscanf(line,"%d %d %d",&tmpMaxkredi,&tmpMaxcourse,&counter);
			fclose(fp); free(line);
			fp=fopen("parameters.txt","w");
			fprintf(fp,"%d %d %d",maxkredi,maxcourse,counter);
		}
		fclose(fp); 
		free(cevap);
		return;
	}
	fp= fopen("parameters.txt","w+");
	printf("\n** Setting up the parameters: \n");
	printf("\n** Please enter the maximum number of credits that a student can take: ");
	scanf(" %d",&maxkredi);
	printf("\n** Please enter the maximum number of courses that a student can take: ");
	scanf(" %d",&maxcourse);
	fprintf(fp,"%d %d 0 ",maxkredi,maxcourse);
	fclose(fp); 
	return;
}
void menu(){
	int secenek; /*Used to choose an option from the menus*/
	int back; /*Used to back to the main menu*/
	int devam=1; /*Used to do another operation*/
	char cevap; /*used for the choice of continue doing another operation*/
	char* id;
	while(devam){
		system(CLEAR);
		printf("\t****************** University Data Base ******************\n");
		printf("\n 1-Course Affairs.");
		printf("\n 2-Student Affairs.");
		printf("\n 3-Lecturer Affairs.");
		printf("\n 4-Enrollment Affairs."); 
		printf("\n 5-Displaying functions.");
		printf("\n Please choose a number: ");
		scanf(" %d",&secenek);  
		while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4 && secenek!=5 ){
			printf("\nError: Please choose a number between 1 and 5: ");
			scanf(" %d",&secenek);  
		}
		back=0;
		switch(secenek){
			case 1:
				system(CLEAR);
				printf("****************** Course Affairs ******************\n");
 				printf("\n1- Display all the existing courses.");
				printf("\n2- Add a new course.");
				printf("\n3- Update information of a course.");
				printf("\n4- Delete a course.");
				printf("\n5- Go back.");
				printf("\nPlease choose a number: ");
				scanf(" %d",&secenek);  
				while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4 && secenek!=5 ){
					printf("\nError: Please choose a number between 1 and 5: ");
					scanf(" %d",&secenek);   
				}
				switch(secenek){
					case 1:
						system(CLEAR);
						printf("\t****************** Display all Courses ******************\n\n");
						if(!display("Dersler.txt")) printf("\nMake sure you have added courses to the data base!");
						break;
					case 2:
						system(CLEAR);
						printf("****************** Add a new course ******************\n\n");
						dersEkle();
						break;
					case 3:
						system(CLEAR);
						printf("****************** Update information of a course ******************\n\n");
						dersGuncel();
						break;
					case 4:
						system(CLEAR);
						printf("****************** Delete a course ******************\n\n");
						printf("\nPlease enter the code of the course that you want to delete: ");
						id= (char*)malloc(sizeof(char)*ID);
						scanf(" %s",id);    uppercase(id); 
						dersSil(id);
						free(id);
						break;
					case 5:
						back=1;
						break;
				}
				break;
			case 2:
				system(CLEAR);
				printf("****************** Student Affairs ******************\n");
				printf("\n1- Display all the registered students.");
				printf("\n2- Add a new student.");
				printf("\n3- Update information of a student.");
				printf("\n4- Delete a student.");
				printf("\n5- Go back. ");
				printf("\nPlease choose a number: ");
				scanf(" %d",&secenek);   
				while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4 && secenek!=5){
					printf("\nError: Please choose a number between 1 and 5 : ");
					scanf(" %d",&secenek);   
				}
				switch(secenek){
					case 1:
						system(CLEAR);
						printf("\t****************** Display all Students ******************\n\n");
						if(!display("Ogrenciler.txt")) printf("\nMake sure you have added students to the data base!");
						break;
					case 2:
						system(CLEAR);
						printf("****************** Add a new student ******************\n\n");
						ogrcEkle();
						break;
					case 3:
						system(CLEAR);
						printf("****************** Update information of a student ******************\n\n");
						ogrcGuncel();
						break;
					case 4:
						system(CLEAR);
						printf("****************** Delete a student ******************\n\n");
						printf("\nPlease enter the student ID that will be deleted:");
						id= (char*)malloc(sizeof(char)*ID);
						scanf(" %s",id);    uppercase(id);
						ogrcSil(id);
						free(id);
						break;
					case 5:
						back=1;
						break;
				}
				break;
			case 3:
				system(CLEAR);
				printf("****************** Lecturer Affairs: ******************\n");
				printf("\n1- Display all the existing lecturers.");
				printf("\n2- Add a new Lecturer.");
				printf("\n3- Update information of a Lecturer.");
				printf("\n4- Delete a Lecturer.");
				printf("\n5- Go back.");
				printf("\n Please choose a number: ");
				scanf(" %d",&secenek);   
				while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4 && secenek!=5){
					printf("\nError: Please choose a number between 1 and 5: ");
					scanf(" %d",&secenek);   
				}
				switch(secenek){
					case 1:
						system(CLEAR);
						printf("\t****************** Display all lecturers ******************\n\n");
						if(!display("ogretimUyesi.txt")) printf("\nMake sure you have added lecturers to the data base!");
						break;
					case 2:
						system(CLEAR);
						printf("\t****************** Add a new Lecturer ******************\n\n");
						ogrtEkle();
						break;
					case 3:
						system(CLEAR);
						printf("****************** Update information of a Lecturer ******************\n\n");
						ogrtGuncel();
						break;
					case 4:
						system(CLEAR);
						printf("****************** Delete a Lecturer ******************\n\n");
						printf("\nPlease enter the Lecturer ID that will be deleted: ");
						id= (char*)malloc(sizeof(char)*ID);
						scanf(" %s",id);    uppercase(id);
						printf("\nWarning: If you delete a lecturer all his courses will be deleted.\nDo you want to continue? Y/N: ");
						scanf(" %c",&cevap);
						if(cevap=='Y'|| cevap=='y') ogrtSil(id);
						free(id);
						break;
					case 5:
						back=1;
						break;
				}
				break;
			case 4:
				system(CLEAR);
				printf("****************** Enrollment Affairs:******************\n");
 				printf("\n1- Register a student in a course (Add an enrollment).");
				printf("\n2- Update information of an existing enrollment.");
				printf("\n3- Delete an enrollment.");
				printf("\n4- Go back");
				printf("\nPlease choose a number: ");
				scanf(" %d",&secenek);   
				while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4){
					printf("\nError: Please choose a number between 1 and 4: ");
					scanf(" %d",&secenek);   
				}
				switch(secenek){
					case 1:
						system(CLEAR);
						printf("****************** Add an enrollment ******************\n\n");
						kayitEkle();
						break;
					case 2:
						system(CLEAR);
						printf("********** Update information of an existing enrollment ********\n\n");
						kayitGuncel();
						break;
					case 3:
						system(CLEAR);
						printf("****************** Delete an enrollment ******************\n\n");
						kayitSil();
						break;
					case 4:
						back=1;
						break;
				}
				break;
				
			case 5:	
				system(CLEAR);
				printf("****************** Displaying Functions ******************\n");
 				printf("\n1- List the courses given by a lecturer.");
				printf("\n2- List the students enrolled in a course.");
				printf("\n3- List the courses taken by a student.");
				printf("\n4- Create the course class list of a specific lecturer.");
				printf("\n5- Go back");
				printf("\n Please choose a number: ");
				scanf(" %d",&secenek);   
				while(secenek!=1 && secenek!=2 && secenek!=3 && secenek!=4 && secenek!=5 ){
					printf("\nError: Please choose a number between 1 and 4: ");
					scanf(" %d",&secenek);   
				}
				switch(secenek){
					case 1:
						system(CLEAR);
						printf("****************** List the courses of a lecturer ******************\n\n");
						listOgrtDers();
						break;
					case 2:
						system(CLEAR);
						printf("****************** List the students enrolled in a course ******************\n\n");
						ListDersOgrc();
						break;
					case 3:
						system(CLEAR);
						printf("****************** List the courses taken by a student ******************\n\n");
						ListOgrcDers();
						break;
					case 4:
						system(CLEAR);
						printf("****************** Create the course class list ******************\n\n");
						ClassList();
						break;
					case 5:
						back=1;
						break;
				}
				break;
						
		}
		if(!back){
			printf("\nDo you want to do another operation? Y/N: ");
			scanf(" %c",&cevap);  
			if(cevap!='Y'&& cevap!='y'){
				devam=0;
			}	
		}
	}
	
}


/*Function to add a course*/
void dersEkle(){
	
	DERS* ders= (DERS*) malloc(sizeof(DERS));
	char cevap;
	printf("\nPlease enter the information of the course: ");
	printf("\nCourse code: "); scanf(" %s",ders->dersKodu);   uppercase(ders->dersKodu);
	/*Check if the code is unique*/
	
	if (search("Dersler.txt",ders->dersKodu)==-1){ /*DersKodu doesn not exist*/ 
		/* Add a new course*/
		printf("\nCourse name: "); scanf (" %[^\n]%*c", ders->ad); remove_spaces(ders->ad);
		printf("\nCredit: "); scanf(" %d", &ders->kredi);  
		while(ders->kredi<0){
			printf("\nThe credit should be a positif number! please try again: ");
			scanf(" %d", &ders->kredi);  
		}
		ders->kapasite=0;
		printf("\nQuota (Maximum number of students that can take the course): "); 
		scanf(" %d", &ders->kontenjan);  
		while(ders->kontenjan<0){
			printf("\nQuota should be a positif number! please try again: ");
			scanf(" %d", &ders->kontenjan);  
		}
		printf("\nCourse Lecturer\'s ID: "); scanf(" %s",ders->dersVeren);   uppercase(ders->dersVeren);
		/*Check if the teacher exists*/
		while(search("ogretimUyesi.txt",ders->dersVeren)==-1){
			printf("\nWarning: The ID that you entered does not much any lecturer!\nDo you want to add a new lecturer? Y/N: ");
			scanf(" %c",&cevap);  
			if(cevap=='Y'|| cevap=='y'){ /*Add a new lecturer*/
				ogrtEkle();
				printf("\nPlease enter again the Course Lecturer\'s ID: "); 
				scanf(" %s",ders->dersVeren);   uppercase(ders->dersVeren);
			}
			else{
				free(ders); 
				return;
			}
		}
		/*write to the file	*/
		FILE *fptr = fopen("Dersler.txt","a+");
		fprintf(fptr,"%s %s %d %d %d %s\n",ders->dersKodu, ders->ad, ders->kredi,ders->kapasite,ders->kontenjan,ders->dersVeren);
		fclose(fptr); 
		printf("\nThe course was successfully added.");
	}
	else{
		printf("\nThis course already exists. Do you want to update it? Y/N: ");
		scanf(" %c",&cevap);  
		if(cevap=='Y'|| cevap=='y'){ /*Update*/
			dersGuncelId(ders->dersKodu);
		}
		else{
			printf("\nPlease check your information again!");
			free(ders);
			return;
		} 
	}
	free(ders);	
	return;
}
int dersGuncel(){
	char* kod= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the code of the course that you want to update: ");
	scanf(" %s",kod); uppercase(kod);
	if(search("Dersler.txt",kod)==-1){ /*The course does not exist*/
		char* cevap= (char*) malloc(sizeof(char));
		printf("\nThis code does not match any course. Do you want to add a new course? Y/N: ");
		scanf(" %[^\n]%*c",cevap); uppercase(cevap);
		if(strcmp(cevap,"Y")==0) dersEkle();
		else printf("\nPlease check your information!");
		free(kod); free(cevap);
		return FAIL;
	}
	dersGuncelId(kod);
	free(kod); 
	return 1;	
}
/*Function to update the information of  a course*/
int dersGuncelId(char* kod){
	char* cevap= (char*)malloc(sizeof(char)*10);
	DERS* ders= (DERS*) malloc(sizeof(DERS));
	/*fetch old iformatios of the course*/
	DERS* old= (DERS*) malloc(sizeof(DERS)); 
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	FILE *fp=fopen("Dersler.txt","r");
	fseek(fp,search("Dersler.txt",kod),SEEK_SET); /*seek the position of the course*/
	fgets(line,LINESIZE-1,fp);
	sscanf(line,"%s %s %d %d %d %s\n",old->dersKodu,old->ad,&old->kredi,&old->kapasite,&old->kontenjan,old->dersVeren);
	free(line); fclose(fp);
	/*Read the new information*/
	strcpy(ders->dersKodu,kod);
	printf("\nPlease enter the new information of the course: ");
	printf("\nCourse Name (old= %s): ",old->ad); scanf (" %[^\n]%*c", ders->ad); remove_spaces(ders->ad);
	printf("\nCredit (old=%d): ",old->kredi); scanf( " %d", &ders->kredi);  
	while(ders->kredi<0){
		printf("\nThe credit should be a positif number! please try again: ");
		scanf(" %d", &ders->kredi);
	}
	ders->kapasite = old->kapasite;
	printf("\nQuota (old= %d): ",old->kontenjan); scanf(" %d", &ders->kontenjan);  
	while(ders->kontenjan<0){
		printf("\nQuota should be a positif number! please try again: ");
		scanf(" %d", &ders->kontenjan);
	}
	printf("\nCourse Lecturer\'s ID (old=%s): ",old->dersVeren); scanf(" %s",ders->dersVeren);   uppercase(ders->dersVeren);
	/*Check if the teacher exists*/
	while(search("ogretimUyesi.txt",ders->dersVeren)==-1){
		printf("\nWarning:The ID that you entered does not much any lecturer!\nDo you want to add a new lecturer? Y/N: ");
		scanf(" %[^\n]%*c",cevap); uppercase(cevap);
		if(strcmp(cevap,"Y")==0){ /*Add a new lecturer*/
			ogrtEkle();
			printf("\nPlease enter again the Course Lecturer\'s ID: "); 
			scanf(" %s",ders->dersVeren);   uppercase(ders->dersVeren);	
		}
		else{
			free(ders);	free(old); free(cevap);
			/*pos point at Null no need to free it here*/
			return FAIL;
		}
	}
	/*change the specific course in the file*/
	satirGuncelDers(ders);
	free(ders); free(old); free(cevap); 
	return 1;
}
int satirGuncelDers(DERS* ders){
	FILE *fp1,*fp2;
	fp1= fopen("Dersler.txt","r");
	if (fp1==NULL){
        printf("\nUnable to open the Dersler.txt file!!\n");
        return FAIL;
    }
	char *line= (char*) malloc(sizeof(char)*LINESIZE);
	fp2 = fopen("temp.txt", "w"); /* open the temporary file in write mode */
	DERS* tmpders= (DERS*) malloc(sizeof(DERS));
	while(fgets(line,LINESIZE-1,fp1)!= NULL){
		sscanf(line,"%s %s %d %d %d %s",tmpders->dersKodu, tmpders->ad, &tmpders->kredi,&tmpders->kapasite,&tmpders->kontenjan,tmpders->dersVeren);
		if(strcmp(tmpders->dersKodu,ders->dersKodu)!=0){
			fprintf(fp2,"%s %s %d %d %d %s\n",tmpders->dersKodu, tmpders->ad, tmpders->kredi,tmpders->kapasite,tmpders->kontenjan,tmpders->dersVeren);
		}
		else{
			fprintf(fp2,"%s %s %d %d %d %s\n",ders->dersKodu, ders->ad, ders->kredi,ders->kapasite,ders->kontenjan,ders->dersVeren);
			printf("\nThe course %s was successfully updated.",ders->dersKodu);
			if(ders->kredi!= tmpders->kredi){
				/*Ogrencinin toplam kredisi guncel*/
				if(findAllStudents(ders->dersKodu)){
					FILE *fp3=fopen("Students.txt","r"); /*This file cotais IDs of all students taking this course*/
					int newkredi= ders->kredi-tmpders->kredi;
					char* idtmp= (char*) malloc(sizeof(char)*ID);
					char* line2=(char*) malloc(sizeof(char)*LINESIZE);
					while(fgets(line2,LINESIZE-1,fp3)!=NULL){
						sscanf(line2,"%s",idtmp);
						removeFromStudent(idtmp,newkredi,0);
					}
					free(idtmp); free(line2);
					fclose(fp3);
					remove("Students.txt");
					
				}
			}
		}
	}
	fclose(fp1); fclose(fp2);
	remove("Dersler.txt");
	rename("temp.txt","Dersler.txt");
	free(tmpders); free(line);
	return 1;
}
int dersSil(char* kod){
	int kredi= krediBul(kod);
	if(!satirSil("Dersler.txt",kod)){
		printf("\nThis code does not match any course! Please check your information.");
		return FAIL;
	}
	printf("\nThe course %s was successfully deleted! ",kod);
		/*****************Course was deleted********************
		decrement ogrencinin toplam aldigi dersler ve toplam kredi*/
			if(findAllStudents(kod)){/*If there exist students who are taking this course*/
					FILE *fp3=fopen("Students.txt","r");/*This file cotais IDs of all students taking this course*/
					char* tmpid= (char*) malloc(sizeof(char)*ID);
					char* line=(char*) malloc(sizeof(char)*LINESIZE);
					while(fgets(line,LINESIZE-1,fp3)!=NULL){
						sscanf(line,"%s",tmpid);
						removeFromStudent(tmpid,-kredi,1);
					}
					fclose(fp3);
					remove("Students.txt");	
			 }
	/*	Change the file of OgrenciDersKAyit.txt*/
	return 1;
}
/*This function decrements the number of students taking the course by 1 (ders->kapasite--)
And updates the informatios of this course in Dersler.txt*/
int removeFromCourse(char* kod){
	FILE *fp= fopen("Dersler.txt","r");
	if (fp==NULL){
        printf("\nUnable to open the Dersler.txt file!!\n");
        return FAIL;
    }
	char* line=(char*)malloc(LINESIZE*sizeof(char));
	DERS* tmpders= (DERS*) malloc(sizeof(DERS));
	FILE *fp2= fopen("tmp1.txt","w");
	while(fgets(line,LINESIZE-1,fp)!= NULL){
		sscanf(line,"%s %s %d %d %d %s",tmpders->dersKodu, tmpders->ad, &tmpders->kredi,&tmpders->kapasite,&tmpders->kontenjan,tmpders->dersVeren);
		if(strcmp(tmpders->dersKodu,kod)!=0){
			fprintf(fp2,"%s %s %d %d %d %s\n",tmpders->dersKodu, tmpders->ad, tmpders->kredi,tmpders->kapasite,tmpders->kontenjan,tmpders->dersVeren);
		}
		else{
			tmpders->kapasite--;
			fprintf(fp2,"%s %s %d %d %d %s\n",tmpders->dersKodu, tmpders->ad, tmpders->kredi,tmpders->kapasite,tmpders->kontenjan,tmpders->dersVeren);
			printf("\nThe information of the course %s were successfully updated.",kod);

		}
	}
	fclose(fp); fclose(fp2);
	remove("Dersler.txt");
	rename("tmp1.txt","Dersler.txt");
	free(tmpders); free(line);
	return 1;
}
/*Function to add a student*/
int ogrcEkle(){
	/**/
	OGRENCI *ogrc= (OGRENCI*)malloc(sizeof(OGRENCI));
	printf("\nPlease enter the information of the student:");
	printf("\nID: "); scanf(" %s",ogrc->id);   uppercase(ogrc->id);
	/*Check unique function*/
	if (search("Ogrenciler.txt",ogrc->id)==-1){ /*File empty or does not exist so  add new student*/
		printf("\nName: "); scanf (" %[^\n]%*c", ogrc->ad); remove_spaces(ogrc->ad);
		printf("\nSurname: "); scanf(" %[^\n]%*c", ogrc->soyad); remove_spaces(ogrc->soyad);
		ogrc->toplamDers=0;
		ogrc->toplamKredi=0;
		/*write to the file	*/
		FILE *fptr = fopen("Ogrenciler.txt","a+");
		fprintf(fptr,"%s %s %s %d %d\n",ogrc->id,ogrc->ad,ogrc->soyad,ogrc->toplamDers,ogrc->toplamKredi);
		fclose(fptr);	
		printf("\nThe student was successfully added.");	
	}
	else{
		printf("This student is already registered. Do you want to update his information? Y/N: ");
		char cevap;
		scanf(" %c",&cevap);
		if(cevap=='y' || cevap=='Y'){ /*Update*/
			ogrcGuncelId(ogrc->id);
		}
		else{
			printf("\nPlease check your information!");
			free(ogrc);
			return FAIL;
		}
	}
	free(ogrc);
	return 1;
}
int ogrcGuncel(){ 
	char* id= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the student ID whose information is to be updated: ");
	scanf(" %s",id); uppercase(id);
	if(search("Ogrenciler.txt",id)==-1){
		char cevap;
		printf("\nThis ID does not match any student. Do you want to add a new student? Y/N: ");
		scanf(" %c",&cevap);
		if(cevap=='Y'|| cevap=='y') ogrcEkle();
		else printf("\nPlease check your information!");
		free(id);
		return FAIL;
	}
	ogrcGuncelId(id);
	free(id);		
	return 1;
}
int ogrcGuncelId(char id[]){
	/*Find the maximum kredi*/
	int* maxkredi= (int*)malloc(sizeof(int));
	int* maxcourse= (int*)malloc(sizeof(int));
	if (!maxFind(maxkredi,maxcourse)){
		printf("\nError: Unable to read the parameter file!\n"); 
		free(maxkredi); free(maxcourse);
		return FAIL;
	}
	/*************************/
	
	OGRENCI *ogrc= (OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI *old= (OGRENCI*)malloc(sizeof(OGRENCI));
	FILE *fp=fopen("Ogrenciler.txt","r");
	fseek(fp,search("Ogrenciler.txt",id),SEEK_SET);
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	fgets(line,LINESIZE-1,fp); 
	sscanf(line,"%s %s %s %d %d\n",old->id,old->ad,old->soyad,&old->toplamDers,&old->toplamKredi);
	free(line);	fclose(fp);
	strcpy(ogrc->id,id);
	printf("Please enter the new information:");  
	printf("\nName (old=%s): ",old->ad); scanf (" %[^\n]%*c", ogrc->ad); remove_spaces(ogrc->ad);
	printf("\nSurname (old=%s): ",old->soyad); scanf(" %[^\n]%*c", ogrc->soyad); remove_spaces(ogrc->soyad);
	printf("\nTotal courses (old=%d): ",old->toplamDers); scanf(" %d", &ogrc->toplamDers);
	while(ogrc->toplamDers<0 || ogrc->toplamDers>*maxcourse){
		printf("\nTotal courses should be between 0 and %d. Please try again: ",*maxcourse);
		scanf(" %d", &ogrc->toplamDers);
	}
	free(maxcourse);
	printf("\nTotal credits(old=%d): ",old->toplamKredi); scanf(" %d", &ogrc->toplamKredi);
	while(ogrc->toplamKredi<0 || ogrc->toplamKredi>*maxkredi){
		printf("\nTotal credits should be between 0 and %d. Please try again: ",*maxkredi);
		scanf(" %d", &ogrc->toplamKredi);
	}
	free(maxkredi);
	free(old);
	/*change the specific student in the file*/
	satirGuncelOgrenci(ogrc);
	free(ogrc); 
	return 1;
	
	
}
/*This function searches for the line that starts with ogrc->id in the file "Ogrenciler.txt" and update its information
It returns 1 if the file is updated otherwiae it returns FAIL*/
int satirGuncelOgrenci(OGRENCI* ogrc){
	FILE *fp1,*fp2;
	fp1= fopen("Ogrenciler.txt","r");
	if (fp1==NULL){
        printf("\nUnable to open the Ogrenciler.txt file!!\n");
        return FAIL;
    }
	char* line= (char*)malloc(sizeof(char)*LINESIZE);
	char* tmpId=(char*) malloc(sizeof(char)*ID);
	fp2 = fopen("temp.txt", "w"); /* open the temporary file in write mode */
	while(fgets(line,LINESIZE-1,fp1)!= NULL){
		sscanf(line,"%s ",tmpId); /*Take the student ID*/
		if(strcmp(tmpId,ogrc->id)!=0){
			fprintf(fp2,"%s",line);
		}
		else{
			fprintf(fp2,"%s %s %s %d %d\n",ogrc->id,ogrc->ad,ogrc->soyad,ogrc->toplamDers,ogrc->toplamKredi);
			printf("\nThe student of %s Id was successfully updated.",ogrc->id);
		}
	}
	fclose(fp1); fclose(fp2);
	remove("Ogrenciler.txt");
	rename("temp.txt","Ogrenciler.txt");
	free(tmpId); free(line);
	return 1;
}
int ogrcSil(char* id){
	/*search for the courses he took to decrement them*/
	if(!satirSil("Ogrenciler.txt",id)){
		printf("\nThis ID does not match any student! Please try again.");
		return FAIL;
	}
	printf("\nThe student of ID %s was successfully deleted!",id);
	/*Decrement ders kapasite*/
	if(findAllCoursesForStd(id)){
		/*There exist courses take by this student*/
		FILE *fp3=fopen("Courses.txt","r");/*This file cotains codes of all courses taken by this student*/
		char* kod= (char*) malloc(sizeof(char)*ID);
		char* line=(char*) malloc(sizeof(char)*LINESIZE);
		while(fgets(line,LINESIZE-1,fp3)!=NULL){
			sscanf(line,"%s",kod);
			removeFromCourse(kod); /*Decrement the capacity of each course*/
		}
		 
		fclose(fp3);
		remove("Courses.txt");
		/*********************************************/
	}
	
	return 1;
}
/*Update the information of student id by decrementing the total credit by kod->kredi 
and the total number of courses by 1*/
int removeFromStudent(char* id,int kredi,int dec){
	FILE* fp1= fopen("Ogrenciler.txt","r");
	if (fp1==NULL){
        printf("\nUnable to open the Ogrenciler.txt file!!\n");
        return FAIL;
    }
	char* line=(char*)malloc(LINESIZE*sizeof(char));
	FILE *fp2 = fopen("temp2.txt", "w"); /* open the temporary file in write mode */
	OGRENCI* tmp=(OGRENCI*) malloc(sizeof(OGRENCI));
	while(fgets(line,LINESIZE-1,fp1)!= NULL){
		sscanf(line,"%s %s %s %d %d",tmp->id,tmp->ad,tmp->soyad,&tmp->toplamDers,&tmp->toplamKredi);
		if(strcmp(tmp->id,id)!=0){
			fprintf(fp2,"%s %s %s %d %d\n",tmp->id,tmp->ad,tmp->soyad,tmp->toplamDers,tmp->toplamKredi);
		}
		else{
			if(dec) tmp->toplamDers--;
			tmp->toplamKredi += kredi;
			fprintf(fp2,"%s %s %s %d %d\n",tmp->id,tmp->ad,tmp->soyad,tmp->toplamDers,tmp->toplamKredi);			
			printf("\nThe information of the student %s were successfully updated.",id);
		}
	}
	fclose(fp1); fclose(fp2);
	remove("Ogrenciler.txt");
	rename("temp2.txt","Ogrenciler.txt");
	free(tmp); free(line);
	return 1;
}
/*This function searches for the line that starts with "id" in the file "name" and delete it
It returns 1 if the value exists otherwiae it returns NULL*/
void ogrtEkle(){
	char cevap;
	OGRETMEN* ogrt=(OGRETMEN*)malloc(sizeof(OGRETMEN));
	printf("\nPlease enter the information of the lecturer: ");
	printf("\nID: "); scanf(" %s",ogrt->id);   uppercase(ogrt->id);
	/*Check unique function*/
	if (search("ogretimUyesi.txt",ogrt->id)==-1){ /* Yeni gretmen ekle*/
		printf("\nName: "); scanf (" %[^\n]%*c", ogrt->ad); remove_spaces(ogrt->ad);
		printf("\nSurname: "); scanf (" %[^\n]%*c", ogrt->soyad); remove_spaces(ogrt->soyad);
		printf("\nJob title: "); scanf (" %[^\n]%*c", ogrt->unvan); remove_spaces(ogrt->unvan);
		/*write to the file	*/
		FILE *fptr = fopen("ogretimUyesi.txt","a+");
		fprintf(fptr,"%s %s %s %s\n",ogrt->id,ogrt->ad,ogrt->soyad,ogrt->unvan);
		fclose(fptr);
		printf("\nThe lecturer was successfully added.");	
	
	}
	else{
		printf("This ID already exists. Do you want to update it? Y/N: ");
		scanf(" %c",&cevap);
		if (cevap=='y' || cevap=='Y'){ /*Update*/
			ogrtGuncelId(ogrt->id);
		}
		else{
			printf("\nPlease check your information!");
		}
	}
	free(ogrt);
}
int ogrtGuncel(){
	char* id= (char*)malloc(sizeof(char)*ID);
	printf("\nPlease enter the Lecturer ID whose information is to be updated: ");
	scanf(" %s",id); uppercase(id);
	char cevap;
	if(search("ogretimUyesi.txt",id)==-1){
		printf("\nThis ID does not match any lecturer. Do you want to add a new lecturer? Y/N: ");
		scanf(" %c",&cevap);
		if(cevap=='Y'|| cevap=='y') ogrtEkle();
		else printf("\nPlease check your information!");
		free(id);
		return FAIL;
	}
	ogrtGuncelId(id);
	free(id);		
	return 1;
}
int ogrtGuncelId(char* id){
	OGRETMEN* ogrt=(OGRETMEN*)malloc(sizeof(OGRETMEN));
	OGRETMEN* old=(OGRETMEN*)malloc(sizeof(OGRETMEN));
	FILE *fp,*fp2;
	/*Get the old information*/
	fp=fopen("OgretimUyesi.txt","r");
	fseek(fp,search("OgretimUyesi.txt",id),SEEK_SET);
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	fgets(line,LINESIZE-1,fp); 
	sscanf(line,"%s %s %s %s\n",old->id,old->ad,old->soyad,old->unvan);
	fclose(fp);
	strcpy(ogrt->id,id);
	printf("\nPlease enter the new information:"); 
	printf("\nName (old= %s): ",old->ad); scanf (" %[^\n]%*c", ogrt->ad); remove_spaces(ogrt->ad);
	printf("\nSurname (old=%s): ",old->soyad); scanf (" %[^\n]%*c", ogrt->soyad); remove_spaces(ogrt->soyad);
	printf("\nTitle (old=%s): ",old->unvan); scanf (" %[^\n]%*c", ogrt->unvan); remove_spaces(ogrt->unvan);
	/*change the specific lecturer in the file*/
	fp=fopen("OgretimUyesi.txt","r"); fseek(fp,0,SEEK_SET);
	fp2= fopen("temp.txt", "w"); /* open the temporary file in write mode */
	while(fgets(line,LINESIZE-1,fp)!= NULL){
		/*old struct will be used as a tmp struct */
		sscanf(line,"%s %s %s %s",old->id,old->ad,old->soyad,old->unvan);
		if(strcmp(old->id,id)!=0){
			fprintf(fp2,"%s %s %s %s\n",old->id,old->ad,old->soyad,old->unvan);
		}
		else{
			fprintf(fp2,"%s %s %s %s\n",ogrt->id,ogrt->ad,ogrt->soyad,ogrt->unvan);
		}
	}
	free(line);
	fclose(fp); fclose(fp2);
	remove("OgretimUyesi.txt");
	rename("temp.txt","OgretimUyesi.txt");
	printf("\nThe lecturer was successfully updated.");
	free(old); free(ogrt);
	return 1;
}
int ogrtSil(char* id){
	
	if(!satirSil("ogretimUyesi.txt",id)){
			printf("\nThis ID does not match any Lecturer. Please check your information!");
			return FAIL;
	}
	printf("The Lecturer of ID %s was successfully deleted!",id);
	/*Delete all his courses and all the enrollments.*/
	if(findAllCoursesForLect(id)){
		/*Check if the file is empty*/
		FILE *fp= fopen("Lecturer.txt","r");
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0){/*The file is empty so no courses to be deleted*/
			fclose(fp);	remove("Lecturer.txt");
		}
		else{
			/*Delete all the courses*/
			fseek(fp,0,SEEK_SET);
			char* line= (char*) malloc(sizeof(char)*LINESIZE);
			char* course= (char*) malloc(sizeof(char)*ID);
			while(fgets(line,LINESIZE-1,fp)!=NULL){
				sscanf(line,"%s\n",course);
				dersSil(course);
			}
			free(line); fclose(fp);
			remove("Lecturer.txt");
			
		}
	}
	return 1;
	
}
int satirSil(char* name,char* id){
	FILE *fp1,*fp2;
	fp1= fopen(name,"r");
	if (fp1==NULL){
        printf("\nUnable to open the input file!!\n");
        return FAIL;
    }
    /*check if the file is empty*/
    fseek(fp1,0,SEEK_END);
    if(ftell(fp1)==0) return FAIL;
    fseek(fp1,0,SEEK_SET);
	int value= 0;
   	char* tmpid= (char*)malloc(sizeof(char)*ID);
    char* line= (char*)malloc(sizeof(char)*LINESIZE);
	fp2 = fopen("temp.txt", "w"); /* open the temporary file in write mode */
    while(fgets(line,LINESIZE-1,fp1)!= NULL){
    	sscanf(line, "%s ",tmpid);
		if (strcmp(tmpid,id)!=0) {
			fprintf(fp2,"%s",line);
		}
		else value=1; /*The line was found and deleted*/
	}
	fclose(fp1); fclose(fp2);
	free(line); free(tmpid);
	remove(name);
	rename("temp.txt",name);
	return value;
}
/*A function to search for id in the file name. If it 
exists it returns its position pos otherwise returns -1 */
long search(char* name, char* id){
	
	FILE *fp=fopen(name,"r");
	if(fp == NULL) {
		printf("\n%s File could not be found ",name);
    	return -1; /*File doesn't exist i.e. id does not exist*/
   	}
   	/*Pick the curseur of this line*/
   	char* tmpid= (char*)malloc(sizeof(char)*ID);
   	char* line= (char*)malloc(sizeof(char)*LINESIZE);
	long pos=ftell(fp); /*Used to find which line the id exist*/
	while(fgets(line,LINESIZE-1,fp)!= NULL){
	/*take the first word before " " */
		sscanf(line, "%s ",tmpid);
		if (strcmp(tmpid,id)==0) {
			free(line); free(tmpid);
			fclose(fp);
			return pos; /*Id exists at position pos*/
		}
		/*Pick the pointer of this line*/
		pos= ftell(fp);
	}
	fclose(fp);
	free(line); free(tmpid);
	return -1; /*ID does not exist*/	
}
/*Function to delete a line*/
/*Function to add registration*/
/*This function searched for the position of an enrollment given student ID and course code*/
long searchIdKod(int* kayitId, char* id,char* kod){
	FILE *fp=fopen("OgrenciDersKayit.txt","r");
	if(fp==NULL){
		/*printf("\nError:OgrenciDersKayit.txt File could not be found ");*/
        return(-1); /*File doesn't exist i.e. enrollment does not exist*/	
	}
	
	char* line= (char*)malloc(sizeof(char)*LINESIZE);
	char* tmpKod= (char*)malloc(sizeof(char)*ID);
   	char* tmpId= (char*)malloc(sizeof(char)*ID);
	while(fgets(line,LINESIZE-1,fp)!= NULL){
		sscanf(line,"%d %s %s",kayitId, tmpKod,tmpId); 
		if (strcmp(tmpId,id)==0 && strcmp(tmpKod,kod)==0) { /*ID is found*/
			fclose(fp);
			free(line); free(tmpKod); free(tmpId);
			return 1;
		}
	}
	fclose(fp);
	free(line); free(tmpKod); free(tmpId);
	return -1; /*ID does not exist*/		
}

/*Function to find the max credita, and the max number of courses*/
int maxFind(int* maxkredi, int* maxcourse){
	FILE *fp=fopen("parameters.txt","r");
	if(fp==NULL){
		printf("\nFile could not be found");
		return FAIL;
	}
	char* line=(char*)malloc(LINESIZE*sizeof(char));
	fgets(line,LINESIZE-1,fp);
	sscanf(line,"%d %d",maxkredi,maxcourse);
	fclose(fp); free(line);
	return 1;
}
/*This function finds the number of enrollments (Id) and increments it*/
int incrementId(){

	FILE *fp=fopen("parameters.txt","r+");
	if(fp==NULL) return FAIL;
	int maxkredi,maxcourse,counter;
	char* line= (char*)malloc(sizeof(char)*LINESIZE);
	fgets(line,LINESIZE-1,fp);
	sscanf(line,"%d %d %d",&maxkredi,&maxcourse,&counter);
	counter++;
	fclose(fp);	free(line);
	fp=fopen("parameters.txt","w");
	fprintf(fp,"%d %d %d",maxkredi,maxcourse,counter);
	fclose(fp); 
	return counter;
}
int kayitEkle(){
	
	char *stdId=(char*)malloc(sizeof(char)*SIZE);
	printf("\nPlease enter the following information:");
	printf("\nStudent ID: "); 
	scanf(" %s",stdId);   uppercase(stdId);
	/*Make sure that the student and the course both exist*/
	long pos1=search("Ogrenciler.txt",stdId);
	char cevap;
	if (pos1==-1){
		printf("\nThis ID does not match any student. Do you want to add a new student? Y/N: ");
		scanf(" %c",&cevap);  
		if(cevap=='Y'|| cevap=='y') ogrcEkle();
		else{
			free(stdId);
			return FAIL;
		} 
	}
	char *kod=(char*)malloc(sizeof(char)*SIZE);
	printf("\nCourse code: ");
	scanf(" %s",kod);   uppercase(kod);
	long pos2=search("Dersler.txt",kod);
	if (pos2==-1){
		printf("\nThis code does not match any course. Do you want to add a new course? Y/N: ");
		scanf(" %c",&cevap);  
		if(cevap=='Y'|| cevap=='y') dersEkle();
		else{
			free(stdId); free(kod);
			return FAIL;
		} 
	}
	/****/
	/*Check if the enrollment exists*/
	int id;/*to save the id of the enrollment*/
	if(searchIdKod(&id,stdId,kod)!=-1){
		printf("This enrollment already exists. Do you want to update it? Y/N: ");
		scanf(" %c",&cevap);
		if(cevap=='Y'|| cevap=='y'){ /*Update the enrollment*/
			kayitGuncelId(id);
		}
		else{
			printf("\nPlease check your information!");
		}
		free(stdId); free(kod);
		return FAIL;	
	}
	free(stdId);free(kod);
	/*Fetch data for enrollment*/
	char *line= (char*) malloc(LINESIZE*sizeof(char));
	/*Read the information of the student*/
	OGRENCI *ogrc= (OGRENCI*)malloc(sizeof(OGRENCI));
	FILE *fp1=fopen("Ogrenciler.txt","r");
	fseek(fp1,pos1,SEEK_SET);
	fgets(line,LINESIZE-1,fp1);
	sscanf(line,"%s %s %s %d %d",ogrc->id,ogrc->ad,ogrc->soyad,&ogrc->toplamDers,&ogrc->toplamKredi);
	fclose(fp1);
	/*Read the information of the course*/
	DERS *ders= (DERS*)malloc(sizeof(DERS));
	fp1= fopen("Dersler.txt","r");		
	fseek(fp1,pos2,SEEK_SET);
	fgets(line,LINESIZE-1,fp1);
	sscanf(line,"%s %s %d %d %d %s\n",ders->dersKodu, ders->ad, &ders->kredi,&ders->kapasite,&ders->kontenjan,ders->dersVeren);
	fclose(fp1); free(line); 
	
	/*Find the maximum credit and maximum number of courses */
	int maxkredi, maxcourse;
	if (!maxFind(&maxkredi,&maxcourse)){
		printf("\nError: Unable to read the maximum credit and maximum course!\n");
		return FAIL;
	}
	/**/
	/*Check if the course can be added*/
	if ((ogrc->toplamKredi+ders->kredi)<= maxkredi && ogrc->toplamDers<maxcourse && ders->kapasite<ders->kontenjan){
		ogrc->toplamKredi += ders->kredi;
		ogrc->toplamDers++; 
		ders->kapasite++;
		/*Add a new enrollment to the file "OgrenciDersKayit.txt"*/
		/*Get the current time*/
		time_t t = time(NULL);
        struct tm tm = *localtime(&t);
		fp1=fopen("ogrenciDersKayit.txt","a+");
		/*Increment the ID of registration */
		int counter=incrementId();
		fprintf(fp1,"%d %s %s 1 %d-%d-%d %d:%d:%d\n", counter,ders->dersKodu,ogrc->id,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fclose(fp1);	
		/*Update the information of the student and the course*/
		if(!satirGuncelOgrenci(ogrc) ){
			printf("\nError: The course was added but we failed to update the information of the student!\n");
		}
		if(!satirGuncelDers(ders)){
			printf("\nError: The course was added but we failed to update the information of the course!\n");
		}
	}
	else{
		if(ders->kapasite>= ders->kontenjan) printf("\nEnrollment failed because quota of the course is full!");
		else if(ogrc->toplamDers>= maxcourse) {
			printf("\nError: Enrollment failed because the student took the maximum number of courses!");
		}
		else printf("\nError: Enrollment failed because the student took the maximum number of credits!");
		 free(ogrc);free(ders);
		return FAIL;
	}
	printf("\nEnrollment was successfully added.");
	free(ogrc);free(ders);
	return 1;
}	

int kayitSil(){
	int id=getId();
	if(id==-1) return FAIL;
	if(kayitSilId(id)){
		printf("\nThe enrollment was successfully deleted");
		return 1;
	}
	return FAIL;
}
int getId(){
	int id;
	char* idstr= (char*) malloc(sizeof(char)*ID);
	printf("Please enter the ID of the enrollment. If you do not know it enter 0: ");
	scanf(" %d",&id);  
 	snprintf(idstr, sizeof(idstr), "%d", id);	
	 if(id!=0){
		if (search("OgrenciDersKayit.txt",idstr)==-1){
			printf("\nError: This enrollment does not exist! Please check your information");
			free(idstr);
			return -1;
		}
		free(idstr);
		return id;
	}
	
	else{
		char* stdId= (char*) malloc(sizeof(char)*ID);
		char* kod= (char*) malloc(sizeof(char)*ID);
		printf("\nPlease enter the student ID: ");
		scanf(" %s",stdId);   uppercase(stdId);
		printf("\nPlease enter the course code: ");
		scanf(" %s",kod);   uppercase(kod);
		if(searchIdKod(&id,stdId,kod)==-1){
			printf("\nError: Error: This enrollment does not exist! Please check your information.");
			free(idstr); free(kod); free(stdId);
			return -1;
		}	
		free(idstr); free(kod); free(stdId);
	}
	return id;
}
int kayitSilId(int id){
	int tmpId;
	char* kod= (char*) malloc(ID*sizeof(char));
	char* stdId= (char*) malloc(ID*sizeof(char));
	char* line= (char*) malloc(LINESIZE*sizeof(char));
	FILE *fp1,*fp2;
	fp1=fopen("OgrenciDersKayit.txt","r");
	fp2=fopen("tmp.txt","w");
	while(fgets(line,LINESIZE-1,fp1)!= NULL){
		sscanf(line,"%d ", &tmpId);
		if(tmpId!=id){
			fprintf(fp2,"%s",line);
		}
		else{
			int y,mo,d,h,m,s;
			sscanf(line,"%d %s %s 1 %d-%d-%d %d:%d:%d",&tmpId,kod,stdId,&y,&mo,&d,&h,&m,&s);
			fprintf(fp2,"%d %s %s 0 %d-%d-%d %d:%d:%d\n",tmpId,kod,stdId,y,mo,d,h,m,s);
		}
	}

	fclose(fp1); fclose(fp2);
	remove("OgrenciDersKayit.txt");
	rename("tmp.txt","OgrenciDersKayit.txt");
	/*Update information of the student and the course*/
	/*fetch the credit of the course*/
	int kredi=krediBul(kod);
	if(!removeFromStudent(stdId,-kredi,1)) printf("\nError: Student information could not be updated!\n");
	if(!removeFromCourse(kod)) printf("\nError: course information could not be updated!!\n");
	free(line);
	free(kod); free(stdId);
	return 1;
}
int kayitGuncel(){
	int id;
	if((id=getId())==-1) return FAIL;
	if(kayitGuncelId(id)){
		printf("\nThe enrollment was successfully updated");
		return 1;
	}
	return FAIL;	
}
int kayitGuncelId(int id){
	char* kod= (char*) malloc(ID*sizeof(char));
	char* stdId= (char*) malloc(ID*sizeof(char));
	char* durum= (char*) malloc(ID*sizeof(char));
	char* tarih= (char*) malloc(30*sizeof(char));
	char* line= (char*) malloc(LINESIZE*sizeof(char));
	int tmpId,durumInt=1,eski;
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
	printf("\nPlease enter the new status of the enrollment (REGISTERED/DROPPED): ");
	scanf(" %[^\n]%*c",durum); uppercase(durum);
	while(strcmp(durum,"DROPPED")!=0 && strcmp(durum,"REGISTERED")!=0){
		printf("\nPlease if the student will be enrolled enter REGISTERED, otherwise enter DROPPED: ");
		scanf(" %[^\n]%*c",durum); uppercase(durum);
	}
	if(strcmp(durum,"DROPPED")==0) durumInt=0;
	printf("Please enter the new date of the enrollment in the format of (yyyy-m-d h:m:s) 24h");
	printf("\nOr enter YES if you want to use the current time and date\nOr enter NO if you want to use the same old date\nYour choice: ");
	scanf(" %[^\n]%*c",tarih); uppercase(tarih);
	FILE *fp1,*fp2;
	fp1=fopen("OgrenciDersKayit.txt","r");
	fp2=fopen("tmp.txt","w+");
	fseek(fp1,0,SEEK_SET);
	while(fgets(line,LINESIZE-1,fp1)!= NULL){
		sscanf(line,"%d ", &tmpId);
		if(tmpId!=id){
			fprintf(fp2,"%s",line);
		}
		else{
			int y,mo,d,h,m,s;
			sscanf(line,"%d %s %s %d %d-%d-%d %d:%d:%d",&tmpId,kod,stdId,&eski,&y,&mo,&d,&h,&m,&s);
			if(strcmp(tarih,"YES")==0){
				fprintf(fp2,"%d %s %s %d %d-%d-%d %d:%d:%d\n",tmpId,kod,stdId,durumInt,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			}
			else if(strcmp(tarih,"NO")==0){
				fprintf(fp2,"%d %s %s %d %d-%d-%d %d:%d:%d\n",tmpId,kod,stdId,durumInt,y,mo,d,h,m,s);
			}
			else{
				sscanf(tarih,"%d-%d-%d %d:%d:%d",&y,&mo,&d,&h,&m,&s);
					fprintf(fp2,"%d %s %s %d %d-%d-%d %d:%d:%d\n",tmpId,kod,stdId,durumInt,y,mo,d,h,m,s);
			}
			if(!durumInt){ /*The enrollment is deleted so update the information of student and course*/
				int kredi=krediBul(kod);
				if(kredi!=-1){
					if(!removeFromStudent(stdId,-kredi,1)) printf("\nError: Student information could not be updated!\n");
					if(!removeFromCourse(kod)) printf("\nError: Course information could not be updated!!\n");
				}
			}
		}
	}
	fclose(fp1); fclose(fp2);
	remove("OgrenciDersKayit.txt");
	rename("tmp.txt","OgrenciDersKayit.txt");
	free(stdId); free(kod); free(tarih); free(durum); free(line);
	return 1;
}
/*fetch the credit of the course*/
int krediBul(char* kod){
	long pos=search("Dersler.txt",kod);
	if(pos!=-1){
		char* line= (char*)malloc(sizeof(char)*LINESIZE);
		FILE* fptr=fopen("Dersler.txt","r");
		fseek(fptr,pos,SEEK_SET);
		fgets(line,LINESIZE-1,fptr);
		DERS* ders= (DERS*)malloc(sizeof(DERS)); 
		sscanf(line,"%s %s %d",ders->dersKodu,ders->ad,&ders->kredi);
		fclose(fptr); free(line);
		int kredi= ders->kredi;
		free(ders);
		return kredi;
	}
	return -1;
}

/*This function lists all the courses given by the lecturer of the ID*/



int findAllCoursesForLect(char* id){
	FILE *fp=fopen("Dersler.txt","r");
	if(fp==NULL) return FAIL;	
	FILE *fp2= fopen("Lecturer.txt","w+");
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	DERS* ders= (DERS*) malloc(sizeof(DERS));
	while(fgets(line,LINESIZE-1,fp)!=NULL){
		sscanf(line,"%s %s %d %d %d %s\n",ders->dersKodu, ders->ad, &ders->kredi,&ders->kapasite,&ders->kontenjan,ders->dersVeren);
		if(strcmp(ders->dersVeren,id)==0){
			putSpaces(ders->ad);
			fprintf(fp2,"%s %s\n",ders->dersKodu,ders->ad);
		}
	}
	fclose(fp); fclose(fp2);
	free(ders); free(line);
	return 1;
}
int listOgrtDers(){

	char* id= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the ID of the lecturer: ");
	scanf(" %s",id); uppercase(id);
	/*Check if the lecturer exists */	
	if(search("ogretimUyesi.txt",id)==-1){
		printf("\nThis ID does not match any lecturer. Please check your information! ");
		free(id);
		return FAIL;
	}
	if(findAllCoursesForLect(id)){
		/*Check if the file is empty*/
		FILE *fp= fopen("Lecturer.txt","r");
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0){
			printf("\nThis lecturer does not give any course!");
			fclose(fp);	remove("Lecturer.txt");
			free(id);
			return FAIL;
		}
		/***********************/
		fclose(fp);
		/*The file is not empty*/	
		display("Lecturer.txt");
		remove("Lecturer.txt");
	}
	else printf("\nError: Failed to open Dersler.txt file. Probably it does not exist.");
	free(id);
	return 1;
}
/*This function finds all the students registered in a course kod and save them in the file "Students.txt"*/
int findAllStudents(char* kod){
	FILE *fp, *fp2,*fp3;
	fp=fopen("OgrenciDersKayit.txt","r");
	if(fp==NULL) return FAIL; /*no enrollments*/
	fp2= fopen("Students.txt","w+");
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	char* line2= (char*) malloc(sizeof(char)*LINESIZE);
	char* kodtmp= (char*) malloc(sizeof(char)*ID);
	char* idtmp=(char*) malloc(sizeof(char)*ID);
	char* name=(char*) malloc(sizeof(char)*SIZE);
	char* surname=(char*) malloc(sizeof(char)*SIZE);
	int counter,durum;
	long pos;
	while(fgets(line,LINESIZE-1,fp)!=NULL){
		sscanf(line,"%d %s %s %d",&counter, kodtmp,idtmp,&durum);
		if(strcmp(kod,kodtmp)==0 && durum==1){ /*Save only students enrolled (durum==1)*/
			/*We found a student so search for name and surname*/
			pos=search("Ogrenciler.txt",idtmp);
			if(pos!=-1){
				fp3=fopen("Ogrenciler.txt","r");
				fseek(fp3,pos,SEEK_SET);
				fgets(line2,LINESIZE-1,fp3);
				sscanf(line2,"%s %s %s ",idtmp,name,surname);
				/*putSpaces(name); putSpaces(surname);*/
				fprintf(fp2,"%s %s %s \n",idtmp,name,surname);
				fclose(fp3);
			}
		}
	}
	fclose(fp); fclose(fp2); 
	free(line); free(line2);
	free(name); free(surname);free(kodtmp); free(idtmp);
	
	return 1;
		
}


/*This function displays all the student that are taking this course*/
int ListDersOgrc(){
	char* kod= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the code of the course: ");
	/*Check if the course exists*/
	scanf(" %s",kod); uppercase(kod);
	if(search("Dersler.txt",kod)==-1){
		printf("\nThis code does not match any course. Please check your information!");
		free(kod);
		return FAIL;
	}
	if(findAllStudents(kod)){
		/*Check if the file is empty*/
		FILE *fp= fopen("Students.txt","r");
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0){
			printf("\nNo student is registered in this course!");
			fclose(fp);	remove("Students.txt");
			free(kod);
			return FAIL;
		}
		fclose(fp);
		/*The file is not empty*/
		printf("\nThe students registered in the course %s are:\n",kod);
		display("Students.txt");
		remove("Students.txt");
	}
	free(kod);
	return 1;
}
/*This function finds all the courses taken by the student id*/
int findAllCoursesForStd(char* id){
	FILE *fp, *fp2, *fp3;
	fp=fopen("OgrenciDersKayit.txt","r");
	if(fp==NULL) return FAIL; /*no enrollments*/
	fp2= fopen("Courses.txt","w+");
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	char* line2= (char*) malloc(sizeof(char)*LINESIZE);
	char* kodtmp= (char*) malloc(sizeof(char)*ID);
	char* idtmp=(char*) malloc(sizeof(char)*ID);
	char* name=(char*) malloc(sizeof(char)*SIZE);
	int counter, durum;
	long pos;
	while(fgets(line,LINESIZE-1,fp)!=NULL){
		sscanf(line,"%d %s %s %d",&counter, kodtmp,idtmp,&durum);
		if(strcmp(id,idtmp)==0 && durum==1){
			pos=search("Dersler.txt",kodtmp);
			if(pos!=-1){
				fp3=fopen("Dersler.txt","r");
				fseek(fp3,pos,SEEK_SET);
				fgets(line2,LINESIZE-1,fp3);
				sscanf(line2,"%s %s ",kodtmp,name);
				fprintf(fp2,"%s %s\n",kodtmp,name);
				fclose(fp3);
			}
			
		}
	}
	fclose(fp); fclose(fp2); 
	free(line); free(line2);
	free(kodtmp); free(idtmp); free(name);
	return 1;
	
}


/*This function displays all the courses taken by the student of ID*/

int ListOgrcDers(){
	char* id= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the student ID: ");
	scanf(" %s",id); uppercase(id);
	if(search("Ogrenciler.txt",id)==-1){
		printf("\nThis ID does not match any student. Please check your information!");
		free(id);
		return FAIL;
	}
	if(findAllCoursesForStd(id)){
		/*Check if the file is empty*/
		FILE *fp= fopen("Courses.txt","r");
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0){
			printf("\nThis student is not enrolled in any course!");
			fclose(fp);	remove("Courses.txt");
			free(id);
			return FAIL;
		}
		fclose(fp);
		/*File is not empty*/
		
		printf("\nThe courses that the student %s is taking are:\n",id);
		display("Courses.txt");
		remove("Courses.txt");
	}
	free(id);
	return 1;
	
}
int ClassList(){
	
	char* id= (char*) malloc(sizeof(char)*ID);
	printf("\nPlease enter the ID of the lecturer: ");
	scanf(" %s",id); uppercase(id);
	/*Check if the lecturer exists */	
	if(search("ogretimUyesi.txt",id)==-1){
		printf("\nThis ID does not match any lecturer. Please check your information! ");
		free(id);
		return FAIL;
	}
	
	char* kod= (char*) malloc(sizeof(char)*30);
	long pos; /*Used to point to the position of the cource in Dersler.txt file*/
	printf("\nPlease enter the code of the course: ");
	/*Check if the course exists*/
	scanf(" %s",kod); uppercase(kod);
	pos =search("Dersler.txt",kod);
	if(pos==-1){
		printf("\nThis code does not match any course. Please check your information!");
		free(kod); free(id);
		return FAIL;
	}
	/*Check if the course is given by the instructor*/
	FILE *fp=fopen("Dersler.txt","r");
	DERS* ders= (DERS*) malloc(sizeof(DERS));
	char* line= (char*)malloc(sizeof(char)*LINESIZE);
	fseek(fp,pos,SEEK_SET);
	fgets(line,LINESIZE-1,fp);
	sscanf(line,"%s %s %d %d %d %s\n",ders->dersKodu,ders->ad,&ders->kredi,&ders->kapasite,&ders->kontenjan,ders->dersVeren);
	
	if(strcmp(ders->dersVeren,id)!=0){
		printf("\nError: This course is not given by this lecturer! please check your information! ");
		free(ders); free(kod);
		return FAIL;
	}
	/*********/
	free(ders);
	fclose(fp); free(line);
	if(findAllStudents(kod)){
		strcat(kod,"_SINIFLISTESI.txt");
		rename("Students.txt",kod);
		printf("\n%s File was successfully created.",kod);
	}
	else{
		printf("\nStudents could not be found! Probably no student is registered yet!");
	}
	free(kod);
	free(id);
	return 1;
	
}
/*Function to display the content of a file */

int display(char* name){
	FILE *fp= fopen(name,"r");
	if(fp==NULL){
		printf("Error: Failed to access the %s file.",name);
		return FAIL;
	} 
	/*File exists*/
	char* line= (char*) malloc(sizeof(char)*LINESIZE);
	while(fgets(line,LINESIZE-1,fp)!=NULL){
		putSpaces(line);
		printf("%s",line);
	}
	free(line); fclose(fp);
	return 1;
}
void remove_spaces(char* s) {
    const char* tmp = s;
    do {
        while (*tmp == ' ') {
        	*s++='_';
            ++tmp;
        }
    } while ((*s++ = *tmp++));
}
void putSpaces(char* s) {
    const char* tmp = s;
    do {
        while (*tmp == '_') {
        	*s++=' ';
            ++tmp;
        }
    } while ((*s++ = *tmp++));
}
void uppercase(char* s){
	do{
		if (*s>='a' && *s<='z'){
			*s=*s-32;
		}	
	}while(*s++);
}

