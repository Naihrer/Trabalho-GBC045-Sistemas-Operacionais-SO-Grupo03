# Universidade Federal de Uberlândia – UFU
**Bacharelado em Ciência da Computação**  
**GBC045 – Sistemas Operacionais – 2026/1**

### Integrantes do Grupo
* Alan Thúlio Dias Costa – 12411BSI315 
* Ananda Carolliny de Sá e Silva – 12411BSI360 
* Catiúscia da Conceição Deodato – 12411BSI340
* Marco Thulio de Santi Roncolato – 12421BCC036 
* Rhian Emanuel Rodrigues Pádua – 12411BCC051 

---

## 1. O que é escalonamento de CPU?
O escalonamento de CPU é o mecanismo responsável por decidir qual processo, dentre os que estão na fila de prontos, será selecionado para alocação e ser executado pela CPU. Ou seja, é o compartilhamento do processador entre múltiplos processos concorrentes em sistemas multiprogramados.

**Por que ele existe?**
O escalonamento de CPU é necessário em sistemas multiprogramados, onde múltiplos processos competem para utilizar recursos da CPU ao mesmo tempo. Como apenas um processo pode utilizar a CPU por vez (em um dado núcleo), o escalonador tem como objetivo principal decidir qual processo será selecionado para execução de forma a otimizar o uso do sistema.

## 2. System Call
System calls ou chamadas de sistema fornecem a interface entre um programa em execução e os serviços disponibilizados pelo sistema operacional. É o meio que uma aplicação de usuário tem para solicitar que o sistema operacional execute tarefas privilegiadas em sua camada – o kernel. As chamadas de sistema provocam uma interrupção de software (trap) que altera a modalidade de usuário para a modalidade kernel, garantindo uma mudança de privilégio. O kernel examina a interrupção, verifica qual serviço foi solicitado, executa a tarefa e retorna o controle para a aplicação, voltando para a modalidade de usuário.

## 3. Tema 7: Algoritmo SJF e Syscall getruntime()
Nesta proposta, designada como Tema 7 do trabalho prático, foram implementados e analisados dois elementos principais no xv6: um algoritmo de escalonamento e um mecanismo de medição de tempo de CPU.

* **O Padrão Original – Round Robin:** O sistema operacional xv6 utiliza nativamente o algoritmo Round Robin. Esse algoritmo funciona distribuindo a CPU de forma cíclica entre os processos ativos, concedendo a cada um um intervalo de tempo fixo (*quantum*). Após esse intervalo, ocorre a preempção e a troca de contexto.
* **O Algoritmo Implementado – Shortest Job First (SJF):** O SJF é um algoritmo de escalonamento que define como prioridade a tarefa mais curta. Entre os processos em estado de prontidão, terá prioridade aquele com o menor tempo de execução. Este algoritmo fornece o menor tempo médio de espera possível. Neste trabalho, implementamos uma heurística do SJF diretamente no kernel do xv6: o sistema rastreia o histórico de uso da CPU de cada processo e o escalonador sempre seleciona aquele que possui o menor tempo acumulado.
* **A Syscall – getruntime():** Para viabilizar a análise do SJF, criamos a chamada de sistema `getruntime()`. Ela acessa a estrutura do processo ativo no kernel e retorna o valor acumulado do seu tempo de execução. Esse tempo é medido em *ticks* de clock gerados pelas interrupções de hardware.

## 4. Funcionamento da Solução
A solução substitui o mecanismo original do xv6, integrando a coleta de tempo com a decisão de escalonamento:
1. **Contabilização do tempo de CPU:** A cada interrupção de temporizador de hardware (no arquivo `trap.c`), o kernel identifica o processo em execução e incrementa um contador (`runtime`) presente na sua estrutura (PCB).
2. **Seleção via SJF:** O escalonador (no arquivo `proc.c`) varre a tabela de processos e compara o `runtime` de todos que estão no estado `RUNNABLE`. A troca de contexto é realizada para o processo que apresentar o menor valor de tempo.
3. **Coleta com getruntime:** A chamada de sistema permite que programas de usuário consultem o tempo de CPU.
4. **Validação:** O programa `testesjf` executa um laço de processamento chamando `getruntime()` no início e no fim, comprovando o tempo de CPU alocado para aquela tarefa sob o novo escalonador.

## 5. Arquivos Modificados no xv6
Para a entrega da Etapa 2, as seguintes modificações foram estruturadas na arquitetura do kernel e do espaço de usuário:

* **`kernel/proc.c`** -> Modificação na função `scheduler` (Implementação do algoritmo SJF e varredura de processos) e `allocproc` (zerando o tempo inicial).
* **`kernel/syscall.c`** -> Roteamento e mapeamento da nova syscall.
* **`user/user.h`** -> Definição da interface no espaço de usuário para `getruntime()`.
* **`kernel/proc.h`** -> Adição do campo `runtime` na estrutura `struct proc`.
* **`kernel/trap.c`** -> Atualização do tempo do processo a cada tick de interrupção do temporizador.
* **`kernel/syscall.h`** -> Definição do número da syscall.
* **`user/usys.pl`** -> Inclusão do ponto de entrada (entry) para gerar o Assembly da chamada.

## 6. Roteiro de Reprodução
Para testar o funcionamento do escalonador SJF e da chamada `getruntime()` utilizando os arquivos fornecidos nesta entrega:

1. No ambiente Linux (Ubuntu recomendado) contendo uma instalação limpa do xv6-riscv, substitua os arquivos originais pelos arquivos modificados disponibilizados na pasta `code/` deste repositório, respeitando a hierarquia de diretórios (`kernel/` e `user/`).
2. Adicione o arquivo do programa de teste `testesjf.c` (disponível na pasta `tests/`) ao diretório `user/` e certifique-se de que ele esteja incluído no `Makefile` (UPROGS).
3. Compile o sistema e inicie o emulador QEMU utilizando o comando:
   ```bash
   make qemu
