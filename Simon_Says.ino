/* segmentos do display */
int a = 5;
int b = 6;
int c = 7;
int d = 8;
int e = 9;
int f = 10;
int g = 11;
int h = 12;

int eixoX = A0;
int eixoY = A1;
int eixoZ = 2;

void setup(){
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);

  pinMode(eixoX, INPUT);
  pinMode(eixoY, INPUT);
  pinMode(eixoZ, INPUT_PULLUP);
    
  limpa();

  randomSeed(analogRead(0));
  Serial.begin(9600);
}
/* a b d f g*/

/* variaveis que vão ser usadas */

#define MAX 5
#define QTD_SEQ 10

/*matriz das sequencias */
int seq[][MAX] = {{a,b,a,f,d},
                  {f,f,f,g,d},
                  {g,d,a,g,f},
                  {b,a,d,a,g},
                  {a,f,d,b,g},
                  {d,f,g,a,b},
                  {g,b,b,d,a},
                  {a,g,a,d,f},
                  {b,a,f,f,g},
                  {d,d,f,a,g}};
                


int cont = 0;
bool jogando = 0;
int jogo = 0;

bool ehB = 0;
bool ehF = 0;


/* printa o jogo que o player vai ter que decorar */ 

void mostra_jogo(int jogo){
  for(int i = 0; i < MAX; i++){
    ehB = (seq[jogo][i] == b);
    ehF = (seq[jogo][i] == f);
    
    digitalWrite(seq[jogo][i], HIGH); 
    if (ehB)  digitalWrite(c, HIGH);
    if (ehF)  digitalWrite(e, HIGH);
    
    delay(700);
    
    digitalWrite(seq[jogo][i], LOW);
    if (ehB)  digitalWrite(c, LOW);
    if (ehF)  digitalWrite(e, LOW);
    
    delay(700);
  }
}


/* print de perdeu */
void perdeu(){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  delay(2000);
  limpa();
  jogando = 0;
}

/* Mensagem da vitória */

#define WAIT_WIN 800

void letraG() {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);

    delay(WAIT_WIN);
    limpa();
}

void letraA() {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
        
    delay(WAIT_WIN);
    limpa();
}

void letraN() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
            
    delay(WAIT_WIN);
    limpa();
}

void letraH() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
            
    delay(WAIT_WIN);
    limpa();
}

void letraO() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
        
    delay(WAIT_WIN);
    limpa();
}

void letraU() {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
            
    delay(WAIT_WIN);
    limpa();
}

void ganhou(){
  letraG();
  letraA();
  letraN();
  letraH();
  letraO();
  letraU();

  jogando = 0;
}

/* acertou uma letra */

void ok(){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,LOW);
  delay(350);
  limpa();
}

/* limpa o display de 7 segmentos */ 
void limpa(){
  for(int i = 5; i <= 12; i++){
    digitalWrite(i,LOW);
  }
}

/* contagem antes de começar uma partidoa */
void tres() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(h, LOW);

  delay(1000);  // espera 1 segundo
  limpa();
}

void dois() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(h, LOW);

  delay(1000);  // espera 1 segundo
  limpa();
}

void um() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(h, LOW);

  delay(1000);  // espera 1 segundo
  limpa();
}

void zero() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(h, LOW);

  delay(1000);  // espera 1 segundo
  limpa();
}

void printNumeros() {
  tres();
  dois();
  um();
  zero();
}

/* Término do bloco de contagem pré-partida */

/* Funções para verificar se houve alguma ação observável com o joystick */
bool verifyX(int x) {
    return ((x > 200 && x < 800) || x == -1);
}

bool verifyY(int y) {
    return ((y > 200 && y < 800) || y == -1);
}

bool joystickParado(int x, int y, int z) {
    return (verifyX(x) && verifyY(y) && z);
}

/* 
  ~*~*~*~*~*~*~*~*~*    COMO FUNCIONA O JOYSTICK    ~*~*~*~*~*~*~*~*

  Joystick para CIMA:       X ~ 1022,   Y ~ 520  
  Joystick para BAIXO:      X ~ 0,    Y ~ 520
  Joystick para ESQUERDA:   X ~ 520,  Y ~ 0
  Joystick para DIREITA:    X ~ 520,  Y ~ 1020

  Aperta o Botão:   Z ~ 0
  nao aperta:     Z ~ 1

*/

bool cima(int x) {
    return (x > 800);
}

bool baixo(int x) {
    return (x < 200);
}

bool direita(int y) {
    return (y > 800);
}

bool esquerda(int y) {
    return (y < 200);
}

/* Fim das funções de verificação */

/* main */
void loop(){
    jogo = random(0,QTD_SEQ);     // [0,6)

    if(!jogando){
        int x = analogRead(eixoX);
        int y = analogRead(eixoY);
        int z = digitalRead(eixoZ);
        
        if(!joystickParado(x, y, z)){
            jogando = 1;
            printNumeros();   // 3 2 1 0
        }
        
    } else {
        mostra_jogo(jogo);
        printNumeros();
        mostra_jogo(jogo);

        for(int i = 0; i < MAX; i++){
            int x = -1;
            int y = -1;
            int z = 1;

            while(verifyX(x) && verifyY(y) && z){
                x = analogRead(eixoX);
                y = analogRead(eixoY);
                z = digitalRead(eixoZ);
            }

            /* Verifica se o usuario pôs a entrada correta */

            if(seq[jogo][i] == a){
                if(!cima(x)){
                    perdeu();
                    return;
                }
            }
            
            if(seq[jogo][i] == b){
                if(!direita(y)){
                    perdeu();
                    return;
                }
            }
            
            if(seq[jogo][i] == d){
                if(!baixo(x)){
                    perdeu();
                    return;
                }
            }
            
            if(seq[jogo][i] == f){
                if(!esquerda(y)){
                    perdeu();
                    return;
                }
            }
            
            if(seq[jogo][i] == g){
                if(z != 0) {  
                    perdeu();
                    return;
                }
            }
            
            /* se foi gera o ok */
            ok();
            
            /* verifica se ganhou */
            if(i == MAX - 1)  ganhou();
        }
    }
}
