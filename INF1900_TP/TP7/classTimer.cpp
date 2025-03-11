Timers::Timers(TypeTimer type, ModeTimer mode, uint16_t valeurCtc, uint16_t prescaler)
    : leType_(type), leMode_(mode), valeurCtc_(valeurCtc) {
    prescaler_= choisirPrescaler(prescaler);
    if (leType_ == TIMER1) {
        leMode_ = CTC;  // TIMER1 doit être en mode CTC pour calculer le delais
    } else if (leType_ == TIMER0 || leType_ == TIMER2) {
        leMode_ = PWM;  // TIMER0 et TIMER2 doivent être en mode PWM vu qu'on ne peut pas utiliser ;etimer1
    }
    if (mode == CTC) {
        configurationCTC();
    } else if (mode == PWM) {
        configurationPWM();
    } //else if(mode == NORMAL){
    //     configurationNormal();
    // }
} 

uint16_t Timers:: choisirPrescaler(uint16_t valeur){ //page 131 
    switch (leType_)
    {
       
    case TIMER0:
        if (valeur == 1)return (1<<CS00);
        if(valeur == 8)return (1<<CS01);
        if(valeur == 64)return (1<<CS00)|(1<<CS01);
        if (valeur == 256)return (1<<CS02);
        if (valeur ==1024)return (1<<CS00)|(1<<CS02);
     
       break;
    
    case TIMER2:
        if (valeur == 1) return (1<<CS20);
        if(valeur == 8) return (1<<CS21);
        if(valeur == 64) return (1<<CS20)|(1<<CS21);
        if (valeur == 256)return (1<<CS22);
        if (valeur == 1024) return (1<<CS20)|(1<<CS22);
    
        break;

    }
    return 0;
}

void Timers::configurationPWM(){ //130
    switch (leType_){
        case TIMER0:
        TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
        TCCR0B = (1 << CS01);    
        
        break;
        case TIMER2:

        TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
        TCCR2B = (1 << CS21);
        
        break;
    }
}
void Timers::ajustementPwm( uint8_t dureeA , uint8_t dureeB) {

    dutyCycle( dureeA , dureeB);
    configurationPWM();
}

void Timers::partirCompteur(){

    switch (leType_) {
    case TIMER0:
        TCCR0B |= prescaler_; //partir compteur en activant le prescaler (ChoisirPrescaler)
        break;
    case TIMER1:
        TCNT1 = 0;
        TCCR1B |= prescaler_;
        break;
    case TIMER2:
        TCCR2B |= prescaler_;
        break;
    }
}


void Timers::arretCompteur() {

    switch (leType_) {
    case TIMER0:
        TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); //tous bits a 0 = desactive prescaler
        TIMSK0 = 0;
        break;
    case TIMER1:
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        TIMSK1 =0;
        break;
    case TIMER2:
        TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
        TIMSK2 = 0;
        break;
    }
}

void Timers::configurationCTC() { //mode ctc -> bit WGMx1 = 1 et OCRxA = valeurCtc

    switch (leType_) {
    case TIMER0:
        TCNT0 = 0;
        TCCR0A = 0; //reinitialisation
        TCCR0A |= (1 << WGM01);
        OCR0A = valeurCtc_;
        break;
    case TIMER1: // 16 bits
        TCNT0 = 0;
        TCCR1B = 0; 
        TCCR1B |= (1 << WGM12);
        OCR1A = valeurCtc_;
        break;
    case TIMER2:
        TCNT2 = 0;
        TCCR2A = 0; 
        TCCR2A |= (1 << WGM21);
        OCR2A = valeurCtc_;
        break;
    }
}
void Timers::dutyCycle(uint16_t dureeA , uint16_t dureeB){

    switch (leType_) {

    case TIMER0:
        OCR0A = dureeA; // duty cycle pwm
        OCR0B = dureeB;
        break;
    case TIMER1:
        OCR1A = dureeA;
        break;
    case TIMER2:
        OCR2A = dureeA; // duty cycle pwm
        OCR2B = dureeB;
        break;
    }
}
uint16_t Timers::calculPourcentage(uint16_t pourcentage, uint16_t top){
    return (pourcentage * top)/100;
}
