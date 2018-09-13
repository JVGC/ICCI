#include <stdio.h>
#include <stdlib.h>

void imprimeResposta(int* Resposta, int cont){

	// imprimindo o vetor resposta
	int i;
	for(i=0;i<cont;i++){
	
		printf("%d ", Resposta[i]); 
	}
	printf("\n");

}

void LerMatriz(int(*Labirinto)[7])
{
	// lendo a matriz Labirinto
	int i, j;
	for (i=0;i<7;i++){
	
		for (j=0;j<7;j++){
		
			scanf("%d", &Labirinto[i][j]); 
		}
	}
}



int main(){


	int Labirinto[7][7]; // matriz que será preenchida com os 0 e 1 do labirinto
	int Resposta[49]; // vetor que guardará o menor caminho do labirinto
	int inicio, posicaoI,posicaoJ,Iinicial,Jinicial; 
	// Respectivamente: variavel que guarda a posicao inicial, I e J que vao caminhando durante o labirinto, e I e J da posicao inicial
	int  i, j, cont=1; // variaveis I e J auxiliares, e um contador que contará o numero de casas andadas para chegar a saida. Começa em 1, a casa 0 eh a inicial

	LerMatriz(Labirinto); // Lendo a matriz por meio de uma funcao

	scanf("%d", &inicio); // lendo a posicao inicial

	// o primeiro IF verifica se a posicao inicial esta na primeira linha
	if(inicio>=0 && inicio<=6){
			
		i=0;
		j=0;
		while(1){
		
			// se estiver na primeira linha, procuro o 0 para começar e defino a posição i,j desse 0 como a inicial 
			if(Labirinto[i][j]==0){
			

				Iinicial=0;
				Jinicial=j; 
				break;

			}
			j++; // movendo de coluna em coluna ate achar o 0
		}
		// se nao estiver na primeira linha, testo para ver se ele esta na ultima
	}else if(inicio>=42 && inicio<=48){
	
		i=6;
		j=0;
		while(1){
		
			// se estiver na ultima linha, procuro o 0 para começar e defino a posição i,j desse 0 como a inicial 
			if(Labirinto[i][j]==0){
			

				Iinicial=6;
				Jinicial=j;
				break;

			}
			j++; // movendo de coluna em coluna ate achar o 0
		}

	}else if(inicio%7==0){ // se o valor inicial for divisivel por 7, entao ele esta na primeira coluna da matriz
	
		i=0;
		j=0;
		while(1){
		
			// se estiver na primeira coluna, procuro o 0 para começar e defino a posição i,j desse 0 como a inicial 
			if(Labirinto[i][j]==0){
			

				Iinicial=i;
				Jinicial=0;
				break;

			}
			i++; // movendo de linha em linha ate achar o 0
		}

	}else{ // se nao estiver em nenhuma das opcoes anteriores, entao a posicao inicial esta na ultima coluna
		i=0;
		j=6;
		while(1){
		
			// portanto a posição inicial terá j=6 e i igual a linha em que estiver localizado o 0
			if(Labirinto[i][j]==0){
			

				Iinicial=i;
				Jinicial=6;
				break;

			}
			i++; // movendo de linha em linha ate achar o 0
		}
	}	


	int posicaoANT=inicio; // declaro uma variavel posicaoANT para ir guardando o valor da posicao passada, para que nao volte a posicao anterior e 
	//depois va de novo para frente, evitando o loop infinito
	Resposta[0]= inicio; // o vetor resposta sempre terá na sua primeira posição o valor inicial dado pelo usuario
	posicaoI=Iinicial; // A posição inicial é igual ao I inicial e ao J inicial
	posicaoJ=Jinicial;

	// esse Do/while vai executar pelo menos uma vez o código para andar pelas nas direções
	// Há um padrão de movimentos a serem testados: cima, esquerda, direita, baixo (nessa sequencia)
	// (Só passa para o próximo movimento caso a direção anterior não possua um 0)


	do{	

		// testando se há uma posição livre acima da que eu estou no labirinto
		// As condições são de que haja um 0 na posição acima(i-1) e que essa posição não seja a posicao anterior(posicaoANT)
		// Há um caso especifico, onde eu posso comecar na linha 0 e acima da minha matriz a um lixo=0, 
		// para evitar isso, houve a necessidade de se especificar uma condicao para que ele nao saisse do campo da matriz,
		// que no caso é a primeira condicao especificada no IF

		if(((posicaoI-1)>=0)&&(Labirinto[posicaoI-1][posicaoJ]==0) && (((posicaoI-1)*7 + posicaoJ) != posicaoANT)){
		
			//se for 0
			posicaoANT= (posicaoI*7) + posicaoJ; // marca a posicao atual como a anterior

			posicaoI-=1; // anda para cima
			Resposta[cont] = (posicaoI*7) + posicaoJ; // marca a posicao no vetor resposta

			cont++; // passa para a proxima posicao do vetor resposta

		}
		// testando se há uma posição livre a esquerda da que eu estou no labirinto
		// As condições são de que haja um 0 na posição a esquerda(j-1) e que essa posição não seja a posicao anterior(posicaoANT)

		else if((Labirinto[posicaoI][posicaoJ-1]==0) && ((posicaoI*7 + (posicaoJ-1)) != posicaoANT) ){
			
			//se for 0
			posicaoANT=(posicaoI*7) + posicaoJ; // marca a posicao atual como a anterior
			posicaoJ-=1; // anda para a esquerda
			Resposta[cont] = (posicaoI*7) + posicaoJ;  // marca a posicao no vetor resposta

			cont++;// passa para a proxima posicao do vetor resposta

		}
		// testando se há uma posição livre a direita da que eu estou no labirinto
		// As condições são de que haja um 0 na posição a direita(j+1) e que essa posição não seja a posicao anterior(posicaoANT)

		else if((Labirinto[posicaoI][posicaoJ+1]==0) && ((posicaoI*7 + (posicaoJ+1))!= posicaoANT)){
		
			//se for 0
			posicaoANT=posicaoI*7 + posicaoJ; // marca a posicao atual como a anterior

			posicaoJ+=1; // anda para a direita
			Resposta[cont] = (posicaoI*7) + posicaoJ; // marca a posicao no vetor resposta

			cont++; // passa para a proxima posicao do vetor resposta


		}	
		// testando se há uma posição livre abaixo da que eu estou no labirinto
		// As condições são de que haja um 0 na posição abaixo(i+1) e que essa posição não seja a posicao anterior(posicaoANT)

		else if((Labirinto[posicaoI+1][posicaoJ]==0 ) && (((posicaoI+1)*7 + posicaoJ) != posicaoANT)){
		
			//se for 0
			posicaoANT=posicaoI*7 + posicaoJ; // marca a posicao atual como a anterior

			posicaoI+=1; // anda para baixo
			Resposta[cont] = (posicaoI*7) + posicaoJ; // marca a posicao no vetor resposta

			cont++; // passa para a proxima posicao do vetor resposta

		}

		// se não tiver nenhuma posicao livre, ou seja, igual a 0, em torno da posicao atual que nao seja a posicao anterior dele
		// quer dizer que achou um caminho sem saida
		// nesse caso, seta-se a posicao atual, e volta para a inicial
		else{
		
			cont =1; // reseta a contagem
			Labirinto[posicaoI][posicaoJ]=1; // setando a posicao atual
			posicaoI=Iinicial;// volta para o Iinicial
			posicaoJ=Jinicial; // volta para o Jinicial
			posicaoANT=inicio;// marca posicaoANT como a inicial novamente




		}
		// esse if serve para testar se a posicao em que estou no  labirinto é uma extremida da matriz
		if(((posicaoI==0) || (posicaoI==6 )) || ((posicaoJ==6) || (posicaoJ==0) )){
		
			//caso seja, esse extremidade tem que ser diferente da inicial
			// pois como foi especificado no trabalho, há somente dois 0 nas extremidades, a saida e a entrada do labirinto
			if(posicaoI*7 + posicaoJ!= inicio) 
				// caso entre aqui, encontrou a saida do labirinto
				// sai do do/while
				break;
		}
	}while(1);



	imprimeResposta(Resposta, cont); // chama a função para a imprimir o vetor resposta, passando o vetor e o tamanho dele como parametros
	// a variável cont possui o tamanho do vetor resposta

	return 0;
}
