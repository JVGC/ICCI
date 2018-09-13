#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define D_CA 10 // CA do Drizzt
#define A_CA 7 // CA da Artemis


int main(){
	
	int luta, luta_D=0, luta_A=0; // luta EH A VARIAVEL QUE CONTEM O NUMERO DE LUTAS , E luta_D e luta_A SAO OS CONTADORES DE LUTAS GANHAS POR CADA PERSONAGEM
	int V_D; // PONTOS DE VIDA DO DRIZZT
	int V_A; // PONTOS DE VIDA DA ARTEMIS
	int DDA, DDA_A, DDA_D; // DDA EH O NUMERO DE FACES DOS DADOS(QUE VAI DAR ORIGEM A SEED DO SRAND), E OS OUTROS DOIS SAO OS DADOS QUE CADA UM IRA JOGAR
	int i,aux=0; // VARIAVEIS AUXILIARES
	int Ordem_D, Ordem_A; // VARIAVEIS QUE TEM O VALOR DOS DDA JOGADOS PARA DETERMINAR A ORDEM DAS LUTAS
	int FA_A=0, FA_D=0; // FORÇA DE ATAQUE DE DRIZZT E ARTEMIS, RESPECTIVAMENTE
	int aux2,aux3;
	
	//LENDO O NUMERO DE LUTAS, A VIDA DE DRIZZT E ARTEMIS E O NUMERO DE FACES DO DDA
	
	scanf ("%d", &luta);
	scanf ("%d", &V_D);
	scanf ("%d", &V_A);
	scanf ("%d", &DDA);	
	
	// GUARDANDO EM DUAS VARIAVEIS AUXILIARES(aux2 e aux3) O VALOR DOS PONTOS DE VIDA DO DRIZZT E DA ARTEMIS
	// ESSAS VARIAVEIS SERAO UTILIZADAS PARA RESETAR A VIDA DOS PERSONAGENS
	
	aux2=V_D; 
	aux3=V_A;
	
	srand(DDA*DDA); // SEED DA BATALHA
	
// ESSE FOR VAI DE 1 ATE O NUMERO DE BATALHAS MAXIMO POSSIVEL
	for(i=1;i<=luta;i++){
		
		
		// A CADA COMEÇO DE UMA LUTA AS ORDENS SAO DECIDIDAS JOGANDO OS DDA
	
			Ordem_D = 1+rand()%DDA;
			Ordem_A = 1+rand()%DDA;
		
			printf("Luta %d\n",i);
			
		// RESETANDO AS VIDAS DOS PERSONAGENS ATRAVES DAS VARIAVEIS AUXILIARES A CADA COMEÇO DE LUTA
			V_D= aux2;
			V_A= aux3;
			
		// O WHILE EH USADO PARA MANTER AS JOGADAS SE ALTERNANDO ATE QUE UM DELES TENHA VIDA <=0
			while(V_D>0 && V_A>0){
		
			// SE O DADO DA ORDEM DA ARTEMIS FOR MAIOR QUE O DO DRIZZT, ELA COMEÇA JOGANDO
				if(Ordem_A>Ordem_D){
				//RODANDO O DDA DA ARTEMIS
					DDA_A = 1+ rand()%DDA;
		 			// SE O DDA DA ARTEMIS FOR MAIOR QUE O CA DO DRIZZT, ELA PODE ATACAR
		 				if(DDA_A>D_CA){
		 					
						//RODANDO OS 2d7 QUE ARTEMIS TEM DIREITO EM SUA VEZ
						
						 	FA_A = 1+rand()%7;
		 					FA_A = FA_A + (1+rand()%7);
		 							
						 
						 	
						//SE OS VALORES DOS DADOS FOREM MAXIMOS(14), ELA TIRA 14+(14/2)=21 DE DANO
							if(FA_A==14){
		 						FA_A =21;
								V_D=V_D-21;
								printf("Artemis 21\n");	
							
						//SE O DANO FOR MENOR QUE DOIS, ELA ERRA O ATAQUE, E CASO CONTRARIO, O DANO EH CALCULADO NORMALMENTE		 	
							 }else if (FA_A>2){
								V_D= V_D - FA_A;
								printf("Artemis %d\n", FA_A);
							 } 	
		 			}
		 			
		 		//USANDO UMA VARIAVEL AUXILIAR PARA TROCAR OS VALORES DOS DADOS DE ORDEM, E ASSIM ALTERNAR AS JOGADAS	
					aux=Ordem_A;
					Ordem_A=Ordem_D;
					Ordem_D=aux;
				
				
				// O VALOR DO DANO DA ARTEMIS EH RESETADO TODA VEZ QUE ELA JOGAR
				// ISSO PARA NAO INTEFERIR NO DADO DE DANO DA PROXIMA VEZ DELA
					FA_A = 0;
				
			//CASO O DDA DE ORDEM DE DRIZZT FOR MAIOR OU IGUAL AO DA ARTEMIS ELE COMEÇA		
				}else{
				//RODANDO O DDA DE DRIZZT
					DDA_D = 1+rand()%DDA;
				
				//SE O VALOR DO DADO FOR MAIOR QUE A CLASSE DE ARMADURA(CA) DE ARTEMIS, ELE PODE ATACAR
					if(DDA_D>A_CA){
					//RODANDO O DADO DE FORÇA DE ATAQUE DO DRIZZT(FA)
		 				FA_D = 1+rand()%9;
		 		
					// SE O VALOR DO DADO FOR MAXIMO(9), ELE TIRA 9+(9/2)=13 DE DANO					 
				 		if(FA_D==9){
		 					FA_D =13;
							V_A=V_A-13;
							printf("Drizzt %d\n", FA_D);			  		
					
					//SE O DANO FOR MENOR QUE UM, ELE ERRA O ATAQUE, E CASO CONTRARIO, O DANO EH CALCULADO NORMALMENTE			
					 }else if(FA_D>1){
					 	V_A = V_A - FA_D;
					 	printf("Drizzt %d\n", FA_D);
					 }
				
					}
				//USANDO UMA VARIAVEL AUXILIAR PARA TROCAR OS VALORES DOS DADOS DE ORDEM, E ASSIM ALTERNAR AS JOGADAS	
					aux=Ordem_D;
					Ordem_D=Ordem_A;
					Ordem_A=aux+1;	
				// O +1 AQUI EH PARA GARANTIR QUE NA PROXIMA RODADA OS VALORES SEJAM IGUAIS DE NOVO, E ASSIM DRIZZT NAO JOGUE DUAS VEZES SEGUIDAS
				}
		
			//SE A VIDA DE UM DOS DOIS FOR MENOR OU IGUAL A 0, O OUTRO EH O VENCEDOR DA LUTA		
				if(V_D<=0){
					printf("Fim da luta. Vencedor: Artemis\n");
					luta_A++;
				}else if(V_A<=0){
					printf("Fim da luta. Vencedor: Drizzt\n");	 
					luta_D++;
				}
			
			
			}
			//SE UM DOS DOIS TIVEREM VENCIDOS MAIS DA METADE DAS LUTAS((NUMERO DE LUTAS/2)+1), A BATALHA ACABA, E FOR EH FINALIZADO
		if(luta_D==((luta/2)+1)){
			printf("Fim da batalha. Vencedor: DRIZZT\n");
			break;
		}else if(luta_A==((luta/2)+1)){
			printf("Fim da batalha. Vencedor: ARTEMIS\n");
			break;
		}
		
		
	}
	
	return 0;
	
}
