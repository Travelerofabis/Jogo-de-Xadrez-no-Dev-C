//bibliotecas 
#include <stdio.h>
#include <stdlib.h>

//tabuleiro � feito por uma matriz de (8�8) onde a casa branca � representada por . e a casa preta � representada por :.
//n�meros de baixo representas as brancas e as letras de cima as pretas
//baseada nas linhas de baixo (pe�as brancas) os n�meros correspondem as pe�as do jogo tradicional
//10-pe�es 20-bispo 30-cavalos 40-torres 50-rainha 60-rei

int Board[8][8] = //matriz do tabuleiro
{
 41, 31, 21, 51, 61, 21, 31, 41,//lado preto
 11, 11, 11, 11, 11, 11, 11, 11,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 00, 00, 00, 00, 00, 00, 00, 00,
 10, 10, 10, 10, 10, 10, 10, 10,
 40, 30, 20, 50, 60, 20, 30, 40,//lado branco
};

//fun��es de funcionamento inicial
void PrintBoard( void );//tabuleiro na tela
void SelectPiece( int vez, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC );//Seleciona e verifica a pe�a do lado que come�ar� e faz a jogada
void BoardClean ( void );//ap�s uma jogada representada por "int vez" limpar� o tabuleiro e passar� a vez para o pr�ximo lado
//int vez contar� uma jogada por vez, 
//RokB1 e RokP1 ler�o o comando de roque para a dirreita ou para a esquerda
//de passagem L e C armazenar�o a jogada dentro da matriz, uma casa antes preenchida fica vazia e a casa selecionada � preenchida por RokP1 ou RokP2
int main() //primeira fun��o 
{
	int vez = 0;//contador come�a zerado 
	bool RokeBranco1, RokePreto1, RokeBranco2, RokePreto2;//prepara��o para reconhecer o lado que come�a e qual ir� andar e pra onde ir�
	int el_passantL, el_passantC;//casa andou, fica onde est� at� a pr�xima jogada
	while(1)//jogada por int vez
	{
		PrintBoard();//chama a fun��o que cont�m os comandos de jogada, sele��o e execu��o
		SelectPiece( vez, RokeBranco1, RokePreto1, RokeBranco2, RokePreto2, el_passantL, el_passantC );//chama a fun��o que executa as pe�as para cada um dos comandos dentro das possibilidades
		if (vez == 0) vez = 1; else vez = 0; //verifica se a jogada for 0 ela receber� 1, caso contr�rio chamr� a fun��o PrintBoard de novo
	}
	return 0;//retorno da fun��o
}

