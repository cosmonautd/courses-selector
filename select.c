#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Função que imprime os cursos selecionados de forma a maximizar o nível 
    de interesse estudantil através da alocação de displinas dentro de um
    número máximo de horas/semana disponíveis */
int select_courses(const char** courses, int* interest, int* duration, int n, int available_time) {

    /*  i, j: Variáveis de loop
        K: Matriz em que o elemento K[i][j] armazena a satisfação máxima 
            utilizando as disciplinas 0,1,...,i alocadas dentro de um
            intervalo de j horas/semana.
        keep: Variável auxiliar para obtenção das disciplinas alocadas.
            keep[i][j] é 1 se a i-ésima disciplina é selecionada dentro 
            dentro do intervalo de j horas.
    */
    int i, j;
    int K[n+1][available_time+1];
    int keep[n+1][available_time+1];

    /* Loop para construção bottom-up da matriz K */
    for(i=0; i <= n; i++) {
        for(j=0; j <= available_time; j++) {
            /* Nenhuma disciplina pode ser alocada se não for considerada
                ou se o tempo disponível é zero */
            if(i == 0 || j == 0) K[i][j] = 0;
            /*  Se a disciplina puder ser alocada dentro de intervalo de 
                tempo j e sua alocação resultar em um nível de satisfação
                maior que o máximo nível de satisfação com uma disciplina
                a menos, a disciplina é dada como alocada, considerando as
                primeiras i disciplinas dentro de um tempo j */
            else if(duration[i-1] <= j && interest[i-1] + K[i-1][j-duration[i-1]] > K[i-1][j]) {
                K[i][j] = interest[i-1] + K[i-1][j-duration[i-1]];
                keep[i][j] = 1;
            /*  Caso contrário, a disciplina não é alocada e o nível
                de satisfação é mantido */
            } else {
                K[i][j] = K[i-1][j];
                keep[i][j] = 0;
            }
        }
    }

    /* Análise da matriz keep e impressão das disciplinas alocadas */
    int k = available_time;
    for(i=n; i > 0; i--) {
        if(keep[i][k]) {
            printf("%s\n", courses[i-1]);
            k = k - duration[i];
        }
    }

    /* Retorno do score de satisfação estudantil obtido */
    return K[n][available_time];
}

