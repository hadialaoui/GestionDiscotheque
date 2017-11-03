#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure de donnee d'un album
typedef struct donnee{
	char  titre [20];
    char  interprete [20];
    char  label [20];
    char  date [20];
    char  style_music [20];
}donnee;

//structure d 'un album
typedef struct album{
	int cle;
	donnee* d;
    struct album *gauche;
    struct album *droit;
}album; 



//fonction permet de creer un pointeur de donnees d'un album
donnee* creer_donnee(char  titre [20],char  interprete [20],char  label [20],char  date [20],char  style_music [20]){
     donnee* d=(donnee*)malloc(sizeof(donnee));
    strcpy(d->titre,titre);
	strcpy(d->interprete,interprete);
	strcpy(d->label,label);
	strcpy(d->date,date);
	strcpy(d->style_music,style_music);
	return d;
}

//fonction permet de creer noeud pour un nouveau album
album* creerAlbum(int cle,donnee* d){
	album* nouveau=(album*)malloc(sizeof(album));
	nouveau->cle=cle;
	nouveau->d=creer_donnee(d->titre,d->interprete,d->label,d->date,d->style_music);
	
	
	nouveau->droit=NULL;
	nouveau->gauche=NULL;
	
	return nouveau;
}

//fonction recursive pour affecter un album par un recherche en profondeur
album* rec_rech(album *nouveau ,album *racine,album *temp){
 if(racine==NULL) return nouveau;
 if(nouveau->cle==temp->cle)	printf("Album existe deja !");
 else if(nouveau->cle < temp->cle){
	    	if(temp->gauche==NULL)
	 	    temp->gauche=nouveau;
	    	else
	 	    rec_rech(nouveau,racine,temp->gauche);
 }else{
	 		if(temp->droit==NULL)
	 	    temp->droit=nouveau;
	     	else
	 	    rec_rech(nouveau,racine,temp->droit);
	 }
 return racine;
 
}
//fonction de recherche permet de trouver un album dons l'arbre
album* rech_album(int cle , album* racine){
	if(racine->cle==cle)
	return racine;
	else if(cle < racine->cle){
		if(racine->gauche!=NULL)
		return rech_album(cle,racine->gauche);
		else
		return NULL;
	}else{
		if(racine->droit!=NULL)
		return rech_album(cle,racine->droit);
		else
		return NULL;
	}
}

//fonction pour ajouter un album dans l'arbre
album* ajouter_album(int cle,donnee *d ,album *racine){
	album* nouveau=creerAlbum(cle,d);	
	return rec_rech(nouveau,racine,racine); 
}	

//procedure pour afficher les albums de discotheque(les elements de l)
void afficher_preFix(album* racine){
	printf("***********album : %s ************\n",racine->d->titre);
	printf("titre : %s \t",racine->d->titre);
	printf("interprete : %s \t",racine->d->interprete);
	printf("date : %s \t",racine->d->date);
	printf("style_music : %s \n",racine->d->style_music);
	
	if(racine->gauche!=NULL) afficher_preFix(racine->gauche);
	if(racine->droit!=NULL) afficher_preFix(racine->droit);
}

//procedure pour afficher un album de discothequ
void afficher_album(album* album){
	printf("***********album : %s ************\n",album->d->titre);
	printf("titre : %s \t",album->d->titre);
	printf("interprete : %s \t",album->d->interprete);
	printf("date : %s \t",album->d->date);
	printf("style_music : %s \n",album->d->style_music);

}

//fonction de plus grand cle 
album* plusGrand(album* alb){
	if(alb->droit==NULL)
	    return alb;
	else
	    return plusGrand(alb->droit);
}

//fonction recursif de suppression
album* suppression(int cle, album* racine){
	album* albSupp=rech_album(cle,racine);
	album* local, *noeud;
		if(racine==NULL){
			printf("l'album non trouvé dans la discotheque !!");
			return NULL;
		}else{
			
			if(cle<racine->cle){
				suppression(cle,racine->gauche);//on cherche a gauche
			}else{
			
			   if(cle>racine->cle){
			   	suppression(cle,racine->droit);//on cherche a droite
			   }else{//l'album est dans ce noeud
			   	   if(racine->gauche==NULL){//sous-arbre gauche vide
			   	         local=racine;
			   	         racine=racine->droit;//remplacer arbre par son sous-arbre droit
			   	         //dispose(local)
			   	         return local;
				    }else{
					
				   	       if(racine->droit==NULL){//sous-arbre droit vide
				   	           local=racine;
							   racine=racine->gauche;//remplacer arbre par son sous-arbre gauche
				   	           //dispose(local)
				   	           return local;
							}else{ //le noeud a deux descendant
				   	          noeud=plusGrand(racine->gauche);
				   	          local=noeud;
				   	          racine->cle=noeud->cle;
				   	          racine->gauche=noeud->gauche;
				   	          //dispose(local)
				   	          return local;
				   	      }
					}
			   }
			}
		}
}

int main(){
	//declaration des variables
	    int key;
	   char  titre [20];
	   char  interprete [20];
	   char  label [20];
	   char  date [20];
	   char  style_music [20];
		int choix_int = -1;
		album *alb=NULL;
		
		while (choix_int != 0) {
		printf("\n\n--------------\n");
		printf("MENU PRINCIPAL\n");
		printf("--------------\n\n");
		
		printf("Que voulez-vous faire ?\n");
		printf("1 - ajouter un album \n");
		printf("2 - afficher tous les albums \n");
		printf("3 - rechercher un album\n");
		printf("4 - supprimer un album\n");
		printf("5 - detruire discotheque\n");
		printf("0 - Quitter\n");
		printf("----\n");
		//scanf("%d", &choix_int);
		scanf("%d", &choix_int);
		
	
		switch (choix_int)
		{
			case 1: {
				printf("---- numero : ");scanf("%d",&key);
			     printf("---- Titre : ");scanf("%s",titre);
			     printf("---- Interprete : ");scanf("%s",interprete);
			     printf("---- Label : ");scanf("%s",label);
			     printf("---- date : ");scanf("%s",date);
			     printf("---- style_music : ");scanf("%s",style_music);
			     donnee* d1=creer_donnee(titre,interprete,label,date,style_music);
			     if(alb==NULL){
			     	alb=creerAlbum(key,d1);
				 }else{
				 	ajouter_album(key ,d1,alb);
				 }
				break;
			}
			case 2:
				  if(alb==NULL){
				  	printf("Aucun album existe !!!");
				  	break;
				  }else{
				  	afficher_preFix(alb); break;
				  }
			case 3:{
				printf("Veuillez saisir le numero d'album : ");scanf("%d",&key);
				album *albRech=rech_album(key,alb);
				if(albRech!=NULL)
				afficher_album(albRech);
				else
				printf("cet album n'existe pas !!!'");
				break;
			}
			case 4:{
				printf("Veuillez saisir le numero d'album : ");scanf("%d",&key);
				album *albRech=rech_album(key,alb);
				if(albRech!=NULL){
				albRech=suppression(key,alb);
				afficher_album(albRech);
				}
				else
				printf("cet album n'existe pas !!!'");
				break;
			}
			case 5:{
				alb=NULL;
				break;
			}
			default : printf("Erreur de choix"); break; 	      
		}
    } 

	
	return 0;
}
