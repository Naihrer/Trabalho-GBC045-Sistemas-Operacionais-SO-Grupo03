Universidade Federal de Uberlândia – UFU |
Bacharelado em Ciência da Computação |
GBC – Sistemas Operacionais – 2026/1 |

Alan Thúlio Dias Costa – 12411BSI315 

Ananda Carolliny de Sá e Silva – 12411BSI360 

Catiúscia da Conceição Deodato – 12411BSI340

Marco Thulio de Santi Roncolato – 12421BCC036 

Rhian Emanuel Rodrigues Pádua – 12411BCC051 

  1. O que é escalonamento de CPU? O escalonamento de CPU é o mecanismo responsável por decidir qual processo, dentre os que estão na fila de prontos, será selecionado para alocação e ser executado pela CPU, ou seja, é o compartilhamento do processador entre múltiplos processos concorrentes em sistemas multiprogramados.
     
  1.1. Por que ele existe? O escalonamento de CPU é necessário em sistemas multiprogramados, onde múltiplos processos competem para utilizar recursos da CPU ao mesmo tempo. Como apenas um processo pode utilizar a CPU por vez, o escalonador tem como objetivo principal decidir qual processo será selecionado para execução.
  
  2. System call - System calls ou chamadas de sistema fornecem a interface entre um programa em execução e os serviços disponibilizados pelo sistema operacional, ou seja, é um meio que uma aplicação tem para solicitar que o sistema operacional execute tarefas privilegiadas em sua camada – o kernel. As chamadas de sistema provocam uma interrupção de software que, altera a modalidade de usuário para modalidade kernel, garantindo uma mudança de estado. Então o kernel examina a interrupção e verifica qual serviço foi solicitado, recebe informações necessárias, executa a tarefa e retorna o controle para a aplicação, alterando novamente para a modalidade de usuário.

  3. Algoritmo e mecanismos implementados nesta proposta, são abordados dois elementos principais: um algoritmo de escalonamento e um mecanismo de medição de tempo de CPU.

     i. Algoritmo de escalonamento – Round Robin O sistema operacional xv6 utiliza o algoritmo Round Robin como política padrão de escalonamento de processos. Esse algoritmo funciona distribuindo a CPU de forma cíclica entre os processos ativos, concedendo a cada um, um intervalo de tempo fixo. Após esse intervalo, ocorre a troca de contexto, permitindo que outro processo seja executado. Esse mecanismo garante o compartilhamento equilibrado da CPU, evita que processos fiquem sem executar e apresenta simplicidade de implementação.

     ii. Algoritmo analisado – Shortest Job First (SJF) O STF – Shortest Job First – é um algoritmo de escalonamento não preemptivo que define como prioridade a tarefa mais curta, ou seja, aos processos que estão em estado pronto e competem a CPU simultaneamente, terá prioridade aquele com menor tempo de execução. Este algoritmo fornece o menor tempo médio de espera possível entre os processos concorrentes quando os processos estão disponíveis simultaneamente, e tem como objetivos:

     • Maximizar utilização da CPU – evitar ociosidade e aumentar a eficiência do sistema;

     • Maximizar throughput (vazão) – quanto mais processos finalizados melhor desempenho;

     • Minimizar tempo de espera (waiting time) – tempo que o processo fica na fila de prontos;

     • Garantir justiça – evitar starvation e garantir que todos os processos tenham chance de executar;

     O algoritmo Shortest Job First é estudado como estratégia alternativa de escalonamento e sua lógica consiste em selecionar o processo com menor tempo de CPU. Entre suas características estão a redução do tempo médio de espera, a possibilidade de implementação e a dependência de conhecimento prévio do tempo de execução. Neste trabalho, o SJF não será implementado diretamente no xv6, sendo apenas simulado com base nos dados coletados.

        iii. Mecanismo implementado – getruntime A chamada de sistema getruntme() não é padrão em sistemas operacionais reais, e pode ser definida como uma extensão didática do sistema operacional xv6. Essa chamada acessa informações contidas no kernel, especificamente relacionadas à estrutura do processo, retornando o valor acumulado de tempo de execução. Esse tempo é normalmente medido em unidades chamads de ticks, que correspondem às informações do relógio do sistema. O principal mecanismo desenvolvido será a chamada de sistema getruntime, responsável por medir o tempo de CPU utilizado pelos processos. Dessa forma, este mecanismo permite monitorar o uso da CPU por processo, coletar dados reais de execução e servir como base para a simulação de algoritmos de escalonamento.

4. Funcionamento da solução - A solução proposta baseia-se na integração entre o funcionamento real do xv6 e uma análise posterior dos dados coletados.
       
      i. Execução dos processos - Os processos são executados normalmente no xv6 sob o controle do algoritmo Round Robin. Durante a execução, o sistema alterna entre processos e cada um recebe uma fatia de tempo da CPU.

     ii. Contabilização do tempo de CPU - A cada interrupção de temporizador, o sistema identifica o processo em execução e incrementa um contador de tempo associado a esse processo. Esse contador representa o tempo total de CPU consumido.

    iii. Coleta dos dados com getruntime - A chamada de sistema getruntime permite consultar o tempo de CPU de um processo específico e retornar esse valor para o espaço de usuário. Esses dados podem ser exibidos na tela ou armazenados para análise posterior.

    iv. Simulação do algoritmo SJF - Com os tempos coletados, um programa em linguagem C, executado fora do xv6, lê os dados e organiza os processos pelo menor tempo de CPU, gerando uma sequência que simula a execução segundo o algoritmo SJF.

    v. Resultado esperado - A solução permite observar o comportamento real dos processos no xv6, comparar com uma política de escalonamento teórica e compreender o impacto da escolha do algoritmo de escalonamento.

  5. Aplicações práticas - O mecanismo de execução de tempo de CPU é utilizado em escalonamento de processos, análise de desempenho, monitoramento de uso de recursos, ou seja, fornece a base para a implementação de algoritmo SJF.
     
  6. Considerações finais - A combinação do mecanismo getruntime() com o algoritmo SJF permite explorar, de forma prática, conceitos fundamentais de escalonamento de CPU. Embora a implementação represente uma aproximação do comportamento ideal do SJF, ela evidencia desafios reais enfrentados por sistemas operacionais, como a ausência de conhecimento prévio sobre o tempo de execução dos processos.
