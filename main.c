/**************************
JOGO DE ELIMINIÇÃO DAS PEDRAS
***************************/

#include <stdio.h>

/* DECLARAÇÃO DAS FUNÇÕES */
// Inicia o tabuleiro
void inic_tab(char m[8][8]) {
    // Declaração das variáveis locais
    int i, j;                                              // Variáveis de controle

    // Preencher as pedras do jogo
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            m[i][j] = '*';                                 // Representação das pedras no jogo
        }
    }

    // Preencher a parte vazia do jogo
    for(i = 2; i <= 5; i++) {
        for(j = 2; j <= 5; j++) {
            m[i][j] = '-';                                // Representação da parte vazia no jogo
        }
    }
}

// Apresenta o tabuleiro
void apr_tab(char m[8][8]) {
  // Declaração das variáveis locais
  int i, j;                                               // Variáveis de controle

  // Apresentação do tabuleiro
  printf("\n");
  printf("-=-  TABULEIRO DO JOGO  -=-  \n\n");
  printf("  ");
  for(i = 0; i < 8; i++) {
      printf("%d ", i + 1);                                
  }
  printf("\n");
  for(i = 0 ; i< 8; i++) {
      printf("%d ", i + 1);                                
      for(j = 0; j < 8; j++) {
        printf("%c ", m[i][j]);                            
      }
    printf("\n");
  }
  printf("\n");
}

// Instruções do tabuleiro
void manual(char como_jogar) {
  // Seção de comandos
  if (como_jogar == 'S' || como_jogar == 's'){              // Caso o jogador deseje receber as instruções
    
    printf("-=-  INSTRUÇÕES DO JOGO  -=-  \n\n");
    printf("Os saltos devem ser realizados observando-se o seguinte:\n");
    printf("a) Um salto consiste sempre em deslocar uma pedra qualquer para uma casa que esteja vazia;\n");
    printf("b) A casa de destino da pedra no salto deve estar na diagonal da sua casa de origem;\n");
    printf("c) Para atingir a casa vazia, a pedra não pode passar por outras casas vazias.\n\n");
    printf("O jogo possui os seguintes graus de dificuldade:\n");
    printf("a) Extremamente fácil: eliminar até 29 pedras;\n");
    printf("b) Fácil: eliminar de 30 a 39 pedras;\n");
    printf("c) Difícil: eliminar de 40 a 44 pedras;\n");
    printf("d) Extremamente difícil: eliminar de 45 a 47 pedras.\n\n");
    
  } else if (como_jogar == 'N' || como_jogar == 'n'){      // Caso o jogador não deseje receber as instruções
    printf("\n");
    
  }
}

// Solicita a casa de origem e a de destino
void solicita(int *lin_o, int *col_o, int *lin_d, int *col_d) {
  // Entrada de dados
  printf("Digite a linha e a coluna de origem da pedra. \n");
  printf("Linha: ");
  scanf("%d", lin_o);
  printf("Coluna: ");
  scanf("%d", col_o);
  printf("Digite a linha e a coluna de destino da pedra. \n");
  printf("Linha: ");
  scanf("%d", lin_d);
  printf("Coluna: ");
  scanf("%d", col_d);
  printf("\n");

  // Subtraindo 1 das coordenadas inseridas pelo usuário
  (*lin_o)--;
  (*col_o)--;
  (*lin_d)--;
  (*col_d)--;
}

// Verifica a jogada
int verificar_jogada(char m[8][8], int lin_o, int col_o, int lin_d, int col_d, int *lin_elim, int *col_elim, int *num_pedras_elim) {
  // Declaração de variáveis locais
  int dif_linha = lin_d - lin_o;                                  // Calcula a diferença entre as linhas
  int dif_coluna = col_d - col_o;                                 // Calcula a diferença entre as colunas
  int incremento_linha = (dif_linha > 0) - (dif_linha < 0);       // Calcula o incremento para a difereça entre as linhas
  int incremento_coluna = (dif_coluna > 0) - (dif_coluna < 0);    // Calcula o incremento para a difereça entre as colunas

  
  // Atualizam os valores apontados pelos ponteiros com as posições de eliminação calculadas
  *lin_elim = lin_o + incremento_linha;
  *col_elim = col_o + incremento_coluna;

    // Verificar se as posições são válidas
    if (lin_o < 0 || lin_o >= 8 || col_o < 0 || col_o >= 8 || lin_d < 0 || lin_d >= 8 || col_d < 0 || col_d >= 8) {
        printf("Posição inválida! Tente novamente.\n");
        return 0;
    }

    // Verificar se as posições estão na mesma diagonal
    if (dif_linha != dif_coluna && dif_linha != -dif_coluna) {
        printf("As posições não estão na mesma diagonal! Tente novamente.\n");
        return 0;
    }

    // Verificar se a casa de origem contém uma pedra
    if (m[lin_o][col_o] != '*') {
        printf("A casa de origem não contém uma pedra! Tente novamente.\n");
        return 0;
    }

    // Verificar se a casa de destino está vazia
    if (m[lin_d][col_d] != '-') {
        printf("A casa de destino não está vazia! Tente novamente.\n");
        return 0;
    }

    // Verificar se há uma pedra no meio da diagonal
    if (m[*lin_elim][*col_elim] != '*') {
        printf("Não há uma pedra no meio da diagonal! Tente novamente.\n");
        return 0;
    }

    // Verificar se o salto elimina uma pedra
    *num_pedras_elim = 0;                                 
    while (*lin_elim != lin_d || *col_elim != col_d) {
        if (m[*lin_elim][*col_elim] != '*') {
            printf("O salto não elimina uma pedra! Tente novamente.\n");
            return 0;
        }
        (*num_pedras_elim)++;              // Incrementa o número de pedras eliminadas                   
        *lin_elim += incremento_linha;     // Adiciona o valor de incremento_linha à variável apontada por lin_elim                     
        *col_elim += incremento_coluna;    // Adiciona o valor de incremento_coluna à variável apontada por col_elim                         
    }

  return 1;
}

