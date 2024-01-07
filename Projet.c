#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int info;
	struct Node* next;
}Node;

typedef Node* File;

void InitFile(File* p){
	(*p)=NULL;
}

bool FileVide(File p){
	if(p==NULL) return true;
	return false;
}

int SommetFile(File p){
	return p->info;
}

void Enfiler(File* p, int x){
	File t,q;
	t=(File)malloc(sizeof(Node));
	t->info=x;
	t->next=NULL;
	if(*p!=NULL){
		q=(*p);
		while(q->next!=NULL){
			q=q->next;
		}
		q->next=t;
	}else{
		*p=t;
	}
}

void Desenfiler(File* p, int* x){
	File t;
	(*x)=(*p)->info;
	t=(*p);
	(*p)=(*p)->next;
	free(t);	
}

void RemplirFile(File* p, int n){
	int i,x;
	for(i=0;i<n;i++){
		printf("give element %d\n",i+1);
		scanf("%d",&x);
		Enfiler(p,x);
	}
}

void AfficherFile(File p){
	File t;
	InitFile(&t);
	int x;
	while(!FileVide(p)){
		Desenfiler(&p,&x);
		printf("->%d",x);
		Enfiler(&t,x);
	}
	printf("\n");
	while(!FileVide(t)){
		Desenfiler(&t,&x);
		Enfiler(&p,x);
	}	
}

bool RechercherVal(File p, int v){
	bool found=false;
	int x;
	File t;
	InitFile(&t);
	while(!FileVide(p)){
		Desenfiler(&p,&x);
		Enfiler(&t,x);
		if(x==v){
			found=true;
		}
	}
	while(!FileVide(t)){
		Desenfiler(&t,&x);
		Enfiler(&p,x);
	}
	return found;
}

void Remplacer(File* p, int val1, int val2){
	File t;
	InitFile(&t);
	int x;
	while(!FileVide(*p)){
		Desenfiler(p,&x);
		if(x==val1){
			Enfiler(&t,val2);
		}else{
			Enfiler(&t,x);
		}
	}
	while(!FileVide(t)){
		Desenfiler(&t,&x);
		Enfiler(p,x);
	}
} 

void Inserer(File* p, int k, int val){
	File t;
	InitFile(&t);
	int x,i=1;
	
	while(!FileVide(*p) && i<k){
		Desenfiler(p,&x);
		Enfiler(&t,x);
		i++;
	}
	Enfiler(&t,val);
	while(!FileVide(*p)){
		Desenfiler(p,&x);
		Enfiler(&t,x);
	}
	while(!FileVide(t)){
		Desenfiler(&t,&x);
		Enfiler(p,x);
	}
}

File Fusion(File a, File b){
	File t,t1,t2;
	InitFile(&t);
	InitFile(&t1);
	InitFile(&t2);
	int x;
	while(!FileVide(a) && !FileVide(b)){
		if(SommetFile(a)<SommetFile(b)){
			Desenfiler(&a,&x);
			Enfiler(&t,x);
			Enfiler(&t1,x);
		}else{
			Desenfiler(&b,&x);
			Enfiler(&t,x);
			Enfiler(&t2,x);
		}
	}
	while(!FileVide(a)){
		Desenfiler(&a,&x);
		Enfiler(&t,x);
		Enfiler(&t1,x);
	}
	while(!FileVide(b)){
		Desenfiler(&b,&x);
		Enfiler(&t,x);
		Enfiler(&t2,x);
	}
	while(!FileVide(t1)){
		Desenfiler(&t1,&x);
		Enfiler(&a,x);
	}
	while(!FileVide(t2)){
		Desenfiler(&t2,&x);
		Enfiler(&b,x);
	}
	return t;
}

void Fractionner(File* p, File* op, File* ou){
	int x;
	File t1,t2,t3;
	InitFile(&t1);
	InitFile(&t2);
	InitFile(&t3);
	while(!FileVide(*p)){
		Desenfiler(p,&x);
		if(x%2==0){
			Enfiler(&t1,x);
			Enfiler(&t3,x);
		}else{
			Enfiler(&t2,x);
			Enfiler(&t3,x);
		}
	}
	while(!FileVide(t1)){
		Desenfiler(&t1,&x);
		Enfiler(op,x);
	}
	while(!FileVide(t2)){
		Desenfiler(&t2,&x);
		Enfiler(ou,x);
	}
	while(!FileVide(t3)){
		Desenfiler(&t3,&x);
		Enfiler(p,x);
	}
}
