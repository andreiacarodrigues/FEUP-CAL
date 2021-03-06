#include "Graph.h"
#include "Empresa.h"
#include "Recursos.h"
#include "Excecoes.h"
#include "Gerador.h"
#include "graphviewer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

//CLIENTE
//==============================================================================================================

void addCliente(Empresa *e){
	string nome;
	Morada *casa = new Morada();
	Morada *escola = new Morada();
	int id;

	clrscr();
	displayTitulo("ADICIONAR CLIENTE");

	cout << "Nome: ";
	cin.ignore(1000,'\n');
	getline(cin,nome);
	cout << "Ponto de Recolha (id): ";
	cin >> id;
	casa = e->getMapa()->getPonto(id);

	if(casa->getID() == -1){
		throw PontoInexistente(*casa);
	}
	//so sao aceites pontos de recolha que s�o estao assinalados como pontos de recolha
	if(!e->getMapa()->isPontoInteresse(*casa))
		throw PontoRecolhaInvalido(*casa);

	Cliente *c = new Cliente(nome,casa);
	if(!e->getIsEscola()){
		cout << "Morada Escolar (id): ";
		cin >> id;

		escola = e->getMapa()->getPonto(id);
		if(escola->getID() == -1){
			throw PontoInexistente(*escola);
		}
		c->setNovaEscola(escola);
	}
	else
		c->setNovaEscola(e->getEndereco());

	if(e->addCliente(c) == false)
		throw ClienteJaExiste(nome,*escola,*casa);
	cout << endl;

	e->update();

	esperar();
	throw VoltarAtras();
}

void removerCliente(Empresa *e){
	int id;

	clrscr();
	displayTitulo("REMOVER CLIENTE");
	e->displayClientes();
	cout << "\nDigite o ID do cliente que quer remover: ";
	cin >> id;

	if(e->removeCliente(id) == false)
		throw ClienteInexistente(id);
	cout << endl;

	e->update();

	esperar();
	throw VoltarAtras();
}

void verClientes(Empresa *e){
	clrscr();
	displayTitulo("CLIENTES");
	e->displayClientes();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

//-------------------------------------//
// NOVO
//-------------------------------------//
void procurarCLientes(Empresa *e){
	clrscr();
	displayTitulo("PROCURAR CLIENTE");

	string nome;

	cout << "Introduza o Nome : " << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, nome);
	e->proximitySearchClient(nome);	//pesquisa aproximada na lista de clientes pelo nome introduzido
	cout << endl;
	esperar();
	throw VoltarAtras();
}

//-------------------------------------//
// NOVO
//-------------------------------------//
void procurarClientesMorada(Empresa *e){
	clrscr();
	displayTitulo("PROCURAR CLIENTES POR MORADA");
	string morada;

	cout << "Introduza a morada : " << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, morada);
	e->displayClientesMorada(morada);	//pesquisa exata : retorna todos os clientes que moram nessa morada
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuClientes(Empresa *e){
	int op;
	do {
		clrscr();
		displayMenuClientes();
		opccao(op, 1, 6);
		switch (op) {
		case 1: { //add
			addCliente(e);
			break;
		}
		case 2: { //rem
			removerCliente(e);
			break;
		}
		case 3: {//ver
			verClientes(e);
			break;
		}
		case 4: {//pesq. nome
			procurarCLientes(e);
			break;
		}
		case 5:{//pesq.morada
			procurarClientesMorada(e);
			break;
		}
		case 6: {
			throw VoltarAtras();
		}
		}
	} while (1);
}


//VEICULO
//==============================================================================================================

void addVeiculo(Empresa *e){
	string matricula;
	int num;
	//char classe;

	clrscr();
	displayTitulo("ADICIONAR VEICULO");
	cout << "Matricula: ";
	cin >> matricula;
	cout << "N�mero de lugares: ";
	cin >> num;

	Veiculo *v = new Veiculo(matricula, num);

	if(!e->addTransporte(v))
		throw VeiculoJaExiste(matricula);

	cout << endl;
	esperar();
	throw VoltarAtras();
}