// Atualiza o tabuleiro
void atualiza_tab(char m[8][8], int lin_o, int col_o, int lin_d, int col_d, int *lin_elim, int *col_elim, int num_pedras_elim) {
  // Declaração das variáveis locais
  int incremento_linha = (lin_d > lin_o) - (lin_d < lin_o);     // Inidica a direção do movimento a ser realizado
  int incremento_coluna = (col_d > col_o) - (col_d < col_o);    // indicam a direção do movimento a ser realizado
  
  
  // Atualizam os valores apontados pelos ponteiros com as posições de eliminação calculadas
  *lin_elim = lin_o + incremento_linha;
  *col_elim = col_o + incremento_coluna;

  // Percorre as posições intermediárias entre a posição de origem e a posição de destino do movimento
  while (*lin_elim != lin_d || *col_elim != col_d) {
      m[*lin_elim][*col_elim] = '-';
      *lin_elim += incremento_linha;
      *col_elim += incremento_coluna;
  }

  m[lin_d][col_d] = '*';                                         // Atualiza a posição de destino com o caractere '*'
  m[lin_o][col_o] = '-';                                         // Atualiza a posição de origem com o caractere '-'
}

// Informações da jogada
void info_jogada(char m[8][8], int lin_o, int col_o, int lin_d, int col_d, int pedra_elim, int pedra_rest, int num_pedras_elim){
  // Informa os dados de cada jogada
  printf("\nSalto de (%d,%d) para (%d,%d) com %d pedra(s) eliminada(s) neste salto.\n", lin_o + 1, col_o + 1, lin_d + 1, col_d + 1, num_pedras_elim);
  printf("%d pedras eliminadas; restam %d pedras no tabuleiro.\n", pedra_elim, pedra_rest);
}

// Processa a jogada
void processa_jogada(char m[8][8], int lin_o, int col_o, int lin_d, int col_d, int *pedra_elim, int *pedra_rest, int *saltos) {
  // Declaração de variáveis locais
  int lin_elim, col_elim;
  int num_pedras_elim;

  if (verificar_jogada(m, lin_o, col_o, lin_d, col_d, &lin_elim, &col_elim, &num_pedras_elim)) {
      atualiza_tab(m, lin_o, col_o, lin_d, col_d, &lin_elim, &col_elim, num_pedras_elim);
      (*pedra_elim) += num_pedras_elim;     // Atualiza o número de pedras eliminadas 
      *pedra_rest = 48 - *pedra_elim;       // Calcula o número de pedras restantes
      (*saltos)++;                          // Atualiza o número de saltos
      info_jogada(m, lin_o, col_o, lin_d, col_d, *pedra_elim, *pedra_rest, num_pedras_elim);
  }
}

// Verificar o fim do jogo
int verificar_fim_jogo(char m[8][8]) {
  // Variáveis de controle
  int i, j;

  // Verificar todas as posições do tabuleiro
  for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++) {
          if (m[i][j] == '*') {
              // Verificar se é possível pular para a diagonal superior esquerda
              if (i >= 2 && j >= 2 && m[i - 1][j - 1] == '*' && m[i - 2][j - 2] == '-')
                  return 0;

              // Verificar se é possível pular para a diagonal superior direita
              if (i >= 2 && j <= 5 && m[i - 1][j + 1] == '*' && m[i - 2][j + 2] == '-')
                  return 0;

              // Verificar se é possível pular para a diagonal inferior esquerda
              if (i <= 5 && j >= 2 && m[i + 1][j - 1] == '*' && m[i + 2][j - 2] == '-')
                  return 0;

              // Verificar se é possível pular para a diagonal inferior direita
              if (i <= 5 && j <= 5 && m[i + 1][j + 1] == '*' && m[i + 2][j + 2] == '-')
                  return 0;
          }
      }
  }

  return 1;   // Não há mais saltos válidos, fim do jogo
}