//Fun��o de comando que mostra a orienta��o do tabuleiro e os comandos de entrada de qual pe�a anda e para onde vai de acordo com a orienta��o
void PrintBoard( void )
{
	printf("\n*| a b c d e f g h|*\n--------------------\n");//orienta��o do tabuleiro
	for(int ver=0; ver<8; ver++) //comando iniciado zerado em int vez dentro do limite do tabuleiro [8][8]
	{
		printf("%d|", 8-ver);//vai mostrar a jogada (valor dela na matriz) e vai diminuir uma casa do limite de linhas e de colunas 
		for(int hor=0; hor<8; hor++) //for das jogadasx
		{
			switch( Board[ver][hor] ) //plano de jogadas dentro do tabuleiro onde ver e de p� e hor � deitado
			{
				case 2: printf(" X"); break;//Sele��o de casa branca.
				case 3: printf(" X"); break;//Sele��o de casa preta.

				case 10: printf(".1"); break;//Pe�o Branco.
				case 11: printf(".A"); break;//Pe�o Preto.
				case 20: printf(".2"); break;//Bispo Branco.
				case 21: printf(".B"); break;//Bispo Preto.
				case 30: printf(".3"); break;//Cavalo Branco.
				case 31: printf(".C"); break;//Cavalo Preto.
				case 40: printf(".4"); break;//Torre Branca.
				case 41: printf(".D"); break;//Torre Preta.
				case 50: printf(".5"); break;//Rainha Branca.
				case 51: printf(".E"); break;//Rainha Preta.
				case 60: printf(".6"); break;//Rei Branco.
				case 61: printf(".F"); break;//Rei Preto.

				case 12: printf("!1"); break;//Pe�o Branco Amea�ado.
				case 13: printf("!A"); break;//Pe�o Preto Amea�ado.
				case 22: printf("!2"); break;//Bispo Branco Amea�ado.
				case 23: printf("!B"); break;//Bispo Preto Amea�ado.
				case 32: printf("!3"); break;//Cavalo Branco Amea�ado.
				case 33: printf("!C"); break;//Cavalo Preto Amea�ado.
				case 42: printf("!4"); break;//Torre Branca Amea�ada.
				case 43: printf("!D"); break;//Torre Preta Amea�ada.
				case 52: printf("!5"); break;//Rainha Branca Amea�ada.
				case 53: printf("!E"); break;//Rainha Preta Amea�ada.
				case 62: printf("!6"); break;//Rei Branco em Cheque.
				case 63: printf("!F"); break;//Rei Preto em Cheque.

				default: if ((ver+hor) % 2 ==0) printf(" ."); else printf(" :"); break;//Case Vazia.mostra a casa vazia atrav�s do movimento, a casa anterior fica vazia
			}
		}
		printf("|%d\n", 8-ver);//mostra a jogada 
	}
	printf("--------------------\n*| 1 2 3 4 5 6 7 8|*\n");//orianta��o de novo
}

