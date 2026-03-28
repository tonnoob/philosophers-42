*Este projeto foi criado como parte do currículo 42 por osousa-d.*

# Philosophers

## Descrição

O projeto **Philosophers (philo)** é um exercício clássico de programação concorrente, baseado no problema dos jantares dos filósofos.

- Pense que tem X números de filósofos sentados em uma mesa.
- Cada filósofo traz para a mesa **1 garfo**, e deixa esse garfo do seu lado, ou seja, 1 garfo, 1 filósofo, 1 garfo, 1 filósofo...
- Contudo, para **comer**, o filósofo precisa de **2 garfos**, um garfo da esquerda e outro da direita.
- Os filósofos podem fazer 4 ações: 
	- **Pegar os garfos**
	- **Comer**
	- **Dormir**
	- **Pensar**

- O filósofo após **comer** é obrigado a **dormir** pra fazer a digestão, depois ele **pensa**, e depois pode **comer** novamente, mas só pode comer com **2 garfos**.

- O Desafio é justamente brincar com o tempo que os filósofos demoram pra fazer as ações usando **threads**.

- O que é **Threads**?
De forma bem simples, são **subprocessos** dentro de um **processo**.
Pois cada filósofo executam as ações simuntaneamente, contudo, o que faz eles diferenciarem se um **processo** (filósofo) ta usando um garfo, tornando o garfo indisponivel, é os **mutexes**, então quando um **processo** (filósofo) usa um **garfo** ele trava o **mutex** desse **garfo** e nenhum outro **processo** (filósofo) pode pegar esse mesmo garfo (lembrando que eles pegam os garfos que estão do lado deles).

- No input do projeto, colocamos os seguintes dados:
	- **Número de filósofos** na mesa.
	- **Tempo para morrer** dos filósofos (em milissegundo), se um filósofo ficar sem comer dentro desse tempo ele morre.
	- **Tempo para comer** (em milissegundo), ou seja, o filósofo vai demorar esse tempo para comer.
	- **Tempo para dormir** (em milissegundo), tempo que o filósofo demora dormindo.
	- **[Número de refeições]**, quantas vezes os filósofos tem que comer pra ficar saciados (esse input é opcional).

---
### Detalhes da Implementação
Esta implementação utiliza:
- **Threads** que são os filósofos.
- **Mutexes** para travar os garfos.
- **Duas Structs**
	- **t_philo** Contendo todos os dados do filósofo individual:
		- **id** (se é o filósofo 1, 2, 3...);
		- **thread** (subprocesso que vai ser criado);
		- **last_meal_time** (tempo da ultima refeição);
		- **meals_eaten** (quantas refeições realizou);
		- **philo_is_full** (pra saber se já fez todas as refeições);
		- **meal_mutex**;
		- **left_fork**(ponteiro para o garfo esquerdo);
		- **right_fork**(ponteiro para o garfo direito);
		- **p_data** (ponteiro para a struct com todos os dados globais);
	- **t_data** Contendo todos os dados globais:
		- **n_philo** (quantidade de filósofos);
		- **time_to_die** (tempo para morrer);
		- **time_to_eat** (tempo para comer);
		- **time_to_sleep** (tempo para dormir);
		- **times_a_philo_must_eat** (número de refeições que um filósofo deve realizar);
		- **time_start** (tempo inicial);
		- **print_mutex** (mutex para o print para controlar quem vai printar o que);
		- **death_mutex** (mutex para alterar a variavel de morte);
		- **philos** (ponteiro para os filósofos);
		- **forks** (ponteiro para os garfos);
		- someone_died (verifica se alguem morreu);

---
### Compilação

Na raiz do projeto, entre na pasta "philo":
```bash
➜  philosophers git:(main) ✗ ls
philo  README.md
➜  philosophers git:(main) ✗ cd philo
➜  philo git:(main) ✗ 
➜  philo git:(main) ✗ ls
inc  Makefile  obj  philo  src
```

