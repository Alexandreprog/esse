#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> /*Serve para que se possa utiliar a função "Sleep()" */

#define MAX 3

extern void cadastro(char nome[], int idade, int registro, char sexo_user[], char arquivo[]);
extern void inicializa_funcionarios();
extern int procurar_vazio();
extern void cadastro_funcionario();
extern void tela_login();
extern int escolha_adm();
extern int escolha_funcinario();
extern void cadastrar_paciente();
extern void arquivopaciente();

int main(){

	setlocale(LC_ALL, "Portuguese");											/*Coloca a acentuação do português na saída */

	printf("Seja bem-vindo ao nosso sistema.\n\n");
	Sleep(3000);																/*Coloca um temporizador para que a mensagem de "bem-vindo" desapareça*/
	system("cls");

	tela_login();

	return 0;
}

struct funcionario{ 					/*Esse bloco possui os dados do paciente a serem armazenados*/
	char nome_funcionario[51];
	char sexo_funcionario[11];
	char endereco_funcionario[50];
	unsigned int idade_funcionario[1];
	char login_user[30];
	char senha_user[16];
}member[MAX];

int situacao = 0; /*Usada para verificar a situação do banco de dados. Foi decalarada de forma global pois exsitem funções diferentes que necessitam de seu valor.*/

void tela_login(){															/*Verifica o login e a senha dos funcionários.*/
	char login_sistema[30], senha_sistema[16];
	char login_mestre[] = "ryann.arruda", senha_mestre[] = "diretor";

	setbuf(stdin, NULL);
	printf("Login:\n");
	gets(login_sistema);

	printf("\nSenha:\n");
	gets(senha_sistema);

	system("cls");

	if((strcmp(login_sistema, login_mestre) == 0) && (strcmp(senha_sistema, senha_mestre) == 0)){
		escolha_adm();
	}

	else if((strcmp(login_sistema, member[situacao].login_user) == 0) && (strcmp(senha_sistema, member[situacao].senha_user) == 0)){   /*PARTE DE CÓDIGO A SER CORRIGIDA*/
		escolha_funcinario();
		Sleep(800);
	}

	else {
		printf("Login ou senha estão incorretas.");
		Sleep(800);
		system("cls");
		tela_login();
	}
}

int escolha_adm(){ 																		/*Mostra as opções de escolha para o administrador cadastrado no sistema. */
	int  opcao = 0, retorno = 1;

	printf(" 1 - Cadastrar Funcionário\t");
	printf(" 2 - Sair do Sistema\t\n\n");

	printf("Insira o número correspodente a opção que você deseja acessar:\n");
	scanf("%d", &opcao);
	system("cls");

	switch (opcao){
		case 1:
			cadastro_funcionario(retorno);
			break;

		case 2:
			tela_login();
			break;

		default:
			escolha_adm();
			break;
	}

	return 0;
}

int escolha_funcinario(){ 																/*Mostra as opções de escolha para os funcionários cadastrados no sistema. */
	int  opcao = 0;

	printf(" 1 - Cadastrar Paciente\t\n");
	printf(" 2 - Acessar Dados do Paciente\t\n");							/*FALTA CONSTRUIR ESSE BLOOCO DE CÓDIGO*/
	printf(" 3 - Cadastrar Sintomas do Paciente\t\n"); 						/* FALTA- SE CONSTRUI: DEVE-SE VERIFICAR SE O PACIENTE JÁ ESTÁ CADASTRADO ANTES DE INSERIR OS SINTOMAS*/
	printf(" 4 - Sair do Sistema\t\n");

	printf("Insira o número correspodente a opção que você deseja acessar:\n");
	scanf("%d", &opcao);
	system("cls");

	switch (opcao){
		case 1:
			cadastrar_paciente();
			break;

		case 2:
		    arquivopaciente();
			break;

		case 3:
			break;

		case 4:
			tela_login();
			break;

		default:
			escolha_funcinario();
			break;
	}

	return 0;
}

void inicializa_funcionarios(){ 		/*Inicializa a matriz de struct com o primeiro elemento nulo (\0) */
	register int t;

	for(t = 0; t < MAX; t++){
		member[MAX].nome_funcionario[0] = '\0';
	}
}

int procurar_vazio(){					/*Procura um elemento vazio na matriz de struct para que se possa cadastrar novos funcionários*/
	register int p;

	for (p = 0; member[p].nome_funcionario[0] && p < MAX; p++);

	if(p == MAX){
		return -1;
	}

	return p;
}

