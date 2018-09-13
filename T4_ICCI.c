/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TRABALHO 4 DE ICC 1 - 2017 - 1 SEMESTRE 
  UNIVERSIDADE DE SAO PAULO(USP) - CAMPUS SAO CARLOS

  NOME DO ALUNO: JOAO VICTOR GARCIA COELHO
  PROFESSOR: JOAO BATISTA

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// STRUCT QUE GUARDA TODO O CONTEUDO DA IMAGEM
typedef struct _imagem { 
	char tipo; // TIPO DA IMAGEM: 2 PARA ASCII E 5 PARA BINARIO       
	int XDIM; // LARGURA DA IMAGEM
	int YDIM; // ALTURA DA IMAGEM
	int MaxVal; //VALOR MAXIMO DE UM PIXEL DE UMA IMAGEM(NO FORMATO "PGM", O VALOR É 255)
	unsigned char *data; // PONTEIRO PARA UNSIGNED CHAR QUE SERA USADO PARA ALOCAR DINAMICAMENTE O VETOR DE PIXELS

}imagem; 

//////////////////////////////////////////////////HEADERS DAS FUNCOES/////////////////////////////////////////////////////////////////////////

FILE* LOADImage(char *file_name, imagem* img); // FUNÇÃO QUE ABRE O ARQUIVO
void read(imagem* img, FILE* arquivo); // FUNÇAO QUE LE O HEADER DA IMAGEM E SEUS RESPECTIVOS PIXELS(CHAMADA DENTRO DA FUNÇAO LOADImage)
unsigned char* alloca(imagem* img); // FUNCAO QUE ALOCA O VETOR DE PIXELS DINAMICAMENTE

void saveimage(imagem* img, int operacao); // FUNCAO QUE SALVA A IMAGEM(PRINTA O HEADER E OS NOVOS PIXELS NA TELA)

void Image_log(imagem* aux); // CASO A OPERACAO DE MUDANCA DA IMAGEM SEJA 1, ESSA FUNCAO É CHAMADA PARA ALTERAR A IMAGEM
void Image_Contrast(imagem* aux); // CASO A OPERACAO DE MUDANCA DA IMAGEM SEJA 2, ESSA FUNCAO É CHAMADA PARA ALTERAR A IMAGEM
void paint_brush(imagem* img, int x, int y); // CASO A OPERACAO DE MUDANCA DA IMAGEM SEJA 3, ESSA FUNCAO É CHAMADA PARA ALTERAR A IMAGEM

int menor(imagem* aux2); // FUNCAO QUE RETORNA O MENOR VALOR DE UM PIXEL NA IMAGEM
int maior(imagem* aux2); // FUNCAO QUE RETORNA O MAIOR VALOR DE UM PIXEL NA IMAGEM

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	imagem img; 
	int operacao; // VARIAVEL QUE CONTEM A OPERACAO A SER FEITA PARA ALTERAR A IMAGEM
	scanf("%d", &operacao);
	char filename[100]; // STRING QUE CONTEM O NOME DO ARQUIVO A SER ABERTO
	scanf("%s", filename); 

	FILE *arquivo = LOADImage(filename, &img);  

	fclose(arquivo); 
	saveimage(&img, operacao); 
	free(img.data); 
	return 0;
}


///////////////////////////////////////////////////FUNCOES QUE LEEM ABREM E LEEM A IMAGEM/////////////////////////////////////////////////////


FILE* LOADImage(char *file_name, imagem* img){ 

	// ABERTURA DO ARQUIVO. 'file_name' CONTEM O NOME DO ARQUIVO, E ABRE A IMAGEM COM O MODO rb POIS A IMAGEM PODE ESTAR EM MODO BINARIO
	FILE*arquivo = fopen(file_name,"rb"); 

	read(img,arquivo); 

	return arquivo; // RETORNA PARA A MAIN, RETORNANDO O PONTEIRO UTILIZADO PARA ABRIR O ARQUIVO
}


void read(imagem* img, FILE* arquivo){

	char coment; // CHAR PARA LER OS CARACTERES DO COMENTARIO; SERA USADO PARA "IGNORAR" O COMENTARIO DO ARQUIVO
	fscanf(arquivo, "P%c", & img->tipo); // LE O NUMERO DO TIPO DO ARQUIVO(EX: P'2');
	fscanf(arquivo, " %c", &coment); // LE O PROXIMO CARACTER


	if(coment == '#'){ // TODO COMENTARIO COMECA COM O'#', ENTAO SE HOUVER COMENTARIO ELE ENTRA NO WHILE 
	
		// LE OS CARACTERES DO COMENTARIO ATE HOUVER UMA QUEBRA DE LINHA('\n')
		while(coment!='\n'){
		
			fscanf(arquivo, "%c", &coment); 
		}
		fscanf(arquivo, "%d", &img->XDIM); // LE O XDIM DA IMAGEM

	}else{ // CASO NAO HOUVER COMENTARIO, QUER DIZER QUE O CARACTER LIDO PELO 'COMENT', ERA O XDIM DA IMAGEM
		// ENTAO ATRIBUI AO XDIM, O VALOR LIDO
		img->XDIM=(int)coment;
	}

	fscanf(arquivo, "%d", &img->YDIM); 
	fscanf(arquivo, "%d\n", &img->MaxVal);
	img->data = alloca(img); // ALOCA O VETOR DE PIXELS

	if(img->tipo=='2'){ // SE A IMAGEM FOR DO TIPO ASCII
		int i;
		for (i=0;i<(img->XDIM*img->YDIM);i++){
		
			fscanf(arquivo, "%hhu", &img->data[i]); // LE OS PIXELS DA IMAGEM
		}
	}
	else if(img->tipo=='5'){ // SE A IMAGEM FOR DO TIPO BINARIO
	
		fread(&img->data[0],sizeof(img->data),img->XDIM*img->YDIM, arquivo);	// LE TODOS OS PIXELS DA IMAGEM E ARMAZENA NO VETOR ALOCADO
	}
}