void removerVeiculo(Empresa *e){
	string m;
	clrscr();
	displayTitulo("REMOVER VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	Veiculo * v = new Veiculo(m,0);
	if(!e->removeTransporte(v))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verVeiculos(Empresa *e){
	clrscr();
	displayTitulo("VEICULOS");
	e->displayVeiculos();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void trajetoVeiculoIda(Empresa *e){

	string m;
	clrscr();
	displayTitulo("VER TRAJETO DO VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	if(!e->displayTrajetosIda(m))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void trajetoVeiculoVolta(Empresa *e){

	string m;
	clrscr();
	displayTitulo("VER TRAJETO DO VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	if(!e->displayTrajetosVolta(m))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuVeiculos(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuVeiculos();
		opccao(op, 1, 6);
		switch (op) {
		case 1: { //add
			addVeiculo(e);
			break;
		}
		case 2: { //rem
			removerVeiculo(e);
			break;
		}
		case 3: {//ver
			verVeiculos(e);
			break;
		}
		case 4: {//ver traj ida
			trajetoVeiculoIda(e);
			break;
		}
		case 5:{//ver traj volta
			trajetoVeiculoVolta(e);
			break;
		}
		case 6: {
			throw VoltarAtras();
		}
		}
	} while (1);
}
//PONTOS DE RECOLHA
//==============================================================================================================

//-------------------------------------//
// NOVO
//-------------------------------------//
void addPontoRecolha(Empresa *e){
	int id;

	clrscr();
	displayTitulo("ADICIONAR PONTO DE RECOLHA");

	string morada;
	cout << "Procurar Morada:  "<< endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, morada);
	vector<Morada> moradas = e->getMapa()->getAllMorada();	//podemos adicionar uma morada pesquisada por proximidade (todas as ruas)
	e->proximitySearchMorada(moradas,morada);
	cout << endl;

	cout << "Morada Recolha (id): ";
	cin >> id;
	Morada *ponto = e->getMapa()->getPonto(id);

	if(ponto->getID() == -1){
		throw PontoInexistente(*ponto);
	}

	if(!e->getMapa()->setPontoInteresse(*ponto,true))
		throw PontoRecolhaInvalido(*ponto);

	cout << endl;
	esperar();
	throw VoltarAtras();
}

void removerPontoRecolha(Empresa *e){
	int id;

	clrscr();
	displayTitulo("REMOVER PONTO DE RECOLHA");

	e->displayPontosRecolha();

	cout << "Morada Recolha (id): ";
	cin >> id;
	Morada *ponto = e->getMapa()->getPonto(id);

	if(ponto->getID() == -1){
		throw PontoInexistente(*ponto);
	}
	e->setClientesPI(ponto->getID());
	e->getMapa()->setPontoInteresse(*ponto,false);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

//-------------------------------------//
// NOVO
//-------------------------------------//
void verPontosRecolha(Empresa *e){
	clrscr();
	displayTitulo("PONTOS DE RECOLHA");
	e->displayPontosRecolha();	//usa pesquisa exata para indicar o numero de criancas por rua
	cout << endl;
	esperar();
	throw VoltarAtras();
}

//-------------------------------------//
// NOVO
//-------------------------------------//
void procurarPontosRecolha(Empresa *e){
	clrscr();
	displayTitulo("PROCURAR PONTOS DE RECOLHA");
	string morada;
	cout << "Introduza a morada de recolha : " << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, morada);
	vector<Morada> pr = e->getMapa()->getInterestPoints();
	e->proximitySearchMorada(pr,morada);	//pesquisa aproximada dos pontos de recolha possiveis (nome da rua)
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuPontos(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuPI();
		opccao(op, 1, 5);
		switch (op) {
		case 1: { //ver escolas
			addPontoRecolha(e);
			break;
		}
		case 2: { //ver por alunos
			removerPontoRecolha(e);
			break;
		}
		case 3: {//ver
			verPontosRecolha(e);
			break;
		}
		case 4: {
			procurarPontosRecolha(e);
			throw;
		}
		case 5:{
			throw VoltarAtras();
		}
		}
	} while (1);
}
//Escolas
//==============================================================================================================
void verEscolas(Empresa * e){
	clrscr();
	displayTitulo("ESCOLAS");
	e->displayEscolas();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verAlunosEscolas(Empresa * e){
	clrscr();
	displayTitulo("ESCOLAS");
	vector<Cliente *> clientes;
	for (unsigned int i = 0; i < e->getEscolas().size(); ++i) {
		cout << "Escola - " << *e->getEscolas()[i] << endl;
		clientes = e->getClientesEscola(e->getEscolas()[i]);
		for (int j = 0; j < clientes.size(); ++j) {
			cout << *clientes[j] << endl;
		}
		cout << endl;
	}
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuEscolas(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuEscolas();
		opccao(op, 1, 3);
		switch (op) {
		case 1: { //ver escolas
			verEscolas(e);
			break;
		}
		case 2: { //ver por alunos
			verAlunosEscolas(e);
			break;
		}
		case 3: {
			throw VoltarAtras();
		}
		}
	} while (1);
}

//ArestasBloqueadas
//==============================================================================================================

void bloquearArestas(Empresa *e){
	clrscr();
	displayTitulo("ARESTAS BLOQUEADAS");
	int id;
	cout << "ID da aresta a bloquear : \n";
	cin >> id;

	e->getMapa()->setBlockedEdge(id, true);
	//mensagem de erro?

	e->update();

	esperar();
	throw VoltarAtras();
}

void desbloquearArestas(Empresa *e){
	clrscr();
	displayTitulo("ARESTAS BLOQUEADAS");

	e->getMapa()->displayBlockedEdges();
	int id;
	cout << "ID da aresta a desbloquear : \n";
	cin >> id;

	e->getMapa()->setBlockedEdge(id, false);
	//mensagem de erro?

	e->update();

	esperar();
	throw VoltarAtras();
}

void menuArestas(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuArestas();
		opccao(op, 1, 3);
		switch (op) {
		case 1: { //bloquear arestas
			bloquearArestas(e);
			break;
		}
		case 2: { //desbloquear arestas
			desbloquearArestas(e);
			break;
		}
		case 3: {
			throw VoltarAtras();
		}
		}
	} while (1);
}

//==============================================================================================================
void opMenuInicial(Empresa *e, int op) {
	switch (op) {
	case 1: { //veiculos
		menuVeiculos(e);
		break;
	}
	case 2: { //clientes
		menuClientes(e);
		break;
	}
	case 3: {//trajetos
		menuPontos(e);
		break;
	}
	case 4: { //escolas
		menuEscolas(e);
		break;
	}
	case 5:{
		menuArestas(e);
		break;
	}
	case 6:{
		e->writeLastAndInfo();
		break;
	}
	}
}

void menuInicial(Empresa *e) {
	int op;
	do {
		try {
			clrscr();
			displayMenuInicial(e->getNome());
			opccao(op, 1, 6);
			opMenuInicial(e, op);
		}
		catch (OpccaoInvalida<int>(x)) {
			cout << x.getOp() << " nao se encontra entre as opccoes "
					<< x.getMin() << " e " << x.getMax() << endl << endl;
			esperar();
		}
		catch (VoltarAtras) {
		}
		catch (InputFail) {
			cout << endl;
			esperar();
		}
		catch (ClienteJaExiste(e)){
			cout << "Nao foi possivel adicionar o cliente com nome " << e.getNome() << " ou morada escolar " << e.getMoradaEscola() << " e residencia "<< e.getMoradaResidencia() << ".\n";
			esperar();
		}

		catch ( ClienteInexistente(e)){
			cout << "Nao existe um cliente com o id " << e.getID() << endl;
			esperar();
		}

		catch (PontoInexistente(e)){
			cout << "Nao existe no mapa esse ponto\n";
			esperar();
		}
		catch (VeiculoJaExiste(e)){
			cout << "Ja existe um veiculo com a matricula " << e.getMatric()<< endl;
			esperar();
		}
		catch (VeiculoInexistente(e)){
			cout << "Nao existe um veiculo com a matricula " << e.getMatric()<< endl;
			esperar();
		}
		catch (ResidenciaInvalida(e)){
			cout << "A residencia " << e.getResidencia() << " nao pode ser uma escola\n";
			esperar();
		}
		catch (VeiculosInsuficientes()){
			cout << "Nao ha veiculos suficientes para o numero de clientes. Adicione um novo veiculo.\n";
			esperar();
		}
		catch(PontoRecolhaInvalido(e)){
			cout << "Nao existe um ponto de recolha " << e.getPonto() << endl;
			esperar();
		}
	} while (op != 6);
}

//Empresa
//==============================================================================================================

int main(){

	int op;
	Empresa *e;

	do{
		cout << " 1 - Usar ultimo ficheiro \n 2 - Criar novo ficheiro \n";
		cin >> op;

		if(op == 1)	//ultimo ficheiro -> l� last.txt com as informacoes da empresa
		{
			e = new Empresa();
			e->readLast();
		}
		else if(op == 2)// vai para o gerador
		{
			int num;
			string b;
			bool esc;

			cout << "Numero de alunos : ";
			cin >> num;

			do {
				cout << "E escola ? (S/N) ";
				cin >> b;
			}
			while(b != "S" && b != "N" && b != "s" && b != "n");

			if(b == "S" || b == "s")
				esc = true;
			else if(b == "N" || b == "n")
				esc = false;

			Gerador g = Gerador(num, esc);
			e = g.getEmpresa();
		}
	}while(!(op == 1 || op == 2));

	menuInicial(e);
	delete(e);
	return 0;
}