void cadastro_funcionario(int x){   					  /*Esse bloco realiza o cadastramento dos dados do funcionário*/

	inicializa_funcionarios();

	situacao = procurar_vazio();
	if(situacao == -1){
		printf("Banco de dados cheio!");
		Sleep(800);
		system("cls");

		if(x == 1){
			escolha_adm();
		}

		else{
			escolha_funcinario();
		}
	}

	setbuf(stdin, NULL);				/*Limpa o buffer do teclado;*/
	printf("Insira o nome do funcionário:\n");
	gets(member[situacao].nome_funcionario);
	printf("\nInsira o sexo do funcionário:\n");
	gets(member[situacao].sexo_funcionario);
	printf("\nInsira o endereço do funcionário:\n");
	gets(member[situacao].endereco_funcionario);
	printf("\nInsira a idade do funcionário:\n");
	scanf("%d", &member[situacao].idade_funcionario);
	printf("\nInsira o login do funcionário:\n");
	setbuf(stdin, NULL);				/*Limpa o buffer do teclado;*/
	gets(member[situacao].login_user);
	printf("\nInsira a senha do funcionário:\n");
	gets(member[situacao].senha_user);
	system("cls");

	procurar_vazio();

	FILE *informacoes;

	informacoes = fopen ("dados_func.txt", "w");

	if(informacoes == NULL){
		printf("Não foi possível salvar os dados cadastrados, por favor, tente novamente!");
		member[situacao].nome_funcionario[0] = '\0';
		cadastro_funcionario(x);
	}
	fprintf(informacoes, "%s\n", member[situacao].login_user);
	fprintf(informacoes, "%s\n", member[situacao].senha_user);
	fclose(informacoes);

	if(x == 1){						/*Bloco if com a funcionalidade de receber o retorno da tela de login, se esse retorno for 1 significa que quem logou foi o dono da empresa*/
		escolha_adm();
	}

	else{
		escolha_funcinario();
	}
}

void cadastro(char nome[], int idade, int registro, char sexo_user[], char arquivo[]){   /*Realiza o cadastro dos novos usuários criando uma documento para os dados*/

	FILE *dados;

	dados = fopen (arquivo, "w");
	fprintf(dados, "\t\tFicha do Paciente\t\t\n\n");
	fprintf(dados, "Nome: %s", nome);
	fprintf(dados, "\n\nIdade: %d", idade);
	fprintf(dados, "\n\nRegistro: %d", registro);
	fprintf(dados, "\n\nSexo: %s", sexo_user);
	fclose(dados);
}

void cadastrar_paciente(){
		int idade = 0, numero_registro = 0;
		char nome[50], sexo_user [11];
		char arquivo[50], extensao [5] = ".txt";									/* Passa extenssão ".doc" para o arquivo poder ser criado*/
		char resposta[4];

		printf ("Insira os seguintes dados para realizar o cadastro.\n\n");
		Sleep(1000);

		setbuf(stdin, NULL);
		printf("Nome:");
		gets(nome);

		printf("\n\nIdade:");
		scanf ("%d" , &idade);

		if(idade < 0 ){
			printf("Idade não reconhecida ou inválida, tente novamente com uma idade válida.");
			cadastrar_paciente();
		}

		printf("\n\nRegistro:");
		scanf ("%d" , &numero_registro);

		if(numero_registro < 0){
			printf("Registro não reconhecindo ou inválido, tente novamente com um registro válido.");
			cadastrar_paciente();
		}

		printf("\n\nSexo:");
		scanf ("%s" , &sexo_user);

		if(!stricmp(sexo_user, "Masculino")){
			strcpy(arquivo, nome);											/*Pega o nome do paciente e passa para a string "arquivo";*/
			strcat(arquivo, extensao);										/*Junta com o nome do paciente a extensão ".doc" criando arquivos documentos diferentes para pacientes diferentes;*/
			cadastro(nome, idade, numero_registro, sexo_user, arquivo);

			printf("Insira os sintomas:");

		}

		else if(!stricmp(sexo_user, "Feminino")){
			strcpy(arquivo, nome);											/*Pega o nome do paciente e passa para a string "arquivo";*/
			strcat(arquivo, extensao);										/*Junta com o nome do paciente a extensão ".doc" criando arquivos documentos diferentes para pacientes diferentes;*/
			cadastro(nome, idade, numero_registro, sexo_user, arquivo);
		}

		else{
			printf("Sexo inválido!");
		}

		setbuf(stdin, NULL);
		printf("\nDeseja cadastrar outro paciente?\n");
		gets(resposta);

		if(!strcmp(resposta, "Sim")){
			system("cls");
			cadastrar_paciente();
		}

		else{
			escolha_funcinario();
		}
}
void arquivopaciente(){

    char url[50];
    printf("Digite o nome do paciente:\n");
    scanf("%s", &url);
    FILE *file;

    file = fopen(url, "r");

    if(file == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");//mensagem exibida caso o arquivo nao exista
        getchar();
        exit(0);
    }

    char ler[100];

    while(fgets(ler, 100, file) != NULL){ //Vai ler o arquivo ate encontrar o fim
        setlocale(LC_ALL, "Portuguese");
        printf("%s", ler);
    }

     fclose(file);
}