unsigned char* alloca(imagem* img){

	unsigned char* aux=(unsigned char*) malloc(sizeof(unsigned char) * (img->XDIM*img->YDIM));  
	return aux;
}


////////////////////////////////////////////////////FUNCOES QUE SALVAM E IMPRIMEM A IMAGEM////////////////////////////////////////////////////


void saveimage(imagem* img, int operacao){ 
	
	int Xc, Yc;
	switch(operacao){
	
		case 1:
		Image_log(img); //OPERACAO DE LOG
		break;
		
		case 2:
		Image_Contrast(img); // OPERACAO DE CONTRASTE 
		break;
		
		case 3:
		Xc = img->XDIM/2;
		Yc = img->YDIM/2;
		paint_brush(img, Xc, Yc); // OPERACAO DO BALDINHO(PAINT_BRUSH)
		break;

	}

	//IMPRIME TODOS OS DADOS DA NOVA IMAGEM, DESDE O HEADER ATE TODOS OS PIXELS DA NOVA IMAGEM
	printf("P2\n");
	printf("# CREATOR: Image Generator SCC-221 - ICC I\n");
	printf("%d %d\n",img->XDIM, img->YDIM);
	printf("%d\n",img->MaxVal);
	int i;
	for (i=0;i<(img->XDIM*img->YDIM);i++){
	

		printf("%hhu\n", img->data[i]);
	}


}


//////////////////////////////////////////////////////FUNCOES QUE MODIFICAM OS PIXELS/////////////////////////////////////////////////////////


void Image_log(imagem* img){
	
	// APLICACAO DA FORMULA PARA MUDAR OS PIXELS DA IMAGEM QUANDO A OPERACAO A SER FEITA EH A 1
	double c=255/((double)log(1.0+img->MaxVal));
	double LOG=0;
	int i;
	for (i=0;i<(img->XDIM*img->YDIM);i++){
	

		LOG = 1.0+img->data[i];
		img->data[i]=c*(log(LOG));

	}
}


void Image_Contrast(imagem* img){
	
	// APLICACAO DA FORMULA PARA MUDAR OS PIXELS DA IMAGEM QUANDO A OPERACAO A SER FEITA EH A 2
	int min = menor(img); 
	int Max = maior(img);
	int i;
	for (i=0;i<(img->XDIM*img->YDIM);i++){
	
		img->data[i]=255*(double)((img->data[i])-min)/(Max-min); // APLICACAO DA FORMULA

	}
}

void paint_brush(imagem* img, int x, int y){

	// APLICACAO DA FORMULA PARA MUDAR OS PIXELS DA IMAGEM QUANDO A OPERACAO A SER FEITA EH A 3
	int ponto = y*(img->XDIM) + x; // TRANSFORMANDO AS COORDENADAS X E Y DE UMA MATRIZ, EM UMA POSICAO DE UM VETOR 
	if((img->data[ponto]!= 255) && (img->data[ponto]!=100)){ // SE O PIXEL NAO ESTIVER NA DELIMITACAO(BRANCO) E NEM TIVER SIDO PINTADO AINDA
	
		// PINTA O PIXEL
		img->data[ponto]=100; 
		paint_brush(img,x, y+1); // DIREITA
		paint_brush(img,x-1,y); // CIMA
		paint_brush(img,x+1,y); // BAIXO
		paint_brush(img,x,y-1); // ESQUERDA

	}


}


/////////////////////////////////////////////FUNCOES QUE ACHAM O MENOR E MAIOR VALOR DE PIXEL////////////////////////////////////////////////////


int menor(imagem* img){ 

	int i;
	int menor;
	menor=img->data[0]; // ATRIBUINDO A VARIAVEL 'menor' O VALOR DO PRIMEIRO PIXEL DA IMAGEM
	for (i=0;i<(img->XDIM*img->YDIM);i++){
	

		if((img->data[i])==0){ // COMO O MENOR PIXEL DE UMA IMAGEM ".PGM" É 0, ENTAO SE HOUVER UM PIXEL=0, ELE SERA O MENOR VALOR
			menor=img->data[i];
			return menor;
		}
		else if((img->data[i])<menor) 
			menor=img->data[i];

	}
	return menor; 
}


int maior(imagem* img){

	int i;
	int maior;
	maior=img->data[0]; // ATRIBUINDO A VARIAVEL 'maior' O VALOR DO PRIMEIRO PIXEL DA IMAGEM
	for (i=0;i<(img->XDIM*img->YDIM);i++){
	
		// COMO O MAIOR PIXEL DE UMA IMAGEM ".PGM" É O ARMAZENADO NA VARIAVEL 'MaxVal', ENTAO SE HOUVER UM PIXEL=MaxVal, ELE SERA O MAIOR VALOR
		if((img->data[i])==img->MaxVal)  
			return maior;
		else if((img->data[i])>maior) 
			maior=img->data[i];
	}
	return maior; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