// Estatísticas
void estatisticas(int pedra_elim, int pedra_rest, int saltos){
  // Dados apresentados ao finalizar o jogo
  printf("\bSaltos realizados: %d\n", saltos);
  printf("Pedras eliminadas: %d\n", pedra_elim);
  printf("Pedras restantes: %d\n", pedra_rest);
}

// Dificuldade atingida
void dificuldade(int pedra_elim){
  // Condição para cada dificuldade atingida pelo jogador
  if (pedra_elim <= 29){
      printf("\nDificuldade atingida: Extremamente Fácil (eliminou até 29 pedras).\n");
  } else if (pedra_elim >= 30 && pedra_elim <= 39){
      printf("\nDificuldade atingida: Fácil (eliminou de 30 a 39 pedras).\n");
  } else if(pedra_elim >= 40 && pedra_elim <= 44){
      printf("\nDificuldade atingida: Difícil (eliminou de 40 a 44 pedras).\n");   
  } else if(pedra_elim >= 45 && pedra_elim <= 47){
      printf("\nDificuldade atingida: Extremamente Difícil (eliminou de 45 a 47 pedras).\n");
  }
}

// Reiniciar o jogo
void reiniciar_jogo(char m[8][8], int *pedra_elim, int *pedra_rest, int *saltos) {
  // Reinicia as informações do jogo
  *pedra_elim = 0;
  *pedra_rest = 48;
  *saltos = 0;
  inic_tab(m);
}

/* FUNÇÃO MAIN */
int main() {
  // Declaração das variáveis
  char tab[8][8];                                          // Tabuleiro (representação)
  char como_jogar;                                         // Instrução do jogo
  char jogar_dnv;                                          // Caso o jogadr deseje jogar novamente
  int lin_o, col_o, lin_d, col_d;                          // Dados da jogada
  int pedra_elim = 0;                                      // Contador de pedras eliminadas
  int pedra_rest = 48;                                     // Contador de pedras restantes
  int saltos = 0;                                          // Contador de saltos realizados
  

  // Mensagem de início do jogo
  printf("\n-=-  JOGO DE ELIMINAÇÃO DAS PEDRAS  -=-  \n\n");
  printf("Para receber as instruções do jogo, digite 'S' ");
  printf("se não desejar receber as instruções, digite 'N'.\n");
  printf("Digite (S/N): ");
  scanf(" %c", &como_jogar);
  printf("\n");
  printf("Caso deseje sair do jogo digite 1 na linha/coluna de origem e linha/coluna de destino.\n\n");
  
  // Apresenta as instruções
  manual(como_jogar);
  
  // Apresenta o tabuleiro
  inic_tab(tab);
  
  do{
    do{
      // Apresenta o tabuleiro
      apr_tab(tab);

    
      // Solicita a casa de origem e a de destino
      solicita(&lin_o, &col_o, &lin_d, &col_d);

      // Verificar se o jogador desistiu
      if (lin_o == 0 && col_o == 0 && lin_d == 0 && col_d == 0) {
        printf("O jogador desistiu. Fim de jogo!\n");
        
        // Mostra as estatísticas
        estatisticas(pedra_elim, pedra_rest, saltos);
        dificuldade(pedra_elim);
        
        // Verifica se o jogador deseja jogar novamente
        printf("Deseja jogar novamente? (S/N):");
        scanf(" %c", &jogar_dnv);
        break;
      }
    
      // Processa a jogada
      processa_jogada(tab, lin_o, col_o, lin_d, col_d, &pedra_elim, &pedra_rest, &saltos);

    
      // Verificar o fim do jogo
      if (verificar_fim_jogo(tab)) {
        printf("\nFim do jogo!\n");
        
        // Mostra as estatísticas
        estatisticas(pedra_elim, pedra_rest, saltos);
        dificuldade(pedra_elim);
        
        // Verifica se o jogador deseja jogar novamente
        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &jogar_dnv);
        break;
      }
      
    } while (lin_o != 0 || col_o != 0 || lin_d != 0 || col_d != 0);

    // Caso o jogador desejar jogar novamente
    reiniciar_jogo(tab, &pedra_elim, &pedra_rest, &saltos);
    
  } while(jogar_dnv == 'S' || jogar_dnv == 's');
}