Após entrar na pasta, digite o comando para gerar o executável do projeto: 

```bash
make
```

Outros comandos:
| Comando | Descrição |
|---------|-----------|
| make clean | Limpa arquivos .o |
| make fclean | Limpa arquivos .o e arquivos executáveis. |
| make re | Recompila tudo|
| make valgrind ARGS="input" | Verifica vazamento de memória |

## Instruções ##

Após compilar o projeto, você deve executar o arquivo **philo** que foi gerado, com os seguintes argumentos:

```bash
./philo "<quantidade de filósofos> <tempo para morrer> <tempo para comer> <tempo para dormir> <argumento opcional[número de vezes que um filósofo tem que comer para ficar cheio]>"
```
Exemplo:
```bash
./philo 3 410 200 200
```
ou

```bash
./philo 3 410 200 200 3
```

Os argumentos não são passados ​​aleatoriamente; as seguintes entradas não são permitidas:

- Apenas o nome do programa;
- Cadeias vazias ou cadeias contendo apenas espaços;
- Argumentos que não sejam números;
- Um sinal (+ ou -) sem um número;
- Números negativos;
- Valores iguais a zero (para argumentos obrigatórios);
- Quantidade incorreta de argumentos;
- Números maiores que o limite de um int (overflow);
- Argumento opcional (n_meals) inválido ou menor/igual a zero;

---
Após executar o programa com os argumentos, ele imprimirá as ações que cada filósofo está fazendo:

```bash
➜  philo git:(main) ✗ ./philo 3 410 200 200 3
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
200 3 has taken a fork
400 1 is thinking
400 1 has taken a fork
400 2 is sleeping
400 3 has taken a fork
400 3 is eating
410 1 died
```

O programa só termina quando algum filósofo morre ou quando todos os filósofos realizam todas as suas refeições (caso tenha colocado).
## Critérios de Avaliação ##

O projeto é avaliado visando a lógica e o seu comportamento

- Não pode crasha, não pode dar segfault ou não entra em estado estranho.

- Um filósofo morre exatamente quando deveria. Se o input de morte foi ~400ms e um filósofo morrer tem que ter um died exatamente em ~400ms.

- Valores consistentes, ou seja, ninguém morre "enquanto está comendo".

- O programa não pode travar (deadlock), todos os filósofos pegam somente 1 garfo (isso trava o sistema, pois ninguem vai "soltar" o garfo enquanto não tiver comido, mas só podem comer se tiverem 2 garfos)

- Todos os filósofos comem, ninguém fica "esquecido" até morrer (starvation).

- Prints corretos, as mensagens não se misturam, se alguém morreu nada mais pode ser imprimido depois do "died" ou se todos ficaram "cheios", sendo feitas da seguinte forma:
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died

- Sem data race, que seria quando um dos subprocessos vai acessar uma váriavel, só que quando esse subprocesso entrou na função a váriavel tinha um valor e antes de terminar a função ela recebeu outro valor de outro subprocesso (isso pode ser testado com helgrind).

- Não deve haver vazamento de memória (isso é testado com valgrind).

- Outra coisa legal de se testar é que se o input for um que seja possivel todos os filósofos realizar as suas refeições até ficar "cheio/satisfeito", a quantidade tem que ser exatamente (número de filósofos * quantidade de refeições) até ficar satisfeito. Pode ser testado com o seguinte input:

```bash
./philo <input> | grep eating | wc -l
```
Exemplo:
```bash
➜  philo git:(main) ✗ ./philo 2 800 200 200 5 | grep eating | wc -l
10
```
(2 * 5 = 10)

---

## Recursos ##
Utilizei o ChatGPT (https://chatgpt.com/) para me ajudar a entender o conceitos das threads e de mutexes, organizar o projeto (definindo os próximos passos) e debugar um caso de deadlock que apresentava.
