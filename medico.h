#ifndef MEDICO_H
#define MEDICO_H

// Capacidade máxima diária de pacientes para filas e heap prioritário
#define MAX_DIARIO 20

// Estrutura que representa um paciente cadastrado
typedef struct {
    char nome[100];   // Nome completo do paciente (até 99 caracteres + '\0')
    int idade;        // Idade em anos
    char rg[20];      // Número de RG (até 19 caracteres + '\0')
    int dia, mes, ano;// Data de entrada: dia, mês e ano
} Paciente;


/* === Funções de Cadastro (lista encadeada) === */

// Insere um novo paciente no início da lista
void cadastrarPaciente();

// Busca e exibe dados de um paciente pelo RG
void consultarPaciente();

// Lista todos os pacientes cadastrados
void listarPacientes();

// Atualiza os dados de um paciente existente
void atualizarPaciente();

// Remove um paciente da lista pelo RG
void removerPaciente();


/* === Funções de Atendimento Normal (fila FIFO) === */

// Enfileira um paciente no fim da fila normal
void enfileirarNormal();

// Desenfileira (atende) o paciente no início da fila normal
void desenfileirarNormal();

// Exibe toda a fila normal na ordem de atendimento
void mostrarFilaNormal();


/* === Funções de Atendimento Prioritário (max-heap por idade) === */

// Insere um paciente no heap de prioridade (mais velho sobe)
void enfileirarPrioritario();

// Remove (atende) o paciente mais velho do heap
void desenfileirarPrioritario();

// Exibe o conteúdo atual do heap (sem garantir ordenação externa)
void mostrarFilaPrioritaria();


/* === Funções de Pesquisa / Ordenação (Árvore Binária de Busca) ===
 * Cada função monta uma ABB ordenada por um critério e exibe em ordem crescente.
 */

// Monta/exibe ABB ordenada pelo ano de registro (ascendente)
void mostrarPorAno();

// Monta/exibe ABB ordenada pelo mês de registro (ascendente)
void mostrarPorMes();

// Monta/exibe ABB ordenada pelo dia de registro (ascendente)
void mostrarPorDia();

// Monta/exibe ABB ordenada pela idade do paciente (ascendente)
void mostrarPorIdade();


/* === Funções de Desfazer Operações (pilha) === */

// Exibe o log das operações de enfileiramento/desenfileiramento normal
void mostrarLogOperacoes();

// Desfaz a última operação de enfileirar ou desenfileirar na fila normal
void desfazerUltimaOperacao();


/* === Funções de I/O em Arquivo === */

// Carrega pacientes de “pacientes.txt” para a lista (substitui conteúdo atual)
void carregarDados();

// Salva a lista de pacientes em “pacientes.txt” (formato CSV simples)
void salvarDados();


/* === Função Sobre o Sistema === */

// Exibe informações de desenvolvedor, curso, disciplina e data de compilação
void mostrarSobre();

#endif /* MEDICO_H */