//fun��o para as sele��es de pe�as, leitura do comando e execu��o do movimento, qual e para onde 
void SelectPiece( int vez /*come�a zerado e contar� a vez at� o fim da jogada*/, bool &RokB1, bool &RokP1, bool &RokB2, bool &RokP2, int &DePassagemL, int &DePassagemC )
{
	int linha=0, coluna=0, DestLinha=0, DestColuna=0, peca, hor, ver; //ir� come�ar zerado, as pe�as no seu lugar,a  pe�a e a possibilidade de jogada

	PONTO1://Selecionar uma pe�a:
	do //executar� os comandos uma vez dentro do while que � o tabuleiro
	{
		printf("\nDigite para onde quer se mover(exemplo: 2(linha) 4(coluna))? ");
		scanf("%d%d", &linha, &coluna);//qual pe�a queres mover

		//Checa se a casa selecionada � v�lida:
		if((linha<1 || linha >8)||(coluna<1 || coluna>8))
		{
			printf("\nVoce digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada est� vazia:
		if (Board[8-linha][coluna-1] == 0)
		{
			printf("\nVoce selecionou uma casa vazia!Selecione uma peca!\n");
			linha = 0, coluna = 0;//?isso far� o la�o repetir!
		}
		else
		//Checa se � a vez das brancas uma pe�a branca deve ser selecionada e vice versa:
		if (((Board[8-linha][coluna-1] % 2 == 0)&&(vez == 1))||((Board[8-linha][coluna-1] % 2 != 0)&&(vez == 0)))
		{
			printf("\nVoce nao pode selecionar uma peca do oponente!Seleciona as suas!\n");
			linha = 0, coluna = 0;//?isso far� o la�o criado pelo "do" se repetir
		}
		
	}while ((linha<1 || linha >8)||(coluna<1 || coluna>8));

	linha = 8-linha;//se digitado 1, dever� ser acessado 0 em "Board[0][].
	coluna -= 1;//se digitado 1, dever� ser acessado 0 em "Board[][0].

	//Seleciona a pe�a e mostra seus possiveis destinos:

	if (Board[linha][coluna] == 10)//Pe�o Branco:
	{
		if (Board[linha-1][coluna] == 0)//0 em "Board[][0]"
		{
			Board[linha-1][coluna] = 2;
			if ((Board[linha-2][coluna] == 0)&&(linha == 6))
			Board[linha-2][coluna] = 2;
		}
		if ((linha<7)&&(coluna<7)) if ((Board[linha-1][coluna+1] % 2 !=0)&&(Board[linha-1][coluna+1] > 2)) Board[linha-1][coluna+1] += 2; //jogada dentro da matriz
		if ((linha<7)&&(coluna>0)) if ((Board[linha-1][coluna-1] % 2 !=0)&&(Board[linha-1][coluna-1] > 2)) Board[linha-1][coluna-1] += 2; //jogada dentro da matriz

		if((linha-1 == DePassagemL)&&(coluna+1 == DePassagemC)) Board[linha-1][coluna+1] = 2; //reposiciona dentro da matriz
		if((linha-1 == DePassagemL)&&(coluna-1 == DePassagemC)) Board[linha-1][coluna-1] = 2;

		peca = Board[linha][coluna];//salva a pe�a em sua nova posi��o
	}

	if (Board[linha][coluna] == 11)//Pe�o Preto:
	{
		if (Board[linha+1][coluna] == 0)
		{
			Board[linha+1][coluna] = 3;
			if ((Board[linha+2][coluna] == 0)&&(linha == 1))
			Board[linha+2][coluna] = 3;
		}
		if ((linha<7)&&(coluna<7)) if ((Board[linha+1][coluna+1] % 2 ==0)&&(Board[linha+1][coluna+1] > 3)) Board[linha+1][coluna+1] += 2;
		if ((linha<7)&&(coluna>0)) if ((Board[linha+1][coluna-1] % 2 ==0)&&(Board[linha+1][coluna-1] > 3)) Board[linha+1][coluna-1] += 2;

		if((linha+1 == DePassagemL)&&(coluna+1 == DePassagemC)) Board[linha+1][coluna+1] = 3;
		if((linha+1 == DePassagemL)&&(coluna-1 == DePassagemC)) Board[linha+1][coluna-1] = 3;

		peca = Board[linha][coluna];
	}

	if ((Board[linha][coluna] == 20+vez)||(Board[linha][coluna] == 50+vez))//Bispo e Rainha Branca e Preta:
	{
		hor = coluna;//movimento vertical na esquerda
		for(ver = linha-1;ver>-1;ver--)
		{
			if (hor == 0) break;
			hor--;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
			 if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
			 if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Para cima na horizontal na direita 
		for(ver = linha-1;ver>-1;ver--)
		{
			if (hor == 7) break;
			hor++;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Movimento para baixo na esquerda
		for(ver = linha+1;ver<8;ver++)
		{
			if (hor == 0) break;
			hor--;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//Movimento para baixo na esquerda
		for(ver = linha+1;ver<8;ver++)
		{
			if (hor == 7) break;
			hor++;
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		peca = Board[linha][coluna];
	}

	if ((Board[linha][coluna] == 40+vez)||(Board[linha][coluna] == 50+vez))//Torres ou Rainha Brancas e Pretas:
	{
		hor = coluna;//Cima:
		for(ver = linha-1;ver>-1;ver--)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		hor = coluna;//para baixo no meio do tabuleiro
		for(ver = linha+1;ver<8;ver++)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		ver = linha;//Movimento para a esquerda 
		for(hor = coluna-1;hor>-1;hor--)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		ver = linha;//Movimento para a direita
		for(hor = coluna+1;hor<8;hor++)
		{
			if (Board[ver][hor] == 0) Board[ver][hor] = 2+vez;
			if (vez == 0)
			{
				if (((Board[ver][hor] == 10)||(Board[ver][hor] > 19))&&(Board[ver][hor] % 2 == 0)) break;
				if ((Board[ver][hor] % 2 != 0)) { Board[ver][hor] += 2; break; }
			}
			if (vez == 1)
			{
				if (((Board[ver][hor] == 11)||(Board[ver][hor] > 20))&&(Board[ver][hor] % 2 != 0)) break;
				if ((Board[ver][hor] % 2 == 0)) { Board[ver][hor] += 2; break; }
			}
		}

		peca = Board[linha][coluna];
	}

	if (Board[linha][coluna] == 30+vez)//Cavalo Branco e Preto.
	{
		//L para a esquerda:
		if ((linha > 1)&&(coluna > 0))
		{
			if (Board[linha-2][coluna-1] == 0) Board[linha-2][coluna-1] = 2+vez;
			if ((Board[linha-2][coluna-1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna-1] += 2;
			if ((Board[linha-2][coluna-1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna-1] += 2;
		}

		//L para a direita:
		if ((linha > 1)&&(coluna < 7))
		{
			if (Board[linha-2][coluna+1] == 0) Board[linha-2][coluna+1] = 2+vez;
			if ((Board[linha-2][coluna+1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna+1] += 2;
			if ((Board[linha-2][coluna+1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna+1] += 2;
		}

		//L para baixo na direita:
		if ((linha < 6)&&(coluna < 7))
		{
			if (Board[linha+2][coluna+1] == 0) Board[linha+2][coluna+1] = 2+vez;
			if ((Board[linha+2][coluna+1] % 2 !=0)&&(vez == 0)) Board[linha+2][coluna+1] += 2;
			if ((Board[linha+2][coluna+1] % 2 ==0)&&(vez == 1)) Board[linha+2][coluna+1] += 2;
		}

		//L parra baixo na esquerda:
		if ((linha < 6)&&(coluna > 0))
		{
			if (Board[linha+2][coluna-1] == 0) Board[linha+2][coluna-1] = 2+vez;
			if ((Board[linha+2][coluna-1] % 2 !=0)&&(vez == 0)) Board[linha-2][coluna+1] += 2;
			if ((Board[linha+2][coluna-1] % 2 ==0)&&(vez == 1)) Board[linha-2][coluna+1] += 2;
		}

		//L para cima na esquerda:
		if ((linha > 0)&&(coluna > 1))
		{
			if (Board[linha-1][coluna-2] == 0) Board[linha-1][coluna-2] = 2+vez;
			if ((Board[linha-1][coluna-2] % 2 !=0)&&(vez == 0)) Board[linha-1][coluna-2] += 2;
			if ((Board[linha-1][coluna-2] % 2 ==0)&&(vez == 1)) Board[linha-1][coluna-2] += 2;
		}

		//L para cima na direita:
		if ((linha > 0)&&(coluna < 6))
		{
			if (Board[linha-1][coluna+2] == 0) Board[linha-1][coluna+2] = 2+vez;
			if ((Board[linha-1][coluna+2] % 2 !=0)&&(vez == 0)) Board[linha-1][coluna+2] += 2;
			if ((Board[linha-1][coluna+2] % 2 ==0)&&(vez == 1)) Board[linha-1][coluna+2] += 2;
		}

		//L na esquerda para baixo:
		if ((linha < 7)&&(coluna > 1))
		{
			if (Board[linha+1][coluna-2] == 0) Board[linha+1][coluna-2] = 2+vez;
			if ((Board[linha+1][coluna-2] % 2 !=0)&&(vez == 0)) Board[linha+1][coluna-2] += 2;
			if ((Board[linha+1][coluna-2] % 2 ==0)&&(vez == 1)) Board[linha+1][coluna-2] += 2;
		}

		//L na direita para baixo:
		if ((linha < 7)&&(coluna < 6))
		{
			if (Board[linha+1][coluna+2] == 0) Board[linha+1][coluna+2] = 2+vez;
			if ((Board[linha+1][coluna+2] % 2 !=0)&&(vez == 0)) Board[linha+1][coluna+2] += 2;
			if ((Board[linha+1][coluna+2] % 2 ==0)&&(vez == 1)) Board[linha+1][coluna+2] += 2;
		}

		peca = Board[linha][coluna];
	}

	if (Board[linha][coluna] == 60+vez)//Reis:
	{
		//Casas vazias e como se portar� caso o rei ande.
		if (Board[linha][coluna-1] == 0) Board[linha][coluna-1] = 2+vez;//Cima.
		if (Board[linha][coluna+1] == 0) Board[linha][coluna+1] = 2+vez;//Baixo.
		if (Board[linha-1][coluna] == 0) Board[linha-1][coluna] = 2+vez;//Esquerda.
		if (Board[linha+1][coluna] == 0) Board[linha+1][coluna] = 2+vez;//Direita.
		if (Board[linha-1][coluna-1] == 0) Board[linha-1][coluna-1] = 2+vez;//Diagonal cima esquerda.
		if (Board[linha+1][coluna-1] == 0) Board[linha+1][coluna-1] = 2+vez;//Diagonal cima direita.
		if (Board[linha+1][coluna+1] == 0) Board[linha+1][coluna+1] = 2+vez;//Diagonal baixo direita.
		if (Board[linha-1][coluna+1] == 0) Board[linha-1][coluna+1] = 2+vez;//Diagonal baixo esquerda.

		//Pe�as do aders�rio brancas:
		if ((Board[linha][coluna-1] %2 == 0)&&(vez == 1)) Board[linha][coluna-1] += 2;//Cima.
		if ((Board[linha][coluna+1] %2 == 0)&&(vez == 1)) Board[linha][coluna+1] += 2;//Baixo.
		if ((Board[linha-1][coluna] %2 == 0)&&(vez == 1)) Board[linha-1][coluna] += 2;//Esquerda.
		if ((Board[linha+1][coluna] %2 == 0)&&(vez == 1)) Board[linha+1][coluna] += 2;//Direita.
		if ((Board[linha-1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna-1] += 2;//Diagonal cima esquerda.
		if ((Board[linha+1][coluna-1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna-1] += 2;//Diagonal cima direita.
		if ((Board[linha+1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha+1][coluna+1] += 2;//Diagonal baixo direita.
		if ((Board[linha-1][coluna+1] %2 == 0)&&(vez == 1)) Board[linha-1][coluna+1] += 2;//Diagonal baixo esquerda.

		//Pe�as do aders�rio pretas:
		if ((Board[linha][coluna-1] %2 != 0)&&(vez == 0)) Board[linha][coluna-1] += 2;//Cima.
		if ((Board[linha][coluna+1] %2 != 0)&&(vez == 0)) Board[linha][coluna+1] += 2;//Baixo.
		if ((Board[linha-1][coluna] %2 != 0)&&(vez == 0)) Board[linha-1][coluna] += 2;//Esquerda.
		if ((Board[linha+1][coluna] %2 != 0)&&(vez == 0)) Board[linha+1][coluna] += 2;//Direita.
		if ((Board[linha-1][coluna-1] %2 != 0)&&(vez == 0)) Board[linha-1][coluna-1] += 2;//Diagonal cima esquerda.
		if ((Board[linha+1][coluna-1] %2 != 0)&&(vez == 0)) Board[linha+1][coluna-1] += 2;//Diagonal cima direita.
		if ((Board[linha+1][coluna+1] %2 != 0)&&(vez == 0)) Board[linha+1][coluna+1] += 2;//Diagonal baixo direita.
		if ((Board[linha-1][coluna+1] %2 != 0)&&(vez == 0)) Board[linha-1][coluna+1] += 2;//Diagonal baixo esquerda.

		peca = Board[linha][coluna];

		if (vez == 0)//Roque:
		{
			if (RokB1 == 1)
			{ if ((Board[linha][coluna-2] == 0)&&(Board[linha][coluna-1] == 2+vez)) Board[linha][coluna-2] = 2+vez;/*Roque Esquerdo.*/ }
			if (RokB2 == 1)
			{ if ((Board[linha][coluna+2] == 0)&&(Board[linha][coluna+1] == 2+vez)) Board[linha][coluna+2] = 2+vez;/*Roque Direito.*/ }
		}
		if (vez == 1)
		{
			if (RokP1 == 1)
			{ if ((Board[linha][coluna-2] == 0)&&(Board[linha][coluna-1] == 2+vez)) Board[linha][coluna-2] = 2+vez;/*Roque Esquerdo.*/ }
			if (RokP2 == 1)
			{ if ((Board[linha][coluna+2] == 0)&&(Board[linha][coluna+1] == 2+vez)) Board[linha][coluna+2] = 2+vez;/*Roque Direito.*/ }
		}
	}//Reis

	PrintBoard();//chama as orienta��es do tabuleiro

	do //la�o de repeti��o do while de novo
	{
		printf("\nDigite o local que deseja mover a pe�a? ");
		scanf("%d%d", &DestLinha, &DestColuna);

		//Checa se foi digitado um n�mero valido>0:
		if ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8))
		{
			printf("\nVoc� digitou errado!Tente novamente!\n");
		}
		else
		//Checa se a casa selecionada est� vazia:
		if (Board[8-DestLinha][DestColuna-1] == 0)
		{
			printf("\nVoce selecionou uma casa invalida, selecione o 'X' ou uma outra peca!\n");
		}
		else
		//Checa se o jogador escolheu um local com uma pe�a aliada:
		for(int Blc = 6;Blc<57;Blc++)//Checa quais pe�as est�o amea�adas(14,15,24,25,34,35,44,45,46,47,54,55,56,57).
		{
			if (Blc % 2 ==0){ Blc += 8; }

			//Se a casa n�o estiver vazia, e n�o for uma casa selecionada pora possivel jogada.
			if ((Board[8-DestLinha][DestColuna-1] >0)&&(Board[8-DestLinha][DestColuna-1] != 2+vez))
			//Se escolheu pe�a branca na vez das brancas, ou escolheu pe�a preta na vez das pretas:
			if (((Board[8-DestLinha][DestColuna-1] % 2 == 0)&&(vez == 0)) || ((Board[8-DestLinha][DestColuna-1] % 2 != 0)&&(vez == 1)))
			{
				printf("\nVoce nao pode comer uma peca da sua 'cor'! Tente de novo ou selecione outra.\n");
				linha = 0, coluna = 0, DestLinha = 0, DestColuna = 0, peca = 0;
				BoardClean();//chama a finaliza��o da jogada
				PrintBoard();//chama a as orienta��es do tabuleiro
				goto PONTO1;//vai para o la�o de repeiti��o
			}
		}
	}while ((DestLinha<1 || DestLinha >8)||(DestColuna<1 || DestColuna>8));

	DestLinha = 8-DestLinha;//inverte os numeros ( 8 equivale a 0, 7 equivale a 1, 6 equivale a 2 ...)
	DestColuna -= 1;//se digitado 1, dever� ser acessado 0 em "Board[][0].

	//?Move a pe�a:
	if ((Board[DestLinha][DestColuna] == 2)||(Board[DestLinha][DestColuna] == 3))
	//Se uma casa selecionada:
	{
		Board[DestLinha][DestColuna] = peca;//Aloca a pe�a em seu destino.
		Board[linha][coluna] = 0;//Retira a pe�a de sua origem.
		if (( DestLinha == DePassagemL )&&( DestColuna == DePassagemC ))
		{
			if ( vez == 0)Board[DePassagemL+1][DePassagemC] = 0;
			if ( vez == 1)Board[DePassagemL-1][DePassagemC] = 0;
		}

		//Ativa a Jogada "El_passant" no Pe�o:
		if (( peca == 10 )&&(DestLinha == 4))
		{
			DePassagemL = DestLinha+1, DePassagemC = DestColuna;
			printf("De Passagem = linha %d, coluna %d\n", DePassagemL, DePassagemC );
		}
		else if (( peca == 11 )&&(DestLinha == 3))
		{
			DePassagemL = DestLinha-1, DePassagemC = DestColuna;
			printf("De Passagem = linha %d, coluna %d\n", DePassagemL, DePassagemC );
		}
		else{ DePassagemL = -1, DePassagemC = -1; }

	}//ou uma pe�a do oponente � escolhida.
	else
	{
		for(int Blc = 4;Blc<54;Blc++)//Checa quais pe�as est�o amea�adas(12,13,22,23,32,33,42,43,42,43,52,53).
		{
			if (Blc % 2 == 0){ Blc += 8; }

			if (Board[DestLinha][DestColuna] == Blc)
			{
				Board[DestLinha][DestColuna] = peca;//Aloca a pe�a em seu destino.
				Board[linha][coluna] = 0;//Retira a pe�a de sua origem.
			}
		}
	}

	//Se um Rei ou uma Torre se moveu (Roques):
	if ((peca == 40+vez)||(peca == 60+vez))
	if(((RokB1 == 1)||(RokB2 == 1))||((RokP1 == 1)||(RokP2 == 1)))
	{
		if (peca == 60+vez)
		{
			if (peca %2 ==0)
			{
				if ((Board[7][2] == 60)&&(RokB1 == 1))
				{
					Board[7][0] = 0;
					Board[7][3] = 40;
				}
				if ((Board[7][6] == 60)&&(RokB2 == 1))
				{
					Board[7][7] = 0;
					Board[7][5] = 40;
				}
				RokB1 = 0, RokB2 = 0;
			}
			if (peca %2 !=0)
			{
				if ((Board[0][2] == 61)&&(RokP1 == 1))
				{
					Board[0][0] = 0;
					Board[0][3] = 41;
				}
				if ((Board[0][6] == 61)&&(RokP2 == 1))
				{
					Board[0][7] = 0;
					Board[0][5] = 41;
				}
				RokP1 = 0, RokP2 = 0;
			}
		}
		else
		{
			if (peca %2 == 0)
			{
				if (coluna == 7) RokB2 = 0;
				if (coluna == 0) RokB1 = 0;
			}
			if (peca %2 != 0)
			{
				if (coluna == 7) RokP2 = 0;
				if (coluna == 0) RokP1 = 0;
			}
		}
	}


	BoardClean();//Limpa o Tabuleiro das amea�as!

	if (((Board[DestLinha][DestColuna] == 10)&&(DestLinha == 0))||((Board[DestLinha][DestColuna] == 11)&&(DestLinha == 7)))//Se um pe�o chegar ao lado oposto:
	{
		printf("***Parab�ns!***\nSeu pe�o chegou ao lado oposto, em qual pe�a gostaria de transform�-lo?");
		PONTO4://ressucita uma pe�a
		printf("\n1?bispo. 2?cavalo. 3?torre. 4?rainha.\n?");//codigo das pe�as que podem voltar
		scanf("%d", &Board[DestLinha][DestColuna]);
		switch( Board[DestLinha][DestColuna] )//organiza��o de acordo comonde o pe�o chegou e onde a pe�a vai ficar
		{
			case 1: Board[DestLinha][DestColuna] = 20+vez; break;
			case 2: Board[DestLinha][DestColuna] = 30+vez; break;
			case 3: Board[DestLinha][DestColuna] = 40+vez; break;
			case 4: Board[DestLinha][DestColuna] = 50+vez; break;
			default: { printf("\nOp��o inv�linda!tente novamente!"); goto PONTO4; } break;//valores inv�lidos, volta para o la�o de repeti��o
		}
	}
} //fim

void BoardClean ( void )
{
	for(int ver=0; ver<8; ver++)//Limpa o Tabuleiro de amea�as:
	{
		for(int hor=0; hor<8; hor++)
		{
			if ((Board[ver][hor] == 2)||(Board[ver][hor] == 3))
			Board[ver][hor] = 0;
			
			for(int Blc = 4;Blc<64;Blc++)//Checa quais pe�as est�o amea�adas(12,13,22,23,32,33,42,43,52,53,62,63).
			{
				if (Blc % 2 ==0){ Blc += 8; }

				if (Board[ver][hor] == Blc)
				{
					Board[ver][hor] -=2;//Desamea�a a pe�a.
				}
			}
		}
	}
}