void main() {

    /*  courses: Vetor de disciplinas eletivas do 
        curso de Engenharia de Computação */
    const char* courses[60];
    courses[0]  = "Lógica Matemática";
    courses[1]  = "Computação Gráfica";
    courses[2]  = "Pesquisa e Ordenação de Dados";
    courses[3]  = "Teoria dos Autômatos e Linguagens Formais";
    courses[4]  = "Algoritmos em Grafos";
    courses[5]  = "Construção e Análise de Algoritmos";
    courses[6]  = "Programação Linear";
    courses[7]  = "Redes de Petri";
    courses[8]  = "Programação Paralela e Distribuída";
    courses[9]  = "Construção de Compiladores";
    courses[10] = "Teoria da Computação";
    courses[11] = "Algoritmos Distribuídos";
    courses[12] = "Tecnologias WEB";
    courses[13] = "Sistemas Distribuídos";
    courses[14] = "Redes de Alta Velocidade";
    courses[15] = "Qualidade de Software";
    courses[16] = "Sistemas Tolerantes a Falhas";
    courses[17] = "Análise e Projeto de Sistemas I";
    courses[18] = "Análise e Projeto de Sistemas II";
    courses[19] = "Sistemas de Gerenciamento de Bancos de Dados";
    courses[20] = "Tópicos Especiais em Computação I";
    courses[21] = "Tópicos Especiais em Computação II";
    courses[22] = "Tópicos de Programação";
    courses[23] = "Sistemas Embarcados";

    courses[24] = "Controle Adaptativo";
    courses[25] = "Controle e Automação Industrial";
    courses[26] = "Identificação de Sistemas";
    courses[27] = "Técnicas Avançadas em Microprocessadores";
    courses[28] = "Técnicas Avançadas em Eletrônica Digital";
    courses[29] = "Sistemas Eletrônicos";
    courses[30] = "Circuitos Elétricos II";
    courses[31] = "Variáveis Complexas";
    courses[32] = "Processamento Digital de Sinais";
    courses[33] = "Microprocessadores II";
    courses[34] = "Eletrônica Industrial";
    courses[35] = "Teoria do Controle Discreto";
    courses[36] = "Sistemas Lineares";
    courses[37] = "Higiene Industrial e Segurança no Trabalho";
    courses[38] = "Engenharia Ecônomica";
    courses[39] = "Química Geral para Engenharia";
    courses[40] = "Seminário em Automação e Controle";
    courses[41] = "Tópicos Especiais em Automação e Controle";
    courses[42] = "Controle de Sistemas Dinâmicos";

    courses[43] = "Princípios de Comunicações";
    courses[44] = "Comunicações Analógicas e Digitais";
    courses[45] = "Sistemas de Comunicações Móveis";
    courses[46] = "Sistemas de Comunicações Ópticas";
    courses[47] = "Sistemas Telefônicos";
    courses[48] = "Tópicos em Redes de Comunicações";
    courses[49] = "Arquitetura e Organização das Redes de Comunicações";
    courses[50] = "Tópicos em Sistemas de Comunicações Móveis";
    courses[51] = "Tópicos em Sistemas de Comunicações Ópticas";
    courses[52] = "Sistemas de Comunicações via Rádio";
    courses[53] = "Laboratório de Comunicações I";
    courses[54] = "Comunicação por Satélite";
    courses[55] = "Processos Estocásticos";
    courses[56] = "Empreendedorismo e Administração de Empresas";
    courses[57] = "Seminário de Telecomunicações I";
    courses[58] = "Tópicos Especiais em Telecomunicações I";
    courses[59] = "Linhas de Transmissão e Guias de Ondas";

    /*  data: Resultados da pesquisa realizada. Os índices, de 0 a 4, 
        representam, respectivamente, o número de estudantes com nenhum 
        interesse, pouco interesse, cursaria se disponível, muito 
        interesse e considera essencial */
    int data[60][5] = { {20, 5, 5, 8, 12},
                        {19, 8, 5, 10, 12},
                        {16, 9, 7, 9, 15},
                        {18, 5, 10, 9, 11},
                        {21, 6, 12, 6, 7},
                        {17, 7, 9, 11, 10},
                        {11, 5, 12, 16, 10},
                        {19, 5, 16, 9, 2},
                        {12, 3, 12, 20, 9},
                        {14, 3, 14, 12, 12},
                        {10, 3, 11, 14, 15},
                        {13, 3, 14, 17, 8},
                        {5, 3, 11, 12, 24},
                        {9, 2, 13, 14, 14},
                        {8, 1, 10, 20, 12},
                        {12, 6, 14, 8, 13},
                        {9, 2, 12, 16, 14},
                        {10, 3, 15, 15, 11},
                        {10, 3, 15, 15, 11},
                        {14, 6, 6, 16, 12},
                        {12, 6, 12, 11, 10},
                        {12, 6, 12, 11, 10},
                        {16, 3, 12, 13, 8},
                        {6, 5, 8, 14, 22},
                        
                        {21, 6, 7, 4, 7},
                        {19, 6, 2, 11, 10},
                        {18, 6, 7, 8, 6},
                        {11, 4, 9, 14, 9},
                        {13, 6, 9, 10, 9},
                        {18, 4, 6, 11, 8},
                        {22, 4, 5, 9, 7},
                        {19, 3, 9, 6, 9},
                        {17, 3, 5, 9, 13},
                        {14, 4, 5, 14, 11},
                        {18, 4, 5, 7, 13},
                        {22, 3, 9, 5, 6},
                        {19, 4, 5, 8, 9},
                        {21, 6, 5, 6, 7},
                        {20, 7, 9, 5, 4},
                        {16, 6, 7, 7, 11},
                        {23, 9, 7, 2, 4},
                        {21, 8, 6, 5, 6},
                        {21, 8, 4, 7, 7},
                        
                        {16, 7, 5, 8, 10},
                        {14, 7, 6, 8, 11},
                        {15, 7, 3, 9, 13},
                        {14, 6, 3, 12, 12},
                        {13, 6, 8, 10, 9},
                        {14, 7, 7, 11, 9},
                        {13, 6, 8, 8, 11},
                        {16, 9, 6, 8, 8},
                        {17, 8, 5, 9, 5},
                        {14, 8, 6, 8, 8},
                        {15, 7, 6, 7, 10},
                        {10, 6, 1, 10, 19},
                        {20, 7, 4, 6, 8},
                        {18, 4, 7, 7, 9},
                        {20, 7, 8, 4, 5},
                        {20, 7, 6, 7, 7},
                        {18, 4, 5, 10, 10} };

    /*  duration: Duração em horas/semana de cada disciplina */
    int duration[60] = { 4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         6,
                         4,
                         4,
                         6,
                         6,
                         4,
                         4,
                         2,
                         2,
                         6,
                         2,
                         4,
                         6,
                         
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         4,
                         2,
                         4,
                         4};

    /*  i, j: Variáveis de loop
        n: Número de disciplinas consideradas
        interest: Vetor com nível de interesse estudantil em cada disciplina
    */
    int i, j;
    int n = 60;
    int interest[n];

    /*  Loop para definição do nível de interesse
        estudantil utilizando os dados da pesquisa.
        Impressão do nome de cada disciplina, junto
        ao o nível de interesse estudantil calculado
        e sua duração em horas/semana.
    */
    for(i=0; i < n; i++) {
        interest[i] = 0;
        int sum = 0;
        printf("%s ", courses[i]);
        for(j=0; j < 5; j++) {
            interest[i] += (j*data[i][j])*10;
            sum += data[i][j];
        }
        interest[i] /= sum;
        printf("%d ", interest[i]);
        printf("%d", duration[i]);
        printf("\n");
    }

    int T = 50;
    /*  Impressão das disciplinas selecionadas, ocupando no máximo 
        T horas/semana, com maximização dos scores de interesse
        estudantil.
    */
    printf("\n");
    select_courses(courses, interest, duration, n, T);
}